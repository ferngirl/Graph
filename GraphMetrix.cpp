#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<assert.h>
#include<iostream>
using namespace std;

//用矩阵存储图
template<class V,class W>
class GraphMetrix
{
public:
	GraphMetrix(const V* array, size_t size, bool isDirection = true)
		:_veritx(array, array + size)
		, _isDirection(isDirection)
	{
		_edges.resize(size);
		for (size_t idx = 0; idx < size; ++idx)
		{
			_edges[idx].resize(size);
		}
	}

	size_t GetIndexOfVeritx(const V& v)
	{
		for (size_t idx = 0; idx < _veritx.size(); ++idx)
		{
			if (_veritx[idx] == v)
				return idx;
		}
	}

	void AddEdge(const V& v1, const V& v2,const W& weight)
	{
		size_t index1 = GetIndexOfVeritx(v1);
		size_t index2 = GetIndexOfVeritx(v2);

		assert(index1 != index2);
		_edges[index1][index2] = weight;
		if (_isDirection)//默认为无向图
		{
			_edges[index2][index1] = weight;
		}
	}
	
private:
	vector<V> _veritx;//存放顶点值
	vector <vector<W>> _edges;//用二维矩阵存放边
	bool _isDirection;
};
