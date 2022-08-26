#include <Arduino.h>
//https://github.com/AlexandreBlais42/arduinoUnoRapide


//Temps
void delay(int t){
  _delay_ms(t);
}

//Pins

void pinMode2(uint8_t pin, uint8_t mode){
  //TODO: Trouver comment overwrite la fonction pinMode implémenter par arduino (wiring_digital.c)
  volatile uint8_t *targeted_DDR = &DDRD;
  
  if (pin >= 8){
    pin -= 8;
    targeted_DDR = &DDRB;
  }

  pin = 1<<pin;
  
  if (mode == INPUT){
    *targeted_DDR &= ~pin;
  }else if (mode == OUTPUT){
    *targeted_DDR |= pin;
  }else{
    //TODO: INPUT_PULLUP
  }
}
