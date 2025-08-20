#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"



namespace WLib
{
template <typename T>
class DynamicList: public SeqList<T>
{
	protected:
		int m_capacity;
	public:
		DynamicList(int capacity)
		{
			this->m_array = new T[capacity];

			if(this->m_array != NULL)
			{
				this->m_length = 0;
				this->m_capacity = capacity;
			}
			else
			{
				THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create dynamiclist object...");
			}
		}
		int capacity()const
		{
			return m_capacity;
		}

		void resize(int capacity)
		{
			if(m_capacity != capacity)
			{
				T* array = new T[capacity];

				if(array != NULL)
				{
					int length = (this->m_length < capacity)?this->m_length: capacity;

					for(int i = 0;i<length;i++)
					{
						array[i] = this->m_array[i];
					}

					T* temp = this->m_array;

					this->m_array = array;
					this->m_length = length;
					this->m_capacity = capacity;

					delete[] temp;
				}
				else
				{
					THROW_EXCEPTION(NoEnoughMemoryException,"no memory to resize dynamic object ...");
				}
			}
		}

		~DynamicList()
		{
			delete[] this->m_array;
		}
};
}

#endif

