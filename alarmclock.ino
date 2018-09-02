/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            9

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability


const int BUTTON_PIN = 2;     // the number of the pushbutton pin
const int ENCODER_1 = 5;
const int ENCODER_2 = 6;

const int CLOCK_MODE = 0;
const int ALARM_SET_MODE = 1;
const int NUM_MODES = 2;

int button_debounce_counter = 0;
int last_press = 0;

int alarm_hour = 0;
int alarm_minute = 0;



int mode = 0;

int current_hour = 0;
int current_minute = 0;
int last_millis = millis();






Encoder myEnc(ENCODER_1, ENCODER_2);
//   avoid using pins with LEDs attached

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
    // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);
  pixels.begin(); // This initializes the NeoPixel library.
}

long oldPosition  = -999;

void loop() {
  
  handle_encoder();


  handle_button();

  update_time();
  
}


void handle_encoder(){
  
  
  
  long newPosition = myEnc.read();
  if (newPosition != oldPosition && mode == ALARM_SET_MODE) {

    if(newPosition > oldPosition){
      alarm_minute ++;
      if(alarm_minute >= 60){
        alarm_hour ++;
        alarm_hour = alarm_hour % 24;
        alarm_minute = 0;
      }
      
    }else{
      alarm_minute --;
      if(alarm_minute < 0){
        alarm_minute = 59;
        alarm_hour --;
        if(alarm_hour < 0){
          alarm_hour = 23;
        }
        
      }
    }

//    alarm_minute = 
    
    Serial.println(newPosition);

    Serial.print("Time: ");
    Serial.print(alarm_hour);
    Serial.print(":");
    Serial.println(alarm_minute);
    neopixel_set_time(alarm_hour, alarm_minute);

    oldPosition = newPosition;
  }
}

void handle_button(){
  
   // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
//    Serial.println("!!!");
    button_debounce_counter ++;
  } else {
    // turn LED off:
//    Serial.println("....");
    button_debounce_counter = 0;
//    digitalWrite(ledPin, LOW);
  }

  if (button_debounce_counter == 5000 && millis() > last_press + 500){
    button_debounce_counter = 0;
    last_press = millis();
    Serial.println("Button Pressed");
    mode ++;
    mode = mode % NUM_MODES;
    if(mode == CLOCK_MODE){
      
      Serial.println("Clock Mode");
      Serial.print("Current time: ");
       Serial.print(current_hour);
       Serial.print(":");
       Serial.println(current_minute);
      
      
    }else if(mode == ALARM_SET_MODE){
      
       Serial.println("Alarm Set Mode");
       
      
    }
   }


  
}

void update_time(){
  int current_millis = millis();
  if(current_millis > float(last_millis) + (1000.0 * 60.0)){
    last_millis = current_millis;
    current_minute ++;
    
    if(current_minute >= 60){
      current_minute = 0;
      current_hour ++;
      current_hour = current_hour % 24;
     }
   
   Serial.print("Current time: ");
   Serial.print(current_hour);
   Serial.print(":");
   Serial.println(current_minute);
  }
}



void neopixel_set_time(int hour, int minute){
  
  bool AM = hour < 12;
  hour = hour % 12;
  //AM case
  int num_hour_pixels = int(float(hour) * (float(NUMPIXELS) / 12.0));


  for(int pixel = 0; pixel < NUMPIXELS; pixel++){
    pixels.setPixelColor(pixel, pixels.Color(0, 0, 0));
  }
//  pixels.show(); // This sends the updated pixel color to the hardware.

  
  for(int pixel = 0; pixel< num_hour_pixels; pixel++){
    if(AM){
      pixels.setPixelColor(pixel, pixels.Color(255, 255, 255));
    }else{
       pixels.setPixelColor(pixel, pixels.Color(0, 0, 255));
    }
    
  }
  
  int minute_pixel = int(float(minute) * (float(NUMPIXELS)/60.0));

  pixels.setPixelColor(minute_pixel, pixels.Color(255,0,0));
  pixels.show(); // This sends the updated pixel color to the hardware.
  
}
