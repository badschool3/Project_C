/* --------include문------- */
#include <stdio.h>
#include <stdbool.h>    // bool 자료형 사용
#include <stdlib.h>
#include <stdarg.h>     // 가변 인자 사용
#include <string.h>
#include <time.h>		// time 함수 사용
#include <termio.h>		// getch() 함수 사용
/* --------define문-------- */

/* --------함수정의-------- */
void first_menu(void);      // 초기 메뉴 함수
void member_menu(void);		// 회원 메뉴 함수
void admin_menu(void);		// 관리자 메뉴 함수
void now_logout(void);		// 로그아웃 함수

void loadMember(void);		// 멤버파일 불러오기
void loadBook(void);		// 도서파일 불러오기
void loadBorrow(void);		// 대여파일 불러오기
void writeMember(void);		// 멤버파일 쓰기
void writeBook(void);		// 도서파일 쓰기
void writeBorrow(void);		// 대여파일 쓰기

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
	char bookPub[50];		// 출판사
	unsigned long long ISBN;// ISBN (정수 13자리)
	char bookWhere[50];		// 소장처
	char canBorrow[3];		// 대여가능 여부
	struct book *next;
	struct book *prev;
}B;
typedef struct borrow{		// 대여구조체
	int stdNum;				// 학생번호 (정수 7자리)
	int bookNum;			// 도서번호	(정수 8자리)
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
	int cnt;
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
