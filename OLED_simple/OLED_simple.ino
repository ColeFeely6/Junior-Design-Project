
/************************************************************* 
 *  OLED_simple.ino This code demonstrates the use of a small
 *  128 row x 64 column organic LED (OLED) display using a 4
 *  wire (VCC=5V, GND, SDA, SCL) I2C Interface. 
 *  First, install the Adafruit SSD1306 library using the
 *  library manager in your Arduino IDE. (You might be promoted to
 *  also install Adafruit GFX Library and the Adafruit BusIO library.
 *  Your Arduino IDE might be smart enough to tell you to install these.
 *  If not, and if this code doesn't compile, then install them 
 *  via the library manager.
 *  Date        Author            Revision
 *  10/31/21    D. McLaughlin     initial code write for Engin 100/Digital Ready
 *  2/15/22     D. McLaughlin     revised comments, prepared for ECE-304 Spring 2022
 *  ************************************************************/
#include <SPI.h>  
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128,64, &Wire, 4); 
int myCounter;  //this is the variable that will be displayed

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);  
  myCounter = 0;
}

void loop() {
  display.clearDisplay(); 
  display.setCursor(1,1);
  myCounter = myCounter +1;
  display.print("Counter value = ");
  display.println(myCounter);
  display.println("");
  display.println("Hey there.\nHave a nice day! :)");
  display.display();
  if (myCounter > 1000){
    myCounter = 0;
  }
  delay(100);
}

/************ End of File ***************/
