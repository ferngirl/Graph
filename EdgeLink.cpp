#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<queue>
#include<assert.h>
#include<iostream>
using namespace std;

//���ڽӱ�洢ͼ
template<class W>
struct EdgeLinkNode
{
	EdgeLinkNode(size_t src, size_t dst, W weight)
	:_src(src)
	, _dst(dst)
	, _weight(weight)
	{}

	size_t _src;//��ʼλ��
	size_t _dst;//Ŀ��λ��
	W _weight;//Ȩֵ
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

	void AddEdge(const V& v1, const V& v2, W weight)//ͼ�����������ڵ�ڵ㼰��ߵ���Ϣ
	{
		size_t src = GetIndexOfVeritx(v1);
		size_t dst = GetIndexOfVeritx(v2);
		assert(src != dst);
		_AddrEdge(src, dst, weight);
	}

	//����ڵ���Ⱥͳ���
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
		if (_isDirection)//����ͼ��ȵ��ڳ���
		{
			inCount = outCount;
		}
		
		if (!_isDirection)//����ͼ������£�Ҫ�����������
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

	void Print()//ѹӡͼ
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



/////////////////////////////ͼ�ı��������֣�/////////////////////
//������ȱ��������������Ĳ�����������ö��У�
	/*
	void BFS(const V& v)//ȱ�ݣ�ֻ�ܷ�����ͨͼ
	{
		queue<size_t> q;
		vector<bool> flags(_vertrix.size(), false);//����Ѿ����ʹ��Ľڵ�
		size_t index = GetIndexOfVeritx(v);
		q.push(index);
		while (!q.empty())
		{
			size_t ret = q.front();
			q.pop();
			if (flags[ret] == false)
			{
				cout << _vertrix[ret] << "--->";
				flags[ret] = true;
				EdgeLinkNode<W>* pCur = _edges[ret];
				while (pCur)
				{
					q.push(pCur->_dst);
					pCur = pCur->_pNext;
				}
			}
		}
	}
*/

	void _BFS(queue<size_t> &q, vector<bool>& flags, const V& v)
	{
		size_t index = GetIndexOfVeritx(v);
		q.push(index);
		while (!q.empty())
		{
			size_t ret = q.front();
			q.pop();
			if (flags[ret] == false)
			{
				cout << _vertrix[ret] << "--->";
				flags[ret] = true;
				EdgeLinkNode<W>* pCur = _edges[ret];
				while (pCur)
				{
					q.push(pCur->_dst);
					pCur = pCur->_pNext;
				}
			}
		}
	}

	void BFS(const V& v)//ȱ�ݣ�ֻ�ܷ�����ͨͼ
	{
		queue<size_t> q;
		vector<bool> flags(_vertrix.size(), false);//����Ѿ����ʹ��Ľڵ�
		
		_BFS(q, flags, v);

		for (size_t idx = 0; idx < _vertrix.size(); ++idx)
		{
			if (flags[idx] == false)
			{
				//cout << _vertrix[idx]<< "--->";
				_BFS(q, flags, _vertrix[idx]);
			}
		}
		cout << "NULL" <<endl;
	}

	//�����������

	void _MSF(size_t& src, vector<bool>& flags)
	{
		if (flags[src] == false)
		{
			cout << _vertrix[src] << "--->";
			flags[src] = true;
			EdgeLinkNode<W>* pCur = _edges[src];
			while (pCur)
			{
				_MSF(pCur->_dst, flags);
				pCur = pCur->_pNext;
			}
		}
	}
	void MSF(const V& v)
	{
		vector<bool> flags(_vertrix.size(),false);
		size_t index = GetIndexOfVeritx(v);
		_MSF(index, flags);
		for (size_t idx = 0; idx < _vertrix.size(); ++idx)
		{
			if (flags[idx] == false)
				_MSF(idx, flags);
		}
		cout << "NULL" << endl;
	}

	/////////////////////////��С������////////////////////////
	//��������ͼ�Ķ�����ͬ
	//n���ڵ㣬��ͼ�� n-1����
	//��С������Ȩֵ��С

//kruskal�㷨---ÿ��ѡ��Ȩֵ��С�ıߣ�Ȼ���жϸñ߼��Ϻ��Ƿ񹹳ɻ������ò��鼯��
	struct complare
	{
		bool operator()(EdgeLinkNode<W>* n1, EdgeLinkNode<W>* n2)
		{
			if (n1->_weight < n2->_weight)
				return true;
			return false;
		}
	};
	bool kruskal(GraphLink<V, W>& g)
	{
		g._vertrix = _vertrix;
		g._isDirection = _isDirection;
		g._edges.resize(_edges.size());

		vectoe<EdgeLinkNode<W>*> edges;//�����洢�����ڵ㣬Ȼ���������
		for (size_t idx = 0; idx < _vertrix.size(); ++idx)
		{
			EdgeLinkNode<W>* pCur = _edges[idx];
			while (pCur)
			{
				edges.push(pCur);
				pCur = pCur->_pNext;
			}
		}
		sort(edges.begin(),edges.end(), complare);
		size_t count = 1;
		UnionFindSer ufs(_vertrix.size());

		for (size_t idx = 0; idx < edges.size(); ++idx)
		{
			EdgeLinkNode<W>* pCur = edges[idx];
			if (!ufs.IsSameSet(pCur->_src, pCur->_dst))
			{
				g._AddEdge(pCur->_src, pCur->_dst, pCur->_weight);
				if (_isDirection)
					g._AddrEdge(pCur->_dst, pCur->_src, pCur->_weight);
				ufs.Union(pCur->_dst, pCur->_src);
				count++;
				if (count == _vertrix.size());
				return true;
			}
		}
		return false;
	}


private:
	vector<V> _vertrix;
	vector<EdgeLinkNode<W>*> _edges;
	bool _isDirection;
};
