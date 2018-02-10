#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "taskset.h" //Calls the task set files

//Constructor of pointers
task_list* initialize_task_set_list()
{
  task_list *task_list = malloc(sizeof(task_list));//Allocating spaces of th\
    e heap to store a pointer(task_liat) to an integer.
      task_list->tasks = NULL; //Task initialized to NULL
    task_list->size = 0; //Task size initialized to 0.

    return task_list; //Returns the list of tasks
}

//Purpose: To add the taskset list.
//Parameters: Takes link name wcet and period as a parameter
void add_task_set_list(task_link *link, char* name, int wcet, int period)
{
  task *new_task = malloc(sizeof(task *));
  new_task->name = malloc(sizeof(name));
  strcpy(new_task->name, name);//Copies the new task name to name
  new_task->wcet = wcet;//The task links to the wcet
  new_task->period = period;//The task links to the period

  //If the link in NULL then it cannot be initialized
  if (link == NULL) {
    perror("Error initializing task set link.");
    exit(EXIT_FAILURE);
  }
  //Moves the link to the new task until the next one points to NULL
  link->task = new_task;
  link->next = NULL;
}

//Passes a list and an index as an argument
task *get_task(task_list *list, int index)
{
  task_link *link = list->tasks;  //The list of tasks creates the links of tasks
  if (index > sizeof(link) || index < 0) //if the index is negative or greater than link size then error.
    {

      perror("Index cannot be bigger than number of tasks or less than 0.");
      exit(EXIT_FAILURE);
    }

  task *task = link->task; //link will link to the task which is created by the pointer.

  // While the index is greater than 0, then the link will point to the next link and link will point to the next task and decrements the index.
  while (index > 0) {
    link = link->next;
    task = link->task;
    index--;
  }

  return task; //Returns the task.
}

