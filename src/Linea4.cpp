#include <iostream>
#include <array>
#include <limits>
#include <thread>   // sleep
#include <chrono>   // milliseconds

// =================== CONFIGURACIÓN ===================
constexpr int FILAS = 6;
constexpr int COLUMNAS = 7;
constexpr char VACIO = '.';
constexpr char JUGADOR1 = 'X';
constexpr char JUGADOR2 = 'O';

// Animación (puedes ajustarlo)
bool ANIMAR_CAIDA = true;        // ponlo en false si no quieres animación
int  MS_POR_FRAME = 300;          // tiempo entre “frames” de la caída (en ms)

using Tablero = std::array<std::array<char, COLUMNAS>, FILAS>;

// =================== PROTOTIPOS ===================
void clearScreen();
void inicializarTablero(Tablero& t);
void mostrarTablero(const Tablero& t);
bool colocarFicha(Tablero& t, int col0, char ficha);
bool colocarFichaAnimada(Tablero& t, int col0, char ficha, int msPorFrame);
bool columnaLlena(const Tablero& t, int col0);
bool tableroLleno(const Tablero& t);
int  obtenerJugadaValida(const Tablero& t, int numJugador);
bool verificarHorizontal(const Tablero& t, char ficha);
bool verificarVertical(const Tablero& t, char ficha);
bool verificarDiagonalAsc(const Tablero& t, char ficha);
bool verificarDiagonalDesc(const Tablero& t, char ficha);
bool hayGanador(const Tablero& t, char ficha);
bool preguntarJugarDeNuevo();

// =================== IMPLEMENTACIÓN ===================

// Limpia pantalla con ANSI. Si tu consola no soporta, cambia por varios '\n'.
void clearScreen() {
    std::cout << "\x1B[2J\x1B[H"; // clear + cursor home
    // Alternativa sin ANSI:
    // for (int i=0;i<50;++i) std::cout << "\n";
}

void inicializarTablero(Tablero& t) {
    for (int f = 0; f < FILAS; ++f) {
        for (int c = 0; c < COLUMNAS; ++c) t[f][c] = VACIO;
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

// Coloca sin animación (gravedad clásica)
bool colocarFicha(Tablero& t, int col0, char ficha) {
    for (int f = FILAS - 1; f >= 0; --f) {
        if (t[f][col0] == VACIO) { t[f][col0] = ficha; return true; }
    }
    return false; // columna llena
}

// Coloca con animación de caída
bool colocarFichaAnimada(Tablero& t, int col0, char ficha, int msPorFrame) {
    // 1) Encontrar la fila destino (como en gravedad)
    int destino = -1;
    for (int f = FILAS - 1; f >= 0; --f) {
        if (t[f][col0] == VACIO) { destino = f; break; }
    }
    if (destino == -1) return false; // columna llena

    // 2) Desde arriba hasta destino, ir “dibujando” la ficha
    //    Observación: las celdas por encima del destino están vacías por definición.
    for (int f = 0; f <= destino; ++f) {
        // Colocar ficha temporal en (f, col0)
        t[f][col0] = ficha;

        // Redibujar frame
        clearScreen();
        std::cout << "Conecta 4 (efecto de caída)\n";
        mostrarTablero(t);

        // Si no es el destino, “borrar” para el siguiente frame
        if (f != destino) {
            t[f][col0] = VACIO;
        }

        // Pausa entre frames
        std::this_thread::sleep_for(std::chrono::milliseconds(msPorFrame));
    }
    // Al terminar el bucle, la ficha quedó en destino.
    return true;
}

bool columnaLlena(const Tablero& t, int col0) {
    return t[0][col0] != VACIO;
}

bool tableroLleno(const Tablero& t) {
    for (int c = 0; c < COLUMNAS; ++c) if (t[0][c] == VACIO) return false;
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
        return col0;
    }
}

bool verificarHorizontal(const Tablero& t, char ficha) {
    for (int f = 0; f < FILAS; ++f)
        for (int c = 0; c <= COLUMNAS - 4; ++c)
            if (t[f][c] == ficha && t[f][c+1] == ficha &&
                t[f][c+2] == ficha && t[f][c+3] == ficha) return true;
    return false;
}

bool verificarVertical(const Tablero& t, char ficha) {
    for (int c = 0; c < COLUMNAS; ++c)
        for (int f = 0; f <= FILAS - 4; ++f)
            if (t[f][c] == ficha && t[f+1][c] == ficha &&
                t[f+2][c] == ficha && t[f+3][c] == ficha) return true;
    return false;
}

bool verificarDiagonalDesc(const Tablero& t, char ficha) { // ↘
    for (int f = 0; f <= FILAS - 4; ++f)
        for (int c = 0; c <= COLUMNAS - 4; ++c)
            if (t[f][c] == ficha && t[f+1][c+1] == ficha &&
                t[f+2][c+2] == ficha && t[f+3][c+3] == ficha) return true;
    return false;
}

bool verificarDiagonalAsc(const Tablero& t, char ficha) { // ↗
    for (int f = 3; f < FILAS; ++f)
        for (int c = 0; c <= COLUMNAS - 4; ++c)
            if (t[f][c] == ficha && t[f-1][c+1] == ficha &&
                t[f-2][c+2] == ficha && t[f-3][c+3] == ficha) return true;
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

        clearScreen();
        std::cout << "======================================\n";
        std::cout << "           CONECTA 4 (6x7)\n";
        std::cout << "======================================\n";
        std::cout << "Jugador 1 = " << JUGADOR1 << "   |   Jugador 2 = " << JUGADOR2 << "\n";
        std::cout << "======================================\n";

        while (!terminado) {
            mostrarTablero(tablero);

            int col0 = obtenerJugadaValida(tablero, jugadorNum);

            bool ok = false;
            if (ANIMAR_CAIDA) ok = colocarFichaAnimada(tablero, col0, ficha, MS_POR_FRAME);
            else              ok = colocarFicha(tablero, col0, ficha);

            if (!ok) {
                // Esto no debería ocurrir porque ya validamos, pero por seguridad:
                std::cout << "[Aviso] La columna se encuentra llena.\n";
                continue;
            }

            // ¿Ganó el jugador actual?
            if (hayGanador(tablero, ficha)) {
                clearScreen();
                std::cout << "======================================\n";
                std::cout << "           CONECTA 4 (6x7)\n";
                std::cout << "======================================\n";
                mostrarTablero(tablero);
                std::cout << "¡Jugador " << jugadorNum << " (" << ficha << ") gana! 🎉\n\n";
                terminado = true;
            }
            // ¿Empate?
            else if (tableroLleno(tablero)) {
                clearScreen();
                std::cout << "======================================\n";
                std::cout << "           CONECTA 4 (6x7)\n";
                std::cout << "======================================\n";
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
        clearScreen();
    }

    std::cout << "Gracias por jugar Conecta 4. ¡Hasta pronto!\n";
    return 0;
}