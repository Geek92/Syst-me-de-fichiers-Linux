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
//mov(source, destination)
#define LOAD_CONTEXT(current_context){                                    \
  asm ("mov %0, %%esp" "\n\t" "mov %1,%%ebp"                              \
      :                                                                   \
      :"r"(current_context->esp_value),"r"(current_context->ebp_value));  \
}while(0)

//macro qui permets de sauvegarder un contexte
#define SAVE_CONTEXT(current_context){                                     \
  asm ("mov %%esp, %0" "\n\t" "mov %%ebp,%1"                               \
      :"=r"(current_context->esp_value),"=r"(current_context->ebp_value)); \
}while(0)
