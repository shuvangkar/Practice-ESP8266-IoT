  #include <Wire.h>           // To Be Able To Use Sensors Like IMU9050
  #include <EEPROM.h>         // To Be Able To Store & Read Data Between Power Off
  #include <ESP8266WiFi.h>    // The Basic Function Of The ESP NOD MCU
  #define  LED0 2         // WIFI Module LED

  char* ssid = "Out Of Range";            // Wifi Name
  char* password ="marakha_1106125";        // Wifi Password
  
// This WIFI Module Code Works As A TCP Client
  int             serverPort  = 8000;
  IPAddress       serverIP(192,168,0,110);
  //192,168,0,110
  WiFiClient      client;
 void setup() 
  {
    Serial.begin(115200);    
    WiFi.mode(WIFI_STA);            // To Avoid Broadcasting An SSID
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
    delay(1000);
    Serial.println("Connecting.."+ WiFi.SSID());
    }
    // Printing IP Address --------------------------------------------------
    Serial.println("Connected To      : " + String(WiFi.SSID()));
    Serial.println("Signal Strenght   : " + String(WiFi.RSSI()) + " dBm");
    Serial.print  ("Server IP Address : ");
    Serial.println(serverIP);
    Serial.print  ("Server Port Num   : ");
    Serial.println(serverPort);
    // Printing MAC Address
    Serial.print  ("Device MC Address : ");
    Serial.println(String(WiFi.macAddress()));
    // Printing IP Address
    Serial.print  ("Device IP Address : ");
    Serial.println(WiFi.localIP());
  
  }
   
  void loop()
  {
    //IF the connection with server is establised
    if(client.connect(serverIP,serverPort))
    {
      long firstMillis = millis();
      client.write("Hello Server"); //Send data to the server
      long secondMillis = millis();
      Serial.println(secondMillis-firstMillis);
    // Read all the lines of the reply from server and print them to Serial
      while(client.available())
      {
        String line = client.readStringUntil('\r');
        Serial.print(line);
      }
     
    }
  }


//====================================================================================

  void CheckWiFiConnectivity()
  {
    while(WiFi.status() != WL_CONNECTED)
    {
      for(int i=0; i < 10; i++)
      {
        digitalWrite(LED0, !HIGH);
        delay(250);
        digitalWrite(LED0, !LOW);
        delay(250);
        Serial.print(".");
      }
      Serial.println("");
    }
  }

