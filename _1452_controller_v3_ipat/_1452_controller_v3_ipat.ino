
#define M5STACK
#define MOD_INDIRECTPARAMACCESSMODULE_START_ADDRESS_ADDR 24583
#define MOD_INDIRECTPARAMACCESSMODULE_NUM_OF_LOADS_AND_TRIGGER_ADDR 24584
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_1L_TARGET_ADDR 24585
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_1R_TARGET_ADDR 24586
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2L_TARGET_ADDR 24587
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2R_TARGET_ADDR 24588
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_1L_TARGET_ADDR 24589
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_1R_TARGET_ADDR 24590
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_1R_TARGET_ADDR 24591
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_2R_TARGET_ADDR 24592
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_1L_TARGET_ADDR 24593
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_1R_TARGET_ADDR 24594
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_2L_TARGET_ADDR 24595
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_2R_TARGET_ADDR 24596
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_1L_TARGET_ADDR 24597
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_2L_TARGET_ADDR 24598
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_1R_TARGET_ADDR 24599
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_2R_TARGET_ADDR 24600

#if defined(M5STACK)
#include <M5Stack.h>
#endif

#include <DNSServer.h>
#include <ESPUI.h>
#include <SPI.h>

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

const char *ssid = "";
const char *password = "";

long oldTime = 0;
bool switchi = false;

void numberCall(Control sender, int type) { Serial.println(sender.value); }

void textCall(Control sender, int type) { Serial.println(sender.value); }

#if defined(M5STACK)
int SS_PIN = G22;//D0;
#else
int SS_PIN = D0;
#endif

// 5.23 (decimal) format
// https://github.com/AidaDSP/AidaDSP/blob/master/Software/Libraries/Arduino/Aida2/AidaDSP2.cpp
#define FLOAT_TO_FIXED(a)        (a*((int32_t)1 << 24))
void float_to_fixed(float value, uint8_t *buffer)
{
  int32_t fixedval = 0;

  fixedval = FLOAT_TO_FIXED(value);
  buffer[0] = (fixedval>>24)&0xFF;
  buffer[1] = (fixedval>>16)&0xFF;
  buffer[2] = (fixedval>>8)&0xFF;
  buffer[3] = fixedval&0xFF;
}

uint8_t* int_to_bytes(int value)
{
  static uint8_t buffer[4];
  buffer[0] = (value>>24)&0xFF;
  buffer[1] = (value>>16)&0xFF;
  buffer[2] = (value>>8)&0xFF;
  buffer[3] = value&0xFF;
  return buffer;
}

void slider(Control *sender, int type) { 
  uint8_t buf[4];
  #if defined(M5STACK)
  //
  //M5.Lcd.print(sender->value.toInt()); 
  M5.Lcd.fillRect(0,0,320,20,0);
  M5.Lcd.progressBar(0,0,320,20, sender->value.toInt());
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.print("dry"); 

  #endif
  //Serial.println(sender->value.toInt());
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(0x0027);

  float_to_fixed(sender->value.toInt() / 100., buf);
  SPI.transfer(buf, 4);
  digitalWrite(SS_PIN, HIGH);
      
  SPI.endTransaction();
}
void sliderReverb(Control *sender, int type) { 
  uint8_t buf[4];
  //#if defined(M5STACK)
  //M5.Lcd.setCursor(50, 50, 2);
  //M5.Lcd.print(sender->value.toInt()); 
  //#endif
  //Serial.println(sender->value.toInt());
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(0x0021);

  float_to_fixed(sender->value.toInt() / 100., buf);
  SPI.transfer(buf, 4);
  digitalWrite(SS_PIN, HIGH);
      
  SPI.endTransaction();
}
void sliderDelay(Control *sender, int type) { 
  uint8_t buf[4];
  //#if defined(M5STACK)
  //M5.Lcd.setCursor(50, 50, 2);
  //M5.Lcd.print(sender->value.toInt()); 
  //#endif
  //Serial.println(sender->value.toInt());
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(0x0024);

  float_to_fixed(sender->value.toInt() / 100., buf);
  SPI.transfer(buf, 4);
  digitalWrite(SS_PIN, HIGH);
      
  SPI.endTransaction();
}

void sliderTruncate(Control *sender, int type) { 
  uint8_t buf[4];
  //#if defined(M5STACK)
  //M5.Lcd.setCursor(50, 50, 2);
  //M5.Lcd.print(sender->value.toInt()); 
  //#endif
  //Serial.println(sender->value.toInt());
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(0x00A0);

  float_to_fixed(sender->value.toInt() / 100., buf);
  SPI.transfer(buf, 4);
  digitalWrite(SS_PIN, HIGH);
      
  SPI.endTransaction();
}

void sliderPhat(Control *sender, int type) { 
uint8_t buf[4];
  //#if defined(M5STACK)
  //M5.Lcd.setCursor(50, 50, 2);
  //M5.Lcd.print(sender->value.toInt()); 
  //#endif
  //Serial.println(sender->value.toInt());
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(0x004C);

  float_to_fixed(sender->value.toInt() / 100., buf);
  SPI.transfer(buf, 4);
  digitalWrite(SS_PIN, HIGH);
      
  SPI.endTransaction();
}

void masterDry1L(Control *sender, int type) { 
  send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_1L_TARGET_ADDR, sender->value.toInt());
}
void masterDry1R(Control *sender, int type) { 
  send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_1R_TARGET_ADDR, sender->value.toInt());
}
void masterFxBuiltin1L(Control *sender, int type) { 
  send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_1L_TARGET_ADDR, sender->value.toInt());
}
void masterFxBuiltin1R(Control *sender, int type) { 
  send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_1R_TARGET_ADDR, sender->value.toInt());
}
void masterFxSend1L(Control *sender, int type) { 
  send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_1L_TARGET_ADDR, sender->value.toInt());
}
void masterFxSend1R(Control *sender, int type) { 
  send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_1R_TARGET_ADDR, sender->value.toInt());
}

void send(int param, int value) {
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));
  
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(param);
    uint8_t buf[4];
    float_to_fixed(value / 100., buf);
  SPI.transfer(buf, 4);
  digitalWrite(SS_PIN, HIGH);
  
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(MOD_INDIRECTPARAMACCESSMODULE_START_ADDRESS_ADDR);
  SPI.transfer(int_to_bytes(param),4);
  digitalWrite(SS_PIN, HIGH);
    
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(MOD_INDIRECTPARAMACCESSMODULE_NUM_OF_LOADS_AND_TRIGGER_ADDR);
  SPI.transfer(int_to_bytes(1),4);
  digitalWrite(SS_PIN, HIGH);
  
  SPI.endTransaction();
}

void buttonCallback(Control sender, int type) {
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));
  /*
  switch (type) {
    case B_DOWN:
      {
        Serial.println("Button DOWN");
        digitalWrite(SS_PIN, LOW);
        SPI.transfer(0b00000000); //== write //0x00000001 == read
        SPI.transfer16(0x73FF);
        //8.24 number format
        //multiply by 2^24
        stuff sendThis;
        sendThis.a = 1 * (2^24) ;
        byte cmd[4]={0x01,0x00,0x00,0x00};
        SPI.transfer(cmd, 4);
        digitalWrite(SS_PIN, HIGH);
      }
      break;
    case B_UP:
      {
        Serial.println("Button UP");
        digitalWrite(SS_PIN, LOW);
        SPI.transfer(0b00000000); //== write //0x00000001 == read
        SPI.transfer16(0x73FF);
        byte cmd[4]={0x00,0x00,0x06,0x8e};
        SPI.transfer(cmd, 4);
        digitalWrite(SS_PIN, HIGH);
      }
      break;
  }
  */
  SPI.endTransaction();
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
  #if defined(M5STACK)
  // Initialize the M5Stack object
  M5.begin();
  M5.Speaker.tone(360, 50); 
  delay(100);
  M5.Speaker.mute();

  // LCD display
  M5.Lcd.println("Testing ADAu1452");  
  M5.Speaker.tone(240, 50);
  delay(100);
  M5.Speaker.mute(); 
  #endif


  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH); 
  digitalWrite(SS_PIN, LOW);    
  delayMicroseconds(1);    
  digitalWrite(SS_PIN, HIGH);    
  digitalWrite(SS_PIN, LOW);    
  delayMicroseconds(1);    
  digitalWrite(SS_PIN, HIGH);    
  digitalWrite(SS_PIN, LOW);    
  delayMicroseconds(1);    
  digitalWrite(SS_PIN, HIGH);
  digitalWrite(SS_PIN, LOW);
  delayMicroseconds(1);    
  digitalWrite(SS_PIN, HIGH);
  SPI.begin();
    
    Serial.begin(115200);
    #if defined(ESP32)
      WiFi.setHostname(ssid);
    #else
      WiFi.hostname(ssid);
    #endif
     
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
     
  #if defined(M5STACK)
    M5.Lcd.setTextColor(TFT_GREEN,TFT_BLACK);
    M5.Lcd.setTextFont(4);
    // LCD display
    M5.Lcd.print("\ncontrol ui:\nhttp://");
    M5.Lcd.print(WiFi.localIP()); 
  #endif
  ESPUI.slider("dry 1", &slider, ControlColor::Alizarin, 128);
  ESPUI.slider("reverb 1", &sliderReverb, ControlColor::Sunflower, 128);
  ESPUI.slider("delay 1", &sliderDelay, ControlColor::Carrot, 128);
  ESPUI.slider("bit 1", &sliderTruncate, ControlColor::Dark, 128);
  ESPUI.slider("phat 1", &sliderPhat, ControlColor::None, 128);
  ESPUI.slider("Master Dry 1L", &masterDry1L, ControlColor::None, 128);
  ESPUI.slider("Master Dry 1R", &masterDry1R, ControlColor::None, 128);
  ESPUI.slider("Master FX Builtin 1L", &masterFxBuiltin1L, ControlColor::None, 128);
  ESPUI.slider("Master FX Builtin 1R", &masterFxBuiltin1R, ControlColor::None, 128);
  ESPUI.slider("Master FX Send 1L", &masterFxSend1L, ControlColor::None, 128);
  ESPUI.slider("Master FX Send 1R", &masterFxSend1R, ControlColor::None, 128);

  /*
     .begin loads and serves all files from PROGMEM directly.
     If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
     (.prepareFileSystem has to be run in an empty sketch before)
   */
  /*
   * Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
   SECURE way of limiting access.
   * Anyone who is able to sniff traffic will be able to intercept your password
   since it is transmitted in cleartext ESPUI.begin("ESPUI Control", "myuser",
   "mypassword");
  */
  //ESPUI.beginSPIFFS("Test123");
  ESPUI.sliderContinuous = true;
  ESPUI.begin("ADAU1452 control ui");
}

void loop(void) {

  if (millis() - oldTime > 5000) {
    switchi = !switchi;
    oldTime = millis();
  }
}
