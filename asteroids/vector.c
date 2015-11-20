
//vector.c

#include <stdio.h>
#include "vector.h"

void add_vector(struct vector2d* a, struct vector2d* b) {

	a->x += b->x;
	a->y += b->y;
}

struct vector2d add_vector_new(struct vector2d* a, struct vector2d* b) {

	struct vector2d new = {a->x + b->x, a->y + b->y};

	return new;
}

void multiply_vector(struct vector2d* v, float n) {

	v->x *= n;
	v->y *= n;
}

void print_vector(struct vector2d* a) {
	
	printf("x = %f\n y = %f\n", a->x, a->y);
}

