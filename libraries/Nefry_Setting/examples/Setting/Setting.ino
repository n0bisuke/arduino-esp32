#include<NefrySetting.h>
void setting(){
  Serial.begin(115200);
  Serial.println();
  Serial.println("***************");
  Serial.println("TestSetting");
  Serial.println("***************");
}
NefrySetting nefrySetting(setting);
void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
