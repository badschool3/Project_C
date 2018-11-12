#include "base.h"

void myborrow_list(void);	// 내 대여 목록 함수
void change_info(void);		// 개인정보 수정 함수
void out_member(void);		// 회원 탈퇴 함수

void member_menu()
{
	int input;
	while(1)
	{
		printf(">> 회원 메뉴 <<\n");
		printf("1. 도서 검색		2. 내 대여 목록\n");
		printf("3. 개인정보 수정	4. 회원 탈퇴\n");
		printf("5. 로그아웃			6. 프로그램 종료\n");
		printf("숫자를 입력해주세요 : ");

		scanf("%d",&input);
		
		switch(input)
		{
			case 1:
				search_book();
				break;
			case 2:
				myborrow_list();
				break;
			case 3:
				change_info();
				break;
			case 4:
				out_member();
				break;
			case 5:
				now_logout();

		}
	}
	
}
