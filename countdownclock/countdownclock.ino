#include <FastLED.h>

#define LED_PER_DIGIT 39
#define DIGITS      3
#define LED_PIN     7
#define NUM_LEDS    LED_PER_DIGIT*DIGITS+2


int digits[10][39] = {
  {1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0}, // 0
  {0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,1,1, 1,1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0}, // 1
  {1,1,1,1,1,1, 0,0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1,1, 0,0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1}, // 2
  {0,0,0,0,0,0, 0,0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1}, // 3
  {0,0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0, 1,1,1,1,1,1, 1,1,1,1,1,1, 0,0,0,0,0, 1,1,1,1,1}, // 4
  {0,0,0,0,0,0, 1,1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0,0, 1,1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1}, // 5
  {1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0,0, 1,1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1}, // 6
  {0,0,0,0,0,0, 0,0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0}, // 7
  {1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1}, // 8
  {0,0,0,0,0,0, 1,1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1}, // 9
};

CRGB leds[NUM_LEDS];

void display_digit(int i, int k)
{
  int offset = (k-1)*LED_PER_DIGIT;
  
  for (int j=0; j<LED_PER_DIGIT; j++)
  {
    if(digits[i][j])
    {
      leds[j+offset] = CRGB(32, 0, 0);
    }  else {
      leds[j+offset] = CRGB(0, 0, 0);     
    }
  }  
}

const byte numChars = 4;        // 0:00
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;

void recv() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
   
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
//            Serial.print("received: ");Serial.println(rc);
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
//            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
//            Serial.print("string: ");Serial.println(receivedChars);
            newData = true;
        }
    }
}



void setup() {
Serial.begin(9600);
FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
leds[NUM_LEDS-2] = CRGB(32, 0, 0);
leds[NUM_LEDS-1] = CRGB(32, 0, 0);
}

void loop() {
  recv();
  if(newData)
  {
//    Serial.println("Showing new chars");
    display_digit(receivedChars[0]-'0', 1);
    display_digit(receivedChars[2]-'0', 2);
    display_digit(receivedChars[3]-'0', 3);
    FastLED.show();
    newData = false;
  }

/* DEMO
  for (int i = 0; i <= 9; i++)
  {
    display_digit(i, 1);
    FastLED.show();
    delay(1000);
  }
*/
}
