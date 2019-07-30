//
//  main.c
//  fastcam
//
//  Created by 최민규 on 29/07/2019.
//  Copyright © 2019 최민규. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct Node {
    char data[50];
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

char* getPop(Stack *stack);
char* pop(Stack *stack);
void push(Stack *stack, char *data);
void showAll(Stack *stack);
int isContained(char *str, int args, ...);
int getPriority(char *str);
char* getAddedStr(char *str);
int getLength(char *data);
char* translation(Stack *stack, char **data, int count);

int main(int argc, const char * argv[]) {
    
    // insert code here...
    Stack stack;
    stack.top = NULL;
    
    char a[100] = "( 5 + 3 ) / 2";
    int count = (int) (strlen(a) + 1) / 2;
    
    char *pt = strtok(a, " ");
    char **dpt = (char**) malloc(sizeof(char*) * count);
    
    for (int i = 0; i < count; i++) {
        dpt[i] = (char*) malloc(sizeof(char) * 100);
    }
    
    for (int i = 0; i < count; i++) {
        strcpy(dpt[i], pt);
        pt = strtok(NULL, " ");
    }
    
    for (int i = 0; i < count; i++) {
        printf("%s\n", dpt[i]);
    }
    
    char *res = translation(&stack, dpt, count);
    
    printf("후위 표기법: %s\n", res);
    
    return 0;
}

/**
 *
 * 스택 pop 반환 시 반환될 객체값 반환
 * 실제로 pop 동작을 하진 않고 pop 동작시 반환될 객체값만 반환된다.
 *
 * @param stack 스택 자료구조
 *
 * @return res 스택 pop 동작시 반환될 값
 */
char* getPop(Stack *stack) {
    return stack->top->data;
}

/**
 * 스택의 데이터 하나를 꺼내는 함수
 *
 * @param stack stack LIFO 자료구조
 * @return char data 마지막 인덱스의 값 반환
 */
char* pop(Stack *stack) {
    
    if (stack->top == NULL) {
        printf("스택 언더플로우가 발생하였습니다.\n");
        return NULL;
    }
    
    Node *node = stack->top;
    char* data = node->data;
    stack->top = node->next;
    
    free(node);
    
    return data;
}

/**
 * 입력받은 스택의 데이터 삽입 함수
 *
 * @param stack LIFO 자료구조
 * @param data 삽입할 값
 */
void push(Stack *stack, char *data) {
    Node *node = (Node*) malloc(sizeof(Node));
    strcpy(node->data, data);
    node->next = stack->top;
    stack->top = node;
}

/**
 *
 * 입력받은 스택에 담겨있는 모든 문자열을 순차적으로 출력
 *
 * @param stack 스택 자료구조
 */
void showAll(Stack *stack) {
    Node *node = stack->top;
    
    printf("----- show all -----\n");
    
    while (node != NULL) {
        printf("%s\n", node->data);
        node = node->next;
    }
    
    printf("----- /show all -----\n");
}

/**
 *
 * 입력받은 문자열이 가변인자 문자열들 중 포함되어있는지 여부 반환
 *
 * @param str 입력 문자열
 * @param args 가변인자 갯수
 * @param .... 가변인자
 */
int isContained(char *str, int args, ...) {
    int isResult = 0; // 포함 여부
    
    va_list ap;
    
    va_start(ap, args);
    
    for (int i = 0; i < args; i++) {
        char *charArr = va_arg(ap, char*);
        
        if (!strcmp(str, charArr)) {
            isResult = 1;
            break;
        }
    }
    
    va_end(ap);
    
    return isResult;
}

/**
 *
 * 입력받은 문자열의 연산자 우선순위 반환
 *
 * @param str 문자열
 */
int getPriority(char *str) {
    int priority = 0;
    
    if (isContained(str, 2, "(", ")")) {
        priority = 0;
    } else if (isContained(str, 2, "+", "-")) {
        priority = 1;
    } else if (isContained(str, 2, "*", "/")) {
        priority = 2;
    } else {
        priority = 3;
    }
    
    return priority;
}

char* getAddedStr(char *str) {
    strcat(str, " ");
    return str;
}

// 중위 표기법 문자열의 길이 반환
int getLength(char *data) {
    return (int) (strlen(data) + 1) / 2;
}

/**
 *
 * 중위 표기법 연산자를 후위 표기법 연산자로 변환하여 반환한다.
 *
 * @param stack 스택 자료구조
 * @param data 2차원 포인터 문자 배열
 * @param count 2차원 문자열 사이즈
 *
 * @return res 후위표기법
 */
char* translation(Stack *stack, char **data, int count) {
    char *res = (char*) malloc(sizeof(char) * count + 1);
    
    for (int i = 0; i < count; i++) {
        char *str = data[i];
        
        if (isContained(str, 4, "-", "+", "*", "/")) {
            
            if (stack->top != NULL && getPriority(getPop(stack)) > getPriority(str)) {
                strcat(res, pop(stack));
            }
            
            push(stack, str);
        } else if (!strcmp(str, "(")) {
            push(stack, str);
        } else if (!strcmp(str, ")")) {
            
            while (strcmp(getPop(stack), "(")) {
                strcat(res, getAddedStr(pop(stack)));
            }
            
            pop(stack);
        } else {
            strcat(res, getAddedStr(str));
        }
    }
    
    while (stack->top != NULL) {
        strcat(res, getAddedStr(pop(stack)));
    }
    
    return res;
}
