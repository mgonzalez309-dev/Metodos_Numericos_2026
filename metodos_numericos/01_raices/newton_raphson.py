# ==========================================
# METODO DE NEWTON-RAPHSON
# ==========================================
# Es un metodo ABIERTO: no necesita un intervalo que encierre la raiz,
# solo una aproximacion inicial x0.
#
# Se traza la recta TANGENTE a la curva en el punto (x_n, f(x_n)) y se
# toma como nueva aproximacion el punto donde esa tangente corta el eje x:
#
#       x_(n+1) = x_n - f(x_n) / f'(x_n)
#
# Es el metodo de convergencia mas rapida de los vistos (cuadratica),
# pero puede fallar si f'(x) se anula o es muy chica, o si x0 esta lejos
# de la raiz.

import math


# ==========================================
# DATOS DEL PROBLEMA
# ==========================================

def f(x):
    return x**3 - x - 2

# Derivada de f(x), cargada manualmente
def df(x):
    return 3*x**2 - 1

x0 = 1

# Tolerancia expresada en PORCENTAJE (error porcentual aproximado)
tolerancia = 0.0001
max_iteraciones = 100

# Valor minimo admitido para |f'(x)| antes de considerarla "casi cero"
derivada_minima = 1e-12

# Limite para detectar divergencia evidente
limite_divergencia = 1e12


# ==========================================
# ALGORITMO
# ==========================================

def newton_raphson(f, df, x0, tolerancia, max_iteraciones):
    """
    Aplica el metodo de Newton-Raphson partiendo de x0.
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

    # ---- Encabezado de la tabla ----
    print("Iteracion       x anterior       f(x)             f'(x)            x nuevo          Error %")
    print("------------------------------------------------------------------------------------------------")

    i = 0
    x_actual = x0
    error = None
    convergio = False

    while i < max_iteraciones:
        i = i + 1

        # ---- Evaluar la funcion y su derivada ----
        try:
            fx = f(x_actual)
            dfx = df(x_actual)
        except Exception as e:
            print()
            print("Error al evaluar f(x) o f'(x) en x =", x_actual, ":", e)
            print("Se detiene el calculo.")
            return {"raiz": x_actual, "error": error,
                    "iteraciones": i - 1, "convergio": False}

        if math.isnan(fx) or math.isnan(dfx) or math.isinf(fx) or math.isinf(dfx):
            print()
            print("Se obtuvo un valor no valido (NaN o infinito) al evaluar f(x) o f'(x).")
            print("Se detiene el calculo en la iteracion", i)
            return {"raiz": x_actual, "error": error,
                    "iteraciones": i - 1, "convergio": False}

        # ---- Si ya estamos parados sobre la raiz, no hace falta iterar ----
        if fx == 0:
            print("{:<16d}{:<17.8f}{:<17.8f}{:<17.8f}{:<17.8f}{:<17.8f}".format(
                i, x_actual, fx, dfx, x_actual, 0.0))
            return {"raiz": x_actual, "error": 0.0,
                    "iteraciones": i, "convergio": True}

        # ---- Control de la derivada: no dividir por cero ni por algo casi cero ----
        if abs(dfx) < derivada_minima:
            print()
            print("La derivada es nula o demasiado cercana a cero en x =", x_actual)
            print("f'(x) =", dfx)
            print("Newton-Raphson no puede continuar: la tangente es horizontal.")
            print("Se sugiere elegir otra aproximacion inicial x0.")
            return {"raiz": x_actual, "error": error,
                    "iteraciones": i - 1, "convergio": False}

        # Formula de Newton-Raphson:
        # x_(n+1) = x_n - f(x_n) / f'(x_n)
        x_nuevo = x_actual - fx / dfx

        # ---- Control de divergencia ----
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

        print("{:<16d}{:<17.8f}{:<17.8f}{:<17.8f}{:<17.8f}{:<17.8f}".format(
            i, x_actual, fx, dfx, x_nuevo, error))

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

resultado = newton_raphson(
    f,
    df,
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
