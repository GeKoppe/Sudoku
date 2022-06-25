/**
 * @file timeHelper.c
 * @author Jannik Glane
 * @brief Provides functions for taking time
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <time.h>
#include "timeHelper.h"
#include "common.h"

/**
 * @brief Ersellt einen Timer, welcher bei den übergebenen Sekunden beginnt
 * 
 * @param seconds Die Sekundenzahl, wie lange der Timer bei der Erstellung schon gelaufen seien soll
 * @return Das StopWatch Struct mit entsprechenden Werten
 */
StopWatch startTimer(int seconds)
{
    // Schreibt die aktuelle Zeit in das struct
    clock_t currentTime = clock() - seconds*(CLOCKS_PER_SEC * 1.0);
    StopWatch watch = {currentTime, currentTime, seconds};
    return watch;
}

/**
 * @brief Setzt die jetzige Zeit in die endTime Variable
 * 
 * @param StopWatch *watch Pointer zum StopWatch struct
 */
void stopTimer(StopWatch *watch)
{
    watch->endTime = clock();
}

/**
 * @brief Gibt die vergange Zeit in Sekunden zurück
 * 
 * @param StopWatch *watch Pointer zum StopWatch struct 
 * @return int Zeit in vollen Sekunden
 */
int getTimeInSeconds(StopWatch *watch)
{
    // Berechnet die vergange Zeit mit den startTime und endTime werten des structs
    if(watch->endTime != watch->startTime){
        watch->timeInSeconds = (watch->endTime - watch->startTime) / CLOCKS_PER_SEC;
    } else {
        watch->timeInSeconds = (clock() - watch->startTime) / CLOCKS_PER_SEC;
    }
    return watch->timeInSeconds;
}