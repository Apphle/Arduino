#include <MsTimer2.h>


#define RAD2DEG(x)    (x*180.0/3.14159)
#define DEG2RAD(x)    (x*3.14159/180.0)
#define wheel_track  0.144     //m단위로 구하기    0.1인경우 10cm


const byte outPin = 13; // Output pin: digital pin 4(D4)
//const byte interruptPin1 = 2; // Interrupt pin: D2
//const byte interruptPin2 = 3; // Interrupt pin: D2
const byte encoder1_A = 2;
const byte encoder1_B = 3;
const byte encoder2_A = 18;
const byte encoder2_B = 19;


const byte resetPinm = 5;
volatile byte state = 0;
//unsigned long cnt1 = 0; //추가
//unsigned long cnt2 = 0; //추가
long cnt1 = 0; //추가
long cnt2 = 0; //추가

long cnt1_old = 0; //추가
long cnt2_old = 0; //추가

double pulse_to_distance_left  = 0.2/939.8;
double pulse_to_distance_right = 0.2/503.1;
//double pulse_to_distance_left = 0.2/503.1;



const double odom_left  = 0;
const double odom_right = 0;

double yaw = 0.0;
double yaw_degree = 0.0;

double heading(double x,double y)
{
  double head = atan2(y,x); //Slope Y,Slope X
  return head;
}

void msTimer2_ISR()
{
  char msg[100] = {0x00,};
  double odom_left_delta   = 0.0;
  double odom_right_delta  = 0.0;
  long delta_encoder_left  = 0;
  long delta_encoder_right = 0;
  double theta_delta  = 0.0;
  double theta_delta_degree  = 0.0;
  //double wheel_track = 0.15;
  //const double yaw = 0.0;
  //const double yaw_degree = 0.0;

  delta_encoder_left  = cnt1 - cnt1_old;
  delta_encoder_right = cnt2 - cnt2_old;

  //delta_encoder_left  = 100;
  //delta_encoder_right = -100;
  

  //sprintf(msg,"encoder delta : [%3d %3d]",delta_encoder_left,delta_encoder_right);
  //Serial.println(msg);

  
  odom_left_delta   = delta_encoder_left * pulse_to_distance_left;
  odom_right_delta  = delta_encoder_right * pulse_to_distance_right;



  theta_delta = heading(wheel_track,(odom_right_delta - odom_left_delta));

  Serial.print("delta_encoder_left: ");
  Serial.print(delta_encoder_left); 
  Serial.print("    ");
  Serial.print("delta_encoder_right: ");
  Serial.println(delta_encoder_right);
  
  Serial.print("odom_left_delta: ");Serial.print(odom_left_delta);
  Serial.print("    ");
  Serial.print("odom_right_delta: ");Serial.println(odom_right_delta);
  Serial.print("w.t.:  ");Serial.println(wheel_track);
  
  Serial.print("delta_theta_raidan: ");Serial.println(theta_delta);


  yaw += theta_delta;
  theta_delta_degree = RAD2DEG(theta_delta);   //theta_delta * 180.8/3.14150;  
  
  Serial.print("yaw radian: "); Serial.println(yaw);
  Serial.print("theta_delta_degree: ");Serial.println(theta_delta_degree);Serial.println("");

  yaw_degree += theta_delta_degree;
  Serial.print("yaw degree : ");Serial.println(yaw_degree);Serial.println("");

  
  cnt1_old = cnt1;
  cnt2_old = cnt2;
}

void setup()
{
 pinMode(outPin, OUTPUT); // Output mode
 //pinMode(interruptPin1, INPUT_PULLUP); // Input mode, pull-up
 //pinMode(interruptPin2, INPUT_PULLUP); // Input mode, pull-up
 pinMode(encoder1_A,INPUT_PULLUP);
 pinMode(encoder1_B,INPUT_PULLUP);
 pinMode(encoder2_A,INPUT_PULLUP);
 pinMode(encoder2_B,INPUT_PULLUP);
 pinMode(resetPinm, INPUT);
 //attachInterrupt(digitalPinToInterrupt(interruptPin1), intfunc1, RISING); // Enable interrupt
 //attachInterrupt(digitalPinToInterrupt(interruptPin2), intfunc2, RISING); // Enable interrupt
 attachInterrupt(digitalPinToInterrupt(encoder1_A), intfunc1, RISING); // Enable interrupt
 attachInterrupt(digitalPinToInterrupt(encoder2_A), intfunc2, RISING); // Enable interrupt

 Serial.begin(115200);
 MsTimer2::set(1000,msTimer2_ISR);
 MsTimer2::start();
}

void intfunc1()
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

void intfunc2()
{
  if (digitalRead(encoder2_B) == LOW)
  {
    cnt2++;
  }
  else
  {
    cnt2--;
  }
}


/*void intfunc1()
{
  if(encoder1_A == HIGH)
  {
    cnt1++;
  }
  else
  {
    cnt1++;
  }
}
void intfunc2()
{
  if(encoder1_B == HIGH)
  {
    cnt2++;
  }
  else
  {
    cnt2++;
  }
}*/
/*void intfunc1() // Interrupt function
{
 cnt1++;
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
}

void intfunc2() // Interrupt function
{
 cnt2++;
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
}*/

void loop()
{
 
  
/*Serial.print(cnt1);
 Serial.print("     ");
 Serial.println(cnt2);
 delay(1000);
 if(digitalRead(resetPinm) == HIGH)
 {
  cnt1 = 0;
  cnt2 = 0;
 }*/

}
