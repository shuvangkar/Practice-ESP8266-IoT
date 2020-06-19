#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

char* ssid = "Shuvo Wifi";            // Wifi Name
char* password ="marakha_1106125";        // Wifi Password

unsigned int localPort = 2000; // local port to listen for UDP packets
 
IPAddress ServerIP(192,168,4,1);
IPAddress ClientIP(192,168,4,2);
 
// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
 
char packetBuffer[9];   //Where we get the UDP data

void setup() 
{
 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting.."+ WiFi.SSID());
  }
    Serial.println("Connected to WiFi Network");
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
        udp.beginPacket(ServerIP, 2000);  //Send Data to Master unit
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

//String RTC()
//{
//  timeNow = millis()/1000;
//  seconds = timeNow-timeLast;
//  if(seconds>=60)
//  {
//    timeLast = timeNow;
//    minutes = minutes+1;
//  }
//  if(minutes>=60)
//  {
//    minutes = 0 ;
//    hours = hours+1;
//  }
//  String Time = String(hours)+ ":" +String(minutes)+ ":" + String(seconds);
//  return Time;
//}

