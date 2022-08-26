#include <Arduino.h>
//https://github.com/AlexandreBlais42/arduinoUnoRapide

//Temps
void delay(int t){
  _delay_ms(t);
}

//Pins
void digitalWrite2(uint8_t pin, uint8_t mode){
  //TODO: Trouver comment overwrite la fonction digitalWrite implémenter par arduino (wiring_digital.c)
  volatile uint8_t * targeted_PORT = &PORTD;

  if (pin >= 8){
    pin -= 8;
    targeted_PORT = &PORTB;
  }

  pin = 1<<pin; //pin devient un bit mask sans déclarer une nouvelle variable

  if (mode == HIGH){
    *targeted_PORT |= pin;
  }else if (mode == LOW){
    *targeted_PORT &= ~pin;
  }
}

void pinMode2(uint8_t pin, uint8_t mode){
  //TODO: Trouver comment overwrite la fonction pinMode implémenter par arduino (wiring_digital.c)
  volatile uint8_t *targeted_DDR = &DDRD;
  
  if (pin >= 8){
    pin -= 8;
    targeted_DDR = &DDRB;
  }

  uint8_t bitMask = 1<<pin;
  
  if (mode == INPUT){
    *targeted_DDR &= ~bitMask;
  }else if (mode == OUTPUT){
    *targeted_DDR |= bitMask;
  }else if (mode == INPUT_PULLUP){
    *targeted_DDR &= ~bitMask;
    digitalWrite2(pin, HIGH);
  }
}

uint8_t digitalRead2(uint8_t pin){
  volatile uint8_t *targeted_PIN = &DDRD;

  if (pin >= 8){
    pin -= 8;
    targeted_PIN = &DDRB;
  }

  pin = 1<<pin; //pin devient un bit mask sans déclarer une nouvelle variable

  if (*targeted_PIN & pin){
    return 1;
  }else{
    return 0;
  }
}
