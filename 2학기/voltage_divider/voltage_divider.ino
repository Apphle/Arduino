void setup() 
{
  Serial.begin(9600);
}
void loop() 
{
  int sensorValue = analogRead(A0);
  float resistance1 = 15.4;
  float voltage_out = sensorValue * (5.0 / 1023.0);
  float resistance2 = (resistance1 * voltage_out) / (5.0 - voltage_out);
  Serial.println(resistance2);
}
