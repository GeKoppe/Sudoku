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
#include <time.h>

typedef struct{
    clock_t startTime;
    clock_t endTime;
    double timeInSeconds;
} StopWatch;

StopWatch startTimer();

void stopTimer(StopWatch *watch);

double getTimeInSeconds(StopWatch *watch);