#include "minilib.h"
#include "appmain.h"
#include "list.h"

//typedef int(func_t)(int);
//typedef void(func_ctx)(void*);

//declaration des fonctions ping et pong a utiliser pour le changement de contexte
void f_ping(void *arg);
void f_pong(void *arg);

//declaration des contextes de  ping et pong
struct pctx ctx_ping = {.context_state = NEW_CONTEXT};
struct pctx ctx_pong = {.context_state = NEW_CONTEXT};

//contexte courant
struct pctx *current_context = NULL;

//procedure qui permets d'initialiser un contexte
int init_ctx(struct pctx *ctx, func_ctx f, void *args){
      ctx->function_pointer = f;
      ctx->arg_pointer = args;
      ctx->context_state = NEW_CONTEXT;
      ctx->ebp_value = (int)ctx->stack[STACK_SIZE - 4];
      ctx->esp_value = (int)&ctx->stack[STACK_SIZE - 4];
      return 0;
}

//procedure qui effectue le changement de contexte
 void switch_to_ctx(struct pctx *ctx){
    if(current_context != NULL){
        SAVE_CONTEXT(current_context);
    }
    current_context = ctx;
    LOAD_CONTEXT(current_context);
    if(current_context->context_state == NEW_CONTEXT){
        current_context->context_state = ACTIVE;
        current_context->function_pointer(current_context->arg_pointer);
    }
 }

 //fonction f_ping
 void f_ping(void *args)
   {
       while(1) {
           putc('A') ;
           switch_to_ctx(&ctx_pong);
           putc('B') ;
           switch_to_ctx(&ctx_pong);
           putc('C') ;
           switch_to_ctx(&ctx_pong);
 } }

 //fonction f_pong
 void f_pong(void *args)
    {
        while(1) {
            putc('1') ;
            switch_to_ctx(&ctx_ping);
            putc('2') ;
            switch_to_ctx(&ctx_ping);
 } }

void app_main(){

      init_ctx(&ctx_ping, f_ping, NULL);
      init_ctx(&ctx_pong, f_pong, NULL);
      switch_to_ctx(&ctx_ping);
}
