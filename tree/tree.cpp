#include <iostream>
#include <locale.h>
#include <queue>

using namespace std;

class node
{
public:
    int m_info;
    node* m_left;
    node* m_right;


    node(int info) :m_info(info), m_right(nullptr), m_left(nullptr) {}
};

void print_depth(node* root);
void print_width(node* root);

class tree
{
public:
    node* m_root;


    tree() : m_root(nullptr) {}
public:
    node* add(int x, node* root)
    {
        if (!root)
            return new node(x);
        if (x >= root->m_info)
            root->m_right = add(x, root->m_right);
        else
            root->m_left = add(x, root->m_left);
        return root;
    }

    node* find(int x, node* root)
    {
        node* v = root;
        if (root)
        {
            while (x != v->m_info)
            {
                if (x > v->m_info)
                {
                    if (v->m_right)
                        v = v->m_right;
                    else
                    {
                        cout << "Такого элемента нет\n";
                        return nullptr;
                    }
                }
                else
                {
                    if (v->m_left)
                        v = v->m_left;
                    else
                    {
                        cout << "Такого элемента нет\n";
                        return nullptr;
                    }
                }
            }
            return v;
        }
        else
        {
            cout << "Дерева нет\n";
            return nullptr;
        }
    }

    void print(node* root)
    {
        if (root)
        {
            int flag;
            cout << "Обход в глубину: 0\nОбход в ширину: 1\n";
            cin >> flag;
            while (flag != 1 && flag != 0)
            {
                cout << "Обход в глубину: 0\nОбход в ширину: 1\n";
                cin >> flag;
            }
            if (flag)
                print_width(root);
            if (!flag)
                print_depth(root);
        }
        else
            cout << "Дерева нет\n";
    }

    int del(node* &root)
    {
        int flag;
        if (root)
        {
            cout << "Удалить элемент: 0\nУдалить дерево: 1\n";
            cin >> flag;
            while (flag != 1 && flag != 0)
            {
                cout << "Удалить элемент: 0\nУдалить дерево: 1\n";
                cin >> flag;
            }
            if (flag)
            {
                del_tree(root);
                return 0;
            }
            else
            {
                del_node(root);
                return 0;
            }
        }
        else
        {
            cout << "Дерево отсутствует\n";
            return 0;
        }
    }

    void del_node(node* root)
    {
        int info;
        cout << "Введите элемент: ";
        cin >> info;
        node* v = root;
        if (find(info, root) != nullptr)
        {
            while (1)
            {
                if (v->m_right)
                {
                    if (info == v->m_right->m_info)
                    {
                        if (v->m_right->m_right)
                        {
                            node* buf = v->m_right->m_right;
                            delete(v->m_right);
                            v->m_right = buf;
                        }
                        else if (v->m_right->m_left)
                        {
                            node* buf = v->m_right->m_left;
                            delete(v->m_right);
                            v->m_right = buf;
                        }
                        else
                        {
                            delete(v->m_right);
                            v->m_right = nullptr;
                        }
                        return;
                    }
                    if (info > v->m_right->m_info)
                        v = v->m_right;
                }
                if (v->m_left)
                {
                    if (info == v->m_left->m_info)
                    {
                        if (v->m_left->m_right)
                        {
                            node* buf = v->m_left->m_right;
                            delete(v->m_left);
                            v->m_left = buf;
                        }
                        else if (v->m_left->m_left)
                        {
                            node* buf = v->m_left->m_left;
                            delete(v->m_left);
                            v->m_left = buf;
                        }
                        else
                        {
                            delete(v->m_left);
                            v->m_left = nullptr;
                        }
                        return;
                    }
                    if (info > v->m_left->m_info)
                        v = v->m_left;
                }               
            }
        }
        else
        {
            cout << "Такого элемента нет";
            return;
        }
	}

    node* del_tree(node* &root)
    {
        if (root)
        {
            del_tree(root->m_left);
            del_tree(root->m_right);
            delete(root);
            root = nullptr;
            return nullptr;
        }
        return nullptr;
    }
};

void print_depth(node* root) // в глубину
{
    if (root == nullptr)
        return;
    cout << root->m_info << " ";
    print_depth(root->m_right);
    print_depth(root->m_left);
}

void print_width(node* root)
{
    if (root == nullptr)
        return;
    queue<node*> q;
    q.push(root);
    while (!q.empty())
    {
        node* cur = q.front();
        q.pop();
        cout << cur->m_info << " ";
        if (cur->m_right != nullptr)
            q.push(cur->m_right);
        if (cur->m_left != nullptr)
            q.push(cur->m_left);
    }
}

int main()
{
    setlocale(LC_ALL, "russian");
    int flag;
    tree root;
    cout << "Добавить элемент: 1\nУдалить элемент: 2\nНайти элемент: 3\nВывести дерево: 4\nВыход: 0\n";
    cin >> flag;
    while (flag != 1 && flag != 2 && flag != 3 && flag != 4 && flag != 0)
    {
        cout << "Добавить элемент: 1\nУдалить элемент: 2\nНайти элемент: 3\nВывести дерево: 4\n";
        cin >> flag;
    }
    while (1)
    {
        int x;
        switch (flag)
        {
            case 1: cout << "Введите элемент: "; cin >> x; root.m_root = root.add(x, root.m_root); break;
            case 2: root.del(root.m_root); break;
            case 3: cout << "Введите элемент: "; cin >> x; cout << root.find(x, root.m_root) << endl; break;
            case 4: root.print(root.m_root); break;
            case 0: exit(0);
        }
        cout << "\nДобавить элемент: 1\nУдалить элемент: 2\nНайти элемент: 3\nВывести дерево: 4\nВыход: 0\n\n";
        cin >> flag;
        while (flag != 1 && flag != 2 && flag != 3 && flag != 4 && flag != 0)
        {
            cout << "Добавить элемент: 1\nУдалить элемент: 2\nНайти элемент: 3\nВывести дерево: 4\n";
            cin >> flag;
        }
    }
}