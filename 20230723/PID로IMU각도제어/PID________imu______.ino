/////////////////////// PID //////////////////////////
double Kp = 1.0, Ki = 0.45, Kd = 2.8;

///////////////////// driving ////////////////////////

float t_angle[4] {0, 90, 180, 270};

/////////////////////// IMU /////////////////////////
#include <Wire.h>
#include <MPU6050_tockn.h>

#define THRESHOLD_ANGLE1 1
#define THRESHOLD_ANGLE2 0.2


MPU6050 mpu6050(Wire);

float heading_angle = 0.0;
float init_heading_angle = 0.0; // 초기 방향
float target_heading_angle = 90;

float heading_angle_error = 0.0;  //  error 값
float heading_angle_error_old = 0.0;
float heading_angle_error_sum = 0.0;
float heading_angle_error_d = 0.0;
float Output = 0.0;
float Output1 = 0.0;

//////////////////////// sonar ///////////////////////
#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 150 // Maximum distance (in cm) to ping.
#define WALL_GAP_DISTANCE 400 // mm
#define WALL_GAP_DISTANCE_HALF 200 // mm
#define MOTOR_PWM_OFFSET 10
#define MOTOR_SPEED 80

float front_sonar, left_sonar, right_sonar = 0.0;

///////////////L298/////////////////
#define ENA 8
#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12
#define ENB 13

////////////////////// Maze Status ////////////////////
int maze_status = 0;


void setup() 
{
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(115200);                         // 통신 속도를 115200으로 정의

  Wire.begin(); // IMU initiallize
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}
void motor_R_control(int motor_speed_r)         //모터 A의 방향(direction)과 속도(speed)제어
{  

  if (motor_speed_r >= 0) 
  {
    digitalWrite(IN1, LOW);  // 모터의 방향 제어
    digitalWrite(IN2, HIGH);
    if (motor_speed_r >= 255) 
    {
      motor_speed_r = 255;
    }
    analogWrite(ENA, motor_speed_r);            // 모터의 속도 제어
  }

  else {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    if (motor_speed_r <= -255) 
    {
      motor_speed_r = -255;
    }
    analogWrite(ENA, -motor_speed_r);
  }

}
void motor_L_control(int motor_speed_l)     //모터 B의 방향(direction)과 속도(speed)제어
{  

  if (motor_speed_l >= 0) 
  {
    digitalWrite(IN3, LOW);   // 모터의 방향 제어
    digitalWrite(IN4, HIGH);
    if (motor_speed_l >= 255) 
    {
      motor_speed_l = 255;
    }
    analogWrite(ENB, motor_speed_l);  // 모터의 속도 제어
  }

  else 
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    if (motor_speed_l <= -255) 
    {
      motor_speed_l = -255;
    }
    analogWrite(ENB, -motor_speed_l);
  }
}

void imu_rotation(void) 
{
  bool flag = 1;  // bool type - 0 or 1
  while (flag) 
  {
    read_imu_sensor();
    Output = Kp * heading_angle_error + Ki * heading_angle_error_sum + Kd * heading_angle_error_d;
    if (heading_angle_error > THRESHOLD_ANGLE1) // 반시계 방향으로 회전
    { 
      motor_L_control(Output);
      motor_R_control(-Output);
    }
    else if ((heading_angle_error >= THRESHOLD_ANGLE2) && (heading_angle_error <= THRESHOLD_ANGLE1)) { // 정지
      motor_L_control(Output);
      motor_R_control(-Output);
    }
    else if ((heading_angle_error > -THRESHOLD_ANGLE2) && (heading_angle_error < THRESHOLD_ANGLE2)) { // 정지
      heading_angle_error = 0;
      heading_angle_error_sum = 0;
      heading_angle_error_d = 0;
      Output1 = Kp * heading_angle_error + Ki * heading_angle_error_sum + Kd * heading_angle_error_d;
      motor_L_control(Output1);
      motor_R_control(Output1);
      flag = 0;
    }
    else if ((heading_angle_error >= -THRESHOLD_ANGLE1) && (heading_angle_error <= -THRESHOLD_ANGLE2)) { // 정지
      motor_L_control(Output);
      motor_R_control(-Output);
    }
    else                                        // heading_angle_error < -THRESHOLD_ANGLE1 // 시계방향으로 회전
    { 
      motor_L_control(Output);
      motor_R_control(-Output);
    }
  }
}

void read_imu_sensor(void) 
{
  mpu6050.update();
  float heading1 = mpu6050.getAngleZ();
  mpu6050.update();
  float heading2 = mpu6050.getAngleZ();
  mpu6050.update();
  float heading3 = mpu6050.getAngleZ();
  heading_angle = (heading1 + heading2 + heading3) / 3;

  heading_angle = 360 - heading_angle;  // 회전 좌표계를 반시계 방향으로 전환

  while (heading_angle >= 360) 
  {
    heading_angle -= 360;
  }
  
  heading_angle_error = target_heading_angle - heading_angle;
  
  if (heading_angle_error > 180) 
  {
    heading_angle_error = heading_angle_error - 360;
  }
  else if (heading_angle_error < -180) 
  {
    heading_angle_error = heading_angle_error + 360;
  }
  else
  {
    
  }
  
  heading_angle_error_sum += heading_angle_error;
  heading_angle_error_d = heading_angle_error - heading_angle_error_old;
  heading_angle_error_sum = (heading_angle_error_sum >=  100) ?  100 : heading_angle_error_sum;
  heading_angle_error_sum = (heading_angle_error_sum <= -100) ? -100 : heading_angle_error_sum;

  Serial.print("Heading Angle Error : ");
  Serial.print(heading_angle_error);  // heading angle error 표시
  Serial.print(" = ");
  Serial.print(target_heading_angle);
  Serial.print(" - ");
  Serial.println(heading_angle); // headning_angle 표시
  
  heading_angle_error_old = heading_angle_error;
}
void loop() 
{
  target_heading_angle = 40;
  imu_rotation();
  delay(2000);
  target_heading_angle = 160;
  imu_rotation();
  delay(2000);
}
