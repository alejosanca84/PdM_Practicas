#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/* Includes ------------------------------------------------------------------*/
// Para uint32_t, necesitamos los tipos de enteros de tamaño estándar.
#include <stdint.h>
// Para bool, necesitamos el tipo de dato booleano estándar de C.
#include <stdbool.h>

/* Typedef -------------------------------------------------------------------*/
typedef uint32_t tick_t;
typedef bool     bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

/* Function Prototypes -------------------------------------------------------*/
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );
bool_t delayIsRunning( delay_t * delay ); // <-- NUEVA FUNCIÓN AÑADIDA

#endif /* API_INC_API_DELAY_H_ */
