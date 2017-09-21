#include <NefryFastSensing.h>
//インスタンスを作成します
NefryFastSensing fastSensing;
float floatData = 0;
float intData = 0;

void setup() {
  //FastSensingで必要な情報を入力し、初期化をします
  //https://console.fastsensing.com/devicesからデバイスとチャンネル
  //begin(デバイス、チャンネル1、チャンネル2、チャンネル3)
  fastSensing.begin("device", "channel1", "channel2", "channel3");
}

void loop() {
  //FastSensingに送るデータを作成します
  //setValue(チャンネル、データ)
  fastSensing.setValue(0, floatData);
  fastSensing.setValue(1, intData);

  //setValueで入れた値をFastSensingに送信します
  //push()
  fastSensing.push();
  
  floatData += 0.1;
  intData++;
  delay(10000);

}
