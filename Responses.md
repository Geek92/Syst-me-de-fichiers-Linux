
# Reponse aux exercices 3

Exercice 3.2

3.2.1

int esp_value,ebp_value;
  //j'affiche les valeurs des registres esp et ebp
  asm ("mov %%esp, %0" "\n\t"
      "mov %%ebp, %1"
      :"=r"(esp_value),
       "=r"(ebp_value));
       putud(esp_value);
       puts("\n");
       putud(ebp_value);
       puts("\n");

3.2.2

   la valeur du registre esp est inferieure a celles des variables locales 
   declarées dans les fonctions par contre, les valeurs des variables locales sont inferieures a la valeur 
   du registre ebp.

3.2.3

les valeurs des parametres des fonctions sont inferieures a celles du registre ebp et superieures 
a celles du registre esp.

3.2.4

ces differentes valeurs indiquent le fonctionement de la pile d'execution: losrqu'une fonction est appelée,
les arguments sont empilés et ensuite les variables locales. le registre ebp pointe a la base de la pile tandis que
le registre esp pointe au sommet de la pile.

   
