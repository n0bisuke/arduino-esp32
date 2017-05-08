#include <Nefry.h>
//フルカラーLED　ランダムに色が変わります。
void setup() {
  Nefry.setProgramName("FullColorLED"); //プログラム名を管理することができます。
  randomSeed(analogRead(A0));
}
int red,green,blue;
void loop() {
  red=random(255);                      //random関数は0-255の数値をランダムに返します。
  green=random(255);
  blue=random(255);
  Nefry.setLed(red,green,blue);         //LEDがランダムに点灯します。
  delay(1000);                          //1秒待つ
}
