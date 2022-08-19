//
// Created by shea on 8/12/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED                1
#define BLACK            2

typedef int KEY_TYPE;

typedef struct rbtree_node {
    unsigned char color;
    struct rbtree_node *right;
    struct rbtree_node *left;
    struct rbtree_node *parent;
    KEY_TYPE key;
    void *value;
} rbtree_node;

typedef struct rbtree {
    rbtree_node *root;
    rbtree_node *nil;
} rbtree;

rbtree_node *rbtree_mini(rbtree *T, rbtree_node *x) {
    while (x->left != T->nil) {
        x = x->left;
    }
    return x;
}

rbtree_node *rbtree_maxi(rbtree *T, rbtree_node *x) {
    while (x->right != T->nil) {
        x = x->right;
    }
    return x;
}

rbtree_node *rbtree_successor(rbtree *T, rbtree_node *x) {
    rbtree_node *y = x->parent;

    if (x->right != T->nil) {
        return rbtree_mini(T, x->right);
    }

    while ((y != T->nil) && (x == y->right)) {
        x = y;
        y = y->parent;
    }
    return y;
}

/**
 * 红黑树左旋
 * @param T
 * @param x 结点
 */
void rbtree_left_rotate(rbtree *T, rbtree_node *x) {

    rbtree_node *y = x->right;  // x  --> y  ,  y --> x,   right --> left,  left --> right

    x->right = y->left; //1 1
    if (y->left != T->nil) { //1 2
        y->left->parent = x;
    }

    y->parent = x->parent; //1 3
    if (x->parent == T->nil) { //1 4
        T->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x; //1 5
    x->parent = y; //1 6
}

/**
 * 红黑树右旋
 * @param T
 * @param y 结点
 */
void rbtree_right_rotate(rbtree *T, rbtree_node *y) {

    rbtree_node *x = y->left;

    y->left = x->right;
    if (x->right != T->nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == T->nil) {
        T->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

void rbtree_insert_fixup(rbtree *T, rbtree_node *z) {

    while (z->parent->color == RED) { //z ---> RED
        if (z->parent == z->parent->parent->left) { //父结点是祖父结点的左子树
            rbtree_node *y = z->parent->parent->right;
            if (y->color == RED) {  //叔结点是红色
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent; //z --> RED
            } else {    //叔结点是黑色

                if (z == z->parent->right) {    //当前结点是右孩子
                    z = z->parent;
                    rbtree_left_rotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_right_rotate(T, z->parent->parent);
            }
        } else {    //父结点是祖父结点的右子树
            rbtree_node *y = z->parent->parent->left;
            if (y->color == RED) {  //叔结点是红色
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent; //z --> RED
            } else {    //叔结点是黑色
                if (z == z->parent->left) { //当前结点是左孩子
                    z = z->parent;
                    rbtree_right_rotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_left_rotate(T, z->parent->parent);
            }
        }

    }

    T->root->color = BLACK;
}


void rbtree_insert(rbtree *T, rbtree_node *z) {

    rbtree_node *y = T->nil;
    rbtree_node *x = T->root;

    while (x != T->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else if (z->key > x->key) {
            x = x->right;
        } else {    //Exist
            return;
        }
    }

    //将z插入
    z->parent = y;
    if (y == T->nil) {  //T是空树
        T->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;

    rbtree_insert_fixup(T, z);  //插入后修复
}

void rbtree_delete_fixup(rbtree *T, rbtree_node *x) {

    while ((x != T->root) && (x->color == BLACK)) {
        if (x == x->parent->left) {

            rbtree_node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;

                rbtree_left_rotate(T, x->parent);
                w = x->parent->right;
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {

                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbtree_right_rotate(T, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rbtree_left_rotate(T, x->parent);

                x = T->root;
            }

        } else {

            rbtree_node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rbtree_right_rotate(T, x->parent);
                w = x->parent->left;
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {

                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbtree_left_rotate(T, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbtree_right_rotate(T, x->parent);

                x = T->root;
            }

        }
    }

    x->color = BLACK;
}

rbtree_node *rbtree_delete(rbtree *T, rbtree_node *z) {

    rbtree_node *y;
    rbtree_node *x = T->nil;

    if ((z->left == T->nil) || (z->right == T->nil)) {
        y = z;
    } else {
        y = rbtree_successor(T, z);
    }

    if (y->left != T->nil) {
        x = y->left;
    } else if (y->right != T->nil) {
        x = y->right;
    }

    x->parent = y->parent;
    if (y->parent == T->nil) {
        T->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != z) {
        z->key = y->key;
        z->value = y->value;
    }

    if (y->color == BLACK) {
        rbtree_delete_fixup(T, x);
    }

    return y;
}

rbtree_node *rbtree_search(rbtree *T, KEY_TYPE key) {

    rbtree_node *node = T->root;
    while (node != T->nil) {
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            return node;
        }
    }
    return T->nil;
}


void rbtree_traversal(rbtree *T, rbtree_node *node) {
    if (node != T->nil) {
        rbtree_traversal(T, node->left);
        printf("key:%d, color:%d\n", node->key, node->color);
        rbtree_traversal(T, node->right);
    }
}

int main() {

    int keyArray[20] = {24, 25, 13, 35, 23, 26, 67, 47, 38, 98, 20, 19, 17, 49, 12, 21, 9, 18, 14, 15};

    rbtree *T = (rbtree *) malloc(sizeof(rbtree));
    if (T == NULL) {
        printf("malloc failed\n");
        return -1;
    }

    T->nil = (rbtree_node *) malloc(sizeof(rbtree_node));
    T->nil->color = BLACK;
    T->root = T->nil;

    rbtree_node *node;
    int i;
    for (i = 0; i < 20; i++) {
        node = (rbtree_node *) malloc(sizeof(rbtree_node));
        node->key = keyArray[i];
        node->value = NULL;

        rbtree_insert(T, node);

    }

    rbtree_traversal(T, T->root);
    printf("----------------------------------------\n");
    rbtree_node *inode;
    for (i = 0; i < 20; i++) {

        inode = rbtree_search(T, keyArray[i]);
        rbtree_node *cur = rbtree_delete(T, inode);
        free(cur);

        rbtree_traversal(T, T->root);
        printf("----------------------------------------\n");
    }


}
