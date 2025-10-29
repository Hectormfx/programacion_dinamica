#include <iostream>
#include <string>
using namespace std;

struct Alumno{
    string nombre;
    int edad;
    float promedio;
};

int main()
{

    const int TAM = 10;
    Alumno grupo[TAM]; // Arreglo de una estructura definida por el usario
    cout << "===Captura los datos del alumno" << endl;
    for (int i = 0; i < TAM; i++){
        cout << "\nAlumno" << i +1 << ":" << endl;
        getline(cin >> ws, grupo[i].nombre);
        cout << "Edad: ";
        cin >> grupo[i].edad;
        cout << "Promedio: ";
        cin >> grupo[i].promedio;
    }

    cout << "=== Listado de alumnos ===" << endl;
    for (int i=0; i < TAM; i++){
        cout << "\nAlumno " << i +1 << ":" << endl;
        cout << "Nombre" << grupo[i].nombre;
        cout << "Edad" << grupo[i].edad;
        cout << "Promedio" << grupo[i].promedio;
    }

    return 0;
}