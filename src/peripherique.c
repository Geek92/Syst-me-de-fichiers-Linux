#include "minilib.h"
#include "appmain.h"
#include "ioport.h"



void appmain_periph(){
    
    //on affiche hello world
    puts("Hello World!\n");
    //fonction qui retourne le code ascii associé à une touche de clavier
    /*char keyboard_map(unsigned char caracter){
        return 0;
    }*/
    //putc(_inb(0x60));
    while(1){
       // on affiche le caractère entré au niveau du clavier
       putc(_inb(0x60));
    }

}