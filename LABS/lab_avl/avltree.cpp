/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file. IMPORTANT: read avltree.h to understand
 * what to do in this lab.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL) {
        subtree = new Node(key, value);
    } else {
        if (key < subtree->key) {
            insert(subtree->left, key, value);
        } else {
            insert(subtree->right, key, value);
        }
    }

    // Rebalance tree after insertion (don't remove this)
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node* node)
{
    if (node == NULL){
        node->height = -1;
        return;
    }

    node->height = max(height(node->left), height(node->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    Node* newSubRoot = t->right;
    t->right = newSubRoot->left;
    newSubRoot->left = t;
    t = newSubRoot;

    updateHeight(t->left);
    updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    Node* newSubRoot = t->left;
    t->left = newSubRoot->right;
    newSubRoot->right = t;
    t = newSubRoot;

    updateHeight(t->right);
    updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{

    int leftHeight = height(subtree->left);
    int rightHeight = height(subtree->right);

    if (leftHeight == rightHeight || leftHeight - rightHeight == 1 || leftHeight - rightHeight == -1) {                                    // case 5: tree is already balanced
        updateHeight(subtree);

    } else if(leftHeight - rightHeight >= 2) {

        int leftLeftHeight = height(subtree->left->left);
        int leftRightHeight = height(subtree->left->right);

        if(leftRightHeight > leftLeftHeight) {
            rotateLeftRight(subtree);                                  // case 3: left right
            updateHeight(subtree);
        } else {
            rotateRight(subtree);                                      // case 2: right
            updateHeight(subtree);
        }

    } else if(leftHeight - rightHeight <= -2){
        
        int rightLeftHeight = height(subtree->right->left);
        int rightRightHeight = height(subtree->right->right);

        if(rightLeftHeight > rightRightHeight) {
            rotateRightLeft(subtree);                                 // case 4: right left
            updateHeight(subtree);
        } else {
            rotateLeft(subtree);                                      // case 1: left
            updateHeight(subtree);
        }  

    }

    return;

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        /* Reached the node that we need to delete */
        if (subtree->left == NULL && subtree->right == NULL) {
            /* Case 1: Node to remove has no children */
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /*Case 2: Node to remove has two children */
            // find iop
            Node *iop = subtree->left;
            Node* parent = subtree;

            while (iop->right!=NULL) {
                parent = iop;
                iop = iop->right;
            }

            parent->right = iop->left;
            swap(iop, subtree);
            delete iop;
            
            return;

        } else {
            /* Case 3: Node to remove has one child */
            Node* curr = subtree;
            subtree = max(subtree->left, subtree->right);
            delete curr;
        }
        rebalance(subtree);
    }
}
