#include "state.h"

#include <Arduino.h>

namespace state {
    const int DELAY = 300; //ms

    int counter = 0;

    TaskHandle_t Task1;
    SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();

    void increment() {
        xSemaphoreTake( xMutex, portMAX_DELAY );
        counter++;
        xSemaphoreGive(xMutex);
    }

    int getCount(){
        int count;
        xSemaphoreTake( xMutex, portMAX_DELAY );
        count = counter;
        xSemaphoreGive(xMutex);

        return count;
    }

    void CounterTask( void * parameter) {
        while (true){
            increment();
            delay(300);
        }
    }

    void setup() {
        xTaskCreatePinnedToCore(
            CounterTask, /* Function to implement the task */
            "Task1",     /* Name of the task */
            10000,       /* Stack size in words */
            NULL,        /* Task input parameter */
            0,           /* Priority of the task (0: lowest) */
            &Task1,      /* Task handle. */
            0);          /* Core where the task should run (0: sys, 1: usr) */
    }
}