// Time library:
#include <time.h>

// Steps to implemente the code:

// 1. Define the pins for LEDs and buttons.
// 2. Set up the pins in the setup() function.
// 3. Read the state of buttons in the loop() function.
// 4. If either button is pressed, call the alternateBlink() function.
// 5. In t/Users/nidhood/Desktop/University/2023/Quinto semestre/Introducción a la programación Embebida/embebid/Arduino/Tarea1/punto_1/punto_1.inohe alternateBlink() function, calculate the ON time for the LEDs.
// 6. While either button is pressed:
// ----> a. Turn on LED1, wait for the ON time, and turn it off.
// ----> b. Check if button2 is still pressed, if not, break out of the loop.
// ----> c. Turn on LED2, wait for the ON time, and turn it off.

// Define pins for the LEDs and buttons:
const int pinLed1 = 2;
const int pinLed2 = 3;
const int pinButton1 = 4;
const int pinButton2 = 5;

// Variables to control time:
unsigned long startTime = 0;
unsigned long currentTime = 0;
unsigned long elapsedTime = 0;

// Calculate the ON time for a 3-second period with a 66% duty cycle:
const int onTime = 1980;  // 66% of 3000 milliseconds (3 seconds)
const int outTime = 1020; // 34% of 3000 milliseconfs (3 seconds)

// Variables to store the state of buttons:
int stateButton1 = LOW; 
int stateButton2 = LOW; 

// Initial configurations:
void setup() {
  
  // Configure LED pins as outputs:
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  
  // Configure button pins as inputs with pull-up resistors:
  pinMode(pinButton1, INPUT_PULLUP);
  pinMode(pinButton2, INPUT_PULLUP);
}

void loop() {

  // Read the state of buttons:
  stateButton1 = digitalRead(pinButton1);
  stateButton2 = digitalRead(pinButton2);

  // Check if either button is pressed:
  if (stateButton1 == LOW || stateButton2 == LOW) {

    // Call the function to alternate between LED1 and LED2 while the button is pressed:
    alternateBlink();
  }
}

// Function to alternate blinking between LED1 and LED2:
void alternateBlink() {

  // Get the current time:
  startTime = millis();

  // While either button is pressed:
  while (digitalRead(pinButton1) == LOW || digitalRead(pinButton2) == LOW) {

    // Update the current time:
    currentTime = millis();

    // Calculate the elapsed time:
    elapsedTime = currentTime - startTime;

    if (elapsedTime < onTime) {
      // Turn on LED1 (66%):
      digitalWrite(pinLed1, HIGH);
      digitalWrite(pinLed2, HIGH);
    } else if (elapsedTime < (onTime + outTime)) {
      // Turn off LEDs (34%):
      digitalWrite(pinLed1, LOW);
      digitalWrite(pinLed2, LOW);
    } else {
      // Reset the timer:
      startTime = millis();
    }
  }

  // Ensure both LEDs are turned off after the function ends:
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
}