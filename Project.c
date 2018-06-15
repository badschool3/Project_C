#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>	
#include <unistd.h>	
#include <termios.h>

#define TRUE 1
#define FALSE 0
#define COLOR_YELLOW "\x1b[33m"		// 글자에 색깔 적용
#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"		// 글자의 색깔 지우기

void clearBuffer();			// 버퍼 정리
int menu();					// 메뉴
int getch();				// getch 구현
void spacePractice();		// 자리 연습
void wordPractice();		// 단어 연습
void shortScript();			// 짧은글 연습
void longScript();			// 긴글 연습
int abs(int);				// 절댓값

int main(void)
{
	while (menu() != FALSE);
	system("clear");
	return 0;
}

void clearBuffer()
{
	while (getchar() != '\n');
}

int abs(int x)
{
	return (x > 0) ? x : -x;
}

int getch(void)  
{  
  int ch;  
  struct termios buf;  
  struct termios save;  
  
   tcgetattr(0, &save);  
   buf = save;  
   buf.c_lflag &= ~(ICANON|ECHO);  
   buf.c_cc[VMIN] = 1;  
   buf.c_cc[VTIME] = 0;  
   tcsetattr(0, TCSAFLUSH, &buf);  
   ch = getchar();  
   tcsetattr(0, TCSAFLUSH, &save);  
   return ch;  
}  
  
int menu()
{
	int input;
	system("clear");

	printf(">> 영문 타자 연습 프로그램 <<\n");
	printf("1) 자리 연습	2) 낱말 연습\n\
3) 짧은 글 연습	4) 긴 글 연습\n\
5) 프로그램 종료\n\n\
번호를 선택하세요: ");
	scanf("%d", &input);
	clearBuffer();
	switch (input)
	{
	case 1:
		spacePractice();
		return TRUE;
	case 2:
		wordPractice();
		return TRUE;
	case 3:
		shortScript();
		return TRUE;
	case 4:
		longScript();
		return TRUE;
	case 5:
		return FALSE;
	}
}

void spacePractice()
{
	/*
		prog : 진행도
		wrong : 틀린개수
		acc : 정확도
		insert : 입력횟수
		word : 랜덤값
		input : 입력값 
	*/
	int prog, wrong, acc, insert;
	short word;
	char input;
	wrong = prog = insert = acc = 0;

	while (prog < 20)
	{
		srand(time(NULL));
		word = (rand() % 58) + 65;
		if (word >= 91 && word <= 96)	// 문자 범위 체크
			continue;					// 만약 특수문자라면 다시 랜덤 값 가져옴

		while (1)
		{
			input = 0;
			if (insert != 0)
				acc = 100 - (100 * wrong / insert);
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 자리 연습 <<\n");
			printf(">> [ESC]를 누르면 메뉴로 돌아갑니다. <<\n");
			printf("진행도 : %d%%	오타수 : %d		정확도 : %d%%\n\n", (prog * 100 / 20), wrong, acc);
			printf("%c\n-", word);
			input = getch();
			insert++;
			if ((int)input == word || (int)input == 27)		// 입력값이 정답이거나 ESC를 눌렀다면 break
				break;
			else
				wrong++;									// 아니라면 오타수만 증가하고 같은 문자 사용
		}
		if (input == 27)									// ESC 입력 시 종료
		{
			printf("\n=====================\n");
			printf("[ESC]를 누르셨습니다. 엔터키를 누르시면 메뉴로 돌아갑니다.");
			while(getch()!=10);
			return;
		}
		prog++;
	}
	system("clear");
	printf("\n=====================\n");
	printf("진행도 : %d%%	오타수 : %d		정확도 : %d%%\n", (prog * 100 / 20), wrong, acc);
	printf("자리 연습이 끝났습니다. 엔터키를 누르시면 메뉴로 돌아갑니다.");
	while(getch()!=10);
}

void wordPractice()
{
	/*
		prog : 진행도
		wrong : 틀린개수
		acc : 정확도
		insert : 입력횟수
		word : 단어
		myWord : 랜덤값
		input : 입력값 
	*/
	int prog, wrong, acc, insert;
	short myWord;
	char *word[] = { "address", "practice", "available", "measure", "claim", "draw",
	 "issue", "raise", "work", "fall", "arrange", "make", "develop", "order", "serve", "effort",
	 "approach", "reach", "contain", "break", "change", "have", "follow", "direct", "receive",
	 "perform", "purchase", "place","above", "exercise", "produce", "choose", "report", "cover",
	 "examine", "drive", "plant", "patient", "instrument", "check", "show", "toward", "avoid", "carry",
	 "upon", "article", "around", "right", "construction", "stock", "board", "drop", "clear", "grow",
	 "equipment", "vendor", "wait", "borrow", "structure", "stack", "frame", "roll", "fuel", "occupy",
	 "transport", "drill", "cut", "disembark", "lie", "sun", "obscure", "balcony", "touch", "steer",
	 "behind", "roost", "athlete", "waddle", "secretary", "facsimile", "handle", "scuffle", "space", "ivy",
	 "empty", "accost", "walk", "motorcycle", "beneath", "page", "relax", "cardboard", "tension", "bush",
	 "crop","standby", "pair", "cower", "arrive", "yard"};
	char input[20] = { '\0' };

	wrong = prog = insert = acc = myWord = 0;

	while (prog < 20)
	{
		srand(time(NULL));
		myWord = (rand() % 100);
		while (1)
		{
			if (insert != 0)
				acc = 100 - (100 * wrong / insert);		// 정확도 계산
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 낱말 연습 <<\n");
			printf(">> [###]를 입력하시면 메뉴로 돌아갑니다. <<\n");
			printf("진행도 : %d%%	오타수 : %d		정확도 : %d%%\n\n", (prog * 100 / 20), wrong, acc);
			puts(word[myWord]);
			fgets(input, sizeof(input) / sizeof(input[0]), stdin);			// 버퍼오버플로우를 방지하기 위해 fgets 사용
			if (input[strlen(input) - 1] == '\n')		// fgets에서 입력받은 개행문자 제거
				input[strlen(input) - 1] = '\0';
			insert++;									// 입력횟수 증가
			if ((!strcmp(input, word[myWord])) || (!strcmp(input, "###")))
				break;									// 입력 값이 정답이거나 ###이라면 break
			else
			{
				wrong++;								// 입력 값이 오답일 때 오타수 증가
				break;
			}
		}
		if (!strcmp(input, "###"))						// break로 빠져나온 후 앞서 입력받은 값이 ### 이었다면 메뉴로 돌아감
			{
				printf("\n=====================\n");
				printf("[###]를 입력하셨습니다. 엔터키를 누르시면 메뉴로 돌아갑니다.");
				while(getch()!=10);
				return;
			}
		prog++;
	}
	system("clear");
	printf("\n=====================\n");
	printf("진행도 : %d%%	오타수 : %d		정확도 : %d%%\n", (prog * 100 / 20), wrong, acc);
	printf("낱말 연습이 끝났습니다. 엔터키를 누르시면 메뉴로 돌아갑니다.");
	while(getch()!=10);
}

void shortScript()
{
	/*
		prog : 진행도
		wrong : 틀린개수
		acc : 정확도
		nTasu : 현재타수
		MTasu : 최고타수
		nCol : 현재열
		cntTasu : 정답개수
		randS : 랜덤값
		start, end : 타수 계산 위한 시간
		errorS, errorE : 연산으로 인한 오차를 최소화 하기 위한 시간
		sScript : 짧은글
		inputScript : 입력값
		i : 반복문을 위한 카운터변수, 표준을 위해 미리 선언
	*/
	char sScript[][30] = { "I like A.", "I like B.", "I like C.", "I like D.", "I like E.", "I like F.", "I like G.", "I like H.",
		"I like I.", "I like J.", "I like K.", "I like L.", "I like M.", "I like N.", "I like O.", "I like P.", "I like Q.",
		"I like R.", "I like S.", "I like T.", "I like U.", "I like V.", "I like W.", "I like X.", "I like Y.", "I like Z.",
		"I like a.", "I like b.", "I like c.", "I like d." };
	char inputScript[30] = { '\0' };
	int prog, nTasu, MTasu, acc, wrong, nCol, cntTasu, i;
	double cTime, eTime;
	short randS;

	struct timeval start, end, errorS, errorE;
	prog = nTasu = MTasu = acc = wrong = cntTasu = 0;

	while (prog < 5)
	{
		nCol = nTasu = acc = 0;
		srand(time(NULL));
		randS = (rand() % 30);				// 랜덤 값 가져옴

		for(i = 0; i < 30; i++)				// 입력 변수 초기화
			inputScript[i] = '\0';

		gettimeofday(&start, NULL);
		while (nCol < strlen(sScript[randS]) + 1)	// 원문 길이보다 한번 더 반복
		{
			gettimeofday(&errorS, NULL);			// 오차 줄이기 위해 출력되는 동안의 시간을 측정
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<\n");
			printf(">> [ESC]를 누르면 메뉴로 돌아갑니다. <<\n");
			printf("진행도 : %d%%  현재타수 : %d  최고타수 : %d  정확도 : %d%%\n\n", (prog * 100) / 5, nTasu, MTasu, acc);
			
			for(i = 0; i < strlen(sScript[randS]); i++)		// 가독성을 높이기 위해 현재 입력하는곳 빨간색 적용
			{
				if(i==nCol)
					printf(COLOR_RED"%c",sScript[randS][i]);
				else
					printf("%c",sScript[randS][i]);
				printf(COLOR_RESET);
			}
			printf("\n");
			fputs(inputScript, stdout);

			gettimeofday(&errorE, NULL);	// 출력되는 동안의 시간을 측정
			inputScript[nCol] = getch();
			
			gettimeofday(&end, NULL);
			if ((inputScript[nCol] == 8 || inputScript[nCol] == 127) && nCol > 0)
			{								// 현재 입력한 갯수가 1개 이상이고 backspace일 때
				inputScript[nCol] = '\0';	// 입력 값이 backspace라면 backspace값과 그 전 값을 지우고 nCol--
				inputScript[nCol-1] = '\0';	
				nCol--;
			}
			else if ((inputScript[nCol] == 8 || inputScript[nCol] == 127) && nCol == 0)
				inputScript[nCol] = '\0';	// 현재 입력한 갯수가 0개고 backspace를 입력받았을 때 backspace값만 지움
			else if (inputScript[nCol] == 27 || inputScript[nCol] == 10)
				break;						// 입력 값이 엔터이거나 ESC일 때 break
			else if (nCol >= 0)	
				nCol++;						// 위 조건들에 들어가지 않는 정상적인 입력일 때 nCol++

			wrong = 0;						// wrong을 0으로 초기화
			
			for(i = 0; i < nCol; i++)		// 오타 개수 측정
				if(sScript[randS][i] != inputScript[i])
					wrong++;

			cntTasu = nCol - wrong;			// 입력 개수에서 틀린 개수를 빼어 정답 개수를 측정
			eTime = (errorE.tv_sec + errorE.tv_usec / 1000000.0) - (errorS.tv_sec + errorS.tv_usec / 1000000.0);
			cTime = (end.tv_sec + end.tv_usec / 1000000.0) - (start.tv_sec + start.tv_usec / 1000000.0);
			cTime -= eTime;						// 출력되는 시간의 시간을 빼주어 오차를 최소화

			nTasu = (cntTasu / cTime) * 60;		// 타수 계산

			if(nCol != 0)						// 입력 값이 있을 때 정확도 측정
				acc = 100 - (100 * wrong / nCol);
			else 								// 입력 값이 없을 때 계산오류를 방지하기 위해 0으로 적용
				acc = 0;

			if (nTasu > MTasu)					// 현재타수가 최고타수보다 크다면 최고타수를 현재타수값으로 변경
				MTasu = nTasu;
		}

		if (inputScript[nCol] == 27)			// ESC 입력 시
		{
			printf("\n=====================\n");
			printf("[ESC]를 누르셨습니다. 엔터키를 누르시면 메뉴로 돌아갑니다.");
			while(getch()!=10);
			return;
		}

		for (i = 0; i <= nCol; i++)				// 입력 버퍼 초기화
			inputScript[i] = '\0';
		prog++;
	}
	system("clear");
	printf("\n=====================\n");
	printf("진행도 : %d%%  최고타수 : %d  정확도 : %d%%\n", (prog * 100) / 5, MTasu, acc);
	printf("짧은 글 연습이 끝났습니다. 엔터키를 누르시면 메뉴로 돌아갑니다.");
	while(getch()!=10);
}

void longScript()
{
	/*
		prog : 진행도
		wrong : 틀린개수
		acc : 정확도
		nTasu : 현재타수
		insert : 입력개수
		wrong : 틀린개수
		nCol : 현재열
		nRow : 현재행
		i, j : 반복문을 위한 카운터변수, 표준을 위해 미리 선언
		start, end : 타수 계산 위한 시간
		errorS, errorE : 연산으로 인한 오차를 최소화 하기 위한 시간
		blankSpace : 빈공간 계산
		randL : 랜덤값
		lScript : 긴글
		inputScript : 입력값
	*/
	char lScript[4][10][100] = 
	{
		{
			"The Selfish Giant",
			"Every afternoon, as they were coming from school, the children used",
			"to go and play in the Giant's garden.",
			"It was a large lovely garden, with soft green grass. Here and there",
			"over the grass stook beautiful flowers like starts, and there were twelve",
			"peachtrees that in the springtime broke out into delicate blossoms of pink",
			"and in the autumn bore rich fruit. The birds sat in the trees and sang so",
			"sweetly that the children used to stop their games in order to listen to them.",
			"How happy we are here! they cried to each other.",
			"One day the Giant came back."
		},
		{
			"The Elves and the Shoemaker",
			"There was once a shoemaker, who, through no fault of his own, became",
			"so poor that at last he had nothing left but just enough leather to",
			"make one pair of shoes. He cut out the shoes at night, so as to set to",
			"work upon them next morning, and as he had a good conscience, he laid",
			"himself quietly down in his bed, committed himself to heaven, and fell",
			"asleep. In the morning, after he had said his prayers, and was going",
			"to get to work, he found the pair of shoes make and finished, and standing",
			"on his table. He was very much astonished, and could not tell",
			"what to think, and he took the shoes in his hand to examine then more nearly."
		},
		{
			"Rapunzel",
			"There once lived a man and his wife, who had long wished for a child,",
			"but in vain. Now there was at the back of their house a little window",
			"which overlooked a beautiful garden full of the finest vegetables and",
			"flowers. but there was a high wall all round it, and no one ventured",
			"into it, for it belonged to a witch of great might, and of whom all",
			"the world was afraid. One day, when the wife was standing at the window",
			"and looking into the garden, she saw a bed filled with the finest",
			"rampion, and it looked so fresh and green that she began to wish for",
			"some, and at length she longed for it greatly"
		},
		{
			"Programming is Best class!",
			"I am a student at Soongsil University School of Software",
			"It have a programming class and I like it the most",
			"The professor is very friendly and funny.",
			"I believe the professor will give me a good score :D",
			"I thought a page was over, but it was two pages.",
			"So I thought it was over. Programming is fun too.",
			"There are still three more lines left. What should I say.",
			"Professor Kim is a very good professor!",
			"It's finally over! Programming was really fun."
		}
	};

	char inputScript[10][100] = {'\0'};
	int nCol, nRow, i, j;
	double cTime, eTime, acc, insert, wrong, nTasu;
	short randL;
	int blankSpace;
	struct timeval start, end, errorS, errorE;
	nTasu = acc = wrong = nRow = nCol = insert = cTime = eTime = 0;
	srand(time(NULL));
	randL = (rand() % 4);					// 랜덤 값 가져옴
	gettimeofday(&start, NULL);
	while(nRow < 10)						// 총 10개의 행 반복
	{
		while(1)
		{
			gettimeofday(&errorS, NULL);
			system("clear");
			wrong = 0;
			blankSpace = strlen(lScript[randL][nRow]) - strlen(inputScript[nRow]);		// 값을 입력하지 않은 개수 체크

			for(i = 0; i <= nRow; i++)
			{
				for(j = 0; j < strlen(lScript[randL][i]); j++)							// 오타 수 계산
					if((lScript[randL][i][j] != inputScript[i][j]))
						wrong++;
				if(i == 0)
					wrong -= blankSpace;
			}
			if(insert == 0)					// 첫 번째 입력이라면 계산 오류 방지를 위해 0으로 적용
			{
				acc = nTasu = 0;
			}
			else
			{
				acc = 100.0 - ((100.0 * wrong) / insert);			// 정확도 계산
				nTasu = ((insert - wrong) / cTime) * 60;			// 현재 타수 계산
			}		
			printf(">> 영문 타자 연습 프로그램 : 긴 글 연습 <<\n");
			printf(">> [ESC]를 누르면 메뉴로 돌아갑니다. <<\n");
			printf("정확도 : %.0lf%%		현재타수 : %.0lf\n\n", acc, nTasu);

			if(nRow < 5)						// 첫 번째 페이지 5행 반복
			{
				for(i = 0; i < 5; i++)
				{
					if(i==nRow)					// 현재 유저가 입력하고 있는 줄이라면 가독성을 위해 색깔 입힘
					{
							for(j = 0; j < strlen(lScript[randL][i]); j++)
							{
								if(j==nCol)
									printf(COLOR_RED"%c",lScript[randL][i][j]);		// 현재 입력하는 글자 빨간색 적용
								else
									printf(COLOR_YELLOW"%c",lScript[randL][i][j]);	// 현재 입력하는 줄 	노란색 적용
								printf(COLOR_RESET);
							}
							printf("\n");
					}
					else 						// 아니라면 그냥 출력
						puts(lScript[randL][i]);
				}
				printf("\n");

				for(i = 0; i < nRow; i++)			// 현재 유저가 입력한 값 출력
					puts(inputScript[i]);
				fputs(inputScript[nRow], stdout);	// 마지막 행은 개행문자 제거를 위해 fputs 사용
			}
			else 									// 두 번째 페이지 5행 반복
			{
				for(i = 5; i < 10; i++)
				{
					if(i==nRow)						// 위의 코드와 동일
					{
							for(j = 0; j < strlen(lScript[randL][i]); j++)
							{
								if(j==nCol)
									printf(COLOR_RED"%c",lScript[randL][i][j]);		// 현재 입력하는 글자 빨간색 적용
								else
									printf(COLOR_YELLOW"%c",lScript[randL][i][j]);	// 현재 입력하는 줄 	노란색 적용
								printf(COLOR_RESET);
							}
							printf("\n");
					}
					else
						puts(lScript[randL][i]);
				}
				printf("\n");

				for(i = 5; i < nRow; i++)
					puts(inputScript[i]);
				fputs(inputScript[nRow], stdout);
			}
			gettimeofday(&errorE, NULL);
			inputScript[nRow][nCol] = getch();				// 입력값 받음
			gettimeofday(&end, NULL);

			eTime = (double)(errorE.tv_sec) + ((double)(errorE.tv_usec) / 1000000.0) - (double)(errorS.tv_sec) + (double)(errorS.tv_usec) / 1000000.0;
			cTime = (double)(end.tv_sec) + ((double)(end.tv_usec) / 1000000.0) - (double)(start.tv_sec) + (double)(start.tv_usec) / 1000000.0;
			cTime -= eTime;									// 총 시간에서 출력 시간을 빼주어 오차를 최소화

			if ((inputScript[nRow][nCol] == 8 || inputScript[nRow][nCol] == 127) && nCol > 0)
			{
				inputScript[nRow][nCol] = '\0';				// 입력 값이 backspace이고 입력한 갯수가 1개 이상일 때
				inputScript[nRow][nCol-1] = '\0';			// backspace 기능 실행
				nCol--;
				insert--;
			}
			else if ((inputScript[nRow][nCol] == 8 || inputScript[nRow][nCol]== 127) && nCol == 0)		// 입력 값이 backspace이고 입력한 갯수가 0개 일 때
				inputScript[nRow][nCol] = '\0';															// backspace 기능 실행 없이 입력한 backspace값만 제거
			else if (inputScript[nRow][nCol] == 27)			// 입력한 값이 ESC 일 때 종료
			{
				printf("\n=====================\n");
				printf("[ESC]를 누르셨습니다. 엔터키를 누르시면 메뉴로 돌아갑니다.");
				while(getch()!=10);
				return;
			}
			else if (inputScript[nRow][nCol] == 10 || strlen(lScript[randL][nRow]) < strlen(inputScript[nRow]))
			{												// 입력값 값이 Enter 이거나 문자를 다 입력하지 않고 Enter를 입력하였을 때
				inputScript[nRow][nCol] = '\0';				// 엔터값 제거
				insert += blankSpace;						// 입력하지 않은 문자들을 입력횟수에 증가
				nRow++;
				nCol = 0;
				break;
			}
			else if(nCol >= 0)
			{												// 위 조건들이 아닌 정상적인 입력을 했을 때
				nCol++;
				insert++;
			}
			
		}
	}
	system("clear");
	printf("\n=====================\n");
	printf("정확도 : %.0lf%%		최종타수 : %.0lf\n", acc, nTasu);
	printf("긴 글 연습이 끝났습니다. 엔터키를 누르시면 메뉴로 돌아갑니다.");
	while(getch()!=10);
}
