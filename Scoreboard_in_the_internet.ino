#include <SevSeg1.h>
//Create an instance of the object.
SevSeg myDisplay;
SevSeg myDisplay1;
//Create global variables
unsigned long timer;
int too = 0;
int too1 = 0;
const int  buttonPin = 32;    // the pin that the pushbutton is attached to
//const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int digit1 = 10; //Pin 7 on my 2 digit display
int digit2 = 11; //Pin 8 on my 2 digit display
int digit3 = 0;
int digit4 = 0;
int segA = 3; //Pin 10 on my 2 digit display
int segB = 4; //Pin 9 on my 2 digit display
int segC = 5; //Pin 1 on my 2 digit display
int segD = 6; //Pin 4 on my 2 digit display
int segE = 7; //Pin 3 on my 2 digit display
int segF = 8; //Pin 6 on my 2 digit display
int segG = 9; //Pin 5 on my 2 digit display
int segDP = 0; //Pin 2 on my 2 digit display
int c_seg[7] = {
  A2, A3, A4, A5, A6, A7, A8
};
int seg[7] = {
  A15, A14, A13, A12, A11, A10, A9
};
int round_com = 29;
int c_dig[4] = {
  A0, A1, 0, 0
};

int tsag[4] = {
  21, 22, 24, 26
};
int start = 28;
int Stop = 30;
int numberOfDigits = 2; //Do you have a 1, 2 or 4 digit display?
int d = 0;
int error[5] = {
  44, 46, 48, 50, 52
};
int error1[5] = {
  34, 36, 38, 40, 42
};
int err = 0;
int err1 = 0;
int rst = 32;
void setup()
{
  Serial1.begin(9600);

  int displayType = COMMON_CATHODE; //Your display is either common cathode or common anode
  pinMode(start, OUTPUT);
  pinMode(Stop, OUTPUT);
  pinMode(rst, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(tsag[i], OUTPUT);
  }
  pinMode(round_com, OUTPUT);
  for (int i = 0; i < 7; i++) {
    pinMode(seg[i], OUTPUT);
  }

  for (int i = 0; i < 5; i++) {
    pinMode(error[i], OUTPUT);
  }

  for (int i = 0; i < 5; i++) {
    pinMode(error1[i], OUTPUT);
  }

  digitalWrite(rst, 0);

  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  myDisplay1.Begin(displayType, numberOfDigits, c_dig[0], c_dig[1], c_dig[2], c_dig[3], c_seg[0], c_seg[1], c_seg[2], c_seg[3], c_seg[4], c_seg[5], c_seg[6], 0);

  myDisplay.SetBrightness(255); //Set the display to 100% brightness level
  myDisplay1.SetBrightness(255); //Set the display to 100% brightness level

  timer = millis();
  Serial1.println("ON UART");

  err = 0; too = 0; too1 = 0; d = 0; err1 = 0;
  count(d);
  error_f(err);

  error_e(err1);
  
  char tempString[100]; //Used for sprintf
  sprintf(tempString, "%02d", too); //Convert deciSecond into a string that is right adjusted
  myDisplay.DisplayString(tempString, 0); //(numberToDisplay, decimal point location)
  //
  char tempString1[100]; //Used for sprintf
  sprintf(tempString1, "%02d", too1); //Convert deciSecond into a string that is right adjusted
  myDisplay1.DisplayString(tempString1, 0); //(numberToDisplay, decimal point location)

}

void loop()
{
  //    buttonState = digitalRead(buttonPin);

  //    // compare the buttonState to its previous state
  //    if (buttonState != lastButtonState) {
  //      // if the state has changed, increment the counter
  //      if (buttonState == 0) {
  //        // if the current state is HIGH then the button went from off to on:
  //        too1++;
  //        if(too1>=99){
  //          too1=99;
  //        }
  //    }
  //    }
  //    // save the current state as the last state, for next time through the loop
  //    lastButtonState = buttonState;


  digitalWrite(round_com, 1);
  if (Serial1.available() > 0) {
    int data = Serial1.parseInt();
    switch (data) {
      case 1:
        too1++;
        break;
      case 2:
        if (too1 <= 0)
        {
          too1 = 0;
        } else {
          too1--;
        }
        break;
      case 3:

        too++;
        break;
      case 4:
        if (too <= 0)
        {
          too = 0;
        } else {
          too--;
        }
        break;
      case 5:
        if (d > 9)
        {
          d = 9;
        } else {
          d++;
        }
        break;
      case 6:
        if (err >= 5)
        {
          err = 5;
        } else {
          err++;
        }
        break;
      case 7:
        if (err <= 0)
        {
          err = 0;
        } else {
          err--;
        }
        break;
      case 8:
        if (err1 >= 5)
        {
          err1 = 5;
        } else {
          err1++;
        }
        break;
      case 9:
        if (err1 <= 0)
        {
          err1 = 0;
        } else {
          err1--;
        }
        break;
      case 16:


        setup();
        break;
      case 17:
        digitalWrite(start, 1);
        delay(100);
        digitalWrite(start, 0);
        break;
      case 18:
        digitalWrite(Stop, 1);
        delay(100);
        digitalWrite(Stop, 0);
        break;
      case 19:
        digitalWrite(tsag[0], 1);
        delay(100);
        digitalWrite(tsag[0], 0);

        break;
      case 20:
        digitalWrite(tsag[1], 1);
        delay(100);
        digitalWrite(tsag[1], 0);

        break;
      case 21:
        digitalWrite(tsag[2], 1); delay(100);
        digitalWrite(tsag[2], 0);

        break;
      case 22:
        digitalWrite(tsag[3], 1);
        delay(100);
        digitalWrite(tsag[3], 0);
        break;
      case 23:
        digitalWrite(start, 1);
        digitalWrite(Stop, 1);
        delay(100);
        digitalWrite(start, 0);
        digitalWrite(Stop, 0);
        break;
    }

  }
  count(d);
  error_f(err);

  error_e(err1);
  
  char tempString[100];
  sprintf(tempString, "%02d", too); //Convert deciSecond into a string that is right adjusted
  myDisplay.DisplayString(tempString, 0); //(numberToDisplay, decimal point location)
  //
  char tempString1[100]; //Used for sprintf
  sprintf(tempString1, "%02d", too1); //Convert deciSecond into a string that is right adjusted
  myDisplay1.DisplayString(tempString1, 0); //(numberToDisplay, decimal point location)
//  Serial.print(tempString1);
//  Serial.print(" ");
//  Serial.println(tempString);

  //  if (millis() - timer >= 1000)
  //  {
  //    timer = millis();
  //    too++;
  //  }
  //  if ( too >= 100) too = 0;

}

void error_f(int a) {
  switch (a) {
    case 0:
      digitalWrite(error[0], 0);
      digitalWrite(error[1], 0);
      digitalWrite(error[2], 0);
      digitalWrite(error[3], 0);
      digitalWrite(error[4], 0);
      break;
    case 1:
      digitalWrite(error[0], 1);
      digitalWrite(error[1], 0);
      digitalWrite(error[2], 0);
      digitalWrite(error[3], 0);
      digitalWrite(error[4], 0);
      break;
    case 2:
      digitalWrite(error[0], 1);
      digitalWrite(error[1], 1);
      digitalWrite(error[2], 0);
      digitalWrite(error[3], 0);
      digitalWrite(error[4], 0);
      break;
    case 3:
      digitalWrite(error[0], 1);
      digitalWrite(error[1], 1);
      digitalWrite(error[2], 1);
      digitalWrite(error[3], 0);
      digitalWrite(error[4], 0);
      break;
    case 4:
      digitalWrite(error[0], 1);
      digitalWrite(error[1], 1);
      digitalWrite(error[2], 1);
      digitalWrite(error[3], 1);
      digitalWrite(error[4], 0);
      break;
    case 5:
      digitalWrite(error[0], 1);
      digitalWrite(error[1], 1);
      digitalWrite(error[2], 1);
      digitalWrite(error[3], 1);
      digitalWrite(error[4], 1);
      break;
  }

}
void error_e(int a) {
  switch (a) {
    case 0:
      digitalWrite(error1[0], 0);
      digitalWrite(error1[1], 0);
      digitalWrite(error1[2], 0);
      digitalWrite(error1[3], 0);
      digitalWrite(error1[4], 0);
      break;
    case 1:
      digitalWrite(error1[0], 1);
      digitalWrite(error1[1], 0);
      digitalWrite(error1[2], 0);
      digitalWrite(error1[3], 0);
      digitalWrite(error1[4], 0);
      break;
    case 2:
      digitalWrite(error1[0], 1);
      digitalWrite(error1[1], 1);
      digitalWrite(error1[2], 0);
      digitalWrite(error1[3], 0);
      digitalWrite(error1[4], 0);
      break;
    case 3:
      digitalWrite(error1[0], 1);
      digitalWrite(error1[1], 1);
      digitalWrite(error1[2], 1);
      digitalWrite(error1[3], 0);
      digitalWrite(error1[4], 0);
      break;
    case 4:
      digitalWrite(error1[0], 1);
      digitalWrite(error1[1], 1);
      digitalWrite(error1[2], 1);
      digitalWrite(error1[3], 1);
      digitalWrite(error1[4], 0);
      break;
    case 5:
      digitalWrite(error1[0], 1);
      digitalWrite(error1[1], 1);
      digitalWrite(error1[2], 1);
      digitalWrite(error1[3], 1);
      digitalWrite(error1[4], 1);
      break;
  }

}
void count(int too) {
  switch (too) {
    case 0:
      digitalWrite(seg[0], 1);
      digitalWrite(seg[1], 1);
      digitalWrite(seg[2], 1);
      digitalWrite(seg[3], 1);
      digitalWrite(seg[4], 1);
      digitalWrite(seg[5], 1);
      digitalWrite(seg[6], 0);
      break;
    case 1:
      digitalWrite(seg[0], 0);
      digitalWrite(seg[1], 1);
      digitalWrite(seg[2], 1);
      digitalWrite(seg[3], 0);
      digitalWrite(seg[4], 0);
      digitalWrite(seg[5], 0);
      digitalWrite(seg[6], 0);
      break;
    case 2:
      digitalWrite(seg[0], 1);
      digitalWrite(seg[1], 1);
      digitalWrite(seg[2], 0);
      digitalWrite(seg[3], 1);
      digitalWrite(seg[4], 1);
      digitalWrite(seg[5], 0);
      digitalWrite(seg[6], 1);
      break;
    case 3:
      digitalWrite(seg[0], 1);
      digitalWrite(seg[1], 1);
      digitalWrite(seg[2], 1);
      digitalWrite(seg[3], 1);
      digitalWrite(seg[4], 0);
      digitalWrite(seg[5], 0);
      digitalWrite(seg[6], 1);
      break;
    case 4:
      digitalWrite(seg[0], 0);
      digitalWrite(seg[1], 1);
      digitalWrite(seg[2], 1);
      digitalWrite(seg[3], 0);
      digitalWrite(seg[4], 0);
      digitalWrite(seg[5], 1);
      digitalWrite(seg[6], 1);
      break;
    case 5:
      digitalWrite(seg[0], 1);
      digitalWrite(seg[1], 0);
      digitalWrite(seg[2], 1);
      digitalWrite(seg[3], 1);
      digitalWrite(seg[4], 0);
      digitalWrite(seg[5], 1);
      digitalWrite(seg[6], 1);
      break;
    case 6:
      digitalWrite(seg[0], 1);
      digitalWrite(seg[1], 0);
      digitalWrite(seg[2], 1);
      digitalWrite(seg[3], 1);
      digitalWrite(seg[4], 1);
      digitalWrite(seg[5], 1);
      digitalWrite(seg[6], 1);
      break;
    case 7:
      digitalWrite(seg[0], 1);
      digitalWrite(seg[1], 1);
      digitalWrite(seg[2], 1);
      digitalWrite(seg[3], 0);
      digitalWrite(seg[4], 0);
      digitalWrite(seg[5], 0);
      digitalWrite(seg[6], 0);
      break;
    case 8:
      digitalWrite(seg[0], 1);
      digitalWrite(seg[1], 1);
      digitalWrite(seg[2], 1);
      digitalWrite(seg[3], 1);
      digitalWrite(seg[4], 1);
      digitalWrite(seg[5], 1);
      digitalWrite(seg[6], 1);
      break;
    case 9:
      digitalWrite(seg[0], 1);
      digitalWrite(seg[1], 1);
      digitalWrite(seg[2], 1);
      digitalWrite(seg[3], 1);
      digitalWrite(seg[4], 0);
      digitalWrite(seg[5], 1);
      digitalWrite(seg[6], 1);
      break;
  }
}


void count2digit(int too) {
  switch (too) {
    case 0:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
    case 10:
      digitalWrite(digit1, 0);
      digitalWrite(digit2, 1);
      one();
      delay(5);
      digitalWrite(digit1, 1);
      digitalWrite(digit2, 0);
      zero();
      delay(5);
      break;
    case 11:
      digitalWrite(digit1, 0);
      digitalWrite(digit2, 1);
      one();
      delay(5);
      digitalWrite(digit1, 1);
      digitalWrite(digit2, 0);
      one();
      delay(5);
      break;
    case 12:
      digitalWrite(digit1, 0);
      digitalWrite(digit2, 1);
      one();
      delay(5);
      digitalWrite(digit1, 1);
      digitalWrite(digit2, 0);
      two();
      delay(5);
      break;
    case 13:
      digitalWrite(digit1, 0);
      digitalWrite(digit2, 1);
      one();
      delay(5);
      digitalWrite(digit1, 1);
      digitalWrite(digit2, 0);
      three();
      delay(5);
      break;
    case 14:
      digitalWrite(digit1, 0);
      digitalWrite(digit2, 1);
      one();
      delay(5);
      digitalWrite(digit1, 1);
      digitalWrite(digit2, 0);
      four();
      delay(5);
      break;
  }
}
void zero() {
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 1);
  digitalWrite(segF, 1);
  digitalWrite(segG, 0);
}
void one() {
  digitalWrite(segA, 0);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 0);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 0);
}
void two() {
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 0);
  digitalWrite(segD, 1);
  digitalWrite(segE, 1);
  digitalWrite(segF, 0);
  digitalWrite(segG, 1);
}
void three() {
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 1);
}
void four() {
  digitalWrite(segA, 0);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 0);
  digitalWrite(segE, 0);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
}
void five() {
  digitalWrite(segA, 1);
  digitalWrite(segB, 0);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 0);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
}
void six() {
  digitalWrite(segA, 1);
  digitalWrite(segB, 0);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 1);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
}
void seven() {
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 0);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 0);
}
void eight() {
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 1);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
}
void nine() {
  digitalWrite(segA, 1);
  digitalWrite(segB, 1);
  digitalWrite(segC, 1);
  digitalWrite(segD, 1);
  digitalWrite(segE, 0);
  digitalWrite(segF, 1);
  digitalWrite(segG, 1);
}

