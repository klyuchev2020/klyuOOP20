#include "stdafx.h"
#include "../lab072/CMyList.h"

TEST_CASE("Can create a node containes an int")
{
	NBase* testPrev = new (NBase);
	NBase* testNext = new (NBase);
	{
		Node<int> node(testNext, testPrev, 17);
		CHECK(node.next == testNext);
		CHECK(node.prev == testPrev);
		CHECK(node.value == 17);
	}
	delete testPrev;
	delete testNext;
}

TEST_CASE("Can create nodes chain and erase it back")
{
	NBase* first = new (NBase);
	CHECK(first->next == first);
	CHECK(first->prev == first);
	NBase* third = new (NBase);
	NBase secondNode(third, first);
	CHECK(secondNode.next == third);
	CHECK(secondNode.prev == first);
	CHECK(first->next == &secondNode);
	CHECK(third->prev == &secondNode);

	NBase* fourth = new (NBase);
	fourth->prev = third;
	third->next = fourth;
	CHECK(first->next->next->next == fourth);

	delete first;
	delete third;
	delete fourth;
}
