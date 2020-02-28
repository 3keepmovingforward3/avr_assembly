#include <avr/io.h>
#include <avr/interrupt.h>

#include "avr/iom324pb.h"
#include "SSD1306.h"

// Function Prototypes
//
inline void pwm_setup(void);
inline void board_setup(void);
inline void timer_setup(void);
inline void external_interrupt_setup(void);

// Global variables
// volatile keyword must be used for variables inside ISR blocks
// IF you are leaving GCC optimizations enabled
//
volatile uint8_t hold_counter; // represents RPM
volatile int counter; // represents number of external interrupts
volatile uint8_t button_step; // represents the +10% duty cycle steps for incremental PWM selection

//////////////////////////////////////////////////////////////////////////
// Driver
//////////////////////////////////////////////////////////////////////////
int main(void)
{
OLED_Init();  //initialize the OLED
    board_setup();
    pwm_setup();
timer_setup();
    external_interrupt_setup();

sei();// Set Interrupt Flag
    while (1){
    }
}

//////////////////////////////////////////////////////////////////////////
// Non-delineated Board Setup
//////////////////////////////////////////////////////////////////////////
void board_setup(){
    // Setting I/O Direction & Pull-Up Resistor Enabling
    //
    DDRA |= (1<<PINA6); // To show the one sec timer for debugging

    // PE2 pin set as output
    // the output of PE2 is directly tied to a PWM generation circuit
    //
    DDRE |= (1<<PINE2);

    // PWM Generation Pin as Output
    //
    DDRD |= (1<<PIND7);

    // PWM/INT0 generation pin pull-up
    //
    PORTD |= (1<<PIND2)|(1<<PIND7);

    // Push Button
    // Push-Button = PC6
    //
    PORTC = (1<<PINC6);
}

//////////////////////////////////////////////////////////////////////////
// PWM Output Setup
//////////////////////////////////////////////////////////////////////////
void pwm_setup(){
    // Initialize PWM to 50% duty cycle round(255/127)
    // Initialize counter
    //
    OCR2A = 127;

    // Non-inverting Fast PWM Mode 7
    // START the PWM timer with 64 Pre-scaler
    // I/O Clock @ 16 MHz
    //
    TCCR2A |= (1<<WGM21)|(1<<WGM20)|(1<<COM2A1);
    TCCR2B |= (1<<CS22)|(0<<CS21)|(1<<CS20);
}

//////////////////////////////////////////////////////////////////////////
// One Second Timer Setup
//////////////////////////////////////////////////////////////////////////
void timer_setup(){
    // Enable Timer4 Overflow Interrupt
    //
    TIMSK4 |= (1<<TOIE4);

    // Normal Mode
    //
    TCCR4A |= (1<<COM4A1); // Clear on channel 4A compare match, //N
    TCCR4B |= (1<<CS42)|(0<<CS41)|(0<<CS40); // 1024 clock prescaler

    // 0x3D09 = 15,625
    //
    OCR4AH = 0x3D;
    OCR4AL = 0x09;

    TCNT4 = 0x00; // reset 1 sec counter
}

//////////////////////////////////////////////////////////////////////////
// External Interrupt/Counter Setup
//////////////////////////////////////////////////////////////////////////
void external_interrupt_setup(){
    // Enable External Interrupt Zero by setting
    // the INT0 bit high
    //
    EIMSK = (1<<INT0);

    // INT0 will activate on the rising edge of a trigger
    //
    EICRA = 0X02;
}


ISR(INT0_vect, ISR_BLOCK){
    // Accumulator for rpm calculation
    //
counter++;
}

ISR(TIMER4_OVF_vect){
PORTA ^= (1<<PINA6);
    // Settings Control with button
    //
    if (PINC == 0x80){
        if(button_step <= 10){
            button_step++;
        }
    }
    if(button_step > 10){
        button_step = 0;
    }

    // Sets duty cycle to a rounded_floor percentage ~10%
    // 255 is the MAX value for 8-bit PWM signal
    // Use floor to force integer
    //
    OCR2A = floor(255*button_step*0.1);

    // Actual RPM value
    // Divided by 2 because there are two interrupts per rotation
    // Multiplied by sixty to extrapolate to RPM

    hold_counter=(counter/2)*60;    // for rpm

    // LCD Output
    //
OLED_DisplayString("RPM: ");
OLED_DisplayNumber(C_DECIMAL_U8, counter, 3);
OLED_GoToNextLine();
OLED_DisplayString("Duty Cycle: ");
OLED_DisplayNumber(E_DECIMAL, button_step*10, 3);
    OLED_DisplayString("%");
    OLED_GoToNextLine();
    OLED_DisplayString("OCR2A: ");
    OLED_DisplayNumber(E_DECIMAL, OCR2A, 3);
OLED_SetCursor(0,0);

    counter = 0; // reset accumulator

    cli();
    sei();

    TCNT4 = 0; // reset 1 second cnt

}
