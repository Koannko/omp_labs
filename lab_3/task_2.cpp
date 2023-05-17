#include <vector>
#include <iostream>
using namespace std;
#include <omp.h>

struct Node {
  int number;
  int data;
  vector<Node*> children;
};

void assignData(Node* node, int level) {
  node->data = level;
  for (auto child : node->children) {
    assignData(child, level + 1);
  }
}

void assignDataParallel(Node* node, int level) {
  #pragma omp task
  {
    assignData(node, level);
  }
  #pragma omp taskwait
}

void printData(Node* node) {
  cout << "Node " << node->number << ": data = " << node->data << endl;
  for (auto child : node->children) {
    printData(child);
  }
}

int main() {
  Node* root = new Node{0};
  root->children.push_back(new Node{1});
  root->children.push_back(new Node{2});
  root->children.push_back(new Node{3});
  root->children[2]->children.push_back(new Node{4});
  root->children[2]->children.push_back(new Node{5});
  root->children[2]->children[1]->children.push_back(new Node{6});
  root->children[2]->children[1]->children.push_back(new Node{7});
  root->children[2]->children[1]->children.push_back(new Node{8});
  root->children[2]->children[1]->children[2]->children.push_back(new Node{9});

    #pragma omp parallel
    {
        #pragma omp single
        {
            assignDataParallel(root, 0);
        }
    }

    printData(root);

    return 0;
}
