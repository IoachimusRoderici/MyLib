#include "MyGSLio.h"
#include <ctype.h>

void test_write_vector();
void test_write_matrix();
void test_read_vector();
void test_read_matrix();
void test_print_vector();
void test_print_matrix();

int main(){
   test_print_matrix();

   return 0;
}

void test_write_vector(){
   int n = 4;

   gsl_vector *v = gsl_vector_alloc(n);

   for (int i=0; i<n; i++){
      gsl_vector_set(v, i, i*1.5);
   }

   FILE *f = fopen("test.txt", "w");
   mygsl_write_txt(v, f, "%.3f");
   fclose(f);

   gsl_vector_free(v);
}

void test_write_matrix(){
   int rows = 4;
   int cols = 3;

   gsl_matrix *m = gsl_matrix_alloc(rows, cols);

   for (int i=0; i<rows; i++){
      for (int j=0; j<cols; j++){
         gsl_matrix_set(m, i, j, i+j);
      }
   }

   mygsl_write_txt(m, stdout, "%.1f");

   gsl_matrix_free (m);
}

void test_read_vector(){

   gsl_vector *vec = mygsl_read_vector_d("test_vector.txt", NULL);
   mygsl_write_txt(vec, stdout, "%.2f");
   gsl_vector_free(vec);

   vec = gsl_vector_alloc(5);
   mygsl_read_vector_d("test_vector.txt", vec);
   mygsl_write_txt(vec, stdout, "%.2f");
   gsl_vector_free(vec);
}

void test_read_matrix(){

   gsl_matrix *m = mygsl_read_matrix_d("m.txt", NULL);
   mygsl_write_txt(m, stdout, "%.2f");

   mygsl_read_matrix_d("m.txt", m);
   mygsl_write_txt(m, stdout, "%.2f");
   gsl_matrix_free(m);
}

void test_print_vector(){
   gsl_vector *vec = mygsl_read_vector_d("test_vector.txt", NULL);
   
   mygsl_print(vec);
   mygsl_print(vec, 2);
   mygsl_print(vec, -3);

   gsl_vector_free(vec);
}

void test_print_matrix(){
   gsl_matrix *m = mygsl_read_matrix_d("m.txt", NULL);
   
   mygsl_print(m);

   gsl_matrix_free(m);
}