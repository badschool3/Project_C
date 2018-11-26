#include "base.h"
int first_menu(void);			// 메뉴 출력 함수
void join_member(void);			// 회원 가입 함수
int login_member(void);			// 로그인 함수
bool check_member(M);			// 회원 중복 체크 함수

int first_menu()
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
		
		switch(input)
		{
			case 1:
				join_member();
				break;
			case 2:
				check = login_member();
				check ? return check : break;
			case 3:
				return false;
			default:
				printf("다시 입력해주세요.\n");
				break;
		}
	}
}

void join_member()
{
	M MB;
	printf(">> 회원 가입 <<\n");
	printf("학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n\n");
	
	printf("학번 : ");
	scanf("%d",MB.stdNum);
	printf("비밀번호 : ");
	scanf("%s",MB.passwd);
	printf("이름 : ");
	scanf("%s",MB.name);
	printf("주소 : ");
	scanf("%s",MB.address);
	printf("전화번호 : ");
	scanf("%s",MB.phoneNum);
	
	if(check_member(MB))
	{
		insertNode_Member(MB);
		printf("\n\n회원가입이 완료되셨습니다.\n");
	}
	else
		printf("중복된 정보를 가진 회원이 존재합니다.\n");
	return;
	
}

int login_member()
{
	char num[8];
	char password[20];
	M *mp = Member_L -> head;
	printf("학번 : ");
	scanf("%s", num);
	printf("비밀번호 : ");
	scanf("%s", passwd);
	
	while(mp != NULL)
	{
		if(!(strcmp(mp->stdNum, num) && !(strcmp(mp->passwd, password))))			// 학번, 비밀번호가 일치하는지 비교
		{
			if(!(strcmp(num,"admin")))					// 만약 admin이라면 관리자 메뉴를 위해 2 반환
				return 2;
			else
			{
				Member_L -> cur = mp;					// 일반 회원이라면 cur가 mp를 포인트 하고 1 반환
				return 1;
			}
		}

		mp = mp -> next;
	}
	printf("로그인 정보가 틀립니다.\n");
	return false;										// 로그인 실패 시 0 반환
}

bool check_member(M m1)
{
		M *mp = Member_L -> head;
		while(mp != NULL)
		{
			if(!(strcmp(mp -> stdNum, m1.stdNum))
				return false;
			mp = mp -> next;
		}
		return true;
}
