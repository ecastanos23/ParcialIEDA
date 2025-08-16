#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
#include <windows.h>
using namespace std;

// ========================= CLASE EQUIPO =========================
class Equipo {
private:
    int id;
    string nombre;
    string categoria;
    bool disponible;

public:
    Equipo(int id, string nombre, string categoria)
        : id(id), nombre(nombre), categoria(categoria), disponible(true) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getCategoria() const { return categoria; }
    bool isDisponible() const { return disponible; }

    void setDisponible(bool estado) { disponible = estado; }

    string getIdFormateado() const {
        ostringstream oss;
        oss << setw(3) << setfill('0') << id;
        return oss.str();
    }

    string toString(bool mostrarEstado = false) const {
        string info = getIdFormateado() + ". " + nombre;
        if (mostrarEstado) {
            info += disponible ? " (Disponible)" : " (Reservado)";
        }
        return info;
    }
};

// ========================= CLASE RESERVA =========================
class Reserva {
private:
    string idUsuario;
    Equipo* equipo;

public:
    Reserva(string idUsuario, Equipo* equipo)
        : idUsuario(idUsuario), equipo(equipo) {}

    string getIdUsuario() const { return idUsuario; }
    Equipo* getEquipo() const { return equipo; }

    string toString() const {
        return equipo->getIdFormateado() + ". " + equipo->getNombre() +
               " (Categoría: " + equipo->getCategoria() + ")";
    }
};

// ========================= CLASE SISTEMA =========================
class SistemaReserva {
private:
    vector<Equipo> equipos;
    vector<Reserva> reservas;
    vector<queue<string>> colasEspera;

public:
    SistemaReserva() {
        // Crear equipos de distintas categorías
        equipos.push_back(Equipo(1, "Balón", "Fútbol"));
        equipos.push_back(Equipo(2, "Guantes", "Fútbol"));
        equipos.push_back(Equipo(3, "Gafas de Natación", "Natación"));
        equipos.push_back(Equipo(4, "Flotador", "Natación"));
        equipos.push_back(Equipo(5, "Balón", "Voleibol"));
        equipos.push_back(Equipo(6, "Red", "Voleibol"));
        equipos.push_back(Equipo(7, "Balón", "Básquetbol"));
        equipos.push_back(Equipo(8, "Aro", "Básquetbol"));

        colasEspera.resize(equipos.size());
    }

    // Mostrar equipos por categoría (sin estado)
    void mostrarEquiposPorCategoria(const string& categoria) {
        cout << "Equipos de " << categoria << ":\n";
        for (const auto& e : equipos) {
            if (e.getCategoria() == categoria) {
                cout << "  " << e.toString(false) << endl;
            }
        }
    }

    // Mostrar disponibilidad por categoría (con estado)
    void mostrarDisponibilidadPorCategoria(const string& categoria) {
        cout << "Disponibilidad en " << categoria << ":\n";
        for (const auto& e : equipos) {
            if (e.getCategoria() == categoria) {
                cout << "  " << e.toString(true) << endl;
            }
        }
    }

    // Reservar un equipo
    void reservarEquipo(const string& idUsuario, int idEquipo, bool entrarEnCola = false) {
        if (idEquipo < 1 || idEquipo > (int)equipos.size()) {
            cout << "ID de equipo inválido.\n";
            return;
        }

        Equipo& equipo = equipos[idEquipo - 1];

        if (equipo.isDisponible()) {
            equipo.setDisponible(false);
            reservas.push_back(Reserva(idUsuario, &equipo));
            cout << "✅ Elemento reservado con la identificación " << idUsuario << endl;
        } else {
            if (entrarEnCola) {
                colasEspera[idEquipo - 1].push(idUsuario);
                cout << "📌 Te has añadido a la lista de espera para el equipo " << equipo.getNombre() << endl;
            } else {
                cout << "⚠️ El equipo ya está reservado.\n";
            }
        }
    }

    // Consultar reservas de un usuario
    void consultarReservas(const string& idUsuario) {
        cout << "Reservas de " << idUsuario << ":\n";
        bool tieneReservas = false;
        for (size_t i = 0; i < reservas.size(); i++) {
            if (reservas[i].getIdUsuario() == idUsuario) {
                cout << (i + 1) << ". " << reservas[i].toString() << endl;
                tieneReservas = true;
            }
        }
        if (!tieneReservas) {
            cout << "No tienes reservas activas.\n";
        }
    }

    // Cancelar reserva
    void cancelarReserva(const string& idUsuario, int indiceReserva) {
        int contador = 0;
        for (size_t i = 0; i < reservas.size(); i++) {
            if (reservas[i].getIdUsuario() == idUsuario) {
                contador++;
                if (contador == indiceReserva) {
                    Equipo* equipo = reservas[i].getEquipo();
                    equipo->setDisponible(true);
                    cout << "✅ Reserva cancelada con satisfacción.\n";

                    // Revisar cola de espera
                    if (!colasEspera[equipo->getId() - 1].empty()) {
                        string siguienteUsuario = colasEspera[equipo->getId() - 1].front();
                        colasEspera[equipo->getId() - 1].pop();
                        reservarEquipo(siguienteUsuario, equipo->getId(), false);
                        cout << "📌 El equipo fue asignado automáticamente a " << siguienteUsuario << endl;
                    }

                    reservas.erase(reservas.begin() + i);
                    return;
                }
            }
        }
        cout << "⚠️ No se encontró la reserva indicada.\n";
    }
};

// ========================= MAIN =========================
int main() {
    SetConsoleOutputCP(CP_UTF8); 
    SistemaReserva sistema;
    int opcion;

    do {
        cout << "\n=== Bienvenido al sistema de Reserva de Equipos ===\n";
        cout << "1. Consultar equipos según categoría\n";
        cout << "2. Consultar disponibilidad de equipos\n";
        cout << "3. Reservar un equipo\n";
        cout << "4. Consultar reservas realizadas\n";
        cout << "5. Cancelar reserva\n";
        cout << "6. Salir\n";
        cout << "Elija una opción: ";
        cin >> opcion;

        cin.ignore(); // limpiar buffer

        if (opcion == 1) {
            sistema.mostrarEquiposPorCategoria("Fútbol");
            sistema.mostrarEquiposPorCategoria("Natación");
            sistema.mostrarEquiposPorCategoria("Voleibol");
            sistema.mostrarEquiposPorCategoria("Básquetbol");
        }
        else if (opcion == 2) {
            sistema.mostrarDisponibilidadPorCategoria("Fútbol");
            sistema.mostrarDisponibilidadPorCategoria("Natación");
            sistema.mostrarDisponibilidadPorCategoria("Voleibol");
            sistema.mostrarDisponibilidadPorCategoria("Básquetbol");
        }
        else if (opcion == 3) {
            string idUsuario;
            int idEquipo;
            char entrarCola;

            cout << "Ingrese el número de identificación: ";
            getline(cin, idUsuario);

            cout << "Ingrese el ID del equipo a reservar: ";
            cin >> idEquipo;

            cout << "¿Desea entrar en lista de espera si está reservado? (s/n): ";
            cin >> entrarCola;

            sistema.reservarEquipo(idUsuario, idEquipo, (entrarCola == 's' || entrarCola == 'S'));
        }
        else if (opcion == 4) {
            string idUsuario;
            cout << "Ingrese su número de identificación: ";
            getline(cin, idUsuario);
            sistema.consultarReservas(idUsuario);
        }
        else if (opcion == 5) {
            string idUsuario;
            int indice;
            cout << "Ingrese su número de identificación: ";
            getline(cin, idUsuario);
            sistema.consultarReservas(idUsuario);
            cout << "Ingrese el número de reserva a cancelar: ";
            cin >> indice;
            sistema.cancelarReserva(idUsuario, indice);
        }

    } while (opcion != 6);

    cout << "👋 Gracias por usar el sistema. Hasta luego.\n";
    return 0;
}
