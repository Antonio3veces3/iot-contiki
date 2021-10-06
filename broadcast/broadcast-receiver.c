/*Nodo que recive la info*/
#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include "sys/log.h"


#define LOG_MODULE "Broadcast Receiver App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define WAIT_INTERVAL (5 * CLOCK_SECOND) //Para no ciclar el programa

//Creamos proceso
PROCESS(broadcast_receiver, "Broadcast Received Example");
AUTOSTART_PROCESSES(&broadcast_receiver);

//Funcion a llamar cuando reciba un pack.
//recive todos los parametros del pack
//uint16_t entero de 16 bits sin signo
//linkaddr= todo lo que termine en _t es una estructura

void input_callback(const void *data, uint16_t len, const linkaddr_t *source, const linkaddr_t *destination){
    //Comprobar el tamaño esperado (sin signo)
    if(len == sizeof(unsigned)){
        unsigned counter;
        memcpy(&counter, data, sizeof(counter));//Lo que viene en var data lo copia al counter

        LOG_INFO("Received %u from", counter);
        LOG_INFO_LLADDR(source); //para obtener link layer address
        LOG_INFO_("\n"); //concatena con lo anterior
    }
}

PROCESS_THREAD(broadcast_receiver, ev, data){
    static struct etimer periodic_timer;
    static unsigned counter;

    PROCESS_BEGIN();

    nullnet_buf= (uint8_t *)&counter;
    nullnet_len= sizeof(counter);
    nullnet_set_input_callback(input_callback); //llama a funcion input_callback cuando llega un mensaje

    etimer_set(&periodic_timer, WAIT_INTERVAL);
    while(1){
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

        LOG_INFO("Waiting for data... \n");

        etimer_reset(&periodic_timer);
    }

    PROCESS_END();
}
