#define ImuPin1 12
#define ImuPin2 13

#include <MPU6050_tockn.h> // imu
#include <Wire.h>
MPU6050 mpu6050(Wire);

const unsigned long interval_ms = 100;
unsigned long previous_Millis 
signed current_imu_angle = 0;
signed old_imu_angle = 0;
signed delta_imu_angle = 0;

void setup()
{
  pinMode(pulse, OUTPUT);
  pinMode(ImuPin1, OUTPUT);
  pinMode(ImuPin2, OUTPUT);
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}
void loop()
{
  mpu6050.update();= 0;
bool isHigh = false;
  unsigned long currentMillis = millis();
  delta_imu_angle = current_imu_angle - old_imu_angle;

  if (currentMillis - previous_Millis >= interval_ms)
  {

    digitalWrite(pulse, HIGH);
    previous_Millis = currentMillis;
    digitalWrite(pulse, LOW);
  }
  old_imu_angle = current_imu_angle;
  

  Serial.print("delta_imu_angle ");
  Serial.println(delta_imu_angle);
}
