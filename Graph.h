#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Sort.h"

namespace WLib
{
template <typename E>
struct Edge : public Object
{
	int b;
	int a;
	E data;

	Edge(int i=-1,int j=-1)
	{
		b=i;
		a=j;
	}
	Edge(int i,int j,const E& value)
	{
		b=i;
		e=j;
		data=value;
	}

	bool operator==(const Edge<E>& obj)
	{
		return (b==obj.b)&&(e==obj.e);
	}

	bool operator!=(const Edge<E>& obj)
	{
		return !(*this==obj);
	}
	bool operator<(const Edge<E>& obj)
	{
		return (data<obj.data);
	}

	bool operator>(const Edge<E>& obj)
	{
		return (data > obj.data);
	}
};

template <typename V,typename E>
class Graph: public Object
{
protected:
	DynamicArray<T>* toArray(LinkQueue<T>& queue)
	{
		DynamicArray<T>* ret = new DynamicArray<T>(queue.length());

		if(ret != NULL)
		{
			for(int i=0;i<ret->length();i++,queue.remove())
			{
				ret->set(i,queue.front);
			}
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create ret object ...");
		}

		return ret;
	}

	SharedPointer<Array<Edge<E>>> getUndirectedEdges()
	{
		DynamicArray<Edge<E>>* ret = NULL;
		if(asUndirected())
		{
			LinkQueue<Edge<E>>queue;

			for(int i=0;i<vCount();i++)
			{
				for(int j=i;j<vCount();j++)
				{
					if(isAdjacent(i,j))
					{
						queue.add(Edge<E>(i,j,getEdge(i,j)));
					}
				}
			}

			ret = toArray(queue);
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException,"this function is for undirected graph only ...");
		}

		return ret;
	}

	int find(Array<int>& p,int v)
	{
		while(p[v]!=-1)
		{
			v = p[v];
		}

		return v;
	}
public:
	virtual V getVertex(int i) = 0;
	virtual bool getVertex(int i,V& value) = 0;
	virtual bool setVertex(int i,const V& value) = 0;
	virtual SharedPointer<Array<int>>getAdjacent(int i) = 0;
	virtual bool isAdjacent(int i,int j) = 0;
	virtual E getEdge(int i,int j) = 0;
	virtual bool getEdge(int i,int j,E& value) = 0;
	virtual bool setEdge(int i,int j,const E& value) = 0;
	virtual bool removeEdge(int i,int j) = 0;
	virtual int vCount() = 0;
	virtual int eCount() = 0;
	virtual int OD(int i) = 0;
	virtual int ID(int i) = 0;

	virtual int TD(int i)
	{
		return OD(i)+ID(i);
	}
	
	Graph<V,E>& self()
	{
		return *this;
	}

	bool asUndirected()
	{
		bool ret = true;
		for(int i=0;i<vCount();i++)
		{
			for(int j=0;j<vCount();j++)
			{
				if(isAdjacent(i,j))
				{
					ret = ret && isAdjacent(j,i) && (getEdge(i,j)==getEdge(j,i));
				}
			}
		}

		return ret;
	}

	SharedPointer<Array<Edge<E>>> prim(const E& LIMIT,const bool MININUM=true)
	{
		LinkQueue<Edge<E>> ret;

		if(asUndirected())
		{
			DynamicArray<int> adjVex(vCount());// 记录每个城市在生成树中连接到哪个城市
			DynamicArray<bool> mark(vCount()); //标记哪些城市已经被连接到网络中
			DynamicArray<E> cost(vCount());//记录从当前网络到每个未连接城市的最低成本
			SharedPointer<Array<int>>aj = NULL;

			bool end=false;
			int v=0;

			for(int i=0;i<vCount();i++)
			{
				adjVex[i] = -1;
				mark[i] = false;
				cost[i] = LIMIT;
			}

			mark[v] = true;

			aj = getAdjacent(v); //顶点v所有相邻顶点存储到aj
			for(int j=0;j<aj->length();j++)
			{
				cost[(*aj)[j]] = getEdge(v,(*aj)[j]);
				adjVex[(*aj)[j]] = v;
			}

			for(int i=0;(i<vCount())&&!end;i++)
			{
				E m = LIMIT;
				int k = -1;

				for(int j=0;j<vCount();j++)
				{
					if(!mark[j]&&(MININUM?(cnst[j] < m):(cost[j]> m)))
					{
						m = cost[j];
						k = j;
					}
				}

				end = (k == -1);

				if(!end)
				{
					ret.add(Edge<E>(adjVex[k],k,getEdge(adjVex[k],k)));
					mark[k] = true;

					aj = getAdjacent(k);

					for(int j=0;j<aj->length();j++)
					{
						if(!mark[(*aj)[j]] && (MININUM?(getEdge(k,(*aj)[j])<cost[(*aj)[j]]):(getEdge(k,(*aj)[j]) > cost[(*aj)[j]])))
						{
							cost[(*aj)[j]] = getEdge(k,(*aj)[j]);
							adjVex[(*aj)[j]] = k;
						}
					}
				}
			}

		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException,"prim operation is for undirected graph only ...");
		}
		if(ret.length()!=(vCount()-1))
		{
			THROW_EXCEPTION(InvalidOperationException,"no enough edge for prim operation ...");
		}
		return toArray(ret);
	}

	SharedPointer<Array<Edge<E>>> kruskal(const bool MININUM = true)
	{
		LinkQueue<Edge<E>>ret;
		SharedPointer<Array<Edge<E>>> edges = getUndirectedEdges();
		DynamicArray<int> p(vCount());

		for(int i=0;i<p.length();i++)
		{
			p[i] = -1;
		}

		Sort::Shell(*edges,MININUM);

		for(int i=0;(i<edges->length())&&(ret.length()<(vCount-1));i++)
		{
			int b = find(p,(*edges)[i].b);
			int e = find(p,(*edges)[i].e);

			if(b != e)
			{
				p[e] = b;
				ret.add((*edges)[i]);
			}
		}

		if(ret.length() != (vCount()-1))
		{
			THROW_EXCEPTION(InvalidOperationException,"no enough edges for kruskal operation ...");
		}

		return toArray(ret);
	}

	SharedPointer<Array<int>> BFS(int i)
	{
		DynamicArray<int>* ret = NULL;
		if((0<=i)&&(i<vCount()))
		{
			LinkQueue<int> q;//存储待访问的顶点
			LinkQueue<int> r;//存储访问过的顶点顺序
			DynamicArray<bool> visited(vCount());

			for(int i=0;i<visited.length();i++)
			{
				visited[i] = false;
			}
			q.add(i);

			while(q.length()>0)
			{
				int v = q.front();

				q.remove();

				if(!visited[v])
				{
					SharedPointer<Array<int>>aj = getAdjacent(v);

					for(int j=0;j<aj->length();j++)
					{
						q.add((*aj)[j]);
					}

					r.add(v);
					visited[v] = true;
				}
			}

			ret = toArray(r);

		}
		else
		{
			THROW_EXCEPTION(InvalidParameterException,"index i is invalid ...");
		}

		return ret;
	}

	SharedPointer<Array<int>>DFS(int i)
	{
		DynamicArray<int>* ret = NULL;
		if((0<=i)&&(i<vCount()))
		{
			LinkStack<int> s;
			LinkQueue<int> r;
			DynamicArray<bool> visited(vCount());

			for(int j=0;j<visited.length();j++)
			{
				visited[j] = false;
			}

			s.push(i);

			while(s.size() > 0)
			{
				int v = s.top();

				s.pop();

				if(!visited[v])
				{
					SharedPointer<Array<int>>aj = getAdjacent(v);

					for(int j=aj->length()-1;j>=0;j--)
					{
						s.push((*aj)[j]);
					}

					r.add(v);

					visited[v] = true;
				}
			}

			ret = toArray(r);
		}
		else
		{
			THROW_EXCEPTION(InvalidParameterException,"index i is invalid ...");
		}

		return ret;
	}

	SharedPointer<Array<int>> dijkstra(int i,int j,const E& LIMIT)
	{
		LinkQueue<int> ret;//准备一个队列存放最终的路径

		if((0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount()))
		{
			DynamicArray<E> dist(vCount());//记录从起点到每个点的最短距离
			DynamicArray<int> path(vCount());//记录每个点在最短路径中的前一个点
			DynamicArray<bool> mark(vCount());//标记哪些点已经找到了最短路径

			for(int k=0;k<vCount();k++)
			{
				mark[k] = false; // 所有城市都还没确定最短路线
				path[k] = -1;// 暂时不知道从哪来
				// 如果起点和k城市直接相连，距离就是这条路的长度，否则设为无穷大
				dist[k] = isAdjacent(i,k)?(path[k]=i,getEdge(i,k)):LIMIT;
			}
			mark[i] = true; // 起点的最短距离已经确定（就是0）

			for(int k=0;k<vCount();k++)
			{
				E m = LIMIT;
				int u = -1;

				for(int w=0;w<vCount();w++)
				{
					if(!mark[w]&&(dist[w] < m))
					{
						m = dist[w];
						u = w;
					}
				}

				if(u == -1)
				{
					break;
				}

				mark[u] = true;

				for(int w=0;w<vCount();w++)
				{
					if(!mark[w]&&isAdjacent(u,w)&&(dist[u]+getEdge(u,w)<dist[w]))
					{
						dist[w] = dist[u] + getEdge(u,w);
						path[w] = u;
					}
				}
			}

			LinkStack<int>s;

			s.push(j);

			for(int k=path[j];k!=-1;k=path[k])
			{
				s.push(k);
			}

			while(s.size() > 0)
			{
				ret.add(s.top());

				s.pop();
			}

		}
		else
		{
			THROW_EXCEPTION(InvalidParameterException,"index <i,j>is invalid ...");
		}

		if(ret.length()<2)
		{
			THROW_EXCEPTION(ArithmeticException,"there is no path from i to j ...");
		}

		return toArray(ret);
	}

	SharedPointer<Array<int>> floyd(int x,int y,const E& LIMIT)
	{
		LinkQueue<int> ret;

		if((0<=x)&&(x<vCount())&&(0<=y)&&(y<vCount()))
		{
			DynamicArray<DynamicArray<E>> dist(vCount());
			DynamicArray<DynamicArray<int>> path(vCount());

			for(int k=0;k<vCount();i++)
			{
				dist[k].resize(vCount());
				path[k].resize(vCount());
			}

			for(int i=0;i<vCount();i++)
			{
				for(int j=0;j<vCount();j++)
				{
					path[i][j] = -1;
					dist[i][j] = isAdjacent(i,j)?(path[i][j]=j,getEdge(i,j)):LIMIT;
				}
			}

			for(int k=0;k<vCount();k++)
			{
				for(int i=0;i<vCount();i++)
				{
					for(int j=0;j<vCount();j++)
					{
						if((dist[i][k]+dist[k][j]) < dist[i][j])
						{
							dist[i][j] = dist[i][j]+dist[k][j];
							path[i][j] = path[i][k];
						}
					}
				}
			}

			while((x!=-1)&&(x!=y))
			{
				ret.add(x);
				x = path[x][y];
			}

			if(x != -1)
			{
				ret.add(x);
			}
		}
		else
		{
			THROW_EXCEPTION(InvalidParameterException,"index <x,y> is invalid ...");
		}

		if(ret.length() < 2)
		{
			THROW_EXCEPTION(ArithmeticException,"there is no path from x to y ...");
		}

		return toArray(ret);
	}




};
}

#endif

