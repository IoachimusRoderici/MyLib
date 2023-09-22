#define MyAssert_name "test"
#include "MyAssert.h"

int main(){

   MyAssert(1, "1 %d", 1);
   //MyAssert(0, "0 %d", 1);

   MyAssert_nn(1, "1 %d", 1);
   MyAssert_nn(0, "0");

   return 0;
}