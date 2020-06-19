#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

char* ssid = "Shuvo Wifi";            // Wifi Name
char* password ="marakha_1106125";        // Wifi Password
//const char* host = "192.168.4.1";
String host = "http://192.168.4.1/feed";
// Static network configuration
IPAddress ip(192, 168, 4, 4);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);
WiFiClient client;

void setup() 
{
 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting.."+ WiFi.SSID());
  }
    Serial.println("Connected to WiFi Network");
}
 
void loop()
{
  String JSON = "temp=";
  JSON += String(random(0,100));
  HTTPClient http;
  http.begin(host);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  //http.addHeader("Content-Type", "application/json");  //Specify content-type header
  int httpCode = http.POST(JSON);
  String payload = http.getString();
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  http.writeToStream(&Serial);
  http.end();
  //delay(2000);
  
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

