#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

// Definir el pin del LED
const int ledPin = 13;

// Prototipos de las tareas
void TaskEncender(void *pvParameters);
void TaskApagar(void *pvParameters);

// Declaración de los punteros de las tareas
TaskHandle_t xHandleEncender = NULL;
TaskHandle_t xHandleApagar = NULL;


void setup() {
  Serial.begin(115200);
  Serial.println("Todo OK");
  // Inicializar el pin del LED
  pinMode(ledPin, OUTPUT);
  // Crear las tareas
  xTaskCreate(TaskEncender, "Encender LED", 100, NULL, 1, &xHandleEncender);
  xTaskCreate(TaskApagar, "Apagar LED", 100, NULL, 1, &xHandleApagar);

  vTaskSuspend(xHandleApagar);
  // Iniciar el planificador de FreeRTOS
  vTaskStartScheduler();
}

void loop() {
  // No se usa en FreeRTOS
}

// Tarea para encender el LED
void TaskEncender(void *pvParameters) {
    Serial.println("Iniciando encender");
  for (;;) {
    // Encender el LED
    digitalWrite(ledPin, HIGH);
    Serial.println("LED encendido");

    // Mantener el LED encendido durante 1 segundo
    vTaskDelay(pdMS_TO_TICKS(1000));

    // Suspender esta tarea (Encender) y reanudar la tarea de Apagar
    vTaskResume(xHandleApagar); // Reanudar la tarea de Apagar
    vTaskSuspend(NULL);         // Suspender la tarea actual (Encender)
  }
}

// Tarea para apagar el LED
void TaskApagar(void *pvParameters) {
    Serial.println("Iniciando apagar");
  for (;;) {

    // Apagar el LED
    digitalWrite(ledPin, LOW);
    Serial.println("LED apagado");

    // Mantener el LED apagado durante 1 segundo
    vTaskDelay(pdMS_TO_TICKS(1000));

    // Suspender esta tarea (Apagar) y reanudar la tarea de Encender
    vTaskResume(xHandleEncender);// Reanudar la tarea de Encender
    vTaskSuspend(NULL);          // Suspender la tarea actual (Apagar)
  }
}
