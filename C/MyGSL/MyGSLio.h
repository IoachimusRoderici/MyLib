#ifndef MyGSLio
#define MyGSLio

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>

/* Writing */

#define mygsl_write_txt(arr, ...)    _Generic((arr),\
   const gsl_vector_int * : mygsl_write_vector_int ,\
         gsl_vector_int * : mygsl_write_vector_int ,\
   const gsl_vector     * : mygsl_write_vector_d   ,\
         gsl_vector     * : mygsl_write_vector_d   ,\
   const gsl_matrix_int * : mygsl_write_matrix_int ,\
         gsl_matrix_int * : mygsl_write_matrix_int ,\
   const gsl_matrix     * : mygsl_write_matrix_d   ,\
         gsl_matrix     * : mygsl_write_matrix_d   )(arr, __VA_ARGS__)
void mygsl_write_vector_int (const gsl_vector_int  *v, FILE *file);
void mygsl_write_vector_d   (const gsl_vector      *v, FILE *file, const char *format);
void mygsl_write_matrix_int (const gsl_matrix_int *m, FILE *file);
void mygsl_write_matrix_d   (const gsl_matrix     *m, FILE *file, const char *format);


/* Reading */

gsl_vector_int *mygsl_read_vector_int (const char *filename, gsl_vector_int *dest);
gsl_vector     *mygsl_read_vector_d   (const char *filename, gsl_vector     *dest);

gsl_matrix_int *mygsl_read_matrix_int (const char *filename, gsl_matrix_int *dest);
gsl_matrix     *mygsl_read_matrix_d   (const char *filename, gsl_matrix     *dest);


/* Printing */
#define mygsl_print(v, ...)                    _Generic((v),\
   const gsl_vector_int         * : mygsl_print_vector_int ,\
         gsl_vector_int         * : mygsl_print_vector_int ,\
   const gsl_vector             * : mygsl_print_vector_d   ,\
         gsl_vector             * : mygsl_print_vector_d   ,\
   const gsl_matrix_int         * : mygsl_print_matrix_int ,\
         gsl_matrix_int         * : mygsl_print_matrix_int ,\
   const gsl_matrix             * : mygsl_print_matrix_d   ,\
         gsl_matrix             * : mygsl_print_matrix_d   )(v, (0 __VA_OPT__(,) __VA_ARGS__))
void mygsl_print_vector_int (const gsl_vector_int *v, ssize_t n);
void mygsl_print_vector_d   (const gsl_vector     *v, ssize_t n);
void mygsl_print_matrix_int (const gsl_matrix_int *v, ssize_t n);
void mygsl_print_matrix_d   (const gsl_matrix     *v, ssize_t n);

#endif  //MyGSLio