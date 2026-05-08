#include <iostream>


//Start code with what I need for later


int main()
{
    
    precedence = {
    '^': 3,
    '*': 2,
    '/': 2,
    '+': 1,
    '-': 1
}

# True = right associative (only ^)
right_assoc = {
    '^': True,
    '*': False,
    '/': False,
    '+': False,
    '-': False
}


    for token in postfix:
    if token is a number:
        node = new TreeNode(token)
        stack.push(node)

    else if token is an operator:
        right = stack.pop()
        left = stack.pop()
        node = new TreeNode(token)
        node.left = left
        node.right = right
        stack.push(node)

root = stack.pop()

}

