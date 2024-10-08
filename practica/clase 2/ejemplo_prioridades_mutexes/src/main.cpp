#include <Arduino.h>  // Incluye la librería de Arduino para poder usar Serial
#include <Arduino_FreeRTOS.h>  // Incluye FreeRTOS para gestionar tareas y sincronización
#include <task.h>
#include <semphr.h>  // Librería para usar semáforos en FreeRTOS

// Prototipos de las funciones de las tareas
void tarea1(void *pvParameters);
void tarea2(void *pvParameters);
void tarea3(void *pvParameters);

// Definición de las prioridades de las tareas
#define PRIORIDAD_TAREA1 2
#define PRIORIDAD_TAREA2 2
#define PRIORIDAD_TAREA3 2  // Todas tienen la misma prioridad en este caso

// Definición del semáforo
SemaphoreHandle_t semaforo;

void setup() {
    // Inicializa la comunicación serial
    Serial.begin(115200);

    // Creación de las tareas con sus respectivas prioridades
    xTaskCreate(tarea1, "Tarea 1", 200, NULL, PRIORIDAD_TAREA1, NULL);
    xTaskCreate(tarea2, "Tarea 2", 200, NULL, PRIORIDAD_TAREA2, NULL);
    xTaskCreate(tarea3, "Tarea 3", 200, NULL, PRIORIDAD_TAREA3, NULL);

    // Crear el semáforo binario
    semaforo = xSemaphoreCreateBinary();
    if( semaforo == NULL ) {
        // Si el semáforo no se crea correctamente, se imprime un mensaje de error
        Serial.println("Error al crear el semáforo");
    } else {
        // Inicialmente, otorgamos el semáforo para que esté disponible para la primera tarea
        xSemaphoreGive(semaforo);
    }

    // Inicia el scheduler (planificador) de FreeRTOS
    vTaskStartScheduler();
}

void loop() {
    // El loop no se usará porque el scheduler de FreeRTOS está ejecutando las tareas
}

// Implementación de las tareas

// Tarea 1
void tarea1(void *pvParameters) {
    for(;;) {
        // Intentamos tomar el semáforo con un tiempo de espera de 10 ticks
        if ( xSemaphoreTake(semaforo, 10) == pdTRUE) {
            // Si se toma el semáforo, la tarea se ejecuta
            Serial.println("Tarea 1 ejecutándose");
            // Liberamos el semáforo para que otras tareas puedan ejecutarse
            xSemaphoreGive(semaforo);
            // Aquí podrías poner un retraso o alguna otra acción, simulando trabajo
        }
    }
}

// Tarea 2
void tarea2(void *pvParameters) {
    for(;;) {
        // Intentamos tomar el semáforo con un tiempo de espera de 10 ticks
        if ( xSemaphoreTake(semaforo, 10) == pdTRUE) {
            // Si se toma el semáforo, la tarea se ejecuta
            Serial.println("Tarea 2 ejecutándose");
            // Liberamos el semáforo para que otras tareas puedan ejecutarse
            xSemaphoreGive(semaforo);
        }
    }
}

// Tarea 3
void tarea3(void *pvParameters) {
    for(;;) {
        // Intentamos tomar el semáforo con un tiempo de espera de 10 ticks
        if ( xSemaphoreTake(semaforo, 10) == pdTRUE) {
            // Si se toma el semáforo, la tarea se ejecuta
            Serial.println("Tarea 3 (alta prioridad) ejecutándose");
            // Liberamos el semáforo para que otras tareas puedan ejecutarse
            xSemaphoreGive(semaforo);
        }
    }
}