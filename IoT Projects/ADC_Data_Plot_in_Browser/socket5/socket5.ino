#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
#define N 50
char* ssid = "Out Of Range";            // Wifi Name
char* password ="marakha_1106125";        // Wifi Password 
//Server IP adress is 192.168.0.110
//Device IP will be from 192.168.0.111-192.168.0.122
IPAddress ip(192,168,0,111); //The Device 1 IP address
#define USE_SERIAL Serial
SocketIoClient socket;

 void event(const char * payload, size_t length)
    {
      USE_SERIAL.printf("message: %s\n", payload);
    }


void setup() {
    USE_SERIAL.begin(115200);
    WiFi.mode(WIFI_STA);            // To Avoid Broadcasting An SSID
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
    delay(1000);
    Serial.println("Connecting.."+ WiFi.SSID());
    }
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    socket.begin("192.168.0.110",80);
    //socket.on("event", event); //The callback function will be trigger when data avaiable
}

void loop() 
{
    Serial.printf("loop heap size: %u\n", ESP.getFreeHeap());
    long  millis1 = millis();   
    //char arr[10];
    int adc = 0;
    String str = "\"";
    for(int i = 0; i<=1000; i++)
    {
      adc = analogRead(A0);
      str += String(adc);
      str += ",";
    }
    str += "\"";
    Serial.printf("loop heap size: %u\n", ESP.getFreeHeap());
    //Serial.println(str);
    //str.toCharArray(arr,10);
    char *pointerString = new char[str.length() + 1];
    strcpy(pointerString, str.c_str());
    str = "";
    Serial.printf("loop heap size: %u\n", ESP.getFreeHeap());
    //Serial.println(pointerString);
    socket.emit("D",pointerString);
    Serial.printf("loop heap size: %u\n", ESP.getFreeHeap());
    long millis2 = millis();
    socket.loop();
    Serial.printf("loop heap size: %u\n", ESP.getFreeHeap());
    long millis3 = millis();
    Serial.println("Process Time: "+String(millis2-millis1)+" Send Time: " +String(millis3-millis2));
   Serial.flush();
 
   
}



