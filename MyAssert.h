
#ifndef MyAssert_included
#define MyAssert_included

#ifndef MyAssert_name
#define MyAssert_name ""
#endif

#include <stdio.h>
#include <stdlib.h>

/*
   Si no se cumple la condición, imprime el mensaje y termina el programa.

   El mensaje se prefija con "ERROR:". Si se define el macro MyAssert_name,
   el prefijo se vuelve "ERROR : " MyAssert_name ": ".

   MyAssert agrega el nombre de la función al prefijo; MyAssert_nn (no name)
   no lo hace.
*/
#define MyAssert(cond, mensaje, ...)    if(!(cond)) {          \
   printf("\nERROR: " MyAssert_name ": %s: ", __func__);       \
   printf(mensaje"\n" __VA_OPT__(,) __VA_ARGS__); exit(1);}

#define MyAssert_nn(cond, mensaje, ...)  if(!(cond)) {         \
   printf("\nERROR: " MyAssert_name ": ");                     \
   printf(mensaje"\n" __VA_OPT__(,) __VA_ARGS__); exit(1);}

#endif //MyAssert_included