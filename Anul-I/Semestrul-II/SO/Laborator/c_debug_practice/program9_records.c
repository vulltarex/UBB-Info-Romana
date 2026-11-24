#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *id;
    double score;
} Record;

Record *make_records(int n);
void fill_records(Record *r, int n);
double max_score(Record *r, int n);

Record *make_records(int n)
{
    Record *r = malloc(n * sizeof(Record));
    if (!r)
    {
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        r[i].id = malloc(12);
        r[i].score = 0.0;
    }
    return r;
}

void fill_records(Record *r, int n)
{
    for (int i = 0; i < n; i++)
    {
        snprintf(r[i].id, 12, "R%d", i);
        r[i].score = i * 1.5;
    }
}

double max_score(Record *r, int n)
{
    double best = 0.0;
    for (int i = 0; i < n; i++)
    {
        if (r[i].score > best)
        {
            best = r[i].score;
        }
    }
    if (n > 0)
    {
        return best;
    }
    return 0;
}

int main(void)
{
    int n = 3;
    Record *r = make_records(n);
    char *desc = malloc(8);

    if (!r || !desc)
    {
        return 1;
    }

    strcpy(desc, "report");
    fill_records(r, n);
    printf("max=%lf\n", max_score(r, n));
    printf("%s\n", desc);

    for(int i = 0; i < n; i++)
    {
	    free(r[i].id);
    }
    free(r);
    free(desc);

    puts("records");

    return 0;
}
