#include "base.h"

void myborrow_list(void);	// 내 대여 목록 함수
void change_info(void);		// 개인정보 수정 함수
void out_member(void);		// 회원 탈퇴 함수

void search_menu(void);		// 도서 검색 메뉴 함수
void search_name(void);		// 도서명 검색 함수
void search_pub(void);		// 출판사 검색 함수
void search_ISBN(void);		// ISBN 검색 함수
void search_writer(void);	// 저자명 검색 함수
void search_all(void);		// 전체 검색 함수

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
				scanf("%s", Member_L->cur->number);
				printf("변경이 완료되었습니다.\n");
				break;
			case 4:
				printf("메뉴로 돌아갑니다.\n");
				printf("아무키나 누르시면 계속합니다.\n");
				getch();
				return;
			default:
				printf("잘못 입력하셨습니다.\n");
				break;
	}
	printf("아무키나 누르시면 계속합니다.\n");
	getch();
	}
}

void out_member()
{
		
}
