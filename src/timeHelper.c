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
    clock_t currentTime = clock() - seconds*(CLOCKS_PER_SEC * 1.0);
    StopWatch watch = {currentTime, currentTime, seconds};
    return watch;
}

/**
 * @brief Sets the endTime in the passed StopWatch struct
 * 
 * @param watch 
 */
void stopTimer(StopWatch *watch)
{
    watch->endTime = clock();
}

/**
 * @brief Returns the time passed in seconds. Uses startTime and endTime from StopWatch struct. Also sets the time in the struct.
 * 
 * @param watch 
 * @return double 
 */
int getTimeInSeconds(StopWatch *watch)
{
    // CLOCKS_PER_SEC needs to be converted to a floating point value for accurate division
    if(watch->endTime != watch->startTime){
        watch->timeInSeconds = (watch->endTime - watch->startTime) / (CLOCKS_PER_SEC * 1.0);
    } else {
        watch->timeInSeconds = (clock() - watch->startTime) / (CLOCKS_PER_SEC * 1.0);
    }
    return watch->timeInSeconds;
}