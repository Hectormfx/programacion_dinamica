#include <iostream>
#include <array>
#include <limits>   // para limpiar el buffer de entrada

// =================== CONFIGURACIÓN ===================
constexpr int FILAS = 6;
constexpr int COLUMNAS = 7;
constexpr char VACIO = '.';
constexpr char JUGADOR1 = 'X';
constexpr char JUGADOR2 = 'O';

using Tablero = std::array<std::array<char, COLUMNAS>, FILAS>;

// =================== PROTOTIPOS ===================
void inicializarTablero(Tablero& t);
void mostrarTablero(const Tablero& t);
bool colocarFicha(Tablero& t, int colCeroBase, char ficha);
bool columnaLlena(const Tablero& t, int colCeroBase);
bool tableroLleno(const Tablero& t);
int  obtenerJugadaValida(const Tablero& t, int numJugador);
bool verificarHorizontal(const Tablero& t, char ficha);
bool verificarVertical(const Tablero& t, char ficha);
bool verificarDiagonalAsc(const Tablero& t, char ficha);
bool verificarDiagonalDesc(const Tablero& t, char ficha);
bool hayGanador(const Tablero& t, char ficha);
bool preguntarJugarDeNuevo();

// =================== IMPLEMENTACIÓN ===================
void inicializarTablero(Tablero& t) {
    for (int f = 0; f < FILAS; ++f) {
        for (int c = 0; c < COLUMNAS; ++c) {
            t[f][c] = VACIO;
        }
    }
}

void mostrarTablero(const Tablero& t) {
    std::cout << "\n    ";
    for (int c = 1; c <= COLUMNAS; ++c) std::cout << c << "   ";
    std::cout << "\n  " << std::string(COLUMNAS * 4 + 1, '-') << "\n";

    for (int f = 0; f < FILAS; ++f) {
        std::cout << " | ";
        for (int c = 0; c < COLUMNAS; ++c) {
            std::cout << t[f][c] << " | ";
        }
        std::cout << "\n  " << std::string(COLUMNAS * 4 + 1, '-') << "\n";
    }
    std::cout << "\n";
}

bool colocarFicha(Tablero& t, int colCeroBase, char ficha) {
    // “Gravedad”: de abajo hacia arriba
    for (int f = FILAS - 1; f >= 0; --f) {
        if (t[f][colCeroBase] == VACIO) {
            t[f][colCeroBase] = ficha;
            return true;
        }
    }
    return false; // columna llena
}

bool columnaLlena(const Tablero& t, int colCeroBase) {
    return t[0][colCeroBase] != VACIO;
}

bool tableroLleno(const Tablero& t) {
    for (int c = 0; c < COLUMNAS; ++c) {
        if (t[0][c] == VACIO) return false;
    }
    return true;
}

int obtenerJugadaValida(const Tablero& t, int numJugador) {
    while (true) {
        std::cout << "Jugador " << numJugador << ", elige columna (1-" << COLUMNAS << "): ";
        int colHumana;
        std::cin >> colHumana;

        if (std::cin.fail()) {
            std::cout << "  [Error] Ingresa un numero entero valido.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (colHumana < 1 || colHumana > COLUMNAS) {
            std::cout << "  [Error] La columna debe estar entre 1 y " << COLUMNAS << ".\n\n";
            continue;
        }

        int col0 = colHumana - 1;
        if (columnaLlena(t, col0)) {
            std::cout << "  [Error] La columna " << colHumana << " esta llena. Prueba otra.\n\n";
            continue;
        }

        return col0; // índice 0..6 ya validado y con espacio
    }
}

bool verificarHorizontal(const Tablero& t, char ficha) {
    for (int f = 0; f < FILAS; ++f) {
        for (int c = 0; c <= COLUMNAS - 4; ++c) {
            if (t[f][c] == ficha && t[f][c+1] == ficha &&
                t[f][c+2] == ficha && t[f][c+3] == ficha) {
                return true;
            }
        }
    }
    return false;
}

bool verificarVertical(const Tablero& t, char ficha) {
    for (int c = 0; c < COLUMNAS; ++c) {
        for (int f = 0; f <= FILAS - 4; ++f) {
            if (t[f][c] == ficha && t[f+1][c] == ficha &&
                t[f+2][c] == ficha && t[f+3][c] == ficha) {
                return true;
            }
        }
    }
    return false;
}

bool verificarDiagonalDesc(const Tablero& t, char ficha) { // ↘
    for (int f = 0; f <= FILAS - 4; ++f) {
        for (int c = 0; c <= COLUMNAS - 4; ++c) {
            if (t[f][c] == ficha && t[f+1][c+1] == ficha &&
                t[f+2][c+2] == ficha && t[f+3][c+3] == ficha) {
                return true;
            }
        }
    }
    return false;
}

bool verificarDiagonalAsc(const Tablero& t, char ficha) { // ↗
    for (int f = 3; f < FILAS; ++f) {
        for (int c = 0; c <= COLUMNAS - 4; ++c) {
            if (t[f][c] == ficha && t[f-1][c+1] == ficha &&
                t[f-2][c+2] == ficha && t[f-3][c+3] == ficha) {
                return true;
            }
        }
    }
    return false;
}

bool hayGanador(const Tablero& t, char ficha) {
    return verificarHorizontal(t, ficha) ||
           verificarVertical(t, ficha)   ||
           verificarDiagonalDesc(t, ficha) ||
           verificarDiagonalAsc(t, ficha);
}

bool preguntarJugarDeNuevo() {
    char r;
    std::cout << "¿Jugar otra vez? (s/n): ";
    std::cin >> r;
    return (r == 's' || r == 'S');
}

int main() {
    bool seguir = true;

    while (seguir) {
        Tablero tablero{};
        inicializarTablero(tablero);

        int jugadorNum = 1;
        char ficha = JUGADOR1;
        bool terminado = false;

        std::cout << "\n======================================\n";
        std::cout << "           CONECTA 4 (6x7)\n";
        std::cout << "======================================\n";
        std::cout << "Jugador 1 = " << JUGADOR1 << "   |   Jugador 2 = " << JUGADOR2 << "\n";
        std::cout << "======================================\n";

        while (!terminado) {
            mostrarTablero(tablero);

            int col0 = obtenerJugadaValida(tablero, jugadorNum);

            colocarFicha(tablero, col0, ficha);

            // ¿Ganó el jugador actual?
            if (hayGanador(tablero, ficha)) {
                mostrarTablero(tablero);
                std::cout << "¡Jugador " << jugadorNum << " (" << ficha << ") gana! 🎉\n\n";
                terminado = true;
            }
            // ¿Empate?
            else if (tableroLleno(tablero)) {
                mostrarTablero(tablero);
                std::cout << "Empate. No hay mas movimientos.\n\n";
                terminado = true;
            }
            // Cambiar de jugador
            else {
                if (ficha == JUGADOR1) { ficha = JUGADOR2; jugadorNum = 2; }
                else { ficha = JUGADOR1; jugadorNum = 1; }
            }
        }

        seguir = preguntarJugarDeNuevo();
    }

    std::cout << "Gracias por jugar Conecta 4. ¡Hasta pronto!\n";
    return 0;
}