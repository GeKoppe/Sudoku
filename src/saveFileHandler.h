/**
 * @file saveFileHandler.h
 * @author Jannik Glane
 * @brief 
 * @version 0.1
 * @date 2022-06-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef saveFileHandler_h
#define saveFileHandler_h
#include "fileHelper.h"

int saveToFile(SaveFile save, char *fileName);
SaveFile loadSaveFromFile(char *fileName);
#endif