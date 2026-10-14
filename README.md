
Dr. Juan Manuel González Calleros

Material de apoyo académico para el curso de Implementación de Internet de las Cosas (IoT).

Los ejemplos tienen fines educativos y pueden evolucionar conforme se incorporen nuevos contenidos y prácticas al curso.
# Implementación de Internet de las Cosas (IoT) — Códigos del curso

**Elaborado por Juan Manuel Gonzalez Calleros**  
**Material:** Ejemplos didácticos y prácticas de software

## Propósito del repositorio

Este repositorio reúne y organiza ejemplos de programación utilizados para enseñar cómo un sistema IoT pasa de **generar datos** a **procesarlos, almacenarlos, comunicarlos y convertirlos en acciones o visualizaciones para el usuario**.

El código acompaña el trabajo de modelado: **entidad-relación → modelo relacional → UML → responsabilidades y patrones → servicios → integración IoT**. Se utiliza con casos como CampusIoT, gimnasio inteligente, estacionamiento, parque, semáforos y casa sustentable.

> **Alcance de este paquete:** contiene exclusivamente las cuatro implementaciones del simulador de patos con el patrón **Estrategia (Strategy)**. Los ejemplos de MySQL, APIs, Observer y retos IoT corresponden a la ruta pedagógica general del curso; **no se incluyen en este ZIP**.

## ¿Qué problema resuelve el simulador de patos?

Un pato puede volar con alas, no volar o volar con un cohete; también puede graznar, chillar o guardar silencio. Si cada variante se codifica dentro de las subclases de pato, el código se duplica y cada nuevo comportamiento exige modificaciones repetidas.

El patrón **Estrategia** separa los comportamientos cambiantes en algoritmos independientes. Cada pato **tiene** una estrategia de vuelo y otra de graznido, **delega** su ejecución y puede **intercambiarlas en tiempo de ejecución**.

### Patos incluidos

| Tipo | Vuelo inicial | Graznido inicial |
| --- | --- | --- |
| Mallard (silvestre) | Con alas | Quack |
| Redhead (cabeza roja) | Con alas | Quack |
| Rubber (goma) | No vuela | Chillido |
| Decoy (madera) | No vuela | Silencio |

La demostración cambia al **Mallard** para que vuele con **cohete** y guarde **silencio**, sin reescribir su lógica de ejecución.

## Estructura real de este paquete

```text
IoT_DuckSimulator/
├── README.md              # Esta guía
├── C/
│   └── main.c             # Structs y punteros a función (C11)
├── Cpp/
│   └── main.cpp           # Clases abstractas y unique_ptr (C++17)
├── Java/
│   └── Main.java          # Interfaces e implementaciones (Java)
└── Python/
    └── main.py            # ABC, clases y composición (Python 3)
```

## Ejecutar los programas

Ejecuta los siguientes comandos dentro de la carpeta correspondiente:

**C (GCC):**
```bash
cd C
gcc -std=c11 -Wall -Wextra main.c -o patos
./patos
```

**C++ (G++):**
```bash
cd Cpp
g++ -std=c++17 -Wall -Wextra main.cpp -o patos
./patos
```

**Java (JDK):**
```bash
cd Java
javac Main.java
java Main
```

**Python:**
```bash
cd Python
python3 main.py
```

**Windows:** si compilas C o C++ con GCC/MinGW, ejecuta `patos.exe` en lugar de `./patos`.

## Comparación entre lenguajes

| Concepto | C | C++ | Java | Python |
| --- | --- | --- | --- | --- |
| Abstracción de estrategia | Tipo de puntero a función | Clase abstracta | `interface` | Clase `ABC` |
| Implementación concreta | Función | Clase derivada | Clase `implements` | Subclase |
| Contexto | `struct Pato` | `class Pato` | `abstract class Pato` | `class Pato` |
| Cambio dinámico | Reasignar puntero | Sustituir `unique_ptr` | Sustituir objeto referenciado | Sustituir objeto referenciado |
| Memoria | Arreglo automático | RAII y `unique_ptr` | Recolector de basura | Gestión automática de memoria |

**Nota:** la implementación en C reproduce la intención del patrón, pero no ofrece orientación a objetos ni interfaces de lenguaje nativas.

## Actividad propuesta

1. Dibuja el diagrama UML del ejemplo en uno de los lenguajes orientados a objetos.
2. Identifica **Context**, **Strategy** y **ConcreteStrategy**.
3. Ejecuta el programa y anticipa los resultados de los cuatro patos.
4. Agrega `VolarPlaneando` sin cambiar el método que ejecuta el vuelo.
5. Haz que Rubber pueda volar con cohete y explica por qué eso es posible.
6. Propón cómo aplicar el mismo diseño para intercambiar **procesadores de lecturas** o **protocolos de envío** en `NodoIoT`.

## Relación con el reto IoT

En un nodo IoT, la variación deja de ser `volar()` o `graznar()` y puede ser `procesar(lectura)` o `enviar(resultado)`. En lugar de crear una clase de dispositivo para cada combinación de algoritmos y protocolos, el contexto puede delegar a estrategias intercambiables. El diseño resultante facilita probar diferentes comportamientos y extender el software.

**Objetivo didáctico:** entender *por qué* se separan responsabilidades y *qué cambios* evita el patrón, no solamente memorizar código.

## Créditos

Material didáctico elaborado por **Juan Manuel Gonzalez Calleros**, para el bloque **Implementación de Internet de las Cosas (IoT)**. Ejemplo conceptual basado en el simulador de patos utilizado para introducir el patrón de diseño Strategy.
