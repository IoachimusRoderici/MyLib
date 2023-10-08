# Cuantas Líneas?

Este programa cuenta las líneas en archivos de código fuente, separando código,
comentarios, y líneas vacías.

```
./cuantas_lineas.py archivos|directorio
```

Si el argumento es  un  directorio,  cuenta las  líneas de  código de todos los
archivos con extensión reconocida en  ese directorio y todos sus subdirectorios
que no sean ocultos (ie. sus nombres no empiezan con '.'), recursivamente.

Si  los argumentos  pasados son archivos,  cuenta las líneas  de  código en los
archivos dados.

Las extensiones reconocidas son:
- `.c`
- `.cpp`
- `.h`
- `.hpp`
- `.py`
- `.jl`

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