// TODO: implement faster scrolling for hold-down

/* Pin wirings: 

  * LCD screen: 
  *   For I2C: 
  *     SGA --> A4
  *     SGL --> A5
  *   For 16-bit: 
  *     2 --> RS
  *     3 --> Enable
  *     4 --> D4
  *     5 --> D5
  *     6 --> D6
  *     7 --> D7
  * Button panel:
  *   8  --> switch1
  *   9  --> switch-GND1
  *   10 --> switch-GND2
  *   11 --> switch-GND3
  *   12 --> switch-GND4

*/


#include <Keypad.h>

// figure out which one to use:
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
LiquidCrystal_I2C newLCD(0x38);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define NUM_CLASSES 3
#define NUM_DAYS 7

#define cols 4
#define rows 1

// button panel constants
const char inputs [rows] [cols] = {
  {'A', 'B', 'C', 'D'}
};
const byte rowPins [rows] = {8};
const byte colPins [cols] = {9, 10, 11, 12};
Keypad keypad (makeKeymap (inputs), rowPins, colPins, rows, cols);

// Logic constants
const String classes[NUM_CLASSES] = {"English", "History", "Music"};
const String days[NUM_DAYS] = {"A", "B", "C", "E", "F", "R", "M"};
int classIndex = 0;
int dayIndex = 0;

String getMessage() {
  return days[dayIndex] + ": " + classes[classIndex];
}

void print() {
  lcd.clear();
  lcd.print (getMessage());
}

void loopClass(int increment) {
  classIndex += increment;
  if (classIndex < 0) classIndex = NUM_CLASSES;
  else if (classIndex == NUM_CLASSES) classIndex = 0;
  print();
}

void loopDay(int increment) {
  dayIndex += increment;
  if (dayIndex < 0) dayIndex = NUM_DAYS;
  else if (dayIndex == NUM_DAYS) dayIndex = 0;
  print();
}

void onPress(KeypadEvent key) {
  KeyState state = keypad.getState();
  switch (state) {
    case PRESSED: 
      switch (state) {
        case 'A': loopClass (-1); break;
        case 'B': loopClass (1); break;
        case 'C': loopDay (-1); break;
        case 'D': loopDay (1); break;
      }
      break;
  }
}

void setup() {
  Serial.begin (9600);
  lcd.begin(16, 2);
  keypad.addEventListener (onPress);
}

void loop() {keypad.getKey();}