//Incluye encabezado creado en el dir. local
#include "virtual-sensor.h"

//Libreria para numeros aleatorios
#include <stdlib.h>

//Indicar min y max de num random
float random_value(float min, float max){
    float scale= rand() / (float) RAND_MAX;
    return min + scale * (max-min);
}

//Desarrollo de las funciones
float read_temperature(){
    return random_value(0,35);
}

float read_humidity(){
    return random_value(40,80);
}