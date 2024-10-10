#include <iostream>

class Node
{
public:
    int data;
    Node *next;
};

class LinkedList
{
public:
    Node *head;

    LinkedList()
    {
        head = nullptr;
    }

    // ノードを追加する関数
    void append(int new_data)
    {
        Node *new_node = new Node();
        new_node->data = new_data;
        new_node->next = nullptr;

        if (head == nullptr)
        {
            head = new_node;
            return;
        }

        Node *last = head;
        while (last->next != nullptr)
        {
            last = last->next;
        }
        last->next = new_node;
    }

    // リストの内容を表示する関数
    void printList()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }
};

int main()
{
    LinkedList list;
    list.append(10);
    list.append(20);
    list.append(30);

    list.printList(); // 出力: 10 20 30
    return 0;
}
