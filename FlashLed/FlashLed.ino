/*
  MsTimer2 is a small and very easy to use library to interface Timer2 with
  humans. It's called MsTimer2 because it "hardcodes" a resolution of 1
  millisecond on timer2
  For Details see: http://www.arduino.cc/playground/Main/MsTimer2
*/
#include <MsTimer2.h>

#if ARDUINO >= 100
const int led_pin = LED_BUILTIN;	// 1.0 built in LED pin var
#else
const int led_pin = 13;			// default to pin 13
#endif


void flash()
{
  static boolean output = HIGH; // output을 HIGH로
  
  digitalWrite(led_pin, output);
  output = !output; // HIGH를 LOW로
}

void setup()
{
  pinMode(led_pin, OUTPUT);

  MsTimer2::set(500, flash); // 500ms period
  MsTimer2::start();
}

void loop()
{
}
