#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct node {
    int type;
    bool *value;

    char calc;
    struct node *left;
    struct node *right;
};

bool p, q, r, s, t, one, zero;
static int i = 0;

int create(const char *str, int len, node **root);
int deleteTree(node *root);
bool calcValue(node *root);
void setBoolValue(int i);

int main(void) {
    one = true;
    zero = false;
    string str;
    cin >> str;
    int flag;
    while (str != "0") {
        flag = 0;
        node *root;
        i = 0;
        create(str.c_str(), str.length(), &root);
        for (int j = 0; j < 32; j++) {
            setBoolValue(j);
            if (calcValue(root) == false) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            cout << "not" << endl;
        } else {
            cout << "tautology" << endl;
        }

        deleteTree(root);
        cin >> str;
    }
    return 0;
}

void setBoolValue(int i) {
    p = i & 1;
    q = i & 2;
    r = i & 4;
    s = i & 8;
    t = i & 16;
    return;
}

bool calcValue(node *root) {
    if (root->type == 0) {
        return *(root->value);
    }
    if (root->calc == 'N') {
        return !calcValue(root->left);
    }
    if (root->calc == 'K') {
        return calcValue(root->left) && calcValue(root->right);
    }
    if (root->calc == 'A') {
        return calcValue(root->left) || calcValue(root->right);
    }
    if (root->calc == 'C') {
        return (!calcValue(root->left)) || calcValue(root->right);
    }
    if (root->calc == 'E') {
        return calcValue(root->left) == calcValue(root->right);
    }
    return true;
}

int create(const char *str, int len, node **root) {
    *root = (node *)malloc(sizeof(node));
    (*root)->left = NULL;
    (*root)->right = NULL;
    if (str[i] >= 'p' && str[i] <= 't') {
        (*root)->type = 0;
        (*root)->calc = 0;
    } else {
        (*root)->type = 1;
        (*root)->value = NULL; // do not know
    }
    switch (str[i++]) {
    case 'p':
        (*root)->value = &p;
        break;
    case 'q':
        (*root)->value = &q;
        break;
    case 'r':
        (*root)->value = &r;
        break;
    case 's':
        (*root)->value = &s;
        break;
    case 't':
        (*root)->value = &t;
        break;
    case 'N':
        (*root)->calc = 'N';
        create(str, len, &((*root)->left));
        break;
    case 'K':
        (*root)->calc = 'K';
        create(str, len, &((*root)->left));
        create(str, len, &((*root)->right));
        break;
    case 'A':
        (*root)->calc = 'A';
        create(str, len, &((*root)->left));
        create(str, len, &((*root)->right));
        break;
    case 'C':
        (*root)->calc = 'C';
        create(str, len, &((*root)->left));
        create(str, len, &((*root)->right));
        break;
    case 'E':
        (*root)->calc = 'E';
        create(str, len, &((*root)->left));
        create(str, len, &((*root)->right));
        break;
    default:
        break;
    }
    return 0;
}

int deleteTree(node *root) {
    if (root->left == NULL && root->right == NULL) {
        free(root);
        return 0;
    }
    if (root->left != NULL) {
        deleteTree(root->left);
    }
    if (root->right != NULL) {
        deleteTree(root->right);
    }
    return 0;
}
