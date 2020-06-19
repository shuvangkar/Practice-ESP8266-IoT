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
   socket.loop();
    long firstMillis = millis();
    char arr[10];
    String str = "\"";
    int adc = analogRead(A0);
    str += String(adc);
    str += "\"";
    str.toCharArray(arr,10);
    socket.emit("D",arr);
    long secondMillis = millis();
    Serial.println("Time: "+String(secondMillis- firstMillis));
    //Serial.println(arr);
    //Serial.println(str);
   
   
}



