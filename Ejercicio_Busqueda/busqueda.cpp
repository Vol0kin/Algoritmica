#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int busquedaBinaria(int * array, int elem, int izda, int dcha) {
    if (dcha - izda > 1) {
    
        int medio = (izda + dcha) / 2;
    
        if (array[medio] == elem)
            return medio;
        else {
            if (array[medio] > elem)
                return busquedaBinaria(array, elem, izda, medio - 1);
            else
                return busquedaBinaria(array, elem, medio + 1, dcha);
        }
    } else {
        if (dcha - izda == 0)
            return izda;
        else {
            if (array[izda] == elem)
                return izda;
            else
                return dcha;
        }
    }
}

int busquedaTernaria(int * array, int elem, int izda, int dcha) {
    if (dcha - izda > 2) {
        int medio1, medio2;
        medio1 = izda + (dcha - izda) / 3;
        medio2 = izda + (2 * (dcha - izda)) / 3;

        if (elem == array[medio1])
            return medio1;
        
        if (elem == array[medio2])
            return medio2;

        if (elem < array[medio1])
            return busquedaTernaria(array, elem, izda, medio1 - 1);

        if (elem < array[medio2])
            return busquedaTernaria(array, elem, medio1 + 1, medio2 - 1);
        else
            return busquedaTernaria(array, elem, medio2 + 1, dcha);            
    } else {
        if (dcha - izda == 2) {
            int medio = izda + 1;

            if (array[izda] == elem)
                return izda;
            else if (array[medio] == elem)
                return medio;
            else
                return dcha;
        } else if (dcha - izda == 1) {
            if (array[izda] == elem)
                return izda;
            else
                return dcha;
        } else
            return izda;
    }
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Error en " << argv[0] << ". Falta el tamanio del array" << endl;
        return -1;
    }

    int n = atoi(argv[1]), pos, elemento;
    int * array = new int[n];
    clock_t t1, t2;

    for (int i = 0; i < n; i++)
        array[i] = i + 1;

    srand(time(0));
    elemento = rand() % n + 1;

    t1 = clock();
    pos = busquedaTernaria(array, elemento, 0, n - 1);
    t2 = clock();
   
    cout << n << ' ' << ((double)(t2 - t1)) / CLOCKS_PER_SEC << endl;
    delete[] array;
    return 0;
}
