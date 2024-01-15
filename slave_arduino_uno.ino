#include <Stepper.h>

const int stepsPerRevolution = 200;  // 스텝 모터의 스텝 수를 설정합니다. 모터에 따라 다를 수 있습니다.
const int motorPin1 = 8;
const int motorPin2 = 9;
const int motorPin3 = 10;
const int motorPin4 = 11;

// Stepper 라이브러리 클래스 인스턴스를 생성합니다.
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);
int day_count;
void setup() {
  Serial.begin(115200);
  // 모터의 속도를 설정합니다. (rpm)
  myStepper.setSpeed(60);
}

void loop() {
  if (Serial.available() > 0) {
    day_count = Serial.parseInt();
    // 버퍼 비우기
    while (Serial.available() > 0) {
      Serial.read();
    }
  }

  if(day_count % 2 == 1) {
    for(int i = 0; i < 16; i++) {
        myStepper.step(-stepsPerRevolution);
        delay(600);      
    }
  }
  // else if(day_count % 2 == 0) {
    
  //   delay(6000); // 밤은 7초
  // }
}