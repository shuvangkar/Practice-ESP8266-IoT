#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <SocketIoClient.h>

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
    long firstMillis = micros();
    char arr[10];
    arr[0] = '\"';
    int adc = analogRead(A0);
    char *p = (arr+1);
    itoa(adc,p,10);
    arr[4] = '\"';
    long secondMillis = micros();
    socket.emit("intro",arr);//"intro is the callback event name
    
    Serial.println("Time: "+String(secondMillis- firstMillis));
    Serial.println(arr);
    socket.loop();
    
   
}



