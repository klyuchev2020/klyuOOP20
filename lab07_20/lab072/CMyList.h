#pragma once

struct NBase // реализует связность списка и не несет данных
{
	NBase* next;
	NBase* prev;

	NBase()
		: next(this)
		, prev(this)
	{
	}

	NBase(NBase* nextNode, NBase* prevNode)
		: next(nextNode)
		, prev(prevNode)
	{
		prevNode->next = this;
		nextNode->prev = this;
	}

	virtual ~NBase()
	{
		prev->next = next;
		next->prev = prev;
	}
	
};

template <class T>
struct Node : public NBase
{
	T value;

	Node()
		: NBase()
	{
	}

	Node(NBase* nextNode, NBase* prevNode, const T& nodeValue)
		: NBase(nextNode, prevNode)
		, value(nodeValue)
	{
	}

};

template <class ValueType,
	class Pointer = ValueType*, class Reference = ValueType&>
class BasicIterator
{
public:
	using value_type = ValueType;
	using pointer = Pointer;
	using reference = Reference;
	using node_base = NBase;
	using node = Node<value_type>;

	BasicIterator()
		: m_nodePtr(nullptr)
	{
	}

	BasicIterator(node_base* nodePtr)
		: m_nodePtr(nodePtr)
	{
	}

	operator node*() // оператор преобразования, вспомогательный
	{
		return static_cast<node*>(m_nodePtr);
	}

	BasicIterator& operator++()
	{
		m_nodePtr = m_nodePtr->next;
		return *this;
	}

	BasicIterator operator++(int)
	{
		BasicIterator result(m_nodePtr);
		m_nodePtr = m_nodePtr->next;
		return result;
	}

	BasicIterator& operator--()
	{
		m_nodePtr = m_nodePtr->prev;
		return *this;
	}

	BasicIterator operator--(int)
	{
		BasicIterator result(m_nodePtr);
		m_nodePtr = m_nodePtr->prev;
		return result;
	}

	BasicIterator operator-(int count)
	{
		BasicIterator result(m_nodePtr);
		while (count--)
		{
			--result;
		}
		return result;
	}

	BasicIterator operator+(int count)
	{
		BasicIterator result(m_nodePtr);
		while (count--)
		{
			++result;
		}
		return result;
	}

	bool operator==(const BasicIterator& other) const
	{
		return m_nodePtr == other.m_nodePtr;
	}

	bool operator!=(const BasicIterator& other) const
	{
		return !(*this == other);
	}

	value_type& operator*()
	{
		return (static_cast<node*>(m_nodePtr))->value;
	}

	value_type* operator->()
	{
		return &(static_cast<node*>(m_nodePtr))->value;
	}

protected:
	node_base* m_nodePtr;
};

template <class ValueType,
	class Pointer = ValueType*, class Reference = ValueType&>
class ReverseIterator : public BasicIterator<ValueType, Pointer, Reference>
{
public:
	using BI = BasicIterator<ValueType, Pointer, Reference>;

	ReverseIterator()
		: BI()
	{
	}

	ReverseIterator(BI::node_base* nodePtr)
		: BI(nodePtr)
	{
	}

	ReverseIterator& operator++()
	{
		BI::m_nodePtr = BI::m_nodePtr->prev;
		return *this;
	}

	ReverseIterator operator++(int)
	{
		ReverseIterator result(BI::m_nodePtr);
		BI::m_nodePtr = BI::m_nodePtr->prev;
		return result;
	}

	ReverseIterator& operator--()
	{
		BI::m_nodePtr = BI::m_nodePtr->next;
		return *this;
	}

	ReverseIterator operator--(int)
	{
		ReverseIterator result(BI::m_nodePtr);
		BI::m_nodePtr = BI::m_nodePtr->next;
		return result;
	}

	ReverseIterator operator-(int count)
	{
		ReverseIterator result(BI::m_nodePtr);
		while (count--)
		{
			--result;
		}
		return result;
	}

	ReverseIterator operator+(int count)
	{
		ReverseIterator result(BI::m_nodePtr);
		while (count--)
		{
			++result;
		}
		return result;
	}
};

template <class ValueType>
class CMyList
{
public:
	using value_type = ValueType;
	using reference = ValueType&;
	using const_reference = const ValueType&;
	using node = Node<value_type>;
	using node_base = NBase;
	using pointer = ValueType*;
	using const_pointer = const ValueType*;
	using iterator = BasicIterator<value_type>;
	using const_iterator = BasicIterator<value_type, const_pointer, const_reference>;
	using reverse_iterator = ReverseIterator<value_type>;
	using const_reverse_iterator = ReverseIterator<value_type, const_pointer, const_reference>;

	CMyList()
		: m_elemPtr(new node_base())
	{
	}

	CMyList(const CMyList& other)
		: m_elemPtr(new node_base())
	{
		iterator start = other.begin();
		iterator finish = other.end();
		node_base* currNode = m_elemPtr;

		try
		{
			for (; start != finish; ++start)
			{
				currNode = static_cast<node_base*>(new node(m_elemPtr, currNode, *start));
			}
		}
		catch (...)
		{
			if (currNode != m_elemPtr)
			{
				destroy_nodes(m_elemPtr->next, currNode);
			}			
			throw;
		}
	}

	CMyList& operator=(CMyList const& other)
	{
		if (this == &other)
		{
			return *this;
		}
		
		node_base* copy_elemPtr = new node_base();
		iterator start = other.begin();
		iterator finish = other.end();
		node_base* currNode = copy_elemPtr;

		try
		{
			for (; start != finish; ++start)
			{
				currNode = static_cast<node_base*>(new node(copy_elemPtr, currNode, *start));
			}
			clear();
			m_elemPtr = copy_elemPtr;
			return *this;
		}
		catch (...)
		{
			if (currNode != m_elemPtr)
			{
				destroy_nodes(m_elemPtr->next, currNode);
			}
			delete copy_elemPtr;
			return *this;
		}
		
	}

	


	~CMyList()
	{
		clear();
		delete m_elemPtr;
	}

	int size() const
	{
		int result = 0;
		for (const_iterator i = cbegin(); i != cend(); ++i)
		{
			++result;
		}
		return result;
	}

	bool empty()
	{
		return (m_elemPtr->next == m_elemPtr && m_elemPtr->prev == m_elemPtr);
	}

	void clear()
	{
		while (!empty())
		{
			delete m_elemPtr->next;
		}
	}

	reference back()
	{
		return *(end() - 1);
	}

	reference front()
	{
		return *begin();
	}

	iterator begin() const
	{
		return m_elemPtr->next;
	}

	const_iterator cbegin() const
	{
		return m_elemPtr->next;
	}

	iterator end() const
	{
		return m_elemPtr;
	}

	const_iterator cend() const
	{
		return m_elemPtr;
	}

	reverse_iterator rbegin() const
	{
		return m_elemPtr->prev;
	}

	const_reverse_iterator crbegin() const
	{
		return m_elemPtr->prev;
	}

	reverse_iterator rend() const
	{
		return m_elemPtr;
	}

	const_reverse_iterator crend() const
	{
		return m_elemPtr;
	}

	iterator insert(const_iterator before, const value_type& value)
	{
		return new node(static_cast<node_base*>(before), (static_cast<node_base*>(before))->prev, value);
	}

	iterator erase(const_iterator what)
	{
		const_iterator result = what + 1;
		delete static_cast<node*>(what);
		return static_cast<iterator>(result);
	}

	iterator erase(const_iterator begin, const_iterator end)
	{
		while (begin != end)
		{
			begin = static_cast<const_iterator>(erase(begin));
		}
		return static_cast<iterator>(begin);
	}

	iterator push_front(const value_type& value)
	{
		return insert(cbegin(), value);
	}

	iterator push_back(const value_type& value)
	{
		return insert(cend(), value);
	}

private:
	node_base* m_elemPtr; // особый элемент, предшествующий первому элементу списка и следующий за последним элементом списка

	void destroy_node_at(node* nodePtr)
	{
		nodePtr->~Node();
	}

	void destroy_nodes(node_base* first, node_base* last)
	{
		for (; first != last; first = first->next)
		{
			destroy_node_at(static_cast<node*>(first));
		}
	}

};



