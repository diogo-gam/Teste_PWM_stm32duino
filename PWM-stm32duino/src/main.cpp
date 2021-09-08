#include <Arduino.h>


// vamos tentar usar um canal do TIMER3 para conseguir 2 sinais PWM no pino PB1 e PB0



#define pin1 PB1
#define pin2 PB0


void setup() {
  //definindo modo de pino2, pino1 tem seu modo definido na função setMode
  
  

  //criando instancia de objeto HardwareTimer no timer3 do stm32
  TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin1), PinMap_PWM);

  uint32_t channel_1 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin1), PinMap_PWM));
  uint32_t channel_2 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin2), PinMap_PWM));


  HardwareTimer *MyTim = new HardwareTimer(Instance);
  

  //pino em HIGH quando counter < compare e LOW quando counter > compare
  MyTim->setMode(channel_1, TIMER_OUTPUT_COMPARE_PWM1, pin1);
  MyTim->setMode(channel_2, TIMER_OUTPUT_COMPARE_PWM1, pin2);
  
  MyTim->setOverflow(100, HZ_FORMAT); 

  //setando dutyCycle do channel 1 de 50%
  MyTim->setCaptureCompare(channel_1, 50, PERCENT_COMPARE_FORMAT); 

  //setando dutyCycle do channel 2 de 25%
  MyTim->setCaptureCompare(channel_2, 25, PERCENT_COMPARE_FORMAT);


  // iniciando o Timer
  MyTim->resume();
  
}

void loop() {
  
}
