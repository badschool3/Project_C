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
	memcpy(newM->phoneNum,m1.phoneNum,sizeof(m1.address));
	newM -> next = NULL;

	if(L -> head == NULL && L -> tail == NULL)
		L -> head = L -> tail = newM;
	else
	{
		L -> tail -> next = newM;
		L -> tail -> newM;
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
		L -> tail -> newbT;
	}
}
