#include <DNSServer.h>
#include <ESPUI.h>
#include <SPI.h>
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

const char *ssid = "1452";
const char *password = "";

long oldTime = 0;
bool switchi = false;

void numberCall(Control sender, int type) { Serial.println(sender.value); }

void textCall(Control sender, int type) { Serial.println(sender.value); }

void slider(Control sender, int type) { Serial.println(sender.value); }

void buttonCallback(Control sender, int type) {
  switch (type) {
    case B_DOWN:
      {
        Serial.println("Button DOWN");
        digitalWrite(D0, LOW);
        SPI.transfer(0b00000000); //== write //0x00000001 == read
        SPI.transfer16(0x73FF);
        byte cmd[4]={0x01,0x00,0x00,0x00};
        SPI.transfer(cmd, 4);
        digitalWrite(D0, HIGH);
      }
      break;
    case B_UP:
      {
        Serial.println("Button UP");
        Serial.println("Button DOWN");
        digitalWrite(D0, LOW);
        SPI.transfer(0b00000000); //== write //0x00000001 == read
        SPI.transfer16(0x73FF);
        byte cmd[4]={0x00,0x00,0x06,0x8e};
        SPI.transfer(cmd, 4);
        digitalWrite(D0, HIGH);
      }
      break;
  }
}

void buttonExample(Control sender, int type) {
  switch (type) {
    case B_DOWN:
      Serial.println("Status: Start");
      ESPUI.print(0, "Status: Start");
      break;
    case B_UP:
      Serial.println("Status: Stop");
      ESPUI.print(0, "Status: Stop");
      break;
  }
}
void padExample(Control sender, int value) {
  switch (value) {
    case P_LEFT_DOWN:
      Serial.print("left down");
      break;
    case P_LEFT_UP:
      Serial.print("left up");
      break;
    case P_RIGHT_DOWN:
      Serial.print("right down");
      break;
    case P_RIGHT_UP:
      Serial.print("right up");
      break;
    case P_FOR_DOWN:
      Serial.print("for down");
      break;
    case P_FOR_UP:
      Serial.print("for up");
      break;
    case P_BACK_DOWN:
      Serial.print("back down");
      break;
    case P_BACK_UP:
      Serial.print("back up");
      break;
    case P_CENTER_DOWN:
      Serial.print("center down");
      break;
    case P_CENTER_UP:
      Serial.print("center up");
      break;
  }
  Serial.print(" ");
  Serial.println(sender.id);
}

void switchExample(Control sender, int value) {
  switch (value) {
    case S_ACTIVE:
      Serial.print("Active:");
      break;
    case S_INACTIVE:
      Serial.print("Inactive");
      break;
  }
  Serial.print(" ");
  Serial.println(sender.id);
}

void otherSwitchExample(Control sender, int value) {
  switch (value) {
    case S_ACTIVE:
      Serial.print("Active:");
      break;
    case S_INACTIVE:
      Serial.print("Inactive");
      break;
  }
  Serial.print(" ");
  Serial.println(sender.id);
}

void setup(void) {
  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH); 
  digitalWrite(D0, LOW);    
  delayMicroseconds(1);    
  digitalWrite(D0, HIGH);    
  digitalWrite(D0, LOW);    
  delayMicroseconds(1);    
  digitalWrite(D0, HIGH);    
  digitalWrite(D0, LOW);    
  delayMicroseconds(1);    
  digitalWrite(D0, HIGH);
  digitalWrite(D0, LOW);
  delayMicroseconds(1);    
  digitalWrite(D0, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));
  

  
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  /*
  #if defined(ESP32)
    WiFi.setHostname(ssid);
  #else
    WiFi.hostname(ssid);
  #endif
  */
/*
  WiFi.softAP(ssid);
  // WiFi.softAP(ssid, password);
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
*/
  // change the beginning to this if you want to join an existing network
  
     Serial.begin(115200);
     WiFi.begin(ssid, password);
     Serial.println("");
     // Wait for connection
     while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
     }
     Serial.println("");
     Serial.print("IP address: ");
     Serial.println(WiFi.localIP());
   

  ESPUI.label("Status:", COLOR_TURQUOISE, "Stop");
  ESPUI.label("Millis:", COLOR_EMERALD, "0");
  ESPUI.button("Push Button", &buttonCallback, COLOR_PETERRIVER);
  ESPUI.button("Other Button", &buttonExample, COLOR_WETASPHALT, "Press");
  ESPUI.pad("Pad with center", true, &padExample, COLOR_SUNFLOWER);
  ESPUI.pad("Pad without center", false, &padExample, COLOR_CARROT);
  ESPUI.switcher("Switch one", false, &switchExample, COLOR_ALIZARIN);
  ESPUI.switcher("Switch two", true, &otherSwitchExample, COLOR_NONE);
  ESPUI.slider("Slider one", &slider, COLOR_ALIZARIN, "30");
  ESPUI.slider("Slider two", &slider, COLOR_NONE, "100");
  ESPUI.text("Text Test:", &textCall, COLOR_ALIZARIN, "a Text Field");
  ESPUI.number("Numbertest", &numberCall, COLOR_ALIZARIN, 5, 0, 10);

  /*
     .begin loads and serves all files from PROGMEM directly.
     If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
     (.prepareFileSystem has to be run in an empty sketch before)
   */

  dnsServer.start(DNS_PORT, "*", apIP);

  /*
   * Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
   SECURE way of limiting access.
   * Anyone who is able to sniff traffic will be able to intercept your password
   since it is transmitted in cleartext ESPUI.begin("ESPUI Control", "myuser",
   "mypassword");
  */
  ESPUI.begin("ESPUI Control");
}

void loop(void) {
  dnsServer.processNextRequest();

  if (millis() - oldTime > 5000) {
    ESPUI.print("Millis:", String(millis()));
    switchi = !switchi;
    ESPUI.updateSwitcher("Switch one", switchi);
    oldTime = millis();
  }
}
