#ifndef MyTime
#define MyTime

#include <time.h>

void iniciar_el_reloj ();               //pone el reloj en cero.
double leer_segundos  ();               //devuelve el número de segundos del reloj.
time_t leer_time_t    ();               //devuelve el número (entero) de segundos del reloj.

char *segundos_a_str (double segundos); //devuelve un string con el tiempo en formato xxh xxm x.xs.
char *time_t_a_str   (time_t segundos); //devuelve un string con el tiempo en formato xxh xxm xs.
char *reloj_a_str    ();                //devuelve un string con el tiempo actual en el primer formato.
                                        //los strings son variables estáticas, así que si vas a hacer
                                        //cosas raras mejor tirate un memcpy (son arrays de len=15).


double timespec_a_segundos (struct timespec *coso);

#endif //MyTime