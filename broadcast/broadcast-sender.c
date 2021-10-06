/*
1. Nodo que envie datos cada cierto tiempo
2. Otro nodo que reciba los datos*/

//Netstack , lib. para qcualquier nodo que requiera comunicacion
//Nullnet red sin pila de protocolos
//Sys/log, para usar bitacoras de contiki

#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include "sys/log.h"
#define LOG_MODULE "Broadcast Sending App"
#define LOG_LEVEL LOG_LEVEL_INFO
#define SEND_INTERVAL (8 * CLOCK_SECOND) //intervalo para enviar datos

//Creacion de proceso boadcast_sender
PROCESS(broadcast_sender, "Broadcast Sender Example");
AUTOSTART_PROCESSES(&broadcast_sender);

PROCESS_THREAD(broadcast_sender, ev, data){
    static struct etimer periodic_timer;
    static unsigned counter= 0; //cuenta los datos enviados en un lapso de tiempo

    PROCESS_BEGIN();

    nullnet_buf= (uint8_t *)&counter;  //lo que contenga la counter sera el buffer del nullnet
    //uint_t conviere counter a una var. entera sin signo (1 arreglo de bytes)
    nullnet_len= sizeof(counter); //size del buffer

    etimer_set(&periodic_timer, SEND_INTERVAL); //inicializar timer

    while(1){
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

        LOG_INFO("Sending %u\n ", counter); //muestra info de LOG_LEVEL_INFO, lo que tenga counter le dara formato en el string (var sin signo).

        memcpy(nullnet_buf, &counter, sizeof(counter)); //Guardar en buffer
        nullnet_len= sizeof(counter);

        NETSTACK_NETWORK.output(NULL); //toma valores de memcpy u null_net
        counter++; 

        etimer_reset(&periodic_timer); //resetea timer
    }

    PROCESS_END();
}