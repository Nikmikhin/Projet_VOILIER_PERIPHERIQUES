#include "Encoder.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"


#define PSMAX 0 // Impulsion pour avoir un angle de voile theta maximal
#define PSMIN 90 // Impulsion pour avoir un angle de voile theta minimal


/**
	* @brief  Réalise le setup des pins en lien avec la girouette pour l'utilisation du codeur incrémental
  * @note   On met l'index sur PA5, le CHA sur PA6, le CHB sur PA7
	* @param  None
  * @retval None
  */
void Conf_IO_Girouette(void){
	// Clock de APB
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	// Configuration des broches
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_FLOATING);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_FLOATING);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_FLOATING);
}

/**
	* @brief  Réalise le setup d'un timer en Encoder
  * @note   Utilisé pour lire les données de la girouette
	* @param  TIM_TypeDef Timer : indique le timer à utiliser pour le Encoder, donc pour nous TIM3
  * @retval None
  */
void Timer_Conf_Encoder (TIM_TypeDef * Timer){
LL_TIM_ENCODER_InitTypeDef TIM_EncoderInitStruct;	
	// Validation horloge locale
LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	// Valeurs par defaut de TIM_EncoderInitStruct
LL_TIM_ENCODER_StructInit(&TIM_EncoderInitStruct);
	// Mode comparer TI1 et TI2
TIM_EncoderInitStruct.EncoderMode = LL_TIM_ENCODERMODE_X4_TI12;	
	//Initialisation de encoder mode
LL_TIM_ENCODER_Init(TIM3,&TIM_EncoderInitStruct);

Timer->ARR = 0x05A1; //0x165
	
Conf_IO_Girouette();
}

/**
	* @brief  Fonction pour l'obtention de l'angle nul de la girouette
  * @note   On attend que la giroutte passe devant la valeur d'angle pour laquelle I=0, et ensuite on activera le codeur incrémental au bon moment
	* @param  None
  * @retval None
  */
void Detection_Angle0(void){
  while (!LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_5));
}

/**
	* @brief  On prend les valeurs d'angle provenant de la girouette pour calculer les valeurs de theta
  * @note   Il y a 3 équations pour l'évolution de theta en fonction de alpha
	* @param	int alpha : indique l'angle du vent, avec TimerEncoder->CNT (ira de 0 à 360)
  * @retval l'angle theta auquel les voiles doivent se déplacer
  */
float Calcul_Theta(volatile unsigned int *alpha){
	float theta;
	float aux;
	aux=*alpha * 360.0 / 0x05A1;
	if (aux<45 || aux>315){
		theta=0;
	}else{
		if (aux>=45 && aux<=180){
			theta=(2.0/3.0)* aux-30;
		}else{
			if (aux>180 && aux<=315){
			theta=0; // au debut on croyait que theta pouvait varier entre -90 et 90 (2.0/3.0)* *alpha-210;
			}
		}
	}
return theta;
}

/**
	* @brief  On prend les valeurs d'angle voulus pour les voiles pour agir sur le servo-moteur
  * @note   None
	* @param	float theta : indique l'angle theta auquel les voiles doivent se déplacer (de -90 à 90)
  * @retval Représente le temps (le duty-cycle plutôt), on l'utilisera pour agir sur le CCR1 du TIM1 en PWM
  */
float Calcul_Impulsion(float theta){
	return 2 - (theta-PSMAX)/(PSMIN-PSMAX);
}
