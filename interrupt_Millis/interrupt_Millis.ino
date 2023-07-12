// encoder pin
const int encoderPinA = 2; // 핀 번호
const int encoderPinB = 3; // 핀 번호
int encoderPos = 0;
int digi;
unsigned long currentMillis;
unsigned long oldMillis;
unsigned long dif;

void doEncoder() { // encoderPos = 0 일때 부르는 함수
  currentMillis = millis();
  dif = currentMillis - oldMillis;
  digi = digitalRead(encoderPinB);
  if (digi == LOW) {
    encoderPos++;
  }
  else if (digi == HIGH) {
    encoderPos--;
  }
  else {
  }
  oldMillis = currentMillis;
}

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoder, RISING);// (핀 번호, 인터럽트가 일어났을때 사용할 함수 이름, 5개 mode 중 1개)

  Serial.begin(115200);
}

void loop() {

  Serial.print("A   ");
  Serial.println(1);
  Serial.print("B   ");
  Serial.println(digi);
  Serial.print("encoderPos  ");
  Serial.println(encoderPos);
  Serial.print("dip  ");
  Serial.println(dip);
}
