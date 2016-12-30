/*
 * Copyright (c) 2017, Dat Thanh Vu
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Dat Thanh Vu - CTO HACHI JSC */
/*******************************************************************************
 * Includes 
 ******************************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
/*******************************************************************************
 * Variables
 ******************************************************************************/
const char WiFiAPPSK[] = "datthanhvu";
const char* mqtt_server = "iot.eclipse.org";
char msg[50];
char* topic = "device/control";
char message_buff[100];
bool state = false;
int value = 0;
long lastMsg = 0;
/*******************************************************************************
 * Definitions
 ******************************************************************************/
ESP8266WebServer webserver(80);
WiFiClient espClient;
PubSubClient client(espClient);
void init_wifi_ap_mode();
void handleWifiConfig(void);
/*******************************************************************************
 * Code
 ******************************************************************************/
void setup_webserver(void) {
  // webserver.on ( "/", handleRoot );
  webserver.on ( "/configwifi", handleWifiConfig);
  // webserver.onNotFound ( handleNotFound );
  webserver.begin();
}
/*@!
 * This function get config from http request:
 * URL form: http://192.168.4.1/configwifi?ssid=1334e23&pass=1545678
 */
void handleWifiConfig(void) {
    if (webserver.args() > 0) {
        String message = "Config results\n\n";
        message += "URI: ";
        message += webserver.uri();
        message += "\nMethod: ";
        message += ( webserver.method() == HTTP_GET ) ? "GET" : "POST";
        message += "\nArguments: ";
        message += webserver.args();
        message += "\n";
        for (uint8_t i = 0; i < webserver.args(); i++) {
            message += " " + webserver.argName (i) + ": " + webserver.arg (i) + "\n";
            Serial.print(message);
        }
        char ssid[32];
        webserver.arg (0).toCharArray(ssid, 32);
        char pass[32];
        webserver.arg (1).toCharArray(pass, 32);
        if (webserver.args() != 2) {
            webserver.send ( 200, "text/html", "FAILED");
            state = false;
        }
        else {
            webserver.send (200, "text/html", "OK");
            WiFi.begin(ssid, pass);
            Serial.println(ssid);
            Serial.println(pass);
            state = true;

        }
        delay(1000);
        ESP.reset();
    }
}
void setup() {
	Serial.begin(9600); // Initialize Serial 9600 
  pinMode(LED_BUILTIN, OUTPUT);
  setup_webserver(); // Init web server 
	Serial.print("Configuring access point..."); 
  init_wifi_ap_mode(); // Create AP Mode
  /* If wifi not connect -> config again */
  if(WiFi.status() != WL_CONNECTED) {
   Serial.print("."); 
   state = false;
     init_wifi_ap_mode();
   delay(1000);
  } 
  /* When connect successfully ! */
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  /* Set server MQTT , example : iot.eclipse.org or localhost */
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  }
  
    }
void reconnectwifi() {
   if(WiFi.status() != WL_CONNECTED) {
   Serial.print("."); 
   state = false;
     init_wifi_ap_mode();
   delay(1000);
  } 
void callback(char* topic, byte* payload, unsigned int length) {
   int i = 0;

  Serial.println("Message arrived:  topic: " + String(topic));
  Serial.println("Length: " + String(length,DEC));

  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
   message_buff[i] = '\0';

  String msgString = String(message_buff);

  Serial.println("Payload: " + msgString);
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      state = true;
      // Once connected, publish an announcement...
      client.publish(topic, "hello world");
      // ... and resubscribe
      client.subscribe(topic);
    } else {
      state = false;
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  
	webserver.handleClient(); // Listen event webserver
 if(!WiFi.status() != WL_CONNECTED  ){
  Serial.print("Lost connection");
  reconnectwifi();
  }
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if(state) {
    Serial.print("State current: ONLINE");
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    }
    else if (state != true ){
      Serial.print("State current: OFFLINE");
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off by making the voltage HIGH
     }
}
void init_wifi_ap_mode()
{
    // WiFi.mode(WIFI_AP);

    // Do a little work to get a unique-ish name. Append the
    // last two bytes of the MAC (HEX'd) to "Hachi ":
    uint8_t mac[WL_MAC_ADDR_LENGTH];
    WiFi.softAPmacAddress(mac);
    String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                   String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
    macID.toUpperCase();
    String AP_NameString = "datthanhvu " + macID;

    char AP_NameChar[AP_NameString.length() + 1];
    memset(AP_NameChar, 0, AP_NameString.length() + 1);

    for (int i = 0; i < AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

    WiFi.softAP(AP_NameChar, WiFiAPPSK);
}
