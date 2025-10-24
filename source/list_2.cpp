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
            // cout << "Was added v: " << v << endl;
        };

        auto s() {
            return size;
        };

        void print_count(int c) {
            struct Node* cur = head;

            cout << "output of '" << c << "' falues of list:" << endl;
            cout << "list: ";
            while (cur != nullptr and c > 0) {
                cout << cur->v << " | ";
                cur = cur->next;
                c--;
            }
            cout << endl;
        };

        void print_all() {
            struct Node* cur = head;

            cout << "list: ";
            while (cur != nullptr) {
                cout << cur->v << " | ";
                cur = cur->next;
            }
            cout << endl;
        };

        void break_by_cycle() {
            struct Node* cur = head;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            cur->next = head;
        };

        auto begin() {
            return head;
        };

        auto pop(int v) {
            Node* dummy = new Node(NULL);
            Node* last = head;
            Node* cur = head;

            if (cur->v == v) {
                head = dummy;
                head->next = last->next;
                cout << "Was popped head of list." << endl;
                return true;

            } else {
                while (cur->next != nullptr) {
                    if (cur->v == v) {
                        last->next = cur->next;
                        size--;
                        return true;
                    }
                    last = cur;
                    cur = cur->next;
                }
                cout << "not found such element: " << v << endl;
                return false;
            }
        }; 

        // TODO: not working
        auto reverse() {
            Node* last = nullptr;
            Node* cur = head;
            Node* next = cur;

            while (next != nullptr) {
                next = cur->next;
                cur->next = last;
                last = cur;
                cur = next;
                // if (cur != nullptr) cout << last->v << " " << cur->v << " " << endl;
            }
            head = last;
        }

        void set_head(Node* new_head) {
            head = new_head;
        }
};


auto is_looped(NodeList l)
{
    auto fast = l.begin();
    auto slow = l.begin();
    int i;

    auto run = true;
    while (run) {
        for (i = 0; i < 2; i++) {
            if (fast != nullptr)
                fast = fast->next;
            else return "false";
        }
        if (slow != nullptr)
            slow = slow->next;
        else return "false";

        if (slow == fast) return "true";
    }
}


auto get_value_half(NodeList l)
{
    auto fast = l.begin();
    auto slow = l.begin();
    int i;

    auto run = true;
    while (run) {
        for (i = 0; i < 2; i++) {
            fast = fast->next;
            if (fast == nullptr) return slow->v;
        }
        slow = slow->next;
    }
}


auto is_palindrome(string word) {

    deque <char> deq;
    for (char c:word)
        deq.push_back(c);

    char l, r;
    auto run = true;
    while (deq.size() > 1) {
        l = deq.front();
        r = deq.back();
        if (l == r) {
            deq.pop_front();
            deq.pop_back();
        }
        else return "false";
    }
    return "true";
}


auto is_source(string a, string b) {
    queue<char> q;
    for (char c:a) {
        q.push(c);
    }

    for (char c: b) {
        if (q.front() == c) {
            q.pop();
        };
    }
    if (q.size() == 0) {
        return "true";
    } else {
        return "false";
    }
}

auto merge2sorted(NodeList& l1, NodeList& l2) {
    Node* p1 = l1.begin();
    Node* p2 = l2.begin();
    Node* cur = nullptr;

    if (cur == nullptr) {
        if (p1->v <= p2->v) {
            cur = p1;
            p1 = p1->next;
        }
        else {
            cur = p2;
            p2 = p2->next;
        }
        l1.set_head(cur);
    }

    while (p1 != nullptr or p2 != nullptr) {
        if (p2 == nullptr or p1->v <= p2->v) {
            cur->next = p1;
            cur = p1;
            p1 = p1->next;

        } else {
            cur->next = p2;
            cur = p2;
            p2 = p2->next;
        }
    }
}


int main()
{
    cout << "Generate of list:" << endl;
    NodeList node_list;
    list<int> source_l = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int n: source_l) {
        node_list.push_back(n);
    }
    node_list.print_all(); cout << endl;

    cout << "1) Get half of list: " << get_value_half(node_list) << endl << endl;

    int n = 8; cout << "2) Pop from list: " << n << endl;
    node_list.pop(n);
    node_list.print_all();

    n = 1; cout << "pop from list: " << n << endl;
    node_list.pop(n);
    node_list.print_all(); cout << endl;

    cout << "3) Reversing list: " << endl; node_list.print_all();
    node_list.reverse(); node_list.print_count(15); cout << endl;

    cout << "4) Check of looping list:" << endl;
    cout << "before looping: " << is_looped(node_list) << endl;
    node_list.break_by_cycle();
    cout << "after: " << is_looped(node_list) << endl;
    cout << "for your check, ";
    node_list.print_count(15); cout << endl;

    cout << "5) Check of palindrome (by Deque):" << endl;
    string palindrome = "madam";
    string not_palindrome = "not madam";
    cout << "Word '" << palindrome << "' is palindrome: ";
    cout << is_palindrome(palindrome) << endl; 
    cout << "Word '" << not_palindrome << "' is palindrome: ";
    cout << is_palindrome(not_palindrome) << endl << endl;

    auto s1 = "abc"; auto s2 = "aIbIc";
    cout << "6) String '" << s1 << "' is source for '" << s2 << "': ";
    cout << is_source(s1, s2) << endl;
    s1 = "abc"; s2 = "_IbIc";
    cout << "string '" << s1 << "' is source for '" << s2 << "': ";
    cout << is_source(s1, s2) << endl << endl;

    NodeList l1, l2;
    list<int> s_l = {3, 4, 5, 7, 9};
    for (int n: s_l) {
        l1.push_back(n);
    }
    list<int> s_l2 = {1, 2, 6, 7, 8};
    for (int n: s_l2) {
        l2.push_back(n);
    }
    cout << "7) Merge 2 sorted node-list: " << endl;
    l1.print_all(); l2.print_all();
    merge2sorted(l1, l2);
    l1.print_all();

    return 0;
}