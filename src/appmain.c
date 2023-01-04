#include "minilib.h"

void app_main()
{


  int x, y;

  // je copie les valeurs des registres esp et ebp dans x et y
  asm ("mov %%esp, %1" "\n\t"
      "mov %%ebp, %0"
      :"=r"(x),
       "=r"(y));
    //j'affiche les valeurs des registres;
    puthex(x);
    puts("\n");
    puthex(y);
    puts("\n");
}
