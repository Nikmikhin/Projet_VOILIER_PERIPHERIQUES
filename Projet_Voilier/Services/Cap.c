
/*
Service permettant de chornométrer jusqu'à 59mn 59s 99 1/100
Utilise un timer au choix (TIMER1 à TIMER4).
Utilise la lib MyTimers.h /.c
*/



#include "Cap.h"
#include "MyTimer.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges


/**
	* @brief  Initialise le TIM4 en input PWM (sur CH1 donc PB6)
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void init_inputPWM()
{
	MyTimer_Conf(TIM4,0xFFFFFFF,179);
	//40kHz car t_avant compris entre 1ms et 1.5ms-> F=1/0.5ms=2kHz or on veut le découper en 10 intervalles(pour aller par pas de 10%) 
	//--> F=20kHz, pour plus de précision et palier au imprécision du timer 
	//il faut diviser la clock de 1800
	
	
	
	
	//Configuration mode capture
	 
		LL_TIM_IC_Config(TIM4,LL_TIM_CHANNEL_CH1,LL_TIM_ACTIVEINPUT_DIRECTTI );
		LL_TIM_IC_SetPolarity(TIM4,LL_TIM_CHANNEL_CH1,LL_TIM_IC_POLARITY_RISING);
		
		LL_TIM_IC_Config(TIM4,LL_TIM_CHANNEL_CH2,LL_TIM_ACTIVEINPUT_INDIRECTTI );
		LL_TIM_IC_SetPolarity(TIM4,LL_TIM_CHANNEL_CH2,LL_TIM_IC_POLARITY_FALLING);
	

	
	//Timer synchronisation configuration
	LL_TIM_SetTriggerInput	(TIM4,LL_TIM_TS_TI1FP1);	
	LL_TIM_SetSlaveMode	(TIM4,LL_TIM_SLAVEMODE_RESET); //pour reset les compteur a chaque front montant de l'entrée
	
	
	
	//Activation de l'horloge GPIOB
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	
	//Configuration des GPIOs
	LL_GPIO_SetPinMode	(	GPIO_TIM4,TIM4_CH1,LL_GPIO_MODE_FLOATING); 
}

/**
	* @brief  Initialise l'intérruption sur capture afin de récupérer le dutycycle et le sens  
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void configure_IT_T4()
{
	//Configuration IT sur capture de CH1
	LL_TIM_EnableIT_CC1(TIM4);		
	NVIC_EnableIRQ(TIM4_IRQn);
}

/**
	* @brief  Initialise les GPIOs sur moteur (PA1 pour PWM, PA2 pour SENS)
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void init_PinMoteur()
{
	MyTimer_Conf(TIM4,0xFFFFFFF,1799);
	//Enable clock GPIOA
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_GPIO_SetPinMode	(	GPIO_MOTEUR,TIM2_CH3,LL_GPIO_MODE_ALTERNATE); 
	
	LL_GPIO_SetPinMode	(	GPIO_MOTEUR,SENS,LL_GPIO_MODE_OUTPUT); 
	LL_GPIO_SetPinOutputType(GPIO_MOTEUR,SENS,LL_GPIO_OUTPUT_PUSHPULL); 
}

/**
	* @brief  Initialise le TIM2 pour fonctionner en PWM mode sur le CH2 (PA1) f=10KHz
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void init_outputPWM()
{
	
	MyTimer_Conf(TIM2,(ARR_TIM2-1),1); //On prendra F=10KHz (2*3600*10Khz=72Mhz)
	LL_TIM_OC_SetMode	(	TIM2,LL_TIM_CHANNEL_CH2,LL_TIM_OCMODE_PWM1);	
	LL_TIM_OC_SetIdleState	(	TIM2,LL_TIM_CHANNEL_CH2,LL_TIM_OCIDLESTATE_LOW); 
	LL_TIM_OC_SetCompareCH2	(	TIM2,ARR_TIM2*0); 

}

/**
	* @brief Démare le TIM2
  * @note   Initialement le rapport cyclique est de 0
	* @param  Aucun
  * @retval Aucun
  */
void demarer_output_PWM()
{
	LL_TIM_CC_EnablePreload (TIM2);
  LL_TIM_CC_EnableChannel (TIM2 ,LL_TIM_CHANNEL_CH2);
	LL_TIM_EnableCounter(TIM2);
}

/**
	* @brief  Démarre la fonction capture du Timer4
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void demarer_capture_PWM()
{
	
	//Capture Enable
	 LL_TIM_CC_EnableChannel	(	TIM4,LL_TIM_CHANNEL_CH1);
	 LL_TIM_CC_EnableChannel	(	TIM4,LL_TIM_CHANNEL_CH2);
	//Enable Compteur
	 LL_TIM_EnableCounter(TIM4);	

}

/**
	* @brief  Initialise les péripheriques pour la gestion du Cap a partir de la télécommande 
  * @note   Seule fct a etre appelée dans le main
	* @param  Aucun
  * @retval Aucun
  */
void init_cap()
{
	//pour entrée PWM
	init_inputPWM();
	configure_IT_T4();
	
	//moteur
	init_PinMoteur();
	init_outputPWM();
	demarer_output_PWM();
	demarer_capture_PWM();
	
	
}

/**
	* @brief  Récupérer le rapport cyclique grace au TIM4
  * @note  Est appélée dans la fonction d'IT  
	* @param  Aucun
  * @retval dutycyle 
  */
float get_info_RF()
{
	unsigned int t_on;
	float retour=0; //valeur initiale
	
	t_on=LL_TIM_IC_GetCaptureCH2(TIM4); //comrpirs entre 40 et 80 // 1 dans le conmpteur correspond a 5%
		
	
	if(((t_on>=((FREQUENCE_T4*PERIODE_N_PWM)-1)) && (t_on<=((FREQUENCE_T4*PERIODE_N_PWM)+1))) || t_on==0) //Pour pallier au erreur de la période envoyée 
	{
		
		retour=0;
		return(retour);	
	}
	else 
	{
		if(t_on<(FREQUENCE_T4*PERIODE_N_PWM))		
		{
			retour=t_on-(FREQUENCE_T4*PERIODE_N_PWM);
			retour=retour/((FREQUENCE_T4*PERIODE_N_PWM)-(FREQUENCE_T4*PERIODE_MIN_PWM));
			
		}
		if (t_on>(FREQUENCE_T4*PERIODE_N_PWM))
		{
			retour=t_on-(FREQUENCE_T4*PERIODE_N_PWM);
			retour=retour/((FREQUENCE_T4*PERIODE_MAX_PWM)-(FREQUENCE_T4*PERIODE_N_PWM));
		}
	}
	
	return(retour);	
}

/**
	* @brief Modifie la valeur du rapport cyclique du PWM généré par TIM2
  * @note  Est appelé sur l'interruption capture du TIM2
	* @param  dutycycle
  * @retval Aucun
  */
void controle_moteur(float dutycycle)
{
	if(dutycycle<0) 
	{
		
		dutycycle=-dutycycle;
		
		LL_GPIO_ResetOutputPin (GPIO_MOTEUR, SENS);
		LL_TIM_OC_SetCompareCH2	(	TIM2,ARR_TIM2*dutycycle); 
		
	}
	else
	{
		LL_GPIO_SetOutputPin (GPIO_MOTEUR, SENS);
		LL_TIM_OC_SetCompareCH2	(	TIM2,ARR_TIM2*dutycycle);	
	}
	
}


//Interruptions

void TIM4_IRQHandler(void)
{
	// rabaisser le flag d'IT
	LL_TIM_ClearFlag_CC1(TIM4);	
	controle_moteur(get_info_RF());
}	

