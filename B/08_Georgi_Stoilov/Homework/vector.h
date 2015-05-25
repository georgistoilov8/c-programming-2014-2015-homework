#ifndef VECTOR_H
#define VECTOR_H

struct vector_t {
 int *data;
 int index, size;
};

void v_init(struct vector_t *v);
void v_destroy(struct vector_t *v);
int v_get_size(struct vector_t v);
void v_resize(struct vector_t *v);
int v_at(struct vector_t v, int index);
void v_push(struct vector_t *v, int value);
int v_pop(struct vector_t *v);
void vector_copy(struct vector_t* from, struct vector_t* to);

#endif
