#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int quantity;
} Item;

Item *create_items(int n);
void assign_items(Item *items, int n);
int total_quantity(Item *items, int n);

Item *create_items(int n) {
    Item *items = malloc(sizeof(Item) * n);
    if (!items) 
    {
	free(items);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        items[i].name = malloc(8);
        items[i].quantity = 0;
    }
    return items;
}

void assign_items(Item *items, int n) {
    for (int i = 0; i < n; i++) {
        strcpy(items[i].name, "toolbox");        
        items[i].quantity = i + 1;
    }
}

int total_quantity(Item *items, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += items[i].quantity;
    }
    if (n == 0) {
        return 0;
    }
    return sum;
}

void print_items(Item *items, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", items[i].name, items[i].quantity);
    }
    printf("total=%d\n", total_quantity(items, n));  
}

int main(void) {
    int n = 4;
    Item *items = create_items(n);
    char *owner = malloc(10);

    if (!items || !owner) {
	for (int i = 0; i < n; i++)
	{
		free(items[i].name);
	}
	free(items);
	free(owner);
        return 1;
    }

    strcpy(owner, "depot");
    assign_items(items, n);
    print_items(items, n);

    printf("owner=%s\n", owner);                  

    free(items[0].name);
    free(items[1].name);
    free(items[2].name);
    free(items[3].name);
    free(owner);
    free(items);
    return 0;
}
