#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <chrono>
#include <map>

struct Node {
    int id;
    std::vector<Node*> children;
    Node(int val) : id(val) {}
    bool addChild(Node* child) {
        if (children.size() >= 2) {
            std::cout << "Error: Node " << id << " already has 2 children\n";
            return false;
        }
        children.push_back(child);
        return true;
    }
};

void bfsTraversal(Node* root, int target) {
    if (root == nullptr) return;
    std::deque<Node*> dq;
    dq.push_back(root);

    std::cout << "BFS Traversal: ";
    while (!dq.empty()) {
        Node* current = dq.front();
        if (current->id == target) {
            std::cout << "found " << target << "\n";
            return;
        }
        dq.pop_front();
        for (Node* child : current->children) {
            if (child != nullptr) {
                dq.push_back(child);
            }
        }
    }
    std::cout << "not found " << target << "\n";
}

void buildMapFromTree(Node* root, std::map<int, Node*>& nodeMap) {
    if (root == nullptr) return;

    std::deque<Node*> dq;
    dq.push_back(root);

    while (!dq.empty()) {
        Node* current = dq.front();
        dq.pop_front();
        nodeMap[current->id] = current;
        for (Node* child : current->children) {
            if (child != nullptr) {
                dq.push_back(child);
            }
        }
    }
}

void searchInMap(const std::map<int, Node*>& nodeMap, int target) {
    std::cout << "Map Search: ";
    auto it = nodeMap.find(target);
    if (it != nodeMap.end()) {
        std::cout << "found " << target << "\n";
    } else {
        std::cout << "not found " << target << "\n";
    }
}

int main() {
    const int TOTAL_NODES = 1000000;
    std::cout << "Building tree with " << TOTAL_NODES << " nodes...\n";

    std::vector<Node*> nodes;
    nodes.reserve(TOTAL_NODES);

    for (int i = 1; i <= TOTAL_NODES; ++i) {
        nodes.push_back(new Node(i));
    }

    for (int i = 1; i < TOTAL_NODES; ++i) {
        int parentIdx = (i - 1) / 2;
        nodes[parentIdx]->addChild(nodes[i]);
    }

    Node* root = nodes[0];

    std::map<int, Node*> nodeMap;
    buildMapFromTree(root, nodeMap);

    int target = 999999;

    auto start = std::chrono::high_resolution_clock::now();
    bfsTraversal(root, target);
    auto end = std::chrono::high_resolution_clock::now();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double micros = nanos / 1000.0;
    double millis = nanos / 1000000.0;
    std::cout << "time BFS: " << nanos << " ns (" << micros << " us, " << millis << " ms)\n";

    auto startmap = std::chrono::high_resolution_clock::now();
    searchInMap(nodeMap, target);
    auto endmap = std::chrono::high_resolution_clock::now();
    auto nanosmap = std::chrono::duration_cast<std::chrono::nanoseconds>(endmap - startmap).count();
    double microsmap = nanosmap / 1000.0;
    double millismap = nanosmap / 1000000.0;
    std::cout << "time map: " << nanosmap << " ns (" << microsmap << " us, " << millismap << " ms)\n";

    return 0;
}
