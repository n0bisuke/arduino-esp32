#include "NefryEddystone.h"

NefryEddystone nefryBeacon;
/** NefryEddystoneUrlSimple
 * 
 * 2017/10/27 wami
 * NefryBTにてEddystone URLのパケットを配信します。
 * URLを設定することで発信できます。
 */
void setup() {   
   if( !nefryBeacon.begin("http://google.com")){//begin(url);
      Serial.println("NefryBeacon Error");
   }
}

void loop() {

}
