#include <Nefry.h>
#include <NefryDisplay.h>

/** scrollDialog
   2017/10/09 wami

   NefryBTについているディスプレイの制御をします。
   スクロール機能になります
*/

void fastDisplayPrint() {
  NefryDisplay.drawString(0, 0, "Fast Page");
  NefryDisplay.drawStringWithHScroll(0, 20, "Nefry BT Scroll Display Test    ", 10);
  NefryDisplay.drawString(0, 40, "SSID:");
  NefryDisplay.drawStringWithHScroll(40, 40, WiFi.SSID() + "     ",  10);
}
void secondDisplayPrint() {
  NefryDisplay.drawString(0, 0, "2nd Page");
  NefryDisplay.drawStringWithHScroll(0, 20, "Nefry BT Scroll Display Test    ", 10);
  NefryDisplay.drawString(0, 40, "Displayであそんでみよう!    ");//日本語は非対応
}

void setup() {
  delay(10000);
  NefryDisplay.setAutoScrollFlg(true);//自動スクロールを有効にします
}

void loop() {
  Serial.println("fastDisplayPrint");
  NefryDisplay.autoScrollFunc(fastDisplayPrint);//関数を指定します
  delay(10000);
  Serial.println("secondDisplayPrint");
  NefryDisplay.autoScrollFunc(secondDisplayPrint);
  delay(10000);
}
