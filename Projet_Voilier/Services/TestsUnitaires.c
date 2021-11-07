#include "TestsUnitaires.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_utils.h"

#include "PWM.h"
#include "Encoder.h"
#include "MyTimer.h"
#include "Cap.h"

void Conf_Test (void){
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_5, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_PUSHPULL);
}

void Test_Girouette (int nombre){
  for (int i=0; i<nombre ; i++){
		LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_3);
    LL_mDelay(1);
    LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_4);
    LL_mDelay(1);
    LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_3);
    LL_mDelay(1);
    LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_4);
    LL_mDelay(1);
    if (i==10){   
			LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_2);
      LL_mDelay(1);
      LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_2);
    }
  }
}

void Test_Servomoteur(void){
	Conf_IO_Servomoteur();
	Timer_Conf_PWM(TIM1);
	MyTimer_Start(TIM1);
	Envoi_Impulsion(TIM1, Calcul_Impulsion(90.0));
	LL_mDelay(10000);
	Envoi_Impulsion(TIM1, Calcul_Impulsion(-90.0));
	LL_mDelay(10000);
	Envoi_Impulsion(TIM1, Calcul_Impulsion(0.0));
	LL_mDelay(10000);
}
void Test_moteur()
{
		
	//moteur
	init_PinMoteur();
	demarer_output_PWM();
	
}
