
//vector.h

struct vector2d {
	
	float x;
	float y;
};

void add_vector(struct vector2d* a, struct vector2d* b);

void multiply_vector(struct vector2d* v, float n);

void print_vector(struct vector2d* a);
