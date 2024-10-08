
# Trabajo Práctico Final - Sistemas de Tiempo Real

## Objetivo del Trabajo Práctico
Desarrollar un sistema embebido utilizando **FreeRTOS** en un microcontrolador (Arduino o compatible), el cual gestione al menos **4 interrupciones** diferentes y mantenga **2 tareas cíclicas** ejecutándose de manera continua. El sistema deberá manejar los eventos que generan las interrupciones, sincronizar las tareas de forma eficiente y garantizar el funcionamiento adecuado bajo condiciones de multitarea.

## Estructura del Sistema

### Componentes del Sistema
- **Microcontrolador**: Cualquier placa compatible con Arduino que soporte FreeRTOS (Arduino Uno, Mega, ESP32, etc.).
- **Periféricos**:
  - **4 fuentes de interrupciones**: Gestionar al menos 4 interrupciones provenientes de distintos periféricos (botones, sensores, timers, etc.).
  - **2 tareas cíclicas**: Crear dos tareas que se ejecuten continuamente, manejando algún tipo de monitoreo, control o procesamiento.
  - **Entradas/Salidas digitales**: Uso de LEDs o dispositivos similares para representar el estado del sistema.

### Requisitos Funcionales
1. **Manejo de Interrupciones**:
   - Implementar al menos 4 interrupciones diferentes, cada una asociada a periféricos como botones, sensores o timers.
   - Las interrupciones deben ser gestionadas mediante rutinas de servicio (ISR) y sincronizarse adecuadamente con las tareas.

2. **Tareas Cíclicas**:
   - Crear 2 tareas cíclicas que se ejecuten de forma continua y cumplan con alguna función de control, monitoreo o procesamiento de eventos.

3. **Sincronización y Protección de Recursos**:
   - Implementar mecanismos de sincronización como semáforos, colas o mutexes para asegurar el acceso controlado a recursos compartidos entre tareas e interrupciones.

## Requisitos de Documentación
1. **Código Documentado**:
   - Proveer el código completo, debidamente comentado, explicando cada parte del sistema (tareas, interrupciones, sincronización, etc.).

2. **Diagrama de Conexiones**:
   - Presentar un diagrama de conexiones detallado, que muestre cómo están conectados los distintos componentes del sistema (botones, sensores, LEDs, etc.).

3. **Informe Técnico**:
   - Incluir un documento con la descripción del problema y la solución implementada, justificando el uso de FreeRTOS y los componentes utilizados.
   - Explicar brevemente cada interrupción y su función en el sistema.
   - Describir cómo las tareas cíclicas interactúan con las interrupciones y cómo se asegura la sincronización entre ellas.

## Criterios de Evaluación
1. **Funcionamiento Correcto**: El sistema debe manejar las interrupciones y ejecutar las tareas cíclicas sin errores.
2. **Sincronización**: Las tareas y las interrupciones deben estar bien sincronizadas, evitando condiciones de carrera y garantizando la protección de los recursos compartidos.
3. **Documentación**: La entrega debe incluir el código, diagrama de conexiones, y un informe claro y completo que explique el funcionamiento del sistema.

## Entrega
- **Formato**: La entrega final deberá ser un archivo **.zip** o **.rar** que incluya:
  1. Código fuente completo.
  2. Diagrama de conexiones.
  3. Informe técnico.

