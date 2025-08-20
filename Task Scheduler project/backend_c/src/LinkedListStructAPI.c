#include "LinkedListStructAPI.h"

/*having a struct called task which contains all the things
a task has (title, description, duration, time, date, etc), 
and then create a 2D array with the rows being months and 
the columns being days. Then, depending on the value of the 
date field, I will have that element in the 2D array point 
to the task. If I want to have multiple tasks in a day, this
is where linked lists come into play, to keep track of when
each event happens in a day*/

void printList(List* list){
    Node* tmp = list->head;
    while(tmp != NULL){
        printf("%s, ", tmp->task->title);
        printf("%s, ", tmp->task->description);
        printf("%s, ", tmp->task->time);
        printf("%d, ", tmp->task->month);
        printf("%d, ", tmp->task->day);
        printf("%d, ", tmp->task->year);
        printf("%d, ", tmp->task->hour);
        printf("%d, ", tmp->task->minute);
        printf("%d, ", tmp->task->duration);
        printf("\n");

        tmp = tmp->next;
    }
}

Task* initializeTask(char* title, char* description, char* time, int month, int day, int year, int minute, int duration){
    Task* task = (Task*) malloc(sizeof(Task));
    

    if(task != NULL){
        task->title = malloc(strlen(title) + 1);
        strcpy(task->title, title);

        task->description = malloc(strlen(description) + 1);
        strcpy(task->description, description);

        task->time = malloc(strlen(time) + 1);
        strcpy(task->time, time);
        task->month = month;
        task->day = day;
        task->year = year;
        task->minute = minute;
        task->duration = duration;
    }

    else{
        return NULL;
    }

    return task;
}

Node* initializeNode(Task* task){
    Node* node = (Node*) malloc(sizeof(Node));
    if(node != NULL){
        node->task = task;
        node->next = NULL;
    }

    else{
        return NULL;
    }

    return node;
}

List* initializeList(Node* node){

    List* list = malloc(sizeof(List));
    if(list != NULL){
        list->head = node;
        list->length = (node == NULL) ? 0 : 1;
    }

    return list;
}

void freeList(List* list){
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->task->title);
        free(current->task->description);
        free(current->task->time);
        free(current->task);
        free(current);
        current = next;
    }
    free(list);
}

int getLength(List* list){
    return list->length;
}

int compareTask(Task* task, Task* task2){

    if((strcmp(task->title, task2->title) == 0) && (strcmp(task->description, task2->description) == 0) && (strcmp(task->time, task2->time) == 0) && (task->month == task2->month) && (task->day == task2->day) && (task->year == task2->year) && (task->minute == task2->minute) && (task->duration == task2->duration)){
        return 0;
    }

    else{
        return 1;
    }

}


void insertBack(List* list, Task* toBeAdded){

    Node* node = initializeNode(toBeAdded);
    Node* trav = list->head;

    if (list->head == NULL) {
        list->head = node;
        list->length++;
        return;
    }

    while(trav != NULL){
        if(trav->next == NULL){
            trav->next = node; 
            list->length++;
        }
        trav = trav->next;
    }

}

void insertFront(List* list, Task* toBeAdded){
    Node* node = initializeNode(toBeAdded);
    node->next = list->head;
    list->head = node;
    list->length++; 
}



Task* deleteDataFromList(List* list, Task* taskToDelete){
    if (list == NULL || list->head == NULL || list->length == 0) {
        return NULL;
    }

    Node* curr = list->head;
    Node* prev = NULL;

    while (curr != NULL) {
        if (compareTask(curr->task, taskToDelete) == 0) {
            if (prev == NULL) {
                list->head = curr->next;
            }
            else {
                prev->next = curr->next;
            }

            Task* deletedTask = curr->task;
            free(curr);
            list->length--;

            return deletedTask;
        }

        prev = curr;
        curr = curr->next;
    }

    return NULL; // Not found

}

//THIS IS THE MAIN INSERT INTO LINKED LIST FUNCTION!!

Node* insertSorted(Task* toBeAdded){
    Node* newNode = malloc(sizeof(Node));
    List* list = initializeList(newNode);
    newNode->task = toBeAdded;
    newNode->next = NULL;

    if (list->head == NULL || list->length == 0) {
        list->head = newNode;
        list->length = 1;
        return list->head;
    }

    Node* curr = list->head;
    Node* prev = NULL;

    if (((curr->task->hour >= toBeAdded->hour) && (strcmp(curr->task->time, toBeAdded->time) == 0)) || (strcmp(toBeAdded->time, "am") == 0 && strcmp(curr->task->time, "pm") == 0) || ((curr->task->hour == toBeAdded->hour) && (strcmp(curr->task->time, toBeAdded->time) == 0) && (curr->task->minute >= toBeAdded->minute))){
        insertFront(list, toBeAdded);
        return list->head;
    } 
    else{
        while (curr != NULL) {

            if(curr->next == NULL){
                insertBack(list, toBeAdded);
                return list->head;
            }
            else {
                if(((strcmp(toBeAdded->time, "am") == 0 && strcmp(curr->task->time, "am") == 0) && strcmp(curr->next->task->time, "pm") == 0) || (((strcmp(curr->task->time, toBeAdded->time) == 0) && (strcmp(curr->task->time, curr->next->task->time) == 0) && (curr->task->hour <= toBeAdded->hour) && (toBeAdded->hour <= curr->next->task->hour)))) {
                    
                    if(curr->task->hour == curr->next->task->hour){
                        if(toBeAdded->minute >= curr->task->minute && toBeAdded->minute <= curr->next->task->minute){
                            newNode->next = curr->next;
                            curr->next = newNode;
                            list->length++;
                            return list->head;
                        }
                    }
                    else if(curr->task->hour == toBeAdded->hour && toBeAdded->hour < curr->next->task->hour){
                        if(toBeAdded->minute >= curr->task->minute){
                            newNode->next = curr->next;
                            curr->next = newNode;
                            list->length++;
                            return list->head;
                        }
                    }
                    else if(curr->next->task->hour == toBeAdded->hour && toBeAdded->hour > curr->task->hour){
                        if(toBeAdded->minute <= curr->next->task->minute){
                            newNode->next = curr->next;
                            curr->next = newNode;
                            list->length++;
                            return list->head;
                        }
                    }
                }
            }
            
            prev = curr;
            curr = curr->next;
        }
    }

    return NULL; // Not found

}

