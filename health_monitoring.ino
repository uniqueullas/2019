// the last working code 16/04/2020 on board

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9 // Lower resolution
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <Adafruit_SSD1306.h>
#define OLED_Address 0x3C // 0x3C device address of I2C OLED. Few other OLED has 0x3D
Adafruit_SSD1306 oled(128, 64); // create our screen object setting resolution to 128x64

const int eme = 12;
int emestate = 0;
int a = 0;
int lasta = 0;
int lastb = 0;
int LastTime = 0;
int ThisTime;
bool BPMTiming = false;
bool BeatComplete = false;
int BPM = 0;
#define UpperThreshold 560
#define LowerThreshold 530

void setup() {
  Serial.begin(9600);
  Serial.println("AIT _ health monitoring");
  delay(2000);
  pinMode(eme, INPUT);
  sensors.begin();

  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  oled.setTextSize(2);
}

void loop()
{
  emestate = digitalRead(eme);
  while (emestate == LOW)
  {
    tone(14, 2093, 200);
    delay(100);
    tone(14, 1000, 200);
    delay(100);
    Serial.println("emg");
    emestate = digitalRead(eme);
  }

  sensors.requestTemperatures();
  int tempC = sensors.getTempCByIndex(0);
  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
  if (a > 60)
  {
    oled.clearDisplay();
    a = 0;
    lasta = a;
  }

  ThisTime = millis();
  int value = analogRead(0);
  oled.setTextColor(WHITE);
  //int b = 60 - (value / 16);
  int b = map(value, 0, 1023, 0, 20);
  oled.writeLine(lasta, lastb, a, b, WHITE);
  lastb = b;
  lasta = a;

  if (value > UpperThreshold)
  {
    if (BeatComplete)
    {
      BPM = ThisTime - LastTime;
      BPM = int(60 / (float(BPM) / 1000));
      BPMTiming = false;
      BeatComplete = false;

    }
    if (BPMTiming == false)
    {
      LastTime = millis();
      BPMTiming = true;
      tone(14, 2093, 100);
    }
  }
  if ((value < LowerThreshold) & (BPMTiming))
    BeatComplete = true;

  //oled.clearDisplay(0,30);
  oled.writeFillRect(0, 50, 128, 16, BLACK);
  oled.setCursor(62, 0);
  oled.print("EMR:");
  oled.setCursor(0, 30);
  oled.print("TMP:");
  oled.print((tempC % 99));
  oled.setCursor(0, 51);
  oled.print("BPM:");
  oled.print(BPM);
  oled.display();
  a++;
  a++;
}
