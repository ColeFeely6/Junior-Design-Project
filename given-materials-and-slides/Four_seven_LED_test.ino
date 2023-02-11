/************************************************************************
 * four_seven_LED_test. This code demonstrates a 4 digit 7 segment LED display
 * by running through the numbers 000 - 999 and repeating. Thus code was 
 * written in C then modified for the setup() and loop() functions of the
 * Arduino IDE. Using Sparkfun COM-11409 common cathode 4 digit 7 segment 
 * display with data sheet here: https://www.sparkfun.com/products/11409
 * Revision History
 * Date         Author          Revision
 * 2/22/21      D.McLaughlin    initial C code "adc3DigitDisplay.c" for ECE-231 spring 2021
 * 2/15/22      D.McLaughlin    rewritten as Arduino script for ECE-304 demo spring 2022.
 *                              Tested using Arduino 1.8.19 on MacBook Pro i9, macOS Big Sur 11.6.3
 **************************************************************************/

#include "avr/io.h"
#include "util/delay.h"
#define DIG2 PB2    //enables DIG2. ATmega328P pin PB2/Arduino Uno pin 10
#define DIG3 PB1    //enables DIG3. ATmega328P pin PB1/Arduino Uno pin 9
#define DIG4 PB0    //enables DIG4. ATmega328P pin PB0/Arduino Uno pin 8

void disp3Digits(unsigned char, unsigned char, unsigned char);

void setup() {
    DDRD = 0xFF; //7segment pins
    DDRB = (1 << 2) | (1 << 1) | (1 << 0); //digit enables  
}

void loop() {
        unsigned char digit1, digit2, digit3;
        for (int value = 0; value<999; value++) {
            digit1 = value % 10;
            digit2 = (value / 10) % 10;
            digit3 = (value / 100);
            disp3Digits(digit1, digit2, digit3);
        }
}


/* Illuminate 3 digits of the 4 digit 7 segment display
* The 7 segments (a, b, c, d, e, f, g) correspond to ATmega328P pins D0-D7, 
* Arduino Uno pins 0-6. Enable pins DIG2, DIG3, DIG4 corresspond to PB0, PB1, PB0,
* which correspondsd to Arduino Uno pins 8, 9, 10 */
void disp3Digits(unsigned char d1, 
                 unsigned char d2,
                 unsigned char d3) {
    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
        0x07, 0x7F, 0x67};

    for (unsigned char i = 0; i < 5; i++) { //this code will refresh at 5x30=150 mS
        PORTD = ledDigits[d3]; //10's digit
        PORTB = (1 << DIG3) | (1 << DIG4); //enable DIG2, disable DIG3 & DIG4, 0000 0011
        _delay_ms(10);
        PORTD = ledDigits[d2] + 128; //1's digit w decimal pt
        PORTB = (1 << DIG2) | (1 << DIG4); //enable DIG3, disable DIG2,DIG4  0000 0101
        _delay_ms(10);
        PORTD = ledDigits[d1]; //0.1's digit
        PORTB = (1 << DIG2) | (1 << DIG3); //enable DIG4, disable DIG2,DIG3 0000 0110
        _delay_ms(10);
    }
    return;
}
