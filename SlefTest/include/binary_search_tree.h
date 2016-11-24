#ifndef CHARLES_BINARY_SEARCH_TREE_H__
#define CHARLES_BINARY_SEARCH_TREE_H__

#include <exception>
#include <iostream>
/**
	The key to know the binary search tree is to know
	the building progress of the tree

***/
namespace charles{
	template <typename KeyT,typename ValueT>
		class BST{
			private:
				struct treeNode{
					KeyT 	key;			//	key
					ValueT 	value;			//	value
					treeNode 	*parent;	//	parent
					treeNode	*left;		//	left child
					treeNode 	*right;		//	right child
				};

				class BSTException : public std::exception
				{
					public:
						virtual const char * what() const throw(){
							return "key does not exist";
						}

				} excp_key;

			private:
				treeNode *m_root;
			private:
				BST(const BST&);
				BST& operator=(const BST&);
			public:
				BST():m_root(nullptr){};
				~BST(){
					destruct_(m_root);
				}

				/**
				*find key
				**/
				treeNode * find(const KeyT & key)
				{
					treeNode * n = m_root;
					while(n != nullptr && key != n->key)
					{
						if( key < n->key){
							n = n->left;
						}else{
							n = n->right;
						}
					}
					return n;
				}

				/**
				insert a new data into the binary search tree
				!!!the inserted node will always be the leaf node of the binary search tree!!!
				**/
				void insert(const KeyT& key,const ValueT & value){
					treeNode *z = new treeNode;
					z->key = key;
					z->value = value;
					z->left = z->right = z->parent = nullptr;

					treeNode * n = m_root;
					treeNode * y = nullptr;
					while(n!=nullptr) {
						y = n;
						if(key < n->key) {
							n = n->left;
						}else {
							n = n->right;
						}
					}
					z->parent = y;
					if(y == nullptr) {//means empty tree
						m_root = z;
					} else if(key < y->key) {
						y->left = z;
					} else {
						y->right = z;
					}
				}

				/**
				delete a key from the binary search tree
				!!!first to find the node to be deleted!!!
				**/
				bool deleteKey(const KeyT & key) {
					treeNode * z = find(key);
					if(z == nullptr) {
						return false;
					}

					//if the target node has no left child
					if(z->left == nullptr) { 
						transplant(z, z->right);
					//if the target node has no right child
					}else if(z->right == nullptr) {
						transplant(z, z->left);
					}else {
						//find the minimum element of the right subtree
						treeNode *y = minimum(z->right);
						if(y->parent != z) {
							transplant(y,y->right);
							y->right = z->right;
							y->right ->parent = y;
						}	
						//replace z with y
						transplant(z,y);
						y->left = z->left;
						y->left->parent = y;			
					}
					delete z;
					return true;
				}

				/**
				print tree
				**/
				void print_tree(treeNode* n, int indent) { 
					if(n == nullptr) {
						return;
					}
					print_tree(n->right,indent+1);
					int i;
					for(i = 0;i < indent;++i) {
						printf(" ");
					}
					std::cout << "[" << n->key << "," << n->value << "]" << std::endl;
					print_tree(n->left,indent+1);
				}

				void print_helper() {
				
					print_tree(m_root,0);
				}
				
			private:

				/**
				replace node u with v
				**/
				void transplant(treeNode *u, treeNode *v) {
					if(u->parent == nullptr) {
						m_root = v;
					}else if(u == u->parent->left) {
						u->parent->left = v;
					}else {
						u->parent->right = v;
					}

					if(v != nullptr) {
						v->parent = u->parent;
					}
				}
				void destruct_(treeNode *n) {
					if(n==nullptr) return;
					destruct_(n->left);
					destruct_(n->right);
					delete n;
				}

				/**
				find the minimum element of the subtree
				**/
				treeNode * minimum(treeNode *x) {
					while(x->left != nullptr){
						x = x->left;
					}
					return x;
				}




		};

}

#endif