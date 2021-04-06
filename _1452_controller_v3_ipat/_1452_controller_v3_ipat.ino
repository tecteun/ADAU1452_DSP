
#define M5STACK

#include <MIDI.h>
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
#define MOD_INDIRECTPARAMACCESSMODULE_LEVEL1L_LINX_ADDR 24601
#define MOD_INDIRECTPARAMACCESSMODULE_LEVEL1R_LINX_ADDR 24602
#define MOD_INDIRECTPARAMACCESSMODULE_LEVEL2L_LINX_ADDR 24603
#define MOD_INDIRECTPARAMACCESSMODULE_LEVEL2R_LINX_ADDR 24604
#define MOD_INDIRECTPARAMACCESSMODULE_REVERB1_2_LOOP_GAIN_HALF_ADDR 24605
#define MOD_INDIRECTPARAMACCESSMODULE_REVERB1_2_LP_ADDR 24606
#define MOD_INDIRECTPARAMACCESSMODULE_REVERB1_2_BASS_GAIN_ADDR 24607
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_2L_TARGET_ADDR 24608
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_1R_TARGET_ADDR 24609
#define MOD_INDIRECTPARAMACCESSMODULE_DELAY_VALUE_ADDR 24610
#define MOD_INDIRECTPARAMACCESSMODULE_REVERB1_2_LOOP_GAIN_ADDR 24611
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_3L_TARGET_ADDR 24612
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_3R_TARGET_ADDR 24613
#define MOD_INDIRECTPARAMACCESSMODULE_LEVEL3L_LINX_ADDR 24614
#define MOD_INDIRECTPARAMACCESSMODULE_LEVEL3L_LINX_LO_ADDR 24615
#define MOD_INDIRECTPARAMACCESSMODULE_LEVEL3R_LINX_ADDR 24616
#define MOD_INDIRECTPARAMACCESSMODULE_LEVEL3R_LINX_LO_ADDR 24617
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_3L_TARGET_ADDR 24618
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_3R_TARGET_ADDR 24619
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_3L_TARGET_ADDR 24620
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_3R_TARGET_ADDR 24621
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_3L_TARGET_ADDR 24622
#define MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_3R_TARGET_ADDR 24623



struct MySettings : public midi::DefaultSettings
{
  static const unsigned SysExMaxSize = 1024; // Accept SysEx messages up to 1024 bytes long.
  static const bool UseRunningStatus = false; // My devices seem to be ok with it.
  static const long BaudRate = 31250;
};

// Create a 'MIDI' object using MySettings bound to Serial2.
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial2, MIDI, MySettings);

#if defined(M5STACK)
#include <M5Stack.h>
TFT_eSprite spr = TFT_eSprite(&M5.Lcd);
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


void numberCall(Control sender, int type) {
  Serial.println(sender.value);
}

void textCall(Control sender, int type) {
  Serial.println(sender.value);
}

#if defined(M5STACK)
int SS_PIN = G22;//D0;
#else
int SS_PIN = D0;
#endif

// 5.23 (decimal) format
// https://github.com/AidaDSP/AidaDSP/blob/master/Software/Libraries/Arduino/Aida2/AidaDSP2.cpp
#define FLOAT_TO_FIXED(a)        (a*((int32_t)1 << 23))
void float_to_fixed(float value, uint8_t *buffer)
{
  int32_t fixedval = 0;

  fixedval = FLOAT_TO_FIXED(value);
  buffer[0] = (fixedval >> 24) & 0xFF;
  buffer[1] = (fixedval >> 16) & 0xFF;
  buffer[2] = (fixedval >> 8) & 0xFF;
  buffer[3] = fixedval & 0xFF;
}

// Convert float 5.23 to 28.0
int32_t float_to_int(int32_t value)
{
  return value * ((int32_t)1 << 23);
}

uint8_t* int_to_bytes(int value)
{
  static uint8_t buffer[4];
  buffer[0] = (value >> 24) & 0xFF;
  buffer[1] = (value >> 16) & 0xFF;
  buffer[2] = (value >> 8) & 0xFF;
  buffer[3] = value & 0xFF;
  return buffer;
}

void slider(Control *sender, int type) {
  uint8_t buf[4];
#if defined(M5STACK)
  //
  M5.Power.begin();
  M5.Power.setPowerBoostSet(true);
  //M5.Lcd.print(sender->value.toInt());
  M5.Lcd.fillRect(0, 0, 320, 20, 0);
  M5.Lcd.progressBar(0, 0, 320, 20, sender->value.toInt());
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
#define REG_SOFT_RESET_IC_1_ADDR                  0xF890
void enableDSP() {
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));
  uint16_t memoryAddress = REG_SOFT_RESET_IC_1_ADDR;
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  uint8_t LSByte = (uint8_t)memoryAddress & 0xFF;
  uint8_t MSByte = memoryAddress >> 8;
  SPI.transfer(MSByte);
  SPI.transfer(LSByte);
  byte cmd[2] = {0x00, 0x00};
  SPI.transfer(cmd, 2);
  digitalWrite(SS_PIN, HIGH);

  SPI.endTransaction();
}
// send 5.23 float, fixed number format (value / 100) dsp 1.0 range
void send(int param, int value) {
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(param);
  uint8_t buf[4];
  // convert to float 
  float_to_fixed(value / 100., buf);
  SPI.transfer(buf, 4);
  digitalWrite(SS_PIN, HIGH);

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(MOD_INDIRECTPARAMACCESSMODULE_START_ADDRESS_ADDR);
  SPI.transfer(int_to_bytes(param), 4);
  digitalWrite(SS_PIN, HIGH);

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(MOD_INDIRECTPARAMACCESSMODULE_NUM_OF_LOADS_AND_TRIGGER_ADDR);
  SPI.transfer(int_to_bytes(1), 4);
  digitalWrite(SS_PIN, HIGH);

  SPI.endTransaction();
}

// send 5.23 integer format
void send_523(int param, int value) {
  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(param);
  // convert int to 5.23
  SPI.transfer(int_to_bytes(value*pow(23+1, 2)), 4);
  digitalWrite(SS_PIN, HIGH);

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(MOD_INDIRECTPARAMACCESSMODULE_START_ADDRESS_ADDR);
  SPI.transfer(int_to_bytes(param), 4);
  digitalWrite(SS_PIN, HIGH);

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0b00000000); //== write //0x00000001 == read
  SPI.transfer16(MOD_INDIRECTPARAMACCESSMODULE_NUM_OF_LOADS_AND_TRIGGER_ADDR);
  SPI.transfer(int_to_bytes(1), 4);
  digitalWrite(SS_PIN, HIGH);

  SPI.endTransaction();
}
float log10 (float x) {
  return (log(x) / log(10));
}
double read_level(int address) {

  int length = 4;


  SPI.beginTransaction(SPISettings(22000000, MSBFIRST, SPI_MODE3));
  digitalWrite(SS_PIN, LOW);
  // SPI read address + read/!write bit
  SPI.transfer(0x1);
  SPI.transfer(address >> 8);
  SPI.transfer(address & 0xff);
  int32_t result = 0;
  byte register_value[4];
  for (int i = 0; i < length; i++) {
    register_value[i] = SPI.transfer(0);
  }

  for (int i = 0; i < length; i++) {
    result = (result << 8) + register_value[i];
  }

  //5.23 input back to float
  // 2^(23+1) == 1.0 in dsp land
  float converted = result / pow(23+1, 2);

  // result *= 0xFF;
  // result >>= 24;
  // Serial.println(20*log10(converted));

  digitalWrite(SS_PIN, HIGH);
  SPI.endTransaction();

  // convert to db rms/spl
  return 20*log10(converted);
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

void handleControlChange(byte channel, byte number, byte value) {

  Serial.println(number);
  Serial.println(value);
  switch ((int)number) {

    case 8:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_1L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 9:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_1R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 10:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_2L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 11:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_2R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 12:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_3L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 13:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_SEND_3R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;

    case 16:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_1L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 17:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_1R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 18:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_2L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 19:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_2R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 20:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_3L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 21:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_FX_BUILTIN_3R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;


    case 32:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_1L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 33:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_1R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 34:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_1R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 35:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_2R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 36:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_3R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 37:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2_3R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;


    case 40:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_1L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 41:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_1R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 42:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 43:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_2R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 44:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_3L_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;
    case 45:
      send(MOD_INDIRECTPARAMACCESSMODULE_MASTER_DRY_3R_TARGET_ADDR, map(value, 0, 127, 0, 177827)/100); break;

    case 15:
      send(MOD_INDIRECTPARAMACCESSMODULE_REVERB1_2_LOOP_GAIN_ADDR, map(value, 0, 127, 0, 150));
      send(MOD_INDIRECTPARAMACCESSMODULE_REVERB1_2_LOOP_GAIN_HALF_ADDR, map(value, 0, 127, 0, 75)); break;
    case 23:
      send(MOD_INDIRECTPARAMACCESSMODULE_REVERB1_2_LP_ADDR, map(value, 0, 127, 0, 50)); break;
    case 31:
      send(MOD_INDIRECTPARAMACCESSMODULE_REVERB1_2_BASS_GAIN_ADDR, map(value, 0, 127, 0, -125)); break;
    case 6:
      send_523(MOD_INDIRECTPARAMACCESSMODULE_DELAY_VALUE_ADDR,  value < 64 ? map(value, 0, 127, 0, 50):map(value, 0, 127, 50, 375)); break;

  }
}

void setup(void) {

  MIDI.setHandleControlChange(handleControlChange);
  MIDI.begin(MIDI_CHANNEL_OMNI);
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
  spr.createSprite(320,100, 2);
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
  // enableDSP();
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
  M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  M5.Lcd.setTextFont(4);
  // LCD display
  M5.Lcd.print("\ncontrol ui:\nhttp://");
  M5.Lcd.print(WiFi.localIP());

  xTaskCreatePinnedToCore(
    task3,     /* Function to implement the task */
    "task3",   /* Name of the task */
    4096,      /* Stack size in words */
    NULL,      /* Task input parameter */
    1,         /* Priority of the task */
    NULL,      /* Task handle. */
    1);        /* Core where the task should run */
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
     Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
    SECURE way of limiting access.
     Anyone who is able to sniff traffic will be able to intercept your password
    since it is transmitted in cleartext ESPUI.begin("ESPUI Control", "myuser",
    "mypassword");
  */
  //ESPUI.beginSPIFFS("Test123");
  ESPUI.sliderContinuous = true;
  ESPUI.begin("ADAU1452 control ui");
}

double drawVU(int param, byte x, double previous) {
  if (NULL == previous) {
    previous = 0.;
  }
  double level = read_level(param);
  byte width = 40;
  int height = ceil(map((level + previous)/2, 0, 140, 0, 100));
  //spr.fillRect(x, max(0, 100 - height), width, max(0, height), GREEN);
  byte red = 0;
  byte green = 0;
  byte blue = 0;
  unsigned int colour;
  while(height --> 0){
    int y = 100 - height;
    
    red = height > 70 ? map(height, 100, 70, 240, 255)  : 0;
    green = height < 80 ? map(height, 0, 95, 200, 255) : 0;
    colour = red << 11 | green << 5 | blue;
    spr.drawFastHLine(x, y, width, colour);
  }
  return level;
}

void task3(void * pvParameters) {
  double _1L = NULL;
  double _1R = NULL;
  double _2L = NULL;
  double _2R = NULL;
  double _3L = NULL;
  double _3R = NULL;
  for (;;) {
    spr.fillScreen(BLACK);
    _1L = drawVU(MOD_INDIRECTPARAMACCESSMODULE_LEVEL1L_LINX_ADDR, 10, _1L);
    _1R = drawVU(MOD_INDIRECTPARAMACCESSMODULE_LEVEL1R_LINX_ADDR, 60, _1R);
    _2L = drawVU(MOD_INDIRECTPARAMACCESSMODULE_LEVEL2L_LINX_ADDR, 110, _2L);
    _2R = drawVU(MOD_INDIRECTPARAMACCESSMODULE_LEVEL2R_LINX_ADDR, 160, _2R);
    _3L = drawVU(MOD_INDIRECTPARAMACCESSMODULE_LEVEL3L_LINX_ADDR, 210, _3L);
    _3R = drawVU(MOD_INDIRECTPARAMACCESSMODULE_LEVEL3R_LINX_ADDR, 260, _3R);
    spr.pushSprite(0, 120);
    vTaskDelay(1000/60);
  }
  
}

void loop(void) {
  
  MIDI.read();
  M5.update();
  // make time for the other thread
  
}
