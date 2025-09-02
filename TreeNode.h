#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace WLib
{
template <typename T>
class TreeNode : public Object
{
protected:
	bool m_flag;

	TreeNode(const TreeNode<T>&);
	TreeNode<T>& operator=(const TreeNode<T>&);

	void* operator new(size_t size) throw()
	{
		return Object::operator new(size);
	}
public:
	T value;
	TreeNode<T>* parent;

	TreeNode(bool flag=false)
	{
		m_flag = flag;
		parent = NULL;
	}

	bool flag()
	{
		return m_flag;
	}

	virtual ~TreeNode()=0;
};
}


#endif

