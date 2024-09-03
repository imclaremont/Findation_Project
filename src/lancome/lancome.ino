#include <LiquidCrystal.h>
// 핀 위치 세팅 및 필요 함수 불러오기
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 9 
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LCD 라이브러리 불러오기

// 주파수 값 초기화
int g_redFrequency = 0;
int g_greenFrequency = 0;
int g_blueFrequency = 0;
// 색깔 값 초기화
int g_redColor = 0;
int g_greenColor = 0;
int g_blueColor = 0;
// 스위치 버튼 핀;
int g_button_pin = 10;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // 색깔센서 핀 설정
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // 스위치 핀 설정
  pinMode(g_button_pin,INPUT_PULLUP);

  // 색깔센서 센서 출력값 받음
  pinMode(sensorOut, INPUT);
  
  // 주파수값 세팅
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // 시리얼 모니터랑 lcd 초기 설정
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
 }

void loop() {
  while(digitalRead(g_button_pin) == LOW) {      
    lcd.setCursor(0, 0); // lcd표시 위치 세팅

    // 빨간색 값을 읽을 수 있게 설정
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);

    // 빨간색 주파수값 
    g_redFrequency = pulseIn(sensorOut, LOW);
    // 빨간색 값 0~255로 맵핑
    g_redColor = map(g_redFrequency, 23, 343, 255, 0);
  
    // 빨간색값을 받음
    Serial.print("R = ");
    Serial.print(g_redColor);
    delay(100);


    // 녹색값 읽을 수 있게 설정
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);

    // 녹색 주파수값
    g_greenFrequency = pulseIn(sensorOut, LOW);
    // 녹색값 0~255로 맵핑
    g_greenColor = map(g_greenFrequency, 35, 371, 255, 0);

    // 녹색값을 받음 
    Serial.print("G = ");
    Serial.print(g_greenColor);
    delay(100);
  

    // 파랑색 값을 읽을 수 있게 설정
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);

    // 파랑색 주파수값 
    g_blueFrequency = pulseIn(sensorOut, LOW);
    // 파랑색값 0~255로 맵핑
    g_blueColor = map(g_blueFrequency, 12, 105, 255, 0);

    // 파랑색값을 받음
    Serial.print("B = ");
    Serial.println(g_blueColor);
    delay(100);



    // 판별식을 설정하고 입력값이 맞는 범위에 따라서 화장품 호수가 lcd에 나타나게 표시
    if((245 < g_redColor) && (220 < g_blueColor) && (230 < g_greenColor)) {
      lcd.println(" - Lancome 010 Beige Porcelaine - ");
    }
    else if((230 < g_redColor) && (210 < g_blueColor) && (220 < g_greenColor)) {
      lcd.println(" - Lancome 02 Lys Rose - ");
    } 
    else if((220 < g_redColor) && (200 < g_blueColor) && (210 < g_greenColor)) {
      lcd.println(" - Lancome 03 Beige Diaphane - ");
    } 
    else {
      lcd.println(" - Lancome 04 Beige Nature - ");
    }
    delay(3000);

    // lcd 초기화
    lcd.clear();
  }
} 