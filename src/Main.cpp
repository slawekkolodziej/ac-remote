#include <IRremoteESP8266.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <LGAC.h>

IRsend irsend(0);
LGAC lgac;

const char networkName[] = "...";
const char networkPass[] = "...";

MDNSResponder mdns;
ESP8266WebServer server(80);

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(networkName, networkPass);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("- ");
    Serial.print(WiFi.status());
    Serial.println();
  }

  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void setupServer() {
  static String siteData = "";

  server.on("/", [](){
    server.send(200, "text/html", "<html>Hello cruel world!</html>");
  });

  server.on("/set", HTTP_GET, [](){
    int argValue, temp, fan, mode, state;
    String argName;
    char response[100];

    for (uint8_t i=0; i<server.args(); i++){
      argName = server.argName(i);
      argValue = server.arg(i).toInt();

      if (argName == "temp") {
        temp = argValue;
      } else if (argName == "fan") {
        fan = argValue;
      } else if (argName == "mode") {
        mode = argValue;
      } else if (argName == "state") {
        state = argValue;
      }

      Serial.print("name: ");
      Serial.print(argName);
      Serial.println();
      Serial.print("value: ");
      Serial.print(argValue);
      Serial.println();

    }

    lgac.setMode(mode, fan, temp, state);
    irsend.sendRaw(lgac.codes,LGAC_buffer_size,38);

    sprintf(response, "temp: %d, fan: %d, mode: %d, state: %d", temp, fan, mode, state);
    server.send(200, response);
  });

  server.on("/off", [](){
    lgac.setMode(0, 1, 18, 24);
    irsend.sendRaw(lgac.codes,LGAC_buffer_size,38);
    server.send(200, "text/html", "<html>klima wyłączona!</html>");
  });
  server.begin();
}

void setup() {
  connectWiFi();
  irsend.begin();
  Serial.begin(9600);

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  setupServer();
}

void loop() {
  server.handleClient();
}
