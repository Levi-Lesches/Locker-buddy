// TODO: implement faster scrolling for hold-down

/* Pin wirings: 

  * LCD screen: 
  *   For I2C, match the labels on the chip 
  *   For 16-bit: (see img)
  *     From the left:
  *       1: GND
  *       2: VCC
  *       3: Potentiometer (left: GND, right: VCC)
  *       4: Arduino pin 2
  *       5: GND
  *       6: Arduino pin 3
  *     From the right: 
  *       1: GND
  *       2: VCC (use resistor if too dim)
  *       3: Arduino pin 7
  *       4: Ardiuno pin 6
  *       5: Arduino pin 5
  *       6: Arduino pin 4
  * Button panel:
  *   8  --> switch1
  *   9  --> switch-GND1
  *   10 --> switch-GND2
  *   11 --> switch-GND3
  *   12 --> switch-GND4
  * Class LEDS:
  *   Chemistry: 14
  *   Math: 15
  *   Talmud: 16
  *   History: 17
  *   Spanish: 18
  *   English: 19
  *   Hebrew: 20
  *   Chumash: 21
  *   Health: 22

*/

#include <Keypad.h>

// For I2C chips: 
// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x3F, 16, 2);

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define NUM_CLASSES 10  // ignore Tefillah
#define NUM_DAYS 7
#define NUM_UNIQUE_CLASSES 14

#define cols 4
#define rows 1

// button panel constants
// A, B --> class (top two)
// C, D --> day (bottom two)
const char inputs [rows] [cols] = {
  {'A', 'C', 'B', 'D'}
};
const byte rowPins [rows] = {8};
const byte colPins [cols] = {9, 10, 11, 12};
Keypad keypad (makeKeymap (inputs), rowPins, colPins, rows, cols);

// Logic constants
const String uniqueClasses [NUM_UNIQUE_CLASSES] = {
  "Chemistry",
  "Math",
  "Talmud",
  "Gym",
  "History",
  "Lunch",
  "Spanish",
  "English",
  "Hebrew",
  "Free",
  "Chumash",
  "Art",
  "Health",
  "Tech"
};
const String classes [NUM_DAYS] [NUM_CLASSES] = {
  {  // A
    "Chemistry", 
    "Math", 
    "Talmud",
    "Gym",
    "History",
    "Lunch",
    "Talmud",
    "Spanish",
    "English",
    "Hebrew"
  }, 
  {  // B
    "Chemistry", 
    "Math", 
    "Free",
    "English",
    "Chumash",
    "Gym",
    "Lunch",
    "Hebrew",
    "Free",
    "Talmud"
  }, 
  {  // C
    "Chumash", 
    "History", 
    "Talmud",
    "Math",
    "Art",
    "Lunch",
    "Chemistry",
    "English",
    "Talmud",
    "Health"
  }, 
  {  // E
    "Talmud", 
    "Art", 
    "Spanish",
    "History",
    "Math",
    "Chemistry",
  }, 
  {  // F
    "Chumash", 
    "Talmud", 
    "English",
    "Hebrew",
    "Tech",
    "History",
  }, 
  {  // M
    "Gym", 
    "Gemara", 
    "Chemistry",
    "History",
    "Tech",
    "Lunch",
    "English",
    "Spanish",
    "Math",
    "Chumash",
  }, 
  {  // R
    "Music", 
    "Math", 
    "Spanish",
    "Talmud",
    "English",
    "Tanach",
    "Lunch",
    "Hebrew",
    "History",
    "Chemistry"
  }
};
const String days[NUM_DAYS] = {"A", "B", "C", "E", "F", "M", "R"};
const int ledPins[NUM_UNIQUE_CLASSES] = {  // skip 13, BUILT_IN
  14,
  15,
  16,
  NULL,  // Gym
  17,
  NULL,  // Lunch
  18, 
  19, 
  20,
  NULL,  // Free
  21,
  NULL,  // Art
  22, 
  NULL,  // Tech
};
int classIndex = 0;
int dayIndex = 0;

// returns the current day and class as a string
String getMessage() {
  return days[dayIndex] + ": " + classes[dayIndex][classIndex];
}

// print info on the LCD -- uses getMessage()
void print() {
  // Print the nwe LCD screen message
  lcd.clear();
  lcd.home();
  lcd.print (getMessage());
  // light up the appropriate LED
  int ledPin = getLedPin(classes[dayIndex][classIndex]);
  digitalWrite(ledPin, HIGH);
  delay (5000);  // 5 sec
  digitalWrite(ledPin, LOW);
}

// Moves to the next/prev class
// If it reaches the end, go to the other side
void loopClass(int increment) {
  classIndex += increment;
  if (classIndex < 0) classIndex = NUM_CLASSES - 1;
  else if (classIndex == NUM_CLASSES) classIndex = 0;
  if (
    (dayIndex == 3 || dayIndex == 4) && 
    classIndex >= 6
  ) classIndex = 0;
  print();
}

// Moves to the next/prev day
// If it reaches the end, go to the other side
// Also, reset the classIndex to 0
void loopDay(int increment) {
  dayIndex += increment;
  if (dayIndex < 0) dayIndex = NUM_DAYS - 1;
  else if (dayIndex == NUM_DAYS) dayIndex = 0;
  classIndex = 0;
  print();
}

int getLedPin(String name) {
  for (int index = 0; index < NUM_UNIQUE_CLASSES; index++) {
    if (uniqueClasses[index] == name) 
      return ledPins [index];
  }
} 

// Initialize the LCD and print to the screen
void setup() {
  lcd.begin(16, 2);
  for (int index = 0; index < NUM_UNIQUE_CLASSES; index++) 
    pinMode (ledPins [index], OUTPUT);
  print();
}

// Execute commands based on the button pressed
void loop() {
  char key = keypad.getKey();
  if (key == NULL) return;
  switch (key) {
    case 'A': loopClass (-1); break;
    case 'B': loopClass (1); break;
    case 'C': loopDay (-1); break;
    case 'D': loopDay (1); break;
  }
}
