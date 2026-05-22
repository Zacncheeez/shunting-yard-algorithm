#include <iostream>
#include <string>
#include <cctype>
using namespace std;

/* ============================
   LINKED LIST STACK (string)
   ============================ */
struct StackNode {
    string data;
    StackNode* next;
    StackNode(string d) : data(d), next(nullptr) {}
};

struct Stack {
    StackNode* top = nullptr; //Top of stack

    //Push a value onto the Stack
    void push(string v) {
        StackNode* n = new StackNode(v);
        n->next = top;
        top = n;
    }
    
    //Pop and return the top value
    string pop() {
        string v = top->data;
        StackNode* t = top;
        top = top->next;
        delete t;
        return v;
    }
    string peek() { return top ? top->data : ""; }
    bool empty() { return top == nullptr; }
};

/* ============================
   LINKED LIST QUEUE (string)
   ============================ */
struct QueueNode {
    string data;
    QueueNode* next;
    QueueNode(string d) : data(d), next(nullptr) {}
};

struct Queue {
    QueueNode* head = nullptr; //Front of queue
    QueueNode* tail = nullptr; //Back of queue
    
    // Add value to back of queue
    void enqueue(string v) {
        QueueNode* n = new QueueNode(v);
        if (!tail) head = tail = n;
        else tail->next = n, tail = n;
    }
    
    // Remove and return front value
    string dequeue() {
        string v = head->data;
        QueueNode* t = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete t;
        return v;
    }
    bool empty() { return head == nullptr; }
};

/* ============================
   BINARY TREE NODE
   ============================ */
struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string v) : value(v), left(nullptr), right(nullptr) {}
};

/* ============================
   SHUNTING YARD HELPERS
   ============================ */
int prec(string op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}
bool rightAssoc(string op) { return op == "^"; }

/* ============================
   SHUNTING YARD (INFIX → POSTFIX)
   ============================ */
Queue shuntingYard(string in) {
    Stack ops;
    Queue out;

    string tok;
    for (int i = 0; i <= in.size(); i++) {
        if (i == in.size() || in[i] == ' ') {
            if (tok != "") {
                if (isdigit(tok[0])) out.enqueue(tok);
                else if (tok == "(") ops.push(tok);
                else if (tok == ")") {
                    while (ops.peek() != "(") out.enqueue(ops.pop());
                    ops.pop();
                }
                else {
                    while (!ops.empty() &&
                           prec(ops.peek()) > 0 &&
                           ((!rightAssoc(tok) && prec(ops.peek()) >= prec(tok)) ||
                            ( rightAssoc(tok) && prec(ops.peek()) >  prec(tok))))
                        out.enqueue(ops.pop());
                    ops.push(tok);
                }
            }
            tok = "";
        } else tok += in[i];
    }

    while (!ops.empty()) out.enqueue(ops.pop());
    return out;
}

/* ============================
   STACK FOR TREE NODES
   ============================ */
struct TreeStackNode {
    TreeNode* data;
    TreeStackNode* next;
    TreeStackNode(TreeNode* d) : data(d), next(nullptr) {}
};

struct TreeStack {
    TreeStackNode* top = nullptr;

    void push(TreeNode* n) {
        TreeStackNode* t = new TreeStackNode(n);
        t->next = top;
        top = t;
    }
    TreeNode* pop() {
        TreeNode* v = top->data;
        TreeStackNode* t = top;
        top = top->next;
        delete t;
        return v;
    }
    bool empty() { return top == nullptr; }
};

/* ============================
   BUILD EXPRESSION TREE
   ============================ */
TreeNode* buildTree(Queue post) {
    TreeStack st;

    while (!post.empty()) {
        string t = post.dequeue();

        if (isdigit(t[0])) {
            st.push(new TreeNode(t));
        } else {
            TreeNode* r = st.pop();
            TreeNode* l = st.pop();
            TreeNode* op = new TreeNode(t);
            op->left = l;
            op->right = r;
            st.push(op);
        }
    }

    return st.pop();
}

/* ============================
   TREE TRAVERSALS
   ============================ */
void printPrefix(TreeNode* r) {
    if (!r) return;
    cout << r->value << " ";
    printPrefix(r->left);
    printPrefix(r->right);
}

void printInfix(TreeNode* r) {
    if (!r) return;
    if (r->left) cout << "( ";
    printInfix(r->left);
    cout << r->value << " ";
    printInfix(r->right);
    if (r->right) cout << ") ";
}

void printPostfix(TreeNode* r) {
    if (!r) return;
    printPostfix(r->left);
    printPostfix(r->right);
    cout << r->value << " ";
}

/* ============================
   MAIN
   ============================ */
int main() {
    cout << "Enter infix (space-separated):\n";
    string infix;
    getline(cin, infix);

    Queue postfix = shuntingYard(infix);

    // Build tree directly from postfix queue
    TreeNode* root = buildTree(postfix);

    cout << "\nPrefix: ";  printPrefix(root);
    cout << "\nInfix: ";   printInfix(root);
    cout << "\nPostfix: "; printPostfix(root);
    cout << "\n";
}
