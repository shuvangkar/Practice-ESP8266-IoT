#include <ESP8266WiFi.h>
const int ledPin = 2;

void setup()
{
  const char* ssid = "Out Of Range";
  const char* password = "marakha_1106125";
  int status;
  Serial.begin(115200);
  Serial.print("Trying to connect ");
  Serial.println(ssid);
  status = WiFi.waitForConnectResult();
  if(status !=WL_CONNECTED)
  {
    Serial.println("Connection Failed");
    while(true){}
  }
  Serial.println("Connected ");
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
Serial.println(WiFi.gatewayIP());
Serial.print("DNS: ");
Serial.println(WiFi.dnsIP());
Serial.print("Channel: ");
Serial.println(WiFi.channel());
Serial.print("Status: ");
Serial.println(WiFi.status());
  pinMode(ledPin,OUTPUT);
}

void loop()
{

int k;

for (k = 0; k <= 100; k = k + 1) {

    Serial.println("on");
    digitalWrite(ledPin, HIGH);
    delay(500);

    Serial.println("off");
    digitalWrite(ledPin, LOW);
    delay(500);
    }

WiFi.disconnect(true);

while (true) {}

}

