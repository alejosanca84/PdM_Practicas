# Práctica 1 - Control de LED con Pulsador

## Objetivo
El objetivo de esta práctica es familiarizarse con el entorno de trabajo **STM32CubeIDE**, la placa de desarrollo **NUCLEO-F446RE** y el uso del firmware asociado.

## Punto 1: Parpadeo del LED LD2

Implementar un programa que controle el parpadeo del LED LD2 de la placa NUCLEO-F446RE.

*   El LED debe permanecer encendido durante **200 ms**.
*   El ciclo de trabajo (duty cycle) debe ser del **50%**, lo que implica que el LED también estará apagado durante 200 ms.

## Punto 2: Control del Tiempo de Encendido con Pulsador (B1)

Extender el programa del Punto 1 para que el pulsador B1 (Blue Button) controle el tiempo de encendido del LED.

*   Cada vez que se presione el pulsador B1, el tiempo de encendido del LED debe alternar entre **200 ms** y **500 ms**.
*   El duty cycle del 50% se debe mantener, por lo que el tiempo de apagado será igual al tiempo de encendido.

## Preguntas para Reflexionar sobre el Ejercicio

Estas preguntas invitan a la reflexión sobre el diseño y la robustez del código implementado:

*   **Uso de Arrays de Tiempos:**
    *   ¿De qué serviría usar un array de "tiempos" en el programa?
    *   ¿Qué sucede con la flexibilidad y el mantenimiento de nuestro programa si en el futuro se nos solicita agregar, quitar o cambiar un tiempo de encendido?
*   **Respuesta a las Pulsaciones:**
    *   ¿Cómo responde el programa a las pulsaciones del botón B1?
    *   ¿Se observan "falsos positivos" (lecturas erróneas del botón) o "pulsaciones no detectadas" (pulsaciones reales que el programa ignora)? ¿A qué podrían deberse estos comportamientos?
*   **Momento de Lectura del Pulsador:**
    *   ¿Cuál es el mejor momento para leer el estado del pulsador?
    *   ¿Es más apropiado leerlo después de un ciclo completo de la secuencia de parpadeo (encendido y apagado del LED)?
    *   ¿O es mejor leerlo inmediatamente después de cada cambio de estado del LED (después de encender y después de apagar)?
    *   ¿Qué diferencias fundamentales existen entre estas dos alternativas de lectura en términos de respuesta y complejidad?
*   **Impacto de la Duración del Tiempo de Encendido:**
    *   ¿Cambiarían las respuestas a las preguntas anteriores si el tiempo de encendido del LED fuera sensiblemente más grande, por ejemplo, **2 segundos**?
    *   ¿Y si fuera sensiblemente más chico, por ejemplo, **50 ms**? ¿Cómo afectarían estos cambios a la lógica de detección del pulsador y a la percepción del parpadeo?
