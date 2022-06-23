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

StopWatch startTimer();

void stopTimer(StopWatch *watch);

int getTimeInSeconds(StopWatch *watch);

#endif