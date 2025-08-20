#ifndef _TaskEditor_
#define _TaskEditor_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Convert the input received from the user to create a task
Task* inputToTask(int month, int day, char* title, char* description, char* time, int year, int hour, int minute, int duration);

// Add the task to the calendar 2D array
// Add task to linked list if there are multiple tasks in the same day
void addTaskToCalendar(Task* task);

// Delete the task from the calendar
// Free the memory
// Remove all instances of the task if prompted
void deleteTaskFromCal(Task* taskToBeDeleted, bool dupDelete);

void accessDayList(int day, int month);

#endif