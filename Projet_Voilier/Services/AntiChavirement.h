#include "stm32f103xb.h" 


/**
	* @brief  On fait une conversion avec l'ADC
  * @note   None
	* @param  None
  * @retval None
  */
void DectectionAngleRoulis(void);

/**
	* @brief  Envoie une impulsion au TIM1 en PWM pour relacher les voiles au max pdt 5 secs
  * @note   None
	* @param  None
  * @retval None
  */
void RelachementVoile(void);

/**
	* @brief  On réalise la configuration de base de tous les éléments en rapport avec l'anti Chavirement
  * @note   None
	* @param  None
  * @retval None
  */
void ConfigChavirement(void);

