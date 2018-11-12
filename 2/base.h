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

void search_menu(void);		// 도서 검색 메뉴 함수
void search_name(void);		// 도서명 검색 함수
void search_pub(void);		// 출판사 검색 함수
void search_ISBN(void);		// ISBN 검색 함수
void search_writer(void);	// 저자명 검색 함수
void search_all(void);		// 전체 검색 함수

/* --------구조체정의-------*/
typedef struct member{		// 학생구조체
	int stdNum;				// 학생번호
	char passwd[20];		// 비밀번호
	char name[10];			// 이름
	char address[20];		// 주소
	char phoneNum[12];		// 전화번호
}M;
typedef struct book{		// 도서구조체
	int bookNum;			// 도서번호
	char bookName[20];		// 도서이름
	char bookPub[10];		// 출판사
	unsigned long long ISBN;// ISBN
	char bookWhere[15];		// 소장처
	char canBorrow[10];		// 대여가능 여부
}B;
typedef struct borrow{		// 대여구조체
	int stdNum;				// 학생번호
	int bookNum;			// 도서번호
	time_t borrowT;			// 대여시간
	time_t returnT;			// 반납시간
}bT;

/* -------함수 기능 정의------*/
int compare(const void *a, const void *b)
{
	unsigned long long num1 = *(unsigned long long *)a;
	unsigned long long num2 = *(unsigned long long *)b;
	if (num1 < num2)
		return -1;
	else if (num2 > num1)
		return 1;
	else
		return 0;
}

