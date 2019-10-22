#include<ESP8266HTTPClient.h>
#include<ESP8266WiFi.h>

const String ssid = "lookamee";
const String password = "supersimple0";

void setup(){
  Serial.begin(115200);

  connectWiFi();
}

void loop(){
  if(WiFi.status()!=WL_CONNECTED){
    connectWiFi();
    }
  getHttp("notify", millis());
  delay(60000);
}

void connectWiFi(){
  WiFi.mode(WIFI_STA);
  Serial.println("Attempting to connect it WiFI...");
  WiFi.begin(ssid, password);

  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }

  if(WiFi.status()!=WL_CONNECTED){
    Serial.println("WiFi not connected");
  }
  else{
    Serial.println("WiFi connected");
  }
}

void getHttp(String event, int param1){
  HTTPClient http;

  Serial.println("HTTP beginning...");
  http.begin("http://maker.ifttt.com/trigger/"+event+"/with/key/cLoJtbpaT5nLHgmILYZ_ua/?value1="+String(param1));

  Serial.println("HTTP getting...");
  int httpCode = http.GET();

  if(httpCode>0){
    Serial.print("HTTP get code: ");
    Serial.println(httpCode);

    if(httpCode==HTTP_CODE_OK){
      Serial.println("CODE OK");
    }
  }
  else{
    Serial.println("HTTP get failed");  
  }
  Serial.println("Ending http...");
  http.end();
}
