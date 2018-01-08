#include <Nefry.h>
#include <NefryDisplay.h>
#include <NefrySetting.h>
void setting(){
  Nefry.disableDisplayStatus();
}
NefrySetting nefrySetting(setting);

void setup() {
  NefryDisplay.clear();
  NefryDisplay.display();
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}