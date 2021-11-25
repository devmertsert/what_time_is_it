/*
  Function descriptions:

    int editTime(int hour, int minute):
      this function, if minute is less than 10 then add 0 and return the minute with (0 + minute) e.g.
        editTime(2, 1) = 201
        editTime(3, 14) = 314
        editTime(12, 7) = 1207
        editTime(10, 12) = 1012

    void wrNum(int number):
      this function, parsing the number and add to a array e.g.
        1527:
          arr[0] = 1
          arr[1] = 5
          arr[2] = 2
          arr[3] = 7

      and for the numbers of arr, turns on the leds one by one   
*/
#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(A2, A1, A0);

byte digits[] = {B00000001, B00000010, B00000100, B00001000};
byte numbers[]  = {B10000000, B11110010, B01001000, B01100000, B00110010, B00100100, B00000100, B11110000, B00000000, B00100000};

void setup() {
  DDRD = B11111110;
  DDRB = B00001111;
}

void loop() {
  myRTC.updateTime();
  wrNum(editTime((int)myRTC.hours, (int)myRTC.minutes));
}

int editTime(int hour, int minute) {
  String rHour = "";
  String strHour = "";
  String strMin = "";

  strHour = (String)hour;
  if(minute < 10) {
    strMin = '0' + (String)minute;
  }
  else {
    strMin = (String)minute;
  }
  rHour = strHour + strMin;
  return (rHour.toInt());
}

void wrNum(int number) {
  int steps[] = {-1, -1, -1, -1};
  int i = 3;
  while(number > 0) {
    steps[i] = number % 10;
    i--;
    number /= 10;
  }
  
  for(int j = 0; j < 4; j++) {
    if(steps[j] != -1) {
      PORTB = digits[j];
      PORTD = numbers[steps[j]];
      delay(5);
    }
    else {
      PORTB = B00000000;
      delay(5);
    }
  }
}
