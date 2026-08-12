# ==========================================
# METODO DE ITERACION DE PUNTO FIJO
# ==========================================
# Es un metodo ABIERTO: no necesita un intervalo que encierre la raiz,
# solo una aproximacion inicial x0.
#
# Se parte de la ecuacion f(x) = 0 y se la reescribe en la forma:
#
#       x = g(x)
#
# y luego se itera:
#
#       x_(n+1) = g(x_n)
#
# La convergencia se analiza mediante |g'(x)| < 1 cerca de la raiz.
# Si |g'(x)| >= 1 el metodo puede diverger.
#
# El despeje de g(x) NO es automatico: lo elige el alumno segun el
# ejercicio, y una misma f(x) admite varios despejes (unos convergen
# y otros no).

import math


# ==========================================
# DATOS DEL PROBLEMA
# ==========================================
# Ejemplo: f(x) = x^3 - x - 2 = 0
# Despeje:  x^3 = x + 2   ->   x = (x + 2)^(1/3)

def g(x):
    return (x + 2) ** (1/3)

# Derivada de g(x), cargada manualmente
def dg(x):
    return 1 / (3 * (x + 2) ** (2/3))

x0 = 1

# Tolerancia expresada en PORCENTAJE (error porcentual aproximado)
tolerancia = 0.0001
max_iteraciones = 100

# Limite para detectar divergencia evidente
limite_divergencia = 1e12


# ==========================================
# ALGORITMO
# ==========================================

def punto_fijo(g, dg, x0, tolerancia, max_iteraciones):
    """
    Aplica el metodo de iteracion de punto fijo partiendo de x0.
    Devuelve un diccionario con la raiz aproximada, el error porcentual,
    la cantidad de iteraciones y si el metodo convergio.
    """

    # ---- Validacion de los parametros ----
    if tolerancia <= 0:
        print("La tolerancia debe ser un numero mayor que cero.")
        return None

    if max_iteraciones < 1:
        print("El maximo de iteraciones debe ser al menos 1.")
        return None

    # ---- Analisis de convergencia: |g'(x0)| < 1 ----
    print("Criterio de convergencia:")
    try:
        derivada = abs(dg(x0))
        print("|g'(x0)| =", round(derivada, 8))

        if math.isnan(derivada) or math.isinf(derivada):
            print("WARNING:")
            print("No se pudo evaluar |g'(x0)| (valor no valido).")
            print("Se continuara con las iteraciones.")
        elif derivada < 1:
            print("|g'(x0)| < 1")
            print("Se cumple en x0.")
        else:
            print("WARNING:")
            print("No se cumple |g'(x0)| < 1 en la aproximacion inicial.")
            print("El metodo puede no converger.")
            print("Se continuara con las iteraciones.")
    except Exception as e:
        print("WARNING:")
        print("No se pudo evaluar g'(x0):", e)
        print("Se continuara con las iteraciones.")

    print()

    # ---- Encabezado de la tabla ----
    print("Iteracion       x anterior       x nuevo          Error %")
    print("-----------------------------------------------------------")

    i = 0
    x_actual = x0
    error = None
    convergio = False

    while i < max_iteraciones:
        i = i + 1

        # Iteracion de Punto Fijo:
        # x_(n+1) = g(x_n)
        try:
            x_nuevo = g(x_actual)
        except Exception as e:
            print()
            print("Error al evaluar g(x) en x =", x_actual, ":", e)
            print("Se detiene el calculo.")
            return {"raiz": x_actual, "error": error,
                    "iteraciones": i - 1, "convergio": False}

        # ---- Control de valores no validos ----
        if isinstance(x_nuevo, complex):
            print()
            print("g(x) devolvio un valor complejo. Se detiene el calculo.")
            return {"raiz": x_actual, "error": error,
                    "iteraciones": i - 1, "convergio": False}

        if math.isnan(x_nuevo):
            print()
            print("Se obtuvo un valor NaN. Se detiene el calculo.")
            return {"raiz": x_actual, "error": error,
                    "iteraciones": i - 1, "convergio": False}

        if math.isinf(x_nuevo) or abs(x_nuevo) > limite_divergencia:
            print()
            print("Las aproximaciones crecen sin control: el metodo diverge.")
            print("Se detiene el calculo en la iteracion", i)
            return {"raiz": x_actual, "error": error,
                    "iteraciones": i - 1, "convergio": False}

        # Error porcentual aproximado entre aproximaciones consecutivas
        # (x0 ya es una aproximacion valida, por eso hay error desde la 1ra iteracion)
        if x_nuevo != 0:
            error = abs((x_nuevo - x_actual) / x_nuevo) * 100
        else:
            error = abs(x_nuevo - x_actual)   # evita division por cero

        print("{:<16d}{:<17.8f}{:<17.8f}{:<17.8f}".format(
            i, x_actual, x_nuevo, error))

        # Criterio de parada por tolerancia
        if error <= tolerancia:
            convergio = True
            x_actual = x_nuevo
            break

        # Preparar la siguiente iteracion
        x_actual = x_nuevo

    return {"raiz": x_actual, "error": error,
            "iteraciones": i, "convergio": convergio}


# ==========================================
# EJECUCION
# ==========================================

resultado = punto_fijo(
    g,
    dg,
    x0,
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
        print("Raiz aproximada:", round(resultado["raiz"], 8))
        print("Error:", resultado["error"], "%")
        print("Iteraciones:", resultado["iteraciones"])
        print("Convergencia: SI")
    else:
        if resultado["iteraciones"] >= max_iteraciones:
            print("Se alcanzo el numero maximo de iteraciones.")
        print("Ultima aproximacion:", round(resultado["raiz"], 8))
        if resultado["error"] is None:
            print("Error: no disponible")
        else:
            print("Error alcanzado:", resultado["error"], "%")
        print("Iteraciones:", resultado["iteraciones"])
        print("Convergencia: NO")
