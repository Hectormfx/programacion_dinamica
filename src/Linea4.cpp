#include <iostream>   // Para entrada/salida (cout, cin)
using namespace std;  // Para no escribir std:: cada vez

//CONSTANTES DEL JUEGO
//Usamos constantes para que el código sea más legible
const int FILAS = 6;      // El tablero tiene 6 filas
const int COLUMNAS = 7;   // El tablero tiene 7 columnas
const char VACIO = '.';   // Símbolo para celdas vacías
const char JUGADOR1 = 'X'; // Símbolo del jugador 1
const char JUGADOR2 = 'O'; // Símbolo del jugador 2


// FUNCIÓN 1: Inicializar Tablero 
// Esta función "limpia" el tablero poniéndolo todo vacío
// tablero - matriz que vamos a inicializar
void inicializarTablero(char tablero[FILAS][COLUMNAS]) {
    // Recorremos cada fila
    for (int fila = 0; fila < FILAS; fila++) {
        // Recorremos cada columna en esa fila
        for (int col = 0; col < COLUMNAS; col++) {
            // Ponemos el símbolo de vacío en esa posición
            tablero[fila][col] = VACIO;
        }
    }
    cout << "\n*** Tablero inicializado correctamente ***\n";
}


// FUNCIÓN 2: Mostrar Tablero
// Esta función dibuja el tablero en la consola
// matriz que vamos a mostrar
void mostrarTablero(char tablero[FILAS][COLUMNAS]) {
    cout << "\n";
    
    // Primero mostramos los números de columna (1 a 7)
    cout << "  ";  // Espacio para alinear
    for (int col = 1; col <= COLUMNAS; col++) {
        cout << col << "   ";  // Número de columna con espacios
    }
    cout << "\n";
    
    // Línea separadora decorativa
    cout << "-----------------------------\n";
    
    // Ahora mostramos cada fila del tablero
    for (int fila = 0; fila < FILAS; fila++) {
        cout << "| ";  // Borde izquierdo
        
        // Mostramos cada celda de la fila
        for (int col = 0; col < COLUMNAS; col++) {
            cout << tablero[fila][col] << " | ";  // Celda con bordes
        }
        
        cout << "\n";  // Salto de línea al terminar la fila
    }
    
    // Línea separadora al final
    cout << "-----------------------------\n\n";
}


// FUNCIÓN 3: Colocar Ficha 
// Esta función coloca una ficha en la columna indicada
// La ficha "cae" hasta la posición más baja disponible
// Parámetros:
//   - tablero: la matriz del juego
//   - columna: número de columna (1-7) donde colocar
//   - ficha: símbolo del jugador ('X' o 'O')
// Retorna: true si se pudo colocar, false si la columna está llena
bool colocarFicha(char tablero[FILAS][COLUMNAS], int columna, char ficha) {
    // Ajustamos la columna porque el usuario ve 1-7 pero el array es 0-6
    int col = columna - 1;
    
    // Recorremos la columna de ABAJO hacia ARRIBA
    // (empezamos desde FILAS-1 que es el fondo)
    for (int fila = FILAS - 1; fila >= 0; fila--) {
        // Si encontramos una posición vacía
        if (tablero[fila][col] == VACIO) {
            // Colocamos la ficha ahí
            tablero[fila][col] = ficha;
            return true;  // Éxito: ficha colocada
        }
    }
    
    // Si llegamos aquí, la columna está llena
    return false;  // No se pudo colocar
}


// FUNCIÓN MAIN (PROGRAMA PRINCIPAL)
// Aquí probamos las funciones que creamos
int main() {
    // Declaramos el tablero (matriz de 6x7)
    char tablero[FILAS][COLUMNAS];
    
    cout << "\n";
    cout << "     BIENVENIDO A CONECTA 4\n";
    cout << "\n";
    
    // Inicializamos el tablero (todo vacío)
    inicializarTablero(tablero);
    
    // Mostramos el tablero vacío
    cout << "\nTablero inicial:\n";
    mostrarTablero(tablero);
    
    // PRUEBAS DE COLOCACIÓN
    // Profesor explica: Vamos a hacer algunas pruebas para ver si funciona
    
    cout << " PRUEBA 1: Colocando ficha X en columna 4 \n";
    if (colocarFicha(tablero, 4, JUGADOR1)) {
        cout << "Ficha colocada con exito!\n";
        mostrarTablero(tablero);
    }
    
    cout << "PRUEBA 2: Colocando ficha O en columna 4 \n";
    if (colocarFicha(tablero, 4, JUGADOR2)) {
        cout << "Ficha colocada con exito!\n";
        mostrarTablero(tablero);
    }
    
    cout << "PRUEBA 3: Colocando otra ficha X en columna 4 \n";
    if (colocarFicha(tablero, 4, JUGADOR1)) {
        cout << "Ficha colocada con exito!\n";
        mostrarTablero(tablero);
    }
    
    cout << " PRUEBA 4: Colocando fichas en columna 1 \n";
    colocarFicha(tablero, 1, JUGADOR1);
    colocarFicha(tablero, 1, JUGADOR2);
    mostrarTablero(tablero);
    
    cout << "\n*** FIN DE LAS PRUEBAS DEL COMMIT 1 ***\n";
    cout << "Las fichas 'caen' correctamente!\n\n";
    
    return 0;  // Programa termina exitosamente
}


// ========== NOTAS DEL PROFESOR ==========
/*
COMMIT 1 - RESUMEN:
✅ Creamos el tablero como matriz 6x7
✅ Función para inicializar (poner todo vacío)
✅ Función para mostrar el tablero bonito en consola
✅ Función para colocar fichas (simulando gravedad)
✅ Probamos que las fichas caen correctamente

PRÓXIMO COMMIT:
- Validar entradas del usuario
- Implementar turnos alternados
- Detectar columnas llenas
*/