#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>

// Definición de la estructura Message
typedef struct AMessage {
  char nombre[10];   // Nombre
  int cantidad;      // Cantidad (entero)
} Message;           // Alias para la estructura

// Declaración de la cola
QueueHandle_t xQueue;

// Prototipos de las tareas
void sendTask(void *pvParameters);    // Tarea para enviar datos a la cola
void reciveTask(void *pvParameters);  // Tarea para recibir datos de la cola

void setup() {
  Serial.begin(115200);  // Inicializa la comunicación serie para depuración

  // Crear una cola capaz de almacenar 10 elementos de tipo Message
  xQueue = xQueueCreate(10, sizeof(Message));
  if (xQueue == NULL) {
    Serial.println("Falló la creación de la cola");
  } else {
    Serial.println("Cola creada exitosamente");
  }

  // Crear las tareas:
  // Crear la tarea de envío de datos a la cola
  xTaskCreate(sendTask, "Tarea de envío", 200, NULL, 1, NULL);
  
  // Crear la tarea de recepción de datos desde la cola
  xTaskCreate(reciveTask, "Tarea de recepción", 200, NULL, 1, NULL);

  // Inicia el planificador de FreeRTOS
  vTaskStartScheduler();
}

void loop() {
  // No se usa en FreeRTOS; las tareas se ejecutan de manera cooperativa
}

// Tarea que envía datos a la cola
void sendTask(void *pvParameters) {
  Serial.println("Iniciando tarea de emisión");

  for(;;) {
    Serial.println("En la tarea de enviar");

    // Crear el objeto de tipo Message para enviar
    Message objetoEnviar = {"TuNombre", 789};

    // Simular un retraso de 2 segundos (2000 ms)
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Enviar el objeto a la cola
    Serial.println("Enviando objeto a la cola...");
    if (xQueueSend(xQueue, &objetoEnviar, (TickType_t) 20) != pdPASS) {
      Serial.println("Falló el envío a la cola");
    } else {
      Serial.println("Objeto enviado a la cola");
    }

    // Simular un retraso largo para esperar hasta el próximo envío
    vTaskDelay(pdMS_TO_TICKS(10000));  // 10 segundos
  }
}

// Tarea que recibe datos de la cola
void reciveTask(void *pvParameters) {
  Serial.println("Iniciando tarea de recepción");

  Message objetoRecibido;  // Variable para almacenar el objeto recibido

  for(;;) {
    Serial.println("Esperando recibir datos de la cola...");

    // Intentar recibir un objeto de la cola, con un tiempo de espera de 20 segundos
    if (xQueueReceive(xQueue, &objetoRecibido, pdMS_TO_TICKS(20000)) == pdPASS) {
      Serial.println("Objeto recibido de la cola...");

      // Imprimir los valores del objeto recibido
      Serial.print("Nombre: ");
      Serial.println(objetoRecibido.nombre);
      Serial.print("Cantidad: ");
      Serial.println(objetoRecibido.cantidad);
    } else {
      Serial.println("No se recibió ningún objeto en el tiempo especificado");
    }
  }
}
