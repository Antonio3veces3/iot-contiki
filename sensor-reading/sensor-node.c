#include "contiki.h"
#include "sys/etimer.h"
#include <stdio.h>

#include "virtual-sensor.h"


//Nombre del proceso+mesaje
PROCESS(sensor_node, "Sensor Reading Node");

//Procesos a inicializar
AUTOSTART_PROCESSES(&sensor_node);


//Declarar temporizador
static struct etimer timer; 

//Hilo del proceso.

PROCESS_THREAD(sensor_node, ev, data){
    PROCESS_BEGIN();
    
    etimer_set(&timer, 5 * CLOCK_SECOND);

    //Ciclo pulling
    while (1)
    {
        //Espera a que expire el temporizador timer.
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        //llamar funcion del archivo virtual-sensor.c
        float temperature_reading= read_temperature();
        //Mensaje para mostrar temperatura
        printf("Temperature reading: %.2f C \n",temperature_reading);

        //llamar funcion de arch virtual-sensor.c
        float humidity_reading= read_humidity();
        //Mensaje para lectura de humedad
        printf("Humidity reading: %.2f %% \n", humidity_reading);

        //resetear timer para que c/ 5 segundos muestre mensaje de humedad y temperatura.
        etimer_reset(&timer);
    }
    
    PROCESS_END();
}