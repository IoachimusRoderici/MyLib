MyTime.h
========

Esta es una librería para facilitar la medición de tiempos.

Ojo que esto incluye los siguientes headers:
- `<time.h>`

`time.h`
--------

Para medir tiempo el sistema usa la estructura

```c
struct timespec{
  time_t tv_sec;    //Número (entero) de segundos
  long int tv_nsec; //Número de nanosegundos adicionales (1 ns = 1e-9 s). Está entre 0 y 1e9.
}
```

Hay un par de relojes definidos. CLOCK_REALTIME mide el tiempo desde 00:00:00 del 1º de 
enero de 1970 Coordinated Universal Time. Más comunmente usamos CLOCK_MONOTONIC, que no
tiene un punto de inicio definido.

La resolución del reloj se puede obtener con

```c
int clock_getres (CLOCK_MONOTONIC, struct timespec *res);
```

Y en este sistema me dió 1 ns.

El tiempo actual se obtiene con

```c
int clock_gettime (CLOCK_MONOTONIC, struct timespec *ts);
```

que pone el tiempo en ts y devuelve 0 si está todo bien.

Funciones
---------

En esta librería definimos nuestro propio relojito. Al principio del programa o cuando
quieras lo ponés en cero con

```c
void iniciar_el_reloj();
```

y después lo lees con

```c
double leer_el_reloj();
```

que devuelve el número de segundos desde que se inició el reloj.

También tenemos una función que recibe una timespec y devuelve el número de segundos:

```c
double timespec_a_segundos(struct timespec *coso);
```

Hay un par de funciones más, así que revisá el header antes de usarlo.




