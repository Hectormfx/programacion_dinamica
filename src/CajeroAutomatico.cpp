#include <iostream>
#include <string>
#include <vector>
#include <iomanip>      // fixed, setprecision
#include <stdexcept>    // runtime_error
#include <limits>       // numeric_limits

using namespace std;

// =====================================================
// EXCEPCIONES PERSONALIZADAS
// =====================================================

class SaldoInsuficiente : public runtime_error {
public:
    SaldoInsuficiente()
        : runtime_error("Saldo insuficiente para realizar la operación.") {}
};

class PinIncorrecto : public runtime_error {
public:
    PinIncorrecto()
        : runtime_error("PIN incorrecto. Intente de nuevo.") {}
};

class MontoInvalido : public runtime_error {
public:
    MontoInvalido()
        : runtime_error("El monto debe ser mayor que 0 y numérico.") {}
};

class CuentaNoEncontrada : public runtime_error {
public:
    CuentaNoEncontrada()
        : runtime_error("Cuenta destino no encontrada.") {}
};

// =====================================================
// ESTRUCTURA DE DATOS PARA CUENTA
// =====================================================

struct Cuenta {
    int id;                    // Número de cuenta
    string titular;            // Nombre del titular
    double saldo;              // Saldo actual
    string pin;                // PIN de 4 dígitos
    vector<string> historial;  // Historial de movimientos
};

// =====================================================
// PROTOTIPOS
// =====================================================

void mostrarMenu();
int  leerEnteroSeguro(const string& mensaje);
double leerMontoPositivo(const string& mensaje);
void pausar();

bool iniciarSesion(Cuenta cuentas[], int numCuentas, int& indiceCuentaActual);
bool validarPin(const Cuenta& cuenta, const string& pinIngresado);

void consultarSaldo(const Cuenta* cuenta);
void hacerDeposito(Cuenta* cuenta);
void hacerRetiro(Cuenta* cuenta);
void hacerTransferencia(Cuenta cuentas[], int numCuentas, int indiceOrigen);
void verHistorial(const Cuenta* cuenta);

// =====================================================
// FUNCIONES AUXILIARES DE ENTRADA
// =====================================================

int leerEnteroSeguro(const string& mensaje) {
    int valor;
    cout << mensaje;
    if (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Entrada inválida: se esperaba un número entero.");
    }
    return valor;
}

double leerMontoPositivo(const string& mensaje) {
    double monto;
    cout << mensaje;
    if (!(cin >> monto)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MontoInvalido();
    }
    if (monto <= 0) {
        throw MontoInvalido();
    }
    return monto;
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// =====================================================
// SESIÓN Y PIN
// =====================================================

bool validarPin(const Cuenta& cuenta, const string& pinIngresado) {
    if (cuenta.pin != pinIngresado) {
        throw PinIncorrecto();
    }
    return true;
}

bool iniciarSesion(Cuenta cuentas[], int numCuentas, int& indiceCuentaActual) {
    cout << "\n========== INICIAR SESIÓN ==========\n";
    cout << "Cuentas disponibles:\n";
    for (int i = 0; i < numCuentas; ++i) {
        cout << (i + 1) << ") Cuenta " << cuentas[i].id
             << " - " << cuentas[i].titular << "\n";
    }

    try {
        int opcion = leerEnteroSeguro("Seleccione una cuenta (1 - "
                                      + to_string(numCuentas) + "): ");
        if (opcion < 1 || opcion > numCuentas) {
            throw runtime_error("Opción fuera de rango.");
        }

        string pinIngresado;
        cout << "Ingrese PIN: ";
        cin >> pinIngresado;

        if (validarPin(cuentas[opcion - 1], pinIngresado)) {
            indiceCuentaActual = opcion - 1;
            cout << "\nSesión iniciada correctamente.\n";
            cout << "Bienvenido(a), " << cuentas[indiceCuentaActual].titular << "\n";
            return true;
        }
    } catch (const PinIncorrecto& e) {
        cout << "Error: " << e.what() << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
    return false;
}

// =====================================================
// OPERACIONES DEL CAJERO
// =====================================================

void consultarSaldo(const Cuenta* cuenta) {
    cout << "\n--- CONSULTA DE SALDO ---\n";
    cout << "Cuenta : " << cuenta->id << "\n";
    cout << "Titular: " << cuenta->titular << "\n";
    cout << "Saldo  : $" << fixed << setprecision(2) << cuenta->saldo << "\n";

    string mov = "Consulta de saldo: $" + to_string(static_cast<int>(cuenta->saldo));
    const_cast<Cuenta*>(cuenta)->historial.push_back(mov); // se registra en historial
}

void hacerDeposito(Cuenta* cuenta) {
    cout << "\n--- DEPÓSITO ---\n";
    try {
        double monto = leerMontoPositivo("Ingrese el monto a depositar: $");
        cuenta->saldo += monto;

        cout << "Depósito exitoso.\n";
        cout << "Nuevo saldo: $" << fixed << setprecision(2) << cuenta->saldo << "\n";

        string mov = "Depósito: +$" + to_string(static_cast<int>(monto));
        cuenta->historial.push_back(mov);

    } catch (const MontoInvalido& e) {
        cout << "Error en el depósito: " << e.what() << "\n";
    } catch (const exception& e) {
        cout << "Error inesperado en el depósito: " << e.what() << "\n";
    }
}

void hacerRetiro(Cuenta* cuenta) {
    cout << "\n--- RETIRO ---\n";
    try {
        double monto = leerMontoPositivo("Ingrese el monto a retirar: $");

        if (monto > cuenta->saldo) {
            throw SaldoInsuficiente();
        }

        cuenta->saldo -= monto;

        cout << "Retiro exitoso.\n";
        cout << "Nuevo saldo: $" << fixed << setprecision(2) << cuenta->saldo << "\n";

        string mov = "Retiro: -$" + to_string(static_cast<int>(monto));
        cuenta->historial.push_back(mov);

    } catch (const MontoInvalido& e) {
        cout << "Error en el retiro: " << e.what() << "\n";
    } catch (const SaldoInsuficiente& e) {
        cout << "Error en el retiro: " << e.what() << "\n";
    } catch (const exception& e) {
        cout << "Error inesperado en el retiro: " << e.what() << "\n";
    }
}

void hacerTransferencia(Cuenta cuentas[], int numCuentas, int indiceOrigen) {
    cout << "\n--- TRANSFERENCIA ENTRE CUENTAS ---\n";

    cout << "Cuenta origen: " << cuentas[indiceOrigen].id
         << " - " << cuentas[indiceOrigen].titular << "\n";

    try {
        int idDestino = leerEnteroSeguro("Ingrese el número de cuenta destino: ");

        int indiceDestino = -1;
        for (int i = 0; i < numCuentas; ++i) {
            if (cuentas[i].id == idDestino) {
                indiceDestino = i;
                break;
            }
        }

        if (indiceDestino == -1) {
            throw CuentaNoEncontrada();
        }

        if (indiceDestino == indiceOrigen) {
            cout << "No puede transferir a la misma cuenta.\n";
            return;
        }

        double monto = leerMontoPositivo("Ingrese el monto a transferir: $");

        if (monto > cuentas[indiceOrigen].saldo) {
            throw SaldoInsuficiente();
        }

        cuentas[indiceOrigen].saldo -= monto;
        cuentas[indiceDestino].saldo += monto;

        cout << "Transferencia exitosa.\n";
        cout << "Nuevo saldo cuenta origen  (" << cuentas[indiceOrigen].id
             << "): $" << fixed << setprecision(2) << cuentas[indiceOrigen].saldo << "\n";
        cout << "Nuevo saldo cuenta destino (" << cuentas[indiceDestino].id
             << "): $" << fixed << setprecision(2) << cuentas[indiceDestino].saldo << "\n";

        string movOrigen   = "Transferencia a " + cuentas[indiceDestino].titular
                           + ": -$" + to_string(static_cast<int>(monto));
        string movDestino  = "Transferencia de " + cuentas[indiceOrigen].titular
                           + ": +$" + to_string(static_cast<int>(monto));

        cuentas[indiceOrigen].historial.push_back(movOrigen);
        cuentas[indiceDestino].historial.push_back(movDestino);

    } catch (const MontoInvalido& e) {
        cout << "Error en la transferencia: " << e.what() << "\n";
    } catch (const SaldoInsuficiente& e) {
        cout << "Error en la transferencia: " << e.what() << "\n";
    } catch (const CuentaNoEncontrada& e) {
        cout << "Error en la transferencia: " << e.what() << "\n";
    } catch (const exception& e) {
        cout << "Error inesperado en la transferencia: " << e.what() << "\n";
    }
}

void verHistorial(const Cuenta* cuenta) {
    cout << "\n--- HISTORIAL DE MOVIMIENTOS ---\n";
    cout << "Cuenta: " << cuenta->id << " - " << cuenta->titular << "\n";

    if (cuenta->historial.empty()) {
        cout << "No hay movimientos registrados.\n";
        return;
    }

    for (size_t i = 0; i < cuenta->historial.size(); ++i) {
        cout << (i + 1) << ") " << cuenta->historial[i] << "\n";
    }
}

// =====================================================
// MENÚ
// =====================================================

void mostrarMenu() {
    cout << "\n========== CAJERO AUTOMÁTICO ==========\n";
    cout << "1) Consultar saldo\n";
    cout << "2) Retirar\n";
    cout << "3) Depositar\n";
    cout << "4) Transferir entre cuentas\n";
    cout << "5) Ver historial\n";
    cout << "6) Cambiar de cuenta (cerrar sesión)\n";
    cout << "0) Salir\n";
    cout << "Seleccione una opción: ";
}

// =====================================================
// FUNCIÓN PRINCIPAL
// =====================================================

int main() {
    const int NUM_CUENTAS = 3;
    Cuenta cuentas[NUM_CUENTAS] = {
        {1001, "Juan Perez",   2500.0, "1234", {}},
        {1002, "Maria Lopez",  5000.0, "5678", {}},
        {1003, "Carlos Ruiz",  1000.0, "9012", {}}
    };

    int indiceCuentaActual = -1;
    bool salir = false;

    cout << "=== Bienvenido al sistema de Cajero Automático ===\n";

    while (!salir) {
        // Si no hay sesión, primero iniciar
        if (indiceCuentaActual == -1) {
            bool ok = iniciarSesion(cuentas, NUM_CUENTAS, indiceCuentaActual);
            if (!ok) {
                cout << "No se pudo iniciar sesión.\n";
                // damos opción de intentar de nuevo o salir
                char opc;
                cout << "¿Desea intentar de nuevo? (s/n): ";
                cin >> opc;
                if (opc == 'n' || opc == 'N') {
                    cout << "Saliendo del sistema.\n";
                    break;
                } else {
                    continue;
                }
            }
        }

        try {
            mostrarMenu();
            int opcion;
            if (!(cin >> opcion)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Entrada inválida: se esperaba un número de opción.");
            }

            switch (opcion) {
                case 1:
                    consultarSaldo(&cuentas[indiceCuentaActual]);
                    pausar();
                    break;
                case 2:
                    hacerRetiro(&cuentas[indiceCuentaActual]);
                    pausar();
                    break;
                case 3:
                    hacerDeposito(&cuentas[indiceCuentaActual]);
                    pausar();
                    break;
                case 4:
                    hacerTransferencia(cuentas, NUM_CUENTAS, indiceCuentaActual);
                    pausar();
                    break;
                case 5:
                    verHistorial(&cuentas[indiceCuentaActual]);
                    pausar();
                    break;
                case 6:
                    cout << "Cerrando sesión de " << cuentas[indiceCuentaActual].titular << "...\n";
                    indiceCuentaActual = -1;
                    break;
                case 0:
                    cout << "Gracias por utilizar el cajero. ¡Hasta luego!\n";
                    salir = true;
                    break;
                default:
                    cout << "Opción no válida. Intente de nuevo.\n";
                    pausar();
                    break;
            }

        } catch (const exception& e) {
            cout << "Se ha producido un error: " << e.what() << "\n";
            cout << "Reiniciando menú...\n";
        }
    }

    return 0;
}