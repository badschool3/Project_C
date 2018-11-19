#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//FILE *client_fp, *book_fp, *borrow_fp;
FILE *client_fp;
/* --------구조체정의-------*/
typedef struct member{		// 학생구조체
	int stdNum;				// 학생번호
	char passwd[20];		// 비밀번호
	char name[10];			// 이름
	char address[20];		// 주소
	char phoneNum[12];		// 전화번호
	struct member *next;
}M;
typedef struct book{		// 도서구조체
	int bookNum;			// 도서번호
	char bookName[20];		// 도서이름
	char bookPub[10];		// 출판사
	unsigned long long ISBN;// ISBN
	char bookWhere[15];		// 소장처
	char canBorrow[10];		// 대여가능 여부
	struct book *next;
}B;
typedef struct borrow{		// 대여구조체
	int stdNum;				// 학생번호
	int bookNum;			// 도서번호
	time_t borrowT;			// 대여시간
	time_t returnT;			// 반납시간
	struct borrow *next;
}bT;

typedef struct M_List{
	M *head;
	M *cur;
	M *tail;
}M_LinkedList;

typedef struct B_List{
	B *head;
	B *cur;
	B *tail;
}B_LinkedList;

typedef struct bT_List{
	bT *head;
	bT *cur;
	bT *tail;
}bT_LinkedList;


/* --------변수 정의--------*/
//B_LinkedList *Book_L = (B_LinkedList *)malloc(sizeof(B_LinkedList));
//bT_LinkedList *Borrow_L = (bT_LinkedList *)malloc(sizeof(bT_LinkedList));

/*
void insertNode_Book(B_LinkedList *L, B b1)
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
*/
void insertNode_Member(M_LinkedList *L, M m1)
{
	M *newM = (M *)malloc(sizeof(M));
	newM -> stdNum = m1.stdNum;
	memcpy(newM->passwd,m1.passwd,sizeof(m1.passwd));
	memcpy(newM->name,m1.name,sizeof(m1.name));
	memcpy(newM->address,m1.address,sizeof(m1.address));
	memcpy(newM->phoneNum,m1.phoneNum,sizeof(m1.phoneNum));
	newM -> next = NULL;
	if(L -> head == NULL && L -> tail == NULL)
		L -> head = L -> tail = newM;
	else
	{
		L -> tail -> next = newM;
		L -> tail = newM;
	}
}
/*
void insertNode_Borrow(bT_LinkedList *L, bT bT1)
{
	bT *newbT = (bT *)malloc(sizeof(bT));
	newbT -> stdNum = bT1.stdNum;
	newbT -> bookNum = bT1.bookNum;
	newbT -> borrowT = bT1.borrowT;
	newbT -> returnT = bT1.returnT;

	if(L -> head == NULL && L -> tail == NULL)
		L -> head = L -> tail = newbT;
	else
	{
		L -> tail -> next = newbT;
		L -> tail -> newbT;
	}
}
*/
void load_file(M_LinkedList *Member_L)
{
	client_fp = fopen("client","r");
	//book_fp = fopen("book","r");
	//borrow_fp = fopen("borrow","r");
//	B bb;
//	bT bt;
	M mm;
	int i = 0;

	while(!feof(client_fp))
	{
		i++;
		fscanf(client_fp,"%d | %s | %s | %s | %s\n", &mm.stdNum, mm.passwd, mm.name, mm.address, mm.phoneNum);
		insertNode_Member(Member_L, mm);
	}
	fclose(client_fp);
}

void printNodes(M_LinkedList *newM)
{
	M *p = newM -> head;
	while(p != NULL)
	{
		printf("%08d | %s | %s | %s | %s\n", p -> stdNum, p -> passwd, p -> name, p-> address, p -> phoneNum);
		p = p -> next;
	}
}

int main()
{
	M_LinkedList *Member_L;
	Member_L = (M_LinkedList *) malloc(sizeof(M_LinkedList));
	Member_L -> head = NULL;
	Member_L -> cur = NULL;
	Member_L -> tail = NULL;
	load_file(Member_L);
	printNodes(Member_L);
	return 0;

}
