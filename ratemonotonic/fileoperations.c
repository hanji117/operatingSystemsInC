#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "taskset.h" //Includes a preprocessor called taskset

#define BUFF_SIZE 256 //Buffer size currently initialized to 256.

// Below will error out the program
// if any invalid event occurs.
inline void errorAndDie(const char *errorMsg)
{
  perror(errorMsg);
  exit(EXIT_FAILURE);
}

//OpenFile has fileName and operations as a parameters.
inline FILE *openFile(const char *fileName, char *operations)
{
  FILE *file;
  // Opens a file in read mode.
  if ((file = fopen(fileName, operations)) == NULL)
    {
      // Errors out if the file did not open successfully.
      fputs("Error opening file\n", stderr);
      exit(EXIT_FAILURE);
    }
  return file;
}
//
inline void updateTaskSet(task_link *link, char *lineFromFile)
{
  char *name = NULL;
  int wcet;
  int period;

  char *lineContents = strtok(lineFromFile, " ");
  int contentCount = 1;
  while (lineContents != NULL)
    {
      if (contentCount == 1) {

        name = lineContents;
      }
      else if (contentCount == 2) {
        wcet = atoi(lineContents);
      }
      else if (contentCount == 3) {
        period = atoi(lineContents);
        break;
      }

      lineContents = strtok(NULL, " ");
      contentCount++;
    }

  if (isdigit(wcet))
    errorAndDie("Invalid wcet");

  if (isdigit(period))
    errorAndDie("Invalid period");

  add_task_set_list(link, name, wcet, period);
}

task_list *extract_task_sets(char* fileName)
{
  FILE *file = openFile(fileName, "r");
  char buff[BUFF_SIZE];
  task_list *list = initialize_task_set_list();
  list->tasks = malloc(sizeof(task_list *));
  task_link *link = list->tasks;

  while (fgets(buff, sizeof(buff), file) != NULL) {
    updateTaskSet(link, buff);
    link->next = malloc(sizeof(task_link *));
    link = link->next;
    list->size++;
  }

  return list;
}

void write_to_file(char* fileName, char* stringToWrite)
{
  FILE *file = openFile(fileName, "a+");
  if (fputs(stringToWrite, file) < 0) {
    errorAndDie("Error writing to file.");
  }
}
