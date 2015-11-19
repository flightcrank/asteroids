
//vector.c

#include <stdio.h>
#include "vector.h"

void add_vector(struct vector2d* a, struct vector2d* b) {

	a->x += b->x;
	a->y += b->y;
}

void multiply_vector(struct vector2d* v, float n) {

	v->x *= n;
	v->y *= n;
}

void print_vector(struct vector2d* a) {
	
	printf("x = %f\n y = %f\n", a->x, a->y);
}

