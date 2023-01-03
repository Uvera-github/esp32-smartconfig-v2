
#include <WiFi.h>

void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch (event) {

        case ARDUINO_EVENT_SC_SCAN_DONE:
        {
            Serial.println("Scan done");
        }
        break;

        case ARDUINO_EVENT_SC_FOUND_CHANNEL:
        {
            Serial.println("Found channel");

        }
        break;

        case ARDUINO_EVENT_SC_GOT_SSID_PSWD:
        {
            Serial.println("Got SSID and password");

            uint8_t ssid[33] = { 0 };
            uint8_t password[65] = { 0 };

            uint8_t rvd_data[33] = { 0 };

            memcpy(ssid, info.sc_got_ssid_pswd.ssid, sizeof(info.sc_got_ssid_pswd.ssid));
            memcpy(password, info.sc_got_ssid_pswd.password, sizeof(info.sc_got_ssid_pswd.password));

            Serial.printf("SSID:%s\n", ssid);
            Serial.printf("PASSWORD:%s\n", password);

            if (info.sc_got_ssid_pswd.type == SC_TYPE_ESPTOUCH_V2) {
                ESP_ERROR_CHECK( esp_smartconfig_get_rvd_data(rvd_data, sizeof(rvd_data)) );

                Serial.println("RVD_DATA");
                Serial.printf("USER ID:");
                Serial.write(rvd_data, 33);
                Serial.printf("\n");

                for (int i = 0; i < 33; i++) {
                    Serial.printf("%02x ", rvd_data[i]);
                }
                Serial.printf("\n");
            }
        }
        break;

        case ARDUINO_EVENT_SC_SEND_ACK_DONE:
        {
            Serial.println("SC_EVENT_SEND_ACK_DONE");
        }
        break;
        
        default:
        {
            Serial.printf("no case event: %d\n", event);
        }
        break;
    }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32 START");
  WiFi.mode(WIFI_AP_STA);
  WiFi.onEvent(WiFiEvent);
  WiFi.beginSmartConfig(SC_TYPE_ESPTOUCH_V2, "1234567890123456");
  Serial.println("SmartConfig...");
}

void loop()
{
  // put your main code here, to run repeatedly:
}
