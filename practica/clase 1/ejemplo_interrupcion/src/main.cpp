#include <Arduino.h>

volatile bool eventTriggered = false;  // Variable para manejar el evento

// Evento manejador de interrupciones
void eventHandler() {
    eventTriggered = true;  // Cambia el estado de la variable cuando se dispara el evento
}

void setup() {
    Serial.begin(115200);

    // Configuramos el pin 2 como entrada y activamos la interrupción
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), eventHandler, FALLING);  // Interrupción en pin 2 cuando el botón se presiona
}

void loop() {
    if (eventTriggered) {  // Si el evento fue disparado
        Serial.println("Evento detectado!");
        eventTriggered = false;  // Reinicia el estado del evento
    }
    delay(5000);
}