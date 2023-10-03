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
"""

def es_singleline(linea, singleline):
    """Determina si una línea es un comentario singleline."""
    return linea.startswith(singleline)

def tipo_de_linea(linea, singleline, multiline_open, multiline_close):
    """
    Determina qué acciones contiene una línea en cuanto a código y comentarios.

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

def cuantas_lineas(text, singleline, multiline_open, multiline_close):
    """
    Cuenta las líneas de código en un string, ignorando comentarios y líneas
    vacías.

    Argumentos:
    - text es un string con el contenido de un archivo de source code.
    - singleline es un string con el símbolo usado para abrir comentarios de
      una sola línea.
    - multiline_open es un string con el símbolo usado para abrir comentarios
      de múltiples líneas.
    - multiline_clode es un string con el símbolo usado para cerrar comentarios
      de múltiples líneas.
    
    Devuelve el número de líneas de código.
    Eleva un error si un comentario multilínea no se cierra.
    """
    lineas = 0
    multiline_abierto = False
    
    for linea in text.split('\n'):
        #Ignorar líneas vacías:
        if linea.isspace() or linea.isempty():
            continue

        #Si estamos en un comentario multilínea, esperar a que cierre:
        if multiline_abierto:
            if multiline_close in linea:
                multiline_abierto = False
                #Si algún desquiciado escribió código después de un comentario
                #multilínea, conservarlo:
                if not linea.endswith(multiline_close):

            else:
                continue
        
        #Ignorar leading whitespace:
        linea = linea.lstrip()

        #Si no empieza con comentario, es código:
        empieza_con_comentario = linea.startswith(multiline_open) or linea.startswith(singleline)
        if not empieza_con_comentario:
            lineas += 1

        #Chequear si abre un comentario multilínea:
        if multiline_open in linea:
            multiline_abierto = True

        #Chequear si cierra un comentario multilínea:
        if multiline_abierto and multiline_close in linea:
            multiline_abierto = False        



