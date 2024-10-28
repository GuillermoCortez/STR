# Trabajo Práctico Final - Sistemas de Tiempo Real

## Objetivo del Trabajo Práctico

Desarrollar un sistema embebido de control y monitoreo inteligente para una intersección utilizando **FreeRTOS** en un microcontrolador compatible con Arduino. El sistema gestionará el tráfico vehicular y peatonal, incluyendo la detección de vehículos de prioridad y alertas de cruce seguro, con al menos **6 interrupciones** diferentes y **1 tarea cíclica** continua para la sincronización y la gestión de eventos en tiempo real.

## Estructura del Sistema

### Componentes del Sistema

- **Microcontrolador**: Placa compatible con Arduino que soporte FreeRTOS (Arduino Mega, ESP32, etc.).
- **Sensores y Periféricos**:
  - **Sensores** para detectar vehículos en ambas calles.
  - **Sensores** para detectar la presencia de peatones sobre la línea de cebra en ambas calles.
  - **LEDs**: Rojos, amarillos y verdes para simular los semáforos de cada calle.
  - **Sirena** para señal sonora de alerta para peatones y alertas de cruce indebido por vehículos.

### Requisitos Funcionales

1. **Manejo de Interrupciones**:

   - Implementar **6 interrupciones** distintas:
     - **Interrupción por vehículo de prioridad** en cada calle. Cuando se detecte un vehículo prioritario (ambulancia, policía, bomberos), se deberá activar una señal luminosa especial en el semáforo para advertir al tráfico que el semáforo cambiará pronto para darle paso al vehículo prioritario, evitando cambios instantáneos que puedan causar accidentes. Esto constituye dos interrupciones, una por cada calle.
     - **Interrupción por cruce peatonal en luz verde** en cada calle. Un sensor detectará si un peatón comienza a cruzar sobre la línea de cebra cuando el semáforo está en verde para vehículos, activando una sirena de alerta. Esto constituye dos interrupciones, una por cada calle.
     - **Interrupción por vehículo cruzando en luz roja** en cada calle. Si un sensor detecta un vehículo en el paso de cebra cuando el semáforo está en rojo, se activará una sirena para alertar al automovilista. Esto constituye dos interrupciones, una por cada calle.

2. **Tarea Cíclica**:

   - **Tarea de rotación de semáforos**: Encargarse de rotar los semáforos de manera ordenada según los tiempos preestablecidos y las condiciones del tráfico detectadas.

3. **Sincronización y Protección de Recursos**:

   - Implementar **semáforos** y **mutexes** si es necesario, para controlar el acceso a recursos compartidos, evitando condiciones de carrera entre la tarea y las interrupciones.

### Casos de Evaluación

1. **Vehículos de prioridad en ambas calles**:

   - Al detectar un vehículo prioritario en cualquiera de las calles (cada calle constituye una interrupción), el semáforo de esa calle debe activar una señal luminosa de advertencia antes de cambiar a verde para darle paso, evitando cambios abruptos.
   - El otro semáforo se mantendrá en rojo mientras el vehículo prioritario cruza.

2. **Peatón cruzando en luz verde de vehículos**:

   - Cuando un peatón es detectado sobre la línea de cebra en un cruce donde el semáforo está en verde para vehículos, se activa la sirena de alerta.

3. **Vehículo cruzando en rojo**:

   - Si un vehículo es detectado sobre el paso de cebra con el semáforo en rojo, se activará una sirena para advertirlo.

4. **Tráfico en ambas calles**:

   - Ambos semáforos cambian de verde a rojo con tiempos iguales, ajustados en función del tráfico detectado por los sensores.

### Requisitos de Documentación

1. **Código Documentado**:

   - Incluir el código fuente completo, debidamente comentado para explicar cada parte del sistema (tareas, interrupciones, sincronización, etc.).

2. **Diagrama de Conexiones**:

   - Un diagrama que detalle la conexión de sensores, LEDs y sirena, usando una herramienta como Fritzing o similar.

3. **Informe Técnico**:

   - Un documento explicando el problema, la solución, el uso de FreeRTOS y la función de cada interrupción.
   - Descripción de cómo la tarea cíclica interactúa con las interrupciones y los mecanismos de sincronización empleados.

## Criterios de Evaluación

1. **Funcionamiento Correcto**: Manejo correcto de interrupciones y ejecución continua de tareas cíclicas.
2. **Sincronización y Eficiencia**: Buen control de sincronización entre la tarea e interrupciones, sin condiciones de carrera.
3. **Documentación Completa**: Incluir el código, diagramas y un informe técnico que detalle el funcionamiento del sistema.

## Entrega

La entrega debe realizarse en un archivo **.zip** o **.rar** que incluya:

- Código fuente completo en archivo **.ino**.
- Diagrama de conexiones.
- Informe técnico detallado.
