/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#ifndef GATT_SVR_H
#define GATT_SVR_H

/* Includes */
/* NimBLE GATT APIs */
#include "host/ble_gatt.h"
#include "services/gatt/ble_svc_gatt.h"

/* NimBLE GAP APIs */
#include "host/ble_gap.h"

/* Public function declarations */
int  gatt_svc_init(void);

void gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg);

void gatt_svr_subscribe_cb(struct ble_gap_event *event);

//sening message to client
void send_heart_rate_indication(void);

void send_heart_rate_notify(void);

void send_sensor_notify(void);


void send_sensor_notify_osmbuf(struct os_mbuf *om);


#endif // GATT_SVR_H
