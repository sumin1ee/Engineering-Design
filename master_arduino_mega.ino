void day_LED(char role_array[12][10], bool player_life_array[12], int player_pin_array[12]) {
  for(int i = 0; i < 12; i++) {
    if(player_life_array[i]) {
      if(!strcmp(role_array[i], "Citizen")){
        int player_pin = player_pin_array[i];
        setColor(player_pin, player_pin + 1, player_pin + 2, 0, 200, 0);
      }
      else if(!strcmp(role_array[i], "Police")) {
        int player_pin = player_pin_array[i];
        setColor(player_pin, player_pin + 1, player_pin + 2, 0, 0, 200);
      }
      else {
        int player_pin = player_pin_array[i];
        setColor(player_pin, player_pin + 1, player_pin + 2, 200, 0, 0);
      }
    }
    else{
      int player_pin = player_pin_array[i];
      setColor(player_pin, player_pin + 1, player_pin + 2, 0, 0, 0);
    }
  }
}

void night_LED(char role_array[12][10], bool player_life_array[12], int player_pin_array[12]) {
  for(int i = 0; i < 12; i++) {
    if(!player_life_array[i]) {
      int player_pin = player_pin_array[i];
      for(int j = 0; j < 3; j++) {
        digitalWrite(player_pin + j, LOW);
      }
    }
    if((!strcmp(role_array[i], "Citizen"))) {
      int player_pin = player_pin_array[i];
      for(int j = 0; j < 3; j++) {
        digitalWrite(player_pin + j, LOW);
      }
    }
  }
}

void allocate_role_randomly(char roles[12][10]) {
  char temp_roles[12][10] = {"Mafia", "Mafia", "Mafia", "Police", "Police", "Citizen", "Citizen", "Citizen", "Citizen", "Citizen", "Citizen", "Citizen"};
  
  for (int i = 0; i < 12; i++) {
    int randIndex = random(i, 12);
    char temp[10];
    strcpy(temp, temp_roles[i]);
    strcpy(temp_roles[i], temp_roles[randIndex]);
    strcpy(temp_roles[randIndex], temp);
  }
  
  for (int i = 0; i < 12; i++) {
    strcpy(roles[i], temp_roles[i]);
  }
}


void setColor(int redPin, int greenPin, int bluePin, int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  Serial.println(red);
  Serial.println(green);
  Serial.println(blue);
}

// redPin을 기준으로 greenPin, bluePin은 각각 i+1, i+2 임을 주의
void setColorRole(char role[10], int redPin) {
  Serial.print("setColor Func : ");
  Serial.println(role);
  if(!strcmp(role, "Mafia")) {
    setColor(redPin, redPin + 1, redPin + 2, 200, 0, 0);
    }
  else if(!strcmp(role, "Police")) {
    setColor(redPin, redPin + 1, redPin + 2, 0 ,0 ,200);
    }
  else {
    setColor(redPin, redPin + 1, redPin + 2, 0, 200, 0);
    }
}

#define offsetLED 22
#define switchPin 5

void mafia_game_ready(char role_array[12][10]) {
  allocate_role_randomly(role_array);
  for(int i = 0; i < 12; i++) {
    Serial.print("The Player ");
    Serial.print(i+1);
    Serial.print(" : ");
    Serial.println(role_array[i]); 
  }
  for(int i = 0; i < 10; i++) {
    setColorRole(role_array[i], offsetLED + 3 * i);
  }
  setColorRole(role_array[10], 8);
  setColorRole(role_array[11], 11);
}

int kill_vote_day(bool player_life_array[12]) {
  // 살아있는 플레이어 수와 인덱스를 저장하기 위한 배열
  int alive_players[12];
  int alive_count = 0;

  // 살아있는 플레이어를 찾아서 배열에 추가
  for (int i = 0; i < 12; i++) {
    if (player_life_array[i]) {
      alive_players[alive_count++] = i;
    }
  }

  // 살아있는 플레이어 중 랜덤으로 한 명을 선택
  int random_index = random(alive_count);

  // 선택된 플레이어의 인덱스를 반환
  return alive_players[random_index];
}

int killed_by_mafia(char role_array[12][10], bool player_life_array[12]) {
  // 살아있고 마피아가 아닌 플레이어를 찾아서 배열에 추가
  int alive_citizens[12];
  int alive_count = 0;
  
  for (int i = 0; i < 12; i++) {
    if (player_life_array[i] && strcmp(role_array[i], "Mafia") != 0) {
      alive_citizens[alive_count++] = i;
    }
  } 

  // 살아있는 시민 중 랜덤으로 한 명을 선택
  int random_index = random(alive_count);

  // 선택된 시민의 인덱스를 반환
  return alive_citizens[random_index];
}

int police_check_mafia(char role_array[12][10], bool player_life_array[12]) {
  // 살아있고 마피아가 아닌 플레이어를 찾아서 배열에 추가
  int alive_citizens[12];
  int alive_count = 0;
  
  for (int i = 0; i < 12; i++) {
    if (player_life_array[i] && strcmp(role_array[i], "Police") != 0) {
      alive_citizens[alive_count++] = i;
    }
  } 

  // 살아있는 경찰제외 사람 중 랜덤으로 한 명을 선택
  int random_index = random(alive_count);

  // 선택된 사람의 인덱스를 반환
  return alive_citizens[random_index];
}


int count_mafia(char role_array[12][10], bool player_life_array[12]) {
  int mafia_count = 0;
  for(int i = 0; i < 12; i++) {
    if(player_life_array[i] && !strcmp(role_array[i], "Mafia")) {
      mafia_count++;
    }
  }

  return mafia_count;
}


int count_police(char role_array[12][10], bool player_life_array[12]) {
  int police_count = 0;
  for(int i = 0; i < 12; i++) {
    if(player_life_array[i] && !strcmp(role_array[i], "Police")) {
      police_count++;
    }
  }
  
  return police_count;
}

int count_alive(bool player_life_array[12]) {
  int alive_player = 0;
  for(int i = 0; i < 12; i++) {
    if(player_life_array[i]) {
      alive_player++;
    }
  }

  return alive_player;
}



void setup() {
  char role_array[12][10];
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);
  randomSeed(analogRead(0));
  
  for (int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 22; i <= 51; i++) {
    pinMode(i, OUTPUT);
  }
}


void loop() { 
  int game_start_flag = 1;
  while(game_start_flag) {
    char role_array[12][10];
    mafia_game_ready(role_array);
    int day_count = 1;
    int mafia_count;
    int police_count;
    int killed_player_index;
    int die_player1 = 0;
    int die_player2 = 0;
    int isFindMafia = 0;
    int control_lcd = 0;
    int checked_player_index;
    int died_player[2];
    bool player_life_array[12] = {true, true, true, true, true, true, true, true, true, true, true, true};
    int player_pin_array[12] = {22, 25, 28, 31, 34, 37, 40, 43, 46, 49, 8, 11};
    ///////////////
    // First Day //
    ///////////////
    
    // 우선 Slave들에게 필요한 값을 보냄.
    // Serial1.write((byte*)&day_count, sizeof(day_count));
    // Serial1.write((byte*)&die_player1, sizeof(die_player1));
    // Serial1.write((byte*)&die_player2, sizeof(die_player2));
    // Serial1.write((byte*)&isFindMafia, sizeof(isFindMafia));
    // Serial1.write((byte*)&control_lcd, sizeof(control_lcd));
    // Serial2.write((byte*)&day_count, sizeof(day_count));
    Serial1.println(day_count);
    Serial1.println(die_player1);
    Serial1.println(die_player2);
    Serial1.println(isFindMafia);
    Serial1.println(control_lcd);
    Serial2.println(day_count);
    //보내질 떄까지 기다림
    delay(100);


    //낮시간 총 10초
    delay(9900);

    // 투표로 플레이어 한 명 랜덤으로 죽임
    killed_player_index = kill_vote_day(player_life_array);
    player_life_array[killed_player_index] = false;
    die_player1 = killed_player_index + 1;
    
    /////////////////
    // First Night //
    /////////////////
    day_count++; // day_count -> 2

    // 우선 Slave들에게 필요한 값을 보냄.
    Serial1.println(day_count);
    Serial1.println(die_player1);
    Serial1.println(die_player2);
    Serial1.println(isFindMafia);
    Serial1.println(control_lcd);
    Serial2.println(day_count);
    night_LED(role_array, player_life_array, player_pin_array);

    delay(7000); // 밤 7초
    mafia_count = count_mafia(role_array, player_life_array);
    if(mafia_count == 3) {mafia_count--;}
    for(int i = 0; i < mafia_count; i++) {
      killed_player_index = killed_by_mafia(role_array, player_life_array);
      died_player[i] = killed_player_index + 1;
      player_life_array[killed_player_index] = false;
    }
    die_player1 = died_player[0];
    die_player2 = died_player[1];

    police_count = count_police(role_array, player_life_array);
    if(police_count > 0) {
      checked_player_index = police_check_mafia(role_array, player_life_array);
      if(!strcmp(role_array[checked_player_index], "Mafia")) {
        isFindMafia = 1;
      }
    }

    ////////////////
    // Second Day //
    ////////////////
    day_count++; // day_count -> 3
    day_LED(role_array, player_life_array, player_pin_array);

    Serial1.println(day_count);
    Serial1.println(die_player1);
    Serial1.println(die_player2);
    Serial1.println(isFindMafia);
    Serial1.println(control_lcd);
    Serial2.println(day_count);

    delay(9990);

    // LCD에 Player n, m is killed
    //       by Mafia! 3초 출력
    // 경찰이 마피아 찾았으면 LCD에 Turns out Player m
    //                             is the Mafia!  3초출력
    //                             The Second Day.
    //                             Player n dies by vote   4초출력
    // 못 찾았으면 And 
    //   출력

    

    if(isFindMafia == 1) {
      player_life_array[checked_player_index] = false;
      die_player1 = checked_player_index + 1;
      isFindMafia = 0;
    }
    else {
      killed_player_index = kill_vote_day(player_life_array);
      player_life_array[killed_player_index] = false;
      die_player1 = killed_player_index + 1;
    }

  
  
    //////////////////
    // Second Night //
    //////////////////
    day_count++; // day_count -> 4
    // 우선 Slave들에게 필요한 값을 보냄.
    Serial1.println(day_count);
    Serial1.println(die_player1);
    Serial1.println(die_player2);
    Serial1.println(isFindMafia);
    Serial1.println(control_lcd);
    Serial2.println(day_count);
    night_LED(role_array, player_life_array, player_pin_array);
    
    delay(7000); // 밤 7초
    mafia_count = count_mafia(role_array, player_life_array);
    if(mafia_count == 3) {mafia_count--;}
    for(int i = 0; i < mafia_count; i++) {
      killed_player_index = killed_by_mafia(role_array, player_life_array);
      died_player[i] = killed_player_index + 1;
      player_life_array[killed_player_index] = false;
    }
    die_player1 = died_player[0];
    die_player2 = died_player[1];

    police_count = count_police(role_array, player_life_array);
    if(police_count > 0) {
      checked_player_index = police_check_mafia(role_array, player_life_array);
      if(!strcmp(role_array[checked_player_index], "Mafia")) {
        isFindMafia = 1;
      }
    }

    
    //////////////
    // Last Day //
    //////////////
    day_count++; // day_count -> 5
    day_LED(role_array, player_life_array, player_pin_array);

    Serial1.println(day_count);
    Serial1.println(die_player1);
    Serial1.println(die_player2);
    Serial1.println(isFindMafia);
    Serial1.println(control_lcd);
    Serial2.println(day_count);

    delay(9990);
    
    if(isFindMafia == 1) {
      player_life_array[checked_player_index] = false;
      die_player1 = checked_player_index + 1;
      isFindMafia = 0;
    }
    else {
      killed_player_index = kill_vote_day(player_life_array);
      player_life_array[killed_player_index] = false;
      die_player1 = killed_player_index + 1;
    }
    day_LED(role_array, player_life_array, player_pin_array);

    mafia_count = count_mafia(role_array, player_life_array);
    int alive_count = count_alive(player_life_array);
    int citizen_count = alive_count - mafia_count;
    
    if(mafia_count * 2 >= citizen_count) {
      control_lcd = 1;
    }
    else {
      control_lcd = 0;
    }
    day_count++; // -> 6
    
    Serial1.println(day_count);
    Serial1.println(die_player1);
    Serial1.println(die_player2);
    Serial1.println(isFindMafia);
    Serial1.println(control_lcd);
    Serial2.println(day_count);
    

    

    

    delay(10000);
    

  }
  
}