#include <ESP8266WiFi.h>
#include "INDEX.h"

const char* ssid = "Mangatayaru";
const char* password = "12345678";

WiFiServer server(80);

int DigitalPin[] = {4,5, 12, 13};
double Light (int RawADC0)
{
  double Vout=RawADC0*0.0048828125;
  int lux=500/(10*((5-Vout)/Vout));//use this equation if the LDR is in the upper part of the divider
  return lux;
}

void setup() {
  Serial.begin(115200);
  delay(10);


pinMode(4,OUTPUT);
pinMode(5, OUTPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String command1 = client.readStringUntil('/');
  String command = client.readStringUntil('/');
  Serial.println(command1);
  Serial.println(command);

if (command == "ON") {
digitalWrite(12,HIGH);
digitalWrite(13,HIGH);
client.print(F("ON")); 
}
else if (command == "OFF") {
digitalWrite(12,LOW);
digitalWrite(13,LOW);
client.print(F("OFF"));
}
else if(command=="SERIES_1"){
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  client.print(F("SERIES_1"));
}
else if(command=="SERIES_2"){
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  client.print(F("SERIES_2"));
}
else if(command=="STATUS"){
  client.print(F("STATUS#"));
  client.print(int(Light(analogRead(A0))));
  client.print(F("#"));
  client.print(analogRead(A0));
}
else if(command =="AUTO"){
  int lux, timer;
  timer= = client.parseInt();
  if (client.read() == '/') {
lux = client.parseInt();
}
client.print(F("AUTO"));

}
else {  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += file1;  
  client.flush();


  


  // Send the response to the client
while(s.length()>2000)
{
  String dummy = s.substring(0,2000);
  client.print(dummy);
  s.replace(dummy," ");
}
  
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is destroyed
}
}
