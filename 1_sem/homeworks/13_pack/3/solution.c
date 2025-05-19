#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int height(Node *node)
{
    return node ? node->height : 0;
}

int get_balance(Node *node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

Node *create_node(int key)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *tmp = x->right;

    x->right = y;
    y->left = tmp;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *tmp = y->left;

    y->left = x;
    x->right = tmp;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

Node *find_min_node(Node *node)
{
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

Node *find_max_node(Node *node)
{
    while (node->right)
    {
        node = node->right;
    }
    return node;
}

int find_min_value(Node *root, int key, int prev)
{
    if (!root)
    {
        return prev;
    }
    if (key == root->key)
    {
        return key;
    }
    if (key < root->key)
    {
        return find_min_value(root->left, key, root->key);
    }
    return find_min_value(root->right, key, prev);
}

Node *delete(Node *root, int key)
{
    if (!root)
    {
        return root;
    }

    if (key < root->key)
    {
        root->left = delete(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = delete(root->right, key);
    }
    else
    {
        if (!root->left || !root->right)
        {
            Node *temp = root->left ? root->left : root->right;
            if (!temp)
            {
                temp = root;
                root = NULL;
            } else
            {
                *root = *temp;
            }
            free(temp);
        } else
        {
            Node *temp = find_min_node(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }

    if (!root)
    {
        return root;
    }

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0)
    {
        return rotateRight(root);
    }
    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0)
    {
        return rotateLeft(root);
    }
    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}


Node *insert(Node *node, int key)
{
    if (!node)
    {
        return create_node(key);
    }

    if (key < node->key)
    {
        node->left = insert(node->left, key);
    } else if (key > node->key)
    {
        node->right = insert(node->right, key);
    } else
    {
        return node;
    }

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && key < node->left->key)
    {
        return rotateRight(node);
    }

    if (balance < -1 && key > node->right->key)
    {
        return rotateLeft(node);
    }

    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

int contains(Node *root, int key)
{
    if (!root)
    {
        return 0;
    }
    if (key == root->key)
    {
        return 1;
    }
    if (key < root->key)
    {
        return contains(root->left, key);
    }
    return contains(root->right, key);
}


int main()
{
    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M;
    scanf("%d", &M);

    Node *node = NULL;

    while (M--)
    {
        char op[7];
        scanf("%s", &op);
        int key;
        scanf("%d", &key);

        switch (op[0])
        {
            case 'a':
                if (contains(node, key))
                {
                    printf("dupe\n");
                }
                else
                {
                    node = insert(node, key);
                    printf("added\n");
                }
                break;

            case 'r':
                if (contains(node, key))
                {
                    node = delete(node, key);
                    printf("removed\n");
                }
                else
                {
                    printf("miss\n");
                }
                break;
            case 'l':
                if (key > find_max_node(node)->key)
                {
                    printf("###\n");
                }
                else
                {
                    printf("%d\n", find_min_value(node, key, 0));
                }
                break;
        }
    }

    return 0;
}
