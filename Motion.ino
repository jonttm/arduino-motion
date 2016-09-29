/*
  The Ultimate Alarm System!
  By JTTM (Jonathan Currier)
  Version 1.3 Stable - The Remote Update

  Manual:
  Buttons 1,2,3,4 Left to Right or User Preference are the keypad.
  The button away from the keypad is the set button.
  To arm and disarm just type in your code.
  To set a new code, press the set button, then enter old code, then enter new code.
  Make sure and wait between button presses until the beep stops.

  Version History:
  1.3 - The Remote Update
  1.2 - Customizable Settable Code!
  1.1 - Arming Button
  1.0 - Motion!

  Changelog:
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
  - 5 Buttons
  - RGB LED
  - Buzzer
  - Small Speaker
  - Breadboard
  - Arduino (Obviously)
  - A Heck Ton of Wires!
  - 6 Resistors

  Setup:
  -  IRremote  -
  Install the IR Remote library. You will need to do the stuff below so IRremote works with this code:
  Look up how to fix IRremote conflict with tone() and look up how to delete the prexisting IR library from Arduino.
  -   Things   -
  Make a nice row of 4 buttons (this will be your keypad) and put button 5 off to the side (set button).
  Setup everything else how ya like.

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
unsigned long remote1 = 16582903;      // Remote Button1   (DEC VALUE)
unsigned long remote2 = 16615543;      // Remote Button2   (DEC VALUE)
unsigned long remote3 = 16599223;      // Remote Button3   (DEC VALUE)
unsigned long remote4 = 16591063;      // Remote Button4   (DEC VALUE)
unsigned long remoteset = 16589023;    // Remote ButtonSet (DEC VALUE)

// Default Code (When Arduino is reset)
unsigned long code1 = button1;         // First Code
unsigned long code2 = button2;         // Second Code
unsigned long code3 = button3;         // Third Code
unsigned long code4 = button4;         // Fourth Code

// Default Variables (Don't touch any of these)
int pass1 = 0;
int pass2 = 0;
int pass3 = 0;
int pass4 = 0;
int state = 0;
int set = 0;
int set1 = 0;
int set2 = 0;
int set3 = 0;
int set4 = 0;
int correct = 0;
int done = 0;
int rm = 0;
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
}
void loop() {
top:
  // This stuff happens when IR is triggered:
  if (irrecv.decode(&results)) {
    irrecv.resume(); // Recieve the IR Value
    // If someone pushes the set button:
    if (results.value == remoteset) {
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
  if (digitalRead(buttonset) == true) {
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
// This is to make your board flash with a beutiful RGB LED:
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
// WOW! You finally made it! Welcome to the end. ~
