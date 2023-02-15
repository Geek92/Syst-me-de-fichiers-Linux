#include "list.h"
#include "minilib.h"
#include "appmain.h"

//structure de donnés associée a un semaphore
struct sem_s {
    int compteur;
    struct list_head waiting_list;
};

struct sem_s semaphore;

//variable partagee par les deux fonctions
int c = 0;

//procedure d'initialisation d'un semaphore
void sem_init(struct sem_s *sem, unsigned int val){
    sem->compteur = val;
    INIT_LIST_HEAD(&sem->waiting_list);
}

//implantation de la procedure sem_down
void sem_down(struct sem_s *sem){
     sem->compteur--;
    // si la valeur du compteur est negative on bloque le contexte appeleant dans la pile
    if(sem->compteur < 0){
  
    } 

};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
//implantation de la procedure sem_up
void sem_up(struct sem_s *sem){
    sem->compteur++;
    //Si le compteur est négatif ou nul, un contexte est choisi dans la file d’attente et devient actif.
    if(sem->compteur <= 0){
    
    } 
};

//fonction f_pong
void f_ping3(void *args)
   {
         sem_up(&semaphore);
         c++;
         puts("la fonction f_ping3 incremente la variable c");
         sem_down(&semaphore);
    }     

 //fonction f_pong
 void f_pong3(void *args)
   {
         sem_up(&semaphore);
         c++;
         puts("la fonction f_pong3 incremente la variable c");
         sem_down(&semaphore);
    }     
    

void appmain_sem(){
    //on cree les contextes des deux fonctions
    create_ctx(f_pong3,NULL);
    create_ctx(f_ping3, NULL);

};