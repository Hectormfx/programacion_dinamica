#include <iostream>
using namespace std;

int main()
{

    //Tamaño del Arreglo
    const int TAM = 10;
    double numeros[TAM];
    double suma = 0;
    double promedio = 0;
    double maximo, minimo;

    cout << "=== Calculamos la suma, promedio, minimo y maximo===" << endl;
    cout << "Ingrese un numero 1: ";
    cin >> numeros[0];
    suma += numeros[0];
    minimo = maximo = numeros[0];

    //Primero tenemos que leer los valores del Arreglo
    for (int i = 1; i < TAM; i++)
    {
        cout << "Ingrese el numero" << i + 1 << ": ";
        cin >> numeros[i];
        suma += numeros[i];
        if (numeros[i] > maximo)
            maximo = numeros[i];
        if (numeros[i] < minimo)
            minimo = numeros[i];
    }

     promedio = suma / TAM;

    // Resultados
    cout << "\n=== Resultados ===" << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Minimo: " << minimo << endl;
    cout << "Maximo: " << maximo << endl;

return 0;


}