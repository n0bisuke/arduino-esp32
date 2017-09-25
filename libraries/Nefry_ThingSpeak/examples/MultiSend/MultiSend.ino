#include <NefryThingSpeak.h>
/**
 * MultiSend
 * 
 * ThingSpeak(https://thingspeak.com)に複数のデータを送信します。
 */

void setup() {
  //ThingSpeakの初期設定を行います。WriteKeyも設定します
  NefryThingSpeak.begin();
  NefryThingSpeak.setWriteAPIKey();
}

void loop() {
  // ThingSpeakにデータを送信します。フィールドにそれぞれデータを代入します
  // ThingSpeak.setField( Field番号,データ);
  ThingSpeak.setField(1, random(1000));
  ThingSpeak.setField(2, random(1000));
  NefryThingSpeak.writeFields();//データを送信します
  delay(20000); // ThingSpeakには15秒間隔でデータを送信すること
}
