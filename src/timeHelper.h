/**
 * @file timeHelper.h
 * @author Jannik Glane
 * @brief 
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef timeHelper_h
#define timeHelper_h

#include <time.h>

typedef struct stopWatch {
    clock_t startTime;
    clock_t endTime;
    int timeInSeconds;
} StopWatch;

/**
 * @brief Ersellt einen Timer, welcher bei den übergebenen Sekunden beginnt
 * 
 * @param seconds Die Sekundenzahl, wie lange der Timer bei der Erstellung schon gelaufen seien soll
 * @return Das StopWatch Struct mit entsprechenden Werten
 */
StopWatch startTimer();

/**
 * @brief Sets the endTime in the passed StopWatch struct
 * 
 * @param watch 
 */
void stopTimer(StopWatch *watch);

/**
 * @brief Returns the time passed in seconds. Uses startTime and endTime from StopWatch struct. Also sets the time in the struct.
 * 
 * @param watch 
 * @return double 
 */
int getTimeInSeconds(StopWatch *watch);

#endif