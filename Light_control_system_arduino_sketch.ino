// Pin assignments for LEDs
int redPin = 3;
int greenPin = 5;
int bluePin = 6;
int whitePin = 8;
int orangePin = 12;
int yellowPin = 13;

int rgb1R = 2;
int rgb1G = 4;
int rgb1B = 7;
int rgb2R = 9;
int rgb2G = 10;
int rgb2B = 11;

// Variables for the breath effect (solo LEDs)
bool isRedBreathing = false;
bool isGreenBreathing = false;
bool isBlueBreathing = false;

int breathDelay = 5;  // Speed of the transition (faster)
int brightness = 0;  // Current brightness of the LED
int breathDirection = 1;  // 1 for increasing, -1 for decreasing

// Variables for the second RGB LED breath effect
bool isRGB2Breathing = false;
bool isRGB2BreathingRed = false;
bool isRGB2BreathingGreen = false;
bool isRGB2BreathingBlue = false;
int breathDelayRGB2 = 5;  // Speed of the transition (faster)
int brightnessRGB2 = 0;  // Current brightness of the LED
int breathDirectionRGB2 = 1;  // 1 for increasing, -1 for decreasing

bool isBlinkActive = false;

unsigned long sosInterval = 100; // Time for each blink (short time for dots, long for dashes)
unsigned long sosPause = 1000; // Time to pause between SOS sequences
int BlinkState = 0; // Used to toggle SOS blinking pattern


bool isSOSActive = false;


// SOS state and timing for each LED
bool isRedSOS = false, isGreenSOS = false, isBlueSOS = false;
bool isRGB2SOS = false, isRGB1SOS = false;
bool isYellowSOS = false, isOrangeSOS = false, isWhiteSOS = false;

bool isRedBlink = false, isGreenBlink = false, isBlueBlink = false;
bool isRGB2Blink = false, isRGB1Blink = false;
bool isYellowBlink = false, isOrangeBlink = false, isWhiteBlink = false;

// Timing variables for SOS pattern
unsigned long lastSOSTimeRed, lastSOSTimeGreen, lastSOSTimeBlue;
unsigned long lastSOSTimeRGB2, lastSOSTimeRGB1;
unsigned long lastSOSTimeYellow, lastSOSTimeOrange, lastSOSTimeWhite;

unsigned long lastSOSTime = 0;
int sosBlinkState = 0; // Used to toggle SOS blinking pattern
unsigned long sosDotDuration = 400;  // Duration of a dot (short blink)
unsigned long sosDashDuration = 800; // Duration of a dash (long blink)
unsigned long sosPauseBetweenSymbols = 400; // Time to pause between each symbol (short gap between dots or dashes)
unsigned long sosPauseBetweenLetters = 400; // Time to pause between each letter (in SOS, S O S)
unsigned long sosCycleDuration = 0; // Time to track the entire cycle

bool isTestMode = false;
unsigned long testStartTime = 0;
unsigned long testDuration = 1000; // Duration of the first fast blink (1 second)
unsigned long testInterval = 100;  // Time for fast blink (100ms ON, 100ms OFF)
int testState = 0;  // To track the test state for the series of LED blinks

bool isRainbowActive = false;  // Default is OFF


int red_2           = 254;
int green_2         = 1;
int blue_2          = 127;
int red_2_direction = -1;
int green_2_direction = 1;
int blue_2_direction  = -1;

void setColor(int R, int G, int B, int pin2R, int pin2G, int pin2B) {
  analogWrite(pin2R, R);
  analogWrite(pin2G, G);
  analogWrite(pin2B, B);

}
 


void setup() {
  // Set all LED pins as OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(whitePin, OUTPUT);
  pinMode(orangePin, OUTPUT);
  pinMode(yellowPin, OUTPUT);

  pinMode(rgb1R, OUTPUT);
  pinMode(rgb1G, OUTPUT);
  pinMode(rgb1B, OUTPUT);
  
  pinMode(rgb2R, OUTPUT);
  pinMode(rgb2G, OUTPUT);
  pinMode(rgb2B, OUTPUT);

  Serial.begin(9600);  // Start serial communication
  
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Read the command from Serial

    // Solo color LEDs toggle on/off
    if (command == "red light" || command == "red" ) {
      toggleLED(redPin);
    } else if (command == "green light" || command == "green") {
      toggleLED(greenPin);
    } else if (command == "blue light" || command == "blue") {
      toggleLED(bluePin);
    } else if (command == "white light" || command == "white") {
      toggleLED(whitePin);
    } else if (command == "orange light" || command == "orange") {
      toggleLED(orangePin);
    } else if (command == "yellow light" || command == "yellow") {
      toggleLED(yellowPin);
    }

    // RGB LEDs control
    if (command == "first rgb red") {
      setRGBColor(rgb1R, rgb1G, rgb1B, 255, 0, 0);  // Set RGB1 to red
    } else if (command == "first rgb green") {
      setRGBColor(rgb1R, rgb1G, rgb1B, 0, 255, 0);  // Set RGB1 to green
    } else if (command == "first rgb blue") {
      setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 255);  // Set RGB1 to blue
    } else if (command == "first rgb magenta" || command == "first rgb magent") {
      setRGBColor(rgb1R, rgb1G, rgb1B, 255, 0, 255);  // Set RGB1 to magenta
    } else if (command == "first rgb yellow") {
      setRGBColor(rgb1R, rgb1G, rgb1B, 255, 255, 0);  // Set RGB1 to yellow
    } else if (command == "first rgb cyan" || command == "first rgb sign") {
      setRGBColor(rgb1R, rgb1G, rgb1B, 0, 255, 255);  // Set RGB1 to cyan
    } else if (command == "first rgb orange") {
      setRGBColor(rgb1R, rgb1G, rgb1B, 255, 165, 0);  // Set RGB1 to orange
    } else if (command == "first rgb white") {
      setRGBColor(rgb1R, rgb1G, rgb1B, 255, 255, 255);  // Set RGB1 to white
    } else if (command == "first rgb off" || command == "first rgb stop") {
      setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 0);  // Turn off RGB1
    }

    if (command == "second rgb red") {
      setRGBColor(rgb2R, rgb2G, rgb2B, 255, 0, 0);  // Set RGB2 to red
    } else if (command == "second rgb green") {
      setRGBColor(rgb2R, rgb2G, rgb2B, 0, 255, 0);  // Set RGB2 to green
    } else if (command == "second rgb blue") {
      setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 255);  // Set RGB2 to blue
    } else if (command == "second rgb magenta" || command == "second rgb magent") {
      setRGBColor(rgb2R, rgb2G, rgb2B, 255, 0, 255);  // Set RGB2 to magenta
    } else if (command == "second rgb yellow") {
      setRGBColor(rgb2R, rgb2G, rgb2B, 255, 255, 0);  // Set RGB2 to yellow
    } else if (command == "second rgb cyan" || command == "second rgb sign") {
      setRGBColor(rgb2R, rgb2G, rgb2B, 0, 255, 255);  // Set RGB2 to cyan
    } else if (command == "second rgb orange") {
      setRGBColor(rgb2R, rgb2G, rgb2B, 255, 165, 0);  // Set RGB2 to orange
    } else if (command == "second rgb white") {
      setRGBColor(rgb2R, rgb2G, rgb2B, 255, 255, 255);  // Set RGB2 to white
    } else if (command == "second rgb off" || command == "second rgb stop") {
      setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);  // Turn off RGB2
    }

    // Turn off all LEDs (solo and RGB)
    if (command == "lights out" || command == "lights off" || command == "stop") {
      turnOffAllLEDs();
    }

    // Individual breath effect toggle commands for solo LEDs
    if (command == "red breeze" || command == "red breath" ||command == "red breathe" || command == "red breast" || command == "red press" || command == "red fade" || command == "red phase" || command == "red bre") {
      isRedBreathing = !isRedBreathing;  // Toggle red LED breath effect
      if (!isRedBreathing) {
        analogWrite(redPin, 0);  // Turn off the red LED if effect is off
      }
    }
    if (command == "green breeze" || command == "green breath" ||command == "green breathe" || command == "green breast" || command == "green press" || command == "green fade" || command == "green phase" || command == "green bre") {
      isGreenBreathing = !isGreenBreathing;  // Toggle green LED breath effect
      if (!isGreenBreathing) {
        analogWrite(greenPin, 0);  // Turn off the green LED if effect is off
      }
    }
    if (command == "blue breeze" || command == "blue breath" ||command == "blue breathe" || command == "blue breast" || command == "blue press" || command == "blue fade" || command == "blue phase" || command == "blue bre" || command == "blueberries" || command == "blue bre") {
      isBlueBreathing = !isBlueBreathing;  // Toggle blue LED breath effect
      if (!isBlueBreathing) {
        analogWrite(bluePin, 0);  // Turn off the blue LED if effect is off
      }
    }

    // Breath effect for the second RGB LED
    if (command == "rgb breath" || command == "rgb breathe" || command == "rgb breast" || command == "rgb bre" || command == "rgb press") {
      isRGB2Breathing = !isRGB2Breathing;  // Toggle second RGB breath effect
      if (!isRGB2Breathing) {
        setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);  // Turn off second RGB if effect is off
      }
    }

        // Breath effect for the second RGB LED
    if (command == "rgb breast red" || command == "rgb breathe red" || command == "rgb breast red" || command == "rgb bre red" || command == "rgb press red") {
      isRGB2BreathingRed = !isRGB2BreathingRed;  // Toggle second RGB breath effect
      if (!isRGB2BreathingRed) {
        setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);  // Turn off second RGB if effect is off
      }
    }
       // Breath effect for the second RGB LED
    if (command == "rgb breast green" || command == "rgb breathe green" || command == "rgb breast green" || command == "rgb bre green" || command == "rgb press green") {
      isRGB2BreathingGreen = !isRGB2BreathingGreen;  // Toggle second RGB breath effect
      if (!isRGB2BreathingGreen) {
        setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);  // Turn off second RGB if effect is off
      }
    }
       // Breath effect for the second RGB LED
    if (command == "rgb breast blue" || command == "rgb breathe blue" || command == "rgb breast blue" || command == "rgb bre blue" || command == "rgb press blue") {
      isRGB2BreathingBlue = !isRGB2BreathingBlue;  // Toggle second RGB breath effect
      if (!isRGB2BreathingBlue) {
        setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);  // Turn off second RGB if effect is off
      }
    }

    // Toggle SOS effect on/off
    if (command == "blink" || command == "bl") {
      isBlinkActive = !isBlinkActive;  // Toggle the SOS effect
      if (!isBlinkActive) {
        turnOffAllLEDs();  // Turn off all LEDs if SOS is turned off
      }
    }
            // Test or verify command
    if (command == "test" || command == "verify" || command == "light test" || command == "lightest" || command == "light"|| command == "light check") {
      testLEDs();  // Trigger the test function
    }

    

     // Toggle SOS effect on/off
    if (command == "sos") {
      isSOSActive = !isSOSActive;  // Toggle the SOS effect
      if (!isSOSActive) {
        turnOffAllLEDs();  // Turn off all LEDs if SOS is turned off
      }
    }
    if (command == "green sos") {
      isGreenSOS = !isGreenSOS;
      if (!isGreenSOS) {
        digitalWrite(greenPin, LOW);  // Ensure green LED is off if SOS is stopped
      }
    }
    if (command == "blue sos") {
      isBlueSOS = !isBlueSOS;
      if (!isBlueSOS) {
        digitalWrite(bluePin, LOW);  // Ensure blue LED is off if SOS is stopped
      }
    }
    if (command == "second rgb sos") {
      isRGB2SOS = !isRGB2SOS;
      if (!isRGB2SOS) {
        setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);  // Turn off second RGB LED if SOS is stopped
      }
    }
    if (command == "first rgb sos") {
      isRGB1SOS = !isRGB1SOS;
      if (!isRGB1SOS) {
        setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 0);  // Turn off first RGB LED if SOS is stopped
      }
    }
    if (command == "yellow sos") {
      isYellowSOS = !isYellowSOS;
      if (!isYellowSOS) {
        digitalWrite(yellowPin, LOW);  // Ensure yellow LED is off if SOS is stopped
      }
    }
    if (command == "orange sos") {
      isOrangeSOS = !isOrangeSOS;
      if (!isOrangeSOS) {
        digitalWrite(orangePin, LOW);  // Ensure orange LED is off if SOS is stopped
      }
    }
    if (command == "white sos") {
      isWhiteSOS = !isWhiteSOS;
      if (!isWhiteSOS) {
        digitalWrite(whitePin, LOW);  // Ensure white LED is off if SOS is stopped
      }
    }
    if (command == "red sos") {
      isRedSOS = !isRedSOS;  // Toggle the SOS effect
      if (!isRedSOS) {
        digitalWrite(redPin, LOW);;  // Turn off all LEDs if SOS is turned off
      }
    }
    if ( command == "red blink" || command == "red bl"){
      isRedBlink = !isRedBlink;
      if (!isRedBlink) {
        digitalWrite(redPin, LOW); 
      }
    } 
    if ( command == "green blink" || command == "green bl"){
      isGreenBlink = !isGreenBlink;
      if (!isGreenBlink) {
        digitalWrite(greenPin, LOW); 
      }
    }     
    if ( command == "blue blink" || command == "blue bl"){
      isBlueBlink = !isBlueBlink;
      if (!isBlueBlink) {
        digitalWrite(bluePin, LOW); 
      }
    } 
    if ( command == "white blink" || command == "white bl"){
      isWhiteBlink = !isWhiteBlink;
      if (!isWhiteBlink) {
        digitalWrite(whitePin, LOW); 
      }
    } 
    if ( command == "orange blink" || command == "orange bl"){
      isOrangeBlink = !isOrangeBlink;
      if (!isOrangeBlink) {
        digitalWrite(orangePin, LOW); 
      }
    } 
    if ( command == "yellow blink" || command == "yellow bl"){
      isYellowBlink = !isYellowBlink;
      if (!isYellowBlink) {
        digitalWrite(yellowPin, LOW); 
      }
    } 
    if ( command == "first rgb blink" || command == "first rgb bl"){
      isRGB1Blink = !isRGB1Blink;
      if (!isRGB1Blink) {
        setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 0); 
      }
    }  
    if ( command == "second rgb blink" || command == "second rgb bl"){
      isRGB2Blink = !isRGB2Blink;
      if (!isRGB2Blink) {
        setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0); 
      }
    }
    if (command == "rgb rainbow" || command == "second rgb rainbow") {
      isRainbowActive = !isRainbowActive;
      if (!isRainbowActive) {
        setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0); 
      }
    }   
   
    // Existing LED control code continues here...   isRGB2Cycle

 
  }
  
  if (isRGB1Blink) {
    static unsigned long lastBlinkTimeRGB1 = 0;
    static int BlinkStateRGB1 = 0;
    static unsigned long sosIntervalRGB1 = 100; // Default interval
    unsigned long currentTime = millis();

    if (currentTime - lastBlinkTimeRGB1 >= sosIntervalRGB1) {
      lastBlinkTimeRGB1 = currentTime;

      // Fast Blink -> Delay -> Repeat
      switch (BlinkStateRGB1) {
        case 0: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 255, 0, 0);  // Red LED on (first fast blink)
          sosIntervalRGB1 = 100;  // Short duration for fast blink
          BlinkStateRGB1 = 1;
          break;
        case 1: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 0);  // Red LED off
          sosIntervalRGB1 = 100;  // Short duration for fast blink
          BlinkStateRGB1 = 2;
          break;
        case 2: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 255, 0, 0);  // Red LED on (second fast blink)
          sosIntervalRGB1 = 100;  // Short duration for fast blink
          BlinkStateRGB1 = 3;
          break;
        case 3: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 0);
          sosIntervalRGB1 = 500;  // Small delay before repeating
          BlinkStateRGB1 = 4;  // Proceed to next state
          break;
        case 4: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 255, 0);  // Green LED on (first fast blink)
          sosIntervalRGB1 = 100;  // Short duration for fast blink
          BlinkStateRGB1 = 5;
          break;
        case 5: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 0);  // Green LED off
          sosIntervalRGB1 = 100;  // Short duration for fast blink
          BlinkStateRGB1 = 6;
          break;
        case 6: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 255, 0);  // Green LED on (second fast blink)
          sosIntervalRGB1 = 100;  // Short duration for fast blink
          BlinkStateRGB1 = 7;
          break;
        case 7: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 0);
          sosIntervalRGB1 = 500;  // Small delay before repeating
          BlinkStateRGB1 = 8;  // Proceed to next state
          break;
        case 8: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 255);  // Blue LED on (first fast blink)
          sosIntervalRGB1 = 100;  // Short duration for fast blink
          BlinkStateRGB1 = 9;
          break;
        case 9: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 0);  // Blue LED off
          sosIntervalRGB1 = 100;  // Short duration for fast blink
          BlinkStateRGB1 = 10;
          break;
        case 10: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 255);  // Blue LED on (second fast blink)
          sosIntervalRGB1 = 100;  // Short duration for fast blink
          BlinkStateRGB1 = 11;
          break;
        case 11: 
          setRGBColor(rgb1R, rgb1G, rgb1B, 0, 0, 0);
          sosIntervalRGB1 = 500;  // Small delay before repeating
          BlinkStateRGB1 = 0;  // Reset to repeat the pattern
          break;
      }
    }
  }

  if (isRGB2Blink) {
    static unsigned long lastBlinkTimeRGB2 = 0;
    static int BlinkStateRGB2 = 0;
    static unsigned long sosIntervalRGB2 = 100; // Default interval
    unsigned long currentTime = millis();

    if (currentTime - lastBlinkTimeRGB2 >= sosIntervalRGB2) {
      lastBlinkTimeRGB2 = currentTime;

      // Fast Blink -> Delay -> Repeat
      switch (BlinkStateRGB2) {
        case 0: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 255, 0, 0);  // Red LED on (first fast blink)
          sosIntervalRGB2 = 100;  // Short duration for fast blink
          BlinkStateRGB2 = 1;
          break;
        case 1: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);  // Red LED off
          sosIntervalRGB2 = 100;  // Short duration for fast blink
          BlinkStateRGB2 = 2;
          break;
        case 2: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 255, 0, 0);  // Red LED on (second fast blink)
          sosIntervalRGB2 = 100;  // Short duration for fast blink
          BlinkStateRGB2 = 3;
          break;
        case 3: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);
          sosIntervalRGB2 = 500;  // Small delay before repeating
          BlinkStateRGB2 = 4;  // Proceed to next state
          break;
        case 4: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 255, 0);  // Green LED on (first fast blink)
          sosIntervalRGB2 = 100;  // Short duration for fast blink
          BlinkStateRGB2 = 5;
          break;
        case 5: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);  // Green LED off
          sosIntervalRGB2 = 100;  // Short duration for fast blink
          BlinkStateRGB2 = 6;
          break;
        case 6: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 255, 0);  // Green LED on (second fast blink)
          sosIntervalRGB2 = 100;  // Short duration for fast blink
          BlinkStateRGB2 = 7;
          break;
        case 7: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);
          sosIntervalRGB2 = 500;  // Small delay before repeating
          BlinkStateRGB2 = 8;  // Proceed to next state
          break;
        case 8: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 255);  // Blue LED on (first fast blink)
          sosIntervalRGB2 = 100;  // Short duration for fast blink
          BlinkStateRGB2 = 9;
          break;
        case 9: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);  // Blue LED off
          sosIntervalRGB2 = 100;  // Short duration for fast blink
          BlinkStateRGB2 = 10;
          break;
        case 10: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 255);  // Blue LED on (second fast blink)
          sosIntervalRGB2 = 100;  // Short duration for fast blink
          BlinkStateRGB2 = 11;
          break;
        case 11: 
          setRGBColor(rgb2R, rgb2G, rgb2B, 0, 0, 0);
          sosIntervalRGB2 = 500;  // Small delay before repeating
          BlinkStateRGB2 = 0;  // Reset to repeat the pattern
          break;
      }
    }
  }


  // Breath effect for red, green, and blue LEDs
  if (isRedBreathing) {
    breathEffect(redPin);
  }
  if (isGreenBreathing) {
    breathEffect(greenPin);
  }
  if (isBlueBreathing) {
    breathEffect(bluePin);
  }

  // Breath effect for second RGB LED (separate channels)
  if (isRGB2Breathing) {
    breathEffectRGB2(rgb2R);
    breathEffectRGB2(rgb2G);
    breathEffectRGB2(rgb2B);
  }
  if (isRGB2BreathingRed) {
    breathEffectRGB2(rgb2R);
  }
    if (isRGB2BreathingGreen) {
    breathEffectRGB2(rgb2G);
  }
    if (isRGB2BreathingBlue) {
    breathEffectRGB2(rgb2B);
  }

  // SOS effect logic
  if (isBlinkActive) {
    unsigned long currentTime = millis();

    if (currentTime - lastSOSTime >= sosInterval) {
      lastSOSTime = currentTime;

      // Fast Blink -> Delay -> Repeat
      switch (BlinkState) {
        case 0: 
          blinkAllLEDs(255);  // Turn LEDs on (fast blink)
          sosInterval = 100;  // Short duration for fast blink
          BlinkState = 1;
          break;
        case 1: 
          blinkAllLEDs(0);  // Turn LEDs off (fast blink)
          sosInterval = 100;  // Short duration for fast blink
          BlinkState = 2;
          break;
        case 2: 
          blinkAllLEDs(255);  // Turn LEDs on (fast blink)
          sosInterval = 100; 
          BlinkState = 3;
          break;
        case 3: 
          blinkAllLEDs(0);  // Turn LEDs off
          sosInterval = 500;  // Small delay before repeating
          BlinkState = 0;  // Reset to repeat the pattern
          break;
      }
    }
  }

  // Red blink logic
// Red blink logic
  if (isRedBlink) {
    static unsigned long lastBlinkTimeRed = 0;
    static int BlinkStateRed = 0;
    static unsigned long sosIntervalRed = 100; // Default interval
    unsigned long currentTime = millis();

    if (currentTime - lastBlinkTimeRed >= sosIntervalRed) {
      lastBlinkTimeRed = currentTime;

      // Fast Blink -> Delay -> Repeat
      switch (BlinkStateRed) {
        case 0: 
          analogWrite(redPin, 255);  // Turn LED on (first fast blink)
          sosIntervalRed = 100;  // Short duration for fast blink
          BlinkStateRed = 1;
          break;
        case 1: 
          analogWrite(redPin, 0);  // Turn LED off (after first blink)
          sosIntervalRed = 100;  // Short duration for fast blink
          BlinkStateRed = 2;
          break;
        case 2: 
          analogWrite(redPin, 255);  // Turn LED on (second fast blink)
          sosIntervalRed = 100;  // Short duration for fast blink
          BlinkStateRed = 3;
          break;
        case 3: 
          analogWrite(redPin, 0);  // Turn LED off (after second blink)
          sosIntervalRed = 500;  // Small delay before repeating
          BlinkStateRed = 0;  // Reset to repeat the pattern
          break;
      }
    }
  }
  if (isGreenBlink) {
    static unsigned long lastBlinkTimeGreen = 0;
    static int BlinkStateGreen = 0;
    static unsigned long sosIntervalGreen = 100; // Default interval
    unsigned long currentTime = millis();

    if (currentTime - lastBlinkTimeGreen >= sosIntervalGreen) {
      lastBlinkTimeGreen = currentTime;

      // Fast Blink -> Delay -> Repeat
      switch (BlinkStateGreen) {
        case 0: 
          analogWrite(greenPin, 255);  // Turn LED on (first fast blink)
          sosIntervalGreen = 100;  // Short duration for fast blink
          BlinkStateGreen = 1;
          break;
        case 1: 
          analogWrite(greenPin, 0);  // Turn LED off (after first blink)
          sosIntervalGreen = 100;  // Short duration for fast blink
          BlinkStateGreen = 2;
          break;
        case 2: 
          analogWrite(greenPin, 255);  // Turn LED on (second fast blink)
          sosIntervalGreen = 100;  // Short duration for fast blink
          BlinkStateGreen = 3;
          break;
        case 3: 
          analogWrite(greenPin, 0);  // Turn LED off (after second blink)
          sosIntervalGreen = 500;  // Small delay before repeating
          BlinkStateGreen = 0;  // Reset to repeat the pattern
          break;
      }
    }
  }
  if (isBlueBlink) {
    static unsigned long lastBlinkTimeBlue = 0;
    static int BlinkStateBlue = 0;
    static unsigned long sosIntervalBlue = 100; // Default interval
    unsigned long currentTime = millis();

    if (currentTime - lastBlinkTimeBlue >= sosIntervalBlue) {
      lastBlinkTimeBlue = currentTime;

      // Fast Blink -> Delay -> Repeat
      switch (BlinkStateBlue) {
        case 0: 
          analogWrite(bluePin, 255);  // Turn LED on (first fast blink)
          sosIntervalBlue = 100;  // Short duration for fast blink
          BlinkStateBlue = 1;
          break;
        case 1: 
          analogWrite(bluePin, 0);  // Turn LED off (after first blink)
          sosIntervalBlue = 100;  // Short duration for fast blink
          BlinkStateBlue = 2;
          break;
        case 2: 
          analogWrite(bluePin, 255);  // Turn LED on (second fast blink)
          sosIntervalBlue = 100;  // Short duration for fast blink
          BlinkStateBlue = 3;
          break;
        case 3: 
          analogWrite(bluePin, 0);  // Turn LED off (after second blink)
          sosIntervalBlue = 500;  // Small delay before repeating
          BlinkStateBlue = 0;  // Reset to repeat the pattern
          break;
      }    
    }
  }
  if (isWhiteBlink) {
      static unsigned long lastBlinkTimeWhite = 0;
      static int BlinkStateWhite = 0;
      static unsigned long sosIntervalWhite = 100; // Default interval
      unsigned long currentTime = millis();

      if (currentTime - lastBlinkTimeWhite >= sosIntervalWhite) {
          lastBlinkTimeWhite = currentTime;

          // Fast Blink -> Delay -> Repeat
          switch (BlinkStateWhite) {
              case 0: 
                  analogWrite(whitePin, 255);  // Turn LED on (first fast blink)
                  sosIntervalWhite = 100;  // Short duration for fast blink
                  BlinkStateWhite = 1;
                  break;
              case 1: 
                  analogWrite(whitePin, 0);  // Turn LED off (after first blink)
                  sosIntervalWhite = 100;  // Short duration for fast blink
                  BlinkStateWhite = 2;
                  break;
              case 2: 
                  analogWrite(whitePin, 255);  // Turn LED on (second fast blink)
                  sosIntervalWhite = 100;  // Short duration for fast blink
                  BlinkStateWhite = 3;
                  break;
              case 3: 
                  analogWrite(whitePin, 0);  // Turn LED off (after second blink)
                  sosIntervalWhite = 500;  // Small delay before repeating
                  BlinkStateWhite = 0;  // Reset to repeat the pattern
                  break;
          }
      }
  }
  if (isYellowBlink) {
      static unsigned long lastBlinkTimeYellow = 0;
      static int BlinkStateYellow = 0;
      static unsigned long sosIntervalYellow = 100; // Default interval
      unsigned long currentTime = millis();

      if (currentTime - lastBlinkTimeYellow >= sosIntervalYellow) {
          lastBlinkTimeYellow = currentTime;

          // Fast Blink -> Delay -> Repeat
          switch (BlinkStateYellow) {
              case 0: 
                  analogWrite(yellowPin, 255);  // Turn LED on (first fast blink)
                  sosIntervalYellow = 100;  // Short duration for fast blink
                  BlinkStateYellow = 1;
                  break;
              case 1: 
                  analogWrite(yellowPin, 0);  // Turn LED off (after first blink)
                  sosIntervalYellow = 100;  // Short duration for fast blink
                  BlinkStateYellow = 2;
                  break;
              case 2: 
                  analogWrite(yellowPin, 255);  // Turn LED on (second fast blink)
                  sosIntervalYellow = 100;  // Short duration for fast blink
                  BlinkStateYellow = 3;
                  break;
              case 3: 
                  analogWrite(yellowPin, 0);  // Turn LED off (after second blink)
                  sosIntervalYellow = 500;  // Small delay before repeating
                  BlinkStateYellow = 0;  // Reset to repeat the pattern
                  break;
          }
      }
  }
  if (isOrangeBlink) {
      static unsigned long lastBlinkTimeOrange = 0;
      static int BlinkStateOrange = 0;
      static unsigned long sosIntervalOrange = 100; // Default interval
      unsigned long currentTime = millis();

      if (currentTime - lastBlinkTimeOrange >= sosIntervalOrange) {
          lastBlinkTimeOrange = currentTime;

          // Fast Blink -> Delay -> Repeat
          switch (BlinkStateOrange) {
              case 0: 
                  analogWrite(orangePin, 255);  // Turn LED on (first fast blink)
                  sosIntervalOrange = 100;  // Short duration for fast blink
                  BlinkStateOrange = 1;
                  break;
              case 1: 
                  analogWrite(orangePin, 0);  // Turn LED off (after first blink)
                  sosIntervalOrange = 100;  // Short duration for fast blink
                  BlinkStateOrange = 2;
                  break;
              case 2: 
                  analogWrite(orangePin, 255);  // Turn LED on (second fast blink)
                  sosIntervalOrange = 100;  // Short duration for fast blink
                  BlinkStateOrange = 3;
                  break;
              case 3: 
                  analogWrite(orangePin, 0);  // Turn LED off (after second blink)
                  sosIntervalOrange = 500;  // Small delay before repeating
                  BlinkStateOrange = 0;  // Reset to repeat the pattern
                  break;
          }
      }
  }

  // SOS effect logic
  if (isSOSActive) {
    unsigned long currentTime = millis();

    if (currentTime - lastSOSTime >= sosCycleDuration) {
      lastSOSTime = currentTime;

      // SOS Blinking Pattern (S = short blink, O = long blink)
      // Pattern: S S S O O O S S S
      // Timing between symbols: 200ms, between letters: 600ms

      switch (sosBlinkState) {
        case 0: // First dot of S
          blinkAllLEDs(255);  // On (short blink)
          sosCycleDuration = sosDotDuration;  // Wait for short duration
          sosBlinkState = 1;
          break;
        case 1: // First off (pause after dot)
          blinkAllLEDs(0);  // Off
          sosCycleDuration = sosPauseBetweenSymbols;  // Short pause between dots
          sosBlinkState = 2;
          break;
        case 2: // Second dot of S
          blinkAllLEDs(255);  // On (short blink)
          sosCycleDuration = sosDotDuration;  // Wait for short duration
          sosBlinkState = 3;
          break;
        case 3: // Second off (pause after dot)
          blinkAllLEDs(0);  // Off
          sosCycleDuration = sosPauseBetweenSymbols;  // Short pause
          sosBlinkState = 4;
          break;
        case 4: // Third dot of S
          blinkAllLEDs(255);  // On (short blink)
          sosCycleDuration = sosDotDuration;  // Wait for short duration
          sosBlinkState = 5;
          break;
        case 5: // Pause between S and O (after three dots)
          blinkAllLEDs(0);  // Off
          sosCycleDuration = sosPauseBetweenLetters;  // Pause between letters
          sosBlinkState = 6;
          break;
        case 6: // First dash of O
          blinkAllLEDs(255);  // On (long blink)
          sosCycleDuration = sosDashDuration;  // Wait for long duration
          sosBlinkState = 7;
          break;
        case 7: // First off (pause after dash)
          blinkAllLEDs(0);  // Off
          sosCycleDuration = sosPauseBetweenSymbols;  // Pause between dashes
          sosBlinkState = 8;
          break;
        case 8: // Second dash of O
          blinkAllLEDs(255);  // On (long blink)
          sosCycleDuration = sosDashDuration;  // Wait for long duration
          sosBlinkState = 9;
          break;
        case 9: // Second off (pause after dash)
          blinkAllLEDs(0);  // Off
          sosCycleDuration = sosPauseBetweenSymbols;  // Pause between dashes
          sosBlinkState = 10;
          break;
        case 10: // Third dash of O
          blinkAllLEDs(255);  // On (long blink)
          sosCycleDuration = sosDashDuration;  // Wait for long duration
          sosBlinkState = 11;
          break;
        case 11: // Pause between O and S (after three dashes)
          blinkAllLEDs(0);  // Off
          sosCycleDuration = sosPauseBetweenLetters;  // Pause between letters
          sosBlinkState = 12;
          break;
        case 12: // First dot of S again
          blinkAllLEDs(255);  // On (short blink)
          sosCycleDuration = sosDotDuration;  // Wait for short duration
          sosBlinkState = 13;
          break;
        case 13: // First off (pause after dot)
          blinkAllLEDs(0);  // Off
          sosCycleDuration = sosPauseBetweenSymbols;  // Short pause between dots
          sosBlinkState = 14;
          break;
        case 14: // Second dot of S again
          blinkAllLEDs(255);  // On (short blink)
          sosCycleDuration = sosDotDuration;  // Wait for short duration
          sosBlinkState = 15;
          break;
        case 15: // Second off (pause after dot)
          blinkAllLEDs(0);  // Off
          sosCycleDuration = sosPauseBetweenSymbols;  // Short pause
          sosBlinkState = 16;
          break;
        case 16: // Third dot of S again
          blinkAllLEDs(255);  // On (short blink)
          sosCycleDuration = sosDotDuration;  // Wait for short duration
          sosBlinkState = 17;
          break;
        case 17: // Reset the SOS sequence back to the start
          blinkAllLEDs(0);  // Off
          sosCycleDuration = sosPauseBetweenLetters;  // Pause between cycles
          sosBlinkState = 0;  // Reset to start the SOS sequence over
          break;
      }
    }
  }


  // SOS effect logic
  if (isRedSOS) {
    unsigned long currentTime = millis();
    static unsigned long lastSOSTimeRed = 0;
    static int sosBlinkStateRed = 0;

    if (isRedSOS && currentTime - lastSOSTimeRed >= sosCycleDuration) {
      lastSOSTimeRed = currentTime;

      // SOS Blinking Pattern (S = short blink, O = long blink)
      // Pattern: S S S O O O S S S
      // Timing between symbols: 200ms, between letters: 600ms

      switch (sosBlinkStateRed) {
        case 0: 
          digitalWrite(redPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateRed = 1; 
          break;
        case 1: 
          digitalWrite(redPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateRed = 2; 
          break;
        case 2: 
          digitalWrite(redPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateRed = 3; 
          break;
        case 3: 
          digitalWrite(redPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateRed = 4; 
          break;
        case 4: 
          digitalWrite(redPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateRed = 5; 
          break;
        case 5: 
          digitalWrite(redPin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateRed = 6; 
          break;
        case 6: 
          digitalWrite(redPin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateRed = 7; 
          break;
        case 7: 
          digitalWrite(redPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateRed = 8; 
          break;
        case 8: 
          digitalWrite(redPin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateRed = 9; 
          break;
        case 9: 
          digitalWrite(redPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateRed = 10; 
          break;
        case 10: 
          digitalWrite(redPin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateRed = 11; 
          break;
        case 11: 
          digitalWrite(redPin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateRed = 12; 
          break;
        case 12: 
          digitalWrite(redPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateRed = 13; 
          break;
        case 13: 
          digitalWrite(redPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateRed = 14; 
          break;
        case 14: 
          digitalWrite(redPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateRed = 15; 
          break;
        case 15: 
          digitalWrite(redPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateRed = 16; 
          break;
        case 16: 
          digitalWrite(redPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateRed = 17; 
          break;
        case 17: 
          digitalWrite(redPin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateRed = 0;  // Reset SOS state for next cycle
          break;
        } 
    }
  }  


  // SOS effect logic
  if (isGreenSOS) {
    unsigned long currentTime = millis();
    static unsigned long lastSOSTimeGreen = 0;
    static int sosBlinkStateGreen = 0;

    if (isGreenSOS && currentTime - lastSOSTimeGreen >= sosCycleDuration) {
      lastSOSTimeGreen = currentTime;

      // SOS Blinking Pattern (S = short blink, O = long blink)
      // Pattern: S S S O O O S S S
      // Timing between symbols: 200ms, between letters: 600ms

      switch (sosBlinkStateGreen) {
        case 0: 
          digitalWrite(greenPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateGreen = 1; 
          break;
        case 1: 
          digitalWrite(greenPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateGreen = 2; 
          break;
        case 2: 
          digitalWrite(greenPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateGreen = 3; 
          break;
        case 3: 
          digitalWrite(greenPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateGreen = 4; 
          break;
        case 4: 
          digitalWrite(greenPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateGreen = 5; 
          break;
        case 5: 
          digitalWrite(greenPin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateGreen = 6; 
          break;
        case 6: 
          digitalWrite(greenPin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateGreen = 7; 
          break;
        case 7: 
          digitalWrite(greenPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateGreen = 8; 
          break;
        case 8: 
          digitalWrite(greenPin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateGreen = 9; 
          break;
        case 9: 
          digitalWrite(greenPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateGreen = 10; 
          break;
        case 10: 
          digitalWrite(greenPin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateGreen = 11; 
          break;
        case 11: 
          digitalWrite(greenPin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateGreen = 12; 
          break;
        case 12: 
          digitalWrite(greenPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateGreen = 13; 
          break;
        case 13: 
          digitalWrite(greenPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateGreen = 14; 
          break;
        case 14: 
          digitalWrite(greenPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateGreen = 15; 
          break;
        case 15: 
          digitalWrite(greenPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateGreen = 16; 
          break;
        case 16: 
          digitalWrite(greenPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateGreen = 17; 
          break;
        case 17: 
          digitalWrite(greenPin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateGreen = 0;  // Reset SOS state for next cycle
          break;
      } 
    }
  }  
  // SOS effect logic
  if (isBlueSOS) {
    static unsigned long lastSOSTimeBlue = 0;
    static int sosBlinkStateBlue = 0;
    unsigned long currentTime = millis();

    if (isBlueSOS && currentTime - lastSOSTimeBlue >= sosCycleDuration) {
      lastSOSTimeBlue = currentTime;

      // SOS Blinking Pattern (S = short blink, O = long blink)
      // Pattern: S S S O O O S S S
      // Timing between symbols: 200ms, between letters: 600ms

      switch (sosBlinkStateBlue) {
        case 0: 
          digitalWrite(bluePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateBlue = 1; 
          break;
        case 1: 
          digitalWrite(bluePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateBlue = 2; 
          break;
        case 2: 
          digitalWrite(bluePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateBlue = 3; 
          break;
        case 3: 
          digitalWrite(bluePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateBlue = 4; 
          break;
        case 4: 
          digitalWrite(bluePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateBlue = 5; 
          break;
        case 5: 
          digitalWrite(bluePin, LOW); 
        sosCycleDuration = sosPauseBetweenLetters; 
        sosBlinkStateBlue = 6; 
        break;
        case 6: 
          digitalWrite(bluePin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateBlue = 7; 
          break;
        case 7: 
          digitalWrite(bluePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateBlue = 8; 
          break;
        case 8: 
          digitalWrite(bluePin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateBlue = 9; 
          break;
        case 9: 
          digitalWrite(bluePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateBlue = 10; 
          break;
        case 10: 
          digitalWrite(bluePin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateBlue = 11; 
          break;
        case 11: 
          digitalWrite(bluePin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateBlue = 12; 
          break;
        case 12: 
          digitalWrite(bluePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateBlue = 13; 
          break;
        case 13: 
          digitalWrite(bluePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateBlue = 14; 
          break;
        case 14: 
          digitalWrite(bluePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateBlue = 15; 
          break;
        case 15: 
          digitalWrite(bluePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateBlue = 16; 
          break;
        case 16: 
          digitalWrite(bluePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateBlue = 17; 
          break;
        case 17: 
          digitalWrite(bluePin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateBlue = 0;  // Reset SOS state for next cycle
          break;
      }
    }
  }

  if (isWhiteSOS) {
  static unsigned long lastSOSTimeWhite = 0;
  static int sosBlinkStateWhite = 0;
  unsigned long currentTime = millis();

    if (isWhiteSOS && currentTime - lastSOSTimeWhite >= sosCycleDuration) {
      lastSOSTimeWhite = currentTime;

      // SOS Blinking Pattern (S = short blink, O = long blink)
      // Pattern: S S S O O O S S S
      // Timing between symbols: 200ms, between letters: 600ms

      switch (sosBlinkStateWhite) {
        case 0: 
          digitalWrite(whitePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateWhite = 1; 
          break;
        case 1: 
          digitalWrite(whitePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateWhite = 2; 
          break;
        case 2: 
          digitalWrite(whitePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateWhite = 3; 
          break;
        case 3: 
          digitalWrite(whitePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateWhite = 4; 
          break;
        case 4: 
          digitalWrite(whitePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateWhite = 5; 
          break;
        case 5: 
          digitalWrite(whitePin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateWhite = 6; 
          break;
        case 6: 
          digitalWrite(whitePin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateWhite = 7; 
          break;
        case 7: 
          digitalWrite(whitePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateWhite = 8; 
          break;
        case 8: 
          digitalWrite(whitePin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateWhite = 9; 
          break;
        case 9: 
          digitalWrite(whitePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateWhite = 10; 
          break;
        case 10: 
          digitalWrite(whitePin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateWhite = 11; 
          break;
        case 11: 
          digitalWrite(whitePin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateWhite = 12; 
          break;
        case 12: 
          digitalWrite(whitePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateWhite = 13; 
          break;
        case 13: 
          digitalWrite(whitePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateWhite = 14; 
          break;
        case 14: 
          digitalWrite(whitePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateWhite = 15; 
          break;
        case 15: 
          digitalWrite(whitePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateWhite = 16; 
          break;
        case 16: 
          digitalWrite(whitePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateWhite = 17; 
          break;
        case 17: 
          digitalWrite(whitePin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateWhite = 0;  // Reset SOS state for next cycle
          break;
      }
    }
  }
  if (isOrangeSOS) {
  static unsigned long lastSOSTimeOrange = 0;
  static int sosBlinkStateOrange = 0;
  unsigned long currentTime = millis();

    if (isOrangeSOS && currentTime - lastSOSTimeOrange >= sosCycleDuration) {
      lastSOSTimeOrange = currentTime;

      // SOS Blinking Pattern (S = short blink, O = long blink)
      // Pattern: S S S O O O S S S
      // Timing between symbols: 200ms, between letters: 600ms

      switch (sosBlinkStateOrange) {
        case 0: 
          digitalWrite(orangePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateOrange = 1; 
          break;
        case 1: 
          digitalWrite(orangePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateOrange = 2; 
          break;
        case 2: 
          digitalWrite(orangePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateOrange = 3; 
          break;
        case 3: 
          digitalWrite(orangePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateOrange = 4; 
          break;
        case 4: 
          digitalWrite(orangePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateOrange = 5; 
          break;
        case 5: 
          digitalWrite(orangePin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateOrange = 6; 
          break;
        case 6: 
          digitalWrite(orangePin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateOrange = 7; 
          break;
        case 7: 
          digitalWrite(orangePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateOrange = 8; 
          break;
        case 8: 
          digitalWrite(orangePin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateOrange = 9; 
        break;
        case 9: 
          digitalWrite(orangePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateOrange = 10; 
          break;
        case 10: 
          digitalWrite(orangePin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateOrange = 11; 
          break;
        case 11: 
          digitalWrite(orangePin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateOrange = 12; 
          break;
        case 12: 
          digitalWrite(orangePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateOrange = 13; 
          break;
        case 13: 
          digitalWrite(orangePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateOrange = 14; 
          break;
        case 14: 
          digitalWrite(orangePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateOrange = 15; 
          break;
        case 15: 
          digitalWrite(orangePin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateOrange = 16; 
          break;
        case 16: 
          digitalWrite(orangePin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateOrange = 17; 
          break;
        case 17: 
          digitalWrite(orangePin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateOrange = 0;  // Reset SOS state for next cycle
          break;
      }
    }
  }  
  if (isYellowSOS) {
   static unsigned long lastSOSTimeYellow = 0;
   static int sosBlinkStateYellow = 0;
   unsigned long currentTime = millis();

    if (isYellowSOS && currentTime - lastSOSTimeYellow >= sosCycleDuration) {
      lastSOSTimeYellow = currentTime;

      // SOS Blinking Pattern (S = short blink, O = long blink)
      // Pattern: S S S O O O S S S
      // Timing between symbols: 200ms, between letters: 600ms

      switch (sosBlinkStateYellow) {
        case 0: 
          digitalWrite(yellowPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateYellow = 1; 
          break;
        case 1: 
          digitalWrite(yellowPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateYellow = 2; 
          break;
        case 2: 
          digitalWrite(yellowPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateYellow = 3; 
          break;
        case 3: 
          digitalWrite(yellowPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateYellow = 4; 
          break;
        case 4: 
          digitalWrite(yellowPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateYellow = 5; 
          break;
        case 5: 
          digitalWrite(yellowPin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateYellow = 6; 
          break;
        case 6: 
          digitalWrite(yellowPin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateYellow = 7; 
          break;
        case 7: 
          digitalWrite(yellowPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateYellow = 8; 
          break;
        case 8: 
          digitalWrite(yellowPin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateYellow = 9; 
          break;
        case 9: 
          digitalWrite(yellowPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateYellow = 10; 
          break;
        case 10: 
          digitalWrite(yellowPin, HIGH); 
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateYellow = 11; 
          break;
        case 11: 
          digitalWrite(yellowPin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateYellow = 12; 
          break;
        case 12: 
          digitalWrite(yellowPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateYellow = 13; 
          break;
        case 13: 
          digitalWrite(yellowPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateYellow = 14; 
          break;
        case 14: 
          digitalWrite(yellowPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateYellow = 15; 
          break;
        case 15: 
          digitalWrite(yellowPin, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateYellow = 16; 
          break;
        case 16: 
          digitalWrite(yellowPin, HIGH); 
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateYellow = 17; 
          break;
        case 17: 
          digitalWrite(yellowPin, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateYellow = 0;  // Reset SOS state for next cycle
          break;
      }
    }
  }
  if (isRGB1SOS) {
    static unsigned long lastSOSTimeFirstRGB = 0;
    static int sosBlinkStateFirstRGB = 0;
    unsigned long currentTime = millis();

    if (isRGB1SOS && currentTime - lastSOSTimeFirstRGB >= sosCycleDuration) {
      lastSOSTimeFirstRGB = currentTime;

      // SOS Blinking Pattern (S = short blink, O = long blink)
      // Pattern: S S S O O O S S S
      // Timing between symbols: 200ms, between letters: 600ms

      switch (sosBlinkStateFirstRGB) {
        case 0: 
          digitalWrite(rgb1R, HIGH);
          digitalWrite(rgb1G, HIGH);
          digitalWrite(rgb1B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateFirstRGB = 1; 
          break;
        case 1: 
          digitalWrite(rgb1R, LOW);
          digitalWrite(rgb1G, LOW);
          digitalWrite(rgb1B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateFirstRGB = 2; 
          break;
        case 2: 
          digitalWrite(rgb1R, HIGH);
          digitalWrite(rgb1G, HIGH);
          digitalWrite(rgb1B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateFirstRGB = 3; 
          break;
        case 3: 
          digitalWrite(rgb1R, LOW);
          digitalWrite(rgb1G, LOW);
          digitalWrite(rgb1B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateFirstRGB = 4; 
          break;
        case 4: 
          digitalWrite(rgb1R, HIGH);
          digitalWrite(rgb1G, HIGH);
          digitalWrite(rgb1B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateFirstRGB = 5; 
          break;
        case 5: 
          digitalWrite(rgb1R, LOW);
          digitalWrite(rgb1G, LOW);
          digitalWrite(rgb1B, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateFirstRGB = 6; 
          break;
        case 6: 
          digitalWrite(rgb1R, HIGH);
          digitalWrite(rgb1G, HIGH);
          digitalWrite(rgb1B, HIGH);
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateFirstRGB = 7; 
          break;
        case 7: 
          digitalWrite(rgb1R, LOW);
          digitalWrite(rgb1G, LOW);
          digitalWrite(rgb1B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateFirstRGB = 8; 
          break;
        case 8: 
          digitalWrite(rgb1R, HIGH);
          digitalWrite(rgb1G, HIGH);
          digitalWrite(rgb1B, HIGH);
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateFirstRGB = 9; 
          break;
        case 9: 
          digitalWrite(rgb1R, LOW);
          digitalWrite(rgb1G, LOW);
          digitalWrite(rgb1B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateFirstRGB = 10; 
          break;
        case 10: 
          digitalWrite(rgb1R, HIGH);
          digitalWrite(rgb1G, HIGH);
          digitalWrite(rgb1B, HIGH);
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateFirstRGB = 11; 
          break;
        case 11: 
          digitalWrite(rgb1R, LOW);
          digitalWrite(rgb1G, LOW);
          digitalWrite(rgb1B, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateFirstRGB = 12; 
          break;
        case 12: 
          digitalWrite(rgb1R, HIGH);
          digitalWrite(rgb1G, HIGH);
          digitalWrite(rgb1B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateFirstRGB = 13; 
          break;
        case 13: 
          digitalWrite(rgb1R, LOW);
          digitalWrite(rgb1G, LOW);
          digitalWrite(rgb1B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateFirstRGB = 14; 
          break;
        case 14: 
          digitalWrite(rgb1R, HIGH);
          digitalWrite(rgb1G, HIGH);
          digitalWrite(rgb1B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateFirstRGB = 15; 
          break;
        case 15: 
          digitalWrite(rgb1R, LOW);
          digitalWrite(rgb1G, LOW);
          digitalWrite(rgb1B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateFirstRGB = 16; 
          break;
        case 16: 
          digitalWrite(rgb1R, HIGH);
          digitalWrite(rgb1G, HIGH);
          digitalWrite(rgb1B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateFirstRGB = 17; 
          break;
        case 17: 
          digitalWrite(rgb1R, LOW);
          digitalWrite(rgb1G, LOW);
          digitalWrite(rgb1B, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateFirstRGB = 0;  // Reset SOS state for next cycle
          break;
      }
    }
  }
  if (isRGB2SOS) {
    static unsigned long lastSOSTimeSecondRGB = 0;
    static int sosBlinkStateSecondRGB = 0;
    unsigned long currentTime = millis();

    if (isRGB2SOS && currentTime - lastSOSTimeSecondRGB >= sosCycleDuration) {
      lastSOSTimeSecondRGB = currentTime;

      // SOS Blinking Pattern (S = short blink, O = long blink)
      // Pattern: S S S O O O S S S
      // Timing between symbols: 200ms, between letters: 600ms

      switch (sosBlinkStateSecondRGB) {
        case 0: 
          digitalWrite(rgb2R, HIGH);
          digitalWrite(rgb2G, HIGH);
          digitalWrite(rgb2B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateSecondRGB = 1; 
          break;
        case 1: 
          digitalWrite(rgb2R, LOW);
          digitalWrite(rgb2G, LOW);
          digitalWrite(rgb2B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateSecondRGB = 2; 
          break;
        case 2: 
          digitalWrite(rgb2R, HIGH);
          digitalWrite(rgb2G, HIGH);
          digitalWrite(rgb2B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateSecondRGB = 3; 
          break;
        case 3: 
          digitalWrite(rgb2R, LOW);
          digitalWrite(rgb2G, LOW);
          digitalWrite(rgb2B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateSecondRGB = 4; 
          break;
        case 4: 
          digitalWrite(rgb2R, HIGH);
          digitalWrite(rgb2G, HIGH);
          digitalWrite(rgb2B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateSecondRGB = 5; 
          break;
        case 5: 
          digitalWrite(rgb2R, LOW);
          digitalWrite(rgb2G, LOW);
          digitalWrite(rgb2B, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateSecondRGB = 6; 
          break;
        case 6: 
          digitalWrite(rgb2R, HIGH);
          digitalWrite(rgb2G, HIGH);
          digitalWrite(rgb2B, HIGH);
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateSecondRGB = 7; 
          break;
        case 7: 
          digitalWrite(rgb2R, LOW);
          digitalWrite(rgb2G, LOW);
          digitalWrite(rgb2B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateSecondRGB = 8; 
          break;
        case 8: 
          digitalWrite(rgb2R, HIGH);
          digitalWrite(rgb2G, HIGH);
          digitalWrite(rgb2B, HIGH);
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateSecondRGB = 9; 
          break;
        case 9: 
          digitalWrite(rgb2R, LOW);
          digitalWrite(rgb2G, LOW);
          digitalWrite(rgb2B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateSecondRGB = 10; 
          break;
        case 10: 
          digitalWrite(rgb2R, HIGH);
          digitalWrite(rgb2G, HIGH);
          digitalWrite(rgb2B, HIGH);
          sosCycleDuration = sosDashDuration; 
          sosBlinkStateSecondRGB = 11; 
          break;
        case 11: 
          digitalWrite(rgb2R, LOW);
          digitalWrite(rgb2G, LOW);
          digitalWrite(rgb2B, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateSecondRGB = 12; 
          break;
        case 12: 
          digitalWrite(rgb2R, HIGH);
          digitalWrite(rgb2G, HIGH);
          digitalWrite(rgb2B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateSecondRGB = 13; 
          break;
        case 13: 
          digitalWrite(rgb2R, LOW);
          digitalWrite(rgb2G, LOW);
          digitalWrite(rgb2B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateSecondRGB = 14; 
          break;
        case 14: 
          digitalWrite(rgb2R, HIGH);
          digitalWrite(rgb2G, HIGH);
          digitalWrite(rgb2B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateSecondRGB = 15; 
          break;
        case 15: 
          digitalWrite(rgb2R, LOW);
          digitalWrite(rgb2G, LOW);
          digitalWrite(rgb2B, LOW); 
          sosCycleDuration = sosPauseBetweenSymbols; 
          sosBlinkStateSecondRGB = 16; 
          break;
        case 16: 
          digitalWrite(rgb2R, HIGH);
          digitalWrite(rgb2G, HIGH);
          digitalWrite(rgb2B, HIGH);
          sosCycleDuration = sosDotDuration; 
          sosBlinkStateSecondRGB = 17; 
          break;
        case 17: 
          digitalWrite(rgb2R, LOW);
          digitalWrite(rgb2G, LOW);
          digitalWrite(rgb2B, LOW); 
          sosCycleDuration = sosPauseBetweenLetters; 
          sosBlinkStateSecondRGB = 0;  // Reset SOS state for next cycle
          break;
      }
    }
  }

  if (isRainbowActive) {
    // Second RGB LED (looping colors)
    red_2 = red_2 + red_2_direction;   
    green_2 = green_2 + green_2_direction;
    blue_2 = blue_2 + blue_2_direction;
 
    // Change direction for each color if it reaches 255
    if (red_2 >= 255 || red_2 <= 0) {
      red_2_direction = red_2_direction * -1;
    }
    if (green_2 >= 255 || green_2 <= 0) {
      green_2_direction = green_2_direction * -1;
    }
    if (blue_2 >= 255 || blue_2 <= 0) {
      blue_2_direction = blue_2_direction * -1;
    }
    setColor(red_2, green_2, blue_2, rgb2R, rgb2G, rgb2B);
  }
  delay(5);

}



// Function to blink all LEDs (used for SOS effect)
void blinkAllLEDs(int brightness) {
  analogWrite(redPin, brightness);
  analogWrite(greenPin, brightness);
  analogWrite(bluePin, brightness);
  analogWrite(whitePin, brightness);
  analogWrite(orangePin, brightness);
  analogWrite(yellowPin, brightness);
  analogWrite(rgb1R, brightness);
  analogWrite(rgb1G, brightness);
  analogWrite(rgb1B, brightness);
  analogWrite(rgb2R, brightness);
  analogWrite(rgb2G, brightness);
  analogWrite(rgb2B, brightness);
}




void breathEffect(int pin) {
  brightness += breathDirection * breathDelay;  // Increase or decrease brightness

  if (brightness >= 255 || brightness <= 0) {
    breathDirection = -breathDirection;  // Reverse the direction of brightness change
  }

  analogWrite(pin, brightness);  // Set the LED brightness

  delay(30);  // Small delay for smooth transition
}

// Function to create the breathing effect for second RGB LED channels
void breathEffectRGB2(int pin) {
  brightnessRGB2 += breathDirectionRGB2 * breathDelayRGB2;  // Increase or decrease brightness

  if (brightnessRGB2 >= 255 || brightnessRGB2 <= 0) {
    breathDirectionRGB2 = -breathDirectionRGB2;  // Reverse the direction of brightness change
  }

  analogWrite(pin, brightnessRGB2);  // Set the LED brightness

  delay(30);  // Small delay for smooth transition
}

// Helper function to set RGB color
void setRGBColor(int rPin, int gPin, int bPin, int rValue, int gValue, int bValue) {
  analogWrite(rPin, rValue);
  analogWrite(gPin, gValue);
  analogWrite(bPin, bValue);
}

// Helper function to toggle LEDs (on or off)
void toggleLED(int pin) {
  int currentState = digitalRead(pin);
  if (currentState == HIGH) {
    digitalWrite(pin, LOW);
  } else {
    digitalWrite(pin, HIGH);
  }
}

// Function to blink all LEDs (used for SOS effect)


void sosAllLEDs(int brightness) {
  analogWrite(redPin, brightness);
  analogWrite(greenPin, brightness);
  analogWrite(bluePin, brightness);
  analogWrite(whitePin, brightness);
  analogWrite(orangePin, brightness);
  analogWrite(yellowPin, brightness);
  analogWrite(rgb1R, brightness);
  analogWrite(rgb1G, brightness);
  analogWrite(rgb1B, brightness);
  analogWrite(rgb2R, brightness);
  analogWrite(rgb2G, brightness);
  analogWrite(rgb2B, brightness);
}

// Helper function to blink individual LED
void blinkLED(int pin, int brightness) {
  analogWrite(pin, brightness);
  delay(testInterval);
  analogWrite(pin, 0);
}

// Helper function to blink RGB LEDs individually
void blinkRGB(int pin, int brightness) {
  analogWrite(pin, brightness);
  delay(testInterval);
  analogWrite(pin, 0);
}

void turnOffAllLEDs() 
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  analogWrite(whitePin, 0);
  analogWrite(orangePin, 0);
  analogWrite(yellowPin, 0);
  analogWrite(rgb1R, 0);
  analogWrite(rgb1G, 0);
  analogWrite(rgb1B, 0);
  analogWrite(rgb2R, 0);
  analogWrite(rgb2G, 0);
  analogWrite(rgb2B, 0);
  isRGB2Breathing = false;
  isRGB2BreathingRed = false;
  isRGB2BreathingGreen = false;
  isRGB2BreathingBlue = false;
  isRedBreathing = false;
  isGreenBreathing = false;
  isBlueBreathing = false;
  isRedSOS = false, isGreenSOS = false, isBlueSOS = false;
  isRGB2SOS = false, isRGB1SOS = false;
  isYellowSOS = false, isOrangeSOS = false, isWhiteSOS = false;
  isBlinkActive = false;
  isSOSActive = false;
  isRedBlink = false, isGreenBlink = false, isBlueBlink = false;
  isRGB2Blink = false, isRGB1Blink = false;
  isYellowBlink = false, isOrangeBlink = false, isWhiteBlink = false;
  isRainbowActive = false;
}
void testLEDs() {
  int ledSequence[] = {redPin, greenPin, bluePin, rgb2R, rgb2G, rgb2B, yellowPin, orangePin, whitePin, rgb1R, rgb1G, rgb1B};

  // Blink all LEDs quickly for 1 second
  unsigned long startTime = millis();
  while (millis() - startTime < 1000) {  // Blink for 1 second
    for (int i = 0; i < 12; i++) {
      digitalWrite(ledSequence[i], HIGH);  // Turn on the LED
    }
    delay(100);  // 100ms on time
    for (int i = 0; i < 12; i++) {
      digitalWrite(ledSequence[i], LOW);   // Turn off all LEDs
    }
    delay(70);  // 100ms off time
  }

  // Blink each LED twice in the sequence
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 2; j++) {  // Blink each LED twice
      digitalWrite(ledSequence[i], HIGH);  // Turn on the LED
      delay(100);  // 100ms on time
      digitalWrite(ledSequence[i], LOW);   // Turn off the LED
      delay(50);  // 100ms off time
    }
  }
}


