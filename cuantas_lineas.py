#!/usr/bin/python3

"""
Este programa cuenta líneas de código, ignorando comentarios y líneas vacías.

./cuantas_lineas.py archivo|directorio

Si el argumento pasado es un archivo, cuenta las líneas de código en ese
archivo.

Si el argumento es un directorio, cuenta las líneas de código de todos los
archivos con extensión reconocida en ese directorio y todos sus subdirectorios
que no sean ocultos, recursivamente.

Las extensiones reconocidas son:
- .c
- .cpp
- .py
- .jl

Este programa hace las siguientes suposiciones sobre los contenidos de los
contenidos de los archivos:
- Son programas válidos sin errores de sintaxis. En particular, todos los
  comentarios multilínea que se abren también se cierran.
- Todo el texto que no está en un comentario es código a ser contado.
- Los comentarios unilínea pueden empezar al principio de una línea o después
  de código a ser contado.
- Los comentarios multiĺinea pueden empezar al principio de una línea o después
  de código a ser contado.
- Las líneas en las que cierra un comentario multilínea no tienen código ni
  comentarios unilínea, pero sí pueden tener la apertura de otro comentario
  multilínea.
- Los comentarios multilínea pueden abrir y cerrar en la misma línea, excepto
  cuando en esa línea también cierra un comentario multilínea anterior.
- Los comentarios multilínea no tienen en su texto instancias del símbolo que
  abre comentarios multilínea.
- En python los comentarios multilínea se escriben con " y no '.
"""

def tipo_de_linea(linea, singleline, multiline_open, multiline_close):
    """
    Determina qué acciones contiene una línea en cuanto a código y comentarios.

    Parmámetros:
    - línea es la línea. Tiene que estar lstriped.
    - singleline es el símbolo que abre los comentarios unlínea
    - multiline_open es el símbolo que abre los comentarios multilínea
    - multiline_close es el símbolo que cierra los comentarios multilínea

    Los tipos de línea posibles son:
    - Línea vacía
    - Comentario (unilínea o multilínea que abre y cierra)
    - Código (que puede ser seguido por comentario)
    - Abre multilínea (y no lo cierra)
    - Código y abre multilínea (y no lo cierra)
    - Cierra multilínea
    
    Se considera código todo el texto que no incluye delimitadores de
    comentarios (por ejemplo, el texto de un comentario multilínea). Para
    evitar casos especiales, también se consideran código las líneas que
    cierran un comentario multilínea y lo vuelven a abrir (a fines prácticos,
    son lo mismo que texto de un comentario multilínea).

    Devuelve uno de los siguientes strings:
    - "vacía"
    - "comentario"
    - "código"
    - "abre multilínea"
    - "código y abre multilínea"
    - "cierra multilínea"
    """
    if linea.isspace() or len(linea)==0:
        return "vacía"

    elif linea.startswith(singleline):
        return "comentario"

    elif linea.startswith(multiline_open):
        if multiline_close in linea:
            return "comentario"
        else:
            return "abre multilinea"

    elif multiline_open in linea:
        if multiline_close in linea:
            return "código"
        else:
            return "código y abre multilínea"

    elif multiline_close in linea:
        return "cierra multilínea"

    else:
        return "código"

def cuantas_lineas_en_str(text, singleline, multiline_open, multiline_close):
    """
    Cuenta las líneas de código en un string, ignorando comentarios y líneas
    vacías.

    Argumentos:
    - text es un string con el contenido de un archivo de source code.
    - singleline es el símbolo que abre los comentarios unlínea
    - multiline_open es el símbolo que abre los comentarios multilínea
    - multiline_close es el símbolo que cierra los comentarios multilínea
    
    Devuelve el número de líneas de código.
    """
    lineas = 0
    multiline_abierto = False
    
    for linea in text.split('\n'):        
        #Ignorar leading whitespace:
        linea = linea.lstrip()

        tipo = tipo_de_linea(linea, singleline, multiline_open, multiline_close)
        
        if tipo == "cierra multilínea":
            multiline_abierto = False

        elif tipo == "código" and not multiline_abierto:
            lineas += 1

        elif  tipo == "código y abre multilínea":
            lineas += 1
            multiline_abierto = True

        elif tipo == "abre multilinea":
            multiline_abierto = True

    return lineas

def cuantas_lineas_en_archivo(nombre):
    """
    Cuenta las líneas de código en un archivo, ignorando comentarios y líneas
    vacías.

    Nombre es el nombre de archivo. Se eleva un error si no tiene una de las
    extensiones reconocidas.
    
    Devuelve el número de líneas de código.
    """
    singlelines =      {"c":"//", "cpp":"//", "py":"#",   "jl":"#" }
    multiline_opens =  {"c":"/*", "cpp":"/*", "py":'"""', "jl":"#="}
    multiline_closes = {"c":"*/", "cpp":"*/", "py":'"""', "jl":"=#"}

    extension = nombre.split(".")[-1].lower()

    if extension not in ["c", "cpp", "py", "jl"]:
        raise TypeError(f"La extensión {extension} no está soportada (as in {nombre}).")

    singleline = singlelines[est]
    