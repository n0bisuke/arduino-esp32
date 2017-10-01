#include <NefryThingSpeak.h>
/**
 * SimpleSend
 * 
 * ThingSpeak(https://thingspeak.com)に単体のデータを送信します。
 */

void setup() {
  //ThingSpeakの初期設定を行います。WriteKeyも設定します
  NefryThingSpeak.begin();
  NefryThingSpeak.setWriteAPIKey();
}

void loop() {
  // ThingSpeakにデータを送信します。
  // ThingSpeak.writeField( Field番号,データ);
  NefryThingSpeak.writeField(1, random(1000));//データを送信します
  delay(20000); // ThingSpeakには15秒間隔でデータを送信すること
}
