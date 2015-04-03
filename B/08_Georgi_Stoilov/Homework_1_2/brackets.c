 #include <stdio.h>


int init_brackets();
int check_brackets();

struct stack{
	char br[1000];
	int top;
};

typedef struct stack STACK;
STACK s;


int main(){
	char brackets[1000];
	int i;
	init_brackets(brackets);
	check_brackets(brackets);
	return 0;
}


int init_brackets(char brackets[1000]){
	printf("Please input only parentheses\n");
	scanf("%s", brackets);
}

int check_brackets(char brackets[1000]){
	int i;
	int count = 0;
	for(i = 0; brackets[i] != '\0'; i++){
		if(brackets[0] == '}' || brackets[0] == ')' || brackets[0] == ']'){
			printf("The parentheses are not balanced.\n");
			return -1;
		}
		if(brackets[i] == '{'){
			s.top = s.top + 1;
			s.br[s.top] = brackets[i];
			count += 1;
		}else if(brackets[i] == '}'){
			if(s.top != 0 || s.top == '{'){
				brackets[i] = s.br[s.top];
				s.top = s.top - 1;
				count -= 1;
			}else {
				printf("The parentheses are not balanced.\n");
				return -1;
			}
		}
		if(brackets[i] == '['){
			s.top = s.top + 1;
			s.br[s.top] = brackets[i];
			count += 1;
		}else if(brackets[i] == ']'){
			if(s.top == 0 || s.top != '['){
				brackets[i] = s.br[s.top];
				s.top = s.top - 1;	
				count -= 1;
			}else{
				printf("The parentheses are not balanced.\n");
				return -1;
			}
		}
		if(brackets[i] == '('){
			s.top = s.top + 1;
			s.br[s.top] = brackets[i];
			count += 1;
		}else if(brackets[i] == ')'){
			if(s.top == 0 || s.top != '('){
				brackets[i] = s.br[s.top];
				s.top = s.top - 1;
				count -= 1;
			}else {
				printf("The parentheses are not balanced.\n");
				return -1;
			}
		}
	}
	if(s.top == 0 && count == 0){
		printf("The parentheses are balanced\n");
		return 0;
	}else {
		printf("The parentheses are not balanced.\n");
		return -1;
	}
}
