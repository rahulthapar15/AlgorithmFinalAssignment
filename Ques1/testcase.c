#include "skiplist.h"

int main(void)
{
	// int choice;
	// printf("(1) INSERT \n (2) Search\n (3) DELETE\n");
	// scanf("%d\n",&choice);
	 skiplist *sl = create_skiplist();
	//
	// switch (choice) {
	// 	case 1:
	// 					insert(sl, 2, NULL);
	// 					printf("Inserted\n");
	// 					break;
	// 	case 2:
	// 					find(sl,2);
	// 					break;
	// 	case 3:
	// 				delete(sl, 2);
	// 				break;
	// 	default :
	// 	exit(0);
	// }

	insert(sl, 2, NULL);
	insert(sl, 7, NULL);
	insert(sl, 12, NULL);
	insert(sl, 5, NULL);
	insert(sl, 45, NULL);
	insert(sl, 19, NULL);

	print(sl);
	printf("---------------------------------------------------\n");
	printf("SEARCHING\n");
	find(sl,99);
	printf("---------------------------------------------------\n");

	printf("DELETE\n");
	delete(sl,2);
	print(sl);
	printf("---------------------------------------------------\n");


	// print(sl);
	//
	// delete(sl, 2);
	// print(sl);
	// delete(sl, 5);
	// print(sl);
	//
	// delete(sl, 45);
	// print(sl);
	//
	// delete(sl, 19);
	// print(sl);
	//
	// delete(sl, 7);
	// delete(sl, 12);
	// print(sl);

	free_skiplist(sl);

	return 0;
}
