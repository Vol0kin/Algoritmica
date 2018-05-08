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
#include <list>
using namespace std;

double distanciaCiud(pair<double, double> & a, pair<double, double> & b){
	double dif_x = pow(a.first - b.first, 2);
	double dif_y = pow(a.second - b.second, 2);
	double suma = dif_x + dif_y;
	return sqrt(suma);
}

int posCiudadCercana(map<int, pair<int, pair<double, double> > >  M, int pos, double &dist_fin){
	int pos_cerc = -1;
	double mejor_dist = 9999999999;
	std::map<int, pair< int, pair<double, double> > >::iterator original=M.find(pos);
	

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
	dist_fin = mejor_dist;
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

	list<int> orden;
	string fp,fok;
	if (argc == 1) {
		cout << "Error Formato:  tsp puntos orden_correcto" << endl;
		exit(1);
	}
	leer_puntos(argv[1], tam, M);   

	srand(time(NULL));

	//int pos_ini = rand() % tam + 1;
	int pos_ini = 109;

	int aux1, aux2;
		double dist1, dist2;
	orden.push_back(pos_ini);
	int it_pos = posCiudadCercana(M, pos_ini, dist1);
	orden.push_back(it_pos);
	(((*(M.find(pos_ini))).second).first)= 1;
	(((*(M.find(it_pos))).second).first)= 1;

	for(int i = 0; i < M.size()-2; i++){
		aux1 = posCiudadCercana(M, pos_ini, dist1);
		aux2 = posCiudadCercana(M, it_pos, dist2);
		if(dist1<dist2){
			orden.push_front(aux1);
			(((*(M.find(aux1))).second).first)= 1;
			pos_ini = aux1;
			//cout << "delante"<<aux1<<endl;
		}else{
			orden.push_back(aux2);
			(((*(M.find(aux2))).second).first)= 1;
			it_pos = aux2;
			//cout <<"detras"<<aux2<<endl;
		}
		
	}
	cout << "DIMENSION: "<<tam <<endl;
	for(list<int>::iterator it = orden.begin(); it != orden.end(); ++it){
		cout << (*it) << "   ";
		cout << endl;
	}
	//cout << (*(orden.begin())) << "   " << endl;
	return 0;
} 































