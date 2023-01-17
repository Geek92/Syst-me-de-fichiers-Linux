#include "minilib.h"

typedef int(func_t)(int);
typedef void(func_ctx)(void*);
#define STACK_SIZE 4096

//macro qui permets d'afficher les valeurs des registres esp et ebp de la fonction courante
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

enum state {NEW_CONTEXT, ACTIVE, TERMINATED};

struct pctx {
  int esp_value;
  int ebp_value;
  func_ctx *function_pointer;
  void *arg_pointer;
  enum state context_state;
  char stack[STACK_SIZE];
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

//procedure qui permets d'initialiser un context
int init_ctx(struct pctx *ctx, func_ctx f, void *args){
  ctx->function_pointer = f;
  ctx->arg_pointer = args;
    return 0;
}

//procedure qui effectue le changement de contexte
 void switch_to_ctx(struct pctx *ctx){


 }
void app_main(){
  //j'appeles ma fonction try
  int v = try(&my_function,5);
  putud(v);
  puts("\n");
  int a = try(&my_function,-2);
  putud(a);

}
