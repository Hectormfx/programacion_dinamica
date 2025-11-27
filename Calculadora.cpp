#include <iostream>
#include <stdexcept>   // EXCEPCIONES: std::runtime_error
#include <cmath>       // OPERACIONES AVANZADAS: sqrt (raíz), pow (potencia)
#include <limits>      // Para limpiar el buffer de entrada

using namespace std;

// ======================================================
// PROTOTIPOS DE FUNCIONES
// (Aquí se ve que TODO se organiza en funciones -> "Funciones")
// ======================================================

// OPERACIONES BÁSICAS (SOBRECARGA DE FUNCIONES)
// - Sobrecarga: misma función "operar" con distintos tipos (double / int)
double operar(double a, double b, char op);   // Versión double
int    operar(int a, int b, char op);         // Versión int (sobrecarga)

// FACTORIAL (RECURSIVA)
// - Recursividad: factorial se llama a sí misma
long long factorial(int n);

// POTENCIA (SOBRECARGA + PARÁMETRO POR OMISIÓN)
// - Sobrecarga: potencia(int, int) y potencia(double, int)
// - Parámetro por omisión: exponente = 2 (si el usuario no lo pone, se asume 2)
long long potencia(int base, int exponente = 2);      // int^exp, exp por omisión = 2
double    potencia(double base, int exponente = 2);   // double^exp, misma firma con double

// RAÍZ CUADRADA
// - Operación avanzada: raíz cuadrada
double raizCuadrada(double x);

// Utilidades de entrada/salida
void mostrarMenu();
void pausar();
double leerDouble(const char* mensaje);
int leerEntero(const char* mensaje);

// ======================================================
// OPERACIONES BÁSICAS
// (Suma, resta, multiplicación, división)
// ======================================================

// Versión double
// - Sobrecarga: esta es la versión de "operar" que trabaja con double
// - Manejo de excepciones: división entre cero
double operar(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;  // Operación básica: suma
        case '-': return a - b;  // Operación básica: resta
        case '*': return a * b;  // Operación básica: multiplicación
        case '/':                // Operación básica: división
            if (b == 0.0) {
                // EXCEPCIÓN: división entre cero
                throw runtime_error("Error: división entre cero.");
            }
            return a / b;
        default:
            throw runtime_error("Operador inválido para double.");
    }
}

// Versión int (sobrecarga)
// - Misma función "operar" pero con parámetros int -> SOBRECARGA
int operar(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;  // suma
        case '-': return a - b;  // resta
        case '*': return a * b;  // multiplicación
        case '/':
            if (b == 0) {
                // EXCEPCIÓN: división entre cero (entera)
                throw runtime_error("Error: división entre cero (int).");
            }
            return a / b;   // División entera
        default:
            throw runtime_error("Operador inválido para int.");
    }
}

// ======================================================
// FACTORIAL (RECURSIVO)
// - Operación avanzada: factorial
// - RECURRENCIA: la función se llama a sí misma
// - Manejo de excepciones: número negativo
// ======================================================

long long factorial(int n) {
    if (n < 0) {
        // EXCEPCIÓN: factorial de número negativo no está definido
        throw runtime_error("Error: no existe factorial de número negativo.");
    }
    if (n == 0 || n == 1) {
        return 1;  // Caso base de la recursión
    }
    // Recursividad: factorial(n) = n * factorial(n-1)
    return n * factorial(n - 1);
}

// ======================================================
// POTENCIA (SOBRECARGA + PARÁMETRO POR OMISIÓN)
// - Operación avanzada: potencia
// - Sobrecarga: versión int y versión double
// - Parámetro por omisión: exponente = 2
// ======================================================

// Versión entera
long long potencia(int base, int exponente) {
    // EJEMPLO DIRECTO DE PARÁMETRO POR OMISIÓN:
    // si el usuario llama potencia(base), el exponente se asume 2
    long long resultado = 1;
    if (exponente < 0) {
        // Aquí también se muestra manejo de errores lógicos
        throw runtime_error("La potencia con exponente negativo no está soportada en la versión entera.");
    }
    for (int i = 0; i < exponente; ++i) {
        resultado *= base;
    }
    return resultado;
}

// Versión double (usa pow de <cmath>)
double potencia(double base, int exponente) {
    // También con parámetro por omisión en el prototipo
    return pow(base, exponente);
}

// ======================================================
// RAÍZ CUADRADA
// - Operación avanzada: raíz cuadrada
// - Manejo de excepciones: raíz de número negativo
// ======================================================

double raizCuadrada(double x) {
    if (x < 0) {
        // EXCEPCIÓN: raíz de número negativo
        throw runtime_error("Error: no se puede calcular raíz cuadrada de un número negativo.");
    }
    return sqrt(x);
}

// ======================================================
// UTILIDADES (MENÚ Y LECTURA SEGURA)
// ======================================================

void mostrarMenu() {
    cout << "\n========== CALCULADORA ==========\n";
    cout << "1) Suma / Resta / Multiplicación / División (double)\n";
    cout << "2) Suma / Resta / Multiplicación / División (int)\n";
    cout << "3) Factorial (recursivo)\n";              // Operación avanzada
    cout << "4) Potencia (con parámetro por omisión)\n"; // Operación avanzada + parámetro por defecto
    cout << "5) Raíz cuadrada\n";                    // Operación avanzada
    cout << "0) Salir\n";
    cout << "Seleccione una opción: ";
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Lectura segura de double (función auxiliar)
double leerDouble(const char* mensaje) {
    double x;
    cout << mensaje;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Intente de nuevo: ";
    }
    return x;
}

// Lectura segura de int (función auxiliar)
int leerEntero(const char* mensaje) {
    int x;
    cout << mensaje;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Intente de nuevo: ";
    }
    return x;
}

// ======================================================
// FUNCIÓN PRINCIPAL
// - Aquí se integran TODAS las operaciones y el manejo
//   de EXCEPCIONES con try/catch a nivel general.
// ======================================================

int main() {
    bool salir = false;

    cout << "=== Calculadora con funciones, sobrecarga, recursividad y excepciones ===\n";

    while (!salir) {
        try {
            mostrarMenu();
            int opcion;
            if (!(cin >> opcion)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                // EXCEPCIÓN por tipo de dato incorrecto en la opción
                throw runtime_error("Entrada inválida: se esperaba un número de opción.");
            }

            switch (opcion) {
                case 1: {
                    // OPERACIONES BÁSICAS CON double
                    double a = leerDouble("Ingrese el primer número (double): ");
                    double b = leerDouble("Ingrese el segundo número (double): ");
                    char op;
                    cout << "Ingrese la operación (+, -, *, /): ";
                    cin >> op;

                    double resultado = operar(a, b, op); // uso de SOBRECARGA (double)
                    cout << "Resultado (double): " << resultado << "\n";
                    pausar();
                    break;
                }
                case 2: {
                    // OPERACIONES BÁSICAS CON int
                    int a = leerEntero("Ingrese el primer número (int): ");
                    int b = leerEntero("Ingrese el segundo número (int): ");
                    char op;
                    cout << "Ingrese la operación (+, -, *, /): ";
                    cin >> op;

                    int resultado = operar(a, b, op); // uso de SOBRECARGA (int)
                    cout << "Resultado (int): " << resultado << "\n";
                    pausar();
                    break;
                }
                case 3: {
                    // FACTORIAL (OPERACIÓN AVANZADA + RECURSIVIDAD)
                    int n = leerEntero("Ingrese un entero para calcular su factorial: ");
                    long long f = factorial(n); // llamada a función recursiva
                    cout << n << "! = " << f << "\n";
                    pausar();
                    break;
                }
                case 4: {
                    // POTENCIA (OPERACIÓN AVANZADA + PARÁMETRO POR OMISIÓN + SOBRECARGA)
                    cout << "\n1) Potencia entera (int^int, exponente por defecto = 2)\n";
                    cout << "2) Potencia double (double^int, exponente por defecto = 2)\n";
                    int tipo;
                    cout << "Seleccione tipo: ";
                    cin >> tipo;

                    if (tipo == 1) {
                        int base = leerEntero("Base (int): ");
                        cout << "¿Desea usar el exponente por defecto (2)? (s/n): ";
                        char usarDef;
                        cin >> usarDef;
                        int exp;
                        if (usarDef == 's' || usarDef == 'S') {
                            // Aquí se USA explícitamente el PARÁMETRO POR OMISIÓN
                            long long res = potencia(base); // exponente se toma como 2
                            cout << "Resultado: " << res << "\n";
                        } else {
                            exp = leerEntero("Exponente (int): ");
                            long long res = potencia(base, exp); // parámetro explícito
                            cout << "Resultado: " << res << "\n";
                        }
                    } else if (tipo == 2) {
                        double base = leerDouble("Base (double): ");
                        cout << "¿Desea usar el exponente por defecto (2)? (s/n): ";
                        char usarDef;
                        cin >> usarDef;
                        int exp;
                        if (usarDef == 's' || usarDef == 'S') {
                            double res = potencia(base); // usa exponente por defecto = 2
                            cout << "Resultado: " << res << "\n";
                        } else {
                            exp = leerEntero("Exponente (int): ");
                            double res = potencia(base, exp);
                            cout << "Resultado: " << res << "\n";
                        }
                    } else {
                        cout << "Tipo inválido.\n";
                    }
                    pausar();
                    break;
                }
                case 5: {
                    // RAÍZ CUADRADA (OPERACIÓN AVANZADA + EXCEPCIÓN SI ES NEGATIVO)
                    double x = leerDouble("Ingrese un número para calcular su raíz cuadrada: ");
                    double r = raizCuadrada(x); // puede lanzar excepción si x < 0
                    cout << "Raíz cuadrada de " << x << " = " << r << "\n";
                    pausar();
                    break;
                }
                case 0:
                    cout << "Saliendo de la calculadora. ¡Hasta luego!\n";
                    salir = true;
                    break;

                default:
                    cout << "Opción no válida. Intente de nuevo.\n";
                    pausar();
                    break;
            }

        } catch (const exception& e) {
            // MANEJO CENTRALIZADO DE EXCEPCIONES
            // - División entre cero
            // - Raíz de número negativo
            // - Factorial de negativo
            // - Entradas inválidas
            cout << "\nSe produjo una excepción: " << e.what() << "\n";
            cout << "Regresando al menú principal...\n";
            // Limpieza del buffer de entrada por seguridad
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pausar();
        }
    }

    return 0;
}
