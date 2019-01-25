#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./util/stack.h"

Stack *stack;
char *converse_formula(char*); // 中缀表达式转换为后缀表达式
int cal_formula(char*); // 计算后缀表达式
char *calculate_nums(int, int, char);
int converse_char_int(char);
char *converse_int_char(int);

/*
* 局限性：算数式只支持正个位数，且中间结果也只能是个位数。
* 0:48  9:57  (int:ascII)
* 将中缀运算式子转化位后缀运算式子，并计算
* 仅支持输入的数字为正个位数进行计算。涉及多位数和小数则需要使用词法分析
* ref: https://songlee24.github.io/2014/10/10/arithmetic-expression-02/
*/
int main(int argc, char const *argv[])
{
    stack = create_stack();
    char formula[MAXSIZE] = "(2+1)*2/(4-2/1) \0";
    printf("原式为: %s\n", formula);
    char *formula_prefix, *formula_converse;
    formula_prefix = (char *)malloc(MAXSIZE*sizeof(char));
    formula_prefix = converse_formula(formula);
    int res = cal_formula(formula_prefix);
    printf("变为后缀式为%s = %d\n", formula, res);
    return 0;
}

// (a+b)*c*(d-e/f) 中缀
// ab+c*def/-*  后缀
char *converse_formula(char* formula){
    char *formula_converse = (char *)malloc(MAXSIZE*sizeof(char));
    int i=0;
    int j=0;
    while(formula[i] != '\0'){
        if(formula[i] >= '0' && formula[i] <= '9'){ // 1. 若表达式中是数字则放入tempstr中
            formula_converse[j++] = formula[i];
        } else if(formula[i] == '('){  // 2. 若表达式中是'('入栈
            push(stack, &formula[i]);
        }else if(formula[i] == ')'){ // 3. 若表达式中是')'将左括号上方的全部出栈
            while(!isEmpty(stack)){
                if(*(int *)getTop(stack) != '('){
                    formula_converse[j++] = *(char *)pop(stack);
                }else{
                    pop(stack);
                    break;
                }
            }
        }else if(formula[i] == '+' || formula[i] == '-'){ // 4.若有+或-则把优先级高的或等于的运算符出栈 
            while(!isEmpty(stack)){
                char op = *(char *)getTop(stack);
                if(op == '+' || op == '-' || op == '*' || op == '/'){
                    formula_converse[j++] = *(char *)pop(stack);
                }
                else
                    break;
            }
            push(stack, &formula[i]);
        }else if(formula[i] == '*' || formula[i] == '/'){ // 5.若有*或/则把优先级高的或等于的运算符出栈 
            while(!isEmpty(stack)){
                char op = *(char *)getTop(stack);
                if(op == '*' || op == '/'){
                    formula_converse[j++] = *(char *)pop(stack);
                }
                else
                    break;
            }
            push(stack, &formula[i]);
        }
        i++;
    }
    while(!isEmpty(stack)){
        char op = *(char *)getTop(stack);
        formula_converse[j++] = *(char *)pop(stack);
    }
    // 标志式子已结束
    formula[i] = '\0';
    strcpy(formula, formula_converse);
    return formula;
}

int cal_formula(char *formula){
    int i=0;
    int res = 0;
    Stack *nums = create_stack();
    while(formula[i] != '\0'){
        // printf("formula[i] is %c\n", formula[i]);
        if(formula[i] >= '0' && formula[i] <= '9'){
            push(nums, &formula[i]);
        }else if(formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/'){
            int num1 = converse_char_int(*(char *)pop(nums));
            int num2 = converse_char_int(*(char *)pop(nums));
            // printf("%d \n", num1);
            // printf("--------->>>>>>>>> cal: %d %c %d=%d\n", num2, formula[i], num1, converse_char_int(calculate_nums(num1, num2, formula[i])));
            push(nums, calculate_nums(num1, num2, formula[i]));
        }
        i++;
    }
    return converse_char_int(*(char *)pop(nums));
}

char *calculate_nums(int num1, int num2, char operator){
    int tempRes = 0;
    switch(operator){
        case '+': tempRes = num2 + num1;break;
        case '-': tempRes = num2 - num1;break;
        case '*': tempRes = num2 * num1;break;
        case '/': tempRes = num2 / num1;break;
        default: 
            printf("operator: %c error! \n", operator);
            tempRes = -1;
        break;
    }
    return converse_int_char(tempRes);
}

int converse_char_int(char c){
    if(c < '0' || c > '9'){
        puts("char转int不能传非数! \n");
        return -1;
    }
    return c - '0';
}

// only converse 0-9
char *converse_int_char(int n){
    char *str;
    *str = n % 10 + '0';
    n /= 10;
    return str;
}


// char *converse_formula(char* formula, char *formula_converse){
//     // warn 不能返回temp，因为temp的地址仅仅只是在该方法内部的一个变量，到main线程中就不在了
//     char temp[MAXSIZE];
//     formula[0] = '-';
//     formula[1] = '+';
//     formula[2] = '\0';
//     return formula;
// }