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

   list_append(list, 0);
   list_prepend(list, 1);
   list_append(list, 2);
   list_prepend(list, 3);
   list_append(list, 4);

   list_print(list);

   /* test for list_get_item
   for (size_t i = 0; i<list->len; i++){
      printf ("%zu - %d \n", i, list_get_item(list, i));
   }
   printf("len = %zu \n", list->len);*/

   /* test for list_foreach
   void f(int x){
      printf("f(%d) \n", x);
   }

   list_foreach(list, f);*/

   /* test for list_contains 
   printf("3 is %sin the list.\n", list_contains(list, 3)? "":"not ");
   printf("7 is %sin the list.\n", list_contains(list, 7)? "":"not ");*/

   /* test for list_iter */
   size_t i;
   int item;
   list_iter_begin(list);

   while (list_iter_next(list, &i, &item)){
      printf("i=%zd, item=%d \n", i, item);
   }


   list_free(list);
}

void test_double (){
   list_double *list = list_init_double();

   list_append(list, 0);
   list_prepend(list, 1);
   list_append(list, 2);
   list_prepend(list, 3);
   list_append(list, 4);

   list_print(list);

   /* test for list_get_item
   for (size_t i = 0; i<list->len; i++){
      printf ("%zu - %.1f \n", i, list_get_item(list, i));
   }
   printf("len = %zu \n", list->len);*/

   /* test for list_foreach
   void f(double x){
      printf("f(%.1f) \n", x);
   }

   list_foreach(list, f);*/

   /* test for list_contains
   printf("3 is %sin the list.\n", list_contains(list, 3)? "":"not ");
   printf("7 is %sin the list.\n", list_contains(list, 7)? "":"not ");*/

   /* test for list_iter */
   size_t i;
   double item;
   list_iter_begin(list);

   while (list_iter_next(list, &i, &item)){
      printf("i=%zd, item=%.1lf \n", i, item);
   }

   list_free(list);
}

void test_ptr (){
   list_ptr *list = list_init_ptr();

   list_append (list, (void *)"primer elemento");
   list_prepend (list, (void *)"segundo");
   list_append (list, (void *)"tercero");
   list_prepend (list, (void *)"último");

   /* test for list_get_item
   printf("len=%zu l[2]=\"%s\" \n", list->len, (char *)list_get_item(list, 2));*/

   /* test for list_foreach
   list_foreach(list, (void (*)(void *))puts);*/

   /* test for list_contains
   printf("NULL is %sin the list.\n", list_contains(list, NULL)? "":"not ");
   list_append(list, NULL);
   printf("NULL is %sin the list.\n", list_contains(list, NULL)? "":"not ");

   char x[] = "hola";
   printf("\"hola\" is %sin the list.\n", list_contains(list, x)? "":"not ");
   list_prepend(list, x);
   printf("\"hola\" is %sin the list.\n", list_contains(list, x)? "":"not "); */

   /* test for list_iter */
   size_t i;
   char *item;
   list_iter_begin(list);

   while (list_iter_next(list, &i, (void**)&item)){
      printf("i=%zd, item=%s \n", i, item);
   }

   list_free(list);
}

void test_ptr_plus (){
   list_ptr_plus *list = list_init_ptr_plus();

   list_append (list, (void *)"primer elemento", 'p');
   list_prepend (list, (void *)"segundo", 's');
   list_append (list, (void *)"tercero", 't');
   list_prepend (list, (void *)"último", 'u');

   /* test for list_get_item
   printf("len=%zu l[2]=\"%s\" \n", list->len, (char *)list_get_item(list, 2));*/

   /* test for list_foreach
   list_foreach(list, (void (*)(void *))puts);*/

   /* test for list_contains
   printf("NULL is %sin the list.\n", list_contains(list, NULL)? "":"not ");
   list_append(list, NULL);
   printf("NULL is %sin the list.\n", list_contains(list, NULL)? "":"not ");

   char x[] = "hola";
   printf("\"hola\" is %sin the list.\n", list_contains(list, x)? "":"not ");
   list_prepend(list, x);
   printf("\"hola\" is %sin the list.\n", list_contains(list, x)? "":"not "); */

   /* test for list_iter */
   size_t i;
   char *item;
   char c;
   list_iter_begin(list);

   while (list_iter_next(list, &i, (void**)&item, &c)){
      printf("i=%zd, item=%s, code=%c \n", i, item, c);
   }

   list_free(list);
}