#include "LinkedListStructAPI.h"
#include "TaskManipulation.h"

int main() {
    
    int month = 8;
    int day = 28;
    char* title = "Birthday";
    char* description = "Sami's Birthday";
    char* time = "am";
    int year = 2025;
    int hour = 12;
    int minute = 0;
    int duration = 1;

    Task* task = inputToTask(month, day, title, description, time, year, hour, minute, duration);
    addTaskToCalendar(task);

    accessDayList(28, 7);

    return 0; 
}