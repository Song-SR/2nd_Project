#include <SoftwareSerial.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>   // 네오픽셀 라이브러리를 불러옵니다.
#define LEDPIN 10                      // 디지털핀 어디에 연결했는지 입력
#define LEDNUM 60                  // 연결된 네오픽셀의 숫자입력
#define BRIGHTNESS 50               // 네오픽셀의 밝기를 설정합니다. (0~255)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, LEDPIN, NEO_GRBW + NEO_KHZ800);
#include <OneWire.h> // library(라이브러리) 추가
const int Temp_SensingPin = 7; //Temperature Sensing Pin : 7(Digital I/O)
OneWire ds(Temp_SensingPin);   //Basic library - ds(7)
Servo sv;
int trig = 6;
int echo = 5;


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
// WiFi 접속 실패 여부
boolean FAIL_8266 = false;

// TX, RX
SoftwareSerial esp(3, 2);

void setup() {
  pinMode(8, OUTPUT);
  sv.attach(9);
  sv.write(179);
  strip.begin();
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(8,OUTPUT);
  
  Serial.println("Start module connection");
  do {
    Serial.begin(9600);
    esp.begin(9600);
    // ESP8266 모듈 재시작
    esp.println("AT+RST");
    delay(1000);
    // 만약 재시작되었다면
    if (esp.find("ready")) {
      Serial.println("Module ready");
      // ESP8266 모듈의 모드를 듀얼모드로 설정 (클라이언트)
      esp.println("AT+CWMODE=1");
      delay(2000);
      // AP에 접속되면
      if (cwJoinAP()) {
        Serial.println("AP successful");
        FAIL_8266 = false;
        delay(5000);
        Serial.println("Start buffer initialization");
        while (esp.available() > 0) {
          char a = esp.read();
          Serial.write(a);
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
String ledcolor = "";


void loop() {
  int waterlevel = analogRead(A4);
  int fp = analogRead(A5);
  float wtemp = getTemp();
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH); //초음파를 받아오는 시간
  float distance = (duration / 2) / 29.1; // /2는 왕복거리 / 1cm 이동시간 29m/s

  
  message = "";
  if (a) {
    message += "sc=";  // SerialCode
    message += 1;
    message += "&wl=";  // waterlevel
    message += waterlevel;
    message += "&tp=";  // 조도센서 -> 나중에 수온
    message += wtemp;
    message += "&fp=";  // feedpressure
    message += distance;
//    message += "&lc=";  // ledcolor
//    message += ledcolor;
    sendDataToServer(message);
  }
  delay(3000);

}


void sendDataToServer(String data) {
  Serial.println("Start the data transfer part");
  cmd = "AT+CIPSTART=\"TCP\",\"" + SERVER_IP + "\"," + SERVER_PORT + "\r\n";
  Serial.println("Attempt to connect to server");
  esp.println(cmd);
  // 웹 서버에 접속되면
  if (esp.find("OK")) {
    Serial.println("Server connection successful");
  } else {
    Serial.println("Server connection failed");
  }

  // 서버로 GET 메시지 전송
  cmd = "GET /fishngreen7/wifi?";
  cmd += data;
  cmd += "\r\nConnection: close\r\n\r\n";

  Serial.println(cmd);
  esp.print("AT+CIPSEND=");
  esp.println(cmd.length());
  if (esp.find("OK")) {
    Serial.println("Ready to send to server");
  } else {
    Serial.println("Failed to prepare to send to server");
  }
  esp.println(cmd);

  //데이터 전송이 완료되면
  if (esp.find("OK")) {
    Serial.println("Data transfer successful");
    Serial.println();
    delay(3000);
    Serial.println("Attempt to receive data");
    boolean check = false;
    readData = "";
    while (esp.available()) {
      char c = esp.read();
      //      Serial.write(c);
      if (c == '/') {
        check = !check;
      } else if (check) {
        readData += c;
      }
    }
    Serial.println(readData);  // 읽은 데이터 확인용(차후 삭제예정)
    Serial.println("End Receiving Data");

    delay(3000);
    char a = readData[0];  // 모터 on, off
    char b = readData[1];  // heat
    char c = readData[2];  // color1
    char d = readData[3];  // color2
    ledcolor = "";
    ledcolor += c;
    ledcolor += d;
    Serial.println("먹이공급 : " + (String)a);
    Serial.println("발열패드 : " + (String)b);
    Serial.println("color : " + (String)ledcolor);
    delay(1000);
    


    if (a == '1') {
      sv.write(0);
      delay(200);
      sv.write(179);
    } else {
      sv.write(179);
    }

    if (b == '1') {
      digitalWrite(8, 0);
    } else {
      digitalWrite(8, 1);
    }

    strip.begin();

    if(ledcolor == "00"){
      strip.clear();
    }else if (ledcolor == "01"){
      red();
    }else if(ledcolor == "02"){
      tomato();
    }else if(ledcolor == "03"){
      orange();
    }else if(ledcolor == "04"){
      yellow();
    }else if(ledcolor == "05"){
      green();
    }else if(ledcolor == "06"){
      blue();
    }else if(ledcolor == "07"){
      aqua();
    }else if(ledcolor == "08"){
      pink();
    }else if(ledcolor == "09"){
      purple();
    }else if(ledcolor == "10"){
      whitepink();
    }else if(ledcolor == "11"){
      white();
    }else if(ledcolor == "12"){
      stand();
    }else if(ledcolor == "13"){
      rainbow();
    }else{   }
    strip.show();

  } else {
    Serial.println("Data transfer failed");
    sendDataToServer(data);
  }

  delay(1500);
}

boolean cwJoinAP() {
  String cmd = "AT+CWJAP=\"" + SSID + "\",\"" + PASSWORD + "\"";
  esp.println(cmd);
  if (esp.find("OK")) {
    return true;
  } else {
    return false;
  }
}


void red() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 232, 25, 1, 0); // red
  }
}

void tomato() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 142, 42, 9, 0); // tomato
  }
}

void orange() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 135, 63, 1, 10);
  }
}

void yellow() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 225, 228, 0, 0);  // yellow
  }
}

void green() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 28, 150, 31, 0); // green
  }
}

void blue() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 20, 60, 255, 0);  // blue
  }
}

void aqua() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 10, 200, 200, 0); // aqua
  }
}

void pink() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 243, 97, 122, 30);  // pink
  }
}

void purple() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 87, 21, 76, 0); // purple
  }
}

void whitepink() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 72, 46, 57, 0);  // WhitePink
  }
}

void white() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 235, 204, 132, 7); // White
  }
}

void stand() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 0, 0, 0, 255);  // stand(흔한 스탠드조명)
  }
}

void rainbow() {
  for (int i = 0; i < 60; i += 12) {
    strip.setPixelColor(0+i, 232, 25, 1, 0); // red
    strip.setPixelColor(1+i, 142, 42, 9, 0); // tomato
    strip.setPixelColor(2+i, 135, 63, 1, 10);  // orange
    strip.setPixelColor(3+i, 225, 228, 0, 0);  // yellow
    strip.setPixelColor(4+i, 28, 150, 31, 0); // green
    strip.setPixelColor(5+i, 20, 60, 255, 0);  // blue
    strip.setPixelColor(6+i, 10, 200, 200, 0); // aqua
    strip.setPixelColor(7+i, 243, 97, 122, 30);  // pink
    strip.setPixelColor(8+i, 87, 21, 76, 0); // purple
    strip.setPixelColor(9+i, 72, 46, 57, 0);  // WhitePink
    strip.setPixelColor(10+i, 235, 204, 132, 7); // White
    strip.setPixelColor(11+i, 0, 0, 0, 255);  // stand(흔한 스탠드조명)
  }
}

float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius
  byte data[12];
  byte addr[8];
  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }
  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }
  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end
  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad
  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];
  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum; //해당 값을 반환한다. - 즉 해당 값이 출력으로 나온다. 
}
