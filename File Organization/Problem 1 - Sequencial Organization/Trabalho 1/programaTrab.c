//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include <stdio.h>
#include "CREATE_TABLE.h"
#include "SELECT.h"
#include "INSERT_INTO.h"

int main() {

    char c;
    scanf("%c", &c);

    if(c == '1') CREATE_TABLE(c); 
    else if(c == '2') CREATE_TABLE(c);
    else if(c == '3') SELECT_FROM(c);
    else if(c == '4') SELECT_FROM(c);
    else if(c == '5') SELECT_WHERE(c);
    else if(c == '6') SELECT_WHERE(c);
    else if(c == '7') INSERT_INTO(c);
    else if(c == '8') INSERT_INTO(c);

    return 0;
}