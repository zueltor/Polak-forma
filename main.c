#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LStack Node;
struct LStack {
    char data;
    struct LStack *next;
};

void push(Node **top, int data) {
    Node *tmp = malloc(sizeof(Node));
    tmp->data = data;
    tmp->next = *top;
    *top = tmp;
}

int pop(Node **top) {
    Node *temp;
    temp = *top;
    *top = (*top)->next;
    int data = temp->data;
    free(temp);
    return data;
}

int top(Node *top) {
    return (top->data);
}

int isempty(Node *top) {
    if (top == NULL)
        return 1;
    return 0;
}

void into_polak(char *s, char *res) {
    char pr[256];
    int i = 0, j = 0;
    int tmp;
    Node *stack = NULL;
    pr['('] = pr[')'] = 1; //priorities
    pr['+'] = pr['-'] = 2;
    pr['*'] = pr['/'] = 3;
    while (s[i] != '\0') {
        if (s[i] >= 'a' && s[i] <= 'z') { // либо if (s[i] >= '0' && s[i] <= '9') {
            res[j++] = s[i];
        } else if (s[i] == '(')
            push(&stack, '(');
        else if (s[i] == ')') {
            while ((tmp = pop(&stack)) != '(')
                res[j++] = tmp;
        } else {
            while (!isempty(stack) && (pr[top(stack)] >= pr[s[i]]))
                res[j++] = pop(&stack);
            push(&stack, s[i]);
        }
        i++;
    }
    while (!isempty(stack)) {
        res[j++] = pop(&stack);
    }
}

int value_polak(char *res) {
    int j = 0;
    Node *stack;
    int a, b, op;
    while (res[j] != '\0') {
        if (res[j] >= '0' && res[j] <= '9') {
            push(&stack, res[j] - '0');
        } else {
            b = pop(&stack);
            a = pop(&stack);
            op = res[j];
            switch (op) {
                case '*' :
                    push(&stack, a * b);
                    break;
                case '/':
                    push(&stack, a / b);
                    break;
                case '+':
                    push(&stack, a + b);
                    break;
                case '-':
                    push(&stack, a - b);
                    break;
                default:
                    printf("F");
            }
        }
        j++;
    }
    return pop(&stack);
}

int main(void) {

    char s[] = "a+(f-b*c/(z-x)+y)/(a*r-k)"; // либо с цифирками, не переменными, тогда поменять 46 строчку
    char res[100] = {0};
    into_polak(s, res);

    printf("%s\n", res);
    strset(res, 0);

    strcpy(res, "523*42/-4/+1-");

    printf("%d\n", value_polak(res));

    return 0;

}