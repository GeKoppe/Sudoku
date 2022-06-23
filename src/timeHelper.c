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

/**
 * @brief Sets the startTime as the current CPU-Clock
 * 
 * @return StopWatch 
 */
StopWatch startTimer()
{
    clock_t currentTime = clock();
    StopWatch watch = {currentTime, currentTime, 0};
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