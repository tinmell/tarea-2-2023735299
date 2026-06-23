import matplotlib.pyplot as plt
import os

def leer_datos(ruta):
    datos = {}

    with open(ruta, "r") as f:
        for linea in f:
            partes = linea.strip().split()

            # formato esperado:
            # n tb mb tg1 mg1 tg2 mg2 tdp mdp
            if len(partes) != 9:
                continue

            n = int(partes[0])

            tb = float(partes[1])
            mb = float(partes[2])

            tg1 = float(partes[3])
            mg1 = float(partes[4])

            tg2 = float(partes[5])
            mg2 = float(partes[6])

            tdp = float(partes[7])
            mdp = float(partes[8])

            if n not in datos:
                datos[n] = {
                    "tb": [], "mb": [],
                    "tg1": [], "mg1": [],
                    "tg2": [], "mg2": [],
                    "tdp": [], "mdp": []
                }

            datos[n]["tb"].append(tb)
            datos[n]["mb"].append(mb)

            datos[n]["tg1"].append(tg1)
            datos[n]["mg1"].append(mg1)

            datos[n]["tg2"].append(tg2)
            datos[n]["mg2"].append(mg2)

            datos[n]["tdp"].append(tdp)
            datos[n]["mdp"].append(mdp)

    # PROMEDIOS
    n_vals = sorted(datos.keys())

    def promedio(lista):
        return sum(lista) / len(lista) if lista else 0

    tb = [promedio(datos[n]["tb"]) for n in n_vals]
    mb = [promedio(datos[n]["mb"]) for n in n_vals]

    tg1 = [promedio(datos[n]["tg1"]) for n in n_vals]
    mg1 = [promedio(datos[n]["mg1"]) for n in n_vals]

    tg2 = [promedio(datos[n]["tg2"]) for n in n_vals]
    mg2 = [promedio(datos[n]["mg2"]) for n in n_vals]

    tdp = [promedio(datos[n]["tdp"]) for n in n_vals]
    mdp = [promedio(datos[n]["mdp"]) for n in n_vals]

    return n_vals, tb, tg1, tg2, tdp, mb, mg1, mg2, mdp


# GRÁFICOS TIEMPO
def grafico_tiempos(n, tb, tg1, tg2, tdp):
    plt.figure()

    plt.plot(n, tb, marker='o', label='Brute Force')
    plt.plot(n, tg1, marker='o', label='Greedy 1')
    plt.plot(n, tg2, marker='o', label='Greedy 2')
    plt.plot(n, tdp, marker='o', label='DP')

    plt.xlabel("n")
    plt.ylabel("Tiempo (ms)")
    plt.title("Comparación de tiempos")
    plt.legend()
    plt.grid()

    plt.savefig("../data/plots/tiempos.png")
    plt.close()


def grafico_sin_brute(n, tg1, tg2, tdp):
    plt.figure()

    plt.plot(n, tg1, marker='o', label='Greedy 1')
    plt.plot(n, tg2, marker='o', label='Greedy 2')
    plt.plot(n, tdp, marker='o', label='DP')

    plt.xlabel("n")
    plt.ylabel("Tiempo (ms)")
    plt.title("Tiempos sin brute force")
    plt.legend()
    plt.grid()

    plt.savefig("../data/plots/tiempos_sin_brute.png")
    plt.close()


# CALIDAD
def grafico_calidad(n, tg1, tg2, tdp):
    plt.figure()

    ratio_g1 = [g1/dp if dp != 0 else 0 for g1, dp in zip(tg1, tdp)]
    ratio_g2 = [g2/dp if dp != 0 else 0 for g2, dp in zip(tg2, tdp)]

    plt.plot(n, ratio_g1, marker='o', label='Greedy1 / DP')
    plt.plot(n, ratio_g2, marker='o', label='Greedy2 / DP')

    plt.xlabel("n")
    plt.ylabel("Calidad relativa")
    plt.title("Calidad de solución")
    plt.legend()
    plt.grid()

    plt.savefig("../data/plots/calidad.png")
    plt.close()


# MEMORIA
def grafico_memoria(n, mb, mg1, mg2, mdp):
    plt.figure()

    plt.plot(n, mb, marker='o', label='Brute Force')
    plt.plot(n, mg1, marker='o', label='Greedy 1')
    plt.plot(n, mg2, marker='o', label='Greedy 2')
    plt.plot(n, mdp, marker='o', label='DP')

    plt.xlabel("n")
    plt.ylabel("Memoria (KB)")
    plt.title("Uso de memoria")
    plt.legend()
    plt.grid()

    plt.savefig("../data/plots/memoria.png")
    plt.close()


# TABLA
def imprimir_tabla(n, tb, tg1, tg2, tdp):
    print("\nTabla resumen:")
    print("n\tBrute\tG1\tG2\tDP")

    for i in range(len(n)):
        print(f"{n[i]}\t{tb[i]:.4f}\t{tg1[i]:.4f}\t{tg2[i]:.4f}\t{tdp[i]:.4f}")


# MAIN
def main():
    ruta = "../data/measurements/results.txt"

    if not os.path.exists(ruta):
        print("No existe results.txt")
        return

    os.makedirs("../data/plots", exist_ok=True)

    n, tb, tg1, tg2, tdp, mb, mg1, mg2, mdp = leer_datos(ruta)

    grafico_tiempos(n, tb, tg1, tg2, tdp)
    grafico_sin_brute(n, tg1, tg2, tdp)
    grafico_calidad(n, tg1, tg2, tdp)
    grafico_memoria(n, mb, mg1, mg2, mdp)

    imprimir_tabla(n, tb, tg1, tg2, tdp)

    print("\nGráficos generados en data/plots/")


if __name__ == "__main__":
    main()