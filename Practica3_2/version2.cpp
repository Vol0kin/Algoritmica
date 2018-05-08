#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <climits>

using namespace std;

double calcularDistanciaEuclidea(const pair<double, double>& x1, const pair<double, double>& x2) {
    double difX = pow(x1.first - x2.first, 2);
    double difY = pow(x1.second - x2.second, 2);
    
    return sqrt(difX + difY);
}

void calcularMatrizDistancias(vector< vector<double> >& matriz, map<int, pair<double, double> >& M, int tam) {
    double distancia;

    for (int i = 0; i < tam; i++) {
        for (int j = i + 1; j < tam; j++) {
            distancia = calcularDistanciaEuclidea(M[i + 1], M[j + 1]);
            matriz[i][j] = matriz[j][i] = distancia;
        }
    }
}

void leer_puntos(string nombre, map<int, pair<double, double> > & M, int& tam) {
    ifstream datos;
    string s;
    pair<double,double> p;
    int act;
    
    
    datos.open(nombre.c_str());
    if (datos.is_open()) {
        datos >> s; // Leo "dimension:"
        datos >> tam;
        int i=0;
        while (i<tam) {
            datos >> act >> p.first >> p.second;
    	    M[act] = p;
	        i++;
        }
       
        datos.close();
    }

    else { 
        cout << "Error de Lectura en " << nombre << endl;
    }
}

// opcion: 1-> NORTE
//         2-> OESTE
//         3-> ESTE
int buscarCiudadCardinalidad(map<int, pair<double, double> > & M, int opcion) {
    double busqueda;
    int ciudad;

    if (opcion == 1 || opcion == 3)
        busqueda = INT_MIN;
    else
        busqueda = INT_MAX;

    for (auto iter = M.begin(); iter != M.end(); ++iter) {
        if (opcion == 1) {
            if (((*iter).second).second > busqueda) {
                busqueda = ((*iter).second).second;
                ciudad = (*iter).first;
            }
        } else if(opcion == 2) {
            if (((*iter).second).first < busqueda) {
                busqueda = ((*iter).second).first;
                ciudad = (*iter).first;
            }
        } else {
            if (((*iter).second).first > busqueda) {
                busqueda = ((*iter).second).first;
                ciudad = (*iter).first;
            }
        }
    }

    return ciudad;
}

void insercionTSP(vector< vector<double> >& distancias, vector<int>& candidatas, 
                  vector<int>& solucion, map<int, pair<double, double> > M) {
    double coste, costeAux;
    int ciudadNorte, ciudadOeste, ciudadEste;       
    vector<int>::iterator posicion;
    int nodoActual, nodoSiguiente, ciudadInsertar, ciudadEliminar;
    
    ciudadNorte = buscarCiudadCardinalidad(M, 1);                               // Se busca la ciudad mas al norte
    solucion.push_back(ciudadNorte);
    candidatas.erase(find(candidatas.begin(), candidatas.end(), ciudadNorte));
    M.erase(ciudadNorte);
    
    ciudadOeste = buscarCiudadCardinalidad(M, 2);                               // Se busca la ciudad mas al oeste
    solucion.push_back(ciudadOeste);
    candidatas.erase(find(candidatas.begin(), candidatas.end(), ciudadOeste));
    M.erase(ciudadOeste);
    
    ciudadEste  = buscarCiudadCardinalidad(M, 3);                               // Se busca la ciudad mas al este
    solucion.push_back(ciudadEste);
    candidatas.erase(find(candidatas.begin(), candidatas.end(), ciudadEste));
    M.erase(ciudadEste);

    while (candidatas.size() > 0) {
        coste = INT_MAX;

        for (int i = 0; i < solucion.size(); i++) {
            nodoActual = solucion[i];
            nodoSiguiente = solucion[(i + 1) % solucion.size()];

            for (int j = 0; j < candidatas.size(); j++) {
                costeAux = distancias[nodoActual - 1][candidatas[j] - 1] + distancias[candidatas[j] - 1][nodoSiguiente - 1] - distancias[nodoActual - 1][nodoSiguiente - 1];

                if (costeAux < coste) {
                    coste = costeAux;
                    ciudadInsertar = candidatas[j];
                    posicion = find(solucion.begin(), solucion.end(), nodoSiguiente);
                    ciudadEliminar = j;
                }
            }
        }

        solucion.insert(posicion, ciudadInsertar);
        candidatas.erase(candidatas.begin() + ciudadEliminar);
    }
}
 
int main(int argc, char * argv[]) {
    int dimension;
    map<int, pair<double, double> > M;
    vector< vector <double> > distancias;
    vector<int> solucion;
    vector<int> candidatas;

    if (argc == 1) {
        cout << "Error Formato:  tsp puntos" << endl;
        exit(1);
    }
    
    leer_puntos(string(argv[1]), M, dimension);   
    cout << "Dimension" <<  ' ' <<  dimension << endl;

    distancias.resize(dimension);
    fill(distancias.begin(), distancias.end(), vector<double>(dimension, 0.0));
    calcularMatrizDistancias(distancias, M, dimension); 

    for (int i = 0; i < dimension; i++)
        candidatas.push_back(i + 1);

    insercionTSP(distancias, candidatas, solucion, M);

    for (auto iter = solucion.begin(); iter != solucion.end(); ++iter)
        cout << *iter << endl;

/*
    double coste = 0;
    cout << solucion.size() << endl;
    for (int i = 0; i < solucion.size(); i++)
        coste += distancias[solucion[i] - 1][solucion[(i+1) % solucion.size()] - 1];
    cout << coste << endl;
*/
    return 0;
}
