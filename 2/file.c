#include "base.h"

void insertNode_Book(B);		// Book 노드 추가
void insertNode_Member(M);		// Member 노드 추가
void insertNode_Borrow(bT);		// Borrow 노드 추가
void load_file(void);			// 파일에서 정보 메모리에 불러오기
void save_file(void);			// 메모리 상에 정보를 파일에 저장하기

void sort_Member(void);			// Member 정렬 함수
void sort_Book(void);			// Book 정렬 함수
void swap_Book(B*, B*);
void swap_Member(M*, M*);
FILE *client_fp, *book_fp, *borrow_fp;	

void swap_Book(B* b1, B* b2)
{
	if(Book_L -> head == b1)
	{
		b2 -> prev = NULL;
		Book_L -> head = b2;
	}
	else
	{
		b1 -> prev -> next = b2;
		b2 -> prev = b1 -> prev;

	}
		
	if(Book_L->tail==b2)
	{
		b1 -> next = NULL;
		Book_L -> tail = b1;
	}
	else
	{
		b2 -> next -> prev = b1;
		b1 -> next = b2 -> next;
	}
	b1 -> prev = b2;
	b2 -> next = b1;
}

void swap_Member(M* m1, M* m2)
{
	if(Member_L -> head == m1)
	{
		m2 -> prev = NULL;
		Member_L -> head = m2;
	}
	else
	{
		m1 -> prev -> next = m2;
		m2 -> prev = m1 -> prev;
	}
		
	if(Member_L->tail==m2)
	{
		m1 -> next = NULL;
		Member_L -> tail = m1;
	}
	else
	{
		m2 -> next -> prev = m1;
		m1 -> next = m2 -> next;
	}
	m1 -> prev = m2;
	m2 -> next = m1;
}
void sort_Book()
{
	B *bp; 	
	for(int i = 0; i < Book_L -> cnt; i++)
	{
		bp = Book_L -> head;
		for(int j = 0; j < Book_L -> cnt - 1 - i; j++)
		{
			if(bp -> ISBN > bp -> next -> ISBN)
				swap_Book(bp, bp->next);
			else
				bp = bp -> next;
		}
	}
}

void sort_Member()
{
	M *mp;
	for(int i = 0; i < Member_L -> cnt; i++)
	{
		mp = Member_L -> head;
		for(int j = 0; j < Member_L -> cnt - 1 - i; j++)
		{
			if(mp -> stdNum > mp -> next -> stdNum)
				swap_Member(mp, mp->next);
			else
				mp = mp -> next;
		}
	}
}

void insertNode_Book(B b1)
{
	B *newB = (B *)malloc(sizeof(B));
	newB->bookNum = b1.bookNum;
	memcpy(newB->bookName,b1.bookName, sizeof(b1.bookName));
	memcpy(newB->bookWriter, b1.bookWriter, sizeof(b1.bookWriter));
	memcpy(newB -> bookPub, b1.bookPub, sizeof(b1.bookPub));
	newB->ISBN = b1.ISBN;
	memcpy(newB -> bookWhere, b1.bookWhere, sizeof(b1.bookWhere));
	memcpy(newB -> canBorrow, b1.canBorrow, sizeof(b1.canBorrow));
	newB -> next = newB -> prev = NULL;
	Book_L -> cnt += 1;
	if(Book_L -> head == NULL && Book_L -> tail == NULL)
	{
		Book_L -> head = Book_L -> tail = newB;
	}
	else
	{
		Book_L -> tail -> next = newB;
		newB -> prev = Book_L -> tail;
		Book_L -> tail = newB;
		Book_L -> tail -> next = NULL;
	}
}

void insertNode_Member(M m1)
{
	M *newM = (M *)malloc(sizeof(M));
	newM->stdNum = m1.stdNum;
	memcpy(newM->passwd,m1.passwd,sizeof(m1.passwd));
	memcpy(newM->name,m1.name,sizeof(m1.name));
	memcpy(newM->address,m1.address,sizeof(m1.address));
	memcpy(newM->phoneNum,m1.phoneNum,sizeof(m1.phoneNum));
	newM -> next = newM -> prev = NULL;
	Member_L -> cnt += 1;
	if(Member_L -> head == NULL && Member_L -> tail == NULL)
		Member_L -> head = Member_L -> tail = newM;
	else
	{
		Member_L -> tail -> next = newM;
		newM -> prev = Member_L -> tail;
		Member_L -> tail = newM;
		Member_L -> tail -> next = NULL;
	}
}

void insertNode_Borrow(bT bT1)
{
	bT *newbT = (bT *)malloc(sizeof(bT));
	newbT -> stdNum = bT1.stdNum;
	newbT -> bookNum = bT1.bookNum;
	newbT -> borrowT = bT1.borrowT;
	newbT -> returnT = bT1.returnT;
	newbT -> next = newbT -> prev = NULL;

	if(Borrow_L -> head == NULL && Borrow_L -> tail == NULL)
		Borrow_L -> head = Borrow_L -> tail = newbT;
	else
	{
		Borrow_L -> tail -> next = newbT;
		newbT -> prev = Borrow_L -> tail;
		Borrow_L -> tail = newbT;
	}
}

void load_file()
{
	client_fp = fopen("client","r");
	book_fp = fopen("book","r");
	borrow_fp = fopen("borrow","r");
	
	B bb;
	bT bt;
	M mm;
	
	char buf[300];
	char tmp[15];
	Book_L = (B_LinkedList *) malloc(sizeof(B_LinkedList));
	Member_L = (M_LinkedList *) malloc(sizeof(M_LinkedList));
	Borrow_L = (bT_LinkedList *) malloc(sizeof(bT_LinkedList));

	Book_L -> head = Book_L -> cur = Book_L -> tail = NULL;
	Book_L -> cnt = Member_L -> cnt = 0;
	Member_L -> head = Member_L -> cur = Member_L -> tail = NULL;
	Borrow_L -> head = Borrow_L -> cur = Borrow_L -> tail = NULL;

	while(!feof(client_fp))
	{
		fgets(buf, sizeof(buf), client_fp);
		sscanf(buf,"%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|]",\
				tmp, mm.passwd, mm.name, mm.address, mm.phoneNum);
		mm.stdNum = atoi(tmp);
		insertNode_Member(mm);
	}
	while(!feof(book_fp))
	{
		fgets(buf, sizeof(buf), book_fp);
		sscanf(buf,"%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %lld | %[^\n|] | %[^\n|]",\
				tmp, bb.bookName, bb.bookWriter, bb.bookPub, &bb.ISBN, bb.bookWhere, bb.canBorrow);
		bb.bookNum = atoi(tmp);
		insertNode_Book(bb);
	}
	/*
	while(!feof(borrow_fp))
	{
		fgets(buf, sizeof(buf), book_fp);
		sscanf(buf, "%[^\n|] | %[^\n|] | %d | %d\n",\
				bt.stdNum, bt.bookNum, &bt.borrowT, &bt.returnT);
		insertNode_Borrow(bt);
	}
	*/
	fclose(client_fp);
	fclose(book_fp);
	fclose(borrow_fp);
}

void save_file()
{
	client_fp = fopen("client", "w");
	book_fp = fopen("book", "w");
	borrow_fp = fopen("borrow", "w");

	B *bp = Book_L -> head;
	M *mp = Member_L -> head;
	bT *btp = Borrow_L -> head;
	
	while(mp != NULL)
	{
		fprintf(client_fp, "%d | %s| %s| %s| %s\n",\
				mp -> stdNum, mp -> passwd, mp -> name, mp-> address, mp -> phoneNum);
		mp = mp -> next;
	}
	while(bp != NULL)
	{
		fprintf(book_fp, "%08d | %s| %s| %s| %lld | %s| %s\n",\
				bp -> bookNum, bp -> bookName, bp -> bookWriter, bp -> bookPub, bp -> ISBN, bp -> bookWhere, bp -> canBorrow);
		bp = bp -> next;
	}
	while(btp != NULL)
	{
		fprintf(borrow_fp, "%s| %s| %d | %d\n",\
				btp -> stdNum, btp -> bookNum, btp -> borrowT, btp -> returnT);
		btp = btp -> next;
	}
	fclose(client_fp);
	fclose(book_fp);
	fclose(borrow_fp);
}
