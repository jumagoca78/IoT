# ==============================================================
# SIMULADOR DE PATOS - PATRON ESTRATEGIA (PYTHON)
# Elaborado por Juan Manuel Gonzalez Calleros
# Curso: Implementacion de Internet de las Cosas (IoT)
# Objetivo: separar los comportamientos que cambian de los objetos.
# Ejecutar: python3 main.py
# ==============================================================

from abc import ABC, abstractmethod

# Una clase base abstracta establece el CONTRATO de las estrategias.
# Cada estrategia de vuelo debe ofrecer el mismo metodo volar().
class ComportamientoVuelo(ABC):
    @abstractmethod
    def volar(self):
        """Realiza el comportamiento de vuelo."""

# Estrategias concretas: encapsulan las diferentes variantes de vuelo.
class VolarConAlas(ComportamientoVuelo):
    def volar(self):
        print("Vuelo con alas")

class NoVolar(ComportamientoVuelo):
    def volar(self):
        print("No puedo volar")

class VolarConCohete(ComportamientoVuelo):
    def volar(self):
        print("¡Vuelo impulsado por un cohete!")

# Segundo conjunto INDEPENDIENTE de estrategias: los graznidos.
class ComportamientoGraznido(ABC):
    @abstractmethod
    def graznar(self):
        """Reproduce el sonido del pato."""

class Graznar(ComportamientoGraznido):
    def graznar(self):
        print("Quack, quack")

class Chillar(ComportamientoGraznido):
    def graznar(self):
        print("Squeak, squeak")

class Silencio(ComportamientoGraznido):
    def graznar(self):
        print("(Sin sonido)")

# CONTEXTO del patron: un pato TIENE comportamientos (composicion).
# Duck NO implementa el vuelo ni el graznido: DELEGA en sus objetos.
class Pato(ABC):
    def __init__(self, vuelo: ComportamientoVuelo, voz: ComportamientoGraznido):
        self._vuelo = vuelo
        self._voz = voz

    def nadar(self):
        print("Todos los patos de esta simulacion flotan")

    def ejecutar_vuelo(self):
        self._vuelo.volar()  # Delegacion y polimorfismo.

    def ejecutar_graznido(self):
        self._voz.graznar()

    def cambiar_vuelo(self, nuevo_vuelo: ComportamientoVuelo):
        self._vuelo = nuevo_vuelo  # Cambio en tiempo de ejecucion.

    def cambiar_graznido(self, nueva_voz: ComportamientoGraznido):
        self._voz = nueva_voz

    @abstractmethod
    def mostrar(self):
        """Cada especie describe su apariencia."""

# La herencia solo especializa la apariencia y selecciona estrategias iniciales.
class Mallard(Pato):
    def __init__(self):
        super().__init__(VolarConAlas(), Graznar())
    def mostrar(self):
        print("Pato silvestre Mallard")

class Redhead(Pato):
    def __init__(self):
        super().__init__(VolarConAlas(), Graznar())
    def mostrar(self):
        print("Pato de cabeza roja Redhead")

class Rubber(Pato):
    def __init__(self):
        super().__init__(NoVolar(), Chillar())
    def mostrar(self):
        print("Pato de goma Rubber")

class Decoy(Pato):
    def __init__(self):
        super().__init__(NoVolar(), Silencio())
    def mostrar(self):
        print("Pato de madera Decoy")

# Punto de entrada: probar cuatro patos y la sustitucion de estrategias.
def main():
    patos = [Mallard(), Redhead(), Rubber(), Decoy()]
    for pato in patos:
        print("\n---")
        pato.mostrar()
        pato.nadar()
        pato.ejecutar_vuelo()
        pato.ejecutar_graznido()

    print("\n--- Cambio dinamico del Mallard ---")
    mallard = patos[0]
    mallard.cambiar_vuelo(VolarConCohete())
    mallard.cambiar_graznido(Silencio())
    mallard.ejecutar_vuelo()
    mallard.ejecutar_graznido()

if __name__ == "__main__":
    main()
