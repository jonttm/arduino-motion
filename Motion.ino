/*
  The Ultimate Alarm System!
  By JTTM (Jonathan Currier)
  Version 1.4 Stable - Remote Control Revolution

  Manual:
  Before using make sure and double check the setup below. Also, make sure all your variables for pins are correct.
  At any time you can press the stop button to cancel the current action except to disable the alarm.
  For all actions type in your code then press any of the following buttons:
  Disarm - Disarms the system and disables the alarm.
  Alarm - Force triggers an alarm, alarm will continue running until disarmed.
  Arm - Arms the system after a short countdown of 5 seconds. You can change the countdown below.
  Set - Set a new code. Type in your new code then press save to save it or stop to cancel.
  Stop - Cancel the current action like setting a new code and typing in current code.
  | - If you press stop while armed or the alarm is triggered it won't do anything.
  | - If you type in your code then press stop the alarm will stop and disarm.
  Save - Save the current code you are setting or press stop to cancel.
  Reset - Resets everything including wether the system is armed or alarm is triggered.
  | - The default code is also set. Kind of like pressing the reset button on Arduino Board.
  Every action has it's own set of sounds and lights, you can read the code below to find out what each one is.
  The green light is disarm, the red light is armed, and the blue light is setting new code.
  For super specific details then read the serial output. (Click the magnifying glass in the in the upper right.)

  Buttons:
  Type in your custom buttons here so you don't forget them.
  [ VOL- ] = Disarm
  [ ►❚❚ ] = Trigger Alarm
  [ VOL+ ] = Arm
  [ SETUP ] = Set Code
  [ STOP/MODE ] = Cancel Current Action
  [ ENTER/SAVE ] = Save New Code
  [ 0 10+ ] = Keypad 0
  [ ↩ ] = Reset
  [ 1,2,3... ] Entire Keypad

  Versions:
  1.4 - Remote Control Revolution
  1.3 - The Remote Update
  1.2 - Customizable Settable Code!
  1.1 - Arming Button
  1.0 - Motion!

  Changelog:
  1.4_15 - Made very small changes and finished v1.4.
  1.4_14 - General improvements and polishing.
  1.4_13 - Every keypad button will count as a tried code entry.
  1.4_12 - Every keypad button makes a sound now.
  1.4_11 - Added Serial Output and made set code a bit nicer.
  1.4_10 - Fixed a bug where you couldn't enter a number twice.
  1.4_9 - Updated all text for new version and removed old code.
  1.4_8 - Fixed some more small but annoying bugs.
  1.4_7 - Fixed literally the most stupid bugs in the world.
  1.4_6 - Double checked and made some finishing touches
  1.4_5 - Added the alarm and armed functions.
  1.4_4 - Added the new set code function.
  1.4_3 - Updated some text and descriptions to reflect new program.
  1.4_2 - Added the new primary interface: Enter Code, Select Action
  1.4_1 - Starting over and making the remote control primary.

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
  Have fun!
*/

// RGB LED pins
int redPin = 11;        // Red Pin
int greenPin = 10;      // Green Pin
int bluePin = 9;        // Blue Pin

// Please comment the line below if your LED is NOT a Common Anode.
#define COMMON_ANODE

// Please comment the line below if you want a slower arming time of 20 seconds.
// Fast arming time is 5 seconds.
#define FAST_COUNTDOWN

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
unsigned long remotearm = 16597183;    // Remote Confirm Arm              (DEC VALUE)
unsigned long remotedisarm = 16580863; // Remote Confirm Disarm           (DEC VALUE)
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
int set = 0;
int set1 = 0;
int set2 = 0;
int set3 = 0;
int set4 = 0;
int ok = 0;
int irsound = 0;
unsigned long setcode1 = 0;
unsigned long setcode2 = 0;
unsigned long setcode3 = 0;
unsigned long setcode4 = 0;
#include <IRremote.h>           // This isn't a variable.
IRrecv irrecv(remote);          // Neither is this.
decode_results results;         // Also, this.
// Seriously, don't touch.

// When the arduino starts:
void setup() {
  // Setting all these pins to Output:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(motion, INPUT);       // Except this one.
  pinMode(sound, OUTPUT);
  Serial.begin(9600);           // Start Serial Connection.
  irrecv.enableIRIn();          // Start IR Reciever.
  setColor(0, 255, 0);          // Set the LED to green.
  Serial.println("System Ready");
  Serial.println("Please enter your code.");
}

// Run this code repeatably:
void loop() {
top:
  if (ok == 4) {
    ok = 5;
    setColor(0, 0, 0);
    delay(50);
    setColor(0, 0, 255);
    Serial.println("Press save or cancel to continue.");
  }
  delay(150);
  // When we receive an IR input:
  if (irrecv.decode(&results)) {
    irsound = 1;                            // Ladies and Gentlemen! We pressed a button.
    setColor(0, 0, 0);                      // Make some noise when a button is pressed.
    digitalWrite(sound2, HIGH);
    irrecv.resume();                        // Recieve the next input.
    if (set == 0) {                         // Don't recieve input while setting new code.
      // All of these are to make sure someone knows if they got the code wrong:
      if (results.value == remote0) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == remote1) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == remote2) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == remote3) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == remote4) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == remote5) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == remote6) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == remote7) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == remote8) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == remote9) {
        code++;                             // One more button has been pressed!
      }
      if (results.value == code1) {         // The first button is pressed.
        if (pass1 == 0) {                   // Make sure the first button hasn't been pressed.
          pass1 = 1;                        // Tell the next button it is okay to be pressed.
          goto top;
        }
      }
      if (results.value == code2) {         // The second button is pressed.
        if (pass2 == 0) {                   // Make sure the second button hasn't been pressed.
          if (pass1 == 1) {                 // Make sure the first button was pressed.
            pass2 = 1;                      // Tell the next button it is okay to be pressed.
          }
          goto top;
        }
      }
      if (results.value == code3) {         // The third button is pressed.
        if (pass3 == 0) {                   // Make sure the third button hasn't been pressed.
          if (pass1 == 1) {                 // Make sure the first button was pressed.
            if (pass2 == 1) {               // Make sure the second button was pressed.
              pass3 = 1;                    // Tell the next button it is okay to be pressed.
            }
          }
          goto top;
        }
      }
      if (results.value == code4) {         // The third button is pressed.
        if (pass4 == 0) {                   // Make sure the fourth button hasn't been pressed.
          if (pass1 == 1) {                 // Make sure the first button was pressed.
            if (pass2 == 1) {               // Make sure the second button was pressed.
              if (pass3 == 1) {             // Make sure the second button was pressed.
                pass4 = 1;                  // This button has been pressed.
              }
            }
          }
          goto top;
        }
      }
      if (correct == 1) {                         // If the code was correct then allow additional input.
        if (results.value == remoteset) {         // If the set button is pressed.
          alarm = 0;                              // Make sure the system isn't armed or the alarm is triggered.
          armed = 0;
          set = 1;                                // Start set mode.
          correct = 0;                            // Cancel additional input.
          Serial.println("Set your new code.");
          setColor(0, 0, 0);
          digitalWrite(sound2, HIGH);
          delay(200);
          setColor(0, 0, 255);
          digitalWrite(sound2, LOW);
          delay(200);
          setColor(0, 0, 0);
          digitalWrite(sound2, HIGH);
          delay(200);
          setColor(0, 0, 255);
          digitalWrite(sound2, LOW);
          goto top;
        }
        if (results.value == remotearm) {         // If the arm button is pressed.
          armed = 1;                              // Start armed mode.
          correct = 0;                            // Cancel additional input.
          Serial.println("Please leave now!");
          Serial.println("System arming in...");
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
#ifdef FAST_COUNTDOWN
          for (int i = 0; i <= 5; i++) {          // Countdown for 5 seconds.
            Serial.println(i);
            delay(500);
            setColor(0, 0, 0);
            digitalWrite(sound2, HIGH);
            delay(500);
            setColor(255, 0, 0);
            digitalWrite(sound2, LOW);
          }
#else
          for (int i = 0; i <= 30; i++) {         // If slow countdown is selected then countdown for 20 seconds.
            Serial.println(i);
            delay(500);
            setColor(0, 0, 0);
            digitalWrite(sound2, HIGH);
            delay(500);
            setColor(255, 0, 0);
            digitalWrite(sound2, LOW);
          }
#endif
          Serial.println("System Armed");
          delay(500);
          setColor(0, 0, 0);
          digitalWrite(sound2, HIGH);
          delay(3000);
          setColor(255, 0, 0);
          digitalWrite(sound2, LOW);
          goto top;
        }
        if (results.value == remotedisarm) {      // If the disarm button is pressed.
          alarm = 0;                              // Stop the alarm if it was triggered.
          armed = 0;                              // Disable armed mode.
          correct = 0;                            // Cancel additional input.
          Serial.println("System Disarmed");
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
        if (results.value == remotealarm) {       // If the alarm button is pressed.
          alarm = 1;                              // Trigger the alarm.
          correct = 0;                            // Cancel additional input.
          Serial.println("Alarm Triggered!");
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
        if (results.value == remotereset) {       // If the reset button is pressed.
          pass1 = 0;                              // Reset every single variable and state back to 0.
          pass2 = 0;                              // Code entry.
          pass3 = 0;
          pass4 = 0;
          armed = 0;                              // Armed state.
          code = 0;                               // Total code entry.
          alarm = 0;                              // Alarm triggered.
          correct = 0;                            // Additional input.
          set = 0;                                // Set mode.
          set1 = 0;                               // Set code entry.
          set2 = 0;
          set3 = 0;
          set4 = 0;
          setcode1 = 0;                           // Mode set code entry.
          setcode2 = 0;
          setcode3 = 0;
          setcode4 = 0;
          code1 = remote1;                        // Set the code to the default code.
          code2 = remote2;
          code3 = remote3;
          code4 = remote4;
          ok = 0;
          Serial.println("System Reseting");
          digitalWrite(sound2, HIGH);
          delay(30);
          setColor(0, 0, 0);
          digitalWrite(sound2, LOW);
          delay(8000);
          setColor(0, 255, 0);
          Serial.println("System Ready");
          goto top;
        }
        if (results.value == remotestop) {        // If the stop button is pressed while code has been entered.
          pass1 = 0;                              // Reset code entry.
          pass2 = 0;
          pass3 = 0;
          pass4 = 0;
          code = 0;                               // Reset code buttons pressed.
          correct = 0;                            // Cancel additional input.
          armed = 0;                              // Disarm the system.
          alarm = 0;                              // Disable the alarm.
          set = 0;                                // Disable set mode.
          set1 = 0;                               // Reset set code entry.
          set2 = 0;
          set3 = 0;
          set4 = 0;
          setcode1 = 0;                           // Reset secondary set code entry.
          setcode2 = 0;
          setcode3 = 0;
          setcode4 = 0;
          ok = 0;
          Serial.println("Current Action Canceled");
          setColor(255, 0, 0);
          digitalWrite(sound2, HIGH);
          delay(300);
          setColor(0, 255, 0);
          digitalWrite(sound2, LOW);
          goto top;
        }
      }
    }
    if (correct == 0) {                           // Only run when you haven't entered code.
      if (results.value == remotestop) {          // When the stop button is pressed without the code entered.
        pass1 = 0;                                // Reset code entry.
        pass2 = 0;
        pass3 = 0;
        pass4 = 0;
        code = 0;                                 // Reset code buttons pressed.
        correct = 0;                              // Cancel additional input.
        set = 0;                                  // Disable set mode.
        set1 = 0;                                 // Reset set code entry.
        set2 = 0;
        set3 = 0;
        set4 = 0;
        setcode1 = 0;                             // Reset secondary set code entry.
        setcode2 = 0;
        setcode3 = 0;
        setcode4 = 0;
        ok = 0;
        Serial.println("Current Action Canceled");
        setColor(255, 0, 0);
        digitalWrite(sound2, HIGH);
        delay(300);
        setColor(0, 255, 0);
        digitalWrite(sound2, LOW);
        goto top;
      }
    }
    if (set == 1) {                               // If set mode is enabled.
      if (results.value == remote0) {             // If button zero is pressed.
        if (set1 == 0) {                          // If the first code has not been set.
          set1 = 1;                               // The first code has been set.
          setcode1 = remote0;                     // Set the first code to button zero.
          ok++;                                   // One number has been entered.
          goto top;
        }
        else {
          if (set2 == 0) {                        // If the second code has not been set.
            set2 = 1;                             // The second code has been set.
            setcode2 = remote0;                   // Set the second code to button zero.
            ok++;                                 // One number has been entered.
            goto top;
          }
          else {
            if (set3 == 0) {                      // If the third code has not been set.
              set3 = 1;                           // The third code has been set.
              setcode3 = remote0;                 // Set the third code to button zero.
              ok++;                               // One number has been entered.
              goto top;
            }
            else {
              if (set4 == 0) {                    // If the fourth code has not been set.
                set4 = 1;                         // The fourth code has been set.
                setcode4 = remote0;               // Set the third code to button zero.
                ok++;                             // One number has been entered.
                goto top;
              }
            }
          }
        }
      }
      if (results.value == remote1) {             // Same as above, but for button one.
        if (set1 == 0) {
          set1 = 1;
          setcode1 = remote1;
          ok++;
          goto top;
        }
        else {
          if (set2 == 0) {
            set2 = 1;
            setcode2 = remote1;
            ok++;
            goto top;
          }
          else {
            if (set3 == 0) {
              set3 = 1;
              setcode3 = remote1;
              ok++;
              goto top;
            }
            else {
              if (set4 == 0) {
                set4 = 1;
                setcode4 = remote1;
                ok++;
                goto top;
              }
            }
          }
        }
      }
      if (results.value == remote2) {             // Button two.
        if (set1 == 0) {
          set1 = 1;
          setcode1 = remote2;
          ok++;
          goto top;
        }
        else {
          if (set2 == 0) {
            set2 = 1;
            setcode2 = remote2;
            ok++;
            goto top;
          }
          else {
            if (set3 == 0) {
              set3 = 1;
              setcode3 = remote2;
              ok++;
              goto top;
            }
            else {
              if (set4 == 0) {
                set4 = 1;
                setcode4 = remote2;
                ok++;
                goto top;
              }
            }
          }
        }
      }
      if (results.value == remote3) {             // Button three.
        if (set1 == 0) {
          set1 = 1;
          setcode1 = remote3;
          ok++;
          goto top;
        }
        else {
          if (set2 == 0) {
            set2 = 1;
            setcode2 = remote3;
            ok++;
            goto top;
          }
          else {
            if (set3 == 0) {
              set3 = 1;
              setcode3 = remote3;
              ok++;
              goto top;
            }
            else {
              if (set4 == 0) {
                set4 = 1;
                setcode4 = remote3;
                ok++;
                goto top;
              }
            }
          }
        }
      }
      if (results.value == remote4) {             // Button four.
        if (set1 == 0) {
          set1 = 1;
          setcode1 = remote4;
          ok++;
          goto top;
        }
        else {
          if (set2 == 0) {
            set2 = 1;
            setcode2 = remote4;
            ok++;
            goto top;
          }
          else {
            if (set3 == 0) {
              set3 = 1;
              setcode3 = remote4;
              ok++;
              goto top;
            }
            else {
              if (set4 == 0) {
                set4 = 1;
                setcode4 = remote4;
                ok++;
                goto top;
              }
            }
          }
        }
      }
      if (results.value == remote5) {             // Button five.
        if (set1 == 0) {
          set1 = 1;
          setcode1 = remote5;
          ok++;
          goto top;
        }
        else {
          if (set2 == 0) {
            set2 = 1;
            setcode2 = remote5;
            ok++;
            goto top;
          }
          else {
            if (set3 == 0) {
              set3 = 1;
              setcode3 = remote5;
              ok++;
              goto top;
            }
            else {
              if (set4 == 0) {
                set4 = 1;
                setcode4 = remote5;
                ok++;
                goto top;
              }
            }
          }
        }
      }
      if (results.value == remote6) {             // Button six.
        if (set1 == 0) {
          set1 = 1;
          setcode1 = remote6;
          ok++;
          goto top;
        }
        else {
          if (set2 == 0) {
            set2 = 1;
            setcode2 = remote6;
            ok++;
            goto top;
          }
          else {
            if (set3 == 0) {
              set3 = 1;
              setcode3 = remote6;
              ok++;
              goto top;
            }
            else {
              if (set4 == 0) {
                set4 = 1;
                setcode4 = remote6;
                ok++;
                goto top;
              }
            }
          }
        }
      }
      if (results.value == remote7) {             // Button seven.
        if (set1 == 0) {
          set1 = 1;
          setcode1 = remote7;
          ok++;
          goto top;
        }
        else {
          if (set2 == 0) {
            set2 = 1;
            setcode2 = remote7;
            ok++;
            goto top;
          }
          else {
            if (set3 == 0) {
              set3 = 1;
              setcode3 = remote7;
              ok++;
              goto top;
            }
            else {
              if (set4 == 0) {
                set4 = 1;
                setcode4 = remote7;
                ok++;
                goto top;
              }
            }
          }
        }
      }
      if (results.value == remote8) {             // Button eight.
        if (set1 == 0) {
          set1 = 1;
          setcode1 = remote8;
          ok++;
          goto top;
        }
        else {
          if (set2 == 0) {
            set2 = 1;
            setcode2 = remote8;
            ok++;
            goto top;
          }
          else {
            if (set3 == 0) {
              set3 = 1;
              setcode3 = remote8;
              ok++;
              goto top;
            }
            else {
              if (set4 == 0) {
                set4 = 1;
                setcode4 = remote8;
                ok++;
                goto top;
              }
            }
          }
        }
      }
      if (results.value == remote9) {             // Button nine.
        if (set1 == 0) {
          set1 = 1;
          setcode1 = remote9;
          ok++;
          goto top;
        }
        else {
          if (set2 == 0) {
            set2 = 1;
            setcode2 = remote9;
            ok++;
            goto top;
          }
          else {
            if (set3 == 0) {
              set3 = 1;
              setcode3 = remote9;
              ok++;
              goto top;
            }
            else {
              if (set4 == 0) {
                set4 = 1;
                setcode4 = remote9;
                ok++;
                goto top;
              }
            }
          }
        }
      }
      if (ok == 5) {
        if (results.value == remoteok) {
          if (set1 == 1) {
            if (set2 == 1) {
              if (set3 == 1) {
                if (set4 == 1) {
                  code1 = setcode1;
                  code2 = setcode2;
                  code3 = setcode3;
                  code4 = setcode4;
                  setcode1 = 0;
                  setcode2 = 0;
                  setcode3 = 0;
                  setcode4 = 0;
                  set1 = 0;
                  set2 = 0;
                  set3 = 0;
                  set4 = 0;
                  set = 0;
                  ok = 0;
                  Serial.println("Successfully saved new code.");
                  setColor(0, 0, 0);
                  digitalWrite(sound2, HIGH);
                  delay(100);
                  setColor(0, 0, 255);
                  digitalWrite(sound2, LOW);
                  delay(300);
                  setColor(0, 0, 0);
                  digitalWrite(sound2, HIGH);
                  delay(100);
                  setColor(0, 0, 255);
                  digitalWrite(sound2, LOW);
                  delay(300);
                  setColor(0, 0, 0);
                  digitalWrite(sound2, HIGH);
                  delay(100);
                  setColor(0, 255, 0);
                  digitalWrite(sound2, LOW);
                  goto top;
                }
              }
            }
          }
        }
      }
    }
    goto top;
  }
  if (code == 4) {                      // If four buttons have been pressed then...
    if (pass1 == 1) {                   // Check if the first button was pressed.
      if (pass2 == 1) {                 // Check if the second button was pressed.
        if (pass3 == 1) {               // Check if the third button was pressed.
          if (pass4 == 1) {             // Check if the fourth button was pressed.
            correct = 1;                // If everything was good then reset the code entry and allow additional input.
            code = 0;
            pass1 = 0;
            pass2 = 0;
            pass3 = 0;
            pass4 = 0;
            Serial.println("Code Correct");
            Serial.println("Press any button to trigger an action.");
            setColor(0, 0, 255);
            digitalWrite(sound2, HIGH);
            delay(50);
            setColor(0, 0, 0);
            digitalWrite(sound2, LOW);
            delay(100);
            setColor(0, 0, 255);
            digitalWrite(sound2, HIGH);
            delay(500);
            setColor(0, 255, 0);
            digitalWrite(sound2, LOW);
            goto top;
          }
          else {                        // Otherwise reset the code entry and don't allow additional input.
            Serial.println("Code Incorrect");
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
          Serial.println("Code Incorrect");
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
        Serial.println("Code Incorrect");
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
      Serial.println("Code Incorrect");
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
  if (irsound == 1) {                     // If we pressed a button.
    irsound = 0;                          // Finish the sound!
    setColor(0, 255, 0);
    digitalWrite(sound2, LOW);
    goto top;
  }
  if (set == 1) {
    setColor(0, 0, 255);
  }
  if (armed == 1) {                       // If the system is armed.
    setColor(255, 0, 0);
    if (digitalRead(motion) == true) {    // If the motion sensor is triggered.
      alarm = 1;                          // Trigger the alarm.
      Serial.println("Alarm Triggered!");
    }
  }
  if (alarm == 1) {                       // If the alarm is triggered.
    setColor(255, 0, 0);                  // MAKE LOUD NOISES
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
  }
}

// Set the LED to a new color:
void setColor(int red, int green, int blue) {
#ifdef COMMON_ANODE                               // If a common anode.
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);                       // Set the LED to the new color.
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// Wow! You made it to the end, congratulations.
