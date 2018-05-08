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
    int getObjetivo() const;
    bool solucionCorrecta() const;
};

Solucion::Solucion(const int tam_max, int num) {
    sol.resize(tam_max);
    w.resize(tam_max);
    objetivo = num;

    for (int i = 0; i < tam_max; i++)
        w[i] = i + 1;

}

Solucion::~Solucion() {}

int Solucion::size() const { return sol.size(); }

void Solucion::iniciaComp(int k) { sol[k] = NULO; }

void Solucion::sigValComp(int k) { sol[k]--; }

bool Solucion::todosGenerados(int k) const { return sol[k] == END; }

int Solucion::decision(int k) const { return sol[k]; }

void Solucion::procesaSolucion() const {
    for (int i = 0; i < sol.size(); i++)
        cout << sol[i] << ' ';

    cout << endl;
}

bool Solucion::factible(int k) const {
    bool fact = false;
    int sumActual = 0, sumRestante = 0;

    for (int i = 0; i <= k; i++)
        sumActual += sol[i] * w[i];

    for (int i = k + 1; i < w.size(); i++)
        sumRestante += w[i];

    if (((sumActual + w[k + 1] <= objetivo) && (sumActual + sumRestante >= objetivo))
            || (sumActual == objetivo))
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

void fuerzaBruta(Solucion& sol, int k) {
    if (k == sol.size()) {
        if (sol.solucionCorrecta())
            sol.procesaSolucion();
    }
    else {
        sol.iniciaComp(k);
        sol.sigValComp(k);

        while (!sol.todosGenerados(k)) {
            fuerzaBruta(sol, k + 1);
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
    fuerzaBruta(sol, 0);

    return 0;
}
