#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "taskset.h"//We need taskset to run this program

task_list* extract_task_sets(char* fileName);//We need to extract the task sets

void write_to_file(char* fileName, char* stringToWrite);//Must create a function that writes to a file.

#endif
