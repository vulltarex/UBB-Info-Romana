#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    int grade;
} Student;

Student *create_students(int n);
void load_students(Student *s, int n);
float average_grade(Student *s, int n);

Student *create_students(int n)
{
    Student *list = malloc(n * sizeof(Student));
    if (list == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        list[i].name = malloc(16);
	if(list[i].name == NULL)
	{
		for (int j = 0; j < i; j++)
		{
			free(list[j].name);
		}
		free(list);
		return NULL;
	}
        list[i].grade = 0;
    }

    return list;
}

void load_students(Student *s, int n)
{
    for (int i = 0; i < n; i++)
    {
        snprintf(s[i].name, 16, "S%d", i);
        s[i].grade = 10 + i;
    }

}

float average_grade(Student *s, int n)
{
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        total += s[i].grade;
    }
    if (n > 0)
    {
        return (float)total / n;
    }
    return 0;
}

void show_students(Student *s, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s -> %d\n", s[i].name, s[i].grade);
    }
    printf("avg: %.2f\n", average_grade(s, n));
}

int main(void)
{
    int count = 3;
    Student *group = create_students(count);
    char *note = malloc(20);

    if (group == NULL || note == NULL)
    {
	free(group);
	free(note);
        return 1;
    }

    strcpy(note, "classroom");
    load_students(group, count);
    show_students(group, count);

    printf("done\n");

    free(group[0].name);
    free(group[1].name);
    free(group[2].name);
    free(group);
    free(note);
    return 0;
}
