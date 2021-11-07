#include "stm32f103xb.h" 


/**
	* @brief  R�alise le setup du pin du servo-moteur pour l'utilisation du PWM
  * @note   Pour le servo-moteur on utilise TIM1_CH1 donc on configure PA8
	* @param  None
  * @retval None
  */
void Conf_IO_Servomoteur(void);

/**
	* @brief  R�alise le setup d'un timer en PWM
  * @note   Pour le servo moteur on utilise TIM1_CH1 cad PA8
	* @param  TIM_TypeDef Timer : indique le timer � utiliser pour le PWM, TIM1 pour le servo-moteur
  * @retval None
  */
void Timer_Conf_PWM(TIM_TypeDef* Timer);

/**
	* @brief  On met l'impulsion dimensionn�e sur le CCR1 du TIM1 en PWM pour avoir OCxREF qui vaut 1 pendant le temps correspondant
  * @note   Utilis�e en conjonction avec CalculAngle de Encoder.c   
	* @param  TIM_TypeDef TimerPWM : indique le timer qui est en mode PWM, donc pour nous TIM1
	* @param	float t : valeur qui va �tre utilis�e pour dimensionner l'impulsion (entre 1 et 2)
  * @retval None
  */
void Envoi_Impulsion(TIM_TypeDef* TimerPWM, float t);

