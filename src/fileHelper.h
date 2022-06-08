/**
 * @file fileHelper.h
 * @author Jannik Glane
 * @brief 
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
const char *FILE_EXTENSION;

int checkDirExists(char *dir);
void buildFilePath(char *fileName, char *pathVariable, char *directory);
char** getFilesInFolder(char *directory);
int checkForFileExtension(char *name);