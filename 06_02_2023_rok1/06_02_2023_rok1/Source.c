#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_NAME (256)

struct _student;
typedef struct _student *StudentP;
typedef struct _student {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int subject1;
	int subject2;
	int subject3;
	StudentP next;
} Student;

// OCJENA 2
StudentP InitializeStud();
int ReadFile(StudentP head, char* file, int whichList);
StudentP CreateStud(char* firstName, char* lastName, int grade, int whichList);
int AddToFront(StudentP head, StudentP new);
int PrintList(StudentP head);
int DeleteList(StudentP head);





int main() {
	StudentP head1 = NULL;
	StudentP head2 = NULL;
	StudentP head3 = NULL;

	head1 = InitializeStud();
	head2 = InitializeStud();
	head3 = InitializeStud();

	char f1[MAX_NAME] = "subject1.txt";
	char f2[MAX_NAME] = "subject2.txt";
	char f3[MAX_NAME] = "subject3.txt";

	ReadFile(head1, f1, 1);
	ReadFile(head2, f2, 2);
	ReadFile(head3, f3, 3);

	printf("\nLIST 1\n");
	PrintList(head1);
	printf("LIST 2\n");
	PrintList(head2);
	printf("LIST 3\n");
	PrintList(head3);

	DeleteList(head1);
	DeleteList(head2);
	DeleteList(head3);




	if (NULL == head1->next)
		printf("List 1 deleted!\n");
	if (NULL == head2->next)
		printf("List 2 deleted!\n");
	if (NULL == head3->next)
		printf("List 3 deleted!\n");

	return EXIT_SUCCESS;
}

StudentP InitializeStud() {
	StudentP new = NULL;
	new = (StudentP)malloc(sizeof(Student));
	if (NULL == new) {
		printf("\nMemory allocation error!\n");
		return NULL;
	}
	strcpy(new->firstName, "");
	strcpy(new->lastName, "");
	new->subject1 = 1;
	new->subject2 = 1;
	new->subject3 = 1;
	new->next = NULL;

	return new;
}

int ReadFile(StudentP head, char* file, int whichList) {
	FILE* fp = NULL;
	char firstName[MAX_NAME] = "";
	char lastName[MAX_NAME] = "";
	int grade = 1;
	StudentP new = NULL;

	fp = fopen(file, "r");
	if (NULL == fp) {
		printf("\nReading file error!\n");
		return EXIT_FAILURE;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", lastName, firstName, &grade);
		new = InitializeStud();
		new = CreateStud(firstName, lastName, grade, whichList);
		AddToFront(head, new);
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

StudentP CreateStud(char* firstName, char* lastName, int grade, int whichList) {
	StudentP new = NULL;
	new = (StudentP)malloc(sizeof(Student));
	if (!new) {
		printf("\nMemory allocation error!\n");
		return NULL;
	}
	new = InitializeStud();
	strcpy(new->firstName, firstName);
	strcpy(new->lastName, lastName);
	new->next = NULL;

	if (whichList == 1)
		new->subject1 = grade;
	else if (whichList == 2)
		new->subject2 = grade;
	else if (whichList == 3)
		new->subject3 = grade;

	return new;
}

int AddToFront(StudentP head, StudentP new) {
	StudentP temp = head;
	new->next = head->next;
	head->next = new;

	return EXIT_SUCCESS;
}

int PrintList(StudentP head) {
	StudentP t = head->next;
	while (NULL != t) {
		printf(" %s %s (%d, %d, %d)\n", t->lastName, t->firstName, t->subject1, t->subject2, t->subject3);
		t = t->next;
	}
	printf("\n\n");

	return EXIT_SUCCESS;
}

int DeleteList(StudentP head) {
	StudentP t = NULL;
	while (NULL != head->next) {
		t = head->next;
		head->next = t->next;
		free(t);
	}

	return EXIT_SUCCESS;
}