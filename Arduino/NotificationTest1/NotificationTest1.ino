#include<ESP8266WiFi.h>
#include<WiFiClient.h>

void setup(){

  Serial.begin(115200);

  Serial.println("\nConnecting to WiFi...");

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin("lookamee", "supersimple0");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
    }

  if(WiFi.status() == WL_CONNECTED){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("Local IP is ");
    Serial.println(WiFi.localIP());
    }

  Serial.println("Connecting to host...");
  
  WiFiClient client;

  if(client.connect("maker.ifttt.com", 80)){
    Serial.println("Connected successfully");

    String url = "/trigger/alarm/with/key/cLoJtbpaT5nLHgmILYZ_ua";

    Serial.println("Requesting webhook url...");

    client.print(String("POST")+url+"HTTP/1.1\r\nHost: maker.ifttt.com\r\nUser-Agent: bhagatnagi\r\nConnection: close\r\n\r\n");

    Serial.println("Request sent\nClosing Client...");

    //client.close();
    }else{
    Serial.println("Failed to connect");
    }
  }

void loop(){
  }
