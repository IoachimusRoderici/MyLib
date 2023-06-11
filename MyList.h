#ifndef MyList
#define MyList

#include <stddef.h>
#include <stdbool.h>
#include "MyStealPointer.h"

/* Tipos  */

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
} list_int;

typedef struct {
   size_t len;
   list_node_double* first;
   list_node_double* last;
} list_double;

typedef struct {
   size_t len;
   list_node_ptr* first;
   list_node_ptr* last;
} list_ptr;

typedef struct {
   size_t len;
   list_node_ptr_plus* first;
   list_node_ptr_plus* last;
} list_ptr_plus;


/* Funciones de Memoria */

//devuelve una lista vacía
list_int      *list_init_int      ();
list_double   *list_init_double   ();
list_ptr      *list_init_ptr      ();
list_ptr_plus *list_init_ptr_plus ();

//libera la memoria ocupada por la lista
#define list_free(list)            _Generic((list),\
   list_int      * : list_free_int           ,\
   list_double   * : list_free_double        ,\
   list_ptr      * : list_free_ptr           ,\
   list_ptr_plus * : list_free_ptr_plus      )( steal_pointer(list) )
void list_free_int      (list_int      *list);
void list_free_double   (list_double   *list);
void list_free_ptr      (list_ptr      *list);
void list_free_ptr_plus (list_ptr_plus *list);

//libera la memoria ocupada por la lista, y también sus elementos
#define list_free_deep(list, free_func) _Generic((list),\
   list_ptr      * : list_free_deep_ptr                ,\
   list_ptr_plus * : list_free_deep_ptr_plus           )( steal_pointer(list), free_func)
void list_free_deep_ptr      (list_ptr      *list, void free_func(void*));
void list_free_deep_ptr_plus (list_ptr_plus *list, void free_func(void*, char));


/* Agregar Elementos */

//agrega un elemento al principio de la lista
#define list_prepend(list, ...)       _Generic((list),\
   list_int      * : list_prepend_int           ,\
   list_double   * : list_prepend_double        ,\
   list_ptr      * : list_prepend_ptr           ,\
   list_ptr_plus * : list_prepend_ptr_plus      )(list, __VA_ARGS__)
void list_prepend_int      (list_int      *list, int    val);
void list_prepend_double   (list_double   *list, double val);
void list_prepend_ptr      (list_ptr      *list, void  *val);
void list_prepend_ptr_plus (list_ptr_plus *list, void  *val, char code);

//agrega un elemento al final de la lista
#define list_append(list, ...)       _Generic((list),\
   list_int      * : list_append_int           ,\
   list_double   * : list_append_double        ,\
   list_ptr      * : list_append_ptr           ,\
   list_ptr_plus * : list_append_ptr_plus      )(list, __VA_ARGS__)
void list_append_int      (list_int      *list, int    val);
void list_append_double   (list_double   *list, double val);
void list_append_ptr      (list_ptr      *list, void  *val);
void list_append_ptr_plus (list_ptr_plus *list, void  *val, char code);


/* Buscar Elementos */

//devuelve un elemento de la lista
#define list_get_item(list, ...)       _Generic((list),\
   list_int      * : list_get_item_int                ,\
   list_double   * : list_get_item_double             ,\
   list_ptr      * : list_get_item_ptr                ,\
   list_ptr_plus * : list_get_item_ptr_plus           )(list, __VA_ARGS__)
int     list_get_item_int      (const list_int      *list, size_t index);
double  list_get_item_double   (const list_double   *list, size_t index);
void   *list_get_item_ptr      (const list_ptr      *list, size_t index);
void   *list_get_item_ptr_plus (const list_ptr_plus *list, size_t index, char *code);

//Devuelve true si val está en la lista, y false si no
#define list_contains(list, val)       _Generic((list),\
   list_int      * : list_contains_int                ,\
   list_double   * : list_contains_double             ,\
   list_ptr      * : list_contains_ptr                ,\
   list_ptr_plus * : list_contains_ptr_plus           )(list, val)
bool list_contains_int      (const list_int      *list, int    val);
bool list_contains_double   (const list_double   *list, double val);
bool list_contains_ptr      (const list_ptr      *list, void  *val);
bool list_contains_ptr_plus (const list_ptr_plus *list, void  *val);


/* Funciones Misceláneas */

//imprime la lista
#define list_print(list)      _Generic((list),\
   list_int      * : list_print_int     ,\
   list_double   * : list_print_double  )(list)
void list_print_int    (const list_int    *list);
void list_print_double (const list_double *list);

//evalúa f en cada elemento de la lista
#define list_foreach(list, f)       _Generic((list),\
   list_int      * : list_foreach_int              ,\
   list_double   * : list_foreach_double           ,\
   list_ptr      * : list_foreach_ptr              ,\
   list_ptr_plus * : list_foreach_ptr_plus         )(list, f)
void list_foreach_int      (list_int      *list, void f(int));
void list_foreach_double   (list_double   *list, void f(double));
void list_foreach_ptr      (list_ptr      *list, void f(void *));
void list_foreach_ptr_plus (list_ptr_plus *list, void f(void *, char));



#endif //MyList