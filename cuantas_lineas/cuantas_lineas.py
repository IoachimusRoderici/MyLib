#!/usr/bin/python3

"""
Este programa cuenta las líneas en archivos de código fuente, separando código,
comentarios, y líneas vacías.

./cuantas_lineas.py archivos|directorio

Si el argumento es  un  directorio,  cuenta las  líneas de  código de todos los
archivos con extensión reconocida en  ese directorio y todos sus subdirectorios
que no sean ocultos (ie. sus nombres no empiezan con '.'), recursivamente.

Si  los argumentos  pasados son archivos,  cuenta las líneas  de  código en los
archivos dados.

Las extensiones reconocidas son:
- .c
- .cpp
- .h
- .hpp
- .py
- .jl

Se considera código  a  todo el texto que no esté dentro de un comentario.  Las
líneas que tienen  código seguido por un comentario  suman a ambos  contadores,
así que es  posible que la suma de líneas  de código y líneas de comentario sea
mayor al número  total de líneas.  Las líneas que abren o cierran un comentario
pero no le agregan contenido no suman a la cuenta de comentarios.

Este programa hace las siguientes suposiciones sobre los archivos:
- Son programas válidos sin errores de sintaxis. 
- Todos los comentarios multilínea que se abren también se cierran.
- No se cierran comentarios multilínea que no fueron abiertos.
- En python, los comentarios multilínea se escriben con " y los strings
  multilínea se escriben con '.
- No aparecen instancias de los símbolos que abren y cierran comentarios
  dentro de string literals.
"""

import sys, os
from tabulate import tabulate

#Delimitadores de comentarios en los lenguajes reconocidos:
simbolos_singleline = {"c":"//", "py":"#", "jl":"#" }
simbolos_singleline['cpp'] = simbolos_singleline['c']
simbolos_singleline['h']   = simbolos_singleline['c']
simbolos_singleline['hpp'] = simbolos_singleline['c']

simbolos_multiline_open  = {"c":"/*", "py":'"""', "jl":"#="}
simbolos_multiline_open['cpp'] = simbolos_multiline_open['c']
simbolos_multiline_open['h']   = simbolos_multiline_open['c']
simbolos_multiline_open['hpp'] = simbolos_multiline_open['c']

simbolos_multiline_close = {"c":"*/", "py":'"""', "jl":"=#"}
simbolos_multiline_close['cpp'] = simbolos_multiline_close['c']
simbolos_multiline_close['h']   = simbolos_multiline_close['c']
simbolos_multiline_close['hpp'] = simbolos_multiline_close['c']

#Extensiones de archivo reconocidas:
extensiones_conocidas = simbolos_singleline.keys()

def get_extension(nombre):
    if '.' in nombre:
        return nombre.split(".")[-1]
    else:
        return ''

def es_extension_reconocida(nombre):
    return get_extension(nombre) in extensiones_conocidas

def archivos_en_dir(dir):
    """
    Devuelve una lista de los archivos con extensiones reconocidas en el
    directorio dado.

    No se incluyen los archivos ocultos.
    """
    nombres = os.listdir(dir)
    reconocidos = []
    for nombre in nombres:
        if os.path.isfile(dir+'/'+nombre) and es_extension_reconocida(nombre) and not nombre.startswith('.'):
            reconocidos.append(nombre)
    reconocidos.sort()
    return reconocidos

def directorios_en_dir(dir):
    """
    Devuelve una lista de los subdirectorios del directorio dado.

    No se incluyen los directorios ocultos.
    """
    nombres = os.listdir(dir)
    subdirectorios = []
    for nombre in nombres:
        if os.path.isdir(dir+'/'+nombre) and not nombre.startswith('.'):
            subdirectorios.append(nombre)
    subdirectorios.sort()
    return subdirectorios

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
        elif linea.startswith(multiline_open) and multiline_open == multiline_close:
            #Este caso se cumple en python.
            #Si hay un comentario unilínea abierto, esto es parte de su contenido:
            if unilinea_abierto:
                tiene_comentario = True
            #Si no, si estaba abierto se cierra y si estaba cerrado se abre:
            else:
                multilinea_abierto = not multilinea_abierto
            #Avanzar:
            linea = linea[len(multiline_open) : ]
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
    Cuenta las líneas de código, de comentarios, y vacías en un archivo.

    Nombre es el nombre de archivo relativo al cwd. Se eleva una excepción si
    no tiene una de las extensiones reconocidas.
    
    Devuelve una tupla con el número de líneas de código, el número de líneas
    de comentarios, el número de líneas vacías, y el número de líneas total.
    """

    #Chequear la extensión del archivo:
    extension = get_extension(nombre)
    if not es_extension_reconocida(nombre):
        raise Exception(f"La extensión '{extension}' no es reconocida. (as in '{nombre}')")

    #Seleccionar los delimitadores que corresponda:
    singleline      = simbolos_singleline     [extension]
    multiline_open  = simbolos_multiline_open [extension]
    multiline_close = simbolos_multiline_close[extension]

    #Abrir el archivo:
    archivo = open(nombre, 'r')

    #Itear por todas las líneas contando código, comentarios, y vacías:
    codigo = 0
    comentarios = 0
    vacias = 0
    total = 0
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
        total += 1
        if tiene_codigo:
            codigo += 1
        if tiene_comentario:
            comentarios += 1
        if not tiene_codigo and not tiene_comentario:
            vacias += 1
    
    #Chequear si quedó un multilínea sin cerrar:
    if multilinea_abierto:
        raise Exception(f"El archivo '{nombre}' terminó con un comentario multilínea sin cerrar.")

    return codigo, comentarios, vacias, total

def armar_fila(nombre, codigo, comentarios, vacias, total):
    """
    Devuelve una fila de la tabla para el archivo con los datos dados.
    """
    if total != 0:
        porcentaje = 100*codigo/total
    else:
        porcentaje = '-'
    return [nombre, codigo, comentarios, vacias, total, porcentaje]

def armar_tabla(archivos, dir='.'):
    """
    Devuelve una tabla con las cantidades de líneas de código y de comentarios
    de los archivos indicados.

    archivos es una lista de nombres de archivo. Todos tienen que tener
    extensiones soportadas. dir es el directorio donde están los archivos.

    Las columnas de la tabla son:
    - Nombre del archivo
    - Cantidad de líneas de código
    - Cantidad de líneas de comentarios
    - Cantidad de líneas vacías
    - Porcentaje de líneas de código
    """
    tabla = []

    #Agregar una fila para cada archivo:
    for nombre in archivos:
        codigo, comentarios, vacias, total = cuantas_lineas_en_archivo(dir+'/'+nombre)
        fila = armar_fila(nombre, codigo, comentarios, vacias, total)
        tabla.append(fila)
    
    return tabla

def agregar_total(tabla):
    """
    Agrega una última fila a la tabla con los valores totales.

    Si la tabla tiene menos de dos filas no hace nada.
    """
    if len(tabla) > 1:
        total_codigo = sum([fila[1] for fila in tabla])
        total_coment = sum([fila[2] for fila in tabla])
        total_vacias = sum([fila[3] for fila in tabla])
        total_totals = sum([fila[4] for fila in tabla])
        tabla.append(armar_fila('TOTAL', total_codigo, total_coment, total_vacias, total_totals))

def mostrar_tabla(tabla):
    """
    Muestra la tabla con las cantidades de líneas de código y comentarios.

    tabla tiene que ser como la generada por armar_tabla.

    Si hay más de una fila en tabla, se agrega ontra fila con el total.
    """
    headers = ["Archivo", "Código", "Comentarios", "Vacías", "Total", "% de código"]
    agregar_total(tabla)
    print(tabulate(tabla, headers=headers, floatfmt=".1f", tablefmt='fancy_outline'), end='\n\n')

def recuento_recursivo(directorio):
    """
    Recorre todos los subdirectorios no ocultos del directorio dado, mostrando
    la tabla con las cuentas de los archivos reconocidos que haya en cada uno.

    Se muestran primero las tablas de los directorios más profundos, y por
    último la tabla del directorio dado.

    Los archivos con extensiones no reconocidas se ignoran, al igual que los
    subdirectorios que no tengan archivos con extensiones reconocidas.

    La tabla de cada directorio tiene filas con los totales de sus
    subdirectorios.

    Devuelve una tupla con el total de líneas de código, de comentarios,
    vacías, y totales del directorio dado.
    """
    tabla = []

    #Primero recorrer los sub-directorios:
    subdirs = directorios_en_dir(directorio)
    for dir in subdirs:
        codigo, comentarios, vacias, total = recuento_recursivo(directorio+'/'+dir)
        #Ignorar directorios vacíos:
        if total != 0:
            tabla.append(armar_fila(dir+'/', codigo, comentarios, vacias, total))

    #Agregar los archivos sueltos de este directorio:
    tabla += armar_tabla(archivos_en_dir(directorio), directorio)

    #Si había contenido, mostarlo:
    if len(tabla) > 0:
        print(f"En el directorio '{directorio}':")
        mostrar_tabla(tabla) #Esto agrega el total en la última fila.

        #Devolver el total de este directorio:
        return tabla[-1][1], tabla[-1][2], tabla[-1][3], tabla[-1][4]

    else:
        return 0, 0, 0, 0

def directorio_o_archivos():
    """
    Determina si los argumentos recibidos son archivos o un directorio.

    Si hay mezcla de archivos y directorios eleva una excepción.
    Si es sólo un directorio devuelve "directorio".
    Si son archivos devuelve "archivos".
    """
    if len(sys.argv) == 2 and os.path.isdir(sys.argv[1]):
        return "directorio"
    else:
        for nombre in sys.argv[1:]:
            if not os.path.isfile(nombre):
                raise Exception(f"El archivo '{nomobre}' no existe o es un directorio.\nLos argumentos tienen que ser archivos o un sólo directorio.")
        return "archivos"



if __name__ == "__main__":
    #Ver si necesita ayuda:
    if len(sys.argv) == 1 or "--help" in sys.argv or "-h" in sys.argv:
        print(__doc__)
        quit()

    #Ver si tenemos que procesar archivos o un directorio:
    if directorio_o_archivos() == "archivos":
        tabla = armar_tabla(sys.argv[1:])
        mostrar_tabla(tabla)
    else:
        recuento_recursivo(sys.argv[1])