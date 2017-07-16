/**
 * Base　https://github.com/wamisnet/ConfigurableFirmata/tree/esp32-thing 
 * 
 * 上のGithubの開発をベースに作られています。
 * 現時点でポートは3030に固定されています。
 * 
 * 未対応：サーボ、アナログ出力
 * 
 * サンプルjavascript :http://jsdo.it/wamisnet/MYwH
 */

#include "NefryFirmata.h"
NefryFirmata nefryFirmata;

void setup(){
  nefryFirmata.begin();
}

void loop(){
  nefryFirmata.loop();
}

