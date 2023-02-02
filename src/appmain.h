#include "list.h"
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

//macro qui permets de charger un contexte
#define LOAD_CONTEXT(context){                                    \
  asm ("mov %0, %%esp" "\n\t" "mov %1,%%ebp"                              \
      :                                                                   \
      :"r"(context->esp_value),"r"(context->ebp_value));  \
}while(0)

//macro qui permets de sauvegarder un contexte
#define SAVE_CONTEXT(context){                                     \
  asm ("mov %%esp, %0" "\n\t" "mov %%ebp,%1"                               \
      :"=r"(context->esp_value),"=r"(context->ebp_value)); \
}while(0)

#define STACK_SIZE 4096

#define LIST_SIZE 10

typedef void(func_ctx)(void*);
typedef int(func_t)(int);
void f_ping(void *arg);
void f_pong(void *arg);
enum state {NEW_CONTEXT, ACTIVE, TERMINATED, UNUSED};

//defnition de la structure qui definit un contexte
struct pctx {
        int esp_value;
        int ebp_value;
        func_ctx *function_pointer;
        void *arg_pointer;
        enum state context_state;
        char stack[STACK_SIZE];
        struct list_head position;
};

//declaration des fonctions ping et pong a utiliser pour le changement de contexte
extern void switch_to_ctx(struct pctx *ptr);







