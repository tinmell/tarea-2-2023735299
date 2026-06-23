#include <bits/stdc++.h>
#include <chrono>
#include <sys/resource.h>
#include <fstream>

using namespace std;

// memoria
long getMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

struct Chapter {
    int time;
    int energy;
    long long value;
};

struct Anime {
    string name;
    int q;
    long long bonus;
    vector<Chapter> chapters;
};

// declaraciones
long long bruteForce(const vector<vector<tuple<int,int,long long>>>&, int, int);
long long greedy1(const vector<vector<tuple<int,int,long long>>>&, int, int);
long long greedy2(const vector<vector<tuple<int,int,long long>>>&, int, int);
long long dynamicProgramming(const vector<vector<tuple<int,int,long long>>>&, int, int);

// generar opciones
vector<vector<tuple<int,int,long long>>> generarOpciones(const vector<Anime>& animes) {
    int n = animes.size();
    vector<vector<tuple<int,int,long long>>> opciones(n);

    for (int i = 0; i < n; i++) {
        const Anime& anime = animes[i];

        int tiempo = 0;
        int energia = 0;
        long long satisfaccion = 0;

        opciones[i].push_back({0, 0, 0});

        for (int j = 0; j < anime.q; j++) {
            tiempo += anime.chapters[j].time;
            energia += anime.chapters[j].energy;
            satisfaccion += anime.chapters[j].value;

            long long total = satisfaccion;

            if (j == anime.q - 1) {
                total += anime.bonus;
            }

            opciones[i].push_back({tiempo, energia, total});
        }
    }

    return opciones;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string filename = "output";

    if (argc > 1) {
        filename = argv[1];
        filename = filename.substr(filename.find_last_of("/") + 1);

        if (filename.find(".txt") != string::npos) {
            filename = filename.substr(0, filename.find(".txt"));
        }
    }

    int n, M, E;
    cin >> n >> M >> E;

    vector<Anime> animes(n);

    for (int i = 0; i < n; i++) {
        cin >> animes[i].name >> animes[i].q >> animes[i].bonus;

        animes[i].chapters.resize(animes[i].q);

        for (int j = 0; j < animes[i].q; j++) {
            cin >> animes[i].chapters[j].time
                >> animes[i].chapters[j].energy
                >> animes[i].chapters[j].value;
        }
    }

    auto opciones = generarOpciones(animes);

    // OUTPUT MEASUREMENTS
    string out_path = "data/measurements/" + filename + ".txt";
    ofstream out(out_path);

    long long res_brute = -1;
    double time_b = 0;
    long mem_b = 0;

    if (n <= 25) {
        auto start_b = chrono::high_resolution_clock::now();
        res_brute = bruteForce(opciones, M, E);
        auto end_b = chrono::high_resolution_clock::now();

        time_b = chrono::duration<double, milli>(end_b - start_b).count();
        mem_b = getMemoryUsage();
    }

    if (res_brute == -1)
        out << "Brute: SKIPPED\n";
    else
        out << "Brute: " << res_brute << " | T: " << time_b << " | M: " << mem_b << "\n";

    auto start_g1 = chrono::high_resolution_clock::now();
    long long res_g1 = greedy1(opciones, M, E);
    auto end_g1 = chrono::high_resolution_clock::now();
    double time_g1 = chrono::duration<double, milli>(end_g1 - start_g1).count();
    long mem_g1 = getMemoryUsage();

    auto start_g2 = chrono::high_resolution_clock::now();
    long long res_g2 = greedy2(opciones, M, E);
    auto end_g2 = chrono::high_resolution_clock::now();
    double time_g2 = chrono::duration<double, milli>(end_g2 - start_g2).count();
    long mem_g2 = getMemoryUsage();

    auto start_dp = chrono::high_resolution_clock::now();
    long long res_dp = dynamicProgramming(opciones, M, E);
    auto end_dp = chrono::high_resolution_clock::now();
    double time_dp = chrono::duration<double, milli>(end_dp - start_dp).count();
    long mem_dp = getMemoryUsage();

    cout << "Brute: " << res_brute << " | T: " << time_b << " | M: " << mem_b << "\n";
    cout << "Greedy1: " << res_g1 << " | T: " << time_g1 << " | M: " << mem_g1 << "\n";
    cout << "Greedy2: " << res_g2 << " | T: " << time_g2 << " | M: " << mem_g2 << "\n";
    cout << "DP: " << res_dp << " | T: " << time_dp << " | M: " << mem_dp << "\n";

    out << "n " << n << "\n";
    out << "Brute " << res_brute << " " << time_b << " " << mem_b << "\n";
    out << "Greedy1 " << res_g1 << " " << time_g1 << " " << mem_g1 << "\n";
    out << "Greedy2 " << res_g2 << " " << time_g2 << " " << mem_g2 << "\n";
    out << "DP " << res_dp << " " << time_dp << " " << mem_dp << "\n";

    out.close();

    // MAX SATISFACCION
    long long best = LLONG_MIN;

    if (res_brute != -1) best = max(best, res_brute);
    best = max(best, res_g1);
    best = max(best, res_g2);
    best = max(best, res_dp);

    ofstream out_final("data/outputs/MaxSatisfaccion.txt", ios::app);
    out_final << filename << " " << best << "\n";
    out_final.close();
    
    ofstream results("data/measurements/results.txt", ios::app);

    results << n << " "
            << time_b << " " << mem_b << " "
            << time_g1 << " " << mem_g1 << " "
            << time_g2 << " " << mem_g2 << " "
            << time_dp << " " << mem_dp << "\n";

    results.close();
    return 0;
}