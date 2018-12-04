#include "base.h"

void myborrow_list(void);	// 내 대여 목록 함수
void change_info(void);		// 개인정보 수정 함수
void out_member(void);		// 회원 탈퇴 함수
void now_logout(void);		// 로그아웃 함수

void search_menu(void);		// 도서 검색 메뉴 함수
void search_name(void);		// 도서명 검색 함수
void search_pub(void);		// 출판사 검색 함수
void search_ISBN(void);		// ISBN 검색 함수
void search_writer(void);	// 저자명 검색 함수
void search_all(void);		// 전체 검색 함수
void print_book(B*);		// Book 출력 함수

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
				printf("회원 탈퇴가 완료되었습니다.\n");
			case 5:
				now_logout();
				printf("아무키나 누르시면 계속합니다.\n");
				getch();
			case 6:

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

void print_book(B* bp)
{
	printf("====================\n");
	printf("도서명 : %s\n", bp->bookName);
	printf("출판사 : %s\n", bp->bookPub);
	printf("저자명 : %s\n", bp->bookWriter);
	printf("ISBN : %lld\n", bp->ISBN);
	printf("소장처 : %s\n", bp->bookWhere);
	printf("대여가능 여부 : %s\n", bp->canBorrow);
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

void myborrow_list(void)
{
	bT *bt = Borrow_L->head;
	B *bp = Book_L -> head;
	while(bt != NULL)
	{
		if(Member_L->cur->stdNum == bt->stdNum)
		{
			while(bp != NULL)
			{
				if(bt->bookNum == bp->bookNum)
				{
					printf("도서번호 : %d\n",bp->bookNum);
					printf("도서명 : %s\n",bp->bookName);
					printf("대여일자 : %d년 %d월 %d일 %c요일\n",);
					printf("반납일자 : %d년 %d월 %d일 %c요일\n",);
				}
				bp = bp -> next;
			}
		}
		bt = bt->next;
	}
}

void out_member(void)
{
	Book_L->cur->next->prev = Book_L->cur->prev;
	Book_L->cur->prev->next = Book_L->cur->next;
	free(Book_L->cur);
	Book_L->cur = NULL;
}