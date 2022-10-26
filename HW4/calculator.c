#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
	
	char *studentID;
	int grade;

};

struct Node {

	struct Record record;
	struct Node *next;

};

struct List {

	struct Node *head;
	struct Node *tail;

};

struct List SLL_new(){

	struct List temp;
	temp.head = NULL;
	temp.tail = NULL;
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
	struct Record record;
	record.studentID = key;
	record.grade = value;
	node->record = record;
	node->next = list->head;

	if (SLL_empty(list)) list->tail = node;	
	list->head = node;

}
/*
void SLL_pop(struct List *list, char *key, int *value){


}

void SLL_clear(struct List *list){
	
	while (!SLL_empty(list)) {SLL_pop(list);}

}*/

void SLL_insert(struct List *list, char *key, int value){

	if (SLL_empty(list)) SLL_push(list, key, value);
	else {
		struct Node *node = malloc(sizeof(struct Node));
		struct Record record;
		record.studentID = key;
		record.grade = value;
		node->record = record;
		node->next = NULL;

		list->tail->next = node;
		list->tail = node;
	}
	

}

void SLL_print(struct List *list){

	struct Node *curr = list->head;
	while (curr != NULL){
		printf("%s: %d | ", curr->record.studentID, curr->record.grade);
		curr = curr->next;	
	}

}


int main(int argc, char **argv){

	char line[128];
	FILE *file;
	int i = 0;
	struct List list = SLL_new();
	
	if (argc != 5) exit(1); 

	for (i = 1; i < 4; i++){

		file = fopen(argv[i], "r");
		if (file == NULL) break;

		printf("Opened %s\n", argv[i]);
		while (fgets(line, 128, file)){

			char *studentID = strtok(line, ",");
			int grade = atoi(strtok(NULL, ","));
			SLL_insert(&list, studentID, grade);
	
		}

	}

	SLL_print(&list);
	printf("%d", strcmp("appla", "applb"));

	return 0;

}
