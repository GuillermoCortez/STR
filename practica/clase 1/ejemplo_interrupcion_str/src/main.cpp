#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

// Variable global volátil para indicar cuando ocurre un evento
volatile bool hayEvento = false;

// ISR (Interrupción) que se ejecuta cuando se detecta el evento en el pin 2
void handlerEvent () {
  // Marcar que ha sucedido un evento
  hayEvento = true;
}

// Tarea que monitorea la variable "hayEvento" y actúa cuando ocurre un evento
void ImprimirEvento(void *pvParameters) {
  while (true) {
    // Si hay un evento, imprime el mensaje
    if (hayEvento) {
      Serial.println("Sucedió un evento");
      // Restablecer la variable para indicar que el evento ha sido procesado
      hayEvento = false;
    }
  }
}

// Tarea que genera una carga de trabajo intensa en el sistema
void GenerarCargaTrabajo(void *pvParameters) {
  while (true) {
    // Genera un bucle largo de trabajo con un contador
    for (int i = 0; i < 10000000; i++) {
      Serial.print("Dentro de la carga de trabajo n: ");
      Serial.println(i);
    }
  }
}

void setup() {
  // Inicializar el monitor serie
  Serial.begin(115200);
  Serial.println("Iniciando...");

  // Crear la tarea que imprime el evento cuando sucede
  xTaskCreate(ImprimirEvento, "imprimirEvento", 200, NULL, 1, NULL);
  
  // Crear la tarea que simula una carga de trabajo
  xTaskCreate(GenerarCargaTrabajo, "generarCarga", 200, NULL, 1, NULL);

  // Configurar el pin 2 como entrada con resistencia interna de pull-up activada
  pinMode(2, INPUT_PULLUP);

  // Adjuntar la interrupción al pin 2. Se activa en el flanco de bajada (FALLING)
  attachInterrupt(digitalPinToInterrupt(2), handlerEvent, FALLING);

  // Iniciar el planificador de FreeRTOS, las tareas comenzarán a ejecutarse
  vTaskStartScheduler();
}

void loop() {
  // El bucle loop no se usa en FreeRTOS ya que las tareas son gestionadas por el planificador
}
