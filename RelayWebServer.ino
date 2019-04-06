#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const int Relay = 5;
const char* ssid = "SSID";
const char* password = "WIFI PASSWORD";
int status = 0;

ESP8266WebServer server(80);

void handleOn() {
  Serial.println("\n\nClient Connected");
  server.send(200, "text/plain", "{\"status\":\"on\"}");
  Serial.println("Message Sent");
  digitalWrite(LED_BUILTIN, LOW);  
  digitalWrite(Relay, HIGH);  
  Serial.println("Relay On");
  Serial.println("Client Disconnected");
}

void handleOff() {
  Serial.println("\n\nClient Connected");
  server.send(200, "text/plain", "{\"status\":\"off\"}");
  Serial.println("Message Sent");
  digitalWrite(LED_BUILTIN, HIGH);  
  digitalWrite(Relay, LOW);  
  Serial.println("Relay Off");
  Serial.println("Client Disconnected");
}

void handleStatus() {
  status = digitalRead(Relay);
  Serial.println("\n\nClient Connected");
  if (status == 0) 
    server.send(200, "text/plain", "{\"status\":\"off\"}");
  else
    server.send(200, "text/plain", "{\"status\":\"on\"}");
  Serial.println("Message Sent");
}

void handleNotFound(){
  digitalWrite(LED_BUILTIN,HIGH);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(LED_BUILTIN, LOW);
 
}

void setup(void){
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(Relay, OUTPUT);
  
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname("lightRelay");
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/status", handleStatus);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
