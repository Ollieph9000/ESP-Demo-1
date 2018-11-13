#include "GetAPFunc.h"

  char receivedChars[numChars]; // an array to store the received data
  boolean newData;
  
void recvWithEndMarker() {
  
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
 
//  if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false) {
  rc = Serial.read();

  if (rc != endMarker) {
    receivedChars[ndx] = rc;
    ndx++;
    if (ndx >= numChars) {
    ndx = numChars - 1;
    }
  }
 else {
   receivedChars[ndx] = '\0'; // terminate the string
   ndx = 0;
    newData = true;
  }
 }
}
//}

void showNewData() {
  if (newData == true) {
    Serial.print("This just in ... ");
    Serial.println(receivedChars);
    newData = false;
 }
}
