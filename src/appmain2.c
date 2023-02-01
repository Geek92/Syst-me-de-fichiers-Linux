#include "appmain.h"
#include "list.h"
#include "minilib.h"

// on cree la structure qui va permettre de memoriser les contextes actifs
struct pctx context_list[LIST_SIZE];

// on declare une liste d'elements
LIST_HEAD(contextList);

// on declare le context courant
struct pctx current_context;


//fonction qui permets d'initialiser le status des elments du tableau
void initialize_context_list(struct pctx *context_list_pointer){
    for(int i = 0; i < LIST_SIZE; i++){
        (context_list_pointer + i)->context_state = UNUSED; 
    }

}


//procedure qui permets de creer un context et de l'ajouter a la liste de context actifs
int create_ctx(func_ctx f, void *args){
      for(int i = 0; i < LIST_SIZE; i++){
          if(context_list[i].context_state == UNUSED)
              {
                    struct pctx new_context;
                    new_context.function_pointer = f;
                    new_context.arg_pointer = args;
                    new_context.context_state = NEW_CONTEXT;
                    new_context.ebp_value = (int)new_context.stack[STACK_SIZE - 4];
                    new_context.esp_value = (int)&new_context.stack[STACK_SIZE - 4];
                    context_list[i] = new_context;
                     //on cree le chainage
                    //new_context.position = LIST_HEAD_INIT(new_context.position);
                    list_add(&new_context.position, &contextList);
                    break;
              }
       }
      return 0;
}

void yield(){
    //si on n'a pas de context courrant on parcours la liste des context et on charge le premier context
    if(current_context == NULL){
       for(int i = 0; i < LIST_SIZE; i++){
            if(context_list[i].context_state == NEW_CONTEXT){
                current_context = context_list[i];
                break;
            }
       }

    }
    

}

void f_ping(void *args)
   {
       while(1) {
           putc('A') ;
           yield();
           putc('B') ;
           yield();
           putc('C') ;
           yield();
 } }

 void f_pong(void *args)
    {
        while(1) {
            putc('1') ;
            yield();
            putc('2') ;
           yield();
 } }

void app_main2()
{
    initialize_context_list(context_list);
    create_ctx(f_ping,NULL);
    create_ctx(f_pong,NULL);
    yield();
}