#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <SocketIoClient.h>

char* ssid = "Out Of Range";            // Wifi Name
char* password ="marakha_1106125";        // Wifi Password 
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
    socket.begin("192.168.0.110",8000);
    socket.on("event", event);
}

void loop() 
{
    int adc[1000];
    //char data[4100];
    long firstMillis = millis();
    for(int i = 0; i<1000;i++)
    {
      adc[i] = analogRead(A0);
    }
    long secondMillis = millis();
    
    Serial.println("Time Required: " + String(secondMillis-firstMillis));
  
   // socket.on("connect", handler);
    char buffer[10] = {};
    buffer[0] = '\"';
    Serial.println(buffer);
    itoa(adc[0],buffer,16);
 
    
    
    //socket.emit("intro",data);
    socket.emit("intro", "\"Hello from the other Side\"");//"intro is the callback event name
    socket.loop();
    
   
}



