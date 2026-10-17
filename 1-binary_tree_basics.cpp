#include <bits/stdc++.h>

using namespace std;

class Node {
    public: int data;
    Node * left;
    Node * right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// 1. Construct tree from preorder serialization (-1 = NULL)
Node * make_tree(const vector < int > & tree, int & idx) {
    idx++;

    if (idx >= (int) tree.size() || tree[idx] == -1) {
        return NULL;
    }

    Node * root = new Node(tree[idx]);
    root -> left = make_tree(tree, idx);
    root -> right = make_tree(tree, idx);

    return root;
}

// 2. Preorder Traversal: Root, Left, Right
void preorder(Node * root) {
    if (root == NULL) return;

    cout << root -> data << " ";
    preorder(root -> left);
    preorder(root -> right);
}

// 3. Inorder Traversal: Left, Root, Right
void inorder(Node * root) {
    if (root == NULL) return;

    inorder(root -> left);
    cout << root -> data << " ";
    inorder(root -> right);
}

// 4. Postorder Traversal: Left, Right, Root
void postorder(Node * root) {
    if (root == NULL) return;

    postorder(root -> left);
    postorder(root -> right);
    cout << root -> data << " ";
}

// 5. Level Order Traversal
void level_order(Node * root) {
    if (root == NULL) return;

    queue < Node * > q;
    q.push(root);

    while (!q.empty()) {
        Node * curr = q.front();
        q.pop();

        cout << curr -> data << " ";

        if (curr -> left) q.push(curr -> left);
        if (curr -> right) q.push(curr -> right);
    }
}

// 6. Level Order Traversal, each level on a new line
void level_order_endl(Node * root) {
    if (root == NULL) return;

    queue < Node * > q;
    q.push(root);

    while (!q.empty()) {
        int level_size = q.size();

        for (int i = 0; i < level_size; i++) {
            Node * curr = q.front();
            q.pop();

            cout << curr -> data << " ";

            if (curr -> left) q.push(curr -> left);
            if (curr -> right) q.push(curr -> right);
        }

        cout << endl;
    }
}

// 7. Height of the Tree (number of nodes on longest path)
int tree_height(Node * root) {
    if (root == NULL) return 0;

    return 1 + max(
        tree_height(root -> left),
        tree_height(root -> right)
    );
}

// 8. Total Number of Nodes
int number_of_nodes(Node * root) {
    if (root == NULL) return 0;

    return 1 + number_of_nodes(root -> left) +
        number_of_nodes(root -> right);
}

// 9. Sum of All Nodes
int sum_of_nodes(Node * root) {
    if (root == NULL) return 0;

    return root -> data +
        sum_of_nodes(root -> left) +
        sum_of_nodes(root -> right);
}

// 10. Check Whether Two Trees Are Identical
bool is_identical(Node * root1, Node * root2) {
    if (root1 == NULL || root2 == NULL) {
        return root1 == root2;
    }

    return root1 -> data == root2 -> data &&
        is_identical(root1 -> left, root2 -> left) &&
        is_identical(root1 -> right, root2 -> right);
}

// 11. Check Whether root2 Is a Subtree of root1
bool substree(Node * root1, Node * root2) {
    if (root2 == NULL) return true;
    if (root1 == NULL) return false;

    if (is_identical(root1, root2)) return true;

    return substree(root1 -> left, root2) ||
        substree(root1 -> right, root2);
}

// 12. Diameter in O(n), measured in edges
int diameter_helper(Node * root, int & diameter) {
    if (root == NULL) return 0;

    int left_height = diameter_helper(root -> left, diameter);
    int right_height = diameter_helper(root -> right, diameter);

    diameter = max(diameter, left_height + right_height);

    return 1 + max(left_height, right_height);
}

int diameter_of_tree(Node * root) {
    int diameter = 0;
    diameter_helper(root, diameter);
    return diameter;
}

// 13. Top View
void top_view_tree(Node * root) {
    if (root == NULL) return;

    queue < pair < Node * , int >> q;
    map < int, int > m;

    q.push({
        root,
        0
    });

    while (!q.empty()) {
        auto curr_pair = q.front();
        q.pop();

        Node * curr = curr_pair.first;
        int hd = curr_pair.second;

        if (m.find(hd) == m.end()) {
            m[hd] = curr -> data;
        }

        if (curr -> left) q.push({
            curr -> left,
            hd - 1
        });
        if (curr -> right) q.push({
            curr -> right,
            hd + 1
        });
    }

    for (auto it: m) cout << it.second << " ";
    cout << endl;
}

// 14. Bottom View
void bottom_view_tree(Node * root) {
    if (root == NULL) return;

    queue < pair < Node * , int >> q;
    map < int, int > m;

    q.push({
        root,
        0
    });

    while (!q.empty()) {
        auto curr_pair = q.front();
        q.pop();

        Node * curr = curr_pair.first;
        int hd = curr_pair.second;

        m[hd] = curr -> data;

        if (curr -> left) q.push({
            curr -> left,
            hd - 1
        });
        if (curr -> right) q.push({
            curr -> right,
            hd + 1
        });
    }

    for (auto it: m) cout << it.second << " ";
    cout << endl;
}

// 15. Print Nodes at Kth Level (root is level 1)
void nodes_on_kth_level(Node * root, int k) {
    if (root == NULL || k <= 0) return;

    if (k == 1) {
        cout << root -> data << " ";
        return;
    }

    nodes_on_kth_level(root -> left, k - 1);
    nodes_on_kth_level(root -> right, k - 1);
}

// 16. Check Whether a Value Exists in the Tree
bool contains(Node * root, int val) {
    if (root == NULL) return false;

    if (root -> data == val) return true;

    return contains(root -> left, val) ||
        contains(root -> right, val);
}

// 17. Lowest Common Ancestor
Node * lca(Node * root, int p, int q) {
    if (root == NULL) return NULL;

    if (root -> data == p || root -> data == q) {
        return root;
    }

    Node * left_lca = lca(root -> left, p, q);
    Node * right_lca = lca(root -> right, p, q);

    if (left_lca != NULL && right_lca != NULL) {
        return root;
    }

    return (left_lca != NULL) ? left_lca : right_lca;
}

Node * lowest_common_ancestor(Node * root, int p, int q) {
    // Ensure both values exist in the tree.
    if (!contains(root, p) || !contains(root, q)) {
        return NULL;
    }

    return lca(root, p, q);
}

// 18. Find a Value in an Inorder Array
int search(const vector < int > & in, int left, int right, int val) {
    for (int i = left; i <= right; i++) {
        if (in [i] == val) return i;
    }

    return -1;
}

// 19. Construct Tree from Preorder and Inorder
Node * make_tree_preorder_inorder(const vector < int > & pre, const vector < int > & in, int & idx,int left,int right) {
    if (left > right) return NULL;
    if (idx >= (int) pre.size()) return NULL;

    int root_index = search(in, left, right, pre[idx]);

    if (root_index == -1) return NULL;

    Node * root = new Node(pre[idx]);
    idx++;

    root -> left = make_tree_preorder_inorder(
        pre, in, idx, left, root_index - 1
    );

    root -> right = make_tree_preorder_inorder(
        pre, in, idx, root_index + 1, right
    );

    return root;
}

// 20. Convert Each Node to Its Original Subtree Sum
// This modifies the original tree.
int sum_tree(Node * root) {
    if (root == NULL) return 0;

    int left_sum = sum_tree(root -> left);
    int right_sum = sum_tree(root -> right);

    root -> data = root -> data + left_sum + right_sum;

    return root -> data;
}

// 21. Print All Root-to-Leaf Paths
void binary_tree_path(Node * root,vector < string > & path,string curr_path) {
    if (root == NULL) return;

    if (root -> left == NULL && root -> right == NULL) {
        path.push_back(curr_path);
        return;
    }

    if (root -> left) {
        binary_tree_path(
            root -> left,
            path,
            curr_path + "->" + to_string(root -> left -> data)
        );
    }

    if (root -> right) {
        binary_tree_path(
            root -> right,
            path,
            curr_path + "->" + to_string(root -> right -> data)
        );
    }
}
// 22. maximum width of the binary tree 
int max_width = 0;
int maximum_width_tree(Node * root) {
    queue < pair < Node * , long long >> q;
    q.push({root,0});
    while (!q.empty()) {
        int curr_level_size = q.size();
        int st = q.front().second;
        int end = q.back().second;
        max_width = max(max_width, end - st + 1);
        for (int i = 0; i < curr_level_size; i++) {
            Node * curr = q.front().first;
            q.pop();
            if (curr -> left != NULL) {
                q.push({curr -> left,2 * i + 1});
            }
            if (curr -> right != NULL) {
                q.push({curr -> right,2 * i + 2});
            }
        }
    }
    return max_width;
}
//morris inorder traversal
vector < int > morris_inorder(Node * root) {
    vector < int > ans;
    Node * curr = root;
    while (curr != NULL) {
        if (curr -> left == NULL) {
            ans.push_back(curr -> data);
            curr = curr -> right;
        } else {
            Node * IP = curr -> left;
            while (IP -> right != NULL && IP -> right != curr) {
                IP = IP -> right;
            }
            if (IP -> right == NULL) {
                IP -> right = curr;
                curr = curr -> left;
            } else {
                IP -> right = NULL;
                ans.push_back(curr -> data);
                curr = curr -> right;
            }
        }
    }
    return ans;
}
Node* NR=NULL;
void flattern_binary_tree(Node* root){
    if(root == NULL){
        return;
    }
    flattern_binary_tree(root->right);
    flattern_binary_tree(root->left);
    root->left=NULL;
    root->right=NR;
    NR=root;
}
int main() {
    vector < int > tree1 = {1,2,3,4,-1,-1,5,-1,-1,-1,6,7,-1,-1,8,-1,-1};

    int idx1 = -1;
    Node * root1 = make_tree(tree1, idx1);

    vector < int > tree2 = {6,7,-1,-1,8,-1,-1};

    int idx2 = -1;
    Node * root2 = make_tree(tree2, idx2);

    cout << "Preorder Traversal:\n";
    preorder(root1);
    cout << "\n\n";

    cout << "Inorder Traversal:\n";
    inorder(root1);
    cout << "\n\n";

    cout << "Postorder Traversal:\n";
    postorder(root1);
    cout << "\n\n";

    cout << "Simple Level Order:\n";
    level_order(root1);
    cout << "\n\n";

    cout << "Level Order with New Lines:\n";
    level_order_endl(root1);
    cout << "\n";

    cout << "Height of Tree: " <<
        tree_height(root1) << "\n";

    cout << "Number of Nodes: " <<
        number_of_nodes(root1) << "\n";

    cout << "Sum of Nodes: " <<
        sum_of_nodes(root1) << "\n";

    cout << "Identical Trees: " <<
        is_identical(root1, root2) << "\n";

    cout << "Is Subtree: " <<
        substree(root1, root2) << "\n";

    cout << "Diameter (edges): " <<
        diameter_of_tree(root1) << "\n";

    cout << "Top View: ";
    top_view_tree(root1);

    cout << "Bottom View: ";
    bottom_view_tree(root1);

    cout << "Nodes at Level 3: ";
    nodes_on_kth_level(root1, 3);
    cout << "\n";

    Node * lca_node = lowest_common_ancestor(root1, 4, 8);

    cout << "Lowest Common Ancestor: ";
    if (lca_node != NULL) {
        cout << lca_node -> data << "\n";
    } else {
        cout << "Not found\n";
    }

    vector < int > preorder_arr = {3,9,20,15,7};
    vector < int > inorder_arr = {9,3,15,20,7};

    int pre_idx = 0;

    Node * root = make_tree_preorder_inorder(
        preorder_arr,
        inorder_arr,
        pre_idx,
        0,
        (int) inorder_arr.size() - 1
    );

    cout << "Root from Preorder and Inorder: ";
    if (root != NULL) cout << root -> data;
    cout << "\n";

    vector < string > path;
    binary_tree_path(root1, path, to_string(root1 -> data));

    cout << "Binary Tree Paths:\n";
    for (const string & p: path) {
        cout << p << "\n";
    }

    cout << "Total Sum after Subtree-Sum Transformation: " <<
        sum_tree(root2) << "\n";

    cout << " Maximum with of the binary tree at leaf nodes :- " << maximum_width_tree(root1) << endl;

    vector < int > ans = morris_inorder(root1);
    cout << "Morris inorder traversal :-" << endl;
    for (auto it: ans) {
        cout << it << " ";
    }
    cout << endl;
    
    flattern_binary_tree(root1);
    cout<<"flattern_binary_tree :-" <<endl;
    level_order_endl(root1);
    
    return 0;
}