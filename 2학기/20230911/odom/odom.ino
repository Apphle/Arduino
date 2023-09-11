//const byte interruptPin1 = 2; // Interrupt pin: D2
//const byte interruptPin2 = 3; // Interrupt pin: D2
//unsigned long cnt1  = 0; //추가
//unsigned long cnt2  = 0; //추가 

#include <MsTimer2.h>

const byte outPin     = 13; // Output pin: digital pin 4(D4)
const byte resetPinm  = 5;
const byte encoder1_A = 2;
const byte encoder1_B = 3;
const byte encoder2_A = 18;
const byte encoder2_B = 19;

volatile byte state   = 0;

long cnt1 = 0;
long cnt2 = 0; //unsigned 는 음수 사용 못함

long cnt1_old = 0;            
long cnt2_old = 0;           

double pulse_to_distance_left  = 0.2/502.7;
double pulse_to_distance_right = 0.2/904.3;

const double odom_left  = 0;
const double odom_right = 0;

double heading(double x, double y)
{
  double head = atan2(y, x); //slope Y, slope X
  return head;
}

void msTimer2_ISR()
{
  double odom_left_delta = 0.0;
  double odom_right_delta = 0.0;
  double theta_delta = 0.0;
  double wheel_track = 0.15; 
  
  odom_left_delta  = ( cnt1 - cnt1_old ) * pulse_to_distance_left;
  odom_right_delta = ( cnt2 - cnt2_old ) * pulse_to_distance_right;

  theta_delta = heading( wheel_track, (odom_right_delta - odom_left_delta) );
  
  Serial.print(odom_left_delta);
  Serial.print("     "); // 빈칸 생성
  
  Serial.println(odom_right_delta);
  Serial.print("     ");
  theta_delta = theta_delta * 180.0/ 3.14159;
  Serial.println(theta_delta);
  
  cnt1_old = cnt1;
  cnt2_old = cnt2;
}

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
  MsTimer2::set(100,msTimer2_ISR);
  MsTimer2::start();
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
