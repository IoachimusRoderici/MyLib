# Cuantas Líneas?

Este programa cuenta las líneas en archivos de código fuente, separando código,
comentarios, y líneas vacías.

```
./cuantas_lineas.py archivos|directorio
```

Si el argumento es un directorio, cuenta las líneas de código de todos los
archivos con extensión reconocida en ese directorio y todos sus subdirectorios
que no sean ocultos (ie. sus nombres no empiezan con '.'), recursivamente.

Si los argumentos pasados son archivos, cuenta las líneas de código en los
archivos dados.

Las extensiones reconocidas son:
- `.c`
- `.cpp`
- `.h`
- `.hpp`
- `.py`
- `.jl`

Se considera código a todo el texto que no esté dentro de un comentario. Las
líneas que tienen código seguido por un comentario suman a ambos contadores,
así que es posible que la suma de líneas de código y líneas de comentario sea
mayor al número total de líneas. Las líneas que abren o cierran un comentario
pero no le agregan contenido no suman a la cuenta de comentarios.

Este programa hace las siguientes suposiciones sobre los archivos:
- Todos los comentarios multilínea que se abren también se cierran.
- No se cierran comentarios multilínea que no fueron abiertos.
- En python, los comentarios multilínea se escriben con " y los strings
  multilínea se escriben con '.
- No aparecen instancias de los símbolos que abren y cierran comentarios
  dentro de string literals.

# Ejemplo

Pasando como argumento este mismo directorio:

```
$ ./cuantas_lineas.py ./
En el directorio './':
╒════════════════════════════╤══════════╤═══════════════╤══════════╤═════════╤═══════════════╕
│ Archivo                    │   Código │   Comentarios │   Vacías │   Total │   % de código │
╞════════════════════════════╪══════════╪═══════════════╪══════════╪═════════╪═══════════════╡
│ cuantas_lineas.py          │      160 │           133 │       87 │     373 │          42.9 │
│ test_contenido_de_linea.py │       23 │             7 │        6 │      36 │          63.9 │
│ TOTAL                      │      183 │           140 │       93 │     409 │          44.7 │
╘════════════════════════════╧══════════╧═══════════════╧══════════╧═════════╧═══════════════╛
```