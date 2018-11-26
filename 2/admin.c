#include "base.h"

void add_book(void);			// 도서 등록
void remove_book(void);			// 도서 삭제
void borrow_book(void);			// 도서 대여
void return_book(void);			// 도서 반납
void member_list(void);			// 회원 목록

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
		printf("7. 로그아웃			8. 프로그램 종료\n");
		printf("숫자를 입력해주세요 : ");

		scanf("%d",&input);
		
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
				search_book();
				break;
			case 6:
				member_list();
				break;
			case 7:
				now_logout();
				break;
			default:
				printf("다시 입력해주세요.\n\n");
			printf("아무키나 입력하시면 계속합니다.\n");
			getch();
		}
	}
}
