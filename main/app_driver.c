/* Switch demo implementation using button and RGB LED
   
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <sdkconfig.h>

#include <iot_button.h>
#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_params.h> 

#include <app_reset.h>
#include <ws2812_led.h>
#include "app_priv.h"

/* This is the button that is used for toggling the power */
#define BUTTON1_GPIO          27
#define BUTTON2_GPIO          14
#define BUTTON3_GPIO          12
#define BUTTON4_GPIO          13
#define BUTTON_ACTIVE_LEVEL  0

/* This is the GPIO on which the power will be set */
#define OUTPUT1_GPIO    21
#define OUTPUT2_GPIO    19
#define OUTPUT3_GPIO    18
#define OUTPUT4_GPIO    5
static bool g_power_state = DEFAULT_POWER;

/* These values correspoind to H,S,V = 120,100,10 */
#define DEFAULT_RED     0
#define DEFAULT_GREEN   25
#define DEFAULT_BLUE    0

#define WIFI_RESET_BUTTON_TIMEOUT       3
#define FACTORY_RESET_BUTTON_TIMEOUT    10

static void app_indicator_set(bool state)
{
    if (state) {
        ws2812_led_set_rgb(DEFAULT_RED, DEFAULT_GREEN, DEFAULT_BLUE);
    } else {
        ws2812_led_clear();
    }
}

static void app_indicator_init(void)
{
    ws2812_led_init();
    app_indicator_set(g_power_state);
}
static void push_btn1_cb(void *arg)
{
    //bool new_state = !g_power_state;
    app_driver_set_state(0);
    esp_rmaker_param_update_and_report(
            esp_rmaker_device_get_param_by_name(switch_device, ESP_RMAKER_DEF_POWER_NAME),
            esp_rmaker_bool(1));
}
static void release_btn1_cb(void *arg)
{
    //bool new_state = !g_power_state;
    app_driver_set_state(1);
    esp_rmaker_param_update_and_report(
            esp_rmaker_device_get_param_by_name(switch_device, ESP_RMAKER_DEF_POWER_NAME),
            esp_rmaker_bool(0));
}

static void push_btn2_cb(void *arg)
{
    //app_driver_set_state2(0);
    gpio_set_level(OUTPUT2_GPIO, 0);
    esp_rmaker_param_update_and_report(
            esp_rmaker_device_get_param_by_name(switch2_device, ESP_RMAKER_DEF_POWER_NAME),
            esp_rmaker_bool(1));
}
static void release_btn2_cb(void *arg)
{
    //app_driver_set_state2(1);
    gpio_set_level(OUTPUT2_GPIO, 1);
    esp_rmaker_param_update_and_report(
            esp_rmaker_device_get_param_by_name(switch2_device, ESP_RMAKER_DEF_POWER_NAME),
            esp_rmaker_bool(0));
}
static void set_power_state(bool target)
{
    gpio_set_level(OUTPUT1_GPIO, target);
    app_indicator_set(target);
}
static void set_power_state2(bool target)
{
    gpio_set_level(OUTPUT2_GPIO, target);
    app_indicator_set(target);
}

void app_driver_init()
{
    button_handle_t btn1_handle = iot_button_create(BUTTON1_GPIO, BUTTON_ACTIVE_LEVEL);
    if (btn1_handle) {
        /* Register a callback for a button tap (short press) event */
        iot_button_set_evt_cb(btn1_handle, BUTTON_CB_PUSH, push_btn1_cb, NULL);
        iot_button_set_evt_cb(btn1_handle, BUTTON_CB_RELEASE, release_btn1_cb, NULL);
        /* Register Wi-Fi reset and factory reset functionality on same button */
        //app_reset_button_register(btn_handle, WIFI_RESET_BUTTON_TIMEOUT, FACTORY_RESET_BUTTON_TIMEOUT);
    }
    button_handle_t btn2_handle = iot_button_create(BUTTON2_GPIO, BUTTON_ACTIVE_LEVEL);
    if (btn2_handle) {
        /* Register a callback for a button tap (short press) event */
        iot_button_set_evt_cb(btn2_handle, BUTTON_CB_PUSH, push_btn2_cb, NULL);
        iot_button_set_evt_cb(btn2_handle, BUTTON_CB_RELEASE, release_btn2_cb, NULL);
        /* Register Wi-Fi reset and factory reset functionality on same button */
        //app_reset_button_register(btn_handle, WIFI_RESET_BUTTON_TIMEOUT, FACTORY_RESET_BUTTON_TIMEOUT);
    }
    button_handle_t btn3_handle = iot_button_create(BUTTON3_GPIO, BUTTON_ACTIVE_LEVEL);
    if (btn3_handle) {
        /* Register a callback for a button tap (short press) event */
       // iot_button_set_evt_cb(btn3_handle, BUTTON_CB_PUSH, push_btn3_cb, NULL);
       // iot_button_set_evt_cb(btn3_handle, BUTTON_CB_RELEASE, release_btn3_cb, NULL);
        /* Register Wi-Fi reset and factory reset functionality on same button */
        //app_reset_button_register(btn_handle, WIFI_RESET_BUTTON_TIMEOUT, FACTORY_RESET_BUTTON_TIMEOUT);
    }
    button_handle_t btn4_handle = iot_button_create(BUTTON4_GPIO, BUTTON_ACTIVE_LEVEL);
    if (btn4_handle) {
        /* Register a callback for a button tap (short press) event */
        //iot_button_set_evt_cb(btn4_handle, BUTTON_CB_PUSH, push_btn4_cb, NULL);
        //iot_button_set_evt_cb(btn4_handle, BUTTON_CB_RELEASE, release_btn4_cb, NULL);
        /* Register Wi-Fi reset and factory reset functionality on same button */
        //app_reset_button_register(btn_handle, WIFI_RESET_BUTTON_TIMEOUT, FACTORY_RESET_BUTTON_TIMEOUT);
    }

    /* Configure power */
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = 1,
    };
    io_conf.pin_bit_mask = ((uint64_t)1 << OUTPUT1_GPIO);
    /* Configure the GPIO */
    gpio_config(&io_conf);

    app_indicator_init();
}

int IRAM_ATTR app_driver_set_state(bool state)
{
    if(g_power_state != state) {
        g_power_state = state;
        set_power_state(g_power_state);
    }
    return ESP_OK;
}
int IRAM_ATTR app_driver_set_state2(bool state)
{
    
 if(g_power_state != state) {
        g_power_state = state;
        set_power_state2(g_power_state);
    }
    return ESP_OK;
}

bool app_driver_get_state(void)
{
    return g_power_state;
}