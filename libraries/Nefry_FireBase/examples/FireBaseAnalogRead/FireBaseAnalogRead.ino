#include<NefryFireBase.h>
//NefryからセンサーデータをFireBaseにアップロードします
NefryFireBase firebase;
void setup() {
  firebase.begin("APPID.firebaseio.com");//FireBaseに接続するための設定をします。
  //firebase.begin("APPID.firebaseio.com", "AuthToken");//FireBaseに接続するための設定をします。認証情報追加
}
int i = 0;
void loop() {
  DataElement elem = DataElement();
  elem.setValue("sensor", analogRead(A0));
  firebase.write("Nefry", &elem);//FireBaseのデータを書き込みます
  delay(1000);
}

