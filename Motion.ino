/*
  The Ultimate Alarm System!
  By JTTM (Jonathan Currier)
  Version 1.4 Dev 3 - Remote Control Revolution

  Manual:
  Enter in your current code and then you can press any of the following:
  Arm, Disarm, Trigger Alarm, Set New Code, Cancel Current Action, Reset.
  Arm - Arms the system.
  Disarm - Disarms the system.
  Trigger Alarm - Forces the alarm to trigger (Panic Mode).
  Set New Code - Set a new code.
  Cancel Current Action - Cancels the current opperation or action.
  Reset - Resets the program including all states like armed or alarm.
  More later...

  Versions:
  1.4 - Remote Control Revolution
  1.3 - The Remote Update
  1.2 - Customizable Settable Code!
  1.1 - Arming Button
  1.0 - Motion!

  Changelog:
  1.4_3 - Updated some text and descriptions to reflect new program.
  1.4_2 - Added the new primary interface: Enter Code, Select Action
  1.4_1 - Starting over and making the remote control primary.
  1.3_8 - Made the description cooler and added manual, version history.
  1.3_7 - Fixed the button code running when remote was pressed.
  1.3_6 - Fixed tone() conflict with IRremote.
  1.3_5 - Fixed some important bugs.
  1.3_4 - Made it so the Remote is separate from the Buttons.
  1.3_3 - Told the IR Code to reconsider why it won't work.
  1.3_2 - Added some IR stuff I forgot.
  1.3_1 - Added IR Remote Input that doesn't work
  1.2_4 - Added a bunch of text.
  1.2_3 - Small bug fixes.
  1.2_2 - Fixed the set mode.
  1.2_1 - Added a broken set mode.
  1.1_3 - Fixed a lot of small bugs.
  1.1_2 - Made the passcode system great again.
  1.1_1 - Now you press 4 buttons instead of 1 to arm.
  1.0_2 - Made a arming system with the press of a button.
  1.0_1 - Made a motion sensor alarm.

  Stuff Required:
  - IR Sensor
  - IR Remote
  - PIR Motion Sensor
  - RGB LED
  - Buzzer
  - Small Speaker
  - Breadboard
  - Arduino (Obviously)
  - A Heck Ton of Wires!
  - 1 Resistor

  Setup:
  Install the IR Remote library. You will need to do the stuff below so IRremote works with this code:
  Look up how to fix IRremote conflict with tone() and look up how to delete the prexisting IR library from Arduino.
  If you need help on how to setup the hardware then look it up, there should be instructions on everything.
  Input all your hardware pins below.

  Have fun and you can watch the serial log for more detailed output then just beeps and lights.
*/
// RGB LED pins
int redPin = 11;        // Red Pin
int greenPin = 10;      // Green Pin
int bluePin = 9;        // Blue Pin

// Please comment the line below if your LED is NOT a Common Anode.
#define COMMON_ANODE

// Motion and Sound Pins
int motion = 2;                        // Motion Sensor Pin
int sound = 7;                         // Speaker Pin
int sound2 = 4;                        // Buzzer Pin
int remote = 3;                        // IR Sensor

// Button Pins
int button1 = 13;                      // First Button
int button2 = 12;                      // Second Button
int button3 = 8;                       // Third Button
int button4 = 6;                       // Fourth Button
int buttonset = 5;                     // Button used to trigger set mode
unsigned long remote0 = 16593103;      // Remote Keypad 0   (DEC VALUE)
unsigned long remote1 = 16582903;      // Remote Keypad 1   (DEC VALUE)
unsigned long remote2 = 16615543;      // Remote Keypad 2   (DEC VALUE)
unsigned long remote3 = 16599223;      // Remote Keypad 3   (DEC VALUE)
unsigned long remote4 = 16591063;      // Remote Keypad 4   (DEC VALUE)
unsigned long remote5 = 16623703;      // Remote Keypad 5   (DEC VALUE)
unsigned long remote6 = 16607383;      // Remote Keypad 6   (DEC VALUE)
unsigned long remote7 = 16586983;      // Remote Keypad 7   (DEC VALUE)
unsigned long remote8 = 16619623;      // Remote Keypad 8   (DEC VALUE)
unsigned long remote9 = 16603303;      // Remote Keypad 9   (DEC VALUE)
unsigned long remoteset = 16589023;    // Remote Set Code   (DEC VALUE)
unsigned long remotestop = 16605343;   // Remote Cancel Current Action    (DEC VALUE)
unsigned long remoteok = 16617583;     // Remote Save or Confirm          (DEC VALUE)
unsigned long remotearm = 16580863;    // Remote Confirm Arm              (DEC VALUE)
unsigned long remotedisarm = 16597183; // Remote Confirm Disarm           (DEC VALUE)
unsigned long remotealarm = 16613503;  // Remote Trigger Alarm            (DEC VALUE)
unsigned long remotereset = 16609423;  // Remote Reset Program            (DEC VALUE)

// Default Code (When Arduino is reset)
unsigned long code1 = remote1;         // First Code
unsigned long code2 = remote2;         // Second Code
unsigned long code3 = remote3;         // Third Code
unsigned long code4 = remote4;         // Fourth Code

// Default Variables (Don't touch any of these)
int pass1 = 0;
int pass2 = 0;
int pass3 = 0;
int pass4 = 0;
int armed = 0;
int code = 0;
int alarm = 0;
int correct = 0;
#include <IRremote.h>           // This isn't a variable
IRrecv irrecv(remote);          // Neither is this
decode_results results;         // Also, this
// Seriously, don't touch.

void setup() {
  // Setting all these pins to Output:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(motion, INPUT);       // Except this one
  pinMode(sound, OUTPUT);
  Serial.begin(9600);           // Start Serial Connection
  irrecv.enableIRIn();          // Start IR Reciever
  setColor(0, 255, 0);          // Set the LED to green
}
void loop() {       // No descriptions in loop just yet...
top:
  if (irrecv.decode(&results)) {
    irrecv.resume();
    if (results.value == code1) {
      pass1 = 1;
      code++;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(100);
      setColor(0, 255, 0);
      digitalWrite(sound2, LOW);
      goto top;
    }
    if (results.value == code2) {
      if (pass1 == 1) {
        pass2 = 2;
      }
      code++;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(100);
      setColor(0, 255, 0);
      digitalWrite(sound2, LOW);
      goto top;
    }
    if (results.value == code3) {
      if (pass1 == 1) {
        if (pass2 == 1) {
          pass3 = 1;
        }
      }
      code++;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(100);
      setColor(0, 255, 0);
      digitalWrite(sound2, LOW);
      goto top;
    }
    if (results.value == code4) {
      if (pass1 == 1) {
        if (pass2 == 1) {
          if (pass3 == 1) {
            pass4 == 1;
          }
        }
      }
      code++;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(100);
      setColor(0, 255, 0);
      digitalWrite(sound2, LOW);
      goto top;
    }
    if (code == 4) {
      if (pass1 == 1) {
        if (pass2 == 1) {
          if (pass3 == 1) {
            if (pass4 == 1) {
              correct = 1;
              code = 0;
              pass1 = 0;
              pass2 = 0;
              pass3 = 0;
              pass4 = 0;
              setColor(0, 0, 0);
              digitalWrite(sound2, HIGH);
              delay(50);
              setColor(0, 255, 0);
              digitalWrite(sound2, LOW);
              delay(100);
              setColor(0, 0, 0);
              digitalWrite(sound2, HIGH);
              delay(50);
              setColor(0, 255, 0);
              digitalWrite(sound2, LOW);
              goto top;
            }
            else {
              correct = 0;
              code = 0;
              pass1 = 0;
              pass2 = 0;
              pass3 = 0;
              pass4 = 0;
              setColor(255, 0, 0);
              digitalWrite(sound2, HIGH);
              delay(500);
              setColor(0, 255, 0);
              digitalWrite(sound2, LOW);
              goto top;
            }
          }
          else {
            correct = 0;
            code = 0;
            pass1 = 0;
            pass2 = 0;
            pass3 = 0;
            pass4 = 0;
            setColor(255, 0, 0);
            digitalWrite(sound2, HIGH);
            delay(500);
            setColor(0, 255, 0);
            digitalWrite(sound2, LOW);
            goto top;
          }
        }
        else {
          correct = 0;
          code = 0;
          pass1 = 0;
          pass2 = 0;
          pass3 = 0;
          pass4 = 0;
          setColor(255, 0, 0);
          digitalWrite(sound2, HIGH);
          delay(500);
          setColor(0, 255, 0);
          digitalWrite(sound2, LOW);
          goto top;
        }
      }
      else {
        correct = 0;
        code = 0;
        pass1 = 0;
        pass2 = 0;
        pass3 = 0;
        pass4 = 0;
        setColor(255, 0, 0);
        digitalWrite(sound2, HIGH);
        delay(500);
        setColor(0, 255, 0);
        digitalWrite(sound2, LOW);
        goto top;
      }
    }
    if (correct == 1) {
      if (results.value == remoteset) {
        // Enter New Code Here
      }
      if (results.value == remotestop) {
        pass1 = 0;
        pass2 = 0;
        pass3 = 0;
        pass4 = 0;
        code = 0;
        alarm = 0;
        correct = 0;
        setColor(255, 0, 0);
        digitalWrite(sound2, HIGH);
        delay(300);
        setColor(0, 255, 0);
        digitalWrite(sound2, LOW);
        goto top;
      }
      if (results.value == remoteok) {
        // Save New Code Here
      }
      if (results.value == remotearm) {
        armed = 1;
        correct = 0;
        setColor(0, 0, 0);
              digitalWrite(sound2, HIGH);
              delay(1000);
              setColor(255, 0, 0);
              digitalWrite(sound2, LOW);
              delay(100);
              setColor(0, 0, 0);
              digitalWrite(sound2, HIGH);
              delay(150);
              setColor(255, 0, 0);
              digitalWrite(sound2, LOW);
              goto top;
      }
      if (results.value == remotedisarm) {
        alarm = 0;
        armed = 0;
        correct = 0;
        setColor(0, 0, 0);
              digitalWrite(sound2, HIGH);
              delay(1000);
              setColor(0, 255, 0);
              digitalWrite(sound2, LOW);
              delay(100);
              setColor(0, 0, 0);
              digitalWrite(sound2, HIGH);
              delay(150);
              setColor(0, 255, 0);
              digitalWrite(sound2, LOW);
              goto top;
      }
      if (results.value == remotealarm) {
        alarm = 1;
        correct = 0;
        setColor(255, 0, 0);
        digitalWrite(sound2, HIGH);
        delay(100);
        setColor(0, 255, 0);
        digitalWrite(sound2, LOW);
        delay(300);
        setColor(255, 0, 0);
        digitalWrite(sound2, HIGH);
        delay(100);
        setColor(0, 255, 0);
        digitalWrite(sound2, LOW);
        goto top;
      }
      if (results.value == remotereset) {
        pass1 = 0;
        pass2 = 0;
        pass3 = 0;
        pass4 = 0;
        armed = 0;
        code = 0;
        alarm = 0;
        correct = 0;
        digitalWrite(sound2, HIGH);
        delay(30);
        setColor(0, 0, 0);
        digitalWrite(sound2, LOW);
        delay(3000);
        setColor(0, 255, 0);
        goto top;
      }
    }
  }
}
// Still require alarm, armed, and set code here

// Old Code:
/*
  if (pass1 == 0) {
  if (state == 0) {
    Serial.println("Please enter old code!");
    setColor(0, 0, 255);                  // More Sounds and Lights
    digitalWrite(sound2, HIGH);
    delay(50);
    setColor(0, 0, 0);
    digitalWrite(sound2, LOW);
    delay(30);
    setColor(0, 0, 255);
    digitalWrite(sound2, HIGH);
    delay(50);
    setColor(0, 0, 0);
    digitalWrite(sound2, LOW);
    delay(30);
    setColor(0, 0, 255);
    digitalWrite(sound2, HIGH);
    delay(50);
    setColor(0, 0, 0);
    digitalWrite(sound2, LOW);
    delay(30);
    set = 1;
  }
  }
  // Magical stuff happens when buttons are pressed:
  if (pass1 == 1) {
  Serial.println("You can not set while disarming or arming!");
  setColor(255, 0, 0);                // A BIG BRIGHT No
  digitalWrite(sound2, HIGH);
  delay(3000);
  setColor(0, 0, 0);
  digitalWrite(sound2, LOW);
  }
  }
  // Setting this cool new code:
  if (correct == 1) {
  if (results.value == remote1) {
  if (set1 == 0) {                                      // Button1 set to Code1
    Serial.println("Code1 Set to Remote1");
    set1 = 1;
    code1 = remote1;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
  }
  else {
    if (set2 == 0) {                                    // Button1 set to Code2
      Serial.println("Code2 Set to Remote1");
      set2 = 1;
      code2 = remote1;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(500);
    }
    else {
      if (set3 == 0) {                                  // Button1 set to Code3
        Serial.println("Code3 Set to Remote1");
        set3 = 1;
        code3 = remote1;
        setColor(0, 0, 0);
        digitalWrite(sound2, HIGH);
        delay(500);
      }
      else {                                            // Button1 set to Code4
        if (set4 == 0) {
          Serial.println("Code4 Set to Remote1");
          set4 = 1;
          code4 = remote1;
          done = 1;
          rm = 1;
          goto done;
        }
      }
    }
  }
  }
  if (results.value == remote2) {                       // Just like above except button2:
  if (set1 == 0) {
    Serial.println("Code1 Set to Remote2");
    set1 = 1;
    code1 = remote2;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
  }
  else {
    if (set2 == 0) {
      Serial.println("Code2 Set to Remote2");
      set2 = 1;
      code2 = remote2;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(500);
    }
    else {
      if (set3 == 0) {
        Serial.println("Code3 Set to Remote2");
        set3 = 1;
        code3 = remote2;
        setColor(0, 0, 0);
        digitalWrite(sound2, HIGH);
        delay(500);
      }
      else {
        if (set4 == 0) {
          Serial.println("Code4 Set to Remote2");
          set4 = 1;
          code4 = remote2;
          done = 1;
          rm = 1;
          goto done;
        }
      }
    }
  }
  }
  if (results.value == remote3) {                               // Again, Button3
  if (set1 == 0) {
    Serial.println("Code1 Set to Remote3");
    set1 = 1;
    code1 = remote3;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
  }
  else {
    if (set2 == 0) {
      Serial.println("Code2 Set to Remote3");
      set2 = 1;
      code2 = remote3;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(500);
    }
    else {
      if (set3 == 0) {
        Serial.println("Code3 Set to Remote3");
        set3 = 1;
        code3 = remote3;
        setColor(0, 0, 0);
        digitalWrite(sound2, HIGH);
        delay(500);
      }
      else {
        if (set4 == 0) {
          Serial.println("Code4 Set to Remote3");
          set4 = 1;
          code4 = remote3;
          done = 1;
          rm = 1;
          goto done;
        }
      }
    }
  }
  }
  if (results.value == remote4) {                           // Button4 Now
  if (set1 == 0) {
    Serial.println("Code1 Set to Remote4");
    set1 = 1;
    code1 = remote4;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
  }
  else {
    if (set2 == 0) {
      Serial.println("Code2 Set to Remote4");
      set2 = 1;
      code2 = remote4;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(500);
    }
    else {
      if (set3 == 0) {
        Serial.println("Code3 Set to Remote4");
        set3 = 1;
        code3 = remote4;
        setColor(0, 0, 0);
        digitalWrite(sound2, HIGH);
        delay(500);
      }
      else {
        if (set4 == 0) {
          Serial.println("Code4 Set to Remote4");
          set4 = 1;
          code4 = remote4;
          done = 1;
          rm = 1;
          goto done;
        }
      }
    }
  }
  }
  }
  if (results.value == code1) {
  if (correct == 0) {                   // Code1
  Serial.println("Code1 Pressed");
  pass1 = 1;
  setColor(0, 0, 0);
  digitalWrite(sound2, HIGH);
  delay(500);
  goto top;
  }
  }
  if (results.value == code2) {
  if (correct == 0) {                   // Code2
  if (pass1 == 1) {
    Serial.println("Code2 Pressed");
    pass2 = 1;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
    goto top;
  }
  }
  }
  if (results.value == code3) {
  if (correct == 0) {                   // Code3
  if (pass2 == 1) {
    Serial.println("Code3 Pressed");
    pass3 = 1;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
    goto top;
  }
  }
  }
  if (results.value == code4) {
  if (correct == 0) {                   // Code4
  if (pass3 == 1) {
    if (set == 1) {
      Serial.println("Code4 Pressed and please enter new code.");
      correct = 1;
      setColor(0, 0, 255);
      digitalWrite(sound2, HIGH);             // Light Show!
      delay(200);
      setColor(0, 0, 0);
      digitalWrite(sound2, LOW);
      delay(100);
      setColor(0, 0, 255);
      digitalWrite(sound2, HIGH);
      delay(200);
      setColor(0, 0, 0);
      digitalWrite(sound2, LOW);
      delay(100);
      goto top;
    }
    else {
      pass4 = 1;
    }
  }
  }
  }
  }
  done:
  if (done == 1) {
  // This happens when a new code is set:
  Serial.println("Successfully Set New Code!");
  state = 0;          // COOL! Variables!
  pass1 = 0;
  pass2 = 0;
  pass3 = 0;
  pass4 = 0;
  set = 0;
  set1 = 0;
  set2 = 0;
  set3 = 0;
  set4 = 0;
  correct = 0;
  done = 0;
  setColor(0, 0, 255);            // So MUCH Color and Noise!
  digitalWrite(sound2, HIGH);
  delay(1000);
  setColor(0, 0, 0);
  digitalWrite(sound2, LOW);
  delay(300);
  setColor(0, 0, 255);
  digitalWrite(sound2, HIGH);
  delay(200);
  setColor(0, 0, 0);
  digitalWrite(sound2, LOW);
  delay(300);
  }

  // If someone pushes the set button:
  /*if (digitalRead(buttonset) == true) {
  if (pass1 == 0) {
  if (state == 0) {
  Serial.println("Please enter old code!");
  setColor(0, 0, 255);                  // More Sounds and Lights
  digitalWrite(sound2, HIGH);
  delay(50);
  setColor(0, 0, 0);
  digitalWrite(sound2, LOW);
  delay(30);
  setColor(0, 0, 255);
  digitalWrite(sound2, HIGH);
  delay(50);
  setColor(0, 0, 0);
  digitalWrite(sound2, LOW);
  delay(30);
  setColor(0, 0, 255);
  digitalWrite(sound2, HIGH);
  delay(50);
  setColor(0, 0, 0);
  digitalWrite(sound2, LOW);
  delay(30);
  set = 1;
  }
  }
  // Magical stuff happens when buttons are pressed:
  if (pass1 == 1) {
  Serial.println("You can not set while disarming or arming!");
  setColor(255, 0, 0);                // A BIG BRIGHT No
  digitalWrite(sound2, HIGH);
  delay(3000);
  setColor(0, 0, 0);
  digitalWrite(sound2, LOW);
  }
  }
  if (rm == 0) {
  if (digitalRead(code1) == true) {
  if (correct == 0) {                   // Code1
  Serial.println("Code1 Pressed");
  pass1 = 1;
  setColor(0, 0, 0);
  digitalWrite(sound2, HIGH);
  delay(500);
  }
  }
  if (digitalRead(code2) == true) {
  if (correct == 0) {                   // Code2
  if (pass1 == 1) {
  Serial.println("Code2 Pressed");
  pass2 = 1;
  setColor(0, 0, 0);
  digitalWrite(sound2, HIGH);
  delay(500);
  }
  }
  }
  if (digitalRead(code3) == true) {
  if (correct == 0) {                   // Code3
  if (pass2 == 1) {
  Serial.println("Code3 Pressed");
  pass3 = 1;
  setColor(0, 0, 0);
  digitalWrite(sound2, HIGH);
  delay(500);
  }
  }
  }
  if (digitalRead(code4) == true) {
  if (correct == 0) {                   // Code4
  if (pass3 == 1) {
  if (set == 1) {
    Serial.println("Code4 Pressed and please enter new code.");
    correct = 1;
    setColor(0, 0, 255);
    digitalWrite(sound2, HIGH);             // Light Show!
    delay(200);
    setColor(0, 0, 0);
    digitalWrite(sound2, LOW);
    delay(100);
    setColor(0, 0, 255);
    digitalWrite(sound2, HIGH);
    delay(200);
    setColor(0, 0, 0);
    digitalWrite(sound2, LOW);
    delay(100);
  }
  else {
    pass4 = 1;
  }
  }
  }
  }
  }
  // Setting this cool new code:
  if (correct == 1) {
  if (digitalRead(button1) == true) {
  if (set1 == 0) {                                      // Button1 set to Code1
  Serial.println("Code1 Set to Button1");
  set1 = 1;
  code1 = button1;
  setColor(0, 0, 0);
  digitalWrite(sound2, HIGH);
  delay(500);
  }
  else {
  if (set2 == 0) {                                    // Button1 set to Code2
    Serial.println("Code2 Set to Button1");
    set2 = 1;
    code2 = button1;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
  }
  else {
    if (set3 == 0) {                                  // Button1 set to Code3
      Serial.println("Code3 Set to Button1");
      set3 = 1;
      code3 = button1;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(500);
    }
    else {                                            // Button1 set to Code4
      if (set4 == 0) {
        Serial.println("Code4 Set to Button1");
        set4 = 1;
        code4 = button1;
        done = 1;
        rm = 0;
      }
    }
  }
  }
  }
  if (digitalRead(button2) == true) {                       // Just like above except button2:
  if (set1 == 0) {
  Serial.println("Code1 Set to Button2");
  set1 = 1;
  code1 = button2;
  setColor(0, 0, 0);
  digitalWrite(sound2, HIGH);
  delay(500);
  }
  else {
  if (set2 == 0) {
    Serial.println("Code2 Set to Button2");
    set2 = 1;
    code2 = button2;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
  }
  else {
    if (set3 == 0) {
      Serial.println("Code3 Set to Button2");
      set3 = 1;
      code3 = button2;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(500);
    }
    else {
      if (set4 == 0) {
        Serial.println("Code4 Set to Button2");
        set4 = 1;
        code4 = button2;
        done = 1;
        rm = 0;
      }
    }
  }
  }
  }
  if (digitalRead(button3) == true) {                               // Again, Button3
  if (set1 == 0) {
  Serial.println("Code1 Set to Button3");
  set1 = 1;
  code1 = button3;
  setColor(0, 0, 0);
  digitalWrite(sound2, HIGH);
  delay(500);
  }
  else {
  if (set2 == 0) {
    Serial.println("Code2 Set to Button3");
    set2 = 1;
    code2 = button3;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
  }
  else {
    if (set3 == 0) {
      Serial.println("Code3 Set to Button3");
      set3 = 1;
      code3 = button3;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(500);
    }
    else {
      if (set4 == 0) {
        Serial.println("Code4 Set to Button3");
        set4 = 1;
        code4 = button3;
        done = 1;
        rm = 0;
      }
    }
  }
  }
  }
  if (digitalRead(button4) == true) {                           // Button4 Now
  if (set1 == 0) {
  Serial.println("Code1 Set to Button4");
  set1 = 1;
  code1 = button4;
  setColor(0, 0, 0);
  digitalWrite(sound2, HIGH);
  delay(500);
  }
  else {
  if (set2 == 0) {
    Serial.println("Code2 Set to Button4");
    set2 = 1;
    code2 = button4;
    setColor(0, 0, 0);
    digitalWrite(sound2, HIGH);
    delay(500);
  }
  else {
    if (set3 == 0) {
      Serial.println("Code3 Set to Button4");
      set3 = 1;
      code3 = button4;
      setColor(0, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(500);
    }
    else {
      if (set4 == 0) {
        Serial.println("Code4 Set to Button4");
        set4 = 1;
        code4 = button4;
        done = 1;
        rm = 0;
      }
    }
  }
  }
  }
  }
  if (pass4 == 1) {                           // Disarming The System
  if (state == 1) {
    Serial.println("System Disarmed");
    state = 0;
    setColor(0, 255, 0);
    digitalWrite(sound2, HIGH);
    delay(200);
    setColor(0, 0, 0);
    digitalWrite(sound2, LOW);
    delay(100);
    setColor(0, 255, 0);
    digitalWrite(sound2, HIGH);
    delay(200);
    setColor(0, 0, 0);
    digitalWrite(sound2, LOW);
    pass1 = 0;
    pass2 = 0;
    pass3 = 0;
    pass4 = 0;
  }
  // Cool stuff happens when you type in your code:
  if (pass4 == 1) {                         // Arming
    if (state == 0) {
      Serial.println("System Armed");
      state = 1;
      setColor(255, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(300);
      setColor(0, 0, 0);
      digitalWrite(sound2, LOW);
      delay(100);
      setColor(255, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(300);
      setColor(0, 0, 0);
      digitalWrite(sound2, LOW);
      delay(100);
      setColor(255, 0, 0);
      digitalWrite(sound2, HIGH);
      delay(300);
      setColor(0, 0, 0);
      digitalWrite(sound2, LOW);
      pass1 = 0;
      pass2 = 0;
      pass3 = 0;
      pass4 = 0;
    }
  }
  }
  if (state == 1) {                               // Someone is in your House! Alarm Triggered!
  if (digitalRead(motion) == true) {
    Serial.println("Alarm Triggered");
    setColor(255, 0, 0);
    tone(sound, 2000);
    delay(100);
    setColor(0, 0, 0);
    noTone(sound);
    delay(50);
    setColor(255, 0, 0);
    tone(sound, 1000);
    delay(100);
    setColor(0, 0, 0);
    noTone(sound);
    delay(50);
  }
  // This keeps your light on when certain states are present:
  else {
    setColor(255, 0, 0);                        // Armed
    digitalWrite(sound2, LOW);
  }
  }
  else {
  if (set == 1) {
    setColor(0, 0, 255);                        // Set Mode
    digitalWrite(sound2, LOW);
  }
  else {
    setColor(0, 255, 0);                        // Disarmed
    digitalWrite(sound2, LOW);
  }
  }
  }
*/

// I'm still here:
void setColor(int red, int green, int blue) {
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
