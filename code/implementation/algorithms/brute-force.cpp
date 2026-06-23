#include <bits/stdc++.h>
using namespace std;

long long mejor;
vector<long long> max_posible;

// backtracking optimizado
void backtracking(
    int i,
    int tiempo_actual,
    int energia_actual,
    long long satisfaccion_actual,
    const vector<vector<tuple<int,int,long long>>>& opciones,
    int M,
    int E
) {
    // poda por recursos
    if (tiempo_actual > M || energia_actual > E) return;

    // poda por cota superior (BOUND)
    if (satisfaccion_actual + max_posible[i] <= mejor) return;

    // caso base
    if (i == (int)opciones.size()) {
        mejor = max(mejor, satisfaccion_actual);
        return;
    }

    // probar opciones (ya ordenadas)
    for (auto& op : opciones[i]) {
        int t, e;
        long long s;
        tie(t, e, s) = op;

        backtracking(
            i + 1,
            tiempo_actual + t,
            energia_actual + e,
            satisfaccion_actual + s,
            opciones,
            M,
            E
        );
    }
}

// función principal
long long bruteForce(
    const vector<vector<tuple<int,int,long long>>>& opciones,
    int M,
    int E
) {
    int n = opciones.size();

    // copiamos para poder modificar
    auto opciones_local = opciones;

    // ordenar opciones por mayor valor
    for (auto& lista : opciones_local) {
        sort(lista.begin(), lista.end(), [](auto& a, auto& b) {
            return get<2>(a) > get<2>(b);
        });
    }

    // precálculo de cotas superiores
    max_posible.assign(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
        long long best = 0;
        for (auto& op : opciones_local[i]) {
            best = max(best, get<2>(op));
        }
        max_posible[i] = max_posible[i + 1] + best;
    }

    // ejecutar backtracking
    mejor = 0;
    backtracking(0, 0, 0, 0, opciones_local, M, E);

    return mejor;
}