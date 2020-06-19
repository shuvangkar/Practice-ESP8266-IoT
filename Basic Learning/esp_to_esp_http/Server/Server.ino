/*
   This will create an Access Point as well as a Server. So the client will connect with
   this Access Point and send post requenst to the server.The client will send xml data and.
   Server will read post Request of xml format
   and send a JSON file
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

char* ssid = "Shuvo Wifi";            // Wifi Name
char* password = "marakha_1106125";       // Wifi Password


ESP8266WebServer server(80);

void setup()
{
  Serial.begin(115200);
  setAP(ssid, password);
  server.begin();
  Serial.println("Server Started");
  handleRequests();
}

void loop()
{
  server.handleClient();
}

void setAP(char* ssid, char* password)
{
  WiFi.disconnect(); // Stop Any Previous WIFI
  WiFi.mode(WIFI_AP_STA);
  Serial.println(F("WIFI Mode : AccessPoint Station"));
  WiFi.softAP(ssid, password);
  Serial.println("WIFI < " + String(ssid) + " > ... Started");
  delay(1000);
  // Getting Server IP
  IPAddress IP = WiFi.softAPIP();
  // Printing The Server IP Address
  Serial.print("AccessPoint/Server IP : ");
  Serial.println(IP);

  // Printing MAC Address
  Serial.print("AccessPoint MC : ");
  Serial.println(String(WiFi.softAPmacAddress()));
}

void handleRequests() {
  Serial.println("- Handling Request-:");
  server.on("/", handle_index);
  server.on("/feed", handle_feed);
  server.begin();
};

// Handling the / root web page from my server
void handle_index()
{
  server.send(200, "text/plain", "Get the f**k out from my server!");
}

// Handling the /feed page from my server
void handle_feed()
{
  String t = server.arg("temp");
  String h = server.arg("hum");
  Serial.println(t);
  String body = "\"hum\":20";
  //server.send(200, "text/plain", "Hello from server Side");
  server.send(200, "application/json", body);
  //setupStMode(t, h);
}

