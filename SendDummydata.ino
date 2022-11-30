#include <ThingsBoard.h>
#include <PubSubClient.h>
#include <WiFi.h>
WiFiClient espclient;

#define ssid "Your Hotspot SSID"
#define password "Hotspot Password"

#define TOKEN "Acces Token"
#define THINGSBOARD_SERVER "thingsboard.cloud"

ThingsBoard tb(espclient);
int dummyData;
int status = WL_IDLE_STATUS;

void initWifi(){
Serial.println("Connecting to AP...");
WiFi.begin(ssid, password);
while(WiFi.status() !=WL_CONNECTED){
delay(500);
Serial.println(".");
}
Serial.println("Connecting to AP");
}

void reconnect(){
status = WiFi.status();
if(status != WL_CONNECTED){
WiFi.begin(ssid, password);
while(WiFi.status() !=WL_CONNECTED){
delay(500);
Serial.println(".");
}
Serial.println("Try connecting again");
}
}

void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
Serial.println();
initWifi();

}

void loop() {
if (!tb.connected()){
Serial.print("Connecting to");
Serial.print(THINGSBOARD_SERVER);
Serial.print("Your Token : ");
Serial.print(TOKEN);
if (!tb.connect(THINGSBOARD_SERVER, TOKEN)){
Serial.println("Failed Connecting");
return;
}
}
Serial.println("Sending data....");
dummyData = millis();
tb.sendTelemetryInt("Data Dummy", dummyData);
}
