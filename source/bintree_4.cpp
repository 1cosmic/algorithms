#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <ranges>
#include <algorithm>

using namespace std;


template<typename T>
void print_array(vector<T> array);  // forward declaration.

template<typename T>
void print_array(vector<T> array) {
    cout << "[";
    for (auto n : array)
        cout << n << ' ';
    cout << "\b]" << endl;
}


class TreeNode {
    public:
        int v; TreeNode *l, *r;

        TreeNode (int val = -1, TreeNode *left = nullptr, TreeNode *right = nullptr) {
            v = val;
            l = left; r = right;
        };


        bool search_BFS(bool is_symmetric = false) {
            vector<int> res = {};
            deque<int> symmetric = {};
            queue<TreeNode *> breadth;

            int level = 1;
            int i = level;
            breadth.push(this);

            cout << "tree by levels: \n0: ";
            while (!breadth.empty()) {
                i--;

                TreeNode *root = breadth.front();
                if (root) {
                    TreeNode *l = root->l; if (l) breadth.push(l);
                    TreeNode *r = root->r; if (r) breadth.push(r);
                    cout << root->v  << ", ";
                    res.push_back(root->v);
                    if (is_symmetric) symmetric.push_back(root->v);
                }
                breadth.pop();

                if (i <= 0 and !breadth.empty()) {
                    cout << "\b\b \n";
                    cout << level << ": ";
                    i = pow(2, level);
                    level += 1;

                    if (is_symmetric) 
                        while (symmetric.size() > 1) {
                            if (symmetric.front() == symmetric.back()) {
                                symmetric.pop_front(); symmetric.pop_back();
                            }
                            else is_symmetric = false; break;
                            }
                        symmetric.pop_front();
                };
            }
            cout << endl;

            return is_symmetric;
        };
};


TreeNode* build(vector<int> arr, int i = 0) {
    if (i > arr.size() -1) return nullptr;
    if (arr[i] == -1) return nullptr;

    TreeNode* root = new TreeNode(arr[i]);
    root->v = arr[i];
    root->l = build(arr, 2*i + 1);
    root->r = build(arr, 2*i + 2);

    return root;
};


int get_min_h(TreeNode *root) {
    if (!root) return 0;

    if (root->l and root->r)
        return 1 + min(get_min_h(root->l), get_min_h(root->r));
    else if (!root->l and !root->r) return 1;

    if (root->l) return 1 + get_min_h(root->l);
    if (root->r) return 1 + get_min_h(root->r);
};


int get_min_h_2(TreeNode *root, int count = 0) {
    if (!root) return count;

    count = count + 1;

    // TODO: Проверь метод разделяющихся указателей: если дерево вырождено и один из указтелей > 0 - слушаем его.
    // !!! Рекурсировать счётчики по нодам (распределить их по каналам) и собрать воедино, затем выбрать минимальный!
    
    return min(get_min_h_2(root->l, count), get_min_h_2(root->r, count));
};


void testDegenerateTrees() {
    cout << "\n=== Degenerate Trees Tests ===" << endl;
    
    // Тест 5: Вырожденное влево (все узлы только слева)
    //   1
    //  /
    // 2
    ///
    //3
    TreeNode* root5 = new TreeNode(1, 
        new TreeNode(2, 
            new TreeNode(3), 
            nullptr
        ), 
        nullptr
    );
    int result5 = get_min_h_2(root5);
    cout << "Test 5 - Left degenerate: " << (result5 == 3 ? "PASS" : "FAIL") 
         << " (expected: 3, got: " << result5 << ")" << endl;
    delete root5->l->l;
    delete root5->l;
    delete root5;

    // Тест 6: Вырожденное вправо (все узлы только справа)
    //   1
    //    \
    //     2
    //      \
    //       3
    TreeNode* root6 = new TreeNode(1, 
        nullptr, 
        new TreeNode(2, 
            nullptr, 
            new TreeNode(3)
        )
    );
    int result6 = get_min_h_2(root6);
    cout << "Test 6 - Right degenerate: " << (result6 == 3 ? "PASS" : "FAIL") 
         << " (expected: 3, got: " << result6 << ")" << endl;
    delete root6->r->r;
    delete root6->r;
    delete root6;

    // Тест 7: Смешанное вырожденное (разная глубина ветвей)
    //       1
    //      / \
    //     2   3
    //    /     \
    //   4       5
    //  /
    // 6
    TreeNode* root7 = new TreeNode(1,
        new TreeNode(2,
            new TreeNode(4,
                new TreeNode(6),
                nullptr
            ),
            nullptr
        ),
        new TreeNode(3,
            nullptr,
            new TreeNode(5)
        )
    );
    int result7 = get_min_h_2(root7);
    cout << "Test 7 - Mixed depths: " << (result7 == 3 ? "PASS" : "FAIL") 
         << " (expected: 3, got: " << result7 << ")" << endl;
    delete root7->l->l->l;
    delete root7->l->l;
    delete root7->l;
    delete root7->r->r;
    delete root7->r;
    delete root7;
}


int multi2extreme(vector<int> tree) {
    if (tree.size() <= 1) return -1;

    int min = 0, max = 0;
    int l = 0, r = 0, i = 0;

    while (r < tree.size()) {

        if (tree[l] > -1) {
            min = tree[l];
        }
        if (tree[r] > -1) {
            max = tree[r];
        }
        cout << "m:" << min << " | max: " << max << endl;
        cout << "l:" << l << " | r: " << r << endl;

        l = l * 2 + 1;
        r = r * 2 + 2;

        i++;
    }

    return min * max;
}


bool is_identity(TreeNode *left, TreeNode *right) {
    if (!left and !right) return true;
    if (!left or !right) return false;
    if (left->v != right->v) return false;
    
    return (is_identity(left->l, right->l) && is_identity(left->r, right->r));
}


int main() {
    cout << "HOMEWORK #4: binary trees and its algorithms." << endl << endl;
    vector<int> data2tree = {8, 9, 11, 7, 16, 3, 1};

    cout << endl << "1) Revert binary tree off array." << endl;
    cout << "arr: "; print_array(data2tree);
    TreeNode *tree1 = build(data2tree, 0);
    auto symmetric = tree1->search_BFS(true);
    cout << "is symmetric: " << symmetric << endl;

    cout << endl << "2) Check only 'is symmetric?'" << endl;
    vector<int> symmetric2tree = {1, 2, 2, 3, 4, 4, 3};
    auto *tree2 = build(symmetric2tree, 0);
    symmetric = tree2->search_BFS(true);
    cout << "is symmetric: " << symmetric << endl;

    cout << endl << "3) What min h of tree?" << endl;
    data2tree = {11, 8, 18, 2, 9, 6, -1, 7, -1, -1, 9, -1, -1};
    auto *tree3 = build(data2tree); tree3->search_BFS();
    cout << "Min: " << get_min_h(tree3);
    testDegenerateTrees();

    cout << endl << "4) min(tree) * max(tree) of tree." << endl << "arr:";
    vector<int> extreme_tree = {16, 12, 18, 11, 15, 17, 21, -1, -1, -1, -1, -1, -1, 19, 24};
    print_array(extreme_tree);
    int r = multi2extreme(extreme_tree);
    cout << "res: " << r << endl;

    cout << endl << "5) Is identity 2 tree:" << endl;
    cout << "1: "; tree3->search_BFS();  cout << endl;
    cout << "2: "; tree3->search_BFS();
    cout << "res: " << is_identity(tree3, tree3);


    cout << endl << endl;
    cout << "Homeworks was made by Michael Kolobakhin." << endl;
    return 0;
}