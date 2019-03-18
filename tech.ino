#define NUM_LED 2

const int led[NUM_LED] = {2, 3};
int index = 0;

void setup() {
	for (int index_ = 0; index_ < NUM_LED; index_++) 
		pinMode (led [index_], OUTPUT);
}

void loopIndex(int increment) {
	pinMode (led[index], LOW);
	index += increment;
	if (index < 0) index = NUM_LED;
	else if (index == NUM_LED) index = 0;
	pinMode (led[index], HIGH);
}

void loop() {
	loopIndex(1);
	delay (1000);
}