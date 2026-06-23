#include <bits/stdc++.h>
using namespace std;

long long greedy2(
    const vector<vector<tuple<int,int,long long>>>& opciones,
    int M,
    int E
) {
    struct MejorOpcion {
        int anime_id;
        int tiempo;
        int energia;
        long long valor;
        double ratio;
    };

    vector<MejorOpcion> mejores;

    // para cada anime encontrar su mejor prefijo
    for (int i = 0; i < (int)opciones.size(); i++) {
        double mejor_ratio = 0.0;
        int best_t = 0, best_e = 0;
        long long best_v = 0;

        for (auto& op : opciones[i]) {
            int t, e;
            long long v;
            tie(t, e, v) = op;

            if (t == 0 && e == 0) continue;

            double ratio = (double)v / (t + e);

            if (ratio > mejor_ratio) {
                mejor_ratio = ratio;
                best_t = t;
                best_e = e;
                best_v = v;
            }
        }

        // guardar mejor opción del anime
        if (best_t > 0 || best_e > 0) {
            mejores.push_back({i, best_t, best_e, best_v, mejor_ratio});
        }
    }

    // ordenar animes por mejor ratio
    sort(mejores.begin(), mejores.end(), [](const MejorOpcion& a, const MejorOpcion& b) {
        return a.ratio > b.ratio;
    });

    int tiempo_total = 0;
    int energia_total = 0;
    long long satisfaccion_total = 0;

    // seleccionar animes
    for (auto& m : mejores) {
        if (tiempo_total + m.tiempo <= M &&
            energia_total + m.energia <= E) {

            tiempo_total += m.tiempo;
            energia_total += m.energia;
            satisfaccion_total += m.valor;
        }
    }

    return satisfaccion_total;
}