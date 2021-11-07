#include "PWM.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"


/**
	* @brief  Réalise le setup du pin du servo-moteur pour l'utilisation du PWM
  * @note   Pour le servo-moteur on utilise TIM1_CH1 donc on configure PA8
	* @param  None
  * @retval None
  */
void Conf_IO_Servomoteur(void){
	// Validation clock locale
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	// Configuration des broches
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
}

/**
	* @brief  Réalise le setup d'un timer (TIM1) en PWM
  * @note   Pour le servo-moteur on utilise TIM1_CH1 cad PA8
	* @param  TIM_TypeDef Timer : indique le timer à utiliser pour le PWM, TIM1 pour le servo-moteur
  * @retval None
  */
void Timer_Conf_PWM(TIM_TypeDef* Timer){
	//activation du clock avant toute chose
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	
	//setup du clock avec les valeurs pour avoir 20ms
	Timer->ARR=0xE0FF;
	Timer->PSC=0x18;
	
	//setup du Capture/Compare1 en mode PWM1
	LL_TIM_OC_InitTypeDef PWMInitStruct;
	LL_TIM_OC_StructInit(&PWMInitStruct);
	PWMInitStruct.OCMode=LL_TIM_OCMODE_PWM1;
	PWMInitStruct.OCPolarity=LL_TIM_OCPOLARITY_HIGH;
	PWMInitStruct.OCState=LL_TIM_OCSTATE_ENABLE;
	LL_TIM_CC_EnableChannel(Timer,LL_TIM_CHANNEL_CH1);
	LL_TIM_OC_Init(Timer,LL_TIM_CHANNEL_CH1,&PWMInitStruct);
	LL_TIM_EnableAllOutputs(Timer);
}

/**
	* @brief  On met l'impulsion dimensionnée sur le CCR1 du TIM1 en PWM pour avoir OCxREF qui vaut 1 pendant le temps correspondant
  * @note   Utilisée en conjonction avec CalculAngle de Encoder.c
	* @param  TIM_TypeDef TimerPWM : indique le timer qui est en mode PWM, donc pour nous TIM1
	* @param	float t : valeur qui va être utilisée pour dimensionner l'impulsion (entre 1 et 2)
  * @retval None
  */
void Envoi_Impulsion(TIM_TypeDef* TimerPWM, float t){
	TimerPWM->CCR1=0xB3F*t;
}

