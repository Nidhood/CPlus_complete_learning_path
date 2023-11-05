# Control de LED mediante Pulsaciones

Este proyecto permite controlar el parpadeo de LEDs al presionar pulsadores, asegurando una gestión precisa del tiempo y condiciones específicas.

## Configuración de Pines

En la etapa de definición de pines, se establecen las conexiones para LEDs (pinLed1 y pinLed2) y pulsadores (pinButton1 y pinButton2).

## Configuración Inicial

En la función `setup()`, se configuran los pines de LEDs como salidas y los pines de pulsadores como entradas con resistencias pull-up.

## Lectura de Estados

En el bucle principal (`loop()`), se monitorean constantemente los estados de los pulsadores (stateButton1 y stateButton2).

## Detección de Pulsaciones y Llamada a `alternateBlink()`

Si algún pulsador se presiona, se activa la función `alternateBlink()` para alternar el parpadeo entre LED1 y LED2.

## Función `alternateBlink()`

Esta función gestiona el parpadeo alternante entre LED1 y LED2, calculando tiempos precisos para un ciclo útil del 66%.

Este código demuestra una implementación técnica para un control efectivo del parpadeo de LEDs en respuesta a la activación de pulsadores, garantizando precisión y sincronización.
