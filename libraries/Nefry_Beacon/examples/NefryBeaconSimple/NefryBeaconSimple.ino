#include "NefryBeacon.h"

uint8_t uuid[] ={0xFD, 0xA5, 0x06, 0x93, 0xA4, 0xE2, 0x4F, 0xB1, 0xAF, 0xCF, 0xC6, 0xEB, 0x07, 0x64, 0x78, 0x25};
NefryBeacon nefryBeacon;
/** NefryBeaconSimple
 * 
 * 2017/10/27 wami
 * NefryBTにてiBeacon互換のパケットを配信します。
 * UUIDを設定し、Major、Minorを設定することで発信できます。
 */
void setup() {   
   if( !nefryBeacon.begin(uuid,255,255)){//begin(UUID,major,minor);
      Serial.println("NefryBeacon Error");
   }
}

void loop() {

}
