/* ==============================================================
 * SIMULADOR DE PATOS - PATRON ESTRATEGIA (C++17)
 * Elaborado por Juan Manuel Gonzalez Calleros
 * Curso: Implementacion de Internet de las Cosas (IoT)
 * Compilar: g++ -std=c++17 -Wall -Wextra main.cpp -o patos
 * Ejecutar: ./patos
 * ============================================================= */
#include <iostream>  // Para imprimir resultados por consola.
#include <memory>    // unique_ptr y make_unique gestionan memoria automaticamente.
#include <vector>    // Permite reunir diferentes subclases de Pato.
using namespace std;

// CONTRATO abstracto: metodo virtual puro (= 0) obligatorio para cada estrategia.
// Destructor virtual: necesario para destruir subclases mediante puntero base.
struct ComportamientoVuelo {
    virtual ~ComportamientoVuelo() = default;
    virtual void volar() const = 0;
};
// Cada implementacion concreta encapsula un algoritmo distinto.
struct VolarConAlas : ComportamientoVuelo {
    void volar() const override { cout << "Vuelo con alas\n"; }
};
struct NoVolar : ComportamientoVuelo {
    void volar() const override { cout << "No puedo volar\n"; }
};
struct VolarConCohete : ComportamientoVuelo {
    void volar() const override { cout << "Vuelo impulsado por un cohete\n"; }
};

// SEGUNDA familia de estrategias: independiente del vuelo.
struct ComportamientoGraznido {
    virtual ~ComportamientoGraznido() = default;
    virtual void graznar() const = 0;
};
struct Graznar : ComportamientoGraznido {
    void graznar() const override { cout << "Quack, quack\n"; }
};
struct Chillar : ComportamientoGraznido {
    void graznar() const override { cout << "Squeak, squeak\n"; }
};
struct Silencio : ComportamientoGraznido {
    void graznar() const override { cout << "(Sin sonido)\n"; }
};

// CONTEXTO: el pato POSEE estrategias, pero ignora sus clases concretas.
class Pato {
    // unique_ptr expresa propiedad exclusiva y evita fugas de memoria.
    unique_ptr<ComportamientoVuelo> vuelo;
    unique_ptr<ComportamientoGraznido> voz;
public:
    Pato(unique_ptr<ComportamientoVuelo> v,
         unique_ptr<ComportamientoGraznido> g)
        : vuelo(move(v)), voz(move(g)) {}
    virtual ~Pato() = default;
    virtual void mostrar() const = 0; // La apariencia varia por especie.
    void nadar() const { cout << "Floto en el agua\n"; }
    void ejecutarVuelo() const { vuelo->volar(); }     // DELEGACION.
    void ejecutarGraznido() const { voz->graznar(); } // POLIMORFISMO.
    void cambiarVuelo(unique_ptr<ComportamientoVuelo> v) {
        vuelo = move(v); // Sustituye estrategia DURANTE la ejecucion.
    }
    void cambiarGraznido(unique_ptr<ComportamientoGraznido> g) {
        voz = move(g);
    }
};

// Herencia para representar diferencias estables: apariencia del pato.
class Mallard : public Pato {
public:
    Mallard() : Pato(make_unique<VolarConAlas>(), make_unique<Graznar>()) {}
    void mostrar() const override { cout << "Pato Mallard\n"; }
};
class Redhead : public Pato {
public:
    Redhead() : Pato(make_unique<VolarConAlas>(), make_unique<Graznar>()) {}
    void mostrar() const override { cout << "Pato Redhead\n"; }
};
class Rubber : public Pato {
public:
    Rubber() : Pato(make_unique<NoVolar>(), make_unique<Chillar>()) {}
    void mostrar() const override { cout << "Pato Rubber de goma\n"; }
};
class Decoy : public Pato {
public:
    Decoy() : Pato(make_unique<NoVolar>(), make_unique<Silencio>()) {}
    void mostrar() const override { cout << "Pato Decoy de madera\n"; }
};

int main() {
    // vector de punteros a Pato permite almacenar objetos de subclases distintas.
    vector<unique_ptr<Pato>> patos;
    patos.push_back(make_unique<Mallard>());
    patos.push_back(make_unique<Redhead>());
    patos.push_back(make_unique<Rubber>());
    patos.push_back(make_unique<Decoy>());
    for (const auto& pato : patos) {
        cout << "\n---\n";
        pato->mostrar(); pato->nadar();
        pato->ejecutarVuelo(); pato->ejecutarGraznido();
    }
    cout << "\n--- Cambio dinamico de Mallard ---\n";
    patos[0]->cambiarVuelo(make_unique<VolarConCohete>());
    patos[0]->cambiarGraznido(make_unique<Silencio>());
    patos[0]->ejecutarVuelo(); patos[0]->ejecutarGraznido();
}
