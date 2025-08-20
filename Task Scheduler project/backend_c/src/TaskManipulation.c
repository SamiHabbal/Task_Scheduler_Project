// create a 2D array for the months and days, implement the daily linked list, and match task corrosponding to the day in the 2D array
// Be able to add, delete, and edit tasks
// Implement option for repeating tasks. implement deletion of repeating task
#include "LinkedListStructAPI.h"
#include "TaskManipulation.h"



// 12 months, up to 31 days each (0-indexed)
List* Calendar[12][31] = {{NULL}};

Task* inputToTask(int month, int day, char* title, char* description, char* time, int year, int hour, int minute, int duration){
    Task* task = malloc(sizeof(Task));
    if (!task) return NULL;
    task->title = malloc(strlen(title) + 1);
    strcpy(task->title, title);
    task->description = malloc(strlen(description) + 1);
    strcpy(task->description, description);
    task->time = malloc(strlen(time) + 1);
    strcpy(task->time, time);
    task->month = month;
    task->day = day;
    task->year = year;
    task->hour = hour;
    task->minute = minute;
    task->duration = duration;
    return task;
}

void addTaskToCalendar(Task* task){
    int month = task->month;  // 0-indexed
    int day = task->day;      // 0-indexed
    if (month < 0 || month > 11 || day < 0 || day > 30) return;
    if (Calendar[month][day] == NULL) {
        Calendar[month][day] = initializeList(NULL);
    }
    insertFront(Calendar[month][day], task); // or insertSorted(Calendar[month][day], task) if you want sorted
}

void deleteTaskFromCal(Task* taskToBeDeleted, bool dupDelete){
    int month = taskToBeDeleted->month;  // 0-indexed
    int day = taskToBeDeleted->day;      // 0-indexed
    if(dupDelete == true){ //Deleted any repeating tasks
        for(int i = 0; i < 12; i++){
            int daysInMonth = 31;
            if(i == 1) daysInMonth = 29; // Feb
            else if(i == 3 || i == 5 || i == 8 || i == 10) daysInMonth = 30;
            for(int j = 0; j < daysInMonth; j++){
                if(Calendar[i][j] != NULL){
                    deleteDataFromList(Calendar[i][j], taskToBeDeleted);
                }
            }
        }
    }
    else{
        if(Calendar[month][day] == NULL){
            printf("No Task to delete!\n");
        }
        else{
            deleteDataFromList(Calendar[month][day], taskToBeDeleted);
        }
    }
}


void accessDayList(int day, int month){
    if(Calendar[month][day] == NULL){
        printf("No tasks on %d, %d", day, month);
    }
    else{
        printList(Calendar[month][day]);
    }
}