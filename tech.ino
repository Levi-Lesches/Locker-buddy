// TODO: implement faster scrolling for hold-down

// See README for wiring references

#include <Keypad.h>
#include <LiquidCrystal.h>

// Logical constants
#define NUM_CLASSES 10  // ignore Tefillah
#define NUM_DAYS 7
#define NUM_UNIQUE_CLASSES 14

// Button matrix constants
#define SWITCH 53
#define SWITCH_GND_1 51
#define SWITCH_GND_2 49
#define SWITCH_GND_3 47
#define SWITCH_GND_4 45
#define COLS 4
#define ROWS 1

// lcd pins: 
#define LCD_1 2
#define LCD_2 3
#define LCD_3 7
#define LCD_4 6
#define LCD_5 5
#define LCD_6 4

// Schedule constants:
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
const int ledPins[NUM_UNIQUE_CLASSES] = {  // skip 13, BUILT_IN
  8,
  9,
  10,
  NULL,  // Gym
  11,
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

// Wiring configuration
const byte rowPins [ROWS] = {SWITCH};
// button panel constants
// A, B --> class (top two)
// C, D --> day (bottom two)
const char inputs [ROWS] [COLS] = {
  {'D', 'B', 'C', 'A'}  // out of order b/c of wiring issues
};
const byte colPins [COLS] = {
  SWITCH_GND_1,
  SWITCH_GND_2,
  SWITCH_GND_3,
  SWITCH_GND_4,
};
Keypad keypad (makeKeymap (inputs), rowPins, colPins, ROWS, COLS);

// For regular lcds:
LiquidCrystal lcd(
  LCD_1,
  LCD_2,
  LCD_3,
  LCD_4,
  LCD_5,
  LCD_6
);

// For I2C chips: 
// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x3F, 16, 2);

int classIndex = 0;
int dayIndex = 0;
double timePassed;
int ledPin;

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
  ledPin = getLedPin(classes[dayIndex][classIndex]);
  timePassed = millis();
  digitalWrite (ledPin, HIGH);
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
  double time = millis();
  if ((time - timePassed) >= 3000)
    digitalWrite(ledPin, LOW);
  char key = keypad.getKey();
  if (key == NULL) return;
  // if (timePassed != 0)
  digitalWrite(ledPin, LOW);
  switch (key) {
    case 'A': loopClass (-1); break;
    case 'B': loopClass (1); break;
    case 'C': loopDay (-1); break;
    case 'D': loopDay (1); break;
  }
}
