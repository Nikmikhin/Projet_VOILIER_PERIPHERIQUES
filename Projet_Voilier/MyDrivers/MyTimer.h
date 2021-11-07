#ifndef MY_TIMER_H
#define MY_TIMER_H

/*
Driver pour Timer 1 � 4 du STM32F103RB

*/

#include "stm32f103xb.h" 

/**
	* @brief  Active l'horloge et r�gle l'ARR et le PSC du timer vis�
  * @note   Fonction � lancer avant toute autre. Le timer n'est pas encore lanc� (voir MyTimerStart)
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
	* 				int Arr   : valeur � placer dans ARR
	*					int Psc   : valeur � placer dans PSC
  * @retval None
  */
void MyTimer_Conf(TIM_TypeDef * Timer, int Arr, int Psc);


/**
	* @brief  D�marre le timer consid�r�
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_Start(TIM_TypeDef * Timer);

/**
	* @brief  On fait un reset du timer consid�r�
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser
  * @retval None
  */
void MyTimer_Reset(TIM_TypeDef * Timer);
	
#endif
