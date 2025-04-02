#include <iostream>
#include <string>
 
using namespace std;
 
class Node {
  public:
    char data;
    Node* left;
    Node* right;
    Node(char data) {
      this->data = data;
      this->left = NULL;
      this->right = NULL;
    }
};

Node* buildTree(std::string preorder, std::string inorder) {
  if (preorder.length() == 0) return NULL;

  char data = preorder[0];
  Node* root = new Node(data);

  int index = -1;
  for (int i = 0; i < inorder.length(); i++) {
    if (inorder[i] == data) {
      index = i;
      break;
    }
  }

  root->left = buildTree(preorder.substr(1, index), inorder.substr(0, index));
  root->right = buildTree(preorder.substr(1 + index), inorder.substr(index + 1));

  return root;
}

std::string postorderWalk(Node* root) {
  if (root == NULL) return "";

  return postorderWalk(root->left) + postorderWalk(root->right) + root->data;
}

int main() {
  std::string preorder, inorder, postorder;

  int trees = 0;
  std::cin >> trees;
  for (int i = 0; i < trees; i++) {
    int treeSize = 0;

    std::cin >> treeSize;
    std::cin >> preorder;
    std::cin >> inorder;

    Node* tree = buildTree(preorder, inorder);
    postorder = postorderWalk(tree);

    std::cout << postorder << std::endl;
  }

  return 0;
}