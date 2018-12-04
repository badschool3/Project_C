/* --------include문------- */
#include <stdio.h>
#include <stdbool.h>    // bool 자료형 사용
#include <stdlib.h>
#include <stdarg.h>     // 가변 인자 사용
#include <string.h>
#include <time.h>		// time 함수 사용
#include <termio.h>		// getch() 함수 사용
/* --------define문-------- */

/* --------구조체정의-------*/
typedef struct member{		// 학생구조체
	int stdNum;				// 학생번호 (정수 8자리)
	char passwd[30];		// 비밀번호
	char name[30];			// 이름
	char address[30];		// 주소
	char phoneNum[12];		// 전화번호
	struct member *next;
	struct member *prev;
}M;
typedef struct book{		// 도서구조체
	int bookNum;			// 도서번호 (정수 7자리)
	char bookName[50];		// 도서이름
	char bookWriter[50];	// 저자명
	char bookPub[50];		// 출판사
	unsigned long long ISBN;// ISBN (정수 13자리)
	char bookWhere[50];		// 소장처
	char canBorrow[3];		// 대여가능 여부
	struct book *next;
	struct book *prev;
}B;
typedef struct borrow{		// 대여구조체
	int stdNum;			// 학생번호 (정수 7자리)
	int bookNum;		// 도서번호	(정수 8자리)
	time_t borrowT;			// 대여시간
	time_t returnT;			// 반납시간
	struct borrow *next;
	struct borrow *prev;
}bT;

typedef struct M_List{		// 이중 링크드 리스트 구현
	M *head;
	M *cur;
	M *tail;
	int cnt;
}M_LinkedList;

typedef struct B_List{
	B *head;
	B *cur;
	B *tail;
	int cnt;
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

/* -------함수 기능 정의------*/
int getch(void)					
{
	int ch;
	struct termios buf, save;
	tcgetattr(0,&save);
	buf = save;
	buf.c_lflag &= ~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}

void insertNode_Book(B);		// Book 노드 추가
void insertNode_Member(M);		// Member 노드 추가
void insertNode_Borrow(bT);		// Borrow 노드 추가
void load_file(void);			// 파일에서 정보 메모리에 불러오기
void save_file(void);			// 메모리 상에 정보를 파일에 저장하기
void swap_Book(B*, B*);			// swap_Book
void swap_Member(M*, M*);		// swap_Member
void sort_Member(void);			// Member 정렬
void sort_Book(void);			// Book 정렬
void print_book(B*);			// Book 출력

void search_menu(void);		// 도서 검색 메뉴 함수
void search_name(void);		// 도서명 검색 함수
void search_pub(void);		// 출판사 검색 함수
void search_ISBN(void);		// ISBN 검색 함수
void search_writer(void);	// 저자명 검색 함수
void search_all(void);		// 전체 검색 함수

FILE *client_fp, *book_fp, *borrow_fp;	

void print_book(B* bp)
{
	printf("==========================================\n");
	printf("도서번호	:	%d,		도서명	:	%s\n",\
			bp->bookName, bp->bookName);
	printf("출판사		:	%s,저자명	: 	%s\n",\
			bp->bookPub, bp->bookWriter);
	printf("ISBN		:	%lld,	소장처	:	%s\n",\
			bp->ISBN, bp->bookWhere);
	printf("대여 가능 여부 : %s\n",\
			bp->canBorrow);
	return;
}

void search_menu()
{
	int input;
	while(1)
	{
		system("clear");
		printf(">> 도서 검색 <<\n");
		printf("1. 도서명 검색	2. 출판사 검색\n");
		printf("3. ISBN 검색	4. 저자명 검색\n");
		printf("5. 전체 검색	6. 이전 메뉴\n\n");
		printf("번호를 선택하세요 : ");
		scanf("%d", &input);
		getchar();
		switch(input)
		{
			case 1:
				search_name();
				break;
			case 2:
				search_pub();
				break;
			case 3:
				search_ISBN();
				break;
			case 4:
				search_writer();
				break;
			case 5:
				search_all();
				break;
			case 6:
				printf("이전 메뉴로 돌아갑니다.\n");
				printf("아무키나 누르시면 계속합니다.\n");
				getch();
				return;
			default:
				printf("잘못 입력하셨습니다.\n");
		}
		printf("==========================================\n");
		printf("아무키나 누르시면 계속합니다.\n");
		getch();
	}
}

void search_name()
{
	char input[50] = {'\0',};
	B *bp = Book_L -> head;
	printf("도서명을 입력해 주세요 : ");
	fgets(input,sizeof(input), stdin);
	input[strlen(input)-1] = '\0';
	system("clear");
	while(bp != NULL)
	{
		if(strstr(bp->bookName, input) != NULL)
			print_book(bp);
		bp = bp -> next;
	}
	getch();
	return;
}
void search_pub()
{
	char input[50] = {'\0',};
	B *bp = Book_L -> head;
	printf("출판사를 입력해 주세요 : ");
	fgets(input, sizeof(input), stdin);
	input[strlen(input)-1] = '\0';
	system("clear");
	while(bp != NULL)
	{
		if(strstr(bp->bookPub, input) != NULL)
			print_book(bp);
		bp = bp -> next;
	}
	return;
}
void search_ISBN()
{
	unsigned long long input;
	B *bp = Book_L -> head;
	printf("ISBN을 입력해 주세요 : ");
	scanf("%lld", &input);
	getchar();
	system("clear");
	while(bp != NULL)
	{
		if(bp->ISBN == input)
			print_book(bp);
		bp = bp -> next;
	}
	return;
}
void search_writer()
{
	char input[50] = {'\0', };
	B *bp = Book_L -> head;
	printf("저자명을 입력해 주세요 : ");
	fgets(input, sizeof(input), stdin);
	input[strlen(input)-1] = '\0';
	system("clear");
	while(bp != NULL)
	{
		if(strstr(bp -> bookWriter, input) != NULL)
			print_book(bp);
		bp = bp -> next;
	}
	return;
}
void search_all()
{
	B *bp = Book_L -> head;
	while(bp != NULL)
	{
		print_book(bp);
		bp = bp -> next;
	}
	return;
}
void swap_Book(B* b1, B* b2)
{
	if(Book_L -> head == b1)
	{
		b2 -> prev = NULL;
		Book_L -> head = b2;
	}
	else
	{
		b1 -> prev -> next = b2;
		b2 -> prev = b1 -> prev;

	}
		
	if(Book_L->tail==b2)
	{
		b1 -> next = NULL;
		Book_L -> tail = b1;
	}
	else
	{
		b2 -> next -> prev = b1;
		b1 -> next = b2 -> next;
	}
	b1 -> prev = b2;
	b2 -> next = b1;
}

void swap_Member(M* m1, M* m2)
{
	if(Member_L -> head == m1)
	{
		m2 -> prev = NULL;
		Member_L -> head = m2;
	}
	else
	{
		m1 -> prev -> next = m2;
		m2 -> prev = m1 -> prev;
	}
		
	if(Member_L->tail==m2)
	{
		m1 -> next = NULL;
		Member_L -> tail = m1;
	}
	else
	{
		m2 -> next -> prev = m1;
		m1 -> next = m2 -> next;
	}
	m1 -> prev = m2;
	m2 -> next = m1;
}
void sort_Book()
{
	B *bp; 	
	for(int i = 0; i < Book_L -> cnt; i++)
	{
		bp = Book_L -> head;
		for(int j = 0; j < Book_L -> cnt - 1 - i; j++)
		{
			if(j==Book_L->cnt-2-i && i == Book_L->cnt-2)
				printf("g");
			if(bp -> ISBN > bp -> next -> ISBN)
				swap_Book(bp, bp->next);
			else
				bp = bp -> next;
		}
	}
}

void sort_Member()
{
	M *mp;
	for(int i = 0; i < Member_L -> cnt; i++)
	{
		mp = Member_L -> head;
		for(int j = 0; j < Member_L -> cnt - 1 - i; j++)
		{
			if(mp -> stdNum > mp -> next -> stdNum)
				swap_Member(mp, mp->next);
			else
				mp = mp -> next;
		}
	}
}

void insertNode_Book(B b1)
{
	B *newB = (B *)malloc(sizeof(B));
	newB->bookNum = b1.bookNum;
	memcpy(newB->bookName,b1.bookName, sizeof(b1.bookName));
	memcpy(newB->bookWriter, b1.bookWriter, sizeof(b1.bookWriter));
	memcpy(newB -> bookPub, b1.bookPub, sizeof(b1.bookPub));
	newB->ISBN = b1.ISBN;
	memcpy(newB -> bookWhere, b1.bookWhere, sizeof(b1.bookWhere));
	memcpy(newB -> canBorrow, b1.canBorrow, sizeof(b1.canBorrow));
	newB -> next = newB -> prev = NULL;
	Book_L -> cnt += 1;
	if(Book_L -> head == NULL && Book_L -> tail == NULL)
	{
		Book_L -> head = Book_L -> tail = newB;
	}
	else
	{
		Book_L -> tail -> next = newB;
		newB -> prev = Book_L -> tail;
		Book_L -> tail = newB;
		Book_L -> tail -> next = NULL;
	}
}

void insertNode_Member(M m1)
{
	M *newM = (M *)malloc(sizeof(M));
	newM->stdNum = m1.stdNum;
	memcpy(newM->passwd,m1.passwd,sizeof(m1.passwd));
	memcpy(newM->name,m1.name,sizeof(m1.name));
	memcpy(newM->address,m1.address,sizeof(m1.address));
	memcpy(newM->phoneNum,m1.phoneNum,sizeof(m1.phoneNum));
	newM -> next = newM -> prev = NULL;
	Member_L -> cnt += 1;
	if(Member_L -> head == NULL && Member_L -> tail == NULL)
		Member_L -> head = Member_L -> tail = newM;
	else
	{
		Member_L -> tail -> next = newM;
		newM -> prev = Member_L -> tail;
		Member_L -> tail = newM;
		Member_L -> tail -> next = NULL;
	}
}

void insertNode_Borrow(bT bT1)
{
	bT *newbT = (bT *)malloc(sizeof(bT));
	newbT -> stdNum = bT1.stdNum;
	newbT -> bookNum = bT1.bookNum;
	newbT -> borrowT = bT1.borrowT;
	newbT -> returnT = bT1.returnT;
	newbT -> next = newbT -> prev = NULL;

	if(Borrow_L -> head == NULL && Borrow_L -> tail == NULL)
		Borrow_L -> head = Borrow_L -> tail = newbT;
	else
	{
		Borrow_L -> tail -> next = newbT;
		newbT -> prev = Borrow_L -> tail;
		Borrow_L -> tail = newbT;
	}
}

void load_file()
{
	client_fp = fopen("client","r");
	book_fp = fopen("book","r");
	borrow_fp = fopen("borrow","r");
	
	B bb;
	bT bt;
	M mm;
	
	char buf[300];
	char tmp[15];
	Book_L = (B_LinkedList *) malloc(sizeof(B_LinkedList));
	Member_L = (M_LinkedList *) malloc(sizeof(M_LinkedList));
	Borrow_L = (bT_LinkedList *) malloc(sizeof(bT_LinkedList));

	Book_L -> head = Book_L -> cur = Book_L -> tail = NULL;
	Book_L -> cnt = Member_L -> cnt = 0;
	Member_L -> head = Member_L -> cur = Member_L -> tail = NULL;
	Borrow_L -> head = Borrow_L -> cur = Borrow_L -> tail = NULL;

	while(!feof(client_fp))
	{
		fgets(buf, sizeof(buf), client_fp);
		sscanf(buf,"%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|]",\
				tmp, mm.passwd, mm.name, mm.address, mm.phoneNum);
		mm.stdNum = atoi(tmp);
		insertNode_Member(mm);
	}
	while(!feof(book_fp))
	{
		fgets(buf, sizeof(buf), book_fp);
		sscanf(buf,"%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %lld | %[^\n|] | %[^\n|]",\
				tmp, bb.bookName, bb.bookPub, bb.bookWriter, &bb.ISBN, bb.bookWhere, bb.canBorrow);
		bb.bookNum = atoi(tmp);
		insertNode_Book(bb);
	}
	/*
	while(!feof(borrow_fp))
	{
		fgets(buf, sizeof(buf), book_fp);
		sscanf(buf, "%[^\n|] | %[^\n|] | %d | %d\n",\
				bt.stdNum, bt.bookNum, &bt.borrowT, &bt.returnT);
		insertNode_Borrow(bt);
	}
	*/
	fclose(client_fp);
	fclose(book_fp);
	fclose(borrow_fp);
}

void save_file()
{
	client_fp = fopen("client", "w");
	book_fp = fopen("book", "w");
	borrow_fp = fopen("borrow", "w");

	B *bp = Book_L -> head;
	M *mp = Member_L -> head;
	bT *btp = Borrow_L -> head;
	
	while(mp != NULL)
	{
		fprintf(client_fp, "%d | %s| %s| %s| %s\n",\
				mp -> stdNum, mp -> passwd, mp -> name, mp-> address, mp -> phoneNum);
		mp = mp -> next;
	}
	while(bp != NULL)
	{
		fprintf(book_fp, "%08d | %s| %s| %s| %lld | %s| %s\n",\
				bp -> bookNum, bp -> bookName, bp -> bookPub, bp -> bookWriter, bp -> ISBN, bp -> bookWhere, bp -> canBorrow);
		bp = bp -> next;
	}
	while(btp != NULL)
	{
		fprintf(borrow_fp, "%s| %s| %d | %d\n",\
				btp -> stdNum, btp -> bookNum, btp -> borrowT, btp -> returnT);
		btp = btp -> next;
	}
	fclose(client_fp);
	fclose(book_fp);
	fclose(borrow_fp);
}

int main()
{
	load_file();
	sort_Book();
	sort_Member();
	search_menu();
	//save_file();
}
