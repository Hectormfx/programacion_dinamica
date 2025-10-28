#Aqui se subira el codigo del gato


#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==================== CONSTANTES ====================
const char JUGADOR_X = 'X';
const char JUGADOR_O = 'O';
const char VACIO = ' ';

// ==================== PROTOTIPOS DE FUNCIONES ====================
void mostrarMenu();
void inicializarTablero(vector<vector<char>>& tablero);
void mostrarTablero(const vector<vector<char>>& tablero);
bool esMovimientoValido(const vector<vector<char>>& tablero, int fila, int columna);
void realizarMovimiento(vector<vector<char>>& tablero, int fila, int columna, char jugador);
bool verificarGanador(const vector<vector<char>>& tablero, char jugador);
bool verificarEmpate(const vector<vector<char>>& tablero);
void jugarContraHumano();
void jugarContraCPU();
void movimientoCPU(vector<vector<char>>& tablero, char simboloCPU);
void limpiarPantalla();
bool preguntarReinicio();

// ==================== FUNCIÓN PRINCIPAL ====================
int main() {
    srand(time(0)); // Inicializar semilla para números aleatorios
    
    int opcion;
    bool continuar = true;
    
    cout << "==================================" << endl;
    cout << "  BIENVENIDO AL TIC TAC TOE C++  " << endl;
    cout << "==================================" << endl;
    
    while (continuar) {
        mostrarMenu();
        cin >> opcion;
        
        // Validar entrada del menú
        while (cin.fail() || opcion < 1 || opcion > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida. Intente nuevamente: ";
            cin >> opcion;
        }
        
        switch (opcion) {
            case 1:
                jugarContraHumano();
                break;
            case 2:
                jugarContraCPU();
                break;
            case 3:
                cout << "\nGracias por jugar! Hasta pronto." << endl;
                continuar = false;
                break;
        }
    }
    
    return 0;
}

// ==================== IMPLEMENTACIÓN DE FUNCIONES ====================

/**
 * Muestra el menú principal del juego
 */
void mostrarMenu() {
    cout << "\n--- MENU PRINCIPAL ---" << endl;
    cout << "1. Jugar contra otro jugador" << endl;
    cout << "2. Jugar contra la CPU" << endl;
    cout << "3. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

/**
 * Inicializa el tablero con espacios vacíos
 */
void inicializarTablero(vector<vector<char>>& tablero) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = VACIO;
        }
    }
}

/**
 * Muestra el tablero en pantalla con formato visual
 */
void mostrarTablero(const vector<vector<char>>& tablero) {
    cout << "\n     0   1   2" << endl;
    cout << "   +---+---+---+" << endl;
    
    for (int i = 0; i < 3; i++) {
        cout << " " << i << " | ";
        for (int j = 0; j < 3; j++) {
            cout << tablero[i][j] << " | ";
        }
        cout << endl;
        cout << "   +---+---+---+" << endl;
    }
}

/**
 * Verifica si un movimiento es válido
 */
bool esMovimientoValido(const vector<vector<char>>& tablero, int fila, int columna) {
    // Verificar que esté dentro del rango
    if (fila < 0 || fila > 2 || columna < 0 || columna > 2) {
        return false;
    }
    // Verificar que la casilla esté vacía
    return tablero[fila][columna] == VACIO;
}

/**
 * Realiza un movimiento en el tablero
 */
void realizarMovimiento(vector<vector<char>>& tablero, int fila, int columna, char jugador) {
    tablero[fila][columna] = jugador;
}

/**
 * Verifica si un jugador ha ganado
 */
bool verificarGanador(const vector<vector<char>>& tablero, char jugador) {
    // Verificar filas
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) {
            return true;
        }
    }
    
    // Verificar columnas
    for (int j = 0; j < 3; j++) {
        if (tablero[0][j] == jugador && tablero[1][j] == jugador && tablero[2][j] == jugador) {
            return true;
        }
    }
    
    // Verificar diagonal principal
    if (tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) {
        return true;
    }
    
    // Verificar diagonal secundaria
    if (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador) {
        return true;
    }
    
    return false;
}

/**
 * Verifica si hay empate (tablero lleno sin ganador)
 */
bool verificarEmpate(const vector<vector<char>>& tablero) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == VACIO) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Modo de juego: Jugador vs Jugador
 */
void jugarContraHumano() {
    vector<vector<char>> tablero(3, vector<char>(3));
    inicializarTablero(tablero);
    
    char jugadorActual = JUGADOR_X;
    bool juegoActivo = true;
    
    cout << "\n=== MODO: JUGADOR VS JUGADOR ===" << endl;
    cout << "Jugador 1: X | Jugador 2: O" << endl;
    
    while (juegoActivo) {
        mostrarTablero(tablero);
        
        int fila, columna;
        cout << "\nTurno del jugador " << jugadorActual << endl;
        cout << "Ingrese fila (0-2): ";
        cin >> fila;
        cout << "Ingrese columna (0-2): ";
        cin >> columna;
        
        // Validar entrada
        while (cin.fail() || !esMovimientoValido(tablero, fila, columna)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Movimiento invalido. Intente nuevamente." << endl;
            cout << "Ingrese fila (0-2): ";
            cin >> fila;
            cout << "Ingrese columna (0-2): ";
            cin >> columna;
        }
        
        // Realizar movimiento
        realizarMovimiento(tablero, fila, columna, jugadorActual);
        
        // Verificar ganador
        if (verificarGanador(tablero, jugadorActual)) {
            mostrarTablero(tablero);
            cout << "\n¡FELICIDADES! El jugador " << jugadorActual << " ha ganado!" << endl;
            juegoActivo = false;
        }
        // Verificar empate
        else if (verificarEmpate(tablero)) {
            mostrarTablero(tablero);
            cout << "\n¡Es un EMPATE!" << endl;
            juegoActivo = false;
        }
        // Cambiar turno
        else {
            jugadorActual = (jugadorActual == JUGADOR_X) ? JUGADOR_O : JUGADOR_X;
        }
    }
    
    // Preguntar si desea jugar de nuevo
    if (preguntarReinicio()) {
        jugarContraHumano();
    }
}

/**
 * Modo de juego: Jugador vs CPU
 */
void jugarContraCPU() {
    vector<vector<char>> tablero(3, vector<char>(3));
    inicializarTablero(tablero);
    
    char jugadorHumano, jugadorCPU;
    int eleccion;
    
    cout << "\n=== MODO: JUGADOR VS CPU ===" << endl;
    cout << "Elija su simbolo:" << endl;
    cout << "1. X (juega primero)" << endl;
    cout << "2. O (juega segundo)" << endl;
    cout << "Seleccione: ";
    cin >> eleccion;
    
    while (cin.fail() || (eleccion != 1 && eleccion != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcion invalida. Seleccione 1 o 2: ";
        cin >> eleccion;
    }
    
    if (eleccion == 1) {
        jugadorHumano = JUGADOR_X;
        jugadorCPU = JUGADOR_O;
    } else {
        jugadorHumano = JUGADOR_O;
        jugadorCPU = JUGADOR_X;
    }
    
    char jugadorActual = JUGADOR_X;
    bool juegoActivo = true;
    
    while (juegoActivo) {
        mostrarTablero(tablero);
        
        if (jugadorActual == jugadorHumano) {
            // Turno del jugador humano
            int fila, columna;
            cout << "\nSu turno (" << jugadorHumano << ")" << endl;
            cout << "Ingrese fila (0-2): ";
            cin >> fila;
            cout << "Ingrese columna (0-2): ";
            cin >> columna;
            
            while (cin.fail() || !esMovimientoValido(tablero, fila, columna)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Movimiento invalido. Intente nuevamente." << endl;
                cout << "Ingrese fila (0-2): ";
                cin >> fila;
                cout << "Ingrese columna (0-2): ";
                cin >> columna;
            }
            
            realizarMovimiento(tablero, fila, columna, jugadorHumano);
        } else {
            // Turno de la CPU
            cout << "\nTurno de la CPU (" << jugadorCPU << ")..." << endl;
            movimientoCPU(tablero, jugadorCPU);
        }
        
        // Verificar ganador
        if (verificarGanador(tablero, jugadorActual)) {
            mostrarTablero(tablero);
            if (jugadorActual == jugadorHumano) {
                cout << "\n¡FELICIDADES! Has ganado!" << endl;
            } else {
                cout << "\nLa CPU ha ganado. ¡Mejor suerte la proxima vez!" << endl;
            }
            juegoActivo = false;
        }
        // Verificar empate
        else if (verificarEmpate(tablero)) {
            mostrarTablero(tablero);
            cout << "\n¡Es un EMPATE!" << endl;
            juegoActivo = false;
        }
        // Cambiar turno
        else {
            jugadorActual = (jugadorActual == JUGADOR_X) ? JUGADOR_O : JUGADOR_X;
        }
    }
    
    // Preguntar si desea jugar de nuevo
    if (preguntarReinicio()) {
        jugarContraCPU();
    }
}

/**
 * Realiza el movimiento de la CPU (estrategia simple)
 */
void movimientoCPU(vector<vector<char>>& tablero, char simboloCPU) {
    // Estrategia simple: buscar movimientos en orden de prioridad
    char simboloHumano = (simboloCPU == JUGADOR_X) ? JUGADOR_O : JUGADOR_X;
    
    // 1. Intentar ganar
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == VACIO) {
                tablero[i][j] = simboloCPU;
                if (verificarGanador(tablero, simboloCPU)) {
                    return;
                }
                tablero[i][j] = VACIO;
            }
        }
    }
    
    // 2. Bloquear victoria del oponente
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == VACIO) {
                tablero[i][j] = simboloHumano;
                if (verificarGanador(tablero, simboloHumano)) {
                    tablero[i][j] = simboloCPU;
                    return;
                }
                tablero[i][j] = VACIO;
            }
        }
    }
    
    // 3. Tomar el centro si está disponible
    if (tablero[1][1] == VACIO) {
        tablero[1][1] = simboloCPU;
        return;
    }
    
    // 4. Tomar una esquina aleatoria
    vector<pair<int, int>> esquinas = {{0,0}, {0,2}, {2,0}, {2,2}};
    for (const auto& esquina : esquinas) {
        if (tablero[esquina.first][esquina.second] == VACIO) {
            tablero[esquina.first][esquina.second] = simboloCPU;
            return;
        }
    }
    
    // 5. Tomar cualquier casilla disponible
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == VACIO) {
                tablero[i][j] = simboloCPU;
                return;
            }
        }
    }
}

/**
 * Limpia la pantalla (multiplataforma básico)
 */
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * Pregunta al usuario si desea jugar nuevamente
 */
bool preguntarReinicio() {
    char respuesta;
    cout << "\n¿Desea jugar nuevamente? (s/n): ";
    cin >> respuesta;
    
    while (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N') {
        cout << "Respuesta invalida. Ingrese 's' o 'n': ";
        cin >> respuesta;
    }
    
    return (respuesta == 's' || respuesta == 'S');
}