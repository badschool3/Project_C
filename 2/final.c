/* --------include문------- */
#include <stdio.h>
#include <stdbool.h>    // bool 자료형 사용
#include <stdlib.h>
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
	M *head;				// 처음
	M *cur;					// 커서
	M *tail;				// 끝
	int cnt;				// 개수
}M_LinkedList;

typedef struct B_List{
	B *head;
	B *cur;
	B *tail;
	int cnt;
	int topNum;
}B_LinkedList;

typedef struct bT_List{
	bT *head;
	bT *cur;
	bT *tail;
}bT_LinkedList;

typedef struct ISBN_check{
	unsigned long long ISBN;
	struct ISBN_check *next;
}ISBN_check;
typedef struct ISBN_List{
	ISBN_check *head;
	ISBN_check *tail;
}ISBN_List;

/* --------변수 정의--------*/
B_LinkedList *Book_L;
M_LinkedList *Member_L;
bT_LinkedList *Borrow_L;

FILE *client_fp, *book_fp, *borrow_fp;

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

/*-----------데이터 관련 함수--------*/
void load_file(void);			// 파일에서 정보 메모리에 불러오기
void save_file(void);			// 메모리 상에 정보를 파일에 저장하기

void insertNode_Book(B);		// Book 노드 추가
void insertNode_Member(M);		// Member 노드 추가
void insertNode_Borrow(bT);		// Borrow 노드 추가

void sort_Member(void);			// Member 정렬
void sort_Book(void);			// Book 정렬
void swap_Book(B*, B*);			// swap_Book
void swap_Member(M*, M*);		// swap_Member

/*-----------시작 화면 관련 함수-------*/
void first_menu(void);
void join_member(void);
int login_member(void);
bool check_member(M);

/*-----------회원 관련 함수--------*/
void member_menu(void);		// 회원 메뉴 함수

void search_menu(void);		// 도서 검색 메뉴 함수
void change_info(void);		// 정보 변경 함수
void out_member(void);		// 회원 탈퇴 함수
void myborrow_list(void); 	// 내 대여 목록

void search_name(void);		// 도서명 검색 함수
void search_pub(void);		// 출판사 검색 함수
void search_ISBN(void);		// ISBN 검색 함수
void search_writer(void);	// 저자명 검색 함수
void search_all(void);		// 전체 검색 함수
void print_book(B*);		// Book 출력
unsigned long long chk_ISBN(B*, ISBN_List*);			// 검색 관련 중복 체크 함수
bool insertNode_ISBN(unsigned long long, ISBN_List*);	// ISBN 중복 체크 함수
void delete_ISBN(ISBN_List*);							// ISBN 리스트 제거 함수


/*----------관리자 관련 함수-------*/
void admin_menu(void);		// 관리자 메뉴 함수

void add_book(void);			// 도서 등록
void remove_book(void);			// 도서 삭제
void borrow_book(void);			// 도서 대여
void return_book(void);			// 도서 반납
void member_list(void);			// 회원 목록

void remove_ask(void);			// 삭제 여부 질문
void borrow_ask(void);			// 대여 여부 질문

bool admin_borrow(B*);			// 도서 가능 여부 확인
bool admin_name(void);			// 관리자 이름 검색 기능
bool admin_ISBN(void);			// 관리자 ISBN 검색 기능

void remove_borrow(bT*);		// 대여 삭제 기능
char* day_of_the_week(int);		// 요일 변환 기능

void print_member(M*);			// Member 출력
void search_adminName();		// 회원 이름 검색
void search_adminNum();			// 회원 학번 검색
void search_adminAll();			// 회원 전체 목록

int main()
{
	load_file();
	sort_Book();
	sort_Member();
	first_menu();
	save_file();
	return 0;
}

void load_file()
{
	client_fp = fopen("client","r");		// 파일 불러올 준비
	book_fp = fopen("book","r");
	borrow_fp = fopen("borrow","r");
	
	B bb;
	bT bt;
	M mm;
	
	char buf[300] = {'\0',};
	char tmp[15] = {'\0',};
	char tmp2[15] = {'\0',};
	Book_L = (B_LinkedList *) malloc(sizeof(B_LinkedList));				// 동적 할당
	Member_L = (M_LinkedList *) malloc(sizeof(M_LinkedList));
	Borrow_L = (bT_LinkedList *) malloc(sizeof(bT_LinkedList));

	Book_L -> head = Book_L -> cur = Book_L -> tail = NULL;				// 초기화
	Member_L -> head = Member_L -> cur = Member_L -> tail = NULL;
	Borrow_L -> head = Borrow_L -> cur = Borrow_L -> tail = NULL;

	Book_L -> cnt = Book_L -> topNum = Member_L -> cnt = 0 ;			// 데이터 수 카운트

	while(!feof(client_fp))		// 파일의 끝까지 반복
	{
		if(fgets(buf, sizeof(buf), client_fp) == NULL)		// feof 고질적 문제인 마지막 한번더 반복 예외 처리
			break;
		sscanf(buf,"%[^\n|]|%[^\n|]|%[^\n|]|%[^\n|]|%[^\n|]",\
				tmp, mm.passwd, mm.name, mm.address, mm.phoneNum);
		mm.stdNum = atoi(tmp);								// tmp에 받은 것을 atoi함수로 int형으로 변환
		insertNode_Member(mm);								// 노드를 리스트에 추가
	}
	while(!feof(book_fp))
	{
		if(fgets(buf, sizeof(buf), book_fp) == NULL)
			break;
		sscanf(buf,"%[^\n|]|%[^\n|]|%[^\n|]|%[^\n|]|%lld|%[^\n|]|%[^\n|]",\
				tmp, bb.bookName, bb.bookPub, bb.bookWriter, &bb.ISBN, bb.bookWhere, bb.canBorrow);
		bb.bookNum = atoi(tmp);
		insertNode_Book(bb);
	}
	
	while(!feof(borrow_fp))
	{
		if(fgets(buf, sizeof(buf), borrow_fp) == NULL)
			break;
		sscanf(buf, "%[^\n|]|%[^\n|]|%ld|%ld\n",\
				tmp, tmp2, &bt.borrowT, &bt.returnT);
		bt.stdNum = atoi(tmp);
		bt.bookNum = atoi(tmp2);
		insertNode_Borrow(bt);
	}
	
	fclose(client_fp);
	fclose(book_fp);
	fclose(borrow_fp);
}

void save_file()
{
	client_fp = fopen("client", "w");						// load_file과 동일한 구조
	book_fp = fopen("book", "w");
	borrow_fp = fopen("borrow", "w");

	B *bp = Book_L -> head;
	M *mp = Member_L -> head;
	bT *btp = Borrow_L -> head;
	
	while(mp != NULL)
	{
		fprintf(client_fp, "%08d|%s|%s|%s|%s\n",\
				mp -> stdNum, mp -> passwd, mp -> name, mp-> address, mp -> phoneNum);
		mp = mp -> next;
	}
	while(bp != NULL)
	{
		fprintf(book_fp, "%07d|%s|%s|%s|%013lld|%s|%s\n",\
				bp -> bookNum, bp -> bookName, bp -> bookPub, bp -> bookWriter, bp -> ISBN, bp -> bookWhere, bp -> canBorrow);
		bp = bp -> next;
	}
	while(btp != NULL)
	{
		fprintf(borrow_fp, "%08d|%07d|%ld|%ld\n",\
				btp -> stdNum, btp -> bookNum, btp -> borrowT, btp -> returnT);
		btp = btp -> next;
	}
	fclose(client_fp);
	fclose(book_fp);
	fclose(borrow_fp);
}

void insertNode_Book(B b1)
{
	B *newB = (B *)malloc(sizeof(B));							// 노드 동적 할당
	newB->bookNum = b1.bookNum;
	if(newB->bookNum > Book_L->topNum)
		Book_L->topNum = newB->bookNum;

	memcpy(newB->bookName,b1.bookName, sizeof(b1.bookName));	// 인자 값 노드에 넣기
	memcpy(newB->bookWriter, b1.bookWriter, sizeof(b1.bookWriter));
	memcpy(newB -> bookPub, b1.bookPub, sizeof(b1.bookPub));
	newB->ISBN = b1.ISBN;
	memcpy(newB -> bookWhere, b1.bookWhere, sizeof(b1.bookWhere));
	memcpy(newB -> canBorrow, b1.canBorrow, sizeof(b1.canBorrow));
	newB -> next = newB -> prev = NULL;
	Book_L -> cnt += 1;											// 노드 개수 카운트

	if(Book_L -> head == NULL && Book_L -> tail == NULL)		// 만약 처음 노드였다면 head, tail 추가
		Book_L -> head = Book_L -> tail = newB;
	else
	{
		Book_L -> tail -> next = newB;							// 아니라면 기존 tail노드의 next가 새로운 노드를 가르킴
		newB -> prev = Book_L -> tail;							// 새로운 노드의 prev가 기존 tail노드를 가르킴
		Book_L -> tail = newB;									// tail이 새로운 노드가 됨
		Book_L -> tail -> next = NULL;							// tail 노드의 next를 비워줌
	}
	return;
}

void insertNode_Member(M m1)
{
	M *newM = (M *)malloc(sizeof(M));							// Book과 동일한 구조
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
	return;
}

void insertNode_Borrow(bT btp)
{
	bT *newbT = (bT *)malloc(sizeof(bT));
	
	newbT -> stdNum = btp.stdNum;
	newbT -> bookNum = btp.bookNum;
	newbT -> borrowT = btp.borrowT;
	newbT -> returnT = btp.returnT;
	newbT -> next = newbT -> prev = NULL;

	if(Borrow_L -> head == NULL && Borrow_L -> tail == NULL)
		Borrow_L -> head = Borrow_L -> tail = newbT;
	else
	{
		Borrow_L -> tail -> next = newbT;
		newbT -> prev = Borrow_L -> tail;
		Borrow_L -> tail = newbT;
		Borrow_L -> tail -> next = NULL;
	}
	return;
}

void swap_Book(B* b1, B* b2)					// sort를 위한 swap함수, b1과 b2의 위치를 바꿔줌
{
	if(Book_L -> head == b1)					// 만약 b1이 head일 때
	{
		b2 -> prev = NULL;
		Book_L -> head = b2;
	}
	else
	{
		b1 -> prev -> next = b2;
		b2 -> prev = b1 -> prev;

	}
		
	if(Book_L->tail==b2)						// 만약 b2가 tail일 때
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
	return;
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
	return;
}
void sort_Book()								// 버블 정렬 알고리즘 사용
{
	B *bp; 	
	for(int i = 0; i < Book_L -> cnt; i++)
	{
		bp = Book_L -> head;
		for(int j = 0; j < Book_L -> cnt - 1 - i; j++)
		{
			if(bp -> ISBN > bp -> next -> ISBN)	// 더 크다면 앞뒤 노드swap
				swap_Book(bp, bp->next);
			else
				bp = bp -> next;
		}
	}
	return;
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
	return;
}

void first_menu()
{
	int input, check;

	while(1)
	{
		system("clear");
		input = check = 0;
		printf(">> 도서관 서비스 <<\n");
		printf("1. 회원가입		2. 로그인		3. 프로그램 종료\n");
		printf("번호를 입력해주세요 : ");
		scanf("%d",&input);
		getchar();
		switch(input)
		{
			case 1:
				join_member();
				break;
			case 2:
				check = login_member();
				if(check == 2)
					admin_menu();
				else if(check == 1)
					member_menu();
				break;

			case 3:
				printf("프로그램을 종료합니다.\n");
				printf("아무키나 누르시면 계속합니다.\n");
				sort_Book();
				sort_Member();
				save_file();
				getch();
				return;
			default:
				printf("다시 입력해주세요.\n");
		}
		printf("아무키나 누르시면 계속합니다.\n");
		getch();
	}
}

void join_member()
{
	M MB;
	system("clear");
	printf(">> 회원 가입 <<\n");
	printf("학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n\n");
	
	printf("학번 : ");
	scanf("%d",&MB.stdNum);
	printf("비밀번호 : ");
	scanf("%s",MB.passwd);
	printf("이름 : ");
	scanf("%s",MB.name);
	printf("주소 : ");
	scanf("%s",MB.address);
	printf("전화번호 : ");
	scanf("%s",MB.phoneNum);
	
	if(check_member(MB))		// 중복된 회원이 있는지 체크
	{
		insertNode_Member(MB);
		sort_Member();
		printf("\n회원가입이 완료되셨습니다.\n");
	}
	else
		printf("\n중복된 정보를 가진 회원이 존재합니다.\n");
	getchar();
	sort_Member();
	save_file();
	return;
}
int login_member()
{
	char num[10] = {'\0',};
	char password[20] = {'\0',};
	M *mp = Member_L -> head;
	system("clear");
	printf("학번 : ");
	fgets(num,sizeof(num), stdin);
	printf("비밀번호 : ");
	fgets(password,sizeof(password), stdin);
	num[strlen(num)-1] = '\0';
	password[strlen(password)-1] = '\0';
	
	if(!(strcmp(num,"admin")) && !(strcmp(password, "lib_admin")))					// 만약 admin이라면 관리자 메뉴를 위해 2 반환
	{
		printf("관리자 메뉴로 진입합니다.\n아무키나 누르시면 계속합니다.\n");
		getch();
		return 2;
	}
	while(mp != NULL)
	{
		if(atoi(num) == mp -> stdNum && !(strcmp(mp->passwd, password)))			// 학번, 비밀번호가 일치하는지 비교
		{	
			Member_L -> cur = mp;					// 일반 회원이라면 cur가 mp를 포인트 하고 1 반환
			printf("%s님 환영합니다. 회원 메뉴로 진입합니다.\n아무키나 누르시면 계속합니다.\n",mp->name);
			getch();
			return 1;
		}
		mp = mp -> next;
	}
	printf("로그인 정보가 틀립니다.\n");
	return false;									// 로그인 실패 시 0 반환
}

bool check_member(M m1)
{
	M *mp = Member_L -> head;
	while(mp != NULL)
	{
		if(mp -> stdNum == m1.stdNum)				// 중복된 회원이 존재할 시 false 반환
			return false;
		mp = mp -> next;
	}
	return true;
}

void member_menu()
{
	int input;
	while(1)
	{
		system("clear");
		printf(">> 회원 메뉴 <<\n");
		printf(">> %s님 환영합니다 <<\n",Member_L->cur->name);
		printf("1. 도서 검색		2. 내 대여 목록\n");
		printf("3. 개인정보 수정	4. 회원 탈퇴\n");
		printf("5. 로그아웃			6. 프로그램 종료\n"); 
		printf("숫자를 입력해주세요 : ");

		scanf("%d",&input);
		getchar();
		switch(input)
		{
			case 1:
				search_menu();
				break;
			case 2:
				myborrow_list();
				break;
			case 3:
				change_info();
				break;
			case 4:
				out_member();
				printf("회원 탈퇴가 완료되었습니다.\n");
				return;
			case 5:
				Member_L->cur = NULL;
				printf("로그아웃이 완료되었습니다.\n");
				return;
			case 6:
				printf("프로그램을 종료합니다.\n");
				sort_Member();
				sort_Book();
				exit(0);
			default:
				printf("잘못 입력하셨습니다.\n");
		}
		printf("아무키나 누르시면 계속합니다.\n");
		getch();
	}	
}

void search_menu()
{
	int input;
	while(1)
	{
		system("clear");
		printf(">> 도서 검색 <<\n");
		printf("1. 도서명 검색	2. 출판사 검색\n");
		printf("3. ISBN 검색		4. 저자명 검색\n");
		printf("5. 전체 검색		6. 이전 메뉴\n\n");
		printf("번호를 선택하세요 : ");
		scanf("%d", &input);
		getchar();
		system("clear");
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
				return;
			default:
				printf("잘못 입력하셨습니다.\n");
		}
		printf("==========================================\n");
		printf("아무키나 누르시면 계속합니다.\n");
		getch();
	}
}

void change_info()
{
	int input;
	while(1)
	{
		system("clear");
		printf(">> 개인정보 수정 <<\n");
		printf("1. 비밀번호 변경	2. 주소 변경\n");
		printf("3. 전화번호 변경	4. 돌아가기\n");
		printf("숫자를 입력해주세요 : ");
	
		scanf("%d", &input);
		switch(input)
		{
			case 1:
				printf("변경할 비밀번호를 입력해주세요 : ");
				scanf("%s", Member_L->cur->passwd);
				printf("변경이 완료되었습니다.\n");
				break;
			case 2:
				printf("변경할 주소를 입력해주세요 : ");
				scanf("%s", Member_L->cur->address);
				printf("변경이 완료되었습니다.\n");
				break;
			case 3:
				printf("변경할 전화번호를 입력해주세요 : ");
				scanf("%s", Member_L->cur->phoneNum);
				printf("변경이 완료되었습니다.\n");
				break;
			case 4:
				printf("메뉴로 돌아갑니다.\n");
				return;
			default:
				printf("잘못 입력하셨습니다.\n");
				break;
	}
	save_file();
	getchar();
	printf("아무키나 누르시면 계속합니다.\n");
	getch();
	}
}

void myborrow_list(void)
{
	bT *btp = Borrow_L->head;
	B *bp;
	struct tm *t;
	system("clear");
	while(btp != NULL)
	{
		if(Member_L->cur->stdNum == btp->stdNum)
		{
			bp = Book_L -> head;
			while(bp != NULL)
			{

				if(btp->bookNum == bp->bookNum)
				{
					printf("도서번호 : %07d\n",bp->bookNum);
					printf("도서명 : %s\n",bp->bookName);
					t = localtime(&btp->borrowT);				// 요일 쉽게 알기 위해 구조체 사용
					printf("대여 일자 : %d년 %d월 %d일 %s요일\n",t->tm_year+1900, t->tm_mon+1, t->tm_mday, day_of_the_week(t->tm_wday));
					t = localtime(&btp->returnT);
					printf("반납 일자 : %d년 %d월 %d일 %s요일\n",t->tm_year+1900, t->tm_mon+1, t->tm_mday, day_of_the_week(t->tm_wday));
					break;
				}
				bp = bp -> next;
			}
		}
		btp = btp->next;
	}
	return;
}

void out_member(void)
{
	if(Member_L->cur->next == NULL)				// tail일때
	{
		Member_L->tail = Member_L->cur->prev;
		Member_L->tail->next = NULL;
	}
	else
		Member_L->cur->next->prev = Member_L->cur->prev;

	if(Member_L->cur->prev == NULL)				// head 일때
	{
		Member_L->head = Member_L->cur->next;
		Member_L->head->prev = NULL;
	}
	else
		Member_L->cur->prev->next = Member_L->cur->next;
	
	free(Member_L->cur);
	Member_L->cur = NULL;
	Member_L->cnt--;							// 카운트 하나 감소
	sort_Member();
	save_file();
	return;
}

void search_name()
{
	char input[50] = {'\0',};
	ISBN_List *chk;
	chk = (ISBN_List *) malloc(sizeof(ISBN_List));
	chk->head = chk->tail = NULL;
	B *bp = Book_L -> head;
	printf("도서명을 입력해 주세요 : ");
	fgets(input,sizeof(input), stdin);
	input[strlen(input)-1] = '\0';
	system("clear");
	while(bp != NULL)
	{
		if(!strcmp(bp->bookName, input))
		{
			if(insertNode_ISBN(chk_ISBN(bp,chk),chk))
				print_book(bp);
		}
		bp = bp -> next;
	}
	delete_ISBN(chk);
	free(chk);
	return;
}

void search_pub()
{
	char input[50] = {'\0',};
	ISBN_List *chk;
	chk = (ISBN_List *) malloc(sizeof(ISBN_List));
	chk->head = chk->tail = NULL;
	B *bp = Book_L -> head;
	printf("출판사를 입력해 주세요 : ");
	fgets(input, sizeof(input), stdin);
	input[strlen(input)-1] = '\0';
	system("clear");
	while(bp != NULL)
	{
		if(!strcmp(bp->bookPub, input))
		{
			if(insertNode_ISBN(chk_ISBN(bp,chk),chk))
				print_book(bp);
		}
		bp = bp -> next;
	}
	delete_ISBN(chk);
	free(chk);
	return;
}
void search_ISBN()
{
	char input[30];
	unsigned long long num;
	ISBN_List *chk;
	chk = (ISBN_List *) malloc(sizeof(ISBN_List));
	chk->head = chk->tail = NULL;
	B *bp = Book_L -> head;
	printf("ISBN을 입력해 주세요 : ");
	fgets(input, sizeof(input), stdin);
	input[strlen(input)-1] = '\0';
	num = atoll(input);
	system("clear");
	while(bp != NULL)
	{
		if(num == bp->ISBN)
		{
			if(insertNode_ISBN(chk_ISBN(bp,chk),chk))
				print_book(bp);
		}
		bp = bp -> next;
	}
	delete_ISBN(chk);
	free(chk);
	return;
}
void search_writer()
{
	char input[50] = {'\0', };
	ISBN_List *chk;
	chk = (ISBN_List *) malloc(sizeof(ISBN_List));
	chk->head = chk->tail = NULL;
	B *bp = Book_L -> head;
	printf("저자명을 입력해 주세요 : ");
	fgets(input, sizeof(input), stdin);
	input[strlen(input)-1] = '\0';
	system("clear");
	while(bp != NULL)
	{
		if(!strcmp(bp->bookWriter, input))
		{
			if(insertNode_ISBN(chk_ISBN(bp,chk),chk))
				print_book(bp);
		}
		bp = bp -> next;
	}
	delete_ISBN(chk);
	free(chk);
	return;
}
void search_all()
{
	B *bp = Book_L -> head;
	while(bp != NULL)
	{
		printf("====================\n");
		printf("도서명 : %s\n", bp->bookName);
		printf("출판사 : %s\n", bp->bookPub);
		printf("저자명 : %s\n", bp->bookWriter);
		printf("ISBN : %lld\n", bp->ISBN);
		printf("소장처 : %s\n", bp->bookWhere);
		printf("대여가능 여부 : %s\n",bp->canBorrow);
		bp = bp -> next;
	}
	return;
}

void print_book(B *cur)
{
	B *bp = Book_L -> head;
	int Y, N;
	Y = N = 0;
	while(bp != NULL)
	{
		if(bp->ISBN == cur->ISBN)
		{
			if(!strcmp(bp->canBorrow, "Y"))
				Y++;
			else
				N++;
		}
		bp = bp->next;
	}
	printf("====================\n");
	printf("도서명 : %s\n", cur->bookName);
	printf("출판사 : %s\n", cur->bookPub);
	printf("저자명 : %s\n", cur->bookWriter);
	printf("ISBN : %lld\n", cur->ISBN);
	printf("소장처 : %s\n", cur->bookWhere);
	printf("대여가능 여부 : %s (%d/%d)\n", (Y>0) ? "Y" : "N", Y, Y+N);
	return;
}

void delete_ISBN(ISBN_List *list)
{
	ISBN_check *cur;
	ISBN_check *next;
	cur = list->head;
	while(cur!=NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	return;
}
unsigned long long chk_ISBN(B *bp, ISBN_List *list)
{
	ISBN_check *new;
	new = list->head;
	while(new != NULL)
	{
		if(new->ISBN == bp->ISBN)
			return false;
		new = new->next;
	}

	return bp->ISBN;
}
bool insertNode_ISBN(unsigned long long ISBN, ISBN_List *list)
{
	if (ISBN == false)	// return값이 false라면 추가하지 않고 종료
		return false;

	ISBN_check *new = (ISBN_check *)malloc(sizeof(ISBN_check));
	new->ISBN = ISBN;
	new->next = NULL;
	if(list->head == NULL && list->tail == NULL)
		list->head = list->tail = new;
	else
	{
		list->tail->next = new;
		list->tail = new;
	}
	return true;
}

void admin_menu()
{
	int input;
	while(1)
	{
		system("clear");
		printf(">> 관리자 메뉴 <<\n");
		printf("1. 도서 등록		2. 도서 삭제\n");
		printf("3. 도서 대여		4. 도서 반납\n");
		printf("5. 도서 검색		6. 회원 목록\n");
		printf("7. 로그아웃		  8. 프로그램 종료\n");
		printf("숫자를 입력해주세요 : ");

		scanf("%d",&input);
		getchar();
		switch(input)
		{
			case 1:
				add_book();
				break;
			case 2:
				remove_book();
				break;
			case 3:
				borrow_book();
				break;
			case 4:
				return_book();
				break;
			case 5:
				search_all();
				break;
			case 6:
				member_list();
				break;
			case 7:
				return;
			case 8:
				printf("프로그램을 종료합니다.\n");
				sort_Member();
				sort_Book();
				exit(0);
			default:
				printf("다시 입력해주세요.\n\n");
			
		}
		sort_Book();
		save_file();
		printf("아무키나 입력하시면 계속합니다.\n");
		getch();
	}
}

void add_book()
{
	char input;
	B newB;
	system("clear");
	printf("도서명 : ");
	scanf("%s", newB.bookName);
	printf("출판사 : ");
	scanf("%s", newB.bookPub);
	printf("저자명 : ");
	scanf("%s", newB.bookWriter);
	printf("ISBN : ");
	scanf("%lld", &newB.ISBN);
	printf("소장처 : ");
	scanf("%s", newB.bookWhere);
	getchar();
	printf("\n\n자동 입력 사항\n");
	printf("대여가능 여부  : Y\n");
	memcpy(newB.canBorrow,"Y",2);
	Book_L->topNum+=1;
	printf("도서번호 : %07d\n", Book_L->topNum);
	newB.bookNum = Book_L->topNum;
	printf("등록하시겠습니까 ? (Y/N) : ");
	scanf("%c", &input);
	if(input != 'Y')
	{
		printf("등록을 취소합니다.\n");
		return;
	}
	insertNode_Book(newB);
	sort_Book();
	save_file();
	printf("등록이 완료되었습니다.\n");
	return;
}
void remove_book()
{
	int input;
	system("clear");
	printf(">> 도서 제거 <<\n");
	printf("1. 도서명 검색	2. ISBN 검색\n\n");
	printf("검색 번호를 입력하세요 : ");
	scanf("%d", &input);

	switch(input)
	{
		case 1:
			if(admin_name())
				remove_ask();
			else
				printf("검색 결과가 없습니다.\n");
			break;
		case 2:
			if(admin_ISBN())
				remove_ask();
			else
				printf("검색 결과가 없습니다.\n");
			break;
		default:
		printf("잘못 입력하셨습니다.\n");
	}
	save_file();
	return;
}

void borrow_book()
{
	int input;
	system("clear");
	printf(">> 도서 대여 <<\n");
	printf("1. 도서명 검색 	 2. ISBN 검색\n\n");
	printf("검색 번호를 입력하세요 : ");
	scanf("%d",&input);
	switch(input)
	{
		case 1:
			if(admin_name())
				borrow_ask();
			else
				printf("검색 결과가 없습니다.\n");
			break;
		case 2:
			if(admin_ISBN())
				borrow_ask();
			else
				printf("검색 결과가 없습니다.\n");
			break;
		default:
			printf("잘못 입력하셨습니다.\n");
	}
	save_file();
	return;
}

void return_book()
{
	bT *btp = Borrow_L->head;
	B *bp = Book_L -> head;
	int input;
	char YN;
	struct tm *t;
	system("clear");
	printf(">> 회원의 대여 목록 <<\n");
	while(btp != NULL)
	{
		printf("================\n");
		printf("도서번호 : %07d\n", btp->bookNum);
		while(bp != NULL)
		{
			if(bp->bookNum == btp->bookNum)
			{
				printf("도서명 : %s\n",bp->bookName);
				break;
			}
			bp = bp -> next;
		}
		t = localtime(&btp->borrowT);
		printf("대여 일자 : %d년 %d월 %d일 %s요일\n",t->tm_year+1900, t->tm_mon+1, t->tm_mday, day_of_the_week(t->tm_wday));
		t = localtime(&btp->returnT);
		printf("반납 일자 : %d년 %d월 %d일 %s요일\n",t->tm_year+1900, t->tm_mon+1, t->tm_mday, day_of_the_week(t->tm_wday));
		btp = btp -> next;
	}
	printf("\n반납할 도서번호를 입력하세요 : ");
	scanf("%d",&input);
	getchar();
	btp = Borrow_L -> head;
	while(btp != NULL)
	{
		if(btp->bookNum == input)
		{
			printf("도서 반납처리를 할까요? (Y/N) : ");
			scanf("%c", &YN);
			getchar();
			if(YN == 'Y')
			{
				remove_borrow(btp);
				save_file();
				return;
			}
			else
			{
				printf("도서 반납을 취소합니다.\n");
				return;
			}
		}
		btp = btp -> next;
	}
	printf("도서 정보가 잘못되었습니다.\n");
	return;
}

void member_list()
{
	int input;
	system("clear");
	printf(">> 회원 목록 <<\n");
	printf("1. 이름 검색 	2. 학번 검색\n");
	printf("3. 전체 검색		4. 이전 메뉴\n");
	printf("\n번호를 입력하세요 : ");
	scanf("%d",&input);
	getchar();
	switch(input)
	{
		case 1:
			search_adminName();
			break;
		case 2:
			search_adminNum();
			break;
		case 3:
			search_adminAll();
			break;
	}
	return;
}

void remove_ask()
{
	B *bp = Book_L -> head;
	int bookNum;
	bool bok = false;
	printf("삭제할 도서의 번호를 입력하세요 : ");
	scanf("%d", &bookNum);
	getchar();

	while(bp != NULL)
	{
		if((bp -> bookNum == bookNum) && !strcmp(bp -> canBorrow, "Y")) 	// 도서가 존재하고 대여 가능한지 체크
		{
			bok = true;
			break;
		}
		bp = bp -> next;
	}

	if(!bok)
	{
		printf("도서 정보가 잘못되었습니다.\n");
		return;
	}

	if(bp->next == NULL)
	{
		Book_L->tail = bp->prev;
		bp->prev->next = NULL;
	}
	else
		bp->next->prev = bp->prev;

	if(bp->prev == NULL)
	{
		Book_L->head = bp->next;
		bp->next->prev = NULL;
	}
	else
		bp->prev->next = bp->next;

	free(bp);
	Book_L->cnt--;
	printf("삭제되었습니다.\n");
	return;
}

void borrow_ask()
{
	bT btp;
	int stdNum, bookNum;
	char YN;
	time_t now_time;
	struct tm *t;
	bool std = false, bok = false;		// 학번, 도서 가능 여부 확인
	B *bp = Book_L -> head;
	M *mp = Member_L -> head;
	printf("학번을 입력하세요 : ");
	scanf("%d", &stdNum);
	printf("도서번호를 입력하세요 : ");
	scanf("%d", &bookNum);
	getchar();
	while(mp != NULL)
	{
		if(mp -> stdNum == stdNum)			// 학번이 존재하는지 체크
		{
			std = true;
			break;
		}
		mp = mp -> next;
	}
	if(!std)
	{
		printf("학번 정보가 잘못되었습니다.\n");
		return;
	}
	while(bp != NULL)
	{
		if((bp -> bookNum == bookNum) && !strcmp(bp -> canBorrow, "Y")) 	// 도서가 존재하고 대여 가능한지 체크
		{
			bok = true;
			break;
		}
		bp = bp -> next;
	}
	if(!bok)
	{
		printf("도서 정보가 잘못되었습니다.\n");
		return;
	}
	printf("이 도서를 대여합니까 ? (Y/N) : ");
	
	scanf("%c",&YN);
	if(YN == 'Y')
	{
		time(&now_time);
		btp.stdNum = stdNum;
		btp.bookNum = bookNum;
		btp.borrowT = now_time;
		now_time+=2592000;
		t = localtime(&now_time);
		if(t->tm_wday == 0)				// 만약 반납일이 일요일(=0) 일때 체크
			now_time+=86400;			// 하루 추가
		btp.returnT = now_time;
		insertNode_Borrow(btp);
		memcpy(bp->canBorrow,"N",2);
		printf("대여가 완료되었습니다.\n");
		getchar();
	}
	else
		printf("대여를 취소합니다.\n");
	return;
}

bool admin_borrow(B *bp)
{
	printf("================\n");
	printf("도서 번호 : %07d (가능 여부 : %s)\n", bp->bookNum, bp -> canBorrow);
	printf("도서명 : %s\n", bp -> bookName);
	printf("출판사 : %s\n", bp -> bookPub);
	printf("저자명 : %s\n", bp -> bookWriter);
	printf("ISBN : %lld\n", bp -> ISBN);
	printf("소장처 : %s\n", bp -> bookWhere);
	return true;
}

bool admin_name()
{
	char input[50] = {'\0',};
	bool available = false;							// 검색 결과가 있는지 없는지 판단
	ISBN_List *chk;
	chk = (ISBN_List *) malloc(sizeof(ISBN_List));
	chk -> head = chk -> tail = NULL;
	B *bp = Book_L -> head;
	printf("도서명을 입력하세요 : ");
	getchar();
	fgets(input, sizeof(input), stdin);
	input[strlen(input)-1] = '\0';
	system("clear");
	printf(">> 검색 결과 <<\n");
	while(bp != NULL)
	{
		if(!strcmp(bp->bookName, input))
			if(insertNode_ISBN(chk_ISBN(bp, chk), chk))
				available = admin_borrow(bp);		// 검색 결과가 하나라도 있다면 true로 변경
		bp = bp -> next;
	}
	delete_ISBN(chk);
	free(chk);
	return available;
}

bool admin_ISBN()
{
	long long int input;
	bool available = false;
	ISBN_List *chk;
	chk = (ISBN_List *) malloc(sizeof(ISBN_List));
	chk -> head = chk -> tail = NULL;
	B *bp = Book_L -> head;

	printf("ISBN을 입력하세요 : ");
	scanf("%lld", &input);
	system("clear");
	printf(">> 검색 결과 <<\n");
	while(bp != NULL)
	{
		if(bp->ISBN == input)
			if(insertNode_ISBN(chk_ISBN(bp, chk), chk))
				available = admin_borrow(bp);
		bp = bp -> next;
	}
	delete_ISBN(chk);
	free(chk);
	return available;
}

void remove_borrow(bT *btp)
{
	B *bp = Book_L -> head;
	while(bp != NULL)
	{
		if(bp->bookNum == btp -> bookNum)
		{
			memcpy(bp->canBorrow, "Y", 2);
			break;
		}
		bp = bp -> next;
	}

	if(btp->next == NULL)
	{
		Borrow_L->tail = btp->prev;
		btp ->prev->next = NULL;
	}
	else
		btp->next->prev = btp->prev;

	if(btp->prev == NULL)
	{
		Borrow_L->head = btp->next;
		btp->next->prev = NULL;
	}
	else
		btp->prev->next = btp->next;
	save_file();
}

char* day_of_the_week(int day)
{
	switch(day)
	{
		case 0:
			return "일";
		case 1:
			return "월";
		case 2:
			return "화";
		case 3:
			return "수";
		case 4:
			return "목";
		case 5:
			return "금";
		case 6:
			return "토";
	}
}

void print_member(M* mp)
{
	printf("===============\n");
	printf("학번 : %08d\n", mp ->stdNum);
	printf("이름 : %s\n", mp -> name);
	printf("주소 : %s\n", mp->address);
	printf("전화번호 : %s\n", mp->phoneNum);
	return;
}

void search_adminName()
{
	char input[50] = {'\0'};
	M *mp = Member_L -> head;
	printf("이름을 입력해 주세요 : ");
	fgets(input, sizeof(input), stdin);
	input[strlen(input)-1] = '\0';
	system("clear");
	while(mp != NULL)
	{
		if(!strcmp(mp->name, input))
			print_member(mp);
		mp = mp -> next;
	}
	return;
}

void search_adminNum()
{
	int input;
	M *mp = Member_L -> head;
	printf("학번을 입력해 주세요 : ");
	scanf("%d", &input);
	getchar();
	system("clear");
	while(mp != NULL)
	{
		if(mp->stdNum == input)
			print_member(mp);
		mp = mp -> next;
	}
	return;
}

void search_adminAll()
{
	M *mp = Member_L -> head;
	while(mp != NULL)
	{
		print_member(mp);
		mp = mp -> next;
	}
	return;
}