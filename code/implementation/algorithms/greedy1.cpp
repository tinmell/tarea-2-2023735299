#include <bits/stdc++.h>
using namespace std;

// función greedy 1
long long greedy1(
    const vector<vector<tuple<int,int,long long>>>& opciones,
    int M,
    int E
) {
    struct Item {
        int anime_id;
        int tiempo;
        int energia;
        long long valor;
        double ratio;
    };

    vector<Item> items;

    // construir lista de todos los prefijos
    for (int i = 0; i < (int)opciones.size(); i++) {
        for (auto& op : opciones[i]) {
            int t, e;
            long long v;
            tie(t, e, v) = op;

            if (t == 0 && e == 0) continue; // ignorar opción vacía

            double ratio = (double)v / (t + e);

            items.push_back({i, t, e, v, ratio});
        }
    }

    // ordenar por ratio descendente
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    int tiempo_total = 0;
    int energia_total = 0;
    long long satisfaccion_total = 0;

    vector<bool> usado(opciones.size(), false);

    for (auto& item : items) {
        if (usado[item.anime_id]) continue;

        if (tiempo_total + item.tiempo <= M &&
            energia_total + item.energia <= E) {

            tiempo_total += item.tiempo;
            energia_total += item.energia;
            satisfaccion_total += item.valor;

            usado[item.anime_id] = true;
        }
    }

    return satisfaccion_total;
}