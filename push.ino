#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
 
const char* ssid = "xxx";
const char* password = "xxxxxxxxx";
const int DoorGpioPin = 5; // D1 of Node MCU
const int ledGpioPin =4;
int doorState=0;
int ledState=0;
#define closed 0
#define opened 1
 
const char* host = "esp8266.orgfree.com";
void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(DoorGpioPin, INPUT);
  pinMode(ledGpioPin, OUTPUT);
  
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  
} 
void loop() {
 // While pin 12 is HIGH (not activated)
 //   yield(); // Do (almost) nothing -- yield to allow ESP8266 background functions
//if( digitalRead(DoorGpioPin)==HIGH && doorState==opened){ // Print button pressed message.
   SendDoorCloseNotification();
      SendDoorOpenNotification();
   
 //  Serial.println("Close");
//   doorState=closed;
 //  ledState=1;//on
 //  digitalWrite(ledGpioPin, ledState);
//}
 yield();
//if( digitalRead(DoorGpioPin)==LOW && doorState==closed){ 
//   SendDoorOpenNotification();
//   Serial.println("Open");
 //  doorState=opened;
//   ledState=0; //off
//   digitalWrite(ledGpioPin, ledState);
//}
 yield(); // this is most important part of the code, as it tells the esp8266 keep running background wifi work, 
         //without this, your code  will disconnect from wifi, after long run of code. 
}

void SendDoorOpenNotification()
{
 WiFiClient client1;
   const int httpPort = 80;
   if (!client1.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/push/";
  url += "SendDoorOpenNotification.php";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
   client1.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
   delay(5000);       
   while(client1.available()){
  
    String line = client1.readStringUntil('\r');    
    Serial.print(line); 
}}

/*
 Note: This is not the right way, I expect you to pass open/close as parameter to a single function to save
       programme memory
*/

void SendDoorCloseNotification()
{
 WiFiClient client1;
   const int httpPort = 80;
   if (!client1.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/push/";
  url += "SendDoorCloseNotification.php";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
   client1.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
   delay(10000);       
   while(client1.available()){
  
    String line = client1.readStringUntil('\r');    
    Serial.print(line); 
}}
