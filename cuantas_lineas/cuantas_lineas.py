#!/usr/bin/python3

"""
Este programa cuenta las líneas de archivos de código, separando código y
comentarios.

./cuantas_lineas.py archivo|directorio

Si el argumento pasado es un archivo, cuenta las líneas en ese archivo.

Si el argumento es un directorio, cuenta las líneas de código de todos los
archivos con extensión reconocida en ese directorio y todos sus subdirectorios
que no sean ocultos (ie. sus nombres no empiezan con '.'), recursivamente.

Las extensiones reconocidas son:
- .c
- .cpp
- .py
- .jl

Se considera código a todo el texto que no esté dentro de un comentario. Las
líneas que tienen código seguido por un comentario suman a ambos contadores,
así que es posible que la suma de líneas de código y líneas de comentario sea
mayor al número total de líneas. Las líneas vacías (o llenas de whitespace) son
ignoradas. Las líneas que abren un comentario sin contenido no suman a la
cuenta de comentarios.

Este programa hace las siguientes suposiciones sobre los archivos:
- Son programas válidos sin errores de sintaxis. 
- Todos los comentarios multilínea que se abren también se cierran.
- No se cierran comentarios multilínea que no fueron abiertos.
- En python, los comentarios multilínea se escriben con " y los strings
  multilínea se escriben con '.
"""

def contenido_de_linea(linea, multilinea_abierto, singleline, multiline_open, multiline_close):
    """
    Determina qué contenidos tiene una línea en cuanto a código y comentarios.

    Parmámetros:
    - línea es la línea a analizar.
    - multilinea_abierto indica si hay un comentario abierto de líneas anteriores.
    - singleline es el símbolo que abre los comentarios unlínea
    - multiline_open es el símbolo que abre los comentarios multilínea
    - multiline_close es el símbolo que cierra los comentarios multilínea

    Los contenidos de una línea pueden ser:
    - Código
    - Comentario (con contenido)
    - Dejar un multilínea abierto
    - Cerrar un multilínea abierto en líneas anteriores

    Devuelve una tupla con tres valores booleanos:
    - tiene código
    - tiene comentario
    - deja multilínea abierto

    Eleva una excepción si se cierra un multilínea que no fué abierto.
    """
    tiene_codigo       = False #Si hay código en esta línea
    tiene_comentario   = False #Si hay comentario con contenido en esta línea
    unilinea_abierto   = False #Si esta línea abre un unilínea

    #Eliminar leading whietespace:
    linea = linea.lstrip()

    #Escanear la línea de izquierda a derecha en busca de comentarios y código:
    while linea != "":
        #Ver si abre o cierra un comentario:
        if linea.startswith(singleline):
            #Si hay un comentario abierto, esto es parte de su contenido:
            if multilinea_abierto or unilinea_abierto:
                tiene_comentario = True
            #Si no, abre un comentario nuevo:
            else:
                unilinea_abierto = True
            #Avanzar:
            linea = linea[len(singleline) : ]
        elif linea.startswith(multiline_open):
            #Si hay un comentario abierto, esto es parte de su contenido:
            if multilinea_abierto or unilinea_abierto:
                tiene_comentario = True
            #Si no, abre un comentario nuevo:
            else:
                multilinea_abierto = True
            #Avanzar:
            linea = linea[len(multiline_open) : ]
        elif linea.startswith(multiline_close):
            #Si estamos en un multilínea, se cierra:
            if multilinea_abierto:
                multilinea_abierto = False
            #Si estamos en un unilínea, esto es contenido:
            elif unilinea_abierto:
                tiene_comentario = True
            #Si no estamos en un comentario, esto es un error:
            else:
                raise Exception("Se cierra un multilínea que nunca fue abierto.")
            #Avanzar:
            linea = linea[len(multiline_close) : ]
        #Si no empieza con comentario, esto es código o contenido:
        else:
            if unilinea_abierto or multilinea_abierto:
                tiene_comentario = True
            else:
                tiene_codigo = True
            #Avanzar un caracter:
            linea = linea[1:]
        
        #Eliminar leading whietespace:
        linea = linea.lstrip()
    
    return tiene_codigo, tiene_comentario, multilinea_abierto

def cuantas_lineas_en_archivo(nombre):
    """
    Cuenta las líneas de código y comentarios en un archivo.

    Nombre es el nombre de archivo. Se eleva una excepción si no tiene una de
    las extensiones reconocidas.
    
    Devuelve una tupla con el número de líneas de código y el número de líneas
    de comentarios.
    """
    #Delimitadores de comentarios en los lenguajes reconocidos:
    singlelines =      {"c":"//", "cpp":"//", "py":"#",   "jl":"#" }
    multiline_opens =  {"c":"/*", "cpp":"/*", "py":'"""', "jl":"#="}
    multiline_closes = {"c":"*/", "cpp":"*/", "py":'"""', "jl":"=#"}

    #Extensiones de archivo reconocidas:
    extensiones_conocidas = singlelines.keys()

    #Chequear extensión del archivo:
    extension = nombre.split(".")[-1].lower()
    if extension not in extensiones_conocidas:
        raise Exception(f"La extensión '{extension}' no está reconocida. (as in '{nombre}')")
    else:
        #Seleccionar los delimitadores que corresponda:
        singleline = singlelines[extension]
        multiline_open = multiline_opens[extension]
        multiline_close = multiline_closes[extension]

    #Abrir el archivo:
    archivo = open(nombre, 'r')

    #Itear por todas las líneas contando código y comentarios:
    codigo = 0
    comentarios = 0
    multilinea_abierto = False

    for i, linea in enumerate(archivo):
        #Ver qué hay en esta línea:
        try:
            tiene_codigo, tiene_comentario, multilinea_abierto = \
                contenido_de_linea(linea, multilinea_abierto, singleline, multiline_open, multiline_close)
        except Exception as e:
            e.add_note(f"En el archivo '{nombre}', línea {i}:\n{linea}")
            raise

        #Contar:
        if tiene_codigo:
            codigo += 1
        if tiene_comentario:
            comentarios += 1
    
    #Chequear si quedó un multilínea sin cerrar:
    if multilinea_abierto:
        raise Exception(f"El archivo '{nombre}' terminó sin cerrar un comentario multilínea.")

    return codigo, comentarios
    