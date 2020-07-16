#include "stdafx.h"
#include "CMyList.h"

int main()
{
    std::cout << "Double linked list test\n";
	NBase* testPrev = new (NBase);
	NBase* testNext = new (NBase);
	Node<int>(testNext, testPrev, 17);
	delete testPrev;
	delete testNext;
}


