/* --------include문------- */
#include <stdio.h>
#include <stdbool.h>    // bool 자료형 사용
#include <stdlib.h>
#include <stdarg.h>     // 가변 인자 사용
#include <string.h>
#include <time.h>		// time 함수 사용
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
B_LinkedList *Book_L = (B_LinkedList *)malloc(sizeof(B_LinkedList));
M_LinkedList *Member_L = (M_LinkedList *)malloc(sizeof(M_LinkedList));
bT_LinkedList *Borrow_L = (bT_LinkedList *)malloc(sizeof(bT_LinkedList));

/* -------함수 기능 정의------*/
int compare(const void *a, const void *b)
{
	unsigned long long num1 = *(unsigned long long *)a;		// void 포인터 -> ull 포인터로 변환 후 역참조
	unsigned long long num2 = *(unsigned long long *)b;		// ''
	
	// 현재 오름차순, 부등호 반대 시 내림차순
	if (num1 < num2)
		return -1;			// a가 b보다 클 때 -1 반환
	else if (num2 > num1)
		return 1;			// b가 a보다 클 때 1 반환
	else
		return 0;			// a와 b가 같을 때 0 반환

}

