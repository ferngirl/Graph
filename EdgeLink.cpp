#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<assert.h>
#include<iostream>
using namespace std;

//用邻接表存储图
template<class W>
struct EdgeLinkNode
{
	EdgeLinkNode(size_t src, size_t dst, W weight)
	:_src(src)
	, _dst(dst)
	, _weight(weight)
	{}

	size_t _src;//起始位置
	size_t _dst;//目标位置
	W _weight;//权值
	EdgeLinkNode<W>* _pNext;
};

template<class V,class W>
class GraphLink
{
public:
	GraphLink(const V* array, size_t size, bool isDirection=true)
		:_vertrix(array,array+size)
	{
		_edges.resize(size);
	}

	size_t GetIndexOfVeritx(const V& v)
	{
		for (size_t idx = 0; idx < _vertrix.size(); ++idx)
		{
			if (_vertrix[idx] == v)
				return idx;
		}
	}

	void _AddrEdge(size_t src, size_t dst, W weight)
	{
		for (size_t idx = 0; idx < _edges.size(); ++idx)
		{
			EdgeLinkNode<W>* pCur = _edges[idx];
			while (pCur)
			{
				if (pCur->_dst == dst)
				{
					pCur->_weight = weight;
					return;
				}
				pCur = pCur->_pNext;
			}
		}
		EdgeLinkNode<W>* pEdge = new EdgeLinkNode<W>(src,dst,weight);
		pEdge->_pNext = _edges[src];
		_edges[src] = pEdge;
		if (_isDirection)
		{
			pEdge->_pNext = _edges[src];
			_edges[src] = pEdge;
		}
	}

	void AddEdge(const V& v1, const V& v2, W weight)//图中增加两个节点节点及其边的信息
	{
		size_t src = GetIndexOfVeritx(v1);
		size_t dst = GetIndexOfVeritx(v2);
		assert(src != dst);
		_AddrEdge(src, dst, weight);
	}

	//求出入度和出度
	pair<int,int> GetDev(const V& v)
	{
		size_t inCount = 0;
		size_t outCount = 0;

		size_t index = GetIndexOfVeritx(v);
		EdgeLinkNode<W>* pCur = _edges[index];
		while (pCur)
		{
			outCount++;
			pCur = pCur->_pNext;
		}
		if (_isDirection)//无向图入度等于出度
		{
			inCount = outCount;
		}
		
		if (!_isDirection)//有向图的情况下，要单独求出出度
		{
			for (size_t idx = 0; idx < _vertrix.size(); ++idx)
			{
				pCur = _edges[idx];
				if (pCur && pCur->_dst == index)
					continue;
				while (pCur)
				{
					if (pCur->_dst == index)
					{
						inCount++;
						break;
					}
					pCur = pCur->_pNext;
				}
			}
		}
		return make_pair(inCount, outCount);
	}

	void Print()//压印图
	{
		for (size_t idx = 0; idx < _edges.size(); ++idx)
		{
			EdgeLinkNode<W>* pCur = _edges[idx];
			cout << _vertrix[idx] << "--->";
			while (pCur)
			{
				cout << pCur->_dst << "[" << pCur->_weight << "]" << "--->";
				pCur = pCur->_pNext;
			}
			cout << "NULL" << endl;
		}
	}
private:
	vector<V> _vertrix;
	vector<EdgeLinkNode<W>*> _edges;
	bool _isDirection;
};
