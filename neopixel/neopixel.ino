// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

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

int delayval = 10; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket

  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

//  for(int i=0;i<NUMPIXELS;i++){
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(0,10,0)); // Moderately bright green color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//  pulse_on(255, 0, 0);
//  pulse_off(0,255,0);
neopixel_set_time(14,10);
}

void pulse_on(int red, int green, int blue){
  for(int brightness = 0; brightness < 100; brightness++){
    for(int pixel = 0; pixel < NUMPIXELS; pixel ++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(pixel, pixels.Color(
        int(float(brightness)/100.0 * float(red)),
        int(float(brightness)/100.0 * float(green)),
        int(float(brightness)/100.0 * float(blue))
       )); 
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10); // Delay for a period of time (in milliseconds).
    
  }
}

void pulse_off(int red, int green, int blue){
  for(int brightness = 100; brightness > 0; brightness--){
    for(int pixel = 0; pixel < NUMPIXELS; pixel ++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(pixel, pixels.Color(
        int(float(brightness)/100.0 * float(red)),
        int(float(brightness)/100.0 * float(green)),
        int(float(brightness)/100.0 * float(blue))
       )); 
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10); // Delay for a period of time (in milliseconds).
    
  }
}

void neopixel_set_time(int hour, int minute){
  
  bool AM = hour < 12;
  hour = hour % 12;
  //AM case
  int num_hour_pixels = int(float(hour) * (float(NUMPIXELS) / 12.0));
  
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
