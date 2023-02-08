#include "list.h"

//structure de donnés associée a un semaphore
struct sem_s {
    int compteur;
    struct list_head waiting_list;
};

//procedure d'initialisation d'un semaphore
void sem_init(struct sem_s *sem, unsigned int val){
    sem->compteur = val;
    INIT_LIST_HEAD(&sem->waiting_list);
}

//implantation de la procedure sem_down
void sem_down(struct sem_s *sem){
    
};

//implantation de la procedure sem_up
void sem_up(struct sem_s *sem){

};