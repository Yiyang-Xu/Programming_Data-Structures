//
//  main.cpp
//  二叉树
//
//  Created by 康艺潇 on 2020/4/15.
//  Copyright © 2020 康艺潇 518431910002. All rights reserved.
//

#include <iostream>
#include <queue>
#include<vector>
using namespace std;
template<class Type>
class BinaryTree{
private:
    struct Node{//二叉树的结点类
        Node*left,*right;
        Type data;
        Node():left(NULL),right(NULL){}
        //参数化列表，内置结构体，结构体也可以有函数，不同之处：结构体定义中默认情况下的成员是public，而类定义中的默认情况下的成员是private的。
        Node(Type item,Node *L=NULL,Node *R=NULL):data(item),left(L),right(R){}
    };
    Node *root;//二叉树的根节点
public:
    BinaryTree():root(NULL){}//其实里面的元素就只有一个根节点，内置类不用管他。
    BinaryTree(const Type &value){//& 可不要
        root=new Node(value);
    }//why &????
    ~BinaryTree(){clear();}  //有了new，要自己写析构函数，析构一般用clear;clear写在后面也可以哦
    Type getRoot(){return root->data;}
    Type getLeft(){return root->left->data;}
    Type getRight(){return root->right->data;}
    
    void createTree(Type flag){
        Node*tmp;
        queue<Node *>que;
        Type x,ldata,rdata;
        cout<<"\n输入根节点：";
        cin>>x;
        root=new Node(x);
        que.push(root);
        while(!que.empty()){
            tmp=que.front();
            que.pop();
            cout<<"\n输入"<<tmp->data<<"的两个儿子"<<flag<<"表示空结点";
            cin>>ldata>>rdata;
            if (ldata!=flag) {
                que.push(tmp->left=new Node(ldata));
            }
            if (rdata!=flag) {
                que.push(tmp->right=new Node(rdata));
            }
        }
        cout<<"create completed!\n";
    }
    void makeTree(const Type &x,BinaryTree &Lt,BinaryTree &Rt){
        root=new Node(x,Lt.root,Rt.root);
        Lt.root=NULL;
    Rt.root=NULL;//Lt和Rt已经合并到当前的树里面变成子树了，所以不能直接用Lt.root.left之类的调用，这样会对当前的树产生影响，所以开除它在森林里面自立门户的执照，砍掉原来的根。
    }

    void delLeft(){
        BinaryTree tmp=root->left;
        root->left=NULL;
        tmp.clear();
    }
    void delRight(){
        BinaryTree tmp=root->right;
        root->right=NULL;
        tmp.clear();
    }
    bool isEmpty()const{//好的编程习惯是：常数函数加const
        return root==NULL;//学习这个表达！！
    }
    void clear(){
        if(root!=NULL) clear(root);//防止到私有函数那里对于左子树和右子树的访问失败。
        root=NULL;
    }
    //上一个已经delete root了，这样就不能用这个指针了，所以要把它设为空。
    //知识点：指针对应的内存删除之后指向哪里？
    //删除以后，指针还是指向原来的地址，但是原来地址对应的空间已经被系统回收了，如果继续访问很可能会导致异常退出。所以要求删除指针以后，需要将指针赋值为NULL，表示这个指针已经不指向任何有效内存。
    int size()const{
        return size(root);
    }
    int height()const{
        return height(root);
    }
    void preOrder()const{
        if(root!=NULL){
            cout<<"\n先序遍历：";//\n加在”“里面也可以换行
            preOrder(root);
        }
    }
    void midOrder()const{
           if(root!=NULL){
               cout<<"\n中序遍历：";
               midOrder(root);
           }
       }
    void postOrder()const{
           if(root!=NULL){
               cout<<"\n后序遍历：";
               postOrder(root);
           }
       }
private:
    void clear(Node *t){  //递归妙哉！！
        if(t->left!=NULL)clear(t->left);
        if(t->right!=NULL)clear(t->right);
        delete t;
    }
    int size(Node *t)const{
        if(t==NULL)return 0;//注意判空，这样就不用对于左边右边是不是0额外讨论了
        else return 1+size(t->left)+size(t->right);
    }

    int height(Node *t)const{
        if(t==NULL)return 0;//注意:1.判空!!而且放在最前面，不然下一句会爆掉
        else {
            int lh=height(t->left);
            int rh=height(t->right);
            return 1+((lh>rh)?lh:rh);
        }//注意：1.这里的最外面的一个（）必须加上，？的优先级低于+，会报错。2.学习这样的表达
        }
    void preOrder(Node *t)const{
        if (t!=NULL) {
            cout<<t->data;
            preOrder(t->left);
            preOrder(t->right);
        }
    }
    void midOrder(Node *t)const{
         if (t!=NULL) {
             midOrder(t->left);
             cout<<t->data;
             midOrder(t->right);
         }
     }
     void postOrder(Node *t)const{
          if (t!=NULL) {
              postOrder(t->left);
              postOrder(t->right);
              cout<<t->data;
          }
      }
      
    };


int main() {
    BinaryTree<char>tree,tree1('M'),tree2;
    tree.createTree('.');
    cout<<"tree高度为："<<tree.height()<<endl;
    cout<<"tree规模为："<<tree.size()<<endl;
    tree.preOrder();
    tree.midOrder();
    tree.postOrder();
    tree2.makeTree('Y', tree, tree1);
    cout<<endl;
    cout<<"tree2高度为："<<tree2.height()<<endl;
    cout<<"tree2规模为："<<tree2.size()<<endl;
    tree2.preOrder();
    tree2.midOrder();
    tree2.postOrder();
    return 0;
    
}
