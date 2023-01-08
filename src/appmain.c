#include "minilib.h"


int app_main(int a, int b)
{
  int esp_value,ebp_value;
  //j'affiche les valeurs des registres esp et ebp
  asm ("mov %%esp, %0" "\n\t"
      "mov %%ebp, %1"
      :"=r"(esp_value),
       "=r"(ebp_value));
       putud(esp_value);
       puts("\n");
       putud(ebp_value);
       puts("\n");

      return a + b;
}

int multiplication(int a, int b){

  int esp_value,ebp_value;
  //j'affiche les valeurs des registres esp et ebp
  asm ("mov %%esp, %0" "\n\t"
      "mov %%ebp, %1"
      :"=r"(esp_value),
       "=r"(ebp_value));
       putud(esp_value);
       puts("\n");
       putud(ebp_value);
       puts("\n");

      return a * b;

}
