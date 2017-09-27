#include<NefryThingSpeak.h>
/**
 * ReadPrivate
 * ThingSpeakからプライベートデータを取得します
 */
void setup() {
  //初期設定
  NefryThingSpeak.begin();
  NefryThingSpeak.setReadAPIKey();
}

void loop() {
  //読み込みたいチャンネルを設定する
  float readValue = ThingSpeak.readFloatField(NefryThingSpeak.getChannelNumber(), 1, NefryThingSpeak.getReadAPIKey());
  //データを取得できた場合に表示する
  int resultCode = NefryThingSpeak.getLastReadStatus();
  if (resultCode == 200)
  { //正常データを取得できた場合に表示する
    Serial.print("Latest message is: ");
    Serial.println(readValue);
  }
  else
  { //データを取得できなかった場合に表示する
    Serial.print("Error reading message.  Status was: ");
    Serial.println(resultCode);
  }

  delay(30000);
}
