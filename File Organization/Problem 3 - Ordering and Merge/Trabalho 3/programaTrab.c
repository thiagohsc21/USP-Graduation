//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include <stdio.h>
#include "LOOP_ANINHADO.h"
#include "LOOP_UNICO.h"
#include "ORDENACAO.h"
#include "MERGE.h"

int main() {

    int c;
    scanf("%d", &c);

    if(c == 15) LOOP_ANINHADO(); 
    else if(c == 16) LOOP_UNICO();
    else if(c == 17 || c == 18) ORDENACAO(c);
    else if(c == 19) MERGE();

    return 0;
}