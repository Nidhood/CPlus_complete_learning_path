#ifndef MOTIONDATACALCULATOR_H
#define MOTIONDATACALCULATOR_H

// ################################################################## Inclusión de las librerías ##################################################################

#include "Arduino.h"

// ###################################################################### Variables globales ######################################################################

#define PI 3.1415926535897932384626433832795    // Valor de PI.
#define QUEUE_SIZE 10                           // Tamaño de la cola para almacenar las últimas velocidades lineales.
#define INTERVAL 5                              // Intervalo de tiempo para.
#define NUM_PULSES 2                            // Cantidad de pulsos.

// ################################################################## Definición de los estados de la máquina de estados finitos (FSM) para el cálculo de los datos de movimiento circular uniforme (MCU) ##################################################################

typedef enum{
    WAITING_FOR_PULSES,                        // Estado para esperar pulsaciones.

    COUNTING_PULSES,                           // Estado para esperar pulsaciones.
    COUNTING_FIRST_PULSE,                      // Estado para contar el primer pulso.
    COUNTING_SECOND_PULSE,                     // Estado para contar el segundo pulso.
    COUNTING_THIRD_PULSE,                       // Estado para contar el tercer pulso.
    COUNTING_FOURTH_PULSE,                      // Estado para contar el cuarto pulso.
    CALCULATING_MOTION_DATA                    // Estado para calcular los datos de movimiento circular uniforme (MCU).
} MotionStates;

// ################################################################ Definición de las estructuras #################################################################

// Estructura sensorHallEffect que contiene los pines del sensor de efecto Hall.
typedef struct{
    int digitalPin;                       // Pin digital del sensor de efecto Hall.
} SensorHallEffect;

// Estructura FSMVariables que contiene las variables necesarias para el funcionamiento de la máquina de estados finitos (FSM).
typedef struct{
    MotionStates motionState;                               // Estado actual de la FSM.
    int pulse;                                  // Contador de pulsos.
    unsigned long previousTime;                 // Tiempo desde el último pulso (espera al siguiente intervalo de pulsos).
    unsigned long previousTime2;                // Tiempo desde el último pulso (espera al siguiente intervalo de tiempo).
    unsigned long currentTime;                  // Tiempo actual (espera al siguiente intervalo de pulsos).
    unsigned long currentTime2;                 // Tiempo actual (espera al siguiente intervalo de tiempo).
    unsigned long elapsedTime;                  // Tiempo transcurrido.
    unsigned long totalPeriod;                  // Periodo total de los pulsos.


    // Para calcular la velocidad promedio:
    unsigned long accumulatedElapsedTime;       // Tiempo total transcurrido.
    float velocityQueue[QUEUE_SIZE];            // Arreglo para almacenar las últimas velocidades lineales.
    int queueIndex;                             // Índice para seguir la posición actual en la cola.

} FSMVariables;

// Estructura motionData que contiene los datos de movimiento circular uniforme (MCU).
typedef struct{
    float angularVelocity;                      // Velocidad angular    (revoluciones / segundos).
    float linearVelocity;                       // Velocidad lineal     (m/s).
    float distance;                             // Distancia recorrida  (m).
    float maxVelocity;                          // Velocidad máxima     (m/s).
    float averageVelocity;                      // Velocidad promedio   (m/s).
} MotionData;

// ################################################################## Declaración de las funciones ##################################################################

// Constructor o configuración inicial de la estructura sensorHallEffect.
void initializeSensorHallEffect(SensorHallEffect* sensor, const int digitalPin);

// Constructor o configuración inicial de la estructura FSMVariables.
void initializeFSMVariables(FSMVariables* fsmVariables);

// Constructor o configuración inicial de la estructura motionData.
void initializeMotionData(MotionData* motionData);

// Máquina de estados finitos (FSM) para el cálculo de los datos de movimiento circular uniforme (MCU).
void calculateMotionDataFSM(SensorHallEffect* sensor, FSMVariables* fsmVariables, MotionData* motionData, float RADIUS);

// Función que calcula la velocidad angular     (m/s).
void calculateAngularVelocity(MotionData* motionData, FSMVariables* fsmVariables);

// Función que calcula la velocidad lineal      (m/s).
void calculateLinearVelocity(MotionData* motionData, float radius);

// Función que calcula la distancia recorrida   (m).
void calculateDistance(MotionData* motionData, FSMVariables* fsmVariables);

// Función que calcula la velocidad máxima      (m/s).
void calculateMaxVelocity(MotionData* motionData);

// Función que calcula la velocidad promedio    (m/s).
void calculateAverageVelocity(MotionData* motionData, FSMVariables* fsmVariables);

// Función que calcula la velocidad             (km/h).
float calculateVelocityKMH(float linearVelocity);

// Función que calcula la velocidad             (mi/h).
float calculateVelocityMIH(float linearVelocity);

#endif