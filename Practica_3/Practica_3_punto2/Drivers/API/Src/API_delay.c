#include "API_delay.h"
#include "stm32f4xx_hal.h" // Necesario para la función HAL_GetTick()

/**
  * @brief  Inicializa una estructura de retardo.
  * @param  delay: Puntero a la estructura de retardo.
  * @param  duration: Duración del retardo en milisegundos (ms).
  * @retval None
  */
void delayInit( delay_t * delay, tick_t duration )
{
	delay->duration = duration;
	delay->running = false;
}

/**
  * @brief  Lee el estado del retardo. Si no está corriendo, lo inicia.
  *         Si está corriendo, verifica si se ha cumplido el tiempo.
  * @param  delay: Puntero a la estructura de retardo.
  * @retval bool_t: true si el tiempo se cumplió, false en caso contrario.
  */
bool_t delayRead( delay_t * delay )
{
	bool_t time_cumplido = false;

	if( !delay->running )
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else
	{
		if( (HAL_GetTick() - delay->startTime) >= delay->duration )
		{
			time_cumplido = true;
			delay->running = false;
		}
	}

	return time_cumplido;
}

/**
  * @brief  Permite actualizar la duración de un retardo existente.
  * @param  delay: Puntero a la estructura de retardo.
  * @param  duration: Nueva duración del retardo en milisegundos (ms).
  * @retval None
  */
void delayWrite( delay_t * delay, tick_t duration )
{
	delay->duration = duration;
}
