#include "base64.h"
#include <stddef.h>

enum {
    BAD         = 0xFF,  /* invalid encoding */
    PAD         = '=',
    PEM_LINE_SZ = 64
};


static
const byte base64Encode[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                              'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                              'U', 'V', 'W', 'X', 'Y', 'Z',
                              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                              'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                              'u', 'v', 'w', 'x', 'y', 'z',
                              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                              '+', '/'
                            };

/* make sure *i (idx) won't exceed max, store and possibly escape to out,
 * raw means use e w/o decode,  0 on success */
static int CEscape(int escaped, byte e, byte* out, word32* i, word32 max,
                  int raw, int getSzOnly)
{
    int    doEscape = 0;
    word32 needed = 1;
    word32 idx = *i;

    byte basic;
    byte plus    = 0;
    byte equals  = 0;
    byte newline = 0;

    if (raw)
        basic = e;
    else
        basic = base64Encode[e];

    /* check whether to escape. Only escape for EncodeEsc */
    if (escaped == WC_ESC_NL_ENC) {
        switch ((char)basic) {
            case '+' :
                plus     = 1;
                doEscape = 1;
                needed  += 2;
                break;
            case '=' :
                equals   = 1;
                doEscape = 1;
                needed  += 2;
                break;
            case '\n' :
                newline  = 1;
                doEscape = 1;
                needed  += 2;
                break;
            default:
                /* do nothing */
                break;
        }
    }

    /* check size */
    if ( (idx+needed) > max && !getSzOnly) {
        return -132;
    }

    /* store it */
    if (doEscape == 0) {
        if(getSzOnly)
            idx++;
        else
            out[idx++] = basic;
    }
    else {
        if(getSzOnly)
            idx+=3;
        else {
            out[idx++] = '%';  /* start escape */

            if (plus) {
                out[idx++] = '2';
                out[idx++] = 'B';
            }
            else if (equals) {
                out[idx++] = '3';
                out[idx++] = 'D';
            }
            else if (newline) {
                out[idx++] = '0';
                out[idx++] = 'A';
            }
        }
    }
    *i = idx;

    return 0;
}

/* internal worker, handles both escaped and normal line endings.
   If out buffer is NULL, will return sz needed in outLen */
static int DoBase64_Encode(const byte* in, word32 inLen, byte* out,
                           word32* outLen, int escaped)
{
    int    ret = 0;
    word32 i = 0,
           j = 0,
           n = 0;   /* new line counter */

    int    getSzOnly = (out == NULL);

    word32 outSz = (inLen + 3 - 1) / 3 * 4;
    word32 addSz = (outSz + PEM_LINE_SZ - 1) / PEM_LINE_SZ;  /* new lines */

    if (escaped == WC_ESC_NL_ENC)
        addSz *= 3;   /* instead of just \n, we're doing %0A triplet */
    else if (escaped == WC_NO_NL_ENC)
        addSz = 0;    /* encode without \n */

    outSz += addSz;

    /* if escaped we can't predetermine size for one pass encoding, but
     * make sure we have enough if no escapes are in input
     * Also need to ensure outLen valid before dereference */
    if (!outLen || (outSz > *outLen && !getSzOnly)) return -2;

    while (inLen > 2) {
        byte b1 = in[j++];
        byte b2 = in[j++];
        byte b3 = in[j++];

        /* encoded idx */
        byte e1 = b1 >> 2;
        byte e2 = (byte)(((b1 & 0x3) << 4) | (b2 >> 4));
        byte e3 = (byte)(((b2 & 0xF) << 2) | (b3 >> 6));
        byte e4 = b3 & 0x3F;

        /* store */
        ret = CEscape(escaped, e1, out, &i, *outLen, 0, getSzOnly);
        if (ret != 0) break;
        ret = CEscape(escaped, e2, out, &i, *outLen, 0, getSzOnly);
        if (ret != 0) break;
        ret = CEscape(escaped, e3, out, &i, *outLen, 0, getSzOnly);
        if (ret != 0) break;
        ret = CEscape(escaped, e4, out, &i, *outLen, 0, getSzOnly);
        if (ret != 0) break;

        inLen -= 3;

        /* Insert newline after PEM_LINE_SZ, unless no \n requested */
        if (escaped != WC_NO_NL_ENC && (++n % (PEM_LINE_SZ/4)) == 0 && inLen){
            ret = CEscape(escaped, '\n', out, &i, *outLen, 1, getSzOnly);
            if (ret != 0) break;
        }
    }

    /* last integral */
    if (inLen && ret == 0) {
        int twoBytes = (inLen == 2);

        byte b1 = in[j++];
        byte b2 = (twoBytes) ? in[j++] : 0;

        byte e1 = b1 >> 2;
        byte e2 = (byte)(((b1 & 0x3) << 4) | (b2 >> 4));
        byte e3 = (byte)((b2 & 0xF) << 2);

        ret = CEscape(escaped, e1, out, &i, *outLen, 0, getSzOnly);
        if (ret == 0)
            ret = CEscape(escaped, e2, out, &i, *outLen, 0, getSzOnly);
        if (ret == 0) {
            /* third */
            if (twoBytes)
                ret = CEscape(escaped, e3, out, &i, *outLen, 0, getSzOnly);
            else
                ret = CEscape(escaped, '=', out, &i, *outLen, 1, getSzOnly);
        }
        /* fourth always pad */
        if (ret == 0)
            ret = CEscape(escaped, '=', out, &i, *outLen, 1, getSzOnly);
    }

    if (ret == 0 && escaped != WC_NO_NL_ENC)
        ret = CEscape(escaped, '\n', out, &i, *outLen, 1, getSzOnly);

    if (i != outSz && escaped != 1 && ret == 0)
        return -154;

    *outLen = i;
    if(ret == 0)
        return getSzOnly ? -202 : 0;
    return ret;
}

/* Base64 Encode, PEM style, with \n line endings */
int Base64_Encode(const byte* in, word32 inLen, byte* out, word32* outLen)
{
    return DoBase64_Encode(in, inLen, out, outLen, WC_STD_ENC);
}


/* Base64 Encode, with %0A escaped line endings instead of \n */
int Base64_EncodeEsc(const byte* in, word32 inLen, byte* out, word32* outLen)
{
    return DoBase64_Encode(in, inLen, out, outLen, WC_ESC_NL_ENC);
}

int Base64_Encode_NoNl(const byte* in, word32 inLen, byte* out, word32* outLen)
{
    return DoBase64_Encode(in, inLen, out, outLen, WC_NO_NL_ENC);
}


static
const byte base64Decode[] = { 62, BAD, BAD, BAD, 63,   /* + starts at 0x2B */
                              52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
                              BAD, BAD, BAD, BAD, BAD, BAD, BAD,
                              0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                              10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                              20, 21, 22, 23, 24, 25,
                              BAD, BAD, BAD, BAD, BAD, BAD,
                              26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
                              36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
                              46, 47, 48, 49, 50, 51
                            };


int Base64_Decode(const byte* in, word32 inLen, byte* out, word32* outLen)
{
    word32 i = 0;
    word32 j = 0;
    word32 plainSz = inLen - ((inLen + (PEM_LINE_SZ - 1)) / PEM_LINE_SZ );
    const byte maxIdx = (byte)sizeof(base64Decode) + 0x2B - 1;

    plainSz = (plainSz * 3 + 3) / 4;
    if (plainSz > *outLen) return -173;

    while (inLen > 3) {
        byte b1, b2, b3;
        byte e1 = in[j++];
        byte e2 = in[j++];
        byte e3 = in[j++];
        byte e4 = in[j++];

        int pad3 = 0;
        int pad4 = 0;

        if (e1 == 0)            /* end file 0's */
            break;
        if (e3 == PAD)
            pad3 = 1;
        if (e4 == PAD)
            pad4 = 1;

        if (e1 < 0x2B || e2 < 0x2B || e3 < 0x2B || e4 < 0x2B) {
            return -154;
        }

        if (e1 > maxIdx || e2 > maxIdx || e3 > maxIdx || e4 > maxIdx) {
            return -154;
        }

        e1 = base64Decode[e1 - 0x2B];
        e2 = base64Decode[e2 - 0x2B];
        e3 = (e3 == PAD) ? 0 : base64Decode[e3 - 0x2B];
        e4 = (e4 == PAD) ? 0 : base64Decode[e4 - 0x2B];

        b1 = (byte)((e1 << 2) | (e2 >> 4));
        b2 = (byte)(((e2 & 0xF) << 4) | (e3 >> 2));
        b3 = (byte)(((e3 & 0x3) << 6) | e4);

        out[i++] = b1;
        if (!pad3)
            out[i++] = b2;
        if (!pad4)
            out[i++] = b3;
        else
            break;

        inLen -= 4;
        if (inLen && (in[j] == ' ' || in[j] == '\r' || in[j] == '\n')) {
            byte endLine = in[j++];
            inLen--;
            while (inLen && endLine == ' ') {   /* allow trailing whitespace */
                endLine = in[j++];
                inLen--;
            }
            if (endLine == '\r') {
                if (inLen) {
                    endLine = in[j++];
                    inLen--;
                }
            }
            if (endLine != '\n') {
                return -154;
            }
        }
    }
    *outLen = i;

    return 0;
}
