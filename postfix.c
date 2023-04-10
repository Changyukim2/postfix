#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}Stacktype;

void init_stack(Stacktype* s) {

	s->top = -1;
}

int is_empty(Stacktype* s) {

	return (s->top == -1);

}
int is_full(Stacktype* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}


void push(Stacktype* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;

}

element pop(Stacktype* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}


element peek(Stacktype* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
void check_error(char exp[]) {
	int err = -1;
	int len = strlen(exp);

	for (int i = 0; i < len; i++) {
		if (i + 1 < len && exp[i] == '/' && exp[i + 1] == '0') {
			printf("<error 발생>\n");
			err = 0;
			break;
		}
	}
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (exp[i] == '(') {
			count++;
		}
		else if (exp[i] == ')') {
			count--;
		}
	}
	if (count > 0) {
		printf("<error 발생>\n");
		err = 1;
	}
	else if (count < 0) {
		printf("<error 발생>\n");
		err = 1;
	}

	for (int i = 0; i < len; i++) {
		if (exp[i] == '(' || exp[i] == ')') {
			continue;
		}
		else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
			continue;
		}
		else if ('0' <= exp[i] && exp[i] <= '9') {
			continue;
		}
		else {
			printf("<<error 발생>>\n");
			err = 1;
		}
	}
	}
	

int eval(char exp[]) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	Stacktype s;

	init_stack(&s);
	
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';
			push(&s, value);
		}
		else   {
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) {
			case'+':push(&s, op1 + op2); break;
			case'-':push(&s, op1 - op2); break;
			case'*':push(&s, op1 * op2); break;
			case'/':push(&s, op1 / op2); break;
			}
		}
		
		
	}
	return pop(&s);
}
int main(void) {
	int result;
	char express[100];
	
	printf("수식을 입력하세요: ex)23+4*9+\n");
	gets_s(express, 100);
	check_error(express);
	result = eval(express);
	 printf("결과값: %d\n", result);
	return 0;
}
