extern "C" {
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
}
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>             
#include <ESP8266WebServer.h>

#include "./DNSServer.h"  // Patched lib
#include "./Shared.h"
#include "index.h"

using std::vector;

#define NAME "Commutr"

const char * ssid = "eduroam";
const char * username = "tullom@mcmaster.ca";
const char * password = "";

HTTPClient http;

const byte DNS_PORT = 53;  // Capture DNS requests on port 53
const byte ACTIVITY_LED = 2;
const byte ACTIVITY_REVERSE = 1; // turn off when active, not on.. needed for me
IPAddress APIP(10, 10, 10, 1);    // Private network for server
// state:
String allMsgs="<i>*system restarted*</i>";
vector<String> messages = {"*system restart*"};
vector<String> usernames = {"John Doe"};

 // standard api servers
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String index() {
  Serial.print("entered here");
  return home_page;
}

void connectToWifi() {
  wifi_station_disconnect();
  struct station_config wifi_config;
  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);
  strcpy((char*)wifi_config.password, password);
  wifi_station_set_config(&wifi_config);
  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();
  wifi_station_set_wpa2_enterprise_auth(1);
  wifi_station_set_enterprise_identity((uint8*)username, strlen(username));
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen(password));
  wifi_station_connect();
}

void setup() {
  Serial.begin(115200);
  pinMode(ACTIVITY_LED, OUTPUT);
  digitalWrite(ACTIVITY_LED, LOW);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(NAME);

  dnsServer.start(DNS_PORT, "commutr.com", APIP);

  webServer.on("/", []() {
    webServer.send(200, "text/html", index());
  });
  
  webServer.on("/messages", HTTP_POST, []() { 
    messages.push_back(getMessage(webServer.arg("plain")));
    webServer.send(200);
  });

  webServer.on("/messages", HTTP_GET, []() {
    webServer.send(200, "text/json", toJson(messages));
  });

  webServer.onNotFound([]() {
    webServer.send(404);
  });

  webServer.begin();
}


void loop() { 
  dnsServer.processNextRequest();
  webServer.handleClient();
  if(digitalRead(5) == HIGH) {
    Serial.print("goog");
    connectToWifi();
    while(WiFi.status() != WL_CONNECTED) {
      delay(2000);
      Serial.print(WiFi.localIP());
    }
    digitalWrite(0, HIGH);
    //http.begin(http, "lkj");
    digitalWrite(0, LOW);
  }
}
