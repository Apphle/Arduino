#include <MsTimer2.h>

#if ARDUINO >= 100
const int led_pin = LED_BUILTIN;  // 1.0 built in LED pin var
#else
const int led_pin = 13;     // default to pin 13
#endif
const int debug_pin1 = 33;
const int debug_pin2 = 34;
const int debug_pin3 = 35;

void serialprint(void)                                     //
{
  digitalWrite(debug_pin1, HIGH); //함수의 시작
  Serial.print("");
  digitalWrite(debug_pin1, LOW);  //함수의 끝
}

void flash()                                                 //500ms 마다 실행
{
  digitalWrite(debug_pin2, HIGH);  //함수의 시작
  serialprint();
  digitalWrite(debug_pin2, LOW);   //함수의 끝
}

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(debug_pin1, OUTPUT);
  pinMode(debug_pin2, OUTPUT);
  pinMode(debug_pin3, OUTPUT);
  Serial.begin(115200);
  MsTimer2::set(20, flash); // 500ms period
  MsTimer2::start();
}

void loop()
{
  digitalWrite(debug_pin3, HIGH);
  digitalWrite(debug_pin3, LOW);
}
