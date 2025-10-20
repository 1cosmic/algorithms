#include <iostream>
#include <string>
#include <list>
#include <random>
#include <ranges>
#include <algorithm>

using namespace std;

struct Node {
    int v;
    struct Node *next;

    // Constructor
    Node (int value): v(value), next(nullptr) {}
};

struct NodeList{
    private:
        struct Node* head = nullptr;
        int size = 0;

    public:
        void push_back(int v) {
            struct Node* new_node = new Node(v);

            auto cur_node = head;
            while (cur_node != nullptr and cur_node->next != nullptr) {
                cur_node = cur_node->next;
            }
            if (head == nullptr) head = new_node;
            else cur_node->next = new_node;
            size++;

            cout << "Was added v: " << v << endl;
        };

        auto s() {
            return size;
        };

        void print_all() {
            cout << "s: ";
            struct Node* cur = head;
            while (cur != nullptr) {
                cout << cur->v << " | ";
                cur = cur->next;
            }
            cout << endl;
        };
};


auto is_cycled(list<int> l)
{
    auto fast = l.begin();
    auto slow = l.begin();
    auto end = l.end();

    cout << "Start search 1/2 of array..." << endl;
    // while (fast != end or fast != (end - 1)) {
    //     fast++; fast++;
    //     slow++;
    // }
    cout << "The middle of list: " << *slow << endl;
}


int main()
{
    list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    NodeList node_list;
    
    for (int n: list) {
        node_list.push_back(n);
    }
    node_list.print_all(); 
    cout << "size: " << node_list.s() << endl;
    
    // is_cycled(list);

    return 0;
}