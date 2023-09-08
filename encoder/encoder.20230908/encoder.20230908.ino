//const byte interruptPin1 = 2; // Interrupt pin: D2
//const byte interruptPin2 = 3; // Interrupt pin: D2
//unsigned long cnt1  = 0; //추가
//unsigned long cnt2  = 0; //추가 

const byte outPin     = 13; // Output pin: digital pin 4(D4)
const byte resetPinm  = 5;
const byte encoder1_A = 2;
const byte encoder1_B = 3;
const byte encoder2_A = 18;
const byte encoder2_B = 19;
volatile byte state   = 0;
long cnt1             = 0;
long cnt2             = 0; //unsigned 는 음수 사용 못함

void setup()
{
  //pinMode(interruptPin1, INPUT_PULLUP); // Input mode, pull-up
  //pinMode(interruptPin2, INPUT_PULLUP); // Input mode, pull-up
  
  pinMode(outPin, OUTPUT);                // Output mode
  pinMode(encoder1_A, INPUT_PULLUP);      // INPUT mode, puul-up
  pinMode(encoder1_B, INPUT_PULLUP);      // INPUT mode, puul-up
  pinMode(encoder2_A, INPUT_PULLUP);      // INPUT mode, puul-up
  pinMode(encoder2_B, INPUT_PULLUP);      // INPUT mode, puul-up
  pinMode(resetPinm, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder1_A), intfunc1, RISING); // Enable interrupt
  attachInterrupt(digitalPinToInterrupt(encoder2_A), intfunc2, RISING); // Enable interrupt
  Serial.begin(115200);
}


void intfunc1() // Interrupt function
{
  if (digitalRead(encoder1_B) == HIGH) 
  {
    cnt1++;
  }
  else
  {
    cnt1--;
  }
}

void intfunc2() // Interrupt function
{
  if (digitalRead(encoder2_B) == LOW) 
  {
    cnt2++;
  }
  else
  {
    cnt2--;
  }
   /*
  if (state == 0) // If D4 output is low
  {
    digitalWrite(outPin, HIGH);
    state = 1;
  }
  else
  {
    digitalWrite(outPin, LOW);
    state = 0;
  }
  */
}

void loop()
{
  Serial.print(cnt1);
  Serial.print("     "); // 빈칸 생성
  Serial.println(cnt2);
  if (digitalRead(resetPinm) == HIGH)
  {
    cnt1 = 0;
  }
  if (digitalRead(resetPinm) == HIGH)
  {
    cnt2 = 0;
  }
  delay(1000);
}
