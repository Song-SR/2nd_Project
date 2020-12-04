#include<LiquidCrystal.h> //lcd 헤더
//#include <SoftwareSerial.h>


// 모바일 HostSpot의 ID와 패스워드 (변경할 부분)
const String SSID = "KOOooOo";
const String PASSWORD = "12345678";
// 서버주소와 포트 (변경할 부분)
const String SERVER_IP = "192.168.137.1";
const String SERVER_PORT = "8081";

// AT 명령 저장
String cmd = "";
// 전송 데이터 저장
String sendData = "";
String watertemp = "";
String waterlevel = "";
String feed = "";
// WiFi 접속 실패 여부
boolean FAIL_8266 = false;
int lcd = 0;//변경 보낼 값.
// TX, RX
//SoftwareSerial esp(3, 2);
///////////////////////////버튼 변수
int adc_key_val [5] = {50, 200, 400, 600, 800};
int NUM_KEYS = 5; // 버튼 개수
int adc_key_in; // 데이터를 읽을 변수
// 중복 출력 방지를 위한 변수 세트
int key = -1;
int oldkey = -1;
//////////////////////////버튼 변수 끝

LiquidCrystal lcd1(7, 8, 9, 10, 11, 12); //LCD 윗줄용
LiquidCrystal lcd2(7, 8, 9, 10, 11, 12); //LCD 아랫줄용


///////////////////////lcd 메뉴 변경 변수
boolean dup = true;
int select = 0; //메뉴번호 임시저장
int choice = 0; //해당메뉴 진입
int list = 1; //메뉴번호
int temp = 0; 
int out = 0;
int check_info = 0; //받아온 값 비교 조건문용(수온,먹이,수위)


void setup() {
  lcd1.begin(16, 1); //lcd 윗줄
  lcd2.begin(16, 2); //lcd 아랫줄
  lcd1.setCursor(2, 0);
  lcd1.print("Loading...");//첫 보이는 메뉴
  lcd2.setCursor(2, 1);
  lcd2.print("Please wait..");//첫 보이는 메뉴
  Serial.println("Start module connection");
  do {
    Serial.begin(9600);
    Serial2.begin(9600);
    // ESP8266 모듈 재시작
    Serial2.println("AT+RST");
    delay(1000);
    // 만약 재시작되었다면
    if (Serial2.find("ready")) {
      Serial.println("Module ready");
      // ESP8266 모듈의 모드를 듀얼모드로 설정 (클라이언트)
      Serial2.println("AT+CWMODE=1");
      delay(2000);
      // AP에 접속되면
      if (cwJoinAP()) {
        Serial.println("AP successful");
        FAIL_8266 = false;
        delay(5000);
        Serial.println("Start buffer initialization");
        while (Serial2.available() > 0) {
          char b = Serial2.read();
          Serial.write(b);
        }
        Serial.println();
        Serial.println("Buffer initialization terminated");
      } else {
        Serial.println("AP connection failure");
        delay(500);
        FAIL_8266 = true;
      }
    } else {
      Serial.println("Module connection failure");
      delay(500);
      FAIL_8266 = true;
    }
  } while (FAIL_8266);
  Serial.println("Module connection complete");
}


boolean a = true;
String message = "";
String readData = "";

boolean cwJoinAP() {
  String cmd = "AT+CWJAP=\"" + SSID + "\",\"" + PASSWORD + "\"";
  Serial2.println(cmd);
  if (Serial2.find("OK")) {
    return true;
  } else {
    return false;
  }
}
void sendDataToServer(String data) {
  Serial.println("Start the data transfer part");
  cmd = "AT+CIPSTART=\"TCP\",\"" + SERVER_IP + "\"," + SERVER_PORT + "\r\n";
  Serial.println("Attempt to connect to server");
  Serial2.println(cmd);
  // 웹 서버에 접속되면
  while (Serial2.available()) {
    Serial.write(Serial2.read());
    Serial.print(".");
  }
  if (Serial2.find("OK")) {
    Serial.println("Server connection successful");
  } else {
    Serial.println("Server connection failed");
  }
  // 서버로 GET 메시지 전송
  cmd = "GET /fishngreen7/lcdwifi?sc=1&lcd=";
  cmd += data;
  cmd += "\r\nConnection: close\r\n\r\n";

  Serial.println(cmd);
  Serial2.print("AT+CIPSEND=");
  Serial2.println(cmd.length());
  if (Serial2.find("OK")) {
    Serial.println("Ready to send to server");
  } else {
    Serial.println("Failed to prepare to send to server");
  }
  Serial2.println(cmd);

  //데이터 전송이 완료되면
  if (Serial2.find("OK")) {
    Serial.println("Data transfer successful");
    Serial.println();
    delay(3000);
    Serial.println("Attempt to receive data");
    boolean check = false;
    readData = "";
    while (Serial2.available()) {
      char c = Serial2.read();
      //      Serial.write(c);
      if (c == '/') {
        check = !check;
      } else if (check) {
        readData += c;
      }

    }
    Serial.println(readData);  // 읽은 데이터 확인용(차후 삭제예정)

    Serial.println();
    Serial.println("End Receiving Data");
    char wf1 = readData[0];  // 수위10의자리
    char wf2 = readData[1];  // 수위1의자리
    char wt1 = readData[2];  // 수온10의자리
    char wt2 = readData[3];  // 수온1의자리
    char wt3 = readData[4];  // 수온소수점
    char wt4 = readData[5];  // 수온소수점첫째자리
    char wt5 = readData[6];  // 수온소수점둘째자리
    char fd = readData[7];  // 먹이여부
    waterlevel = ""; //수위 값
    waterlevel += wf1;
    waterlevel += wf2;

    watertemp = "";//수온 값
    watertemp += wt1;
    watertemp += wt2;
    watertemp += wt3;
    watertemp += wt4;
    watertemp += wt5;

    feed = "";
    feed += fd;

    Serial.println("수온 : " + watertemp + "º");
    Serial.println("수위 : " + waterlevel + "");
    if (feed.equals("0")) {
      Serial.println("먹이부족");
    }
    else if (feed.equals("1")) {
      Serial.println("먹이충분");
    }

    delay(1000);


  } else {
    Serial.println("Data transfer failed");
    sendDataToServer(data);
  }

  delay(1500);
}




///////////////////////////////각 메뉴 접근
void ChoiceList(void) {
  if (choice == 0) { //메인메뉴
    temp = Menu1(list); //메뉴의 엔터값 반환
  }
  else if (choice == 1) { //수온,수위
    //Serial.println("수온수위메뉴 진입");
    temp = WaterMenu(list);
  }
  else if (choice == 2) { //먹이
    //Serial.println("먹이 메뉴 진입");
    temp = FeedMenu(list);
  }
  else if (choice == 3) { //led 세팅
    //Serial.println("led 세팅 메뉴 진입");
    temp = LedMenu(list);
  }
  //////////////////////////////////////////////////////
  else if (choice == 11) { //수위 waterlevel
    Serial.print("수위진입");
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
    check_info = 1;
    lcd=1;
  }
  else if (choice == 12) { //수온 temper
    Serial.print("수온진입");
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
    check_info = 2;
    lcd=2;
  }
  else if (choice == 21) { //남은 먹이
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
    check_info = 3;
    lcd=3;
  }
  else if (choice == 22) { //먹이 주기
    Serial.print("먹이주기실행");
    lcd = 25;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
  }
  else if (choice == 31) { //red

    lcd = 11;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
  }
  else if (choice == 32) { //tomato
    lcd = 12;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
  }
  else if (choice == 33) { //orange
    lcd = 13;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
  }
  else if (choice == 34) { //yellow
    lcd = 14;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)

  }
  else if (choice == 35) { //green
    lcd = 15;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)

  }
  else if (choice == 36) { //blue
    lcd = 16;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)

  }
  else if (choice == 37) { //aqua
    lcd = 17;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
  }
  else if (choice == 38) { //pink
    lcd = 18;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
  }
  else if (choice == 39) { //purple
    lcd = 19;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
  }
  else if (choice == 40) { //WhitePink
    lcd = 20;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)

  }
  else if (choice == 41) { //white
    lcd = 21;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)

  }
  else if (choice == 42) { //sand
    lcd = 22;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
  }
  else if (choice == 43) { //rainbow
    lcd = 23;
    choice = 0;//초기화면으로 복귀(테스트용)
    out = 0;//초기화면으로 복귀(테스트용)
  }
  else if (choice == 44){ //끄기
    lcd = 24;
    choice = 0;
    out = 0;
  }

  else {

  }
  EnterList(out);
}
//////////////////////////////////////////////각 메뉴 값 버튼 눌렀을때 초이스 변환
void EnterList(int num) {
  //////////////////////메인 메뉴
  if (out == 1) //watercheck
  {
    choice = 1;
  }
  else if (out == 2) //feeding
  {
    choice = 2;
  }
  else if (out == 3) //led
  {
    choice = 3;
  }
  //////////////////////수위,수온
  else if (out == 11)
  {
    choice = 11;
  }
  else if (out == 12)
  {
    choice = 12;
  }
  //////////////////////  먹이
  else if (out == 21)
  {
    choice = 21;
  }
  else if (out == 22)
  {
    choice = 22;
  }
  //////////////////////led
  else if (out == 31)
  {
    choice = 31;
  }
  else if (out == 32)
  {
    choice = 32;
  }
  else if (out == 33)
  {
    choice = 33;
  }
  else if (out == 34)
  {
    choice = 34;
  }
  else if (out == 35)
  {
    choice = 35;
  }
  else if (out == 36)
  {
    choice = 36;
  }
  else if (out == 37)
  {
    choice = 37;
  }
  else if (out == 38)
  {
    choice = 38;
  }
  else if (out == 39)
  {
    choice = 39;
  }
  else if (out == 40)
  {
    choice = 40;
  }
  else if (out == 41)
  {
    choice = 41;
  }
  else if (out == 42)
  {
    choice = 42;
  }
  else if (out == 43)
  {
    choice = 43;
  }
  else if (out == 44)
  {
    choice = 44;
  }
  else if (out == 45)
  {
    choice = 45;
  }
  ///////////////////메인메뉴로
  else if (out == 99)
  {
    choice = 0;
  }


}





void BTN(int limit) {

  int enter = 0;
  adc_key_in = analogRead(0); // 버튼 데이터
  key = get_key(adc_key_in);  // 어떤 버튼이 클릭되었는지 찾음

  if (key != oldkey) {   // 눌러진 버튼확인,
    delay(50);  // 채터링을 방지하기 위해 잠시 기다림
    oldkey = key;
    if (key != -1) { // 버튼 누른 상태가 종료되면 -1을 출력하기 때문에 -1이 아닐 때만 출력함
      Serial.print("버튼 ");
      switch (key) {
        case 0:
          Serial.print("왼쪽(초기(메인)화면)");
          choice = 0;
          temp = 99;
          out = 99;
          list = 1;
          break;
        case 1:
          Serial.print("위(상단)");
          list--;
          ListLimit(limit);
          break;
        case 2:
          Serial.print("아래(하단)");
          list++;
          ListLimit(limit);
          break;
        case 3:
          Serial.print("오른(선택)");
          out = temp;
          list = 1;
          break;
        case 4:
          Serial.print("단독(정보 업데이트)");
          choice = 0;
          temp = 99;
          out = 99;
          lcd=10;
          list = 1;
          break;
      }
      Serial.println();
    }
  }

  delay(100);

}
int get_key(unsigned int input) {
  int k;
  for (k = 0; k < NUM_KEYS; k++) {
    if (input < adc_key_val[k]) {
      return k;
    }
  }
  if (k >= NUM_KEYS)k = -1; // 만약 유효한 버튼이 클릭되지 않았다면 -1 출력
  return k;
}
void ListLimit(int num) {
  if (list < 1)
  {
    list = num;
  }
  else if (list > num)
  {
    list = 1;
  }
}
int Menu1(int num) { //메인메뉴
  BTN(3);
  int main_select = 0;
  switch (num) {
    case 1:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">1:WaterCheck");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 2:feeding");
      main_select = 1;

      break;

    case 2:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">2:feeding");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 3:LED_Setting");
      main_select = 2;

      break;

    case 3:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">3:LED_Setting");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 1:WaterLevel");
      main_select = 3;

      break;
  }
  return main_select;
}
int WaterMenu(int num) { //수위수온 메뉴
  int waterlist = 1;
  BTN(3);
  switch (num) {
    case 1:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">1:WaterLevel");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 2:Water_temp.");
      waterlist = 11;
      break;

    case 2:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">2:Water_temp.");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 3:Back");
      waterlist = 12;
      break;

    case 3:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">3:Back");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 1.WaterLevel");
      waterlist = 99;
      break;

  }
  return waterlist;
}
int FeedMenu(int num) { //먹이메뉴
  int feedlist = 1;
  BTN(3);
  switch (num) {
    case 1:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">1:Feed_Remain");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 2:Feeding");
      feedlist = 21;
      break;

    case 2:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">2:Feeding");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 3:Back");
      feedlist = 22;
      break;

    case 3:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">3:Back");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 1.Feed_Remain");
      feedlist = 99;

      break;

  }
  return feedlist;
}


int LedMenu(int num) { //Led메뉴
  int ledlist = 1;
  BTN(15);
  switch (num) {
    case 1:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">1:Red");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 2:Tomato");
      ledlist = 31;
      break;

    case 2:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">2:Tomato");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 3:Orange");
      ledlist = 32;
      break;

    case 3:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">3:Orange");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 4.Yellow");
      ledlist = 33;

      break;
    case 4:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">4:Yellow");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 5:Green");
      ledlist = 34;
      break;

    case 5:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">5:Green");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 6:Blue");
      ledlist = 35;
      break;

    case 6:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">6:Blue");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 7.Aqua");
      ledlist = 36;
      break;
    case 7:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">7:Aqua");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 8:Pink");
      ledlist = 37;
      break;

    case 8:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">8:Pink");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 9:PurPle");
      ledlist = 38;
      break;

    case 9:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">9:PurPle");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 10.WhitePink");
      ledlist = 39;

      break;

    case 10:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">10:WhitePink");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 11:White");
      ledlist = 40;
      break;

    case 11:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">11:White");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 12:Sand");
      ledlist = 41;
      break;

    case 12:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">12:Sand");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 13.Rainbow");
      ledlist = 42;
      break;

    case 13:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">13:Rainbow");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 14.LED OFF");
      ledlist = 43;

      break;
    case 14:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">14:LED OFF");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 15.Back");
      ledlist = 44;

      break;
    case 15:
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print(">15:Back");
      lcd2.setCursor(0, 1); //lcd 밑줄 시작점
      lcd2.print(" 1.Red");
      ledlist = 99;

      break;          
  }
  return ledlist;
}

void Result_List(void){
    if(check_info == 1){//waterlevel
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print("-Water level-");
      lcd2.setCursor(12, 1); //lcd 밑줄 시작점
      lcd2.print(waterlevel+"cm");
      delay(4000);
    }
    else if(check_info == 2){//watertemp
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print("-Water temp-");
      lcd2.setCursor(8, 1); //lcd 밑줄 시작점
      lcd2.print(watertemp+" C");      
      delay(4000);
    }
    else if(check_info == 3){//feed
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print("Feed Remaining");
      lcd2.setCursor(9, 1); //lcd 밑줄 시작점
      if(feed.equals("0")){
        lcd2.print("LOW");  
      }
      else if(feed.equals("1")){
        lcd2.print("FINE");
      }
      delay(4000);        
    }
    else{
      lcd1.clear();
      lcd2.clear();
      lcd1.setCursor(0, 0); //lcd 윗줄 시작점
      lcd1.print("");
      lcd2.setCursor(8, 1); //lcd 밑줄 시작점
      lcd2.print("Confirm!");      
      delay(4000);      
    }
  
}

void loop() {
  message = "";
  if (lcd == 0) {
    ChoiceList();
  }
  else if(lcd == 1 || lcd == 2 || lcd == 3){
    Result_List();
    lcd = 0;
    check_info = 0;
  }
  else if(lcd == 10){
    Serial.println("lcd값 : " + lcd);
    lcd1.clear();
    lcd2.clear();
    lcd1.setCursor(2, 0); //lcd 윗줄 시작점
    lcd1.print("Updating..");
    lcd2.setCursor(2, 1); //lcd 밑줄 시작점
    lcd2.print("Please wait..");  
    message += lcd;
    
    sendDataToServer(message);
    delay(1000);
    lcd = 0;
    check_info = 0;    
  }
  else {
    Serial.println("lcd값 : " + lcd);
    lcd1.clear();
    lcd2.clear();
    lcd1.setCursor(2, 0); //lcd 윗줄 시작점
    lcd1.print("Checking..");
    lcd2.setCursor(2, 1); //lcd 밑줄 시작점
    lcd2.print("Please wait..");
    
    message += lcd;
    
    sendDataToServer(message);
    delay(1000);
    lcd = 0;
    check_info = 0;
  }


}
