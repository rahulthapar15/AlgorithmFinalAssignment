#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count=0;

int position_judge (int row,int column,int *a){
    int judge=1;
    int line_count;
    for (line_count=0; line_count<row; line_count++)    {
        if (column==a[line_count])
            judge=0;
        else if (abs(column-a[line_count])==abs(row-line_count))
            judge=0;
    }
    return judge;
}

void position_print (int n,int *a){
    int row;
    int column;
    printf("\t");
    for ( row=0; row<n; row++)    {
        for (column=0; column<a[row]; column++)
            printf("_ ");
        printf("%c",'Q');
        printf(" ");
        for (column=a[row]+1; column<n; column++)
            printf("_ ");
        printf("\n");
        printf("\t");
    }
    printf("\n\n");
}

void find_next (int n,int row,int *a){
    row++;
    int column;
    for (column=0; column<n; column++)
        if (position_judge(row,column,a)==1)
        {
            a[row]=column;
            if (row<n-1)
                find_next(n,row,a);
            else if (position_judge(row,column,a)==1)
            {
                position_print(n,a);
                count ++;
            }
        }
}

int main(){
    printf("\n\t\t----------------------\n");
    printf("\t\tn - Queen Problem \n");
    printf("\t\t----------------------\n\n");
    int n=8,row,column;
    printf("Length of the board : ");
    scanf ("%d",&n);
    int a[n];
    for (int z=0; z<n; z++)
        a[z]=0;

    row=0;
    for (column=0; column<n; column++)    {
        a[row]=column;
        find_next(n,row,a);
    }
    printf("Total Solutions for %d Queen's Problem : %d\n",n,count);
    return 0;
}
