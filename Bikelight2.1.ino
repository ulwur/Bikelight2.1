#include <avr/sleep.h>
#include <avr/interrupt.h>

const int switchPin    = 3;
const int statusLED    = 1;
const int lystid       = 3 ;    //6 eller 60 sekunder
volatile int varv ;

void setup() {

    pinMode(switchPin, INPUT);
    digitalWrite(switchPin, HIGH);
    pinMode(statusLED, OUTPUT);

    GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
    PCMSK |= _BV(PCINT3);                   // Use PB3 as interrupt pin
    ADCSRA &= ~_BV(ADEN);                   // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement

    // Flash quick sequence so we know setup has started
//    for (int k = 0; k < 10; k = k + 1) {
//        if (k % 2 == 0) {
//            digitalWrite(statusLED, HIGH);
//            }
//        else {
//            digitalWrite(statusLED, LOW);
//            }
//        delay(250);
//        } // for
        digitalWrite(statusLED, HIGH);
    } // setup

void sleep() {
    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep
//vaknar här
    cli();                                  // Disable interrupts
    PCMSK &= ~_BV(PCINT3);                  // Turn off PB3 as interrupt pin
    sleep_disable();                        // Clear SE bit
    sei();                                  // Enable interrupts

} // sleep



ISR(PCINT3_vect) {
    // This is called when the interrupt occurs
    varv = lystid;   //Resetta räknaren
    }

void loop() {

   digitalWrite(statusLED, HIGH);

   varv = lystid;
     
   while (varv > 0 ) {
    delay(1000);
     varv-- ;
   } //end lyse    
   digitalWrite(statusLED, LOW);
   sleep();
}



