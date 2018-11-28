#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* --------구조체정의-------*/
typedef struct member{		// 학생구조체
	char stdNum[30];			// 학생번호 (정수 8자리)
	char passwd[30];		// 비밀번호
	char name[30];			// 이름
	char address[30];		// 주소
	char phoneNum[32];		// 전화번호
	struct member *next;
}M;
typedef struct book{		// 도서구조체
	char bookNum[37];		// 도서번호 (정수 7자리)
	char bookName[30];		// 도서이름
	char bookPub[30];		// 출판사
	char ISBN[30];				// ISBN (정수 13자리)
	char bookWhere[30];		// 소장처
	char canBorrow[30];		// 대여가능 여부
	struct book *next;
}B;
typedef struct borrow{		// 대여구조체
	char stdNum[30];			// 학생번호 (정수 7자리)
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
M_LinkedList *Member_L = NULL;
bT_LinkedList *Borrow_L;

void insertNode_Book(B);		// Book 노드 추가
void insertNode_Member(M);		// Member 노드 추가
void insertNode_Borrow(bT);		// Borrow 노드 추가
void load_file(void);			// 파일에서 정보 메모리에 불러오기
void save_file(void);			// 메모리 상에 정보 파일에 저장하기

int i =0;

FILE *client_fp, *book_fp, *borrow_fp;	

int main()
{
	load_file();
	save_file();
	return 0;
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
	{
		printf("head초기화\n");
		Member_L -> head = Member_L -> tail = newM;
	}
	else
	{
		Member_L -> tail -> next = newM;
		Member_L -> tail = newM;
		printf("tail초기화\n");
	}
}

void load_file()
{
	client_fp = fopen("client","r");
	book_fp = fopen("book","r");
	char buf[300];

	B bb;
	M mm;
	
	Book_L = (B_LinkedList *) malloc(sizeof(B_LinkedList));
	Member_L = (M_LinkedList *) malloc(sizeof(M_LinkedList));

	Book_L -> head = Book_L -> cur = Book_L -> tail = NULL;
	Member_L -> head = Member_L -> cur = Member_L -> tail = NULL;

	while(!feof(client_fp))
	{
		fgets(buf,sizeof(buf),client_fp);	
		sscanf(buf, "%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|]",\
				mm.stdNum, mm.passwd, mm.name, mm.address, mm.phoneNum);
		insertNode_Member(mm);
	}
	while(!feof(book_fp))
	{
	
		fgets(buf,sizeof(buf),book_fp);
		sscanf(buf,"%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|]",\
				bb.bookNum, bb.bookName, bb.bookPub, bb.ISBN, bb.bookWhere, bb.canBorrow);
		insertNode_Book(bb);
	}
	
	fclose(client_fp);
	fclose(book_fp);
}

void save_file()
{
	B *bp = Book_L -> head;
	M *mp = Member_L -> head;
	
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
	fclose(client_fp);
	fclose(book_fp);
	free(Book_L);
	free(Member_L);
}
