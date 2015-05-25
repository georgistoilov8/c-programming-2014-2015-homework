#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// index, size, data

// [0, 0, 0, 0, 0]
// [0, -1, -2, -3, -4 ...]

#define STARTING_SIZE 5

struct vector_t {
	int *data;
	int index, size;
};

void vector_init(struct vector_t*);
void vector_destroy(struct vector_t*);
int vector_get_size(struct vector_t);
int vector_increase_size(struct vector_t*);
int vector_reduce_size(struct vector_t*);
int vector_resize(struct vector_t*);
void transfer_data(int*, int, int*);
int vector_at(struct vector_t, int index);
void vector_push_back(struct vector_t*, int value);
int vector_pop_back(struct vector_t*);
void vector_copy(struct vector_t *from, struct vector_t *to);

int main() 
{
	struct vector_t v;
	vector_init(&v);

	vector_push_back(&v, 3);
	vector_push_back(&v, 5);

	struct vector_t v2;
	vector_copy(&v, &v2);

	printf("\n");
	printf("Pushing into the vector:\n");

	int i;
	for (i = 0; i < 20; ++i)
	{
		vector_push_back(&v2, i + 1);

		if(i % 5 == 0)
			printf("vector_index: %d, vector_size: %d\n", v2.index, v2.size); //to demonstrate that the size doubles
	}

	printf("\n");
	printf("Popping out of the vector:\n");

	for (i = 0; i < 22; ++i)
	{
		printf("Pop: %d\n", vector_pop_back(&v2));

		if(i % 5 == 0)
			printf("vector_index: %d, vector_size: %d\n", v2.index, v2.size); // to demonstrate that the size reduces
	}

	vector_destroy(&v);
	vector_destroy(&v2);

	return 0;
}

void vector_init(struct vector_t* v) {
	v->size = STARTING_SIZE;
	v->index = 0;
	v->data = (int*) malloc(v->size * sizeof(int));
}

void vector_destroy(struct vector_t* v){
	free(v->data);
	v->size = 0;
	v->index = 0;
}

int vector_get_size(struct vector_t v) {
	return v.index;
}

void vector_push_back(struct vector_t* v, int value) {
	if (v->index == v->size)
		vector_increase_size(v);

	v->data[v->index++] = value;
}

int vector_at(struct vector_t v, int index) {
	if(index < 0 || index >= v.size)
		return INT_MIN; //for error returns the minimum value of int, because it is the least possible number to actually be in the vector

	return v.data[index];
}

int vector_pop_back(struct vector_t* v) {
	if(v->index == 0)
		return INT_MIN; //for error returns the minimum value of int, because it is the least possible number to actually be in the vector

	if(v->index <= v->size / 2 && v->size > STARTING_SIZE)
		vector_reduce_size(v);

	return v->data[--v->index];
}

void transfer_data(int *old_data, int old_data_size, int *new_data)
{
	int i;
	for(i = 0; i < old_data_size; ++i)
		new_data[i] = old_data[i];
}

//returns: 0 if it worked out OK and -1 if something went wrongZ
int vector_increase_size(struct vector_t *v)
{
	v->size *= 2;

	if(vector_resize(v) == -1)
		return -1;

	return 0;
}

//returns: 0 if it worked out OK and -1 if something went wrong
int vector_reduce_size(struct vector_t *v)
{
	v->size /= 2;

	if(vector_resize(v) == -1)
		return -1;

	return 0;
}

//returns: 0 if it worked out OK and -1 if something went wrong
int vector_resize(struct vector_t *v)	
{	
	int *new_data = (int*)malloc(sizeof(int) * v->size);

	transfer_data(v->data, v->size, new_data);

	free(v->data);
	v->data = new_data;

	if(v->data == NULL)
		return -1;

	return 0;
}

void vector_copy(struct vector_t *from, struct vector_t *to)
{
	to->data = (int*)malloc(from->size * sizeof(int));
	transfer_data(from->data, from->size, to->data);
	to->size = from->size;
	to->index = from->index;
}
