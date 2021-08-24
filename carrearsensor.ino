#include <RgbLed.h>
#include "RgbLcd.h"
#include "Buzzer.h"
#include <UltraSonic.h>

#define BUZ_PIN 11

RgbLed myrgbled;
RgbLcd lcd;
Buzzer myBuzzer;
UltraSonic dUltra;

void setup() {
  myrgbled.begin(4, 5, 6);
  lcd.begin(62, 63, 64, 65, 66, 67, 45, 44, 43, 42, 16, 2);
  myBuzzer.begin(BUZ_PIN);
  dUltra.begin(75, 2);
  lcd.onBacklightGreen();
}

void loop() {
  int distance = 0;
  distance = dUltra.ReadDistanceCentimeter();//초음파 센서로 차량 후방 거리를 받아 distance변수에 대입
  lcd.clear();//lcd 내용 제거
  lcd.print("distance : ");//lcd에 차량 후방 거리를 출력
  lcd.print(distance);
  lcd.print("Cm");
  if(distance <= 10) {//차량 후방 거리가 10cm이하일때
    myrgbled.OnRgb(255, 0, 0);//RGBLED RED출력
    lcd.onBacklightGreen(0);//setup에서 On한 lcdbacklightGreen을 꺼줌
    lcd.onBacklightRed();//차량 후방 거리가 짧을때 lcdbacklight를 RED로 출력
    lcd.setCursor(0, 1);
    lcd.print(" Warning!!!! ");
    myBuzzer.Off();//부저 Off
    myBuzzer.setFreq(1000);
    myBuzzer.On();
    delay(100);//차량 후방 거리가 매우 가까울때 딜레이를 100ms로 설정하여 급박한 상황을 부저로 출력
  }else if(distance > 10 && distance <= 20) {//차량 후방 거리가 10cm초과 20cm이하일때
    myrgbled.OnRgb(255, 255, 0);//Yellow 출력
    lcd.onBacklightRed();
    lcd.onBacklightGreen();//Red Green 두 색을 같이 On하여 Yellow 출력
    lcd.setCursor(0, 1);
    lcd.print(" Warning ");
    myBuzzer.Off();
    myBuzzer.setFreq(500);
    myBuzzer.On();
    delay(300);
  }else if(distance > 20) {
    myrgbled.OnRgb(0, 255, 0);
    lcd.onBacklightRed(0);
    lcd.onBacklightGreen();
    myBuzzer.Off();
    lcd.setCursor(0, 1);
    lcd.print(" Safe ");
    delay(500);
  }
}
