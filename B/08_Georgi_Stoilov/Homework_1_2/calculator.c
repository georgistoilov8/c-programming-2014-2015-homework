#include <limits.h>
#include <stdlib.h>
#include<limits.h>

#define STARTING_S 5

struct stack_t {
	int *data, top, size;
};

void stack_init(struct stack_t*);
void stack_destroy(struct stack_t*);
int stack_get_size(struct stack_t*);
int stack_increase_size(struct stack_t*);
int stack_reduce_size(struct stack_t*);
int stack_resize(struct stack_t*);
void transfer_data(int*, int, int*);
void stack_push(struct stack_t*, int value);
int stack_pop(struct stack_t*);
void stack_copy(struct stack_t *from, struct stack_t *to);
char *input_string(char string[1000]);
int polish_notation(struct stack_t *,char string[1000]);

int main(){
	struct stack_t op_stack;
	char math_expression[1000];
	int result;
	input_string(math_expression);
	stack_init(&op_stack);
	polish_notation(&op_stack, math_expression);
	if(result == INT_MIN){
		printf("Wrong values!\n");
	}else if(result == INT_MAX){
		
		printf("Too many values!\n");
	}else {
		printf("%d\n", result);
	}
	stack_destroy(&op_stack);
	return 0;
}

char *input_string(char string[1000]){
	scanf("%s", string);	
	return string;
}

void stack_init(struct stack_t* s) {
	s->size = STARTING_S;
	s->top = 0;
	s->data = (int*) malloc(s->size * sizeof(int));
	
}

void stack_destroy(struct stack_t* s){
	free(s->data);
	s->size = 0;
	s->top = 0;
}

int stack_get_size(struct stack_t *stack) {
	return stack->top;
}

void stack_push(struct stack_t* s, int value) {
	if (s->top == s->size)
		stack_increase_size(s);

	s->data[s->top++] = value;
}

int stack_pop(struct stack_t* stack) {
	 if(stack->top != 0) 
    {
        --stack->top;
        if(stack->size > STARTING_S)
        {
            stack_resize(stack);
        }
        return stack->data[stack->top];
    }
    else 
    {
        return INT_MIN; 
    }
}

void transfer_data(int *old_data, int old_data_size, int *new_data)
{
	int i;
	for(i = 0; i < old_data_size; ++i)
		new_data[i] = old_data[i];
}

//returns: 0 if it worked out OK and -1 if something went wrongZ
int stack_increase_size(struct stack_t *s)
{
	s->size *= 2;

	if(stack_resize(s) == -1)
		return -1;

	return 0;
}

//returns: 0 if it worked out OK and -1 if something went wrong
int stack_reduce_size(struct stack_t *s)
{
	s->size /= 2;

	if(stack_resize(s) == -1)
		return -1;

	return 0;
}

//returns: 0 if it worked out OK and -1 if something went wrong
int stack_resize(struct stack_t *stackk)	
{	
	int *new_data,new_size,counter;
    if(stackk->top == stackk->size)
    {
        new_size = stackk->size * 2;
        new_data = (int*) malloc(new_size * sizeof(int));
        for(counter = 0; counter < stackk->size; counter++)
        {   
            new_data[counter] = stackk->data[counter];
        }
        free(stackk->data);
        stackk->data = new_data;
        stackk->size = new_size;
    }
    else if(stackk->top < (stackk->size)/2)
    {
        stackk->size /= 2;
        new_data = (int*) malloc(stackk->size * sizeof(int));
        for(counter = 0; counter < stackk->size; counter++)
        {
            new_data[counter] = stackk->data[counter];
        }
        free(stackk->data);
        stackk->data = new_data;
    }
}

void stack_copy(struct stack_t *from, struct stack_t *to)
{
	to->data = (int*)malloc(from->size * sizeof(int));
	transfer_data(from->data, from->size, to->data);
	to->size = from->size;
	to->top = from->top;
}

int polish_notation(struct stack_t *stack ,char string[1000]){
	int result, value, count, first_value, second_value;
	for(count = 0; string[count] != '\0'; count++){
		if(string[count] >= 0 && string[count] <= 9){
			value = string[count] - '0';
			
		}else if(string[count] == '+' || string[count] == '-' ||string[count] == '*' || string[count] == '/'){
			if(stack_get_size(stack) < 2){
				return INT_MIN;
			}else  {
				second_value = stack_pop(stack);
				first_value = stack_pop(stack);
				switch(string[count]){
					case '+':
						result = first_value + second_value;
						break;
					case '-':
						result = first_value - second_value;
						break;
					case '*':
						result = first_value * second_value;
						break;
					case '/':
						result = first_value / second_value;
						break;
				}  
				
			}
		}
	}
	if(stack_get_size(stack) == 2){
		return result;
	}else {
		return INT_MAX;
	}
}
