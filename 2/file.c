#include "base.h"

void insertNode_Book(B);		// Book 노드 추가
void insertNode_Member(M);		// Member 노드 추가
void insertNode_Borrow(bT);		// Borrow 노드 추가
void load_file(void);			// 파일에서 정보 메모리에 불러오기
void save_file(void);			// 메모리 상에 정보 파일에 저장하기

FILE *client_fp, *book_fp, *borrow_fp;	

void insertNode_Book(B b1)
{
	B *newB = (B *)malloc(sizeof(B));
	memcpy(newB->bookNum, b1.bookNum, sizeof(b1.bookNum));
	memcpy(newB->bookName,b1.bookName, sizeof(b1.bookName));
	memcpy(newB -> bookPub, b1.bookPub, sizeof(b1.bookPub));
	memcpy(newB -> ISBN, b1.ISBN, sizeof(b1.ISBN));
	memcpy(newB -> bookWhere, b1.bookWhere, sizeof(b1.bookWhere));
	memcpy(newB -> canBorrow, b1.canBorrow, sizeof(b1.canBorrow));
	newB -> next = newB -> prev = NULL;

	if(Book_L -> head == NULL && Book_L -> tail == NULL)
		Book_L -> head = Book_L -> tail = newB;
	else
	{
		Book_L -> tail -> next = newB;
		newB -> prev = Book_L -> tail;
		Book_L -> tail = newB;
	}
}

void insertNode_Member(M m1)
{
	M *newM = (M *)malloc(sizeof(M));
	memcpy(newM->stdNum, m1.stdNum, sizeof(m1.stdNum));
	memcpy(newM->passwd,m1.passwd,sizeof(m1.passwd));
	memcpy(newM->name,m1.name,sizeof(m1.name));
	memcpy(newM->address,m1.address,sizeof(m1.address));
	memcpy(newM->phoneNum,m1.phoneNum,sizeof(m1.phoneNum));
	newM -> next = newM -> prev = NULL;

	if(Member_L -> head == NULL && Member_L -> tail == NULL)
		Member_L -> head = Member_L -> tail = newM;
	else
	{
		Member_L -> tail -> next = newM;
		newM -> prev = Member_L -> tail;
		Member_L -> tail = newM;
	}
}

void insertNode_Borrow(bT bT1)
{
	bT *newbT = (bT *)malloc(sizeof(bT));
	memcpy(newbT->stdNum, bT1.stdNum, sizeof(bT1.stdNum));
	memcpy(newbT->bookNum, bT1.bookNum, sizeof(bT1.bookNum));
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

	Book_L = (B_LinkedList *) malloc(sizeof(B_LinkedList));
	Member_L = (M_LinkedList *) malloc(sizeof(M_LinkedList));
	Borrow_L = (bT_LinkedList *) malloc(sizeof(bT_LinkedList));

	Book_L -> head = Book_L -> cur = Book_L -> tail = NULL;
	Member_L -> head = Member_L -> cur = Member_L -> tail = NULL;
	Borrow_L -> head = Borrow_L -> cur = Borrow_L -> tail = NULL;

	while(!feof(client_fp))
	{
		fgets(buf, sizeof(buf), client_fp);
		sscanf(buf,"%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|]",\
				mm.stdNum, mm.passwd, mm.name, mm.address, mm.phoneNum);
		insertNode_Member(mm);
	}
	while(!feof(book_fp))
	{
		fgets(buf, sizeof(buf), book_fp);
		sscanf(buf,"%[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|] | %[^\n|]",\
				bb.bookNum, bb.bookName, bb.bookPub, bb.ISBN, bb.bookWhere, bb.canBorrow);
		insertNode_Book(bb);
	}
	while(!feof(borrow_fp))
	{
		fgets(buf, sizeof(buf), book_fp);
		sscanf(borrow_fp, "%[^\n|] | %[^\n|] | %d | %d\n",\
				bt.stdNum, bt.bookNum, &bt.borrowT, &bt.returnT);
		insertNode_Borrow(bt);
	}
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
	bT *btp = Borrow_L -> head
	
	while(mp != NULL)
	{
		fprintf(client_fp, "%s| %s| %s| %s| %s\n",\
				mp -> stdNum, mp -> passwd, mp -> name, mp-> address, mp -> phoneNum);
		mp = mp -> next;
	}
	while(bp != NULL)
	{
		fprintf(book_fp, "%s| %s| %s| %s| %s| %s\n",\
				bp -> bookNum, bp -> bookName, bp -> bookPub, bp -> ISBN, bp -> bookWhere, bp -> canBorrow);
		bp = bp -> next;
	}
	while(btp != NULL)
	{
		fprintf(borrow_fp, "%s| %s| %d| %d\n",\
				btp -> stdNum, btp -> bookNum, btp -> borrowT, btp -> returnT);
		btp = btp -> next;
	}
	fclose(client_fp);
	fclose(book_fp);
	fclose(borrow_fp);
}
