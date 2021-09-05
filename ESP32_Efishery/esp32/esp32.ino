#define RXD2 16
#define TXD2 17

String data;

String Data1;

const int LEDPIN = 2;

#include <WiFi.h>

// Replace with your SSID and Password
const char* ssid = "MERAH17";
const char* password = "sheila10";

// Replace with your unique IFTTT URL resource
const char* resource = "/trigger/button_pressed/json/with/key/n--gUfc2IwbvGdgzH-Tr0wZKB8mBOt22Kz_ffpYTNk4";

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// push Button PIN
const int pushButton_PIN = 15; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);

  pinMode(pushButton_PIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  
  initWifi();
  
  makeIFTTTRequest();
}

void loop() {
  int Push_button_state = digitalRead(pushButton_PIN);
  
  
  //Serial to receive the data
  while(Serial2.available() > 0){
    delay(10);
    char d = Serial2.read();
    data += d;
  }
  
  if (data.length() > 0){
    Serial.println(data);
    Data1 = data;
    data = "";
  }

  if ( Push_button_state == HIGH ){
    delay(1000);
    initWifi();
    makeIFTTTRequest();
    delay(1000);
  }
}


// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);
int timeout = 20; // 20 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  
if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
       digitalWrite(LEDPIN , HIGH);
  }
  
Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}


// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  int retries = 20;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
      digitalWrite(LEDPIN , HIGH);
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);
    // JSON data that we got from other Serial and etc
    //send last 3 data that we got from other Serial
  String jsonObject = String("{\"value1\":\"") + "\",\"value2\":\"" + "" +  "\",\"value3\":\""  + ""+ "\"}";

  
  // Comment the previous line and uncomment the next line to publish temperature readings in Fahrenheit                    
  /*String jsonObject = String("{\"value1\":\"") + (1.8 * bme.readTemperature() + 32) + "\",\"value2\":\"" 
                      + (bme.readPressure()/100.0F) + "\",\"value3\":\"" + bme.readHumidity() + "\"}";*/
                      
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
      digitalWrite(LEDPIN,HIGH);
  }
  while(client.available()){
    Serial.write(client.read());
  digitalWrite(LEDPIN,LOW);
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}
