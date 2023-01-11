#include "minilib.h"

typedef int(func_t)(int);

#define DUMP_SP() do{  \
  int esp_value;      \
  int ebp_value;      \
                      \
  asm ("mov %%esp, %0" "\n\t" "mov %%ebp, %1" \
      :"=r"(esp_value),"=r"(ebp_value));      \
                                              \
       putud(esp_value);                      \
       puts("\n");                            \
       putud(ebp_value);                      \
       puts("\n");                            \
}while(0)

struct pctx {
  int esp_value;
  int ebp_value;
};

struct pctx save_context;

int saved_r;
//je definie ma fonction throw
int throw(int r){
  saved_r = r;
  asm("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
       :
       : "r"(save_context.esp_value),"r"(save_context.ebp_value));
  return saved_r;
}

//on definit la function
int my_function(int return_value){
  if(return_value < 0){
    throw(return_value);
  }
  return return_value;
}

// je definit la function try
int try(func_t *f, int arg){
  DUMP_SP();
  asm ("mov %%esp, %0" "\n\t" "mov %%ebp, %1"
    :"=r"(save_context.esp_value),"=r"(save_context.ebp_value));
  return f(arg);
}

void app_main(){
 //puts("hello\n");
  //j'appeles ma fonction try
  int v = try(&my_function,5);
  putud(v);
  puts("\n");
  int a = try(&my_function,-2);
  putud(a);

}
