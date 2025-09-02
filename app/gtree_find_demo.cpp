// demo/gtree_find_demo.cpp
#include "GTree.h"
#include "GTreeNode.h"
#include <iostream>
#include <string>

using namespace std;
using namespace WLib;

int main()
{
    cout << "=== GTree find 方法测试 ===" << endl;
    
    try {
        // 创建一个泛型树
        GTree<string> tree;
        
        // 构建树结构
        cout << "--- 创建树结构 ---" << endl;
        TreeNode<string>* root = tree.insert("Root", nullptr);
        cout << "创建根节点: Root" << endl;
        
        TreeNode<string>* child1 = tree.insert("Child1", root);
        TreeNode<string>* child2 = tree.insert("Child2", root);
        TreeNode<string>* child3 = tree.insert("Child3", root);
        cout << "创建子节点: Child1, Child2, Child3" << endl;
        
        TreeNode<string>* child1_1 = tree.insert("Child1_1", child1);
        TreeNode<string>* child1_2 = tree.insert("Child1_2", child1);
        cout << "为Child1创建子节点: Child1_1, Child1_2" << endl;
        
        TreeNode<string>* child2_1 = tree.insert("Child2_1", child2);
        TreeNode<string>* child2_1_1 = tree.insert("Child2_1_1", child2_1);
        cout << "为Child2创建子节点: Child2_1, Child2_1_1" << endl;
        
        cout << "\n--- 测试 find(const T& value) 方法 ---" << endl;
        
        // 测试查找存在的节点
        GTreeNode<string>* foundNode = tree.find("Child2_1");
        if(foundNode != nullptr) {
            cout << "成功找到节点: " << foundNode->value << endl;
            
            // 显示父节点信息
            if(foundNode->parent != nullptr) {
                GTreeNode<string>* parent = dynamic_cast<GTreeNode<string>*>(foundNode->parent);
                if(parent != nullptr) {
                    cout << "父节点: " << parent->value << endl;
                }
            }
        } else {
            cout << "未找到节点: Child2_1" << endl;
        }
        
        // 测试查找根节点
        foundNode = tree.find("Root");
        if(foundNode != nullptr) {
            cout << "成功找到根节点: " << foundNode->value << endl;
        }
        
        // 测试查找不存在的节点
        foundNode = tree.find("NonExistent");
        if(foundNode == nullptr) {
            cout << "正确处理不存在的节点: NonExistent (返回nullptr)" << endl;
        }
        
        // 测试查找子节点
        foundNode = tree.find("Child1_2");
        if(foundNode != nullptr) {
            cout << "成功找到节点: " << foundNode->value << endl;
        }
        
        cout << "\n--- 测试 find(TreeNode<T>* node) 方法 ---" << endl;
        
        // 获取一个已知节点的指针进行测试
        GTreeNode<string>* knownNode = tree.find("Child2_1_1");
        if(knownNode != nullptr) {
            cout << "已知节点: " << knownNode->value << endl;
            
            // 使用 find(TreeNode<T>* node) 方法查找同一个节点
            GTreeNode<string>* foundByPointer = tree.find(knownNode);
            if(foundByPointer != nullptr) {
                cout << "通过指针成功找到节点: " << foundByPointer->value << endl;
                cout << "两个指针指向同一对象: " << (knownNode == foundByPointer ? "是" : "否") << endl;
            }
        }
        
        // 测试查找nullptr
        GTreeNode<string>* nullResult = tree.find(static_cast<TreeNode<string>*>(nullptr));
        if(nullResult == nullptr) {
            cout << "正确处理nullptr参数 (返回nullptr)" << endl;
        }
        
        // 测试查找不在当前树中的节点
        GTree<string> anotherTree;
        TreeNode<string>* anotherRoot = anotherTree.insert("AnotherRoot", nullptr);
        TreeNode<string>* anotherNode = anotherTree.insert("AnotherNode", anotherRoot);
        
        GTreeNode<string>* anotherGNode = anotherTree.find("AnotherNode");
        if(anotherGNode != nullptr) {
            cout << "在另一棵树中找到节点: " << anotherGNode->value << endl;
            
            // 尝试在第一棵树中查找另一棵树的节点
            GTreeNode<string>* notFound = tree.find(anotherGNode);
            if(notFound == nullptr) {
                cout << "正确处理不属于当前树的节点 (返回nullptr)" << endl;
            }
        }
        
        // cout << "\n--- 遍历并查找所有节点 ---" << endl;
        // 使用广度优先遍历查找所有节点
        // if(tree.begin()) {
        //     int nodeCount = 0;
        //     do {
        //         string currentValue = tree.current();
        //         GTreeNode<string>* node = tree.find(currentValue);
        //         if(node != nullptr) {
        //             cout << "节点 " << ++nodeCount << ": " << currentValue 
        //                  << " - 查找验证: " << (node->value == currentValue ? "成功" : "失败") << endl;
        //         }
        //     } while(tree.next());
        // }
        
        cout << "\n--- 性能测试 ---" << endl;
        // 测试查找性能
        // clock_t start = clock();
        // for(int i = 0; i < 1000; i++) {
        //     tree.find("Child2_1_1");
        // }
        // clock_t end = clock();
        // cout << "1000次查找操作耗时: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << endl;
        
    } catch(const Exception& e) {
        cout << "捕获异常: " << e.message() << " (" << e.location() << ")" << endl;
    } catch(...) {
        cout << "捕获未知异常" << endl;
    }
    
    cout << "\n=== find 方法测试结束 ===" << endl;
    
    return 0;
}