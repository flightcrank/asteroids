
//vector.c

#include <stdio.h>
#include <math.h>
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

void divide_vector(struct vector2d* v, float n) {

	v->x /= n;
	v->y /= n;
}

void print_vector(struct vector2d* a) {
	
	printf("x = %f\n y = %f\n", a->x, a->y);
}

float magnitude_vector(struct vector2d* v) {
	
	float c2 = pow(v->x, 2) + pow(v->y, 2); 

	return sqrt(c2);
}

void normalise_vector(struct vector2d* v) {

	float mag = magnitude_vector(v);

	divide_vector(v, mag);
}

void limit_vector(struct vector2d* v, float limit) {
	
	float mag = magnitude_vector(v);

	if (mag > limit) {
		
		float ratio = limit / mag;
		v->x *= ratio;
		v->y *= ratio;
	}
}

void rotate_vector(struct vector2d* v, float degrees) {
	
	//calculate radians
	float angle = degrees * M_PI / 180;
	float sine = sin(angle);
	float cosine = cos(angle);
	
	//rotation matix
	float matrix[2][2] = {{cosine, -sine}, {sine, cosine}};

	float x = v->x;
	float y = v->y;

	v->x = matrix[0][0] * x + matrix[0][1] * y;
        v->y = matrix[1][0] * x + matrix[1][1] * y;
}

