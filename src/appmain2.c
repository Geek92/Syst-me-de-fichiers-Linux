#include "appmain.h"
#include "minilib.h"
#include "list.h"

// on cree la structure qui va permettre de memoriser les contextes actifs
struct pctx context_list[LIST_SIZE];

// on declare une liste d'elements
LIST_HEAD(runqueue);

// on declare le context courant
struct pctx *actual_context = NULL;


//fonction qui permets d'initialiser le status des elements du tableau
void initialize_context_list()
{
    for(int i = 0; i < LIST_SIZE; i++){
        context_list[i].context_state = UNUSED; 
    }

}


//procedure qui p       ermets de creer un context et de l'ajouter a la liste de context actifs
int create_ctx(func_ctx f, void *args){
      for(int i = 0; i < LIST_SIZE; i++){
          if(context_list[i].context_state == UNUSED)
              {
                    //struct pctx new_context;
                    context_list[i].function_pointer = f;
                    context_list[i].arg_pointer = args;
                    context_list[i].context_state = NEW_CONTEXT;
                    context_list[i].ebp_value = (int)context_list[i].stack[STACK_SIZE - 4];
                    context_list[i].esp_value = (int)&context_list[i].stack[STACK_SIZE - 4];
                    
                     //on cree le chainage
                    INIT_LIST_HEAD(&context_list[i].position);
                    list_add(&context_list[i].position, &runqueue);
                    return i;
              }
       }
      return -1;
}

void yield(){
    if(list_empty(&runqueue)) {
        puts("liste vide\n");
        return;
    }
    list_move_tail(runqueue.next,&runqueue);
    struct pctx *n = list_entry(runqueue.next, struct pctx, position);
    switch_to_ctx(n);
}

void f_ping2(void *args)
   {
       while(1) {
           putc('A') ;
           yield();
           putc('B') ;
           yield();
           putc('C') ;
           yield();
 } }

 void f_pong2(void *args)
    {
        while(1) {
            putc('1') ;
            yield();
            putc('2') ;
           yield();
 } }

void app_main2()
{
    initialize_context_list();
    create_ctx(f_ping2,NULL);
    create_ctx(f_pong2,NULL);
    yield();
}