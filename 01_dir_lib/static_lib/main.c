/* 调用模块 */
#include <stdio.h>
// #include "calc.h"
// #include "show.h"
#include "math.h"

int main(void){
    int a = 123, b = 456;
    int res = add(a, b);
    show(a, '+', b, res);
    show(a, '-', b, sub(a, b));
}

