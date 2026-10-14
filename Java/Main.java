/* ==============================================================
 * SIMULADOR DE PATOS - PATRON ESTRATEGIA (JAVA)
 * Elaborado por Juan Manuel Gonzalez Calleros
 * Curso: Implementacion de Internet de las Cosas (IoT)
 * Compilar: javac Main.java
 * Ejecutar: java Main
 * ============================================================= */

// Contrato de vuelo: todos los algoritmos implementan volar().
interface ComportamientoVuelo { void volar(); }
// Variantes intercambiables: cada una tiene su propia implementacion.
class VolarConAlas implements ComportamientoVuelo {
    public void volar() { System.out.println("Vuelo con alas"); }
}
class NoVolar implements ComportamientoVuelo {
    public void volar() { System.out.println("No puedo volar"); }
}
class VolarConCohete implements ComportamientoVuelo {
    public void volar() { System.out.println("Vuelo impulsado por un cohete"); }
}

// Una segunda interfaz encapsula el comportamiento de graznido.
interface ComportamientoGraznido { void graznar(); }
class Graznar implements ComportamientoGraznido {
    public void graznar() { System.out.println("Quack, quack"); }
}
class Chillar implements ComportamientoGraznido {
    public void graznar() { System.out.println("Squeak, squeak"); }
}
class Silencio implements ComportamientoGraznido {
    public void graznar() { System.out.println("(Sin sonido)"); }
}

// CONTEXTO abstracto: el pato TIENE referencias a interfaces (composicion).
abstract class Pato {
    private ComportamientoVuelo vuelo;
    private ComportamientoGraznido voz;
    protected Pato(ComportamientoVuelo vuelo, ComportamientoGraznido voz) {
        this.vuelo = vuelo; this.voz = voz;
    }
    public abstract void mostrar(); // Cada subclase se representa diferente.
    public void nadar() { System.out.println("Floto en el agua"); }
    public void ejecutarVuelo() { vuelo.volar(); } // Delegacion.
    public void ejecutarGraznido() { voz.graznar(); }
    // Setters: permiten cambiar algoritmos en tiempo de ejecucion.
    public void cambiarVuelo(ComportamientoVuelo nuevo) { vuelo = nuevo; }
    public void cambiarGraznido(ComportamientoGraznido nuevo) { voz = nuevo; }
}
class Mallard extends Pato {
    Mallard() { super(new VolarConAlas(), new Graznar()); }
    public void mostrar() { System.out.println("Pato Mallard"); }
}
class Redhead extends Pato {
    Redhead() { super(new VolarConAlas(), new Graznar()); }
    public void mostrar() { System.out.println("Pato Redhead"); }
}
class Rubber extends Pato {
    Rubber() { super(new NoVolar(), new Chillar()); }
    public void mostrar() { System.out.println("Pato Rubber de goma"); }
}
class Decoy extends Pato {
    Decoy() { super(new NoVolar(), new Silencio()); }
    public void mostrar() { System.out.println("Pato Decoy de madera"); }
}

public class Main {
    public static void main(String[] args) {
        // Un arreglo de Pato puede guardar instancias de cualquiera de sus subclases.
        Pato[] patos = {new Mallard(), new Redhead(), new Rubber(), new Decoy()};
        for (Pato pato : patos) {
            System.out.println("\n---");
            pato.mostrar(); pato.nadar();
            pato.ejecutarVuelo(); pato.ejecutarGraznido();
        }
        System.out.println("\n--- Cambio dinamico de Mallard ---");
        patos[0].cambiarVuelo(new VolarConCohete());
        patos[0].cambiarGraznido(new Silencio());
        patos[0].ejecutarVuelo(); patos[0].ejecutarGraznido();
    }
}
