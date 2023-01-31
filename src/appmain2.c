#include "appmain.h"
#include "list.h"


// on cree la structure qui va permettre de memoriser les contextes actifs
struct pctx context_list[LIST_SIZE];

//fonction qui permets d'initialiser le status des elments du tableau
void initialize_context_list(struct pctx *context_list_pointer){
    for(int i = 0; i < LIST_SIZE; i++){
        (context_list_pointer + i)->context_state = UNUSED; 
    }

}

//je definit la procedure create_context qui cree les contextes des fonctions
//procedure qui permets d'initialiser un contexte
int create_ctx(func_t f, void *args){
      

      
      ctx->function_pointer = f;
      ctx->arg_pointer = args;
      //ctx->context_state = NEW_CONTEXT;
      ctx->ebp_value = (int)ctx->stack[STACK_SIZE - 4];
      ctx->esp_value = (int)&ctx->stack[STACK_SIZE - 4];

      return 0;
}