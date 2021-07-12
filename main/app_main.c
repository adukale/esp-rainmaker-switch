/* Switch Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <iot_button.h>
#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_ota.h>
#include <esp_rmaker_schedule.h>
#include <esp_rmaker_console.h>

#include <esp_rmaker_common_events.h>

#include <app_wifi.h>

#include "app_priv.h"

static const char *TAG = "app_main";
esp_rmaker_device_t *switch_device;
esp_rmaker_device_t *switch2_device;
esp_rmaker_device_t *switch3_device;
esp_rmaker_device_t *switch4_device;
esp_rmaker_device_t *switch5_device;
esp_rmaker_device_t *switch6_device;
esp_rmaker_device_t *switch7_device;
esp_rmaker_device_t *switch8_device;

/* Callback to handle commands received from the RainMaker cloud */

static esp_err_t write_cb(const esp_rmaker_device_t *device, const esp_rmaker_param_t *param,
            const esp_rmaker_param_val_t val, void *priv_data, esp_rmaker_write_ctx_t *ctx)
{
    if (ctx) {
        ESP_LOGI(TAG, "Received write request via : %s", esp_rmaker_device_cb_src_to_str(ctx->src));
    }
    if (strcmp(esp_rmaker_param_get_name(param), ESP_RMAKER_DEF_POWER_NAME) == 0) {
        ESP_LOGI(TAG, "Received value = %s for %s - %s",
                val.val.b? "true" : "false", esp_rmaker_device_get_name(device),
        esp_rmaker_param_get_name(param));
        //app_driver_set_state(val.val.b);
        //esp_rmaker_param_update_and_report(param, val);
if (strcmp(esp_rmaker_device_get_name(device),"Switch1")==0){
    if (val.val.b==true){
            app_driver_set_state(false);
            //gpio_set_level(21, 0);
        //esp_rmaker_param_update_and_report(param, esp_rmaker_bool(true));
        } else if (val.val.b==false){
            app_driver_set_state(true);
            //gpio_set_level(21, 1);
        //esp_rmaker_param_update_and_report(param, esp_rmaker_bool(false));
        }
                        esp_rmaker_param_update_and_report(param, val);

}
if (strcmp(esp_rmaker_device_get_name(device),"Switch2")==0){
    if (val.val.b==true){
            app_driver_set_state2(false);
            //gpio_set_level(19, 0);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch2_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(true));
        } else if (val.val.b==false){
            app_driver_set_state2(true);
            //gpio_set_level(19, 1);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch2_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(false));
        }
                        esp_rmaker_param_update_and_report(param, val);

}
if (strcmp(esp_rmaker_device_get_name(device),"Switch3")==0){
    if (val.val.b==true){
            //app_driver_set_state2(false);
            gpio_set_level(18, 0);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch3_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(true));
        } else if (val.val.b==false){
            //app_driver_set_state2(true);
            gpio_set_level(18, 1);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch3_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(false));
        }
                        esp_rmaker_param_update_and_report(param, val);

}
if (strcmp(esp_rmaker_device_get_name(device),"Switch4")==0){
    if (val.val.b==true){
            //app_driver_set_state2(false);
            gpio_set_level(5, 0);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(true));
        } else if (val.val.b==false){
            //app_driver_set_state2(true);
            gpio_set_level(5, 1);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(false));
        }
                esp_rmaker_param_update_and_report(param, val);

}
if (strcmp(esp_rmaker_device_get_name(device),"Switch5")==0){
    if (val.val.b==true){
            //app_driver_set_state2(false);
            gpio_set_level(23, 0);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(true));
        } else if (val.val.b==false){
            //app_driver_set_state2(true);
            gpio_set_level(23, 1);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(false));
        }
                esp_rmaker_param_update_and_report(param, val);

}
if (strcmp(esp_rmaker_device_get_name(device),"Switch6")==0){
    if (val.val.b==true){
            //app_driver_set_state2(false);
            gpio_set_level(22, 0);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(true));
        } else if (val.val.b==false){
            //app_driver_set_state2(true);
            gpio_set_level(22, 1);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(false));
        }
                esp_rmaker_param_update_and_report(param, val);

}
if (strcmp(esp_rmaker_device_get_name(device),"Switch7")==0){
    if (val.val.b==true){
            //app_driver_set_state2(false);
            gpio_set_level(4, 0);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(true));
        } else if (val.val.b==false){
            //app_driver_set_state2(true);
            gpio_set_level(4, 1);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(false));
        }
                esp_rmaker_param_update_and_report(param, val);

}
if (strcmp(esp_rmaker_device_get_name(device),"Switch8")==0){
    if (val.val.b==true){
            //app_driver_set_state2(false);
            gpio_set_level(15, 0);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(true));
        } else if (val.val.b==false){
            //app_driver_set_state2(true);
            gpio_set_level(15, 1);
        //esp_rmaker_param_update_and_report(esp_rmaker_device_get_param_by_name(switch4_device, ESP_RMAKER_DEF_POWER_NAME), esp_rmaker_bool(false));
        }
                esp_rmaker_param_update_and_report(param, val);

}
    }
    return ESP_OK;
}
/* Event handler for catching RainMaker events */
static void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data)
{
    if (event_base == RMAKER_EVENT) {
        switch (event_id) {
            case RMAKER_EVENT_INIT_DONE:
                ESP_LOGI(TAG, "RainMaker Initialised.");
                break;
            case RMAKER_EVENT_CLAIM_STARTED:
                ESP_LOGI(TAG, "RainMaker Claim Started.");
                break;
            case RMAKER_EVENT_CLAIM_SUCCESSFUL:
                ESP_LOGI(TAG, "RainMaker Claim Successful.");
                break;
            case RMAKER_EVENT_CLAIM_FAILED:
                ESP_LOGI(TAG, "RainMaker Claim Failed.");
                break;
            default:
                ESP_LOGW(TAG, "Unhandled RainMaker Event: %d", event_id);
        }
    } else if (event_base == RMAKER_COMMON_EVENT) {
        switch (event_id) {
            case RMAKER_EVENT_REBOOT:
                ESP_LOGI(TAG, "Rebooting in %d seconds.", *((uint8_t *)event_data));
                break;
            case RMAKER_EVENT_WIFI_RESET:
                ESP_LOGI(TAG, "Wi-Fi credentials reset.");
                break;
            case RMAKER_EVENT_FACTORY_RESET:
                ESP_LOGI(TAG, "Node reset to factory defaults.");
                break;
            case RMAKER_MQTT_EVENT_CONNECTED:
                ESP_LOGI(TAG, "MQTT Connected.");
                break;
            case RMAKER_MQTT_EVENT_DISCONNECTED:
                ESP_LOGI(TAG, "MQTT Disconnected.");
                break;
            case RMAKER_MQTT_EVENT_PUBLISHED:
                ESP_LOGI(TAG, "MQTT Published. Msg id: %d.", *((int *)event_data));
                break;
            default:
                ESP_LOGW(TAG, "Unhandled RainMaker Common Event: %d", event_id);
        }
    } else {
        ESP_LOGW(TAG, "Invalid event received!");
    }
}

void app_main()
{
    /* Initialize Application specific hardware drivers and
     * set initial state.
     */
    esp_rmaker_console_init();
    app_driver_init();
    //app_driver_set_state(DEFAULT_POWER);

    /* Initialize NVS. */
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
    
    /* Initialize Wi-Fi. Note that, this should be called before esp_rmaker_init()
     */
    app_wifi_init();

    /* Register an event handler to catch RainMaker events */
    ESP_ERROR_CHECK(esp_event_handler_register(RMAKER_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));

    /* Initialize the ESP RainMaker Agent.
     * Note that this should be called after app_wifi_init() but before app_wifi_start()
     * */
    esp_rmaker_config_t rainmaker_cfg = {
        .enable_time_sync = false,
    };
    esp_rmaker_node_t *node = esp_rmaker_node_init(&rainmaker_cfg, "SmartSwitcher® Switch Hub", "Switch");
    if (!node) {
        ESP_LOGE(TAG, "Could not initialise node. Aborting!!!");
        vTaskDelay(5000/portTICK_PERIOD_MS);
        abort();
    }

    /* Create a Switch device.
     * You can optionally use the helper API esp_rmaker_switch_device_create() to
     * avoid writing code for adding the name and power parameters.
     */
    switch_device = esp_rmaker_device_create("Switch1", ESP_RMAKER_DEVICE_SWITCH, NULL);
    switch2_device = esp_rmaker_device_create("Switch2", ESP_RMAKER_DEVICE_SWITCH, NULL);
    switch3_device = esp_rmaker_device_create("Switch3", ESP_RMAKER_DEVICE_SWITCH, NULL);
    switch4_device = esp_rmaker_device_create("Switch4", ESP_RMAKER_DEVICE_SWITCH, NULL);
    switch5_device = esp_rmaker_device_create("Switch5", ESP_RMAKER_DEVICE_SWITCH, NULL);
    switch6_device = esp_rmaker_device_create("Switch6", ESP_RMAKER_DEVICE_SWITCH, NULL);
    switch7_device = esp_rmaker_device_create("Switch7", ESP_RMAKER_DEVICE_SWITCH, NULL);
    switch8_device = esp_rmaker_device_create("Switch8", ESP_RMAKER_DEVICE_SWITCH, NULL);

    /* Add the write callback for the device. We aren't registering any read callback yet as
     * it is for future use.
     */
    esp_rmaker_device_add_cb(switch_device, write_cb, NULL);
    esp_rmaker_device_add_cb(switch2_device, write_cb, NULL);
    esp_rmaker_device_add_cb(switch3_device, write_cb, NULL);
    esp_rmaker_device_add_cb(switch4_device, write_cb, NULL);
    esp_rmaker_device_add_cb(switch5_device, write_cb, NULL);
    esp_rmaker_device_add_cb(switch6_device, write_cb, NULL);
    esp_rmaker_device_add_cb(switch7_device, write_cb, NULL);
    esp_rmaker_device_add_cb(switch8_device, write_cb, NULL);

    /* Add the standard name parameter (type: esp.param.name), which allows setting a persistent,
     * user friendly custom name from the phone apps. All devices are recommended to have this
     * parameter.
     */
    esp_rmaker_device_add_param(switch_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Switch"));
    esp_rmaker_device_add_param(switch2_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Switch2"));
    esp_rmaker_device_add_param(switch3_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Switch3"));
    esp_rmaker_device_add_param(switch4_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Switch4"));
    esp_rmaker_device_add_param(switch5_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Switch5"));
    esp_rmaker_device_add_param(switch6_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Switch6"));
    esp_rmaker_device_add_param(switch7_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Switch7"));
    esp_rmaker_device_add_param(switch8_device, esp_rmaker_name_param_create(ESP_RMAKER_DEF_NAME_PARAM, "Switch8"));

    /* Add the standard power parameter (type: esp.param.power), which adds a boolean param
     * with a toggle switch ui-type.
     */
    esp_rmaker_param_t *power_param = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_param_t *power2_param = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_param_t *power3_param = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_param_t *power4_param = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_param_t *power5_param = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_param_t *power6_param = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_param_t *power7_param = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_param_t *power8_param = esp_rmaker_power_param_create(ESP_RMAKER_DEF_POWER_NAME, DEFAULT_POWER);
    esp_rmaker_device_add_param(switch_device, power_param);
    esp_rmaker_device_add_param(switch2_device, power2_param);
    esp_rmaker_device_add_param(switch3_device, power3_param);
    esp_rmaker_device_add_param(switch4_device, power4_param);
    esp_rmaker_device_add_param(switch5_device, power5_param);
    esp_rmaker_device_add_param(switch6_device, power6_param);
    esp_rmaker_device_add_param(switch7_device, power7_param);
    esp_rmaker_device_add_param(switch8_device, power8_param);

    /* Assign the power parameter as the primary, so that it can be controlled from the
     * home screen of the phone apps.
     */
    esp_rmaker_device_assign_primary_param(switch_device, power_param);
    esp_rmaker_device_assign_primary_param(switch2_device, power2_param);
    esp_rmaker_device_assign_primary_param(switch3_device, power3_param);
    esp_rmaker_device_assign_primary_param(switch4_device, power4_param);
    esp_rmaker_device_assign_primary_param(switch5_device, power5_param);
    esp_rmaker_device_assign_primary_param(switch6_device, power6_param);
    esp_rmaker_device_assign_primary_param(switch7_device, power7_param);
    esp_rmaker_device_assign_primary_param(switch8_device, power8_param);

    /* Add this switch device to the node */
    esp_rmaker_node_add_device(node, switch_device);
    esp_rmaker_node_add_device(node, switch2_device);
    esp_rmaker_node_add_device(node, switch3_device);
    esp_rmaker_node_add_device(node, switch4_device);
    esp_rmaker_node_add_device(node, switch5_device);
    esp_rmaker_node_add_device(node, switch6_device);
    esp_rmaker_node_add_device(node, switch7_device);
    esp_rmaker_node_add_device(node, switch8_device);

    /* Enable OTA */
    esp_rmaker_ota_config_t ota_config = {
        .server_cert = ESP_RMAKER_OTA_DEFAULT_SERVER_CERT,
    };
    esp_rmaker_ota_enable(&ota_config, OTA_USING_PARAMS);

    /* Enable timezone service which will be require for setting appropriate timezone
     * from the phone apps for scheduling to work correctly.
     * For more information on the various ways of setting timezone, please check
     * https://rainmaker.espressif.com/docs/time-service.html.
     */
    esp_rmaker_timezone_service_enable();

    /* Enable scheduling. */
    esp_rmaker_schedule_enable();

    /* Start the ESP RainMaker Agent */
    esp_rmaker_start();

    /* Start the Wi-Fi.
     * If the node is provisioned, it will start connection attempts,
     * else, it will start Wi-Fi provisioning. The function will return
     * after a connection has been successfully established
     */
    err = app_wifi_start(POP_TYPE_RANDOM);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Could not start Wifi. Aborting!!!");
        vTaskDelay(5000/portTICK_PERIOD_MS);
        abort();
    }
}