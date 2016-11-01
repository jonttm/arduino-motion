/*
  The Ultimate Alarm System!
  By JTTM (Jonathan Currier)
  Version 1.5 Beta 9 - Keypad Simplification

  Manual:
  Please note that the IR Remote is not supported in this version.
  Enter your code then press * for set new code or # for arm/disarm.
  Set Mode doesn't work while armed.
  When press * enter your new code then press * again to save it.
  When press # wait until you here tone for arm or disarm.
  During set mode press # to cancel set mode.
  Green LED means disarmed, Red means armed, Blue means set mode.
  
  Buttons:
  Type your own buttons here so you don't forgot them.
  [ 0-9 ] Keypad & Code Entry
  [ * ] Set Code & Confirm New Code
  [ # ] Arm/Disarm & Cancel Set Code

  Versions:
  1.5 - Keypad Simplification
  1.4 - Remote Control Revolution
  1.3 - The Remote Update
  1.2 - Customizable Settable Code!
  1.1 - Arming Button
  1.0 - Motion!

  Changelog:
  1.5_9 - Added a lot of explanitory text, not done yet.
  1.5_8 - Added most descriptions and newified manual.
  1.5_7 - Finished visual feedback, done with main development.
  1.5_6 - Started adding visual feedback through a new activity function.
  1.5_5 - Fixed all bugs and made fully working set code.
  1.5_4 - Corrected and finished basic set and enter code.
  1.5_3 - Added basic set and enter code functionality.
  1.5_2 - Added my current pin layout and some starting code.
  1.5_1 - Started working with arrays and keypad.

  Required:
  - Motion Sensor (Digital Input)
  - RGB LED (Define Common Anode Below)
  - Status LEDs (See Hardware Pins List)
  - Buzzer (Digital Output)
  - Speaker (Works with tone Library)
  - Breadboard (Recommended)
  - Arduino Uno (Obviously)
  - Lots of Wires (I use more than 20)
  - Some Resistor (LED's need them)
  - Keypad Arduino Library (Download)
  - Password Arduino Library (Same)

  Setup:
  Install the Keypad and Password Arduino Libraries.
  Plug in and setup all your hardware. You can use the analog pins with digital outputs.
  Make sure all your pins are correct below. Analog pins A0 through A5 are 14 through 19.
  Make sure your keypad pins and layout is correct! This is very important!
  Set your options below like default password and arming countdown.
  Upload your code and have fun! If anything doesn't work please report it on GitHub.
*/

//   All Hardware Pins         
//   int var = < pin - change this >; 

// Sound:
int beep = 19;      // Buzzer for Button Presses (Digital Output)
int alert = 9;      // Speaker for Alarm (tone Library)

// Input:
int motion = 14;    // Motion Sensor for Alarm (Digital Input)

// Status LEDs
int warn = 18;     // Error type things.
int error = 17;      // Warning type things.
int active = 16;    // Usually button press.
int power = 15;     // Simple power status.

// RGB LED
int red = 13;       // Red RGB Pin
int blue = 12;      // Blue RGB Pin
int green = 11;     // Green RGB Pin

//   Keypad Layout
//   Make Sure Everything is Correct!

// Rows and Coloums
const byte ROWS = 4;   //  Horizontal Rows
const byte COLS = 3;   //  Vertical Coloums

// Keypad Buttons
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// Keypad Pins:
byte rowPins[ROWS] = {8, 7, 6, 5};   //  Row Pins
byte colPins[COLS] = {4, 3, 2};   //  Coloum Pins

//   Arduino Libraries
//   Make Sure You Have These!
#include <Keypad.h>     //   Keypad Library
#include <Password.h>   //   Password Library

// Customizable Options
// Change Anything You Want Here!

// Your Default Password:
// Must be 4 Characters Exact
Password password = Password("1234");

// Arming Countdown:
// Must be Larger Than 0
int timer = 5;

// Common Anode RGB LED:
// Comment if You Have A Common Anode LED
#define COMMON_ANODE

//    DON'T CHANGE ANYTHING
//    Seriously, Don't Touch.
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // Make the Keypad.
bool setCode = false;  // Make all the main variables.
bool armed = false;    // These are bools (true or false).
bool alarm = false;
char code[5];          // This is a char array.
byte pressed;          // Normal intergers.
int count;

// Begin Setup:
void setup() {
  pinMode(beep, OUTPUT);      // Declare all the pins.
  pinMode(error, OUTPUT);
  pinMode(warn, OUTPUT);
  pinMode(active, OUTPUT);
  pinMode(power, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(alert, OUTPUT);
  pinMode(motion, INPUT);
  Serial.begin(9600);         // Begin Serial Connection.
  setColor(0, 255, 0);        // Some starting lights and noise.
  digitalWrite(power, HIGH);
  digitalWrite(beep, HIGH);
  delay(1000);
  digitalWrite(beep, LOW);
  keypad.addEventListener(keypadEvent);     // Wait for keypad input.
}

// Looping Code:
void loop() {
  if (armed == true) {        // If the system is armed.
    if (digitalRead(motion) == true) {      // Check if there is motion input.
      setMode("alarm");       // Trigger alarm.
    }
  }
  if (alarm == true) {        // If alarm is true, trigger alarm.
    setMode("alarm");
  }
  keypad.getKey();            // Get the keypad input key.
}

// Keypad Input:
void keypadEvent(KeypadEvent eKey) {
  if (setCode == true) {              // If set mode is true.
    if (armed == false) {             // Make sure the system is not armed.
      switch (keypad.getState()) {    // If keypad is pressed.
        case PRESSED:
          setMode("button");          // Trigger button sound.
          switch (eKey) {             // What key was pressed.
            case '*':                 // If * was pressed.
              setMode("setdone");     // Save the set code.
              break;                  
            case '#':                 // If # was pressed.
              setMode("stopset");     // Cancel set mode.
              break;
            default:                  // If any other key was pressed.
              code[pressed] = eKey;   // Append the currently pressed key to the set code.
              pressed++;              // One key has been pressed.

          }
      }
    }
    else {
      setMode("wrong");
    }
  }
  else {
    switch (keypad.getState()) {
      case PRESSED:
        setMode("button");
        switch (eKey) {
          case '*':
            setPassword();
            break;
          case '#':
            checkPassword();
            break;
          default:
            password.append(eKey);
        }
    }
  }
}

void setPassword() {
  if (password.evaluate()) {
    setMode("correct");
    setMode("setcode");
  }
  else {
    setMode("wrong");
  }
  password.reset();
}

void checkPassword() {
  if (password.evaluate()) {
    setMode("correct");
    if (armed == true) {
      setMode("disarm");
    }
    else {
      setMode("armed");
    }
  }
  else {
    setMode("wrong");
  }
  password.reset();
}

void setMode(String activity) {
  if (activity == "button") {
    digitalWrite(beep, HIGH);
    digitalWrite(active, HIGH);
    delay(100);
    digitalWrite(beep, LOW);
    digitalWrite(active, LOW);
  }
  if (activity == "correct") {
    Serial.println("Code Correct!");
    digitalWrite(beep, HIGH);
    digitalWrite(active, HIGH);
    delay(100);
    digitalWrite(beep, LOW);
    digitalWrite(active, LOW);
    delay(200);
    digitalWrite(beep, HIGH);
    digitalWrite(active, HIGH);
    delay(100);
    digitalWrite(beep, LOW);
    digitalWrite(active, LOW);
    delay(200);
    digitalWrite(beep, HIGH);
    digitalWrite(active, HIGH);
    delay(100);
    digitalWrite(beep, LOW);
    digitalWrite(active, LOW);
  }
  if (activity == "wrong") {
    Serial.println("Code Incorrect");
    digitalWrite(beep, HIGH);
    digitalWrite(error, HIGH);
    delay(500);
    digitalWrite(beep, LOW);
    digitalWrite(error, LOW);
    delay(200);
    digitalWrite(beep, HIGH);
    digitalWrite(error, HIGH);
    delay(500);
    digitalWrite(beep, LOW);
    digitalWrite(error, LOW);
  }
  if (activity == "armed") {
    Serial.println("System Arming in...");
    count = timer;
    for (count <= 0; count--;) {
      Serial.println(count);
      digitalWrite(beep, HIGH);
      digitalWrite(warn, HIGH);
      delay(500);
      digitalWrite(beep, LOW);
      digitalWrite(warn, LOW);
      delay(500);
    }
    Serial.println("System Armed");
    digitalWrite(beep, HIGH);
    digitalWrite(warn, HIGH);
    delay(1000);
    digitalWrite(beep, LOW);
    digitalWrite(warn, LOW);
    setColor(255, 0, 0);
    armed = true;
  }
  if (activity == "disarm") {
    Serial.println("System Disarmed");
    digitalWrite(beep, HIGH);
    digitalWrite(warn, HIGH);
    delay(500);
    digitalWrite(beep, LOW);
    digitalWrite(warn, LOW);
    delay(500);
    Serial.println("System Disarmed");
    digitalWrite(beep, HIGH);
    digitalWrite(warn, HIGH);
    delay(500);
    digitalWrite(beep, LOW);
    digitalWrite(warn, LOW);
    delay(500);
    setColor(0, 255, 0);
    armed = false;
    alarm = false;
  }
  if (activity == "setdone") {
    Serial.println("Successfully Set New Code");
    digitalWrite(beep, HIGH);
    digitalWrite(active, HIGH);
    delay(300);
    digitalWrite(beep, LOW);
    digitalWrite(active, LOW);
    delay(100);
    digitalWrite(beep, HIGH);
    digitalWrite(active, HIGH);
    delay(300);
    digitalWrite(beep, LOW);
    digitalWrite(active, LOW);
    delay(100);
    digitalWrite(beep, HIGH);
    digitalWrite(active, HIGH);
    delay(300);
    digitalWrite(beep, LOW);
    digitalWrite(active, LOW);
    delay(100);
    setColor(0, 255, 0);
    setCode = false;
    code[4] = '\0';
    password.set(code);
    pressed = 0;
  }
  if (activity == "stopset") {
    Serial.println("Canceled Set New Code");
    digitalWrite(beep, HIGH);
    digitalWrite(error, HIGH);
    delay(3000);
    digitalWrite(beep, LOW);
    digitalWrite(error, LOW);
    setColor(0, 255, 0);
    setCode = false;
    code[0] = "";
    pressed = 0;
  }
  if (activity == "setcode") {
    Serial.println("Please Set New Code");
    digitalWrite(beep, HIGH);
    digitalWrite(active, HIGH);
    delay(150);
    digitalWrite(beep, LOW);
    digitalWrite(active, LOW);
    delay(300);
    digitalWrite(beep, HIGH);
    digitalWrite(active, HIGH);
    delay(150);
    digitalWrite(beep, LOW);
    digitalWrite(active, LOW);
    delay(300);
    setColor(0, 0, 255);
    setCode = true;
  }
  if (activity == "error") {
    Serial.println("Error: Something Went Wrong");
    digitalWrite(beep, HIGH);
    digitalWrite(error, HIGH);
    delay(3000);
    digitalWrite(beep, LOW);
    digitalWrite(error, LOW);
  }
  if (activity == "alarm") {
    Serial.println("Alarm Triggered!");
    digitalWrite(error, HIGH);
    tone(alert, 2000);
    delay(100);
    digitalWrite(error, LOW);
    noTone(alert);
    delay(50);
    digitalWrite(error, HIGH);
    tone(alert, 1000);
    delay(100);
    digitalWrite(error, LOW);
    noTone(alert);
    alarm = true;
  }
}

void setColor(int redColor, int greenColor, int blueColor) {
#ifdef COMMON_ANODE
  redColor = 255 - redColor;
  greenColor = 255 - greenColor;
  blueColor = 255 - blueColor;
#endif
  analogWrite(red, redColor);
  analogWrite(green, greenColor);
  analogWrite(blue, blueColor);
}
