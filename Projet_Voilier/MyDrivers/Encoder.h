#include "stm32f103xb.h" 

/**
	* @brief  Réalise le setup des pins en lien avec la girouette pour l'utilisation du codeur incrémental
  * @note   On met l'index sur PA5, le CHA sur PA6, le CHB sur PA7
	* @param  None
  * @retval None
  */
void Conf_IO_Girouette(void);

/**
	* @brief  Réalise le setup d'un timer en Encoder
  * @note   Utilisé pour lire les données de la girouette
	* @param  TIM_TypeDef Timer : indique le timer à utiliser pour le Encoder, donc pour nous TIM3
  * @retval None
  */
void Timer_Conf_Encoder (TIM_TypeDef * Timer);

/**
	* @brief  Fonction pour l'obtention de l'angle nul de la girouette
  * @note   On attend que la giroutte passe devant la valeur d'angle pour laquelle I=0 pour activer le encoder au bon moment
	* @param  None
  * @retval None
  */
void Detection_Angle0(void);

/**
	* @brief  On prend les valeurs d'angle provenant de la girouette pour calculer les valeurs de theta
  * @note   Il y a 3 équations pour l'évolution de theta en fonction de alpha
	* @param	int alpha : indique l'angle du vent, avec TimerEncoder->CNT (ira de 0 à 360)
  * @retval l'angle theta auquel les voiles doivent se déplacer
  */
float Calcul_Theta(volatile unsigned int *alpha);

/**
	* @brief  On prend les valeurs d'angle voulus pour les voiles pour agir sur le servo-moteur
  * @note   None
	* @param	float theta : indique l'angle theta auquel les voiles doivent se déplacer (de -90 à 90)
  * @retval Représente le temps (le duty-cycle plutôt), on l'utilisera pour agir sur le CCR1 du TIM1 en PWM
  */
float Calcul_Impulsion(float theta);
