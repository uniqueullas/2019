/*The code is written for AIT college project, called HEALTH MONITORING SYSTEM
   ECE dept Final year project
   board used is NODE MCU version 2.3
   micro contoller NodeMCU 1.0(ESP-12E MOdule)
   Upload speed 115200
   80 Mhz CPU frequency
   auto bootloader
   code uploaded to https://github.com/uniqueullas/Node-MCU-2019/blob/master/health_monitoring.ino+
   code local path C:\Users\DELL\Documents\Arduino\health_moitoring_with_function
       ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
  /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on NodeMCU
*/

// the last working code 13/05/2020 on board
// uploading to blynk.com maikinng it iot
// adding all features..!

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "peBRDC9wI9FEz-VwIqmlnebONFNcyb3q";
char ssid[] = "new";
char pass[] = "12345678";
BlynkTimer timer;

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 //Selecting the pin GPIO 02 [D4] for temprature sensor
#define TEMPERATURE_PRECISION 9 // Lower resolution
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <Adafruit_SSD1306.h>
#define OLED_Address 0x3C // 0x3C device address of I2C OLED. Few other OLED has 0x3D
Adafruit_SSD1306 oled(128, 64); // create our screen object setting resolution to 128x64

WidgetLED led1(V2);
WidgetLED led2(V5);
const int eme = 12; //Selecting the pin GPIO 12 [D6] for emergency switch
const int bot = 13; //Selecting the pin GPIO 13 [D7] for bottle
const int hb = 0; //Selecting the pin ADC0 [A0] for Heart beat sensor
int emestate = 0;
bool botstate = LOW;
int a = 0;
int lasta = 0;
int lastb = 0;
int LastTime = 0;
int ThisTime;
bool BPMTiming = false;
bool BeatComplete = false;
int BPM = 0;
int value = 0;
#define UpperThreshold 560
#define LowerThreshold 530
void wifi_connect_info();


void setup() {
  Serial.begin(9600);
  // Setup a function to be called every second
  //timer.setInterval(1000L, sendSensor);
  Serial.println("--------------------------AIT_Health_Monitoring_Sysyem--------------------------");
  Serial.println("                            _     ___  ___ ");
  Serial.println("                           /__\    |    |  ");
  Serial.println("                          /    \  _|_   |       2019 Project");
  delay(2000);
  pinMode(eme, INPUT);
  pinMode(bot, INPUT);
  sensors.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  oled.writeFillRect(0, 50, 128, 16, BLACK);
  oled.setTextSize(2);
  oled.clearDisplay();

  wifi_connect_info();
  Blynk.begin(auth, ssid, pass);
  Serial.println("Entering loop....!");
  Serial.println("Function :emergency initialized");
  Serial.println("Function :temparature initialized");
  Serial.println("Function :ecg initialized");
  Serial.println("Function :bpm initialized");
  Serial.println("Function :displai initialized");
  Serial.println("*******Running on loop*******");
}

void loop() {
  value = 0;
  emestate = digitalRead(eme);
  led1.off();
  led2.off();
  value = analogRead(hb);// Reading the value from temprature sensor
  //Serial.print("value ");
  //Serial.println(value);
  bool lvl = level ();
  int temp = temparature ();
  ecg(value);
  int BPM = bpm(value);
  displai(BPM, temp, lvl);
  upload(BPM, temp);
  while (emestate == LOW) {
    led1.on();
    emergency();
    emestate = digitalRead(eme);
  }
}

void emergency() {
  //Serial.println("Function calling-emergency");
  //Serial.println("...");
  oled.clearDisplay();
  tone(14, 2093, 200);
  delay(100);
  tone(14, 1000, 200);
  delay(100);
  Serial.println("Emergency...!");
  Serial.println("              ");
  oled.writeFillRect(0, 50, 128, 16, BLACK);
  oled.setCursor(0, 1);
  oled.print("EMERGENCY!");
  oled.display();
  int temp = temparature ();
  int value = analogRead(0);
  delay(50);
  int BPM = bpm(value);
  bool lvl = level ();
  displai(BPM, temp, lvl);
  String body = String("Emergency button pressed \r\nThe heart beat rate is:") + BPM +
                "\r\nThe Body temprature is:" + temp +
                "\r\nThe Drip bottle status is:" + lvl +
                "\r\nFor quick contact +91 82*******12";
  Serial.println(body);
  Blynk.email("ullas6558@gmail.com", "Emergency..!", body);
}

bool level () {
  botstate = digitalRead(bot);
  if (botstate == LOW) {
    return HIGH;
  }
  else {
    return LOW;
  }
}

int temparature () {
  //Serial.println("Function calling-temparature");
  //Serial.println("...");
  sensors.requestTemperatures();
  int tempC = sensors.getTempCByIndex(0);
  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C) {
    //Serial.print("Temperature for the device 1 (index 0) is: ");
    //Serial.println(tempC);
    //Serial.println("...");
  }
  else {
    Serial.println("Error: Could not read temperature data");
  }
  return tempC;
}

int ecg(int value) {
  //Serial.println("Function calling-ecg");
  //Serial.println("...");
  if (a > 60) {
    oled.clearDisplay();
    a = 0;
    lasta = a;
  }
  ThisTime = millis();
  oled.setTextColor(WHITE);
  //int b = 60 - (value / 16);
  int b = map(value, 0, 1023, 0, 20);
  oled.writeLine(lasta, lastb, a, b, WHITE);
  oled.display();
  lastb = b;
  lasta = a;
  a = a + 3;
  return b;
}

int bpm(int value) {
  //Serial.println("Function calling-bpm");
  //Serial.println("...");
  if (value > UpperThreshold) {
    if (BeatComplete) {
      BPM = ThisTime - LastTime;
      BPM = int(60 / (float(BPM) / 1000));
      BPMTiming = false;
      BeatComplete = false;
    }
    if (BPMTiming == false) {
      LastTime = millis();
      BPMTiming = true;
      tone(14, 2093, 100);
    }
  }
  if ((value < LowerThreshold) & (BPMTiming))
    BeatComplete = true;
  return BPM;
}

void displai(int BPM, int temp, bool bottle) {
  //Serial.println("Function calling-displai");
  //Serial.println("...");
  oled.writeFillRect(0, 50, 128, 16, BLACK);
  oled.setCursor(0, 30);
  oled.print("TMP:");
  oled.print((temp % 99));
  oled.setCursor(0, 51);
  oled.print("BPM:");
  oled.println(BPM);
  Serial.print("   TMP:");
  Serial.print(temp);
  Serial.print("   BPM:");
  Serial.println(BPM);

  if (bottle == HIGH) {
    Serial.print("Bottle: Running");
    oled.setCursor(80, 20);
    oled.print("Bot:");
    oled.setCursor(80, 40);
    oled.println("Run");
  }
  else {
    Serial.print("Bottle: Empty..!");
    led2.on();
    oled.setCursor(80, 20);
    oled.print("Bot:");
    oled.setCursor(80, 40);
    oled.println("Empty");
    tone(14, 93, 200);
    delay(100);
    String bod = String("Check out the drip bottle..!, seems to be empty or may be missplaced. Emercrncy to attend Patent Number 48\r\nStatus of all sersor...\r\nHeart Rate:") + BPM +
                 "\r\nTemprature is:" + temp +
                 "\r\nFor quick contact call @ +91 82*******12";
    Serial.println(bod);
    Blynk.email("ullas6558@gmail.com", "Drip Bottle Empty..!", bod);
  }
  oled.display();
}

void upload(int BPM, int temp) {
  Blynk.virtualWrite(V0, BPM);
  Blynk.virtualWrite(V1, temp);
  //Blynk.virtualWrite(V5, lvl);
  // Blynk.virtualWrite(V3, ecg)
  Blynk.run();
}

void wifi_connect_info() {
  Serial.println("To Run the project we must connect to a network...!");
  Serial.println("Connecting steps:");
  Serial.println("1.Create a Hotspot");
  Serial.println("2.Name/SSID :new");
  Serial.println("3.Password :12345678");
  Serial.println("4.Wait for the system to connect");
  Serial.println("Network Status : OFF LINE MODE");
  oled.setCursor(5, 1);
  oled.print("H M S 2019");
  oled.setCursor(0, 10);
  oled.print("SSID:new");
  oled.setCursor(0, 20);
  oled.print("Password:");
  oled.setCursor(0, 30);
  oled.print("12345678");
  delay(1000);
  oled.display();
}
