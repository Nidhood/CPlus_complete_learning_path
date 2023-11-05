// Time library:
#include <time.h>

// Steps to implement the code:

// 1. Define pins for LEDs and buttons.
// 2. Set up the pins in the setup() function.
// 3.  Read the state of buttons in the loop() function.
// 4. If button1 is pressed:
// -----> a. Toggle the state of LED1.
// -----> b. Apply the new state to LED1.
// -----> c. Wait for a short time to avoid button bounce.
// 5. If button2 is pressed:
// -----> a. Toggle the state of LED2.
// -----> b. Apply the new state to LED2.
// -----> c. Wait for a short time to avoid button bounce.

// Define pins for LEDs and buttons:
const int pinLed1 = 2;
const int pinLed2 = 3;
const int pinButton1 = 4;
const int pinButton2 = 5;

// Variables to control time:
unsigned long startTime = 0;
unsigned long currentTime = 0;
unsigned long elapsedTime = 0;

// Calculate the ON time for a 3-second period with a 66% duty cycle:
const int onTime = 500;  // 500 milliseconds (0.5 seconds)

// Variables to store the state of LEDs:
int stateLed1 = LOW;
int stateLed2 = LOW;

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
  int stateButton1 = digitalRead(pinButton1);
  int stateButton2 = digitalRead(pinButton2);

  // Get the current time:
  currentTime = millis();

  // Check if button1 is pressed:
  if (stateButton1 == LOW) {
    // Wait for a short time to avoid multiple detections due to button bounce:
    if(currentTime - startTime > onTime){
      // Toggle the state of LED1:
      stateLed1 = !stateLed1;
      
      // Apply the new state to LED1:
      digitalWrite(pinLed1, stateLed1);

      // Reset the timer:
      startTime = currentTime;
    } 
  }

  // Check if button2 is pressed:
  if (stateButton2 == LOW) {
    // Wait for a short time to avoid multiple detections due to button bounce:
    if(currentTime - startTime > onTime){
      // Toggle the state of LED2:
      stateLed2 = !stateLed2;
      
      // Apply the new state to LED2:
      digitalWrite(pinLed2, stateLed2);

      // Reset the timer:
      startTime = currentTime;
    } 
  }
}
