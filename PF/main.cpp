#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Node {
    char label;
    Node* left;
    Node* right;
};

bool isOperator(char c) {
    return (c == '&' || c == '|' || c == '!');
}

Node* buildExpressionTree(string expression) {
    stack<Node*> nodeStack;
    for (int i = 0; i < expression.size(); i++) {
        char c = expression[i];
        if (!isOperator(c)) {
            Node* node = new Node;
            node->label = c;
            node->left = nullptr;
            node->right = nullptr;
            nodeStack.push(node);
        } else {
            Node* node = new Node;
            node->label = c;
            node->right = nodeStack.top();
            nodeStack.pop();
            if (c == '!') {
                node->left = nullptr;
            } else {
                node->left = nodeStack.top();
                nodeStack.pop();
            }
            nodeStack.push(node);
        }
    }
    return nodeStack.top();
}

bool evaluateExpressionTree(Node* root, bool values[]) {
    if (root == nullptr) {
        return false;
    }
    if (root->label == '0') {
        return false;
    }
    else if (root->label == '1') {
        return true;
    }
    else if (root->label == '&') {
        bool leftValue = evaluateExpressionTree(root->left, values);
        bool rightValue = evaluateExpressionTree(root->right, values);
        return leftValue && rightValue;
    }
    else if (root->label == '|') {
        bool leftValue = evaluateExpressionTree(root->left, values);
        bool rightValue = evaluateExpressionTree(root->right, values);
        return leftValue || rightValue;
    }
    else if (root->label == '!') {
        bool childValue = evaluateExpressionTree(root->left, values);
        return !childValue;
    }
    else {
        // Unknown label
        return false;
    }
}

int main() {
    string input;
    bool values[16];
    cout << "Ingrese una entrada de 16 bits binarios: ";
    cin >> input;
    if (input.size() != 16) {
        cout << "La entrada debe tener 16 bits." << endl;
        return 1;
    }
    for (int i = 0; i < 16; i++) {
        if (input[i] == '0') {
            values[i] = false;
        } else if (input[i] == '1') {
            values[i] = true;
        } else {
            cout << "La entrada debe contener sólo bits binarios (0 o 1)." << endl;
            return 1;
        }
    }
    Node* root = buildExpressionTree(input);
    bool result = evaluateExpressionTree(root, values);
    cout << "El resultado de la expresión es: " << result << endl;
    return 0;
}