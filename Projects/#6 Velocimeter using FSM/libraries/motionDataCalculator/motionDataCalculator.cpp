#include "motionDataCalculator.h"

// Definición de las funciones:

// Constructor o configuración inicial de la estructura sensorHallEffect:
void initializeSensorHallEffect(SensorHallEffect* sensor, const int digitalPin){

    // Ajustamos pines del módulo de sensor Hall:
    sensor->digitalPin = digitalPin;

    // Configuramos los pines del módulo de sensor Hall:
    pinMode(sensor->digitalPin, INPUT);
}

// Constructor o configuración inicial de la estructura FSMVariables:
void initializeFSMVariables(FSMVariables* fsmVariables){

    // Inicializamos las variables de la FSM:
    fsmVariables->motionState = WAITING_FOR_PULSES;
    fsmVariables->pulse = 0;
    fsmVariables->previousTime = 0.0;
    fsmVariables->previousTime2 = 0.0;
    fsmVariables->currentTime = 0.0;
    fsmVariables->currentTime2 = 0.0;
    fsmVariables->elapsedTime = 0.0;
    fsmVariables->accumulatedElapsedTime = 0.0;
    fsmVariables->queueIndex = 0;
    fsmVariables->velocityQueue[QUEUE_SIZE] = {0.0};
}

// Constructor o configuración inicial de la estructura motionData:
void initializeMotionData(MotionData* motionData){

    // Inicializamos las variables de los datos de movimiento circular uniforme (MCU):
    motionData->angularVelocity = 0.0;
    motionData->linearVelocity = 0.0;
    motionData->distance = 0.0;
    motionData->maxVelocity = 0.0;
    motionData->averageVelocity = 0.0;
}

// Máquina de estados finitos (FSM) para el cálculo de los datos de movimiento circular uniforme (MCU):
void calculateMotionDataFSM(SensorHallEffect* sensor, FSMVariables* fsmVariables, MotionData* motionData, float RADIUS){

    // Obtenemos el tiempo actual (para empezar el intervalo de pulsos):
    fsmVariables->currentTime2 = millis();

    // Solo continuar si ha pasado el intervalo de tiempo
    if (fsmVariables->currentTime2 - fsmVariables->previousTime2 >= INTERVAL) {

        // Actualizar el tiempo previo
        fsmVariables->previousTime2 = fsmVariables->currentTime2;

        // Leer el estado actual del sensor:
        int sensorState = digitalRead(sensor->digitalPin);

        // Variable estática para mantener el estado anterior del sensor
        static int previousSensorState = LOW;

        // Actualizar el estado de la FSM:
        switch (fsmVariables->motionState) {

            // Estado para esperar el primer pulso:
            case WAITING_FOR_PULSES:
                if (sensorState == HIGH) {
                    // Reiniciar pulsaciones:
                    fsmVariables->pulse = 0;

                    // Obtenemos el tiempo actual (para empezar con delta de t):
                    fsmVariables->previousTime = millis();

                    // Guardar el estado anterior del sensor:
                    previousSensorState = sensorState;

                    // Pasamos al siguiente estado:
                    fsmVariables->motionState = COUNTING_FIRST_PULSE;
                }
                break;

                // Estado para contar el primer pulso:
            case COUNTING_FIRST_PULSE:
                // Verificar si se ha producido un pulso y el estado anterior era LOW
                if (sensorState == LOW && previousSensorState == HIGH) {
                    // Incrementar el contador de pulsos
                    fsmVariables->pulse++;

                    // Sí se ha alcanzado el número de pulsos especificado, cambiar al estado COUNTING_SECOND_PULSE
                    if (fsmVariables->pulse >= 1) {
                        // Obtenemos el tiempo actual:
                        fsmVariables->currentTime = millis();

                        // Calculamos el delta de tiempo:
                        fsmVariables->elapsedTime = fsmVariables->currentTime - fsmVariables->previousTime;

                        // Calculamos el delta de tiempo acumulado:
                        fsmVariables->accumulatedElapsedTime += fsmVariables->elapsedTime;

                        // Guardamos el tiempo actual como el tiempo previo para el próximo pulso
                        fsmVariables->previousTime = fsmVariables->currentTime;

                        // Guardar el estado anterior del sensor:
                        previousSensorState = sensorState;

                        // Pasamos al siguiente estado:
                        fsmVariables->motionState = COUNTING_SECOND_PULSE;
                    }
                }
                break;

                // Estado para contar el segundo pulso:
            case COUNTING_SECOND_PULSE:
                // Verificar si se ha producido un pulso y el estado anterior era LOW
                if (sensorState == LOW && previousSensorState == HIGH) {
                    // Incrementar el contador de pulsos
                    fsmVariables->pulse++;

                    // Sí se ha alcanzado el número de pulsos especificado, cambiar al estado COUNTING_THIRD_PULSE
                    if (fsmVariables->pulse >= 2) {
                        // Obtenemos el tiempo actual:
                        fsmVariables->currentTime = millis();

                        // Calculamos el delta de tiempo:
                        fsmVariables->elapsedTime = fsmVariables->currentTime - fsmVariables->previousTime;

                        // Calculamos el delta de tiempo acumulado:
                        fsmVariables->accumulatedElapsedTime += fsmVariables->elapsedTime;

                        // Guardamos el tiempo actual como el tiempo previo para el próximo pulso
                        fsmVariables->previousTime = fsmVariables->currentTime;

                        // Guardar el estado anterior del sensor:
                        previousSensorState = sensorState;

                        // Pasamos al siguiente estado:
                        fsmVariables->motionState = COUNTING_THIRD_PULSE;
                    }
                }
                break;

                // Estado para contar el tercer pulso:
            case COUNTING_THIRD_PULSE:
                // Verificar si se ha producido un pulso y el estado anterior era LOW
                if (sensorState == LOW && previousSensorState == HIGH) {
                    // Incrementar el contador de pulsos
                    fsmVariables->pulse++;

                    // Sí se ha alcanzado el número de pulsos especificado, cambiar al estado CALCULATING_MOTION_DATA
                    if (fsmVariables->pulse >= 3) {
                        // Obtenemos el tiempo actual:
                        fsmVariables->currentTime = millis();

                        // Calculamos el delta de tiempo:
                        fsmVariables->elapsedTime = fsmVariables->currentTime - fsmVariables->previousTime;

                        // Calculamos el delta de tiempo acumulado:
                        fsmVariables->accumulatedElapsedTime += fsmVariables->elapsedTime;

                        // Guardamos el tiempo actual como el tiempo previo para el próximo pulso
                        fsmVariables->previousTime = fsmVariables->currentTime;

                        // Guardar el estado anterior del sensor:
                        previousSensorState = sensorState;

                        // Pasamos al siguiente estado:
                        fsmVariables->motionState = COUNTING_FOURTH_PULSE;
                    }
                }
                break;

                // Estado para contar el cuarto pulso:
            case COUNTING_FOURTH_PULSE:
                // Verificar si se ha producido un pulso y el estado anterior era LOW
                if (sensorState == LOW && previousSensorState == HIGH) {
                    // Incrementar el contador de pulsos
                    fsmVariables->pulse++;

                    // Sí se ha alcanzado el número de pulsos especificado, cambiar al estado CALCULATING_MOTION_DATA
                    if (fsmVariables->pulse >= 4) {
                        // Obtenemos el tiempo actual:
                        fsmVariables->currentTime = millis();

                        // Calculamos el delta de tiempo:
                        fsmVariables->elapsedTime = fsmVariables->currentTime - fsmVariables->previousTime;

                        // Calculamos el delta de tiempo acumulado:
                        fsmVariables->accumulatedElapsedTime += fsmVariables->elapsedTime;

                        // Guardar el estado anterior del sensor:
                        previousSensorState = sensorState;

                        // Pasamos al siguiente estado:
                        fsmVariables->motionState = CALCULATING_MOTION_DATA;
                    }
                }
                break;

                // Estado para calcular los datos de movimiento circular uniforme (MCU):
            case CALCULATING_MOTION_DATA:
                // Calculamos el delta de tiempo acumulado:
                fsmVariables->accumulatedElapsedTime += fsmVariables->elapsedTime;

                // Evitamos la división por 0:
                if (fsmVariables->elapsedTime > 0) {
                    // Hallamos el tiempo transcurrido (segundos):
                    // Serial.print("Delta de tiempo: ");
                    // Serial.println(fsmVariables->elapsedTime * 0.001);

                    // Hallamos W (radianes/segundo):
                    calculateAngularVelocity(motionData, fsmVariables);
                    // Serial.print("Velocidad angular: ");
                    // Serial.println(motionData->angularVelocity);

                    // Hallamos la velocidad lineal (m/s):
                    calculateLinearVelocity(motionData, RADIUS);
                    // Serial.print("Velocidad lineal: ");
                    // Serial.println(motionData->linearVelocity);

                    // Hallamos la distancia recorrida (m):
                    calculateDistance(motionData, fsmVariables);
                    // Serial.print("Distancia recorrida: ");
                    // Serial.println(motionData->distance);

                    // Hallamos la velocidad máxima (m/s):
                    calculateMaxVelocity(motionData);
                    // Serial.print("Velocidad máxima: ");
                    // Serial.println(motionData->maxVelocity);

                    // Hallamos la velocidad promedio (m/s):
                    calculateAverageVelocity(motionData, fsmVariables);
                    // Serial.print("Velocidad promedio: ");
                    // Serial.println(motionData->averageVelocity);
                }

                // Reiniciar FSM:
                fsmVariables->motionState = WAITING_FOR_PULSES;
                break;
        }

        // Guardar el estado actual del sensor para la próxima iteración (para asegurar el correcto conteo de pulsos):
        previousSensorState = sensorState;
    }
}


// Función que calcula la velocidad angular     (m/s).
void calculateAngularVelocity(MotionData* motionData, FSMVariables* fsmVariables){

    // Hallamos W (radianes/segundo):
    motionData->angularVelocity = (2 * PI * (NUM_PULSES - 1)) / (fsmVariables->elapsedTime * 0.001);
}

// Función que calcula la velocidad lineal      (m/s).
void calculateLinearVelocity(MotionData* motionData, float radius){

    // Hallamos la velocidad lineal:
    motionData->linearVelocity = motionData->angularVelocity * radius * 3.6;
}

// Función que calcula la distancia recorrida   (m).
void calculateDistance(MotionData* motionData, FSMVariables* fsmVariables){

    // Hallamos la distancia recorrida:
    motionData->distance = (motionData->linearVelocity / 3600.0) * (fsmVariables->accumulatedElapsedTime / 1000.0);

}

// Función que calcula la velocidad máxima      (m/s).
void calculateMaxVelocity(MotionData* motionData){

    // Hallamos la velocidad máxima:
    if(motionData->linearVelocity > motionData->maxVelocity){
        motionData->maxVelocity = motionData->linearVelocity;
    }
}

// Función que calcula la velocidad promedio    (m/s).
void calculateAverageVelocity(MotionData* motionData, FSMVariables* fsmVariables){

    // Hallamos el promedio, con base a los datos almacenados dentro de la cola:
    fsmVariables->velocityQueue[fsmVariables->queueIndex] = motionData->linearVelocity; // Agregar la velocidad lineal a la cola

    // Incrementar el índice de la cola y volver al principio si es necesario
    fsmVariables->queueIndex = (fsmVariables->queueIndex + 1) % QUEUE_SIZE;

    // Si hemos tomado suficientes muestras, calcular y mostrar el promedio
    if (fsmVariables->queueIndex == 0) {

        // Variable auxiliar para sumar los valores:
        float sum = 0.0;

        // Sumar todas las velocidades en la cola
        for (int i = 0; i < QUEUE_SIZE; i++) {
            sum += fsmVariables->velocityQueue[i];
        }

        // Calculamos el promedio:
        motionData->averageVelocity = sum / QUEUE_SIZE;
    }
}

// Función que calcula la velocidad             (km/h).
float calculateVelocityKMH(float linearVelocity){

    // (m / s) -> (km / h) : (1 m/s) = (1 km / 1000 m) * (3600 seg / 1 h) : (1 m/s) = (3.6 km/h).
    return linearVelocity * 3.6;

};

// Función que calcula la velocidad             (mi/h).
float calculateVelocityMIH(float linearVelocity){

    // (m / s) -> (mi / h) : (1 m/s) = (1 mi / 1609.34 m) * (3600 seg / 1 h) : (1 m/s) = (2.236941 mi/h).
    return linearVelocity * 2.23691;
};