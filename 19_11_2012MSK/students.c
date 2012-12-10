#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_GRADE 10
#define MAX_NAME_LEN 32

typedef struct
{
	char name[MAX_NAME_LEN];
	int group;
	int grade;
}Student;

void print_student_list(Student *students, List *list)
{
	Node *node = NULL;
	if (list->size == 0)
		return;
	node = list->first;
	while(node)
	{
		printf("%s %d %d\n", students[node->value].name, students[node->value].group, 
			students[node->value].grade);
		node = node->next;
	}
}	

int main()
{
	int n, i;
	List grades[MAX_GRADE];
	Student *student_list= NULL;
	memset(&grades, 0, sizeof(grades));
	scanf("%d", &n);
	student_list = (Student *)calloc(n, sizeof(Student));
	if (!student_list)
		return -1;
	for (i = 0; i < n; ++i)
	{
		scanf("%s%d%d", student_list[i].name, &student_list[i].group, 
			&student_list[i].grade);
		list_push_back(&grades[student_list[i].grade - 1], i); 
	}
	printf("Sorted list of students:\n");
	for (i = 0; i < MAX_GRADE; ++i)
		print_student_list(student_list, &grades[i]);
	for (i = 0; i < MAX_GRADE; ++i)
		list_clear(&grades[i]);
	free(student_list);
	return 0;
}
