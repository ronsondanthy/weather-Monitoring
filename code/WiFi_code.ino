#include <SimpleDHT.h>
#include <WiFi.h>

String apiKey = "";  //insert your write API's key here 
char *ssid =  "";     //insert your SSID here
char *pass =  "";    //insert your PASSWORD here
char* server = "api.thingspeak.com";
#define pinDHT11 2
SimpleDHT11  dht11(pinDHT11);
WiFiClient client;

void setup()
{
       Serial.begin(115200);
       delay(1000);
       Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED)
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}

void loop()
{
byte temperature = 0;
byte humidity = 0;
dht11.read(pinDHT11, &temperature, &humidity,NULL);
      
if (client.connect(server,80))
 {  
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String((int)temperature);
    postStr +="&field2=";
    postStr += String((int)humidity);
    postStr += "\r\n\r\n";
 
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
 
    Serial.print("Temperature: ");
    Serial.print((int)temperature);
    Serial.print(" degrees Celcius, Humidity: ");
    Serial.print((int)humidity);
    Serial.println("%. Send to Thingspeak.");
 }
client.stop();
Serial.println("Waiting...");
delay(20000);
}