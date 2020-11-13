#include<stdio.h>
#include<iostream>
#include <stdio.h>
#include <string.h>
#define COMP_MSG(x,y) (strncmp(x,y,sizeof(y))==0)?(1):(0)

char str1[] = {"hi"};
char str2[] = {"hi"};

int main(){
    std::cout << COMP_MSG(str1,str2);
    return 0;
}