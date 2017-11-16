#include <Adafruit_NeoPixel.h>

#define pads 9
#define ledpin 2
#define startpad 4
#define v 500
#define color_idle 0x0000FF
#define color_active 0xFF0000
#define color_pressed 0x00FF00
#define times 20

byte pins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11};
byte active = 255;
byte activeOld = 255;
byte anzahl = 0;
boolean inGame;

unsigned long time;
unsigned long endtime;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(pads, ledpin, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  strip.begin();
  reIdle();
  millis();
  pinMode(A0,INPUT);
  randomSeed(analogRead(A0)); 
}

void loop()
{
  if(!inGame&&digitalRead(pins[startpad]))
  {
    inGame=1;
    strip.setPixelColor(startpad,color_idle);
    strip.show();
    Serial.println("S");
    delay(v);
    time=millis();
    newPad();
  }

  if(anzahl==10&&inGame==1)
  {
    endtime=millis()-time;
    reIdle();

  }


  if (digitalRead(pins[active])&&inGame)
  {
    strip.setPixelColor(active,color_pressed);
    strip.show();
    delay(v);
    strip.setPixelColor(active,color_idle);
    strip.show();
    newPad();
  }
}




void newPad()
{
  
  while(activeOld==active)
  {
  active=random(0,pads);
  }
  activeOld=active;
  strip.setPixelColor(active,color_active);
  strip.show();
  anzahl++;
}

void reIdle()
{
  for (int i = 0; i < pads; i++)
  {
    pinMode(pins[i], INPUT);
    strip.setPixelColor(i,color_pressed);
  }
  strip.show();
  delay(500);
  for (int i = 0; i < pads; i++)
  {
    pinMode(pins[i], INPUT);
    strip.setPixelColor(i,color_idle);
  }
  strip.show();
  Serial.print("T:");
  Serial.println(endtime);
  inGame=0;
  anzahl=0;
  strip.setPixelColor(startpad,color_active);
  strip.show();
}
