#include <Nefry.h>
#include <NefryDisplay.h>

/** easyDisplayDialog
 * 2017/10/9 wami
 * 
 * NefryBTのディスプレイで簡単な表示ができる関数になります
 * 3行表示され、それ以上表示する場合スクロールされます
 */

void setup() {
  //ディスプレイに表示します
  NefryDisplay.print("Hello World!");
  NefryDisplay.print("Welcome to Nefry!");
}
int i = 0;
void loop() {
  //5秒に一度、「Nefry Test long long : 1」などと表示します
  NefryDisplay.print("Nefry Test long long : " + (String)i);
  i++;
  delay(5000);//5秒待つ
}
