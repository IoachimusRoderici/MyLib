#include <stdio.h>

#define mymacro(a, ...) printf(("%.3f" __VA_OPT__(,) __VA_ARGS__), a)

#define f(x) _Generic((x), char* : puts(x), const char* : puts("const"))

int main (){
   
   const char t[] = "hola.";

   f(t);

   return 0;
}