/* --------include문------- */
#include <stdio.h>
#include <stdbool.h>    // bool 자료형 사용
#include <stdlib.h>
#include <stdarg.h>     // 가변 인자 사용
#include <string.h>
#include <time.h>		// time 함수 사용
#include <termio.h>		// getch() 함수 사용
#include <locale.h>
/* --------define문-------- */

/* --------구조체정의-------*/
typedef struct member{		// 학생구조체
	char stdNum[30];			// 학생번호 (정수 8자리)
	char passwd[30];		// 비밀번호
	char name[30];			// 이름
	char address[30];		// 주소
	char phoneNum[30];		// 전화번호
	struct member *next;
}M;
typedef struct book{		// 도서구조체
	char bookNum[30];		// 도서번호 (정수 7자리)
	char bookName[50];		// 도서이름
	char bookPub[50];		// 출판사
	char ISBN[30];				// ISBN (정수 13자리)
	char bookWhere[30];		// 소장처
	char canBorrow[30];		// 대여가능 여부
	struct book *next;
}B;
typedef struct borrow{		// 대여구조체
	char stdNum[7];			// 학생번호 (정수 7자리)
	char bookNum[8];		// 도서번호	(정수 8자리)
	time_t borrowT;			// 대여시간
	time_t returnT;			// 반납시간
	struct borrow *next;
}bT;
typedef struct M_List{		// 링크드 리스트 구현
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
B_LinkedList *Book_L;
M_LinkedList *Member_L;
bT_LinkedList *Borrow_L;


void insertNode_Book(B);		// Book 노드 추가
void insertNode_Member(M);		// Member 노드 추가
void insertNode_Borrow(bT);		// Borrow 노드 추가
void load_file(void);			// 파일에서 정보 메모리에 불러오기
void save_file(void);			// 메모리 상에 정보 파일에 저장하기
void sort_file(void);			// 정렬
FILE *client_fp, *book_fp, *borrow_fp;	


int main()
{
	load_file();
	Member_L -> head = sort_file(Member_L -> head);
	save_file();
}
void insertNode_Book(B b1)
{
	B *newB = (B *)malloc(sizeof(B));
	memcpy(newB->bookNum, b1.bookNum, sizeof(b1.bookNum));
	memcpy(newB->bookName,b1.bookName, sizeof(b1.bookName));
	memcpy(newB -> bookPub, b1.bookPub, sizeof(b1.bookPub));
	memcpy(newB -> ISBN, b1.ISBN, sizeof(b1.ISBN));
	memcpy(newB -> bookWhere, b1.bookWhere, sizeof(b1.bookWhere));
	memcpy(newB -> canBorrow, b1.canBorrow, sizeof(b1.canBorrow));
	newB -> next = NULL;

	if(Book_L -> head == NULL && Book_L -> tail == NULL)
		Book_L -> head = Book_L -> tail = newB;
	else
	{
		Book_L -> tail -> next = newB;
		Book_L -> tail = newB;
	}
}

void insertNode_Member(M m1)
{
	M *newM = (M *)malloc(sizeof(M));
	memcpy(newM->stdNum, m1.stdNum, sizeof(m1.stdNum));
	memcpy(newM->passwd,m1.passwd,sizeof(m1.passwd));
	memcpy(newM->name,m1.name,sizeof(m1.name));
	memcpy(newM->address,m1.address,sizeof(m1.address));
	memcpy(newM->phoneNum,m1.phoneNum,sizeof(m1.phoneNum));
	newM -> next = NULL;

	if(Member_L -> head == NULL && Member_L -> tail == NULL)
		Member_L -> head = Member_L -> tail = newM;
	else
	{
		Member_L -> tail -> next = newM;
		Member_L -> tail = newM;
	}
}
/*
void insertNode_Borrow(bT bT1)
{
	bT *newbT = (bT *)malloc(sizeof(bT));
	memcpy(newbT->stdNum, bT1.stdNum, sizeof(bT1.stdNum));
	memcpy(newbT->bookNum, bT1.bookNum, sizeof(bT1.bookNum));
	newbT -> borrowT = bT1.borrowT;
	newbT -> returnT = bT1.returnT;

	if(Borrow_L -> head == NULL && Borrow_L -> tail == NULL)
		Borrow_L -> head = Borrow_L -> tail = newbT;
	else
	{
		Borrow_L -> tail -> next = newbT;
		Borrow_L -> tail = newbT;
	}
}
*/
void load_file()
{
	client_fp = fopen("client","r");
	book_fp = fopen("book","r");
	//borrow_fp = fopen("borrow","r");
	
	B bb;
	//bT bt;
	M mm;
	
	char buf[300];

	Book_L = (B_LinkedList *) malloc(sizeof(B_LinkedList));
	Member_L = (M_LinkedList *) malloc(sizeof(M_LinkedList));
	//Borrow_L = (bT_LinkedList *) malloc(sizeof(bT_LinkedList));

	Book_L -> head = Book_L -> cur = Book_L -> tail = NULL;
	Member_L -> head = Member_L -> cur = Member_L -> tail = NULL;
	//Borrow_L -> head = Borrow_L -> cur = Borrow_L -> tail = NULL;

	while(!feof(client_fp))
	{
		fgets(buf, sizeof(buf), client_fp);
		sscanf(buf,"%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|]",\
				mm.stdNum, mm.passwd, mm.name, mm.address, mm.phoneNum);
		insertNode_Member(mm);
	}
	while(!feof(book_fp))
	{
		fgets(buf, sizeof(buf), book_fp);
		sscanf(buf,"%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|]",\
				bb.bookNum, bb.bookName, bb.bookPub, bb.ISBN, bb.bookWhere, bb.canBorrow);
		insertNode_Book(bb);
	}
	/*
	while(!feof(borrow_fp))
	{
		fgets(buf, sizeof(buf), book_fp);
		sscanf(borrow_fp, "%[^\n|] | %[^\n|] | %d | %d\n",\
				bt.stdNum, bt.bookNum, &bt.borrowT, &bt.returnT);
		insertNode_Borrow(bt);
	}
	*/
	fclose(client_fp);
	fclose(book_fp);
	//fclose(borrow_fp);
}

void save_file()
{
	//client_fp = fopen("client", "w");
	//book_fp = fopen("book", "w");
	//borrow_fp = fopen("borrow", "w");

	B *bp = Book_L -> head;
	M *mp = Member_L -> head;
	//bT *btp = Borrow_L -> head
	
	while(mp != NULL)
	{
		printf("%s| %s| %s| %s| %s\n",\
				mp -> stdNum, mp -> passwd, mp -> name, mp-> address, mp -> phoneNum);
		mp = mp -> next;
	}
	while(bp != NULL)
	{
		printf("%s| %s| %s| %s| %s| %s\n",\
				bp -> bookNum, bp -> bookName, bp -> bookPub, bp -> ISBN, bp -> bookWhere, bp -> canBorrow);
		bp = bp -> next;
	}
	/*
	while(btp != NULL)
	{
		fprintf("%s| %s| %d| %d\n",\
				btp -> stdNum, btp -> bookNum, btp -> borrowT, btp -> returnT);
		btp = btp -> next;
	}
	*/
	//fclose(client_fp);
	//fclose(book_fp);
	//fclose(borrow_fp);
}
