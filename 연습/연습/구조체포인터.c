#include <stdio.h>

struct Example
{
	int num;
	char def;
};

int main()
{
	struct Example* p;
	p = malloc(sizeof(struct Example));

	p->num = 10;
	p->def = 'A';

	printf("&num : %p\n&def : %p\nnum : %d\ndef : %c\n&p : %p\np : %p\n\n", &(p->num), &(p->def), p->num, p->def, &p, p);
}