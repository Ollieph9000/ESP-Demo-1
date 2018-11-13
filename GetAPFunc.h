#ifndef GETAPFUNC_H
#define GETAPFUNC_H

#include "ESP8266WiFi.h"

 const byte numChars = 32;
 extern char receivedChars[numChars]; // an array to store the received data
 extern boolean newData;
  
void GetAP();
void recvWithEndMarker();
void showNewData();

#endif
