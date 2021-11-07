
#ifndef CAP_H
#define CAP_H

/*
Service permettant de gérer l'orientation du cap en fonction d'un signal PWM entrant venant de la télécommande

*/

#include "stm32f103xb.h" 
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"

/*Define*/
//Valeur 
#define PERIODE_S_IN_PWM 13.6 //13.6ms
#define PERIODE_MIN_PWM  1  //1ms
#define PERIODE_N_PWM    1.5//1.5ms
#define PERIODE_MAX_PWM 	 2 //2ms
#define FREQUENCE_T4 	40		//40kHz

#define ARR_TIM2			3600

//==GPIO==//

#define GPIO_TIM4 GPIOB
#define TIM4_CH1 LL_GPIO_PIN_6
#define TIM4_CH2 LL_GPIO_PIN_7

#define GPIO_MOTEUR GPIOA
#define TIM2_CH3 LL_GPIO_PIN_1
#define SENS LL_GPIO_PIN_2

#define MSK_SENS (0x01<<2)


/*=====================================================================================
Fonction d'initialisation pour la gestion du cap (englobe leus autres fcts init)
========================================================================================*/

/**
	* @brief  Initialise les péripheriques pour la gestion du Cap a partir de la télécommande 
  * @note   Seule fct a etre appelée dans le main
	* @param  Aucun
  * @retval Aucun
  */
void init_cap(void);


/* =====================================================================================
Les fonctions qui récupere l'information du signal PWM 
=======================================================================================*/

/**
	* @brief  Initialise le TIM4 en input PWM (sur CH1 donc PB6)
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void init_inputPWM(void);

/**
	* @brief  Initialise l'intérruption sur capture afin de récupérer le dutycycle et le sens  
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void configure_IT_T4(void);

/**
	* @brief  Démarre la fonction capture du Timer4
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void demarer_capture_PWM(void);

/**
	* @brief  Récupérer le rapport cyclique grace au TIM4
  * @note  Est appélée dans la fonction d'IT  
	* @param  Aucun
  * @retval dutycyle 
  */
float get_info_RF(void);

/* =====================================================================================
Les fonctions qui gèrent l'orientation du CAP
=======================================================================================*/

/**
	* @brief  Initialise le TIM2 pour fonctionner en PWM mode sur le CH2 (PA1) f=10KHz
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void init_outputPWM(void);

/**
	* @brief  Initialise les GPIOs sur moteur (PA1 pour PWM, PA2 pour SENS)
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void init_PinMoteur(void);

/**
	* @brief Démare le TIM2
  * @note   Initialement le rapport cyclique est de 0
	* @param  Aucun
  * @retval Aucun
  */
void demarer_output_PWM(void);

/**
	* @brief Modifie la valeur du rapport cyclique du PWM généré par TIM2
  * @note  Est appelé sur l'interruption capture du TIM2
	* @param  dutycycle
  * @retval Aucun
  */
void controle_moteur(float dutycycle);
#endif
