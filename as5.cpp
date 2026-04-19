#include <iostream>
using namespace std;

class avl_node{
    public:
    int value;
    avl_node *left, *right;
    friend class avltree;
    
};

class avltree {
    public :
    avl_node *root;
    int height (avl_node*);
    int diff (avl_node*);
    avl_node *rr(avl_node*);
    avl_node *ll(avl_node*);
    avl_node *lr(avl_node*);
    avl_node *rl(avl_node*);
    avl_node *balance(avl_node*);
    avl_node* insert();
    avl_node* insert(avl_node*,avl_node*);
    avl_node* display(avl_node*,int);
    // void inorder(avl_node*);
    // void preorder(avl_node*);
    // void postorder(avl_node*);
    avltree()
    {
        root=NULL;
    }

};

avl_node* avltree :: ll (avl_node *parent)
{
   	avl_node * temp = parent->left;
    	parent->left = temp->right;
    	temp->right = parent;
    	return temp;
}

avl_node* avltree:: rr (avl_node *parent)
{
    	avl_node* temp = parent->right;
    	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

avl_node* avltree:: lr(avl_node *parent)
{
    avl_node *temp = parent->left;
    parent->left = rr (temp); //calling RR rotation
    return ll(parent); 
    
}

avl_node* avltree:: rl (avl_node *parent)
{
    avl_node *temp = parent->right;
    parent->right = ll (temp); // calling LL rotation
    return rr (parent);
    
}




int avltree::diff(avl_node *temp){
    int l_height=height (temp->left);
    int r_height=height (temp->right);
    int b_factor=l_height - r_height;
    return b_factor;
}

int avltree::height(avl_node *temp){
    int h=0;
    if(temp != NULL){
        int l_height=height (temp->left);
        int r_height=height (temp->right);
        int max_height= max(l_height,r_height);
        h=max_height + 1;
    }
    return h;
}

avl_node* avltree :: balance(avl_node *temp){
    int bal_factor = diff(temp);
    if(bal_factor > 1){
      if (diff (temp->left)>0){
           temp = ll(temp);       
    } else {
        temp= lr(temp);
    }
    }
    else if(bal_factor < -1){
      if (diff (temp->right)>0){
           temp = rl(temp);       
    } else {
        temp= rr(temp);
    }
    }
    return temp;
}

avl_node* avltree:: insert( avl_node *root, avl_node *temp)
{
    if (root == NULL)
    {
        root = new avl_node;
        root->value= temp->value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
      else if (temp->value< root->value)
     {
        root->left = insert(root->left, temp);
        root = balance (root);
     }
     else if (temp->value >= root->value)
     {
        root->right = insert(root->right, temp);
        root = balance (root);
     }
     return root;
}

avl_node* avltree :: insert()
{
    char ch;
    do {
        avl_node *temp = new avl_node;  // allocate memory
        cout << "Enter the value: ";
        cin >> temp->value;

        root = insert(root, temp);

        cout << "Enter your choice (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

avl_node* avltree::display(avl_node* ptr, int level)
{
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root)
            cout << "Root -> ";
        for (int i = 0; i < level && ptr != root; i++)
            cout << "        ";
        cout << ptr->value;
        display(ptr->left, level + 1);
    }
    return ptr;
}

// avl_node* avltree::inorder(avl_node* tree)
// {
//     if (tree != NULL)
//     {
//         inorder(tree->left);
//         cout << tree->value << " ";
//         inorder(tree->right);
//     }
//     return tree;
// }

// avl_node* avltree::preorder(avl_node* tree)
// {
//     if (tree != NULL)
//     {
//         cout << tree->value << " ";
//         preorder(tree->left);
//         preorder(tree->right);
//     }
//     return tree;
// }

// avl_node* avltree::postorder(avl_node* tree)
// {
//     if (tree != NULL)
//     {
//         postorder(tree->left);
//         postorder(tree->right);
//         cout << tree->value << " ";
//     }
//     return tree;
// }

int main()
{
    avltree obj;

    cout << "AVL Tree Insertion\n";
    obj.insert();

    cout << "\nDisplay AVL Tree:\n";
    obj.display(obj.root, 1);

    // cout << "\n\nInorder Traversal:\n";
    // obj.inorder(obj.root);

    // cout << "\n\nPreorder Traversal:\n";
    // obj.preorder(obj.root);

    // cout << "\n\nPostorder Traversal:\n";
    // obj.postorder(obj.root);

    cout << endl;

    return 0;
}