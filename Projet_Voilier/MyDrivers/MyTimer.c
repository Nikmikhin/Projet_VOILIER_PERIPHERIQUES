#include "MyTimer.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_tim.h" 




/**
	* @brief  Active l'horloge et règle l'ARR et le PSC du timer visé
  * @note   Fonction à lancer avant toute autre. Le timer n'est pas encore lancé (voir MyTimerStart)
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
	* 				int Arr   : valeur à placer dans ARR
	*					int Psc   : valeur à placer dans PSC
  * @retval None
  */
void MyTimer_Conf(TIM_TypeDef * Timer,int Arr, int Psc)
{
	LL_TIM_InitTypeDef My_LL_Tim_Init_Struct;
	
	// Validation horloge locale
	if (Timer==TIM1) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	else if (Timer==TIM2) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	else if (Timer==TIM3) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	else  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	
	// chargement structure Arr, Psc, Up Count
	My_LL_Tim_Init_Struct.Autoreload=Arr;
	My_LL_Tim_Init_Struct.Prescaler=Psc;
	My_LL_Tim_Init_Struct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	My_LL_Tim_Init_Struct.CounterMode=LL_TIM_COUNTERMODE_UP;
	My_LL_Tim_Init_Struct.RepetitionCounter=0;
	
	LL_TIM_Init(Timer,&My_LL_Tim_Init_Struct);
	

	// Blocage IT
	LL_TIM_DisableIT_UPDATE(Timer);
	
	
	// Blocage Timer
	LL_TIM_DisableCounter(Timer);
	
	//Correction remise a 0 de UIF (pas d'explication)
	LL_TIM_ClearFlag_UPDATE(Timer);
		
}

/**
	* @brief  Démarre le timer considéré
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser
  * @retval None
  */
void MyTimer_Start(TIM_TypeDef * Timer){
	LL_TIM_EnableCounter(Timer);
}

/**
	* @brief  On fait un reset du timer considéré
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser
  * @retval None
  */
void MyTimer_Reset(TIM_TypeDef * Timer){
	LL_TIM_SetCounter(Timer, 0);
}
