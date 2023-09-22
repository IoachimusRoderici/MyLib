#include "MyTime.h"
#include <stdio.h>

//el reloj global
static double secs_0;
static time_t time_t_0;
static struct timespec aux;

//las funciones

void iniciar_el_reloj (){
  clock_gettime (CLOCK_MONOTONIC, &aux);

  secs_0 = timespec_a_segundos(&aux);
  time_t_0 = aux.tv_sec;
}

double timespec_a_segundos (struct timespec *coso){
  return (double)coso->tv_sec + 1e-9*(double)coso->tv_nsec;
}

double leer_segundos (){
  clock_gettime (CLOCK_MONOTONIC, &aux);
  return timespec_a_segundos(&aux) - secs_0;
}

time_t leer_time_t (){
  clock_gettime (CLOCK_MONOTONIC, &aux);
  return aux.tv_sec - time_t_0;
}

const char *segundos_a_str (double segundos){
  static char stamp[15]; //a lo sumo, el texto es "xxxh xxm xx.xs": 14 chars.

  //si hay menos de un minuto:
  if (segundos<60){
    snprintf(stamp, sizeof(stamp), "%.1fs", segundos);
  }
  else{
    int mins = (int)(segundos/60);
    double secs = segundos-mins*60;

    //si hay menos de una hora
    if (segundos<3600){      
      snprintf(stamp, sizeof(stamp), "%dm %.0fs",mins, secs);
    }
    else{
      int horas = mins/60;
      mins = mins%60;
      snprintf(stamp, sizeof(stamp), "%dh %dm %.0fs",horas, mins, secs);
    }
  }

  return stamp;
}

const char *time_t_a_str (time_t segundos){
  static char stamp[15]; //a lo sumo, el texto es "xxxh xxm xxs": 12 chars.

  //si hay menos de un minuto:
  if (segundos<60){
    snprintf(stamp, sizeof(stamp), "%lds", segundos);
  }
  else{
    time_t mins = segundos/60;
    segundos = segundos%60;

    //si hay menos de una hora
    if (mins < 60){      
      snprintf(stamp, sizeof(stamp), "%ldm %lds",mins, segundos);
    }
    else{
      int horas = mins/60;
      mins = mins%60;
      snprintf(stamp, sizeof(stamp), "%dh %ldm %lds",horas, mins, segundos);
    }
  }

  return stamp;
}

const char *reloj_a_str(){
  return segundos_a_str(leer_segundos());
}