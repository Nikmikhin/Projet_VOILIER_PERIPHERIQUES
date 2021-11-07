#include "AntiChavirement.h"
#include "PWM.h"
#include "ADC.h"
#include "Encoder.h"

/**
	* @brief  On fait une conversion avec l'ADC
  * @note   None
	* @param  None
  * @retval None
  */
	void DectectionAngleRoulis(void){
		Enable_ADC();
	}

/**
	* @brief  Envoie une impulsion au TIM1 qui est en PWM pour relacher les voiles au max pdt 10 secs
  * @note   None
	* @param  None
  * @retval None
  */
void RelachementVoile(void){
	Envoi_Impulsion(TIM1, Calcul_Impulsion(0));
}

/**
	* @brief  On réalise la configuration de base de tous les éléments en rapport avec l'anti Chavirement
  * @note   None
	* @param  None
  * @retval None
  */
void ConfigChavirement(void){
	// Initialisation de l'ADC
	Conf_IO_ADC();
	Conf_ADC(RelachementVoile);
}

