void DayLED() {
  PORTB = 0x07;
  PORTD = 0xFF;
}

void NightLED() {
  PORTB = 0x00;
  PORTD = 0x00;
}


void setup() {
 DDRB = 0x07;
 DDRD = 0xFF; 
}

void loop() {
  // Master 아두이노에서 블루투스로 isDay flag 값을 받아옴.
  if(isDay == 1) {
   DayLED(); 
  }
  else {
    NightLED();
  }
}
