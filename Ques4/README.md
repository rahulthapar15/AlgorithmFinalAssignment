#### Ques 4 : n-Queen Problem
```
RAHUL THAPAR
```
```
Input n >= 4

```
```
CHECK NEXT POSITION

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
```
```
PLACE QUEEN WHERE POSSIBLE

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
```