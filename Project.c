#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>	
#include <unistd.h>	
#include <termios.h>

#define TRUE 1
#define FALSE 0
#define NULL '\0'		// 표준 위해 재정의

void clearBuffer();		// 버퍼 정리
int menu();				// 메뉴
int getch();
void spacePractice();	// 자리 연습
void wordPractice();	// 단어 연습
void shortScript();		// 짧은글 연습
void longScript();		// 긴글 연습
int abs(int);			// 절대값

int main(void)
{
	while (menu() != FALSE);
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

	while (prog <= 20)
	{
		srand(time(NULL));
		word = (rand() % 58) + 65;
		if (word >= 91 && word <= 96)	// 문자 범위 체크
			continue;

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
				wrong++;
		}
		if (input == 27)
		{
			printf("\n=====================\n");
			printf("[ESC]를 누르셨습니다. 아무키나 누르시면 메뉴로 돌아갑니다.");
			getch();
			return;
		}
		prog++;
	}
	printf("\n=====================\n");
	printf("자리 연습이 끝났습니다. 아무키나 누르시면 메뉴로 돌아갑니다.");
	getch();
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
	char *word[] = { "hello", "hi", "help", "apple", "school", "university", "program", "drink", "do", "like", "mean", "word", "hair", "close", "clear", "Buffer", "note", "book", "speak", "listen"};
	char input[20] = { NULL };

	wrong = prog = insert = acc = myWord = 0;

	while (prog <= 20)
	{
		srand(time(NULL));
		myWord = (rand() % 20);
		while (1)
		{
			if (insert != 0)
				acc = 100 - (100 * wrong / insert);		// 정확도 계산
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 낱말 연습 <<\n");
			printf("진행도 : %d%%	오타수 : %d		정확도 : %d%%\n\n", (prog * 100 / 20), wrong, acc);
			puts(word[myWord]);
			fgets(input, sizeof(input), stdin);			// 버퍼오버플로우를 방지하기 위해 fgets 사용

			if (input[strlen(input) - 1] == '\n')
				input[strlen(input) - 1] = '\0';
			insert++;
			if ((!strcmp(input, word[myWord])) || (!strcmp(input, "###")))
				break;
			else
			{
				wrong++;
				break;
			}
		}
		if (!strcmp(input, "###"))
			{
				printf("\n=====================\n");
				printf("[###]를 입력하셨습니다. 아무키나 누르시면 메뉴로 돌아갑니다.");
				getch();
				return;
			}
		prog++;
	}
	printf("\n=====================\n");
	printf("낱말 연습이 끝났습니다. 아무키나 누르시면 메뉴로 돌아갑니다.");
	getch();
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
	char inputScript[30] = { NULL };
	int prog, nTasu, MTasu, acc, wrong, nCol, cntTasu, i;
	double cTime, eTime;
	short randS;

	struct timeval start, end, errorS, errorE;
	prog = nTasu = MTasu = acc = wrong = cntTasu = 0;

	while (prog < 5)
	{
		nCol = nTasu = acc = 0;
		srand(time(NULL));
		randS = (rand() % 30);

		for(i = 0; i < 30; i++)
			inputScript[i] = NULL;

		gettimeofday(&start, NULL);
		while (nCol < 30)
		{
			gettimeofday(&errorS, NULL);
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<\n");
			printf(">> [ESC]를 누르면 메뉴로 돌아갑니다. <<\n");
			printf("진행도 : %d%%  현재타수 : %d  최고타수 : %d  정확도 : %d%%\n\n", (prog * 100) / 5, nTasu, MTasu, acc);
			puts(sScript[randS]);
			fputs(inputScript, stdout);

			gettimeofday(&errorE, NULL);	// 출력되는 동안의 시간을 측정
			inputScript[nCol] = getch();
			
			gettimeofday(&end, NULL);
			if (inputScript[nCol] == 8 && nCol > 0)
			{
				inputScript[nCol] = NULL;
				inputScript[nCol-1] = NULL;
				nCol--;
			}
			else if (inputScript[nCol] == 8 && nCol == 0)
				inputScript[nCol] = NULL;
			else if (inputScript[nCol] == 27 || inputScript[nCol] == 10)
				break;
			else if (nCol >= 0)
				nCol++;

			wrong = 0;
			for(i = 0; i < nCol; i++)
				if(sScript[randS][i] != inputScript[i])
					wrong++;

			cntTasu = nCol - wrong;
			eTime = (errorE.tv_sec + errorE.tv_usec / 1000000.0) - (errorS.tv_sec + errorS.tv_usec / 1000000.0);
			cTime = (end.tv_sec + end.tv_usec / 1000000.0) - (start.tv_sec + start.tv_usec / 1000000.0);
			cTime -= eTime;						// 출력되는 시간의 시간을 빼주어 오차를 최소화

			nTasu = (cntTasu / cTime) * 60;		// 타수 계산

			if(nCol != 0)
				acc = 100 - (100 * wrong / nCol);
			else
				acc = 0;

			if (nTasu > MTasu)
				MTasu = nTasu;
		}

		if (inputScript[nCol] == 27)
		{
			printf("\n=====================\n");
			printf("[ESC]를 누르셨습니다. 아무키나 누르시면 메뉴로 돌아갑니다.");
			getch();
			return;
		}

		for (i = 0; i <= nCol; i++)
			inputScript[i] = NULL;
		prog++;
	}
	printf("\n=====================\n");
	printf("짧은 글 연습이 끝났습니다. 아무키나 누르시면 메뉴로 돌아갑니다.");
	getch();
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

	char inputScript[10][100] = {NULL};
	int nTasu, nCol, nRow, i, j;
	double cTime, eTime, acc, insert, wrong;
	short randL;
	int blankSpace;
	struct timeval start, end, errorS, errorE;
	nTasu = acc = wrong = nRow = nCol = insert = 0;
	srand(time(NULL));
	randL = (rand() % 4);
	gettimeofday(&start, NULL);
	while(nRow < 10)
	{
		while(1)
		{
			gettimeofday(&errorS, NULL);
			system("clear");
			wrong = 0;
			blankSpace = strlen(lScript[randL][nRow]) - strlen(inputScript[nRow]);	// 입력값에서 빈공간 계산
			for(i = 0; i <= nRow; i++)
			{
				for(j = 0; j < strlen(lScript[randL][i]); j++)
					if((lScript[randL][i][j] != inputScript[i][j]))
						wrong++;
				if(i == 0)					// 만약 문자를 다 입력하지 않고 엔터를 눌렀을 시, 입력안한 글자만큼 틀린개수를 더한다
					wrong -= blankSpace;
			}
			if(insert == 0)
				acc = 0;
			else
				acc = 100.0 - (100.0 * wrong / insert);

			printf(">> 영문 타자 연습 프로그램 : 긴 글 연습 <<\n");
			printf(">> [ESC]를 누르면 메뉴로 돌아갑니다. <<\n");
			printf("정확도 : %.0lf%%		현재타수 : %d\n", acc, nTasu);
			if(nRow < 5)					// 첫 번째 페이지
			{
				for(i = 0; i < 5; i++)
					puts(lScript[randL][i]);
				printf("\n");

				for(i = 0; i < nRow; i++)
					puts(inputScript[i]);
				fputs(inputScript[nRow], stdout);
			}
			else 							// 두 번째 페이지
			{
				for(i = 5; i < 10; i++)
					puts(lScript[randL][i]);
				printf("\n");

				for(i = 5; i < nRow; i++)
					puts(inputScript[i]);
				fputs(inputScript[nRow], stdout);
			}
			inputScript[nRow][nCol] = getch();
			gettimeofday(&errorE, NULL);
			gettimeofday(&end, NULL);
			
			eTime = (errorE.tv_sec + errorE.tv_usec / 1000000.0) - (errorS.tv_sec + errorS.tv_usec / 1000000.0);
			cTime = (end.tv_sec + end.tv_usec / 1000000.0) - (start.tv_sec + start.tv_usec / 1000000.0);
			cTime -= eTime;			// 반복문 연산되는 시간을 빼주어 오차를 최소화

			nTasu = ((insert - wrong) / cTime) * 60;		// 타수 계산

			if (inputScript[nRow][nCol] == 8 && nCol > 0)	// 백스페이스
			{
				inputScript[nRow][nCol] = NULL;
				inputScript[nRow][nCol-1] = NULL;
				nCol--;
				insert--;
			}
			else if (inputScript[nRow][nCol] == 8 && nCol == 0)	// 백스페이스면서 행에서 지울 글자가 없을 때
				inputScript[nRow][nCol] = NULL;
			else if (inputScript[nRow][nCol] == 27)				// ESC 입력
			{
				printf("\n=====================\n");
				printf("[ESC]를 누르셨습니다. 아무키나 누르시면 메뉴로 돌아갑니다.");
				getch();
				return;
			}
			else if (inputScript[nRow][nCol] == 10 || strlen(lScript[randL][nRow]) < strlen(inputScript[nRow]))	// 엔터를 입력했거나, 문자열을 초과했을 때(버퍼오버플로우 방지)
			{
				inputScript[nRow][nCol] = NULL;
				insert += blankSpace;
				nRow++;
				nCol = 0;
				break;
			}
			else if(nCol >= 0)
			{
				nCol++;
				insert++;
			}
		}
	}
	printf("\n=====================\n");
	printf("긴 글 연습이 끝났습니다. 아무키나 누르시면 메뉴로 돌아갑니다.");
	getch();
}