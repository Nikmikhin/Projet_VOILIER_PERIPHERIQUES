#include "stm32f103xb.h" 

extern int chavirement;

/**
	* @brief  R�alise le setup des pins pour l'utilisation de l'ADC
  * @note   On met l'entr�e de l'ADC sur PC0 (CH10)
	* @param  None
  * @retval None
  */
void Conf_IO_ADC(void);

/**
	* @brief  R�alise le setup de l'ADC
  * @note   None
	* @param  void (*IT_function) (void) : pointeur vers la fct qui se d�clenche � l'interruption du watchdog
  * @retval None
  */
void Conf_ADC (void (*IT_function) (void) );


/**
	* @brief  On fait une conversion avec l'ADC
  * @note   None
	* @param  None
  * @retval None
  */
void Enable_ADC(void);
