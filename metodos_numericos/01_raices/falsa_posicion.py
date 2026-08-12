# ==========================================
# METODO DE FALSA POSICION (REGULA FALSI)
# ==========================================
# Es un metodo CERRADO, igual que Biseccion:
# necesita un intervalo [a, b] con f(a) * f(b) < 0 y mantiene
# la raiz encerrada en todo momento.
#
# DIFERENCIA CON BISECCION:
# Biseccion toma el punto medio c = (a + b) / 2, sin mirar el valor
# de la funcion. Falsa Posicion traza la recta (cuerda) que une los
# puntos (a, f(a)) y (b, f(b)) y toma como nueva aproximacion el
# punto donde esa recta corta el eje x:
#
#       c = b - f(b) * (a - b) / (f(a) - f(b))
#
# Al usar la informacion de f, se acerca mas rapido al lado donde
# la funcion vale menos. Como contrapartida, uno de los extremos
# suele quedarse fijo (extremo estancado), por lo que la amplitud
# (b - a) NO tiende a cero. Por eso el error NO se mide con el
# tamano del intervalo sino con el error porcentual aproximado
# entre aproximaciones consecutivas.


# ==========================================
# DATOS DEL PROBLEMA
# ==========================================

def f(x):
    return x**3 - x - 2

a = 1
b = 2

# Tolerancia expresada en PORCENTAJE (error porcentual aproximado)
tolerancia = 0.0001
max_iteraciones = 100


# ==========================================
# ALGORITMO
# ==========================================

def falsa_posicion(f, a, b, tolerancia, max_iteraciones):
    """
    Aplica el metodo de Falsa Posicion (Regula Falsi) sobre [a, b].
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
        print("El intervalo seleccionado no cumple la condicion necesaria para aplicar Falsa Posicion.")
        print("Se requiere f(a) * f(b) < 0.")
        print("f(a) =", fa, "   f(b) =", fb)
        return None

    # ---- Encabezado de la tabla ----
    print("Iteracion        a              b              c              f(c)           Error %")
    print("-----------------------------------------------------------------------------------------")

    i = 0
    c = a
    c_anterior = None      # aproximacion previa (no existe en la 1ra iteracion)
    error = None
    convergio = False

    while i < max_iteraciones:
        i = i + 1

        # Denominador de la formula: no puede ser cero
        denominador = fa - fb
        if denominador == 0:
            print()
            print("El denominador (f(a) - f(b)) es cero: no se puede continuar.")
            break

        # Punto de Falsa Posicion: interseccion de la cuerda con el eje x
        c = b - fb * (a - b) / denominador
        fc = f(c)

        # Error porcentual aproximado entre aproximaciones consecutivas
        if c_anterior is None:
            error = None                 # primera iteracion: no hay referencia previa
            texto_error = "---"
        elif c != 0:
            error = abs((c - c_anterior) / c) * 100
            texto_error = "{:<15.8f}".format(error)
        else:
            error = abs(c - c_anterior)  # evita division por cero si c = 0
            texto_error = "{:<15.8f}".format(error)

        print("{:<12d}{:<15.8f}{:<15.8f}{:<15.8f}{:<15.8f}{}".format(
            i, a, b, c, fc, texto_error))

        # Raiz exacta encontrada
        if fc == 0:
            convergio = True
            error = 0.0
            break

        # Criterio de parada por tolerancia
        if error is not None and error <= tolerancia:
            convergio = True
            break

        # Elegir el subintervalo que conserva el cambio de signo
        if fa * fc < 0:
            # La raiz esta en [a, c]
            b = c
            fb = fc
        else:
            # La raiz esta en [c, b]
            a = c
            fa = fc

        c_anterior = c

    return {"raiz": c, "error": error, "iteraciones": i, "convergio": convergio}


# ==========================================
# EJECUCION
# ==========================================

resultado = falsa_posicion(
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
        print("Raiz aproximada:", round(resultado["raiz"], 8))
        print("Error:", resultado["error"], "%")
        print("Iteraciones:", resultado["iteraciones"])
        print("Convergencia: SI")
    else:
        print("El metodo NO alcanzo la tolerancia pedida.")
        print("Ultima aproximacion:", round(resultado["raiz"], 8))
        if resultado["error"] is None:
            print("Error: no disponible")
        else:
            print("Error alcanzado:", resultado["error"], "%")
        print("Iteraciones:", resultado["iteraciones"])
        print("Convergencia: NO")
