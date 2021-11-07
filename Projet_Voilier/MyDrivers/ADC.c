#include "ADC.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h"

void (*Ptr_ItFct_ADC)(void);
int chavirement=0; // Booléen qui vaut 1 si on s'approche du chavirement, cad quand l'angle de roulis > 40, on attend alors 10 sec

#define SEUILMAX45 0x759 //Seuil de tension pour un angle de roulis 45º
#define SEUILMIN45 0x45E //Seuil de tension pour un angle de roulis -45º
/**
	* @brief  Réalise le setup des pins pour l'utilisation de l'ADC
  * @note   On met l'entrée de l'ADC sur PC0 (CH10)
	* @param  None
  * @retval None
  */
void Conf_IO_ADC(void){
	// Clock de APB
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
	// Configuration des broches
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG);
}

/**
	* @brief  Réalise le setup de l'ADC
  * @note   None
	* @param  void (*IT_function) (void) : pointeur vers la fct qui se déclenche à l'interruption du watchdog
  * @retval None
  */
void Conf_ADC (void (*IT_function) (void) ){
	
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct;

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
   // Validation horloge ADC

	LL_ADC_REG_StructInit(&ADC_REG_InitStruct);
   // Init structure par defaut de ADC

	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, ADC_CHANNEL_10_NUMBER); 
  // choix des chanels à convertir

	LL_ADC_SetAnalogWDMonitChannels(ADC1 ,LL_ADC_AWD_CHANNEL_10_REG); 
  // Surveillance sur le channel 10 (peut être 11 si ce n'est pas le bon axe)

	LL_ADC_SetAnalogWDThresholds(ADC1 ,LL_ADC_AWD_THRESHOLD_HIGH , SEUILMAX45); 
	// Mettre un seuil correspondant a 45º
	LL_ADC_SetAnalogWDThresholds(ADC1 ,LL_ADC_AWD_THRESHOLD_LOW , SEUILMIN45); 
	// Mettre un seuil correspondant a -45º
	LL_ADC_EnableIT_AWD1(ADC1);
	// Validation de l'interruption de depassement de 45º

	NVIC_EnableIRQ(ADC1_2_IRQn);
	NVIC_SetPriority(ADC1_2_IRQn, 3);
  Ptr_ItFct_ADC=IT_function;
	
	LL_ADC_REG_Init(ADC1,&ADC_REG_InitStruct); 
  // Initialisation de l'ADC par defaut
	
}


/**
	* @brief  On fait une conversion avec l'ADC
  * @note   None
	* @param  None
  * @retval None
  */
void Enable_ADC(void){
	LL_ADC_REG_StartConversionSWStart(ADC1);
}

/*
============ LES INTERRUPTIONS =================================

*/
void ADC1_2_IRQHandler (void){
	chavirement=1;
	// On rabaisse le flag de l'IT
    LL_ADC_ClearFlag_AWD1 (ADC1);
    (*Ptr_ItFct_ADC)();
}
