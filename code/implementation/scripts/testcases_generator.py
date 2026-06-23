"""
Este codigo debe generar casos de prueba para los algoritmos implementados en C++, en la carpeta code/implementation/data/intputs/
"""
import random
import os

def generar_testcase(n, max_q=5, max_time=100, max_energy=50, max_value=100):
    M = random.randint(100, 500)   # tiempo máximo
    E = random.randint(50, 300)    # energía máxima

    lines = []
    lines.append(f"{n} {M} {E}")

    for i in range(n):
        name = f"anime_{i}"
        q = random.randint(1, max_q)
        bonus = random.randint(0, 100)

        lines.append(f"{name} {q} {bonus}")

        for _ in range(q):
            t = random.randint(10, max_time)
            e = random.randint(5, max_energy)
            v = random.randint(10, max_value)

            lines.append(f"{t} {e} {v}")

    return "\n".join(lines)


def guardar_testcases():
    os.makedirs("../data/inputs", exist_ok=True)

    tamaños = [5, 10, 15, 20, 30, 50, 80, 120, 200]

    for n in tamaños:
        for i in range(5):
            contenido = generar_testcase(n)

            filename = f"../data/inputs/test_n{n}_{i}.txt"

            with open(filename, "w") as f:
                f.write(contenido)

    print("Testcases generados correctamente.")


if __name__ == "__main__":
    guardar_testcases()