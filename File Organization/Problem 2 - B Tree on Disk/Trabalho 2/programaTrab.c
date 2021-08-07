//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include <stdio.h>
#include "CREATE_INDEX.h"
#include "RECOVER_DATA.h"
#include "INSERT.h"

int main() {

    int c;
    scanf("%d", &c);

    if(c == 9) CREATE_INDEX(c); 
    else if(c == 10) CREATE_INDEX(c);
    
    else if(c == 11) RECOVER_DATA(c);
    else if(c == 12) RECOVER_DATA(c);
    
    else if(c == 13) INSERT(c);
    else if(c == 14) INSERT(c);

    return 0;
}