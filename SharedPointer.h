#ifndef SHAREDSMART_H
#define SHAREDSMART_H

#include "Exception.h"
#include "Pointer.h"
#include <cstdlib>

namespace WLib
{
template <typename T>
class SharedPointer : public Pointer<T>
{
	protected:
		int* m_ref;

		void assign(const SharedPointer<T>& obj)
		{
			this->m_ref = obj.m_ref;
			this->m_pointer = obj.m_pointer;

			if(this->m_ref)
			{
				(*this->m_ref)++;
			}
		}
	public:
		SharedPointer(T* p=NULL):m_ref(NULL)
		{
			if(p)
			{
				this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));

				if(this->m_ref)
				{
					(*this->m_ref) = 1;
					this->m_pointer = p;
				}
				else
				{
					THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create sharedpointer object ...");
				}
			}
		}

		SharedPointer(const SharedPointer<T>& obj): Pointer<T>(NULL)
		{
			assign(obj);
		}

		SharedPointer<T>& operator=(const SharedPointer<T>& obj)
		{
			if(this != &obj)
			{
				clear();
				assign(obj);
			}

			return *this;
		}

		void clear()
		{
			T* toDel = this->m_pointer;
			int* ref = this->m_ref;

			this->m_pointer = NULL;
			this->m_ref = NULL;

			if(ref)
			{
				(*ref)--;

				if(*ref == 0)
				{
					free(ref);

					delete toDel;
				}
			}
		}

		~SharedPointer()
		{
			clear();
		}
	};
template <typename T>	
static bool operator==(const T* l,const SharedPointer<T>& r)
{
	return (l == r.get());
}

template <typename T>
static bool operator!=(const T* l,const SharedPointer<T>& r)
{
	return (l!= r.get());
}

template <typename T>
static bool operator == (const SharedPointer<T>& l,const T* r)
{
	return (l.get()== r);
}

template <typename T>
static bool operator != (const SharedPointer<T>& l,const T* r)
{
	return (l.get()!= r);
}

template <typename T>
static bool operator==(const SharedPointer<T>& l,const SharedPointer<T>& r)
{
	return (l.get()==r.get());
}
template <typename T>
static bool operator!=(const SharedPointer<T>& l,const SharedPointer<T>& r)
{
	return (l.get()!=r.get());
}
}

#endif


