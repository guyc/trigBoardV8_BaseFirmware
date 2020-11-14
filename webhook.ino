// Useful state globals
//   config.trigName
//   buttonWasPressed
//   contactLatchClosed
//   contactLatchOpen
//   timerWake
//   lowBattery
//   batCharString

#define BUFFER_SIZE 512
char buffer[BUFFER_SIZE];
const char * webhookServer = "event.excelpsychology.com.au";

boolean webhook() {
    {
        Serial.println("Sending webhook");

        WiFiClientSecure client;
        if (!client.connect(webhookServer, 443)) {
            Serial.println("couldn't connect..");
            return false;
        }

        Serial.println("Connected");

        char * message = "Unknown";
        if (timerWake && lowBattery) {
            message = "LowBattery";
        } else if (buttonWasPressed) {
            message = "ButtonPress";
        } else if (contactLatchOpen) {
            message = "Opened";
        } else if (contactLatchClosed) {
            message = "Closed";
        }
        
        int len = snprintf(buffer, BUFFER_SIZE,
            "POST /event/trigger?proto=2&id=%s&battery=%s&message=%s&lowBattery=%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
            config.trigName,
            batCharString,
            message,
            lowBattery ? "t": "f",
            webhookServer
        );
        Serial.println(len);
        Serial.println(buffer);
        client.print(buffer);

        unsigned long startTimePush = millis();
        while (millis() - startTimePush < 5000) {
            if (client.available()) {
                Serial.println("From Server");
                break;
            }
        }
        while (client.available() != 0) {
            Serial.print(char(client.read()));
        }
        client.stop();

        return true;
    }
}