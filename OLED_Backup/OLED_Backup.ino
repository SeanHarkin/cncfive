#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
Adafruit_SSD1306 display = Adafruit_SSD1306();                                                                  //This is all OLED Wing code
 
#if defined(ESP8266)
  #define BUTTON_A 0
  #define BUTTON_B 16
  #define BUTTON_C 2
  #define LED      0
#elif defined(ESP32)
  #define BUTTON_A 15
  #define BUTTON_B 32
  #define BUTTON_C 14
  #define LED      13
#elif defined(ARDUINO_STM32F2_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
  #define LED PB5
#elif defined(TEENSYDUINO)
  #define BUTTON_A 4
  #define BUTTON_B 3
  #define BUTTON_C 8
  #define LED 13
#elif defined(ARDUINO_FEATHER52)
  #define BUTTON_A 31
  #define BUTTON_B 30
  #define BUTTON_C 27
  #define LED 17
#else // 32u4, M0, and 328p
  #define BUTTON_A 9
  #define BUTTON_B 6
  #define BUTTON_C 5
  #define LED      13
#endif
 
#if (SSD1306_LCDHEIGHT != 32)
 #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int advice;                           //int to pull from our list of useful/less advice
bool push;                            //bool for 1 button push
 
void setup() {  
  Serial.begin(9600);
 
  Serial.println("OLED FeatherWing test");              // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);            // initialize with the I2C addr 0x3C (for the 128x32)
    // init done
  Serial.println("OLED begun");                         //More OLED wing specific code
  
  display.display();
  delay(1000);
 
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  
  Serial.println("IO test");
 
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
 
  display.setTextSize(1);                                 
  display.setTextColor(WHITE);                                    
  display.setCursor(0,0);
  display.print("Ask me for advice");
  display.setCursor(0,20);                                                                    //Set the question (Subject to change, possibly personalize?)
}
 
 
void loop() {

  if (! digitalRead(BUTTON_A)) ask();                                                         //If any of the buttons are pushed, ask for advice

  if (! digitalRead(BUTTON_B)) ask();

  if (! digitalRead(BUTTON_C)) ask();

  delay(10);
  yield();
  display.display();

    if (digitalRead(BUTTON_A) == LOW){                                                              // boolean functions to limit all the buttons to push = 1 value
    delay(100);                                                                                     
    push = !push;                                                                                   
    digitalWrite(BUTTON_A, push);                                                                   
  }
      if (digitalRead(BUTTON_B) == LOW){                                                            
    delay(100);                                                                                     
    push = !push;                                                                                   
    digitalWrite(BUTTON_B, push);                                                                   
  }
      if (digitalRead(BUTTON_C) == LOW){                                                           
    delay(100);                                                                                     
    push = !push;                                                                                   
    digitalWrite(BUTTON_C, push);                                                                   
  }
}

void ask(){

    display.clearDisplay();                                                   //If there has been previous advice,
    display.display();
    display.setCursor(0,0);                                                   //Reset the cursor position
    display.print("Ask me for advice");                                       //Reprint the question (Should always be shown)
    display.setCursor(0,20);                                                  //Set the cursor position for the answer
  
   advice = round(random(0,3));                                               //randomise what advice is called
  
  if (advice == 0){
  display.print("Hell Yeah!");                                                 //advice should be limited to 21char
  }
  if (advice == 1){
  display.print("That's a bad idea....");
  }
  if (advice == 2){
  display.print("What why?");
  }
}

  

