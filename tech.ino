#include <LiquidCrystal.h>

#define NUM_CLASSES 3
#define NUM_DAYS 7

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const String classes[NUM_CLASSES] = {"English", "History", "Music"};
const String days[NUM_DAYS] = {"A", "B", "C", "E", "F", "R", "M"};
int classIndex = 0;
int dayIndex = 0;

void print() {
  lcd.clear();
  lcd.print (days[dayIndex] + ": " + classes[classIndex]);
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

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  Serial.begin (9600);
}

void loop() {
  loopClass(1);
  delay (1000);
  loopDay(1);
  delay (1000);
}