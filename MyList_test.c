#include "MyList.h"
#include <stdio.h>

void test_int();
void test_double();
void test_ptr();
void test_ptr_plus();

int main (){

   puts("Testing int: \n");
   test_int ();

   puts("\n\nTesting double: \n");
   test_double ();

   puts("\n\nTesting pointer: \n");
   test_ptr ();

   puts("\n\nTesting pointer plus: \n");
   test_ptr_plus ();

   return 0;
}

void test_int (){
   list_int *list = list_init_int();

   printf("%zu - ", list->len);
   list_print(list);

   list_append(list, 0);
   list_prepend(list, 1);
   list_append(list, 2);
   list_prepend(list, 3);
   list_append(list, 4);

   for (size_t i = 0; i<list->len; i++){
      printf ("%zu - %d \n", i, list_get_item(list, i));
   }
   printf("len = %zu \n", list->len);

   void f(int x){
      printf("f(%d) \n", x);
   }

   list_foreach(list, f);

   printf("3 is %sin the list.\n", list_contains(list, 3)? "":"not ");
   printf("7 is %sin the list.\n", list_contains(list, 7)? "":"not ");

   list_free(list);
}

void test_double (){
   list_double *list = list_init_double();

   printf("%zu - ", list->len);
   list_print(list);

   list_append(list, 0);
   list_prepend(list, 1);
   list_append(list, 2);
   list_prepend(list, 3);
   list_append(list, 4);

   for (size_t i = 0; i<list->len; i++){
      printf ("%zu - %.1f \n", i, list_get_item(list, i));
   }
   printf("len = %zu \n", list->len);

   void f(double x){
      printf("f(%.1f) \n", x);
   }

   list_foreach(list, f);

   printf("3 is %sin the list.\n", list_contains(list, 3)? "":"not ");
   printf("7 is %sin the list.\n", list_contains(list, 7)? "":"not ");

   list_free(list);
}

void test_ptr (){
   list_ptr *list = list_init_ptr();

   char x[] = "hola";

   list_append (list, (void *)"primer elemento");
   list_prepend (list, (void *)"segundo");
   list_append (list, (void *)"tercero");
   list_prepend (list, (void *)"último");

   printf("len=%zu l[2]=\"%s\" \n", list->len, (char *)list_get_item(list, 2));

   list_foreach(list, (void (*)(void *))puts);

   printf("NULL is %sin the list.\n", list_contains(list, NULL)? "":"not ");
   list_append(list, NULL);
   printf("NULL is %sin the list.\n", list_contains(list, NULL)? "":"not ");

   printf("\"hola\" is %sin the list.\n", list_contains(list, x)? "":"not ");
   list_prepend(list, x);
   printf("\"hola\" is %sin the list.\n", list_contains(list, x)? "":"not ");

   list_free(list);
}

void test_ptr_plus (){
   list_ptr_plus *list = list_init_ptr_plus();

   char x[] = "hola";
   char _;

   list_append (list, (void *)"primer elemento", 0);
   list_prepend (list, (void *)"segundo", 1);
   list_append (list, (void *)"tercero", 2);
   list_prepend (list, (void *)"último", 3);

   printf("len=%zu l[2]=\"%s\" \n", list->len, (char *)list_get_item(list, 2, &_));

   void f(void *ptr, char code){
      printf("f( \"%s\", %d) \n", (char*)ptr, code);
   }
   
   list_foreach(list, f);

   printf("NULL is %sin the list.\n", list_contains(list, NULL)? "":"not ");
   list_append(list, NULL, 0);
   printf("NULL is %sin the list.\n", list_contains(list, NULL)? "":"not ");

   printf("\"hola\" is %sin the list.\n", list_contains(list, x)? "":"not ");
   list_prepend(list, x, 1);
   printf("\"hola\" is %sin the list.\n", list_contains(list, x)? "":"not ");

   list_free(list);
}