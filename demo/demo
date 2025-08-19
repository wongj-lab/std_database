#include "iostream"

using namespace std;

int func(int a[],int len) // n*n +2
{
	int ret = 0; // 1
	for(int i=0;i< len;i++) // n*n
	{
		for(int j=0;j<len;j++)
		{
			ret += a[i]*a[j];
		}
	}

	return ret; // 1
}

int main()
{
	int array[] = {1,2,3,4,5};
	/*下面这个函数的时间复杂度为O(n^2)*/
	cout << func(array,5) <<endl;

	return 0;
}
