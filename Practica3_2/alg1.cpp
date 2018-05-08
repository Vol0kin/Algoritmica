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

int posCiudadCercana(map<int, pair<int, pair<double, double> > > & M, int pos){
	int pos_cerc = -1;
	double mejor_dist = 9999999999;
	std::map<int, pair< int, pair<double, double> > >::iterator original=M.find(pos);
	(((*original).second).first)= 1;

	double distancia;
	for(std::map<int, pair< int, pair<double, double> > >::iterator it = M.begin(); it != M.end(); ++it){
		if(((((*it).second).first) < 1)&& (it != original)){
			distancia = distanciaCiud(((*original).second).second, ((*it).second).second);
			if(distancia < mejor_dist){
				pos_cerc = ((*it).first);
				mejor_dist = distancia;
			}
		}
	}
	//cout << "Conecto " << (*original).first << " con " << (*(M.find(pos_cerc))).first <<"     " << (*(--(--(M.end())))).first <<endl;
	return pos_cerc;
}

void leer_puntos(char * nombre, int & tam,map<int, pair< int, pair<double, double> > > & M){
    ifstream datos;
    string s;
    pair< int, pair<double,double> > p;
    int n,act;
    
    
    datos.open(nombre);
    if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> tam;
    int i=0;
    while (i<tam) {
        datos >> act >> (p.second).first >> (p.second).second;
	p.first = 0;
	M[act] = p;
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
	int tam;
	map<int, pair<int, pair<double, double> > > M;

	vector<int> orden;
	string fp,fok;
	if (argc == 1) {
		cout << "Error Formato:  tsp puntos orden_correcto" << endl;
		exit(1);
	}
	leer_puntos(argv[1], tam, M);   

	srand(time(NULL));

	//int pos_ini = rand() % tam + 1;
	int pos_ini = 1;

	std::map<int, pair< int, pair<double, double> > >::iterator original=M.find(pos_ini), it;
	
	orden.push_back(pos_ini);
	int it_pos = pos_ini;
	int aux;
	for(int i = 0; i < M.size()-1; i++){
		aux = posCiudadCercana(M, it_pos);
		it_pos = aux;
		orden.push_back(it_pos);
		original = M.find(pos_ini);
		/*for(std::map<int, pair< int, pair<double, double> > >::iterator orig=M.begin(); orig != M.end(); ++orig)
			if((((*orig).second).first) != 1)
				cout << (*orig).first << "  ";
		cout << endl;*/
		
	}
	cout << "DIMENSION: "<<tam <<endl;
	for(vector<int>::iterator it = orden.begin(); it != orden.end(); ++it){
		cout << (*it) << "   ";
		cout << endl;
	}
	//cout << (*(orden.begin())) << "   " << endl;
	return 0;
} 































