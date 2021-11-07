#include "stm32f103xb.h" 


/**
	* @brief  On r�alise la configuration de base de tous les �l�ments en rapport avec le Bordage automatique
  * @note   Utilisation de l'Encoder & du PWM
	* @param  TIM_TypeDef TimerPWM : indique le timer qui est en mode PWM, donc pour nous TIM1
	* @param	TIM_TypeDef TimerEncoder : indique le timer qui est en mode Encoder, donc pour nous TIM3
  * @retval None
  */
void ConfigBordage(TIM_TypeDef* TimerPWM, TIM_TypeDef* TimerEncoder);

/**
	* @brief  On asservit la voile => mise � jour de TIM1->CCR1 en fct de TIM3->CNT
  * @note   Appel�e par SysTick chaque 0.5s
	* @param  TIM_TypeDef TimerPWM : indique le timer qui est en mode PWM, donc pour nous TIM1
	* @param	TIM_TypeDef TimerEncoder : indique le timer qui est en mode Encoder, donc pour nous TIM3
  * @retval None
  */
void AsservBordage(TIM_TypeDef* TimerPWM, TIM_TypeDef* TimerEncoder);
	
