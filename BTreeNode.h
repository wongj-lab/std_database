#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace WLib
{
enum BTNodePos
{
	ANY,
	LEFT,
	RIGHT
};

template <typename T>
class BTreeNode : public TreeNode<T>
{
public:
	BTreeNode* left;
	BTreeNode* right;

	BTreeNode(bool flag=false):TreeNode<T>(flag)
	{
		left = NULL;
		right = NULL;
	}

	static BTreeNode<T>* NewNode()
	{
		BTreeNode<T>* ret = new BTreeNode<T>();

		if(ret != NULL)
		{
			ret->flag = true;
		}

		return ret;
	}
};
}

#endif

