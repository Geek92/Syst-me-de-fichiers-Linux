#include "minilib.h"
#include "appmain.h"

typedef int(func_t)(int);
typedef void(func_ctx)(void*);
#define STACK_SIZE 4096

enum state {NEW_CONTEXT, ACTIVE, TERMINATED};

struct pctx {
  int esp_value;
  int ebp_value;
  func_ctx *function_pointer;
  void *arg_pointer;
  enum state context_state;
  char stack[STACK_SIZE];
};

//declaration des fonctions ping et pong a utiliser pour le changement de contexte
void f_ping(void *arg);
void f_pong(void *arg);

//declaration des contextes de  ping et pong
struct pctx ctx_ping = {.context_state = NEW_CONTEXT};
struct pctx ctx_pong = {.context_state = NEW_CONTEXT};
struct pctx save_context;

//contexte courant
struct pctx *current_context = NULL;
int saved_r;

//on definit la fonction throw
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

// on definit la function try
int try(func_t *f, int arg){
  DUMP_SP();
  asm ("mov %%esp, %0" "\n\t" "mov %%ebp, %1"
    :"=r"(save_context.esp_value),"=r"(save_context.ebp_value));
  return f(arg);
}

//procedure qui permets d'initialiser un contexte
int init_ctx(struct pctx *ctx, func_ctx f, void *args){
      ctx->function_pointer = f;
      ctx->arg_pointer = args;
      return 0;
}

//fonction f_ping


//procedure qui effectue le changement de contexte
 void switch_to_ctx(struct pctx *ctx){
    if(current_context == NULL){

    } else {
              SAVE_CONTEXT(current_context);
              current_context = ctx;
              LOAD_CONTEXT(current_context);
              if(current_context->context_state == NEW_CONTEXT){
                    current_context->context_state = ACTIVE;
                    current_context->function_pointer(current_context->arg_pointer);
              }
    }
 }
void app_main(){
  //j'appeles ma fonction try
  /*int v = try(&my_function,5);
  putud(v);
  puts("\n");
  int a = try(&my_function,-2);
  putud(a);*/
      init_ctx(&ctx_ping, f_ping, NULL);
      init_ctx(&ctx_pong, f_pong, NULL);
      switch_to_ctx(&ctx_ping);
}
