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

	~Node()
	{
		std::cout << "Node dtor done with next " << size_t(next) << " and prev " << size_t(prev) << std::endl;
	}
};

// шаблонный класс итератора двусвязного списка
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
		: data_(0)
	{
	}
	BasicIterator(node_base* data)
		: data_(data)
	{
	}
	// приведение к типу node для реализации вставки элемента
	// (допущение для упрощения)
	operator node*() { return (node*)data_; }
	BasicIterator& operator++()
	{
		data_ = data_->next;
		return *this;
	}
	BasicIterator operator++(int)
	{
		BasicIterator result(data_);
		data_ = data_->next;
		return result;
	}
	BasicIterator& operator--()
	{
		data_ = data_->prev;
		return *this;
	}
	BasicIterator operator--(int)
	{
		BasicIterator result(data_);
		data_ = data_->prev;
		return result;
	}
	BasicIterator operator-(int count)
	{
		BasicIterator result(data_);
		while (count--)
			--result;
		return result;
	}
	BasicIterator operator+(int count)
	{
		BasicIterator result(data_);
		while (count--)
			++result;
		return result;
	}
	bool operator==(const BasicIterator& other) const
	{
		return data_ == other.data_;
	}
	bool operator!=(const BasicIterator& other) const
	{
		return data_ != other.data_;
	}
	value_type& operator*() { return ((node*)data_)->value; }
	value_type* operator->() { return &((node*)data_)->value; }

private:
	node_base* data_;
};

template <class ValueType>
class list
{
public:
	typedef ValueType value_type;
	typedef ValueType& reference;
	typedef Node<value_type> node;
	typedef NBase node_base;
	typedef BasicIterator<value_type> iterator;
	list()
		: data_(new node_base())
	{
	}
	~list()
	{
		clear();
		delete data_;
	}
	int size() const
	{
		int result = 0;
		for (iterator i = begin(); i != end(); ++i)
			++result;
		return result;
	}
	bool empty()
	{
		return (data_->next == data_ && data_->prev == data_);
	}
	void clear()
	{
		while (!empty())
			delete data_->next;
	}
	reference back() { return *(end() - 1); }
	reference front() { return *begin(); }
	iterator begin() const { return data_->next; }
	iterator end() const { return data_; }
	iterator insert(iterator before, const value_type& value)
	{
		return new node((NBase*)before, ((NBase*)before)->prev, value);
	}
	iterator find_first(const value_type& what)
	{
		iterator result = begin();
		while (result != end() && *result != what)
			++result;
		return result;
	}
	iterator erase(iterator what)
	{
		iterator result = what + 1;
		delete (node*)what;
		return result;
	}
	// erases elements in range [begin, end)
	iterator erase(iterator begin, iterator end)
	{
		while (begin != end)
			begin = erase(begin);
		return begin;
	}
	iterator push_back(const value_type& value)
	{
		return insert(end(), value);
		//return new node(data_, data_->prev, value);
	}

private:
	node_base* data_; // элемент, находящийся "перед" списком и сразу
		// "за" списком
};
