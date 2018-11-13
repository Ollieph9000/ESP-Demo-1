#ifndef GETAP_H
#define GETAP_H

#include "ESP8266WiFi.h"

  const byte numChars = 32;
 extern char receivedChars[numChars]; // an array to store the received data
 extern boolean newData;
  
void ScanAP();
void recvWithEndMarker();
void showNewData();

#endif
