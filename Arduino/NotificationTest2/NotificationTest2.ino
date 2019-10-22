#include <ESP8266WiFi.h>

#define ledPin 5 
#define wakePin 16
#define ssid "lookamee"
#define password "supersimple0"
 
// Replace with your unique IFTTT URL resource
const char* resource = "/trigger/alarm/with/key/cLoJtbpaT5nLHgmILYZ_ua";

// How your resource variable should look like, but with your own API KEY (that API KEY below is just an example):
//const char* resource = "/trigger/button_pressed/with/key/nAZjOphL3d-ZO4N3k64-1A7gTlNSrxMJdmqy";

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

void setup() {
  Serial.begin(115200);
  while(!Serial) { 
  }
  Serial.println(" ");// print an empty line before and after Button Press    
  Serial.println("Button Pressed");
  
  connectToWifi();

  //just connected to Wi-Fi so send notification to ifttt

 makeIFTTTRequest();

  //flash led once
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);   
  delay(200);              
  digitalWrite(ledPin, LOW); 

  //now sending board to sleep
  
  Serial.println("deepsleepnow ");// print an empty line  
  ESP.deepSleep(100000); 
}
void connectToWifi() {
  Serial.print("Connecting to: SSID NAME"); //uncomment next line to show SSID name
  //Serial.print(ssid); 
  WiFi.begin(ssid, password);  
  Serial.println(" ");// print an empty line
  Serial.print("Attempting to connect: ");

  //try to connect for 10 seconds
  int i = 10;
  while(WiFi.status() != WL_CONNECTED && i >=0) {
    delay(1000);
    Serial.print(i);
    Serial.print(", ");
    i--;
  }
  Serial.println(" ");// print an empty line

  //print connection result
  if(WiFi.status() == WL_CONNECTED){
    Serial.print("Connected."); 
    Serial.println(" ");// print an empty line
    Serial.print("NodeMCU ip address: "); 
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed - check your credentials or connection");
  }
}
// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
 Serial.print("Connecting to "); 
 Serial.print(server);
 
 WiFiClient client;
 int retries = 5;
 while(!!!client.connect(server, 80) && (retries-- > 0)) {
   Serial.print(".");
 }
 Serial.println();
 if(!!!client.connected()) {
    Serial.println("Failed to connect, going back to sleep");
 }
 
 Serial.print("Request resource: "); 
 Serial.println(resource);
 client.print(String("GET ") + resource + 
                 " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" + 
                 "Connection: close\r\n\r\n");
                 
 int timeout = 5 * 10; // 5 seconds             
 while(!!!client.available() && (timeout-- > 0)){
   delay(100);
 }
 if(!!!client.available()) {
    Serial.println("No response, going back to sleep");
 }
 while(client.available()){
   Serial.write(client.read());
 }
 
 Serial.println("\nclosing connection");
 client.stop();
}

void loop(){
  //if deep sleep is working, this code will never run.
  Serial.println("This shouldn't get printed");
}
