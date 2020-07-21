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

TEST_CASE("Can create int list of four elems, iterate on it and read data")
{
	CMyList<int> ilist;
	CHECK(ilist.size() == 0);
	CHECK(ilist.begin() == ilist.end()); // для одинокого BNode next и prev -- это он сам
	CHECK(ilist.empty());

	ilist.push_back(1);
	ilist.push_back(3);
	ilist.push_back(5);
	ilist.push_back(7);

	CHECK(ilist.size() == 4);
	CHECK(*ilist.cbegin() == 1);
	CHECK(*(ilist.cend() - 1) == 7);

	CMyList<int>::const_iterator cit = ilist.cbegin();
	int i = 1;

	for (; cit != ilist.cend(); ++cit, i += 2)
	{
		CHECK(*cit == i);
	}

	cit = cit - ilist.size();
	CHECK(cit == ilist.cbegin());
}


TEST_CASE("Can insert front and back")
{
	CMyList<int> iList;
	CMyList<std::string> stringList;

	iList.push_front(100);
	iList.push_back(150);
	iList.push_front(50);

	CMyList<int>::const_iterator cit = iList.cbegin();
	CHECK(*cit++ == 50);
	CHECK(*cit++ == 100);
	CHECK(*cit++ == 150);
	CHECK(cit == iList.cend());
	iList.push_back(200);
	CHECK(cit == iList.cend());
	CHECK(*--cit == 200);

	stringList.push_front("Two 2");
	stringList.push_front("One 1");
	stringList.push_back("Three 3");

	CMyList<std::string>::const_iterator scit = stringList.cend();
	CHECK(*--scit == "Three 3");
	CHECK(*--scit == "Two 2");
	CHECK(*--scit == "One 1");
	CHECK(scit == stringList.cbegin());
	stringList.push_front("Zero 0");
	CHECK(--scit == stringList.cbegin());
	CHECK(*scit == "Zero 0");
}

TEST_CASE("Can change values via iterator")
{
	CMyList<int> iList;
	iList.push_back(10);
	iList.push_back(100);
	iList.push_back(1000);

	CHECK(*(iList.begin() + 1) == 100);

	CMyList<int>::iterator it;
	it = iList.end();
	it = it - 2;
	*it = 111;
	auto it2 = iList.begin();
	CHECK(*it2++ == 10);
	CHECK(*it2++ == 111);
	CHECK(*it2++ == 1000);
	CHECK(it2 == iList.end());

	CMyList<std::string> sList;
	sList.push_front("short");
	sList.push_back("medium");
	sList.push_back("large");

	CMyList<std::string>::iterator sit = sList.begin();
	*sit = "just quite " + *sit;
	sit++;
	*sit = "still sized " + *sit;
	sit++;
	*sit = "Became sufficiently more " + *sit;
	auto sit2 = sList.cend();
	CHECK(*--sit2 == "Became sufficiently more large");
	CHECK(*--sit2 == "still sized medium");
	CHECK(*--sit2 == "just quite short");
	CHECK(sit2 == sList.cbegin());
}

TEST_CASE("Can get access with reverse iterator")
{
	CMyList<int> iList;
	iList.push_back(0);
	iList.push_back(1);
	iList.push_back(2);
	iList.push_back(3);
	iList.push_back(4);

	CMyList<int>::const_reverse_iterator crit = iList.crbegin();
	CHECK(*crit == 4);
	CHECK(*++crit == 3);
	CHECK(*crit == 3);
	crit = iList.crend();
	CHECK(*--crit == 0);
	CHECK(*--crit == 1);
	CHECK(*crit-- == 1);
	CHECK(*crit == 2);
	CHECK(*crit++ == 2);
	CHECK(*crit == 1);
	crit = iList.crbegin();
	crit = crit + 3;
	CHECK(*crit == 1);
	crit = crit - 2;
	CHECK(*crit == 3);
}

TEST_CASE("Can get list elems amount")
{
	CMyList<std::string> sList;
	CHECK(sList.size() == 0);
	sList.push_back("First inserted");
	CHECK(sList.size() == 1);
	sList.push_front("Second inserted");
	CHECK(sList.size() == 2);
	sList.push_front("Third inserted");
	sList.push_front("Fourth inserted");
	sList.push_back("Fifth inserted");
	CHECK(sList.size() == 5);
}

TEST_CASE("Can insert element into list in certain position shown by iterator")
{
	CMyList<int> iList;
	iList.push_back(3);
	iList.push_back(14);

	CMyList<int>::const_iterator insPos = iList.cbegin() + 1;
	iList.insert(insPos, 7);
	CHECK(*(iList.cbegin() + 1) == 7);
	
	iList.insert(iList.cend(), 24);
	CHECK(*iList.crbegin() == 24);

	iList.insert(iList.cbegin(), 1);
	CHECK(*iList.cbegin() == 1);
	insPos = iList.cbegin();
	CHECK(*insPos++ == 1);
	CHECK(*insPos++ == 3);
	CHECK(*insPos++ == 7);
	CHECK(*insPos++ == 14);
	CHECK(*insPos++ == 24);
	CHECK(insPos == iList.cend());

	CMyList<std::string> sList;
	sList.insert(sList.cend(), "Before string A");
	sList.insert(sList.cend(), "Past string A");
	sList.insert(sList.cbegin() + 1, "String A itself");

	auto cit = sList.cbegin();

	CHECK(*cit++ == "Before string A");
	CHECK(*cit++ == "String A itself");
	CHECK(*cit++ == "Past string A");

	sList.insert(cit - 2, "Between Before and A itself");
	CHECK(*(sList.cbegin() + 1) == "Between Before and A itself");

}

TEST_CASE("Can erase element on position shown by iterator")
{
	CMyList<int> iList;
	for (int i = 1; i < 10; ++i)
	{
		iList.push_back(i);
	}
	CMyList<int>::const_iterator cit = iList.cbegin() + 7;
	CMyList<int>::iterator retPos = iList.erase(cit); // удаляем элемент 8 на восьмом месте от начала
	CHECK(*retPos == 9);
	CHECK(*(iList.cbegin() + 6) == 7);
	CHECK(*(iList.cbegin() + 7) == 9);

	CHECK(*(iList.erase(iList.cbegin() + 2)) == 4);
	CHECK(*(iList.erase(iList.cbegin())) == 2);
	std::vector<int> resultSet = { 2, 4, 5, 6, 7, 9 };
	size_t i = 0;
	for (auto cit = iList.cbegin(); cit != iList.cend(); ++cit)
	{
		CHECK(*cit == resultSet[i++]);
	}
	CHECK(iList.size() == 6);
	iList.erase(iList.cend() - 1);
	CHECK(iList.size() == 5);
	CHECK(*iList.crbegin() == 7);
}

TEST_CASE("Can erase range in list")
{
	CMyList<std::string> sList;
	for (size_t i = 0; i < 10; ++i)
	{
		sList.push_back("This is string number " + std::to_string(i));
	}
	CHECK(sList.size() == 10);

	CMyList<std::string>::const_iterator cit = sList.cbegin() + 3;
	CMyList<std::string>::iterator res = sList.erase(cit, cit + 4);
	CHECK(*res == "This is string number 7");
	CHECK(sList.size() == 6);
	CHECK(*(sList.cbegin() + 2) == "This is string number 2");
	CHECK(*(sList.cbegin() + 3) == "This is string number 7");

	sList.erase(sList.cbegin(), sList.cbegin() + 2);
	CHECK(*sList.cbegin() == "This is string number 2");
	CHECK(*(sList.cbegin() + 1) == "This is string number 7");

	sList.erase(sList.cbegin() + 2, sList.cend());
	CHECK(*sList.cbegin() == "This is string number 2");
	CHECK(*(sList.cend() - 1) == "This is string number 7");
}

TEST_CASE("Can copy list to other location")
{
	CMyList<int> iList;
	iList.push_back(1);
	iList.push_back(2);
	iList.push_back(3);
	iList.push_back(5);
	iList.push_back(8);
	iList.push_back(13);

	CMyList<int> iListCopy = iList;

	
	CHECK(iListCopy.size() == 6);
	auto copyCit = iListCopy.cbegin();
	for (auto cit = iListCopy.cbegin(); cit != iListCopy.cend(); ++cit, ++copyCit)
	{
		CHECK(*cit == *copyCit);
	}
		
}

TEST_CASE("Can assign list to other")
{
	CMyList<std::string> sList;
	sList = sList;
	CHECK(sList.empty());

	sList.push_back("String zero");
	sList.push_back("String one");
	sList.push_back("String two");
	sList.push_back("String three");
	sList.push_back("String four");

	CMyList<std::string> otherSList;
	
	otherSList = sList;

	auto cit = sList.cbegin();
	auto otherCit = otherSList.cbegin();
	for (; cit != sList.cend(); ++cit, ++otherCit)
	{
		CHECK(*cit == *otherCit);
	}
	CHECK(otherCit == otherSList.cend());
	
	otherSList = otherSList;

	cit = sList.cbegin();
	otherCit = otherSList.cbegin();
	for (; cit != sList.cend(); ++cit, ++otherCit)
	{
		CHECK(*cit == *otherCit);
	}
	CHECK(otherCit == otherSList.cend());

	sList.clear();
	otherSList = sList;

	CHECK(otherSList.empty());
}



