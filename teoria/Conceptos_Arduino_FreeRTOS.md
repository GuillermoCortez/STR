# Conceptos de Arduino y FreeRTOS

## Índice
- [volatile en Arduino y C/C++](#volatile-en-arduino-y-cc)
- [attachInterrupt() en Arduino](#attachinterrupt-en-arduino)
- [Ticks en FreeRTOS](#ticks-en-freertos)
- [pdMS_TO_TICKS() y portTICK_PERIOD_MS](#pdms_to_ticks-y-porttick_period_ms)
- [vTaskDelay() en FreeRTOS](#vtaskdelay-en-freertos)
- [Comparación: vTaskDelay() vs vTaskDelayUntil()](#comparación-vtaskdelay-vs-vtaskdelayuntil)
- [Resumen](#resumen)

---

## `volatile` en Arduino y C/C++

La palabra clave **`volatile`** se utiliza para indicarle al compilador que una variable puede cambiar su valor de manera inesperada, fuera del flujo normal del programa. Esto es útil en sistemas embebidos, como Arduino, donde el hardware o interrupciones externas pueden modificar el valor de una variable sin que el compilador sea consciente de ello.

### ¿Qué hace `volatile`?

Cuando declaras una variable como **`volatile`**, le estás diciendo al compilador que:
- No debe optimizar el acceso a esa variable, ya que su valor puede cambiar en cualquier momento debido a factores externos, como una interrupción, el hardware, o incluso otra tarea o hilo en paralelo.
- Sin `volatile`, el compilador podría optimizar el código y no volver a leer el valor de una variable que no parece cambiar.

### Ejemplo de uso de `volatile` con interrupciones

```cpp
volatile int contadorPulsos = 0;

void setup() {
    pinMode(2, INPUT);
    attachInterrupt(digitalPinToInterrupt(2), contarPulsos, RISING);
    Serial.begin(9600);
}

void loop() {
    Serial.print("Pulsos detectados: ");
    Serial.println(contadorPulsos);
    delay(1000);
}

void contarPulsos() {
    contadorPulsos++;
}
```

---

## `attachInterrupt()` en Arduino

La función **`attachInterrupt()`** se utiliza para asignar una interrupción a un pin digital específico de Arduino. Esto permite que una función ISR (Interrupt Service Routine) se llame automáticamente cuando ocurra un evento en el pin, como un cambio en su estado.

### Sintaxis de `attachInterrupt()`

```cpp
attachInterrupt(digitalPinToInterrupt(pin), ISR, mode);
```

- **`digitalPinToInterrupt(pin)`**: Convierte un número de pin digital de Arduino en el número de interrupción correspondiente.
- **`ISR`**: Es el nombre de la función que deseas ejecutar cuando ocurra la interrupción.
- **`mode`**: Define el tipo de evento que activará la interrupción, como:
    - `LOW`: Activa la interrupción cuando el pin está en estado bajo.
    - `CHANGE`: Activa cuando el pin cambia de estado (alto a bajo o viceversa).
    - `RISING`: Activa cuando el pin pasa de bajo a alto.
    - `FALLING`: Activa cuando el pin pasa de alto a bajo.

---

## Ticks en FreeRTOS

Un **tick** en FreeRTOS es una unidad de tiempo que utiliza el sistema operativo para gestionar la ejecución de tareas. Cada vez que ocurre un tick, FreeRTOS revisa si alguna tarea debe ser ejecutada o suspendida.

### Uso de ticks en FreeRTOS

- **Planificación de tareas**: Los ticks ayudan a FreeRTOS a determinar cuándo debe ejecutar una tarea.
- **Delays y Timers**: Funciones como `vTaskDelay()` utilizan ticks para calcular el tiempo de espera.
- **Sistemas en tiempo real**: Los ticks garantizan que las tareas se ejecuten dentro de sus restricciones de tiempo.

### Tasa de Ticks y configTICK_RATE_HZ

La constante **`configTICK_RATE_HZ`** define cuántos ticks ocurren por segundo. Por ejemplo, si **`configTICK_RATE_HZ`** es 1000, el sistema generará un tick cada milisegundo.

---

## `pdMS_TO_TICKS()` y `portTICK_PERIOD_MS`

### `pdMS_TO_TICKS()`
Es una macro que convierte milisegundos a ticks directamente, considerando la configuración de **`configTICK_RATE_HZ`**.

```cpp
TickType_t xDelay = pdMS_TO_TICKS(500);  // 500 ms convertido a ticks
vTaskDelay(xDelay);
```

### `portTICK_PERIOD_MS`
Es una constante que representa los milisegundos por tick. Se puede utilizar para convertir manualmente el tiempo en ticks.

```cpp
TickType_t xDelay = 500 / portTICK_PERIOD_MS;  // 500 ms a ticks
vTaskDelay(xDelay);
```

---

## `vTaskDelay()` en FreeRTOS

**`vTaskDelay()`** suspende la ejecución de una tarea durante un número determinado de ticks. La tarea entra en el estado **bloqueado** durante ese tiempo, permitiendo al planificador ejecutar otras tareas.

### Ejemplo de uso:

```cpp
void TareaEjemplo(void *pvParameters) {
    for(;;) {
        // Hacer algo
        vTaskDelay(pdMS_TO_TICKS(1000));  // Espera 1 segundo
    }
}
```

### Beneficios de `vTaskDelay()`:
- Evita el uso innecesario del CPU (al bloquear la tarea en lugar de usar un bucle de espera).
- Controla el tiempo de ejecución de manera eficiente.

---

## Comparación: `vTaskDelay()` vs `vTaskDelayUntil()`

### `vTaskDelay()`
El retraso es relativo al tick actual del sistema. La tarea se ejecutará después del tiempo especificado en ticks.

### `vTaskDelayUntil()`
Permite especificar un tiempo absoluto en el que la tarea debe ejecutarse, lo que es útil para tareas que necesitan ejecutarse en momentos específicos del sistema.

```cpp
TickType_t xLastWakeTime = xTaskGetTickCount();
for(;;) {
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));  // Ejecutar cada 1 segundo exacto
}
```

---

## Resumen
- `volatile` se usa para variables que pueden cambiar fuera del flujo normal del programa, como en interrupciones.
- `attachInterrupt()` es crucial para responder a eventos de hardware en Arduino.
- Los ticks en FreeRTOS sincronizan las tareas y garantizan el tiempo real.
- `vTaskDelay()` y `vTaskDelayUntil()` controlan la ejecución temporal de las tareas.
