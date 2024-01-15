#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;  // 서보 객체 생성

void setup() {
  Serial1.begin(115200);

  for(int i = 26; i <= 30; i++) {
    pinMode(i, OUTPUT);
  }
  
  lcd.init();
  lcd.backlight();

  myservo.attach(46);  // 서보모터를 디지털 핀 46번에 연결
  

}

void loop() {
  
  // while(Serial1.available() > 0); //
  // int day_count = Serial1.parseInt();
  // int die_player1 = Serial1.parseInt();
  // int die_player2 = Serial1.parseInt();
  // int isFindMafia = Serial1.parseInt();
  // int lcd_control = Serial1.parseInt();
  // //버퍼 비우기
  // while (Serial1.available() > 0) {
  //   Serial1.read();
  // }
    // 데이터가 도착하기를 기다립니다.

  int day_count = 0; // 이 변수를 루프의 시작 부분에 선언합니다.
  int die_player1 = 0; // 나머지 변수들도 같은 방식으로 선언합니다.
  int die_player2 = 0;
  int isFindMafia = 0;
  int lcd_control = 0;
  if (Serial1.available() > 0) {
    day_count = Serial1.parseInt();
    die_player1 = Serial1.parseInt();
    die_player2 = Serial1.parseInt();
    isFindMafia = Serial1.parseInt();
    lcd_control = Serial1.parseInt();

    // 버퍼 비우기
    while (Serial1.available() > 0) {
      Serial1.read();
    }
  }

  if(day_count == 1) {
    // LED 모두 킴
    for(int i = 24; i <= 33; i++) {
      digitalWrite(i, HIGH);
    }
    
    // 사회자 올라오게끔 Servo 모터 조종
    myservo.write(0);  // 예수 일어나

    // LCD에 "Welcome to Mafia Game!" 4초 출력
    lcd.clear(); // LCD 화면 지우기
    lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
    lcd.print("Hi! Welcome to");
    lcd.setCursor(0, 1); // 커서를 두 번째 행, 첫 번째 열로 이동
    lcd.print("Mafia Game");
    delay(4000); // 4초 대기  

    
    lcd.clear(); // LCD 화면 지우기
    lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
    lcd.print("The First Day...");
    lcd.setCursor(0, 1);
    lcd.print("Who will die?");
    delay(5990); // 6초 대기

  }
  else if(day_count == 2) {
    // LED 모두 끔
    for(int i = 24; i <= 33; i++) {
      digitalWrite(i, LOW);
    }

    // 사회자 내려가게끔 Servo 모터 조종
    myservo.write(90);  // 예수 누워


    lcd.clear(); // LCD 화면 지우기
    lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
    lcd.print("Player " + String(die_player1) + " is killed");
    lcd.setCursor(0, 1);
    lcd.print("by the vote.");
    delay(3000); // 4초 대기

    // LCD에 "The First Night" 3초 출력
    lcd.clear(); // LCD 화면 지우기
    lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
    lcd.print("The First Night..");
    delay(3990); // 4초 대기
  }
  else if(day_count == 3) {
    // LED 모두 킴
    for(int i = 22; i <= 31; i++) {
      digitalWrite(i, HIGH);
    }

    // 사회자 올라오게끔 Servo 모터 조종
    myservo.write(0);  // 예수 일어나

    // LCD에 "Player n, m die" 출력, 그리고 경찰이 마피아 찾았으면 "Police finds Mafia!" 출력 (isFindMafia)
    if(isFindMafia == 1) {
      lcd.clear();
      lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
      lcd.print("Player " + String(die_player1) + ", " + String(die_player2) + " die");
      lcd.setCursor(0, 1);
      lcd.print("Police finds Mafia");
      delay(4000);
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
      lcd.print("Player " + String(die_player1) + ", " + String(die_player2) + " die");
      delay(4000);
    }
    lcd.clear(); // LCD 화면 지우기
    lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
    lcd.print("The Second Day...");
    lcd.setCursor(0, 1);
    lcd.print("Who will die?");
    delay(5990); // 6초 대기
  }
  else if(day_count == 4) {
    // LED 모두 끔
    for(int i = 24; i <= 33; i++) {
      digitalWrite(i, LOW);
    }

    // 사회자 내려가게끔 Servo 모터 조종
    myservo.write(90);  // 예수 누워


    lcd.clear(); // LCD 화면 지우기
    lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
    lcd.print("Player " + String(die_player1) + " is killed");
    lcd.setCursor(0, 1);
    lcd.print("by the vote.");
    delay(3000); // 4초 대기

    // LCD에 "The First Night" 3초 출력
    lcd.clear(); // LCD 화면 지우기
    lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
    lcd.print("The Second Night..");
    delay(3990); // 4초 대기
  }
  else if(day_count == 5) {
    // LED 모두 킴
    for(int i = 22; i <= 31; i++) {
      digitalWrite(i, HIGH);
    }

    // 사회자 올라오게끔 Servo 모터 조종
    myservo.write(0);  // 예수 일어나

    // LCD에 "Player n, m die" 출력, 그리고 경찰이 마피아 찾았으면 "Police finds Mafia!" 출력 (isFindMafia)
    if(isFindMafia == 1) {
      lcd.clear();
      lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
      lcd.print("Player " + String(die_player1) + ", " + String(die_player2) + " die");
      lcd.setCursor(0, 1);
      lcd.print("Police finds Mafia");
      delay(4000);
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
      lcd.print("Player " + String(die_player1) + ", " + String(die_player2) + " die");
      delay(4000);
    }
    lcd.clear(); // LCD 화면 지우기
    lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
    lcd.print("The Last Day...");
    lcd.setCursor(0, 1);
    lcd.print("Who will die?");
    delay(5990); // 6초 대기
  }
  else if(day_count == 6) {
    if(lcd_control == 1) {
      lcd.clear(); // LCD 화면 지우기
      lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
      lcd.print("The Game is done.");
      lcd.setCursor(0, 1);
      lcd.print("Mafia wins !");
      delay(10000);
    }
    else if(lcd_control == 0) {
      lcd.clear(); // LCD 화면 지우기
      lcd.setCursor(0, 0); // 커서를 첫 번째 행, 첫 번째 열로 이동
      lcd.print("The Game is done.");
      lcd.setCursor(0, 1);
      lcd.print("Citizen wins !");
      delay(10000);
    }
  }

}
