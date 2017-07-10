#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include"UnionFindSer.cpp"
#include<iostream>
using namespace std;


class UnionFindSer
{
public:
	UnionFindSer(size_t n)
		:_ufs(n, -1)
	{}
	void Union(size_t n1, size_t n2)//�鲢
	{
		size_t index1 = FindRoot(n1);
		size_t index2 = FindRoot(n2);

		if (index1 != index2)//�������ϲ�����ͬһ������
		{
			_ufs[index1] += _ufs[index2];
			_ufs[index2] = index1;
		}	
	}
	size_t FindRoot(size_t n)
	{
		size_t parent = n;
		while (_ufs[parent] >= 0)
		{
			parent = _ufs[parent];
		}
		return parent;
	}

	size_t Size()const
	{
		size_t count = 0;
		for (size_t idx = 0; idx < _ufs.size(); ++idx)
		{
			if (_ufs[idx] < 0)
				count++;
		}
		return count;
	}
private:
	vector<int> _ufs;
};


//С�������⣺����Ȧ�ĸ���{{1��2}��{2��3}��{3��4}}
size_t Count(int* array)
{
	size_t count = 0;
	for (size_t idx = 0; idx < array.size(); ++idx)
	{
		if (array[idx] < 0)
			count++;
	}
	return count;
}

/*
size_t CountOfFriend()//��������Ȧ�ĸ���
{
	int array[] = { 0, 1, 2, 3, 4 };
	for (size_t idx = 0; idx < sizeof(array) / sizeof(array[0]); ++idx)
	{
		array[idx] = -1;
	}

	Union(array,1, 2);
	Union(array,2, 3);
	Union(array,3, 4);

	return Count(array);
}

size_t FindRoot(int* array,size_t n)//����ÿ������Ȧ����鳤����
{
	size_t parent = n;
	while (array[parent] > 0)
		parent = array[parent];
	return parent;
}
void Union(int* array,size_t n1,size_t n2)//�ϲ�����
{
	size_t index1 = FindRoot(array,n1);
	size_t index2 = FindRoot(array,n2);

	if (index1 != index2)//�������ϲ�����ͬһ������
	{
		array[index1] += array[index2];
		array[index2] = index1;
	}
}
*/