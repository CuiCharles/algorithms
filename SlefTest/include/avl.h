//
//  AVLTree.h
//  C++Primer
//
//  Created by charles on 2016/12/8.
//  Copyright © 2016年 Cuiwenju. All rights reserved.
//

#ifndef AVLTree_h
#define AVLTree_h

#include <stdlib.h>
#include <stdio.h>



#define HEIGHT(p)   (   (p==NULL) ? -1 : ( ((Node*)(p))->height )   )
#define MAX(a,b)    (   (a) > (b) ? (a) : (b)   )


typedef int Type;

typedef struct AVLTreeNode {
    Type key;                   //key
    int height;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
}Node, *AVLTree;



//前序遍历
void preorder_avltree(AVLTree tree);

//中序遍历
void inorder_avltree(AVLTree tree);

//后序遍历
void postorder_avltree(AVLTree tree);

//打印avl树
void print_avltree(AVLTree tree,Type key,int direction);

//递归实现查找
Node* avltree_search(AVLTree tree ,Type key);

//非递归实现查找
Node* iterative_avltree_search(AVLTree tree,Type key);

//查找最小节点
Node* avltree_minimum(AVLTree tree);

//查找最大结点
Node* avltree_maximum(AVLTree tree);

//插入结点 -返回根节点
Node* avltree_insert(AVLTree tree, Type key);

//删除结点 -返回根节点的值
Node* avltree_delete(AVLTree tree, Type key);

//销毁avl树
void destroy_avltree(AVLTree tree);

int avltree_height(AVLTree tree);







//获取avl树的高度
int avltree_height(AVLTree tree) {
    return HEIGHT(tree);
}

//前序遍历
void preorder_avltree(AVLTree tree) {
    if(tree != NULL) {
        printf("%d ",tree->key);
        preorder_avltree(tree->left);
        preorder_avltree(tree->right);
    }
}

//中序遍历
void inorder_avltree(AVLTree tree) {
    if(tree != NULL) {
        inorder_avltree(tree->left);
        printf("%d ",tree->key);
        inorder_avltree(tree->right);
    }
}

//后序遍历
void postorder_avltree(AVLTree tree) {
    if(tree != NULL) {
        postorder_avltree(tree->left);
        postorder_avltree(tree->right);
        printf("%d ",tree->key);
    }
}

//递归实现查找
Node* avltree_search(AVLTree tree ,Type key){
    if(tree == NULL || key == tree->key){
        return tree;
    }
    if(key < tree->key){
        return avltree_search(tree->left,key);
    }else{
        return avltree_search(tree->right,key);
    }
    
}

//非递归实现查找
Node* iterative_avltree_search(AVLTree tree,Type key) {
    while((tree != NULL)&& (key != tree->key)) {
        if(key < tree->key){
            tree = tree->left;
        }else {
            tree = tree->right;
        }
    }
    return tree;
}

//查找最小节点
Node* avltree_minimum(AVLTree tree) {
    if(tree == NULL){
        return tree;
    }
    while(tree->left != NULL){
        tree = tree->left;
    }
    return tree;
}

//查找最大结点
Node* avltree_maximum(AVLTree tree) {
    if(tree == NULL) {
        return tree;
    }
    while(tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}

//创建avl树结点
static Node* avltree_create_node(Type key,Node* left,Node* right) {
    Node *p;
    if((p=(Node*)malloc(sizeof(Node))) == NULL)
        return NULL;
    p->key = key;
    p->left = left;
    p->right = right;
    p->height = 0;
    return p;
}

//LL：左左对应的情况（左单旋转）
//返回值：旋转后的根节点
static Node* left_left_rotation(AVLTree k2) {
    AVLTree k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    
    //取两个子树根节点高度较大的值+1
    k2->height = MAX( HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
    k1->height = MAX( HEIGHT(k1->left), k2->height) + 1;
    
    return k1;
}

//RR：右右对应的情况（右单旋转）
//返回值：旋转后的根节点
static Node* right_right_rotation(AVLTree k1) {
    AVLTree k2;
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    
    //取两个子树根节点高度较大的值+1
    k1->height = MAX( HEIGHT(k1->left), HEIGHT(k1 ->right)) + 1;
    k2->height = MAX( HEIGHT(k2->right), k1->height) + 1;
    
    return k2;
}


//LR:左右对应的情况（左双旋转）
static Node* left_right_rotation(AVLTree k3) {
    k3->left = right_right_rotation(k3->left);
    return left_left_rotation(k3);
}


//RL:右左对应的情况（右双旋转）
static Node* right_left_rotation(AVLTree k1) {
    k1->right = left_left_rotation(k1->right);
    return right_right_rotation(k1);
}

//插入结点 -返回根节点
Node* avltree_insert(AVLTree tree, Type key) {
    if(tree == NULL) {
        tree = avltree_create_node(key, NULL, NULL);
        if(tree == NULL){
            printf("ERROR:create avltree node failed!\n");
            return NULL;
        }
    }else if(key < tree->key){ //将key插入到左子树的情况
        tree->left = avltree_insert(tree->left, key);
        //插入节点后，如果avl树失去平衡，则进行相应的调节
        if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2){
            if(key < tree->left->key){
                tree = left_left_rotation(tree);
            }else{
                tree = left_right_rotation(tree);
            }
        }
    }else if(key > tree->key){
        tree->right = avltree_insert(tree->right, key);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = right_right_rotation(tree);
            else
                tree = right_left_rotation(tree);
        }
    }else{ //key = key
        printf("添加失败：不允许添加相同的节点！\n");
    }
    
    tree->height = MAX( HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
    return tree;
}

/*
 * 删除结点(z)，返回根节点
 *
 * 参数说明：
 *     ptree AVL树的根结点
 *     z 待删除的结点
 * 返回值：
 *     根节点
 */
static Node* delete_node(AVLTree tree, Node *z) {
    if(tree == NULL || z == NULL)
        return NULL;
    if(z->key < tree->key){// 待删除的节点在"tree的左子树"中
        tree->left = delete_node(tree->left, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            Node *r =  tree->right;
            if (HEIGHT(r->left) > HEIGHT(r->right))
                tree = right_left_rotation(tree);
            else
                tree = right_right_rotation(tree);
        }
    }else if(z->key > tree->key) {// 待删除的节点在"tree的右子树"中
        tree->right = delete_node(tree->right, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
        {
            Node *l =  tree->left;
            if (HEIGHT(l->right) > HEIGHT(l->left))
                tree = left_right_rotation(tree);
            else
                tree = left_left_rotation(tree);
        }
    }else {// tree是对应要删除的节点。(真正的删除发生在这里）
        //如果tree的左右孩子都不为空
        if((tree->left) && (tree->right)){
            if(HEIGHT(tree->left) > HEIGHT(tree->right)){
                //如果tree的左子树比右子树高
                //  (1)找出左子树中最大的值
                //  (2)将最大结点的值赋给tree
                //  (3)删除该最大结点
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                Node *max = avltree_maximum(tree->left);
                tree->key = max->key;
                tree->left = delete_node(tree->left,max);
            }else {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree。
                //   (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                Node* min = avltree_minimum(tree->right);
                tree->key = min->key;
                tree->right = delete_node(tree->right, min);
            }
        }else {
            Node *tmp = tree;
            tree = tree->left ? tree->left : tree->right;
            free(tmp);
        }
        
    }
    
    return tree;
}


/*
 * 删除结点(key是节点值)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 待删除的结点的键值
 * 返回值：
 *     根节点
 */
Node* avltree_delete(AVLTree tree, Type key)
{
    Node *z;
    
    if ((z = avltree_search(tree, key)) != NULL)
        tree = delete_node(tree, z);
    return tree;
}


//销毁avl树  递归的遍历思想
void destroy_avltree(AVLTree tree) {
    if(tree == NULL)
        return ;
    
    if(tree->left != NULL){
        destroy_avltree(tree->left);
    }
    if(tree->right != NULL){
        destroy_avltree(tree->right);
    }
    free(tree);
}

//打印avl树
void print_avltree(AVLTree tree,Type key,int direction) {
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            printf("%2d is root\n", tree->key);
        else                // tree是分支节点
            printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right" : "left");
        
        print_avltree(tree->left, tree->key, -1);
        print_avltree(tree->right,tree->key,  1);
    }
}







#endif /* AVLTree_h */
