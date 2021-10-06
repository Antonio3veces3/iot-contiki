#include "contiki.h"
#include "sys/etimer.h"
#include "sys/ctimer.h"
#include <stdio.h>

//Nombre del proceso:
PROCESS(timers_demo, "Timers Demo");
//Cuando empieza y que proceso se inicia 
AUTOSTART_PROCESSES(&timers_demo);

//Estructura etimer.
static struct etimer event_timer;

//Funcion para mandar llamar a partir de otra funcion, cuando el timer ha expirado, se manda a llamar esta funcion.
static struct ctimer callback_timer;

//funcion de callback
void callback_function(){
    printf("This is the callback function\n");
    ctimer_reset(&callback_timer);//Para resetear y que cada 4 seg aparezca este mensaje.
}

//Hilo del proceso, (proceso, variable globalk eventos, variable global datos)
PROCESS_THREAD(timers_demo,ev,data){

    PROCESS_BEGIN();

    //Para inicializar callback timer (variable static), cada 4seg, funcion a llamar, parametro.
    ctimer_set(&callback_timer, 4 * CLOCK_SECOND, callback_function, NULL);

//Para inicializar temporizador(proceso, tiempo)
    etimer_set(&event_timer, 2 * CLOCK_SECOND); //2* 1000 milisegundos= 2seg

    

//Sin este while se sale la simulacion aunque el timer no haya finalizado
    while(1){
    //Para esperar evento, hasta que expire el timer
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&event_timer));

    //Ya que haya expirado el timer
    printf("Event timer expired\n");
    etimer_reset(&event_timer); //Resetea el ciclo, cada 2 segundos muestra el mensaje anterior. Hasta que se apague el dispositivo.
    //break; //rompe ciclo.
    }
    printf("Process ending...\n");
    PROCESS_END();
}