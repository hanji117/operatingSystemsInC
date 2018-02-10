/*
Taskset header file
Defines a taskset using pointers.
*/
#ifndef TASKSET_H
#define TASKSET_H

//Creates a pointer of task
typedef struct task {
  char* name; // name of task
  int wcet;   // worst case execution time
  int period; // when the task gets run
} task; //Struct type task has been created

//Creates the link list
typedef struct task_link {
  task *task; //Sets the task to the pointer
  struct task_link *next; //Variable next is a variable which is created
} task_link; //A link for the task has been created.

//Creates a task list
typedef struct task_list {
  task_link* tasks;//A task typedef has been created
  int size; //Initializes the size of the task sets
} task_list; //Task list pointer created

//Prototypes


task_list* initialize_task_set_list();

void add_task_set_list(task_link *link, char* name, int wcet, int period);

task *get_task(task_list *link, int index);

#endif
