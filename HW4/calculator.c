#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {

	char *key;
    int value;
	struct Node *next;

};

struct List {

	struct Node *head;

};

struct List SLL_new(){

	struct List temp;
	temp.head = NULL;
	return temp;

}

int SLL_empty(struct List *list){ return list->head == NULL; }

int SLL_length(struct List *list){
	
	int i = 0;
	struct Node *current;
	for (current = list->head; current != NULL; current = current->next) i++;
	return i;

}

void SLL_push(struct List *list, char *key, int value){

	struct Node *node = malloc(sizeof(struct Node));
    node->value = value;
    node->key = key;
	node->next = list->head;
	list->head = node;

}

void SLL_insert(struct List *list, char *key, int value){

    char *studentID = (char*)malloc(sizeof(char) * 256);
    strcpy(studentID, key);

    if (SLL_empty(list) || (list->head != NULL && strcmp(list->head->key, studentID) >= 0)){
        SLL_push(list, studentID, value);
	} else {
        struct Node *current = list->head;
        struct Node *temp;
		struct Node *node = malloc(sizeof(struct Node));

        while (current != NULL && strcmp(current->key, studentID) <= 0){
            temp = current;
            current = current->next;
        }

        node->value = value;
        node->key = studentID;
		node->next = current;
        temp->next = node;

	}
	

}

void SLL_pop(struct List *list, char *key, int *value){

    struct Node *head = list->head;
    int grade;
    char *studentID = (char*)malloc(sizeof(char) * 256);

    if (head == NULL) return;
    strcpy(studentID, head->key);
    grade = head->value;

    list->head = head->next;

    if (value != NULL) *value = grade;
    if (key != NULL) strcpy(key, studentID);

    free(head);
    free(studentID);
}

void SLL_clear(struct List *list){

    while (!SLL_empty(list)) {
        SLL_pop(list, NULL, NULL);
    }

}

/*
void SLL_print(struct List *list){

    struct Node *current = list->head;
    while (current != NULL){
        printf("%s (%d)\n", current->studentID, current->grade);
        current = current->next;
    }

}*/


int main(int argc, char **argv){

	char line[256];
    char *buffer = (char*)malloc(sizeof(char) * 256);
	FILE *file;
	int i = 0;
    int grade;
    char *pastStudent = (char*)malloc(sizeof(char) * 256);
    double totalGrade = 0.0;
	struct List list = SLL_new();

	if (argc != 5) exit(1); 

	for (i = 1; i < 4; i++){

		file = fopen(argv[i], "r");
		if (file == NULL) break;

		while (fgets(line, 128, file)){

			strcpy(buffer, strtok(line, ","));
			grade = atoi(strtok(NULL, ","));
			SLL_insert(&list, buffer, grade);
	
		}

	}

    file = fopen(argv[4], "w");
    if (file == NULL) exit(1);

    i = 0;
    while (!SLL_empty(&list)){

        SLL_pop(&list, buffer, &grade);
        if (strcmp(pastStudent, "") == 0) { /* When its first */
            strcpy(pastStudent, buffer);
            totalGrade = grade;

        } else if (strcmp(pastStudent, buffer) != 0){
            fprintf(file, "%s,%d\n", pastStudent, (int)(totalGrade/3 + .5));
            totalGrade = grade;
            strcpy(pastStudent, buffer);

        } else {
            totalGrade += grade;
        }

    }

    if (strcmp(pastStudent, "") != 0) fprintf(file, "%s,%d\n", pastStudent, (int)(totalGrade/3 + .5));
    free(pastStudent);
    free(buffer);
    fclose(file);

	return 0;

}
