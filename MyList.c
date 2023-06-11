#include "MyList.h"

#define MyAssert_name "MyList"
#include "MyAssert.h"

/* Funciones Privadas */

static list_node_int *new_node_int(int val, list_node_int *next){
   /* Aloca un nodo nuevo, e inicializa sus miembros. */

   list_node_int *node = malloc (sizeof(*node));
   MyAssert_nn (node != NULL, "No se pudo alocar un nodo para una lista de int.");

   node->val = val;
   node->next = next;

   return node;
}
static list_node_double *new_node_double(double val, list_node_double *next){
   /* Aloca un nodo nuevo, e inicializa sus miembros. */

   list_node_double *node = malloc (sizeof(*node));
   MyAssert_nn (node != NULL, "No se pudo alocar un nodo para una lista de double.");

   node->val = val;
   node->next = next;

   return node;
}
static list_node_ptr *new_node_ptr(void *val, list_node_ptr *next){
   /* Aloca un nodo nuevo, e inicializa sus miembros. */

   list_node_ptr *node = malloc (sizeof(*node));
   MyAssert_nn (node != NULL, "No se pudo alocar un nodo para una lista de pointer.");

   node->val = val;
   node->next = next;

   return node;
}
static list_node_ptr_plus *new_node_ptr_plus(void *val, char code, list_node_ptr_plus *next){
   /* Aloca un nodo nuevo, e inicializa sus miembros. */

   list_node_ptr_plus *node = malloc (sizeof(*node));
   MyAssert_nn (node != NULL, "No se pudo alocar un nodo para una lista de pointer plus.");

   node->val = val;
   node->code = code;
   node->next = next;

   return node;
}


/* Init */

list_int *list_init_int (){
   list_int * list = malloc (sizeof(* list));
   MyAssert ( list != NULL, "No se pudo alocar la cabeza.");

    list->len = 0;
    list->first = NULL;
    list->last = NULL;

   return  list;
}

list_double *list_init_double (){
   list_double * list = malloc (sizeof(* list));
   MyAssert ( list != NULL, "No se pudo alocar la cabeza.");

    list->len = 0;
    list->first = NULL;
    list->last = NULL;

   return  list;
}

list_ptr *list_init_ptr (){
   list_ptr * list = malloc (sizeof(* list));
   MyAssert ( list != NULL, "No se pudo alocar la cabeza.");

    list->len = 0;
    list->first = NULL;
    list->last = NULL;

   return  list;
}

list_ptr_plus *list_init_ptr_plus (){
   list_ptr_plus * list = malloc (sizeof(* list));
   MyAssert ( list != NULL, "No se pudo alocar la cabeza.");

    list->len = 0;
    list->first = NULL;
    list->last = NULL;

   return  list;
}


/* Free */

void list_free_int (list_int *list){

   //si la lista no está vacía, liberamos los nodos
   if (list->len != 0){
      list_node_int *node, *next;

      node = list->first;

      while (node != NULL){
         next = node->next;
         
         free (node);
         node = next;
      }
   }

   //y después liberamos la lista
   free (list);
}

void list_free_double (list_double *list){

   //si la lista no está vacía, liberamos los nodos
   if (list->len != 0){
      list_node_double *node, *next;

      node = list->first;

      while (node != NULL){
         next = node->next;
         
         free (node);
         node = next;
      }
   }

   //y después liberamos la lista
   free (list);
}

void list_free_ptr (list_ptr *list){

   //si la lista no está vacía, liberamos los nodos
   if (list->len != 0){
      list_node_ptr *node, *next;

      node = list->first;

      while (node != NULL){
         next = node->next;
         
         free (node);
         node = next;
      }
   }

   //y después liberamos la lista
   free (list);
}

void list_free_ptr_plus (list_ptr_plus *list){

   //si la lista no está vacía, liberamos los nodos
   if (list->len != 0){
      list_node_ptr_plus *node, *next;

      node = list->first;

      while (node != NULL){
         next = node->next;
         
         free (node);
         node = next;
      }
   }

   //y después liberamos la lista
   free (list);
}

void list_free_deep_ptr (list_ptr *list, void free_func(void*)){

   list_foreach (list, free_func);
   list_free (list);
}

void list_free_deep_ptr_plus (list_ptr_plus *list, void free_func(void*, char)){

   list_foreach (list, free_func);
   list_free (list);
}


/* Prepend */

void list_prepend_int (list_int *list, int val){
   list_node_int *node = new_node_int(val,  list->first);

   list->first = node;

   if ( list->len == 0)
      list->last = node;

   list->len++;
}

void list_prepend_double (list_double *list, double val){
   list_node_double *node = new_node_double(val,  list->first);

   list->first = node;

   if ( list->len == 0)
      list->last = node;

   list->len++;
}

void list_prepend_ptr (list_ptr *list, void *val){
   list_node_ptr *node = new_node_ptr (val,  list->first);

   list->first = node;

   if ( list->len == 0)
      list->last = node;

   list->len++;
}

void list_prepend_ptr_plus (list_ptr_plus *list, void *val, char code){
   list_node_ptr_plus *node = new_node_ptr_plus (val, code, list->first);

   list->first = node;

   if ( list->len == 0)
      list->last = node;

   list->len++;
}


/* Append */

void list_append_int (list_int *list, int val){
   list_node_int *node = new_node_int(val, NULL);

   if ( list->len == 0)
       list->first = node;
   else
       list->last->next = node;

    list->last = node;
    list->len++;
}

void list_append_double (list_double *list, double val){
   list_node_double *node = new_node_double(val, NULL);

   if ( list->len == 0)
       list->first = node;
   else
       list->last->next = node;

    list->last = node;
    list->len++;
}

void list_append_ptr (list_ptr *list, void *val){
   list_node_ptr *node = new_node_ptr (val, NULL);

   if ( list->len == 0)
       list->first = node;
   else
       list->last->next = node;

    list->last = node;
    list->len++;
}

void list_append_ptr_plus (list_ptr_plus *list, void *val, char code){
   list_node_ptr_plus *node = new_node_ptr_plus (val, code, NULL);

   if ( list->len == 0)
       list->first = node;
   else
       list->last->next = node;

    list->last = node;
    list->len++;
}


/* Get Item */

int list_get_item_int (const list_int *list, size_t index){

   MyAssert (index < list->len, "Index out of range (have %zu, but list->len is %zu).", index, list->len);

   list_node_int *node = list->first;
   for (size_t i = 0; i<index; i++){
      node = node->next;
   }

   return node->val;
}

double list_get_item_double (const list_double *list, size_t index){

   MyAssert (index < list->len, "Index out of range (have %zu, but list->len is %zu).", index, list->len);

   list_node_double *node = list->first;
   for (size_t i = 0; i<index; i++){
      node = node->next;
   }

   return node->val;
}

void *list_get_item_ptr (const list_ptr *list, size_t index){

   MyAssert (index < list->len, "Index out of range (have %zu, but list->len is %zu).", index, list->len);

   list_node_ptr *node = list->first;
   for (size_t i = 0; i<index; i++){
      node = node->next;
   }

   return node->val;
}

void *list_get_item_ptr_plus (const list_ptr_plus *list, size_t index, char *code){

   MyAssert (index < list->len, "Index out of range (have %zu, but list->len is %zu).", index, list->len);

   list_node_ptr_plus *node = list->first;
   for (size_t i = 0; i<index; i++){
      node = node->next;
   }

   *code = node->code;
   return node->val;
}


/* Contains */

bool list_contains_int (const list_int *list, int val){
   list_node_int *node = list->first;

   while (node != NULL){
      if (node->val == val)
         return true;

      node = node->next;
   }

   //si salimos es porque no está en la lista
   return false;
}

bool list_contains_double (const list_double *list, double val){
   list_node_double *node = list->first;

   while (node != NULL){
      if (node->val == val)
         return true;

      node = node->next;
   }

   //si salimos es porque no está en la lista
   return false;
}

bool list_contains_ptr (const list_ptr *list, void *val){
   list_node_ptr *node = list->first;

   while (node != NULL){
      if (node->val == val)
         return true;

      node = node->next;
   }

   //si salimos es porque no está en la lista
   return false;
}

bool list_contains_ptr_plus (const list_ptr_plus *list, void *val){
   list_node_ptr_plus *node = list->first;

   while (node != NULL){
      if (node->val == val)
         return true;

      node = node->next;
   }

   //si salimos es porque no está en la lista
   return false;
}

/* For Each */

void list_foreach_int (list_int *list, void f(int)){
   list_node_int *node = list->first;

   while (node != NULL){
      f (node->val);

      node = node->next;
   }
}

void list_foreach_double (list_double *list, void f(double)){
   list_node_double *node = list->first;

   while (node != NULL){
      f (node->val);

      node = node->next;
   }
}

void list_foreach_ptr (list_ptr *list, void f(void *)){
   list_node_ptr *node = list->first;

   while (node != NULL){
      f (node->val);

      node = node->next;
   }
}

void list_foreach_ptr_plus (list_ptr_plus *list, void f(void *, char)){
   list_node_ptr_plus *node = list->first;

   while (node != NULL){
      f (node->val, node->code);

      node = node->next;
   }
}


/* Print */

void list_print_int (const list_int *list){
   list_node_int *node = list->first;

   while (node != NULL){
      printf ("\t%d", node->val);

      node = node->next;
   }

   putchar ('\n');
}

void list_print_double (const list_double *list){
   list_node_double *node = list->first;

   while (node != NULL){
      printf ("\t%.3lf", node->val);

      node = node->next;
   }

   putchar ('\n');
}
