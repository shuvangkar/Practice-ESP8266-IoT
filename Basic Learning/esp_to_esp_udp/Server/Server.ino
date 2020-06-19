/*
   This will create an Access Point as well as a Server. So the client will connect with
   this Access Point and send post requenst to the server.The client will send xml data and.
   Server will read post Request of xml format
   and send a JSON file
*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

char* ssid = "Shuvo Wifi";            // Wifi Name
char* password = "marakha_1106125";       // Wifi Password

IPAddress ServerIP(192,168,4,1);
IPAddress ClientIP(192,168,4,2);

unsigned int localPort = 2000; // local port to listen for UDP packets
// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
 
char packetBuffer[9];   //Where we get the UDP data
void setup()
{
  Serial.begin(115200);
  setAP(ssid, password);
  //Start UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
}

void loop()
{
  int cb = udp.parsePacket();
    if (!cb) 
    {
      //If serial data is recived send it to UDP
      if(Serial.available()>0)
        {
        udp.beginPacket(ClientIP, 2000);
        //Send UDP requests are to port 2000
        
        char a[1];
        a[0]=char(Serial.read()); //Serial Byte Read
        udp.write(a,1); //Send one byte to ESP8266 
        udp.endPacket();
        }
    }
    else {
      // We've received a UDP packet, send it to serial
      udp.read(packetBuffer, 1); // read the packet into the buffer, we are reading only one byte
      Serial.print(packetBuffer);
      delay(20);
    }
  
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


