#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void v_init(struct vector_t *v) 
{
 v->size = 40;
 v->index = 0;
 v->data = (int*) malloc(v->size * sizeof(int));
}

void v_destroy(struct vector_t *v)
{
 free(v->data);
 v->size = 0;
 v->index = 0;
}

int v_get_size(struct vector_t v)
{
 return v.index;
}

int v_at(struct vector_t v, int index)
{
 if ((v.index >=0) && (v.index < v.size))
  return v.data[index];
}

void v_resize(struct vector_t* v) {
    int *new_data = (int*)malloc(sizeof(int) * v->size);
    if (v->index >= v->size)
        v->size *= 2;
    else if (v->index <= v->size/2 + 1)
        v->size /= 2;
}

void v_push(struct vector_t* v, int value)
{

 if (v->index == v->size )
  v_resize(v);
 v->data[v->index++] = value;
}

int v_pop(struct vector_t* v) 
{
 if(v->index > 0)
  return v->data[--v->index];
}



void vector_copy(struct vector_t* from, struct vector_t* to)
{
    to->size = from->size;
    to->index = 0;
    to->data = (int*) malloc(from->size * sizeof(int));

    int i;
    for (i = 0; i < from->size; i++)
  	v_push(to, from->data[i]);
}

int main(){
	struct vector_t v;
	v_init(&v);

	v_push(&v, 3);
	v_push(&v, 5);

	struct vector_t v2;
	vector_copy(&v, &v2);
	printf("%d\n", v2.data[0]);

	printf("\n");
	printf("Pushing into the vector:\n");

	int i;
	for(i = 0; i < 20; ++i){
		v_push(&v2, i+1);
	
		if(i % 5 == 0)
			printf("vector_index:%d, vector_size:%d\n", v2.index, v2.size);
	}
	
	printf("\n");
	printf("Popping out of the vector:\n");

	for(i = 0; i < 22; ++i){
		printf("Pop: %d\n", v_pop(&v2));

		if(i % 5 == 0)
			printf("vector_index:%d, vector_size:%d\n", v2.index, v2.size);
	}
	printf("asb\n");
	v_destroy(&v);
	printf("bcs\n");
	v_destroy(&v2);
	printf("bcasds\n");
	return 0;
}
