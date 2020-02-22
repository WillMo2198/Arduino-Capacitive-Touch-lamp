#include <CapacitiveSensor.h>
CapacitiveSensor cs_7_8 = CapacitiveSensor(2,7); //10M Resistor between pins 7 and 8, you may also connect an antenna on pin 8
unsigned long csSum;
const int led = 10;
int var = 0;

void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}

void loop() {
    CSread();
}

void CSread() {
    long cs = cs_7_8.capacitiveSensor(80); //a: Sensor resolution is set to 80
	if (cs > 500) { //b: Arbitrary number
		csSum += cs;
		Serial.println(csSum);
		while (csSum >= 5000 && var == 0) {
			digitalWrite(led, HIGH);
			var = 1;
			Serial.println("Pressed");
			if (csSum > 0) { csSum = 0; } //Reset
			cs_7_8.reset_CS_AutoCal(); //Stops readings
		}
		while (csSum >= 3800 && var == 1)  {
			digitalWrite(led, LOW);
			var = 0;
			if (csSum > 0) { csSum = 0; } //Reset
			cs_7_8.reset_CS_AutoCal(); //Stops readings
		}
	}
}