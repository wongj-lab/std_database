#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"
// #include "DynamicHeap.h"


namespace WLib
{
class Sort: public Object
{
private:
	Sort();
	Sort(const Sort&);
	Sort& operator=(const Sort&);


	template <typename T>
	static void Swap(T& a,T& b)
	{
		T c(a);
		a = b;
		b = c;
	}

template <typename T>
static void Merge(T src[],T helper[],int begin,int mid,int end,bool min2max)
{
	int i = begin;
	int j = mid+1;
	int k = begin;

	while((i<=mid)&&(j<=end))
	{
		if(min2max?(src[i]<src[j]):(src[i]>src[j]))
		{
			helper[k++] = src[i++];
		}
		else
		{
			helper[k++] = src[j++];
		}
	}

	while(i <= mid)
	{
		helper[k++] = src[i++];
	}

	while(j <= end)
	{
		helper[k++] = src[j++];
	}

	for(i=begin;i<=end;i++)
	{
		src[i] = helper[i];
	}
}

template <typename T>
static void Merge(T src[],T helper[],int begin,int end,bool min2max)
{
	if(begin < end)
	{
		int mid = (begin+end)/2;

		Merge(src,helper,begin,mid,min2max);
		Merge(src,helper,mid+1,end,min2max);
		Merge(src,helper,begin,mid,end,min2max);
	}
}

template <typename T>
static int Partition(T array[],int begin,int end,bool min2max)
{
	T pv = array[begin];

	while(begin < end)
	{
		while((begin < end)&&(min2max?(array[end]>pv):(array[end]<pv)))
		{
			end--;
		}

		Swap(array[begin],array[end]);

		while((begin < end)&&(min2max?(array[begin]<=pv):(array[begin]>=pv)))
		{
			begin++;
		}

		Swap(array[begin],array[end]);
	}

	array[begin] = pv;

	return begin;
}

template <typename T>
static void Quick(T array[],int begin,int end,bool min2max)
{
	if(begin < end)
	{
		int pivot = Partition(array,begin,end,min2max);

		Quick(array,begin,pivot-1,min2max);
		Quick(array,pivot+1,end,min2max);
	}
}
public:

template <typename T>
static void Select(T array[],int len,bool min2max=true)
{
	for(int i=0;i<len;i++)
	{
		int min = i;
		for(int j=i+1;j<len;j++)
		{
			if(min2max?(array[min]>array[j]):(array[min]<array[j]))
			{
				min = j;
			}
		}

		if(min!=i)
		{
			Swap(array[i],array[min]);
		}
	}
}

template <typename T>
static void Insert(T array[],int len,bool min2max=true)
{
	    // 外层循环：从第二个元素开始处理（索引为1）
    // 因为第一个元素可以看作已排序部分
	for(int i=1;i<len;i++)
	{
		// k 记录当前元素最终应该插入的位置

		int k = i;
		// e 保存当前要插入的元素值
		T e = array[i];
        // 内层循环：在已排序部分中从后往前查找合适的插入位置
        // j=i-1 表示从已排序部分的最后一个元素开始比较
        // 条件：j>=0 保证不越界
        // min2max ? (array[j]>e) : (array[j]<e) 判断是否需要继续向前移动
        // - 如果是升序(min2max=true)，当array[j]>e时继续向前查找
        // - 如果是降序(min2max=false)，当array[j]<e时继续向前查找

		for(int j=i-1;(j>=0)&&(min2max?(array[j]>e):(array[j]<e));j--)
		{
            // 将比e大(升序)或比e小(降序)的元素向后移动一位
			array[j+1] = array[j];
            // 更新插入位置
			k = j;
		}
		// 如果k不等于i，说明元素e需要插入到前面的位置
        // 即在内层循环中找到了合适的插入位置

		if(k!=i)
		{
			// 将元素e插入到正确位置
			array[k]=e;
		}
	}
}

template <typename T>
static void Bubble(T array[],int len,bool min2max = true)
{
	bool exchange = true;
    // 外层循环控制排序轮数，内层循环进行相邻元素比较和交换
    // 若某一轮没有发生交换，则说明数组已经有序，可以提前结束

	for(int i=0;(i<len)&&exchange;i++)
	{
		exchange = false;
    // 从后往前进行比较，将最小(或最大)的元素逐步"冒泡"到前面
 
		for(int j=len-1;j>i;j--)
		{
			if(min2max?(array[j]<array[j-1]):(array[j]>array[j-1]))
			{
				Swap(array[j],array[j-1]);
				exchange = true;
			}
		}
	}
}
template <typename T>
static void Shell(T array[],int len,bool min2max=true)
{
		/*
         * 希尔排序函数
         * 
         * 使用希尔排序算法对数组进行排序。希尔排序是插入排序的一种改进版本，
         * 通过将原始数组分割成若干个子序列来进行排序，从而提高效率。
         * 
         * @param array 待排序的数组
         * @param len 数组长度
         * @param min2max 排序方向，true表示升序，false表示降序，默认为升序
         */	
	int d = len;

	do
	{
		d = d/3+1;
		for(int i=d;i<len;i++)
		{
			int k = i;
			int e = array[i];

			for(int j = i-d;(j>=0)&&(min2max?(array[j]>e):(array[j]<e));j-=d)
			{
				array[j+d] = array[j];
				k=j;
			}

			if(k != i)
			{
				array[k]=e;
			}
		}
	}while(d > 1);
}

template <typename T>
static void Merge(T array[],int len,bool min2max=true)
{
	T* helper = new T[len];

	if(helper != NULL)
	{
		Merge(array,helper,0,len-1,min2max);
	}

	delete[] helper;
}

template <typename T>
static void Quick(T array[],int len,bool min2max = true)
{
	Quick(array,0,len-1,min2max);
}

//   Heap未完成
//
template <typename T>
static void Select(Array<T>& array,bool min2max = true)
{
	Select(array.array(),array.length(),min2max);
}

template <typename T>
static void Insert(Array<T>& array,bool min2max=true)
{
	Insert(array.array(),array.length(),min2max);
}

template <typename T>
static void Bubble(Array<T>& array,bool min2max=true)
{
	Bubble(array.array(),array.length(),min2max);
}

template <typename T>
static void Shell(Array<T>& array,bool min2max=true)
{
	Shell(array.array(),array.length(),min2max);
}

template <typename T>
static void Merge(Array<T>& array,bool min2max=true)
{
	Merge(array.array(),array.length(),min2max);
}

template <typename T>
static void Quick(Array<T>& array,bool min2max=true)
{
	Quick(array.array(),array.length(),min2max);
}

};
}

#endif

