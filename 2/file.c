#include "base.h"

FILE *client_fp, *book_fp, *borrow_fp;	

void insertNode_Book(B_LinkedList *L, B b1)
{
	B *newB = (B *)malloc(sizeof(B));
	newB -> bookNum = b1.bookNum;
	memcpy(newB->bookName,b1.bookName,sizeof(b1.bookName));
	memcpy(newB -> bookPub, b1.bookPub, sizeof(b1.bookPub));
	newB -> ISBN = b1.ISBN;
	memcpy(newB -> bookWhere, b1.bookWhere, sizeof(b1.bookWhere));
	memcpy(newB -> canBorrow, b1.canBorrow, sizeof(b1.canBorrow));
	newB -> next = NULL;

	if(L -> head == NULL && L -> tail == NULL)
		L -> head = L -> tail = newB;
	else
	{
		L -> tail -> next = newB;
		L -> tail = newB;
	}
}

void insertNode_Member(M_LinkedList *L, M m1)
{
	M *newM = (M *)malloc(sizeof(M));
	newM -> stdNum = m1.stdNum;
	memcpy(newM->passwd,m1.passwd,sizeof(m1.passwd));
	memcpy(newM->name,m1.name,sizeof(m1.name));
	memcpy(newM->address,m1.address,sizeof(m1.address));
	memcpy(newM->phoneNum,m1.phoneNum,sizeof(m1.phoneNum));
	newM -> next = NULL;

	if(L -> head == NULL && L -> tail == NULL)
		L -> head = L -> tail = newM;
	else
	{
		L -> tail -> next = newM;
		L -> tail = newM;
	}
}

void insertNode_Borrow(bT_LinkedList *L, bT bT1)
{
	bT *newbT = (bT *)malloc(sizeof(bT));
	newbT -> stdNum = bT1.stdNum;
	newbT -> bookNum = bT1.bookNum;
	newbT -> borrowT = bT1.borrowT;
	newbT -> returnT = bT1.returnT;

	if(L -> head == NULL && L -> tail == NULL)
		L -> head = L -> tail = newbT;
	else
	{
		L -> tail -> next = newbT;
		L -> tail = newbT;
	}
}

void load_file(B_LinkedList *Book_L, M_LinkedList *Member_L, bT_LinkedList *Borrow_L)
{
	client_fp = fopen("client","r");
	book_fp = fopen("book","r");
	borrow_fp = fopen("borrow","r");
	
	B bb;
	bT bt;
	M mm;
	
	Book_L = (B_LinkedList *) malloc(sizeof(B_LinkedList));
	Member_L = (M_LinkedList *) malloc(sizeof(M_LinkedList));
	Borrow_L = (bT_LinkedList *) malloc(sizeof(bT_LinkedList));

	Book_L -> head = Book_L -> cur = Book_L -> tail = NULL;
	Member_L -> head = Member_L -> cur = Member_L -> tail = NULL;
	Borrow_L -> head = Borrow_L -> cur = Borrow_L -> tail = NULL;

	while(!feof(client_fp))
	{
		fscanf(client_fp,"%d | %s | %s | %s | %s\n",\
				&mm.stdNum, mm.passwd, mm.name, mm.address, mm.phoneNum);
		insertNode_Client(Member_L, mm);
	}
	while(!feof(book_fp))
	{
		fscanf(book_fp,"%d | %s | %s | %s | %lld | %s | %s",\
				&bb.bookNum, bb.bookName, bb.bookPub, &bb.ISBN, bb.bookWhere, bb.canBorrow);
		insertNode_Book(Book_L, bb);
	}
	while(!feof(borrow_fp))
	{
		fscanf(borrow_fp, "%d | %d | %d | %d\n",\
				&bt.stdNum, &bt.bookNum, &bt.borrowT, &bt.returnT);
		insertNode_Borrow(Borrow_L, bt);
	}
	fclose(client_fp);
	fclose(book_fp);
	fclose(borrow_fp);
}

void printNodes(B_LinkedList *newB, M_LinkedList *newM, bT_LinkedList *newbT)
{
	client_fp = fopen("client", "w");
	book_fp = fopen("book", "w");
	borrow_fp = fopen("borrow", "w");

	B *bp = newB -> head;
	M *mp = newM -> head;
	bT *btp = newbT -> head
	
	while(p != NULL)
	{
		printf("%d | %s | %s | %s | %s\n", p -> stdNum, p -> passwd, p -> name, p-> address, p -> phoneNum);
		p = p -> next;
	}
}
