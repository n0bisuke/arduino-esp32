#include <AzureIoTHub.h>
#include <Nefry.h>
void setup() {
  Azure.begin(); //YourKey Example:"HostName=YourHost.azure-devices.net;DeviceId=YourDevice;SharedAccessKey=" ‚ðConfig‚Å“ü—Í‚µ‚Ü‚·
  Azure.setCallback(azureCallback);
}

void azureCallback(String s) {
  Serial.print("azure Message arrived [");
  Serial.print(s);
  Serial.println("] ");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Azure.connect();
    DataElement a = DataElement();
    a.setValue("EspAnalog", analogRead(A0));
    Azure.push(&a);
    Nefry.println("pushed");
    delay(2000);
  } else {
    Nefry.println("Not connected to the Internet");
    delay(250);
  }
}



