#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

double distanciaCiud(pair<double, double> & a, pair<double, double> & b){
	double dif_x = pow(a.first - b.first, 2);
	double dif_y = pow(a.second - b.second, 2);
	double suma = dif_x + dif_y;
	return sqrt(suma);
}


void leer_puntos(char * nombre, map<int, pair<double, double> > & M){
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;
    
    
    datos.open(nombre);
    if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> n;
    int i=0;
    while (i<n) {
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

 
   
/* 
*/
void leer_orden(char * nombre, vector<int> & V){
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;
  
    datos.open(nombre);
    if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> n;
    V.reserve(n);
    int i=0;
    while (i<n) {
        datos >> act;
	V.push_back(act);
	i++;
      }
       
    datos.close();
    }
   else { 
      cout << "Error de Lectura en " << nombre << endl;
    }
 }
//////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
  
  map<int, pair<double, double> >  M;
  vector<int> V1, V2;
  string fp,fok;
   if (argc == 3) {
     cout << "Error Formato:  tsp puntos orden_correcto" << endl;
     exit(1);
   }




    leer_puntos(argv[1],M);
    leer_orden(argv[2],V1);
    leer_orden(argv[3],V2);
    

    double total1 = distanciaCiud(M[*(--(V1.end()))], M[*(V1.begin())]);
	double total2 = distanciaCiud(M[*(--(V2.end()))], M[*(V2.begin())]);
	//cout << "Ultimo es " << *(--(V2.end())) << "primero " << *(V2.begin())<<endl;
	for(int i = 0; i < V1.size()-1; i++){
		total1+= distanciaCiud(M[V1[i]], M[V1[i+1]]);
		total2+= distanciaCiud(M[V2[i]], M[V2[i+1]]);
	//	cout << "Total es " <<total2 << " añado " << V2[i] << " y " << V2[i+1]<<endl;
	}

	cout << "El recorrido total del algoritmo propio es: " << total2 << endl;
	cout << "El recorrido total del algoritmo optimo es: " << total1 << endl;
	cout << "La diferencia entre ambos algoritmos es: " << total2-total1 << endl;

    return 0;
} 


















