# ==========================================
# METODO DE BISECCION
# ==========================================
# Metodo cerrado para hallar raices de f(x) = 0.
# Requiere un intervalo [a, b] donde f(a) * f(b) < 0
# (Teorema de Bolzano: si f es continua y cambia de signo,
#  existe al menos una raiz dentro del intervalo).


# ==========================================
# DATOS DEL PROBLEMA
# ==========================================

def f(x):
    return x**3 - x - 2

a = 1
b = 2

tolerancia = 0.0001
max_iteraciones = 100


# ==========================================
# ALGORITMO
# ==========================================

def biseccion(f, a, b, tolerancia, max_iteraciones):
    """
    Aplica el metodo de biseccion sobre el intervalo [a, b].
    Devuelve un diccionario con la raiz aproximada, el error,
    la cantidad de iteraciones y si el metodo convergio.
    """

    fa = f(a)
    fb = f(b)

    # ---- Validacion: alguno de los extremos ya es raiz ----
    if fa == 0:
        print("El extremo a =", a, "ya es una raiz exacta de f(x).")
        return {"raiz": a, "error": 0.0, "iteraciones": 0, "convergio": True}

    if fb == 0:
        print("El extremo b =", b, "ya es una raiz exacta de f(x).")
        return {"raiz": b, "error": 0.0, "iteraciones": 0, "convergio": True}

    # ---- Validacion: debe haber cambio de signo ----
    if fa * fb > 0:
        print("El intervalo seleccionado no cumple la condicion necesaria para aplicar Biseccion.")
        print("Se requiere f(a) * f(b) < 0.")
        print("f(a) =", fa, "   f(b) =", fb)
        return None

    # ---- Encabezado de la tabla ----
    print("Iteracion        a              b              c              f(c)           Error")
    print("-------------------------------------------------------------------------------------")

    i = 0
    c = a
    error = abs(b - a)
    convergio = False

    while i < max_iteraciones:
        i = i + 1

        # Calcular punto medio del intervalo
        c = (a + b) / 2
        fc = f(c)

        # Cota del error: semiamplitud del intervalo actual
        error = (b - a) / 2

        print("{:<12d}{:<15.6f}{:<15.6f}{:<15.6f}{:<15.6f}{:<15.6f}".format(
            i, a, b, c, fc, error))

        # Raiz exacta encontrada
        if fc == 0:
            convergio = True
            error = 0.0
            break

        # Criterio de parada por tolerancia
        if error < tolerancia:
            convergio = True
            break

        # Elegir el subintervalo que contiene la raiz (cambio de signo)
        if fa * fc < 0:
            # La raiz esta en [a, c]
            b = c
            fb = fc
        else:
            # La raiz esta en [c, b]
            a = c
            fa = fc

    return {"raiz": c, "error": error, "iteraciones": i, "convergio": convergio}


# ==========================================
# EJECUCION
# ==========================================

resultado = biseccion(
    f,
    a,
    b,
    tolerancia,
    max_iteraciones
)

if resultado is not None:
    print()
    print("========================================")
    print("RESULTADO")
    print("========================================")
    print()

    if resultado["convergio"]:
        print("Raiz aproximada:", round(resultado["raiz"], 6))
        print("Error:", round(resultado["error"], 8))
        print("Iteraciones:", resultado["iteraciones"])
    else:
        print("El metodo NO convergio en", max_iteraciones, "iteraciones.")
        print("Ultima aproximacion:", round(resultado["raiz"], 6))
        print("Error alcanzado:", round(resultado["error"], 8))
