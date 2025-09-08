# Práctica 2

## Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes.

---

### Punto 1

Implementar las funciones auxiliares necesarias para usar retardos no bloqueantes en un archivo fuente `main.c` con su correspondiente archivo de cabecera `main.h`.

En `main.h` se deben ubicar los prototipos de las siguientes funciones y las declaraciones:

```c
typedef uint32_t tick_t; // ¿Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t;	  // ¿Qué biblioteca se debe incluir para que esto compile?

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );
```

# Proyecto de Retardos No Bloqueantes y Patrones de LED

Este repositorio contiene la implementación de un sistema de retardos no bloqueantes (non-blocking delays) y su aplicación para controlar el parpadeo de LEDs en una placa de desarrollo.

## Implementación de Funciones en `main.c`

El archivo `main.c` contiene la implementación de las funciones para la gestión de retardos no bloqueantes.

### Consideraciones para la Implementación

#### `delayInit`
- Carga el valor de duración del retardo en el campo correspondiente de la estructura.
- No inicia el conteo del retardo.
- Inicializa el flag `running` en `false`.

#### `delayRead`
Esta función verifica el estado del flag `running`:
- Si es **`false`**:
    1. Toma una marca de tiempo.
    2. Cambia el estado de `running` a `true`.
- Si es **`true`**:
    1. Calcula si el tiempo del retardo se ha cumplido mediante la comparación:
       `'marca de tiempo actual' - 'marca de tiempo inicial' >= 'duración del retardo'`
    2. Devuelve un valor booleano indicando si el tiempo se cumplió.
    3. Si el tiempo se cumple, el flag `running` debe cambiar a `false`.

#### `delayWrite`
- Permite modificar el tiempo de duración de un `delay` ya existente.

**NOTA:** Para obtener una marca de tiempo, se puede utilizar la función `HAL_GetTick()`, que devuelve un valor que se incrementa cada 1 ms y sirve como base de tiempo.

---

## Punto 2: Parpadeo Periódico de LED

Sobre el código desarrollado en el punto anterior, se implementa un programa que utiliza los retardos no bloqueantes para hacer parpadear el LED de la placa de desarrollo de forma periódica:
- **100 ms** encendido.
- **100 ms** apagado.

---

## Punto 3 [Opcional]: Patrón de Parpadeo Complejo

Ampliando el código del punto 2, se implementa un programa que hace parpadear el LED de la placa con el siguiente patrón secuencial, utilizando un vector o arreglo para definirlo:

1.  **5 veces** con un período de 1 segundo y un ciclo de trabajo del 50%.
2.  **5 veces** con un período de 200 ms y un ciclo de trabajo del 50%.
3.  **5 veces** con un período de 100 ms y un ciclo de trabajo del 50%.

---

## Para pensar luego de resolver el ejercicio

A continuación, se presentan algunas preguntas para reflexionar sobre el código desarrollado:

-   ¿Se pueden cambiar los tiempos de encendido de cada LED fácilmente en un solo lugar del código o éstos están "hardcodeados"?
-   ¿Qué bibliotecas estándar se debieron agregar para que el código compile? Si las funcionalidades crecieran, ¿cuál sería el mejor lugar para incluir esas bibliotecas y algunos `typedefs` que se usan en el ejercicio?
-   ¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?
-   ¿Cuán reutilizable es el código implementado?
-   ¿Cuán sencillo resulta en su implementación cambiar el patrón de tiempos de parpadeo?
