#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

#define NULO 2
#define END -1

class Solucion {
private:
    vector<int> sol;
    vector<int> w;
    int objetivo;
    int s, r;           // s guarda la suma de numero * aparicion, r guarda la suma de los numeros restantes

public:
    Solucion(const int tam_max, int num);
    ~Solucion();
    int size() const;
    void iniciaComp(int k);
    void sigValComp(int k);
    bool todosGenerados(int k) const;
    int decision(int k) const;
    void procesaSolucion() const;
    bool factible(int k) const;
    void vueltaAtras(int pos);
    int getObjetivo() const;
    bool solucionCorrecta() const;
};

Solucion::Solucion(const int tam_max, int num) {
    sol.resize(tam_max);
    w.resize(tam_max);
    objetivo = num;
    s = r = 0;

    for (int i = 0; i < tam_max; i++) {
        w[i] = i + 1;
        r += i + 1;
    }
}

Solucion::~Solucion() {}

int Solucion::size() const { return sol.size(); }

void Solucion::iniciaComp(int k) { sol[k] = NULO; }

void Solucion::sigValComp(int k) {
    sol[k]--; 

    if (sol[k] == 1) {
        s += w[k];
        r -= w[k];
    }

    if (sol[k] == 0)
        s -= w[k];
}

bool Solucion::todosGenerados(int k) const { return sol[k] == END; }

int Solucion::decision(int k) const { return sol[k]; }

void Solucion::procesaSolucion() const {
    for (int i = 0; i < sol.size(); i++)
        cout << sol[i] << ' ';

    cout << endl;
}

bool Solucion::factible(int k) const {
    bool fact = false;

    if (((s + w[k + 1] <= objetivo) && (s + r >= objetivo))
            || (s == objetivo))
        fact = true;

    return fact;
}

int Solucion::getObjetivo() const { return objetivo; }

bool Solucion::solucionCorrecta() const{
    bool correcta = false;
    int sumAux = 0;

    for (int i = 0; i < sol.size() && !correcta; i++)
        sumAux += sol[i] * w[i];

    if (sumAux == objetivo)
        correcta = true;

    return correcta;
}

void Solucion::vueltaAtras(int pos) {
    if (pos == sol.size())
        return;

    r += w[pos];
    sol[pos] = NULO;
}

void backRecursivo(Solucion& sol, int k) {
    if (k == sol.size())
        sol.procesaSolucion();

    else {
        sol.iniciaComp(k);
        sol.sigValComp(k);

        while (!sol.todosGenerados(k)) {
            if (sol.factible(k)) {
                backRecursivo(sol, k + 1);
                sol.vueltaAtras(k + 1);
            }
            sol.sigValComp(k);
        }
    }
}

int main(int argc, char *argv[]) {
    int tam_max, objetivo;

    if (argc != 3) {
        cerr << "Error en " << argv[0] << endl;
        cerr << "Falta tamanio num_obtener" << endl;
        return -1;
    }

    tam_max = atoi(argv[1]);
    objetivo = atoi(argv[2]);

    Solucion sol(tam_max, objetivo);
    
    backRecursivo(sol, 0);

    return 0;
}
