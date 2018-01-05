#include<NefryFireBase.h>
//NefryのConsoleから0から4までの値を送信するとそれぞれの機能が動作します
NefryFireBase firebase;
void setup() {
  firebase.begin("APPID.firebaseio.com");//FireBaseに接続するための設定をします。
  //firebase.begin("APPID.firebaseio.com", "AuthToken");//FireBaseに接続するための設定をします。認証情報追加
}
int i = 0;
void loop() {
  DataElement elem = DataElement();
  elem.setValue("sensor", i++);
  elem.setValue("NefryTest", 500 + i++);
  String s = Nefry.read();
  if (s.equals("0")) {
    firebase.send("Nefry", &elem);//FireBaseに新規キーを追加し、そこにデータを追加します
  } else if (s.equals("1")) {
    firebase.write("Nefry", &elem);//FireBaseのデータを書き込みます
  } else if (s.equals("2")) {
    firebase.update("Nefry", &elem);//FireBaseのデータを更新します
  } else if (s.equals("3")) {
    firebase.remove("Nefry");//FireBaseのデータを削除します
    //firebase.remove("Nefry/sensor");//FireBaseのデータを削除します
  } else if (s.equals("4")) {
    Serial.println( firebase.read("Nefry"));//FireBaseからデータを受信します
    //Serial.println( firebase.read("Nefry/NefryTest"));//FireBaseからデータを受信します
  }
}
