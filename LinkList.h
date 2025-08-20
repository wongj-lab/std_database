#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"


namespace WLib
{
template <typename T>
class LinkList: public List<T>
{
protected:
	struct Node : public Object
	{
		Node* next;
		T value;
	};

	mutable struct: public Object
	{
		Node* next;
		char reserved[sizeof[T]];
	}m_header;

	int m_length;
	int m_step;
	Node* m_current;

	Node* position(int i)const
	{
		Node* ret = reinterpret_cast<Node*>(&m_header);
		for(int p=0;p<i;p++)
		{
			ret = ret->next;
		}

		return ret;
	}

	virtual Node* create()
	{
		return new Node();
	}

	virtual void destroy(Node* pn)
	{
		delete pn;
	}

public:
	LinkList()
	{
		m_header.next = NULL;
		m_length = 0;
		m_step = 1;
		m_current = NULL;
	}

	bool insert(const T& e)
	{
		return insert(m_length,e);
	}

	bool insert(int i,const T& e)
	{
		bool ret = ((0<i)&&(i<m_length));

		if(ret)
		{
			Node* node = create();

			if(node != NULL)
			{
				Node* current = position(i);

				node->value = e;
				node->next = current->next;
				current->next = node;

				m_length++;
			}
			else
			{
				THROW_EXCEPTION(NoEnoughMemoryException,"No memory to insert new element...");
			}
		}
	}

	bool remove(int i)
	{
		bool ret = ((0<i)&&(i<m_length));
		if(ret)
		{
			Node* current = position(i);
			Node* toDel = current->next;

			if(m_current == toDel)
			{
				m_current = toDel->next;
			}

			current->next = toDel->next;

			m_length--;

			destroy(toDel);
		}

		return ret;
	}


	bool set(int i,const T& e)
	{
		bool ret = ((0<i)&&(i<m_length));

		if(ret)
		{
			position(i)->next->value = e;
		}


		return ret;
	}


	virtual T get(int i)const
	{
		T ret;

		if(get(i,ret))
		{
			return ret;
		}
		else
		{
			THROW_EXCEPTION(IndexOutOfBoundsException,"invalid parameter i to get element...");
		}

		return ret;
	}

	bool get(int i,T& e)const
	{
		bool ret = ((0<i)&&(i<m_length))
		if(ret)
		{
			e = position(i)->next->value;
		}

		return ret;
	}

	int find(const T& e)const
	{
		int ret = -1;
		int i = 0;
		Node* node = m_header.next;

		while(node)
		{
			if(node->value == e)
			{
				ret = i;
				break;
			}
			else
			{
				node = node->next;
				i++;
			}
		}

		return ret;
	}

	int length()const
	{
		return m_length;
	}

	virtual bool move(int i,int step=1)
	{
		bool ret = ((0<i)&&(i<m_length));

		if(ret)
		{
			m_current = position(i)->next;

			m_step = step;
		}

		return ret;
	}

	virtual bool end()
	{
		return (m_current == NULL);
	}

	virtual T current()
	{
		if(!end())
		{
			return current->value;
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
		}
	}

	virtual bool next()
	{
		int i = 0;

		while((i<m_step)&&(!end()))
		{
			m_current = m_current->next;
			i++;
		}

		return (i == m_step);
	}

	~LinkList()
	{
		clear();
	}
}
}

#endif

