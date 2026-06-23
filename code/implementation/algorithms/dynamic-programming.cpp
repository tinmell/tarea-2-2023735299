#include <bits/stdc++.h>
using namespace std;

long long dynamicProgramming(
    const vector<vector<tuple<int,int,long long>>>& opciones,
    int M,
    int E
) {
    // dp[t][e] = max satisfacción
    vector<vector<long long>> dp(M + 1, vector<long long>(E + 1, 0));

    // recorrer cada anime
    for (int i = 0; i < (int)opciones.size(); i++) {

        // nueva tabla para este anime
        vector<vector<long long>> new_dp = dp;

        // probar cada prefijo del anime i
        for (auto& op : opciones[i]) {
            int t_op, e_op;
            long long v_op;
            tie(t_op, e_op, v_op) = op;

            // recorrer dp
            for (int t = t_op; t <= M; t++) {
                for (int e = e_op; e <= E; e++) {

                    new_dp[t][e] = max(
                        new_dp[t][e],
                        dp[t - t_op][e - e_op] + v_op
                    );
                }
            }
        }

        // actualizar dp
        dp = new_dp;
    }

    // respuesta = máximo en dp
    long long ans = 0;
    for (int t = 0; t <= M; t++) {
        for (int e = 0; e <= E; e++) {
            ans = max(ans, dp[t][e]);
        }
    }

    return ans;
}