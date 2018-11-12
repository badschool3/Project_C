#include <stdio.h>
#include <stdlib.h>

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

/* --------변수 정의--------*/
M* MEMBER;
B BOOK;
bT BORROW;

M* loadList(FILE* fp)
{
	M *head = NULL, *p = NULL;

	while(1)
	{
		MEMBER = (M*)malloc(sizeof(M));
		
		int isRead = fread((void*)MEMBER, sizeof(M), 1, fp);
		
		if(!isRead)
			break;

		if(head == NULL)
		{
			head = MEMBER;
			p = MEMBER;
		}
		else
		{
			p->next =MEMBER;
			p = p -> next;
		}
		p->next = NULL;
		return head;
	}
}
