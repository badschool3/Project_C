#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

typedef struct book{		// 도서구조체
	int bookNum;			// 도서번호
	char bookName[20];		// 도서이름
	char bookPub[10];		// 출판사
	unsigned long long ISBN;// ISBN
	char bookWhere[15];		// 소장처
	char canBorrow[10];		// 대여가능 여부
	struct book *next;
}B;
typedef struct _List{
	B *head;			// 시작
	B *cur;			// 커서
	B *tail;			// 끝
} linkedList;


void insertNode(linkedList *L, B b1)
{
	B *newB = (B *)malloc(sizeof(B));
	newB -> bookNum = b1.bookNum;
	memcpy(newB->bookName,b1.bookName,sizeof(b1.bookName));
	memcpy(newB -> bookPub, b1.bookPub, sizeof(b1.bookPub));
	newB -> ISBN = b1.ISBN;
	memcpy(newB -> bookWhere, b1.bookWhere, sizeof(b1.bookWhere));
	memcpy(newB -> canBorrow, b1.canBorrow, sizeof(b1.canBorrow));
	newB -> next = NULL;

	if(L -> head == NULL && L -> tail == NULL)
		L -> head = L -> tail = newB;
	else
	{
		L -> tail -> next = newB;
		L -> tail = newB;
	}
}

void printNodes(linkedList *newB)
{
	B *p = newB -> head;
	fp = fopen("client","w");
	while(p != NULL)
	{
		fprintf(fp,"%d | %s | %s | %lld | %s | %s \n", p -> bookNum, p -> bookName,\
				p-> bookPub, p-> ISBN, p-> bookWhere, p-> canBorrow);
		p = p->next;
	}
}

int campare(const void *a, const void *b)
{
	unsigned long long num1 = *(unsigned long long *)a;
	unsigned long long num2 = *(unsigned long long *)b;

	if(num1 < num2)
		return -1;
	if(num2 < num1)
		return 1;
	return 0;
}

int main()
{
	linkedList *book_L = (linkedList *)malloc(sizeof(linkedList));
	book_L -> head = NULL;
	book_L -> cur = NULL;
	book_L -> tail = NULL;
	B bb;

	for(int i = 0 ; i < 4; i++)
	{
		scanf("%d | %s | %s | %lld | %s | %s",&bb.bookNum, bb.bookName, bb.bookPub, &bb.ISBN, bb.bookWhere, bb.canBorrow);
		insertNode(book_L, bb);
	}
	printNodes(book_L);
	fclose(fp);
}

