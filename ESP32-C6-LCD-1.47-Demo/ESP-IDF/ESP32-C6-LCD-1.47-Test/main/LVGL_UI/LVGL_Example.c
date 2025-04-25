#include "LVGL_Example.h"
#include "lvgl.h"
#include "mqtt_app.h"
#include "simple_wifi_sta.h"

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
} disp_size_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void Onboard_create(lv_obj_t * parent);

static void ta_event_cb(lv_event_t * e);
void example1_increase_lvgl_tick(lv_timer_t * t);
/**********************
 *  STATIC VARIABLES
 **********************/
static disp_size_t disp_size;

static lv_obj_t * tv;
lv_style_t style_text_muted;
lv_style_t style_title;
static lv_style_t style_icon;
static lv_style_t style_bullet;



static const lv_font_t * font_large;
static const lv_font_t * font_normal;

static lv_timer_t * auto_step_timer;

static lv_timer_t * meter2_timer;

lv_obj_t * panel1_title;
lv_obj_t * SD_Size;
lv_obj_t * FlashSize;
lv_obj_t * Board_angle;
lv_obj_t * RTC_Time;
lv_obj_t * Wireless_Scan;

//*********************************** */

lv_obj_t *square_head;
lv_obj_t *label_head ;
lv_obj_t *label_icp;
lv_obj_t *label_temp;
lv_obj_t *label_wifi;

//*********************************** */


void IRAM_ATTR auto_switch(lv_timer_t * t)
{
  uint16_t page = lv_tabview_get_tab_act(tv);

  if (page == 0) { 
    lv_tabview_set_act(tv, 1, LV_ANIM_ON); 
  } else if (page == 3) {
    lv_tabview_set_act(tv, 2, LV_ANIM_ON); 
  }
}
void Lvgl_Example1(void){

  disp_size = DISP_SMALL;                            

  font_large = LV_FONT_DEFAULT;                             
  font_normal = LV_FONT_DEFAULT;                         
  
  lv_coord_t tab_h;
  tab_h = 45;
  #if LV_FONT_MONTSERRAT_18
    font_large     = &lv_font_montserrat_18;
  #else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_18 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
  #endif
  #if LV_FONT_MONTSERRAT_12
    font_normal    = &lv_font_montserrat_12;
  #else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_12 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
  #endif
  
  lv_style_init(&style_text_muted);
  lv_style_set_text_opa(&style_text_muted, LV_OPA_90);

  lv_style_init(&style_title);
  lv_style_set_text_font(&style_title, font_large);

  lv_style_init(&style_icon);
  lv_style_set_text_color(&style_icon, lv_theme_get_color_primary(NULL));
  lv_style_set_text_font(&style_icon, font_large);

  lv_style_init(&style_bullet);
  lv_style_set_border_width(&style_bullet, 0);
  lv_style_set_radius(&style_bullet, LV_RADIUS_CIRCLE);

  tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, tab_h);

  lv_obj_set_style_text_font(lv_scr_act(), font_large, 0);


  lv_obj_t * t1 = lv_tabview_add_tab(tv, "Medtronic");
  
  
  Onboard_create(t1);
}

void Lvgl_Example1_close(void)
{
  /*Delete all animation*/
  lv_anim_del(NULL, NULL);

  lv_timer_del(meter2_timer);
  meter2_timer = NULL;

  lv_obj_clean(lv_scr_act());

  lv_style_reset(&style_text_muted);
  lv_style_reset(&style_title);
  lv_style_reset(&style_icon);
  lv_style_reset(&style_bullet);
}


/**********************
*   STATIC FUNCTIONS
**********************/

static void Onboard_create(lv_obj_t * parent)
{

  /*Create a panel*/
  lv_obj_t * panel1 = lv_obj_create(parent);
  lv_obj_set_height(panel1, LV_SIZE_CONTENT);

  // lv_obj_t * panel1_title = lv_label_create(panel1);
  // lv_label_set_text(panel1_title, "Onboard parameter");
  // lv_obj_add_style(panel1_title, &style_title, 0);

  panel1_title = lv_textarea_create(panel1);
  lv_textarea_set_one_line(panel1_title, true);
  lv_textarea_set_placeholder_text(panel1_title, "24T00032");
  // lv_obj_add_event_cb(Wireless_Scan, ta_event_cb, LV_EVENT_ALL, NULL);

  lv_obj_t * SD_label = lv_label_create(panel1);
  lv_label_set_text(SD_label, "ICP");             //pressure
  lv_obj_add_style(SD_label, &style_text_muted, 0);

  SD_Size = lv_textarea_create(panel1);
  lv_textarea_set_one_line(SD_Size, true);
  // lv_textarea_set_placeholder_text(SD_Size, "SD Size");
  lv_obj_add_event_cb(SD_Size, ta_event_cb, LV_EVENT_ALL, NULL);

  lv_obj_t * Flash_label = lv_label_create(panel1);
  lv_label_set_text(Flash_label, "ICT");                //temperature
  lv_obj_add_style(Flash_label, &style_text_muted, 0);

  FlashSize = lv_textarea_create(panel1);
  lv_textarea_set_one_line(FlashSize, true);
  // lv_textarea_set_placeholder_text(FlashSize, "Flash Size");
  lv_obj_add_event_cb(FlashSize, ta_event_cb, LV_EVENT_ALL, NULL);

  lv_obj_t * Wireless_label = lv_label_create(panel1);
  lv_label_set_text(Wireless_label, "Wireless scan");
  lv_obj_add_style(Wireless_label, &style_text_muted, 0);

  Wireless_Scan = lv_textarea_create(panel1);
  lv_textarea_set_one_line(Wireless_Scan, true);
  lv_textarea_set_placeholder_text(Wireless_Scan, "Wireless number");
  lv_obj_add_event_cb(Wireless_Scan, ta_event_cb, LV_EVENT_ALL, NULL);

  // 器件布局
  static lv_coord_t grid_main_col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static lv_coord_t grid_main_row_dsc[] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(parent, grid_main_col_dsc, grid_main_row_dsc);


  /*Create the top panel*/
  static lv_coord_t grid_1_col_dsc[] = {LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};
  static lv_coord_t grid_1_row_dsc[] = {LV_GRID_CONTENT, /*Avatar*/
                                        LV_GRID_CONTENT, /*Name*/
                                        LV_GRID_CONTENT, /*Description*/
                                        LV_GRID_CONTENT, /*Email*/
                                        LV_GRID_CONTENT, /*Phone number*/
                                        LV_GRID_CONTENT, /*Button1*/
                                        LV_GRID_CONTENT, /*Button2*/
                                        LV_GRID_TEMPLATE_LAST
                                        };

  // lv_obj_set_grid_dsc_array(panel1, grid_1_col_dsc, grid_1_row_dsc);


  static lv_coord_t grid_2_col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static lv_coord_t grid_2_row_dsc[] = {
    LV_GRID_CONTENT,  /*Title*/
    1,                /*Separator*/
    LV_GRID_CONTENT,  /*Box title*/
    35,               /*Box*/
    LV_GRID_CONTENT,  /*Box title*/
    35,               /*Box*/
    LV_GRID_CONTENT,  /*Box title*/
    35,               /*Box*/
    LV_GRID_CONTENT,  /*Box title*/
    35,               /*Box*/
    LV_GRID_CONTENT,  /*Box title*/
    35,               /*Box*/
    LV_GRID_CONTENT,  /*Box title*/
    35,               /*Box*/
    LV_GRID_TEMPLATE_LAST               
  };

  // lv_obj_set_grid_dsc_array(panel2, grid_2_col_dsc, grid_2_row_dsc);
  // lv_obj_set_grid_dsc_array(panel3, grid_2_col_dsc, grid_2_row_dsc);

  lv_obj_set_grid_cell(panel1, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_START, 0, 1);
  lv_obj_set_grid_dsc_array(panel1, grid_2_col_dsc, grid_2_row_dsc);
  lv_obj_set_grid_cell(panel1_title, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
  lv_obj_set_grid_cell(SD_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 2, 1);
  lv_obj_set_grid_cell(SD_Size, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_CENTER, 3, 1);
  lv_obj_set_grid_cell(Flash_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 4, 1);
  lv_obj_set_grid_cell(FlashSize, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_CENTER, 5, 1);
  lv_obj_set_grid_cell(Wireless_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 6, 1);
  lv_obj_set_grid_cell(Wireless_Scan, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_CENTER, 7, 1);

  // 器件布局 END
  
  auto_step_timer = lv_timer_create(example1_increase_lvgl_tick, 100, NULL);
}

void example1_increase_lvgl_tick(lv_timer_t * t)
{
  char buf[100]={0}; 
  
  snprintf(buf, sizeof(buf), "%ld MB\r\n", SDCard_Size);
  lv_textarea_set_placeholder_text(SD_Size, buf);
  snprintf(buf, sizeof(buf), "%ld MB\r\n", Flash_Size);
  lv_textarea_set_placeholder_text(FlashSize, buf);
  if(Scan_finish)
    snprintf(buf, sizeof(buf), "W: %d  B: %d    OK.\r\n",WIFI_NUM,BLE_NUM);
    // snprintf(buf, sizeof(buf), "WIFI: %d     ..OK.\r\n",WIFI_NUM);
  else
    snprintf(buf, sizeof(buf), "W: %d  B: %d\r\n",WIFI_NUM,BLE_NUM);
    // snprintf(buf, sizeof(buf), "WIFI: %d  \r\n",WIFI_NUM);
  lv_textarea_set_placeholder_text(Wireless_Scan, buf);
}

static void ta_event_cb(lv_event_t * e)
{
}



static void lvgl_creat_element(lv_font_t label_font, uint32_t bk_color, uint32_t label_color, lv_obj_t* bk_obj, lv_obj_t* label_obj){

  lv_style_t square_style;
  lv_style_init(&square_style);
  lv_style_set_bg_color(&square_style, lv_color_hex(bk_color)); //blue
  lv_style_set_border_width(&square_style, 0);
  lv_style_set_bg_opa(&square_style, LV_OPA_COVER);
  lv_style_set_radius(&square_style, 0);
  
  lv_style_t label_style;
  lv_style_init(&label_style);
  lv_style_set_text_color(&label_style, lv_color_hex(label_color)); //white
  lv_style_set_text_font(&label_style, &label_font);
  // lv_style_set_transform_angle(&label_style, 900);
  // lv_style_set_transform_pivot_x(&label_style, 0);
  // lv_style_set_transform_pivot_y(&label_style, 0);
  
  // lv_obj_t *square = lv_obj_create(lv_scr_act());
  lv_obj_set_size(bk_obj, 172, 40);
  lv_obj_add_style(bk_obj, &square_style, 0);
  lv_obj_align(bk_obj, LV_ALIGN_TOP_LEFT, 0, 0);

  // lv_obj_t *label = lv_label_create(square);
  // lv_label_set_text(label_obj, "Medtronic ICP Kits");
  lv_obj_add_style(label_obj, &label_style, 0);
  lv_obj_align(label_obj, LV_ALIGN_CENTER, 0, 0);
}


void lvgl_update_head_block(char* id){
  char buf[64];
  snprintf(buf,sizeof(buf),"{\"name\":\"\"%s,\"msg\":\"%s\"}","probe_sn",id);
  mqtt_publish_message(buf);
  lv_label_set_text(label_head, id);

}

void lvgl_head_block(void){

  disp_size = DISP_SMALL;                            
  font_large = LV_FONT_DEFAULT;                             
  font_normal = LV_FONT_DEFAULT;  

  static lv_style_t square_style;
  lv_style_init(&square_style);
  lv_style_set_bg_color(&square_style, lv_color_hex(0xFFFFFF)); //blue,0x007AFF
  lv_style_set_border_width(&square_style, 0);
  lv_style_set_bg_opa(&square_style, LV_OPA_COVER);
  lv_style_set_radius(&square_style, 0);
  
  static lv_style_t label_style;
  lv_style_init(&label_style);
  lv_style_set_text_color(&label_style, lv_color_hex(0x000000)); //white
  lv_style_set_text_font(&label_style, &lv_font_montserrat_24);
  
  square_head = lv_obj_create(lv_scr_act());
  lv_obj_set_size(square_head, 172, 40);
  lv_obj_add_style(square_head, &square_style, 0);
  lv_obj_align(square_head, LV_ALIGN_TOP_LEFT, 0, 0);

  label_head = lv_label_create(square_head);
  lv_label_set_text(label_head, "--------");
  lv_obj_add_style(label_head, &label_style, 0);
  lv_obj_align(label_head, LV_ALIGN_CENTER, 0, 0);

}


void lvgl_update_icp_block(float icp, bool is_push)
{
 
  if(is_push){
    char mqtt_msg[64];
    snprintf(mqtt_msg,sizeof(mqtt_msg),"{\"n\":\"%s\",\"v\":%d}","icp",(int)icp);
    mqtt_publish_message(mqtt_msg);
  }
  else
  {
    
    char buf[32];
    snprintf(buf,sizeof(buf),"%d",(int)(icp/100));
    lv_label_set_text(label_icp,buf);
  }

}


void lvgl_icp_block(void)
{

  disp_size = DISP_SMALL;                            
  font_large = LV_FONT_DEFAULT;                             
  font_normal = LV_FONT_DEFAULT;  

  static lv_style_t square_style;
  lv_style_init(&square_style);
  lv_style_set_bg_color(&square_style, lv_color_hex(0x154360)); //blue,0x007AFF
  lv_style_set_border_width(&square_style, 0);
  lv_style_set_bg_opa(&square_style, LV_OPA_COVER);
  lv_style_set_radius(&square_style, 0);
  
  static lv_style_t label_style;
  lv_style_init(&label_style);
  lv_style_set_text_color(&label_style, lv_color_hex(0xFFFFFF)); //white
  lv_style_set_text_font(&label_style, &lv_font_montserrat_48);
  
  lv_obj_t *square = lv_obj_create(lv_scr_act());
  lv_obj_set_size(square, 172, 100);
  lv_obj_add_style(square, &square_style, 0);
  lv_obj_align(square, LV_ALIGN_TOP_LEFT, 0, 40);

  label_icp = lv_label_create(square);
  lv_label_set_text(label_icp, "---");
  lv_obj_add_style(label_icp, &label_style, 0);
  lv_obj_align(label_icp, LV_ALIGN_BOTTOM_MID, 0, 0);

  static lv_style_t label_style_mmhg;
  lv_style_init(&label_style_mmhg);
  lv_style_set_text_color(&label_style_mmhg, lv_color_hex(0xFFFFFF)); //white
  lv_style_set_text_font(&label_style_mmhg, &lv_font_montserrat_14);

  lv_obj_t *label_mmhg = lv_label_create(square);
  lv_label_set_text(label_mmhg, "ICP(mmHg) [-40/150]");
  lv_obj_add_style(label_mmhg, &label_style_mmhg, 0);
  lv_obj_align(label_mmhg, LV_ALIGN_TOP_RIGHT, 0, 0);

}


void lvgl_update_temp_block(float temp)
{
  char buf[32];
  snprintf(buf,sizeof(buf),"%.1f",temp);

  char mqtt_msg[64];
  snprintf(mqtt_msg,sizeof(mqtt_msg),"{\"n\":\"%s\",\"v\":%d}","ict",(int)(temp*100));
  mqtt_publish_message(mqtt_msg);
  lv_label_set_text(label_temp,buf);
}

void lvgl_temp_block(void)
{

  disp_size = DISP_SMALL;                            
  font_large = LV_FONT_DEFAULT;                             
  font_normal = LV_FONT_DEFAULT;  

  static lv_style_t square_style;
  lv_style_init(&square_style);
  lv_style_set_bg_color(&square_style, lv_color_hex(0xA569BD)); //blue,0x007AFF
  lv_style_set_border_width(&square_style, 0);
  lv_style_set_bg_opa(&square_style, LV_OPA_COVER);
  lv_style_set_radius(&square_style, 0);
  
  static lv_style_t label_style;
  lv_style_init(&label_style);
  lv_style_set_text_color(&label_style, lv_color_hex(0xFFFFFF)); //0x000000
  lv_style_set_text_font(&label_style, &lv_font_montserrat_48);

  lv_obj_t *square = lv_obj_create(lv_scr_act());
  lv_obj_set_size(square, 172, 100);
  lv_obj_add_style(square, &square_style, 0);
  lv_obj_align(square, LV_ALIGN_TOP_LEFT, 0, 141);

  label_temp = lv_label_create(square);
  lv_label_set_text(label_temp, "--.-");
  lv_obj_add_style(label_temp, &label_style, 0);
  lv_obj_align(label_temp, LV_ALIGN_BOTTOM_MID, 0, 0);

  static lv_style_t label_style_mmhg;
  lv_style_init(&label_style_mmhg);
  lv_style_set_text_color(&label_style_mmhg, lv_color_hex(0xFFFFFF)); //white
  lv_style_set_text_font(&label_style_mmhg, &lv_font_montserrat_14);

  lv_obj_t *label_mmhg = lv_label_create(square);
  lv_label_set_text(label_mmhg, "Temp(°C) [20/45]");
  lv_obj_add_style(label_mmhg, &label_style_mmhg, 0);
  lv_obj_align(label_mmhg, LV_ALIGN_TOP_RIGHT, 0, 0);

}

void lvgl_update_wifi_mqtt()
{
    char wifi_addr[32];
    if(wifi_get_ip_addr(wifi_addr)==ESP_OK)
    {
      if(mqtt_is_connected()){
        lv_label_set_text_fmt(label_wifi,"%s (OK)",wifi_addr);
      }
      else{
        lv_label_set_text_fmt(label_wifi,"%s (FAIL)",wifi_addr);
      }
    }
    else
    {
      lv_label_set_text(label_wifi,"--.--.--.-- (FAIL)");
    }
}

void lvgl_update_wifi_block(const char* ip_addr)
{
  lv_label_set_text(label_wifi,ip_addr);
}

void lvgl_wifi_block(void)
{

  disp_size = DISP_SMALL;                            
  font_large = LV_FONT_DEFAULT;                             
  font_normal = LV_FONT_DEFAULT;  

  static lv_style_t square_style;
  lv_style_init(&square_style);
  lv_style_set_bg_color(&square_style, lv_color_hex(0xCC6699)); //blue,0x007AFF
  lv_style_set_border_width(&square_style, 0);
  lv_style_set_bg_opa(&square_style, LV_OPA_COVER);
  lv_style_set_radius(&square_style, 0);
  
  static lv_style_t label_style;
  lv_style_init(&label_style);
  lv_style_set_text_color(&label_style, lv_color_hex(0xFFFFFF)); //0x000000
  lv_style_set_text_font(&label_style, &lv_font_montserrat_16);

  lv_obj_t *square_wifi = lv_obj_create(lv_scr_act());
  lv_obj_set_size(square_wifi, 172, 40);
  lv_obj_add_style(square_wifi, &square_style, 0);
  lv_obj_align(square_wifi, LV_ALIGN_TOP_LEFT, 0, 242);

  label_wifi = lv_label_create(square_wifi);
  lv_label_set_text(label_wifi, "10.152.177.194");
  lv_obj_add_style(label_wifi, &label_style, 0);
  lv_obj_align(label_wifi, LV_ALIGN_BOTTOM_MID, 0, 0);

}

void lvgl_battery_block(void)
{

  disp_size = DISP_SMALL;                            
  font_large = LV_FONT_DEFAULT;                             
  font_normal = LV_FONT_DEFAULT;  

  static lv_style_t square_style;
  lv_style_init(&square_style);
  lv_style_set_bg_color(&square_style, lv_color_hex(0x66CC00)); //blue,0x007AFF
  lv_style_set_border_width(&square_style, 0);
  lv_style_set_bg_opa(&square_style, LV_OPA_COVER);
  lv_style_set_radius(&square_style, 0);
  
  static lv_style_t label_style;
  lv_style_init(&label_style);
  lv_style_set_text_color(&label_style, lv_color_hex(0xFFFFFF)); //0x000000
  lv_style_set_text_font(&label_style, &lv_font_montserrat_16);

  lv_obj_t *square_battery = lv_obj_create(lv_scr_act());
  lv_obj_set_size(square_battery, 60, 35);
  lv_obj_add_style(square_battery, &square_style, 0);
  lv_obj_align(square_battery, LV_ALIGN_TOP_LEFT, 0, 283);

  lv_obj_t *label_battery = lv_label_create(square_battery);
  lv_label_set_text(label_battery, "90\%");
  lv_obj_add_style(label_battery, &label_style, 0);
  lv_obj_align(label_battery, LV_ALIGN_BOTTOM_MID, 0, 0);

}

void lvgl_bluetooth_block(void)
{

  disp_size = DISP_SMALL;                            
  font_large = LV_FONT_DEFAULT;                             
  font_normal = LV_FONT_DEFAULT;  

  static lv_style_t square_style;
  lv_style_init(&square_style);
  lv_style_set_bg_color(&square_style, lv_color_hex(0x0000CC)); //blue,0x007AFF
  lv_style_set_border_width(&square_style, 0);
  lv_style_set_bg_opa(&square_style, LV_OPA_COVER);
  lv_style_set_radius(&square_style, 0);
  
  static lv_style_t label_style;
  lv_style_init(&label_style);
  lv_style_set_text_color(&label_style, lv_color_hex(0xFFFFFF)); //0x000000
  lv_style_set_text_font(&label_style, &lv_font_montserrat_16);

  lv_obj_t *square_bk = lv_obj_create(lv_scr_act());
  lv_obj_set_size(square_bk, 50, 35);
  lv_obj_add_style(square_bk, &square_style, 0);
  lv_obj_align(square_bk, LV_ALIGN_TOP_LEFT, 61, 283);

  lv_obj_t *label_bk = lv_label_create(square_bk);
  lv_label_set_text(label_bk, "BT");
  lv_obj_add_style(label_bk, &label_style, 0);
  lv_obj_align(label_bk, LV_ALIGN_BOTTOM_MID, 0, 0);

}