#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <algorithm> // Para std::swap

using namespace std;

// ===============================================
// 1. ESTRUCTURA DE DATOS
// ===============================================

struct Producto {
    int id;
    string nombre;
    double precio;
    int cantidad;
};

// Constante para el tamaño máximo del arreglo
const int MAX_PRODUCTOS = 10;

// ===============================================
// 2. EXCEPCIONES PERSONALIZADAS
// ===============================================

class ProductoNoEncontrado : public runtime_error {
public:
    ProductoNoEncontrado(const string& criterio) 
        : runtime_error("Error: Producto no encontrado con el criterio: " + criterio) {}
};

class EntradaInvalida : public runtime_error {
public:
    EntradaInvalida(const string& mensaje) 
        : runtime_error("Error de entrada: " + mensaje) {}
};

// ===============================================
// 3. FUNCIONES AUXILIARES DE I/O
// ===============================================

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Lectura segura de enteros con manejo de excepciones
int leerEnteroSeguro(const string& mensaje) {
    int valor;
    cout << mensaje;
    if (!(cin >> valor)) {
        limpiarBuffer();
        throw EntradaInvalida("Se esperaba un número entero.");
    }
    limpiarBuffer();
    return valor;
}

// Lectura segura de dobles (precio) con manejo de excepciones
double leerDobleSeguro(const string& mensaje) {
    double valor;
    cout << mensaje;
    if (!(cin >> valor)) {
        limpiarBuffer();
        throw EntradaInvalida("Se esperaba un valor numérico (precio/cantidad).");
    }
    limpiarBuffer();
    if (valor < 0) {
         throw EntradaInvalida("El valor no puede ser negativo.");
    }
    return valor;
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.get();
}

// ===============================================
// 4. FUNCIONES DE INVENTARIO
// ===============================================

/**
 * @brief Muestra todos los productos en el inventario.
 */
void mostrarInventario(Producto inventario[], int size) {
    cout << "\n============================================\n";
    cout << "          INVENTARIO DE PRODUCTOS\n";
    cout << "============================================\n";
    cout << left << setw(5) << "ID"
         << setw(30) << "Nombre"
         << setw(10) << "Precio"
         << setw(10) << "Cantidad" << endl;
    cout << "--------------------------------------------\n";

    for (int i = 0; i < size; ++i) {
        cout << left << setw(5) << inventario[i].id
             << setw(30) << inventario[i].nombre
             << fixed << setprecision(2) << setw(10) << inventario[i].precio
             << setw(10) << inventario[i].cantidad << endl;
    }
    cout << "============================================\n";
}

/**
 * @brief Busca un producto por ID o Nombre.
 * @param inventario Arreglo de productos.
 * @param size Tamaño del arreglo.
 * @param termino Termino a buscar (ID o Nombre).
 * @param tipo 'ID' o 'NOMBRE'.
 * @return Puntero al producto encontrado.
 * @throws ProductoNoEncontrado si no se encuentra el producto.
 */
Producto* buscarProducto(Producto inventario[], int size, const string& termino, const string& tipo) {
    if (tipo == "ID") {
        try {
            int idBusqueda = stoi(termino);
            for (int i = 0; i < size; ++i) {
                if (inventario[i].id == idBusqueda) {
                    // Retorna un puntero a la estructura encontrada
                    return &inventario[i]; 
                }
            }
        } catch (const invalid_argument&) {
            // Esto ocurre si el término no es un número válido para stoi
            throw EntradaInvalida("La búsqueda por ID debe ser un número entero.");
        }
    } else if (tipo == "NOMBRE") {
        // Búsqueda por nombre (insensible a mayúsculas/minúsculas simple)
        string terminoLower = termino;
        for (char &c : terminoLower) c = tolower(c);

        for (int i = 0; i < size; ++i) {
            string nombreProductoLower = inventario[i].nombre;
            for (char &c : nombreProductoLower) c = tolower(c);
            
            if (nombreProductoLower.find(terminoLower) != string::npos) {
                // Retorna un puntero a la estructura encontrada
                return &inventario[i];
            }
        }
    }
    // Lanza la excepción si el producto no se encuentra
    throw ProductoNoEncontrado(tipo + " = " + termino); 
}

/**
 * @brief Modifica la cantidad de un producto.
 * @param productoMod Puntero al producto a modificar.
 * @param nuevaCantidad Nueva cantidad del producto.
 */
void modificarInventario(Producto* productoMod, int nuevaCantidad) {
    // Uso del operador flecha (->) para acceder a miembros de la estructura a través del puntero
    productoMod->cantidad = nuevaCantidad; 
    cout << "\n✅ Inventario modificado exitosamente:\n";
    cout << "   Producto: " << productoMod->nombre << "\n";
    cout << "   Nueva Cantidad: " << productoMod->cantidad << "\n";
}

// ===============================================
// 5. FUNCIONES DE ORDENAMIENTO (Método de Selección)
// ===============================================

/**
 * @brief Ordena el arreglo de productos usando el método de selección.
 * @param inventario Arreglo de productos.
 * @param size Tamaño del arreglo.
 * @param criterio 'PRECIO' o 'CANTIDAD'.
 */
void ordenarProductos(Producto inventario[], int size, const string& criterio) {
    for (int i = 0; i < size - 1; ++i) {
        int indiceMinimo = i;
        for (int j = i + 1; j < size; ++j) {
            bool debeCambiar = false;

            if (criterio == "PRECIO") {
                // Si el precio actual es menor que el precio mínimo encontrado
                if (inventario[j].precio < inventario[indiceMinimo].precio) {
                    debeCambiar = true;
                }
            } else if (criterio == "CANTIDAD") {
                // Si la cantidad actual es menor que la cantidad mínima encontrada
                if (inventario[j].cantidad < inventario[indiceMinimo].cantidad) {
                    debeCambiar = true;
                }
            }

            if (debeCambiar) {
                indiceMinimo = j;
            }
        }
        // Intercambiar el elemento actual con el elemento mínimo encontrado
        if (indiceMinimo != i) {
            std::swap(inventario[i], inventario[indiceMinimo]); 
        }
    }
    cout << "\n✅ Productos ordenados por " << criterio << " (ascendente).\n";
}

// ===============================================
// 6. FUNCIÓN PRINCIPAL Y MENU
// ===============================================

void mostrarMenu() {
    cout << "\n\n========== SISTEMA DE INVENTARIO ==========\n";
    cout << "1) Mostrar Inventario Completo\n";
    cout << "2) Buscar Producto por ID\n";
    cout << "3) Buscar Producto por Nombre\n";
    cout << "4) Modificar Cantidad de Inventario\n";
    cout << "5) Ordenar por Precio\n";
    cout << "6) Ordenar por Cantidad\n";
    cout << "0) Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    // 1. Inicialización del Arreglo de Estructuras (10 productos)
    Producto inventario[MAX_PRODUCTOS] = {
        {101, "Laptop Gamer X", 1200.00, 15},
        {102, "Monitor 27 Pulgadas", 350.50, 25},
        {103, "Teclado Mecánico RGB", 80.00, 40},
        {104, "Mouse Inalámbrico", 25.99, 60},
        {105, "Disco SSD 1TB", 95.75, 30},
        {106, "Webcam 1080p", 45.00, 12},
        {107, "Router WiFi 6", 110.00, 22},
        {108, "Auriculares Bluetooth", 65.50, 55},
        {109, "Tarjeta Gráfica RTX", 599.99, 8},
        {110, "Hub USB-C 7 en 1", 30.00, 50}
    };

    int opcion;
    bool salir = false;

    while (!salir) {
        try {
            mostrarMenu();
            opcion = leerEnteroSeguro(""); // Lectura segura de la opción del menú

            switch (opcion) {
                case 1:
                    mostrarInventario(inventario, MAX_PRODUCTOS);
                    break;
                
                case 2: // Búsqueda por ID
                case 3: { // Búsqueda por Nombre
                    string tipoBusqueda = (opcion == 2) ? "ID" : "NOMBRE";
                    string terminoBusqueda;
                    cout << "Ingrese el " << tipoBusqueda << " de búsqueda: ";
                    // Usamos getline para NOMBRE; para ID, el error de non-int se captura en buscarProducto
                    if (tipoBusqueda == "NOMBRE") getline(cin, terminoBusqueda);
                    else cin >> terminoBusqueda;

                    Producto* pEncontrado = buscarProducto(inventario, MAX_PRODUCTOS, terminoBusqueda, tipoBusqueda);
                    
                    cout << "\n✅ Producto encontrado:\n";
                    cout << "   ID: " << pEncontrado->id 
                         << " | Nombre: " << pEncontrado->nombre 
                         << " | Precio: $" << fixed << setprecision(2) << pEncontrado->precio 
                         << " | Cantidad: " << pEncontrado->cantidad << "\n";
                    break;
                }
                
                case 4: { // Modificar Cantidad (Uso de punteros)
                    int idModificar = leerEnteroSeguro("Ingrese el ID del producto a modificar: ");
                    // Convertimos el int a string para que la función buscarProducto lo procese
                    Producto* pModificar = buscarProducto(inventario, MAX_PRODUCTOS, to_string(idModificar), "ID");

                    int nuevaCant = leerEnteroSeguro("Ingrese la nueva cantidad en inventario: ");
                    if (nuevaCant < 0) throw EntradaInvalida("La cantidad no puede ser negativa.");

                    modificarInventario(pModificar, nuevaCant); // Uso de puntero
                    break;
                }
                
                case 5: // Ordenar por Precio
                    ordenarProductos(inventario, MAX_PRODUCTOS, "PRECIO");
                    mostrarInventario(inventario, MAX_PRODUCTOS);
                    break;
                
                case 6: // Ordenar por Cantidad
                    ordenarProductos(inventario, MAX_PRODUCTOS, "CANTIDAD");
                    mostrarInventario(inventario, MAX_PRODUCTOS);
                    break;

                case 0:
                    cout << "Saliendo del sistema. ¡Hasta pronto!\n";
                    salir = true;
                    break;

                default:
                    cout << "Opción no válida. Intente de nuevo.\n";
            }
        } catch (const exception& e) {
            // Captura y maneja cualquier excepción (ProductoNoEncontrado, EntradaInvalida, etc.)
            cout << "\n❌ ERROR DEL SISTEMA: " << e.what() << "\n";
        }
        
        if (!salir) {
            pausar();
        }
    }

    return 0;
}