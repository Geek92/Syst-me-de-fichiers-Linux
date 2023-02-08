#include "idt.h"
#include "minilib.h"
#include "appmain.h"
//int create_ctx(func_t f, void *args);

void start_sched(){
    idt_setup_handler(TIMER_IRQ, yield);
}

void app_main3(){

    initialize_context_list();
    create_ctx(f_ping2,NULL);
    create_ctx(f_pong2,NULL);
    start_sched();
}