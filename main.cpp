#include <iostream>
#include <stack>
#include <map>
#include <string>

struct TreeNode {
    std::string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(std::string v) : value(v), left(nullptr), right(nullptr) {}
};

int main() 
{
    // operator precedence
    std::map<char, int> precedence = {
        {'^', 3},
        {'*', 2},
        {'/', 2},
        {'+', 1},
        {'-', 1}
    };

    // right associativity
    std::map<char, bool> right_assoc = {
        {'^', true},
        {'*', false},
        {'/', false},
        {'+', false},
        {'-', false}
    };

    // placeholder: your postfix expression goes here
    std::string postfix = "";  

    std::stack<TreeNode*> stack;

    // loop through postfix tokens
    for (char token : postfix)
    {
        if (isdigit(token)) {
            TreeNode* node = new TreeNode(std::string(1, token));
            stack.push(node);
        }
        else { // operator
            TreeNode* right = stack.top(); stack.pop();
            TreeNode* left  = stack.top(); stack.pop();

            TreeNode* node = new TreeNode(std::string(1, token));
            node->left = left;
            node->right = right;

            stack.push(node);
        }
    }

    TreeNode* root = nullptr;
    if (!stack.empty())
        root = stack.top();

    return 0;
}
