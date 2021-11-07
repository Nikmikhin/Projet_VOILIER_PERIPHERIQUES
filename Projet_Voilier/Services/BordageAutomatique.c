#include "BordageAutomatique.h"
#include "PWM.h"
#include "Encoder.h"
#include "MyTimer.h"

/**
	* @brief  On réalise la configuration de base de tous les éléments en rapport avec le Bordage automatique
  * @note   Utilisation de l'Encoder & du PWM
	* @param  TIM_TypeDef TimerPWM : indique le timer qui est en mode PWM, donc pour nous TIM1
	* @param	TIM_TypeDef TimerEncoder : indique le timer qui est en mode Encoder, donc pour nous TIM3
  * @retval None
  */
void ConfigBordage(TIM_TypeDef* TimerPWM, TIM_TypeDef* TimerEncoder){
	// Initialisation côté Girouette
	Conf_IO_Girouette();
	Timer_Conf_Encoder(TimerEncoder);
	Detection_Angle0();
	MyTimer_Reset(TimerEncoder);
	MyTimer_Start(TimerEncoder);
	
	// Initialisation côté Servo-moteur
	Conf_IO_Servomoteur();
	Timer_Conf_PWM(TimerPWM);
	MyTimer_Start(TimerPWM);
}

/**
	* @brief  On asservit la voile => mise à jour de TIM1->CCR1 en fct de TIM3->CNT
  * @note   Appelée par SysTick chaque 0.5s
	* @param  TIM_TypeDef TimerPWM : indique le timer qui est en mode PWM, donc pour nous TIM1
	* @param	TIM_TypeDef TimerEncoder : indique le timer qui est en mode Encoder, donc pour nous TIM3
  * @retval None
  */
void AsservBordage(TIM_TypeDef* TimerPWM, TIM_TypeDef* TimerEncoder){
	Envoi_Impulsion(TimerPWM, Calcul_Impulsion(Calcul_Theta(&TimerEncoder->CNT)));
}

