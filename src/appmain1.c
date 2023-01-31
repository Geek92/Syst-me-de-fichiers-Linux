#include "minilib.h"
#include "appmain.h"
#include "list.h"



int saved_r;

//on definit la fonction throw
int throw(int r){
    saved_r = r;
    asm("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
        :
        : "r"(saved_context.esp_value),"r"(saved_context.ebp_value));
        return saved_r;
}


//on definit la function
int my_function(int return_value){
    if(return_value < 0){
        throw(return_value);
    }
    return return_value;
}

// on definit la function try
int try(func_t *f, int arg){
      DUMP_SP();
      asm ("mov %%esp, %0" "\n\t" "mov %%ebp, %1"
      :"=r"(saved_context.esp_value),"=r"(saved_context.ebp_value));
      return f(arg);
}

void app_main1(){
  //j'appeles ma fonction try
  /*int v = try(&my_function,5);
  putud(v);
  puts("\n");
  int a = try(&my_function,-2);
  putud(a);*/
}
