#include <Adafruit_NeoPixel.h>

#define pads 9
#define ledpin 2

byte pins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11};
int taste = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(pads, ledpin, NEO_GRB + NEO_KHZ800);

void setup()
{
  for (int i = 0; i < pads; i++)
  {
    pinMode(pins[i], INPUT);
    strip.setPixelColor(i, Color(0, 255, 0));
  }
  strip.begin();
  strip.show();
  
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Read Pins: [");
  for (int i = 0; i < pads; i++)
  {
    taste = digitalRead(pins[i]);
    Serial.print(taste);
    Serial.print(" ");
    if (taste)
    {
    strip.setPixelColor(i, Color(255, 0, 0));
    }
    else
    {
      strip.setPixelColor(i, Color(0, 255, 0));
    }
  }
  strip.show();
  Serial.println("]");
}

uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}
