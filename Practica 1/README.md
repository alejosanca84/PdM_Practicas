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
    *   ¿De qué serviría usar un array de "tiempos" en el programa?\
**_Respuesta: Utilizar un array para almacenar los diferentes tiempos de parpadeo sirve para organizar y desacoplar los datos de la lógica del programa. En lugar de tener valores fijos (como 200 y 500) incrustados directamente en las sentencias condicionales (if-else), estos valores se agrupan en una única estructura de datos._**
    *   ¿Qué sucede con la flexibilidad y el mantenimiento de nuestro programa si en el futuro se nos solicita agregar, quitar o cambiar un tiempo de encendido?\
      
 **_Respuesta: Se convierte en un proceso sencillo, dado que basta con agregar un nuevo dato al array (o eliminar uno existente, si asi se quisiera), sin tener que intervenir los condicionales (if-else)_**
*   **Respuesta a las Pulsaciones:**
    *   ¿Cómo responde el programa a las pulsaciones del botón B1?\
**_Respuesta: Para evitar falsos positivos se coloco un condicional (if-else) para comprobar que el pulsador estaba oprimido y un delay de 50 mS para evitar el rebote del boton, antes de iniciar con la alternancia de tiempos, (la cual antes tiene otro condicional para validar el estado del boton B1)._**\

      <div align="center">
      <img width="862" height="318" alt="image" src="https://github.com/user-attachments/assets/94646b37-09f5-4dfc-b744-55449cde537a" />
      </div>
      \
    *   ¿Se observan "falsos positivos" (lecturas erróneas del botón) o "pulsaciones no detectadas" (pulsaciones reales que el programa ignora)? ¿A qué podrían deberse estos comportamientos?\
 **_Respuesta: Debido al arreglo anteriormente explicado no se observa esta condición, siempre y cuando el boton sea oprimido completamente_**
*   **Momento de Lectura del Pulsador:**
    *   ¿Cuál es el mejor momento para leer el estado del pulsador?\
**_Respuesta: Todo depende del nivel de respuesta que se requiera, es decir de la aplicación. La sentencia HAL_Delay() bloquea el desarrollo del programa, dado que deja en stand-by al micro, por lo cual entre mas largo sea un HAL_Delay(), mas tardara en recibir la señal del boton_**
    *   ¿Es más apropiado leerlo después de un ciclo completo de la secuencia de parpadeo (encendido y apagado del LED)?\
**_Respuesta: De acuerdo a lo expuesto en la anterior respuesta, si yo tengo un tiempo de 800 mS en el delay, este se duplicara en un ciclo completo, por tanto si pongo la opción de leer el pulsador luego de este tiempo se demorara el doble que si lo pongo en medio ciclo._**
    *   ¿O es mejor leerlo inmediatamente después de cada cambio de estado del LED (después de encender y después de apagar)?\
**_Respuesta: De acuerdo a la respuesta anterior esta es mejor opción, dado que solo tendre la mitad del ciclo completo, sin embargo por ser el delay un bloqueo del programa, siempre debera esperar, por tanto la mejor opción deberia ser una opción que permita leer al mismo tiempo, estado de tiempo, estado del led y estado del boton._**
    *   ¿Qué diferencias fundamentales existen entre estas dos alternativas de lectura en términos de respuesta y complejidad?\
**_Respuesta: Tal como lo explicamos anteriormente, todo estara ligado al bloqueo que impedira la lectura del boton mientras se cumple el tiempo, entre mas largo sea el tiempo del delay, mas probabilidad existe de falsos positivos por parte de la lectura del boton._**
*   **Impacto de la Duración del Tiempo de Encendido:**
    *   ¿Cambiarían las respuestas a las preguntas anteriores si el tiempo de encendido del LED fuera sensiblemente más grande, por ejemplo, **2 segundos**?\
**_Respuesta: Totalmente, deberia esperar 2 segundos para leer el boton, si se oprime y se suelta antes de este tiempo, nunca lo vera._**
    *   ¿Y si fuera sensiblemente más chico, por ejemplo, **50 ms**? ¿Cómo afectarían estos cambios a la lógica de detección del pulsador y a la percepción del parpadeo?\
**_Respuesta: Al ser un valor tan bajo el proceso de pulsación seria captado mas facilmente por el micro, sin persivirse posibles falsos positivos en el proceso_**
