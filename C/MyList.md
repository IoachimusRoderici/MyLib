MyLists
=======

Esta librería define objetos y funciones para trabajar con listas.
Por el momento, sólo tenemos *singly linked lists*.

No uses listas, usá arrays; esto fue sólo por diversión.

Ojo que esto incluye `"MyStealPointer.h"`.


Tipos
-----

Tenemos cuatro tipos de listas:

-  Listas de ints

   Cada nodo tiene un `int`.

-  Listas de doubles

   Cada nodo tiene un `double`.

-  Listas de pointers

   Cada nodo tiene un `void *`.
   
-  Listas de pointers plus

   Cada nodo tiene un `void *` y un char que sirve de código.


Para cada tipo de lista se definen dos objetos: una *head* y un nodo. La cabeza es
una estructura que contiene la longitud de la lista, un pointer al primer nodo, un
pointer al último nodo, y un pointer al nodo actual (usado para iterar). Los nodos
son estructuras que contienen sus valores y un pointer al siguiente nodo.

Las definiciones son las siguientes:

```c
typedef struct list_node_int_ {
   struct list_node_int_ *next;
   int val;
} list_node_int;

typedef struct list_node_double_ {
   struct list_node_double_ *next;
   double val;
} list_node_double;

typedef struct list_node_ptr_ {
   struct list_node_ptr_ *next;
   void *val;
} list_node_ptr;

typedef struct list_node_ptr_plus_ {
   struct list_node_ptr_plus_ *next;
   void *val;
   char code;
} list_node_ptr_plus;

typedef struct {
   size_t len;
   list_node_int* first;
   list_node_int* last;
   list_node_int* current;
} list_int;

typedef struct {
   size_t len;
   list_node_double* first;
   list_node_double* last;
   list_node_double* current;
} list_double;

typedef struct {
   size_t len;
   list_node_ptr* first;
   list_node_ptr* last;
   list_node_ptr* current;
} list_ptr;

typedef struct {
   size_t len;
   list_node_ptr_plus* first;
   list_node_ptr_plus* last;
   list_node_ptr_plus* current;
} list_ptr_plus;
```

Uso
---

Las definiciones de los nodos se proveen por si acaso, pero sólo devería ser 
necesario usar las cabezas.

Para trabajar con una lista se usa un pointer a una cabeza, que se aloca e
inicializa con la función que corresponda:

```c
list_int      *list1 = list_init_int ();
list_double   *list2 = list_init_double ();
list_ptr      *list3 = list_init_ptr ();
list_ptr_plus *list4 = list_init_ptr_plus ();
```
Las cabezas se iniciaizan como listas vacías: tienen `len=0` y `first=last=NULL`.


Luego es preferible usar las funciones definidas por la librería en vez de
ensuciarse las manos.

Funciones Disponibles
---------------------

Para facilitar el uso, se definen macros genéricos que redirigen a la
función del tipo que corresponda.

### Memoria

```c
list_int      *list_init_int      ();
list_double   *list_init_double   ();
list_ptr      *list_init_ptr      ();
list_ptr_plus *list_init_ptr_plus ();
```
Devuelve una lista vacía.

```c
void list_free (list_ *list);
```
Libera toda la memoria ocupada por la lista. Si la lista es de tipo pointer o
pointer plus, no se libera la memoria que pueda estar asignada a cada item.
Este macro usa `steal_pointer`, osea que la variable que se pasa como argumento 
queda seteada en `NULL`.

```c
void list_free_deep (list_ptr *list,      void free_func(void*));
void list_free_deep (list_ptr_plus *list, void free_func(void*, char));
```
Libera toda la memoria ocupada por la lista, llamando primero a free_func con
el pointer de cada elemento.
Este macro usa `steal_pointer`, osea que la variable que se pasa como argumento 
queda seteada en `NULL`.


### Agregar Elementos

```c
void list_prepend (list_ *list, TYPE  val [, char code]);
```
Agrega val (y code, si corresponde) al principio de la lista.

```c
void list_append (list_ *list, TYPE  val [, char code]);
```
Agrega val (y code, si corresponde) al final de la lista.


### Buscar Elementos

```c
TYPE list_get_item (const list_ *list, size_t index [, char *code]);
```
Devuelve el i-esimo item de la lista. Si la lista es de tipo pointer plus, pone el
código en code.

```c
bool list_contains (const list_ *list, TYPE val);
```
Devuelve `true` si val está en la lista, y `false` si no.


### Print

```c
void list_print (const list_int    *list);
void list_print (const list_double *list);
```
Imprime la lista en la terminal. Separa los elementos con '\t' para facilitar la
alineación con otras cosas.


### Iterar

```c
void list_foreach (list_ *list, void f(TYPE [, char] ));
```
Llama a f sucesivamente pasando como argumento cada elemento de la lista, en orden.


```c
void list_iter_begin (list_ *list);
```
Prepara la lista para comenzar a iterar con `list_iter_next`.

```c
bool list_iter_next (list_ *list, size_t *i, TYPE *val [, char *code]);
```
Sólo se puede llamar después de haber llamado a `list_iter_begin`.
Si no se llegó al final de la lista pone el siguiente elemento en *val, su índice
en *i, su código en *code, y devuelve `true`. Cuando se llega al final de la lista
devuelve `false` y no hace nada.
La intención es que se use de la siguiente manera:

```c
size_t i;
TYPE item;
list_iter_begin(list);

while (list_iter_next(list, &i, &item)){
   /* hacer cosas acá */
}
```




