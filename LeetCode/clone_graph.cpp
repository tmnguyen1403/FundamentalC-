#include <unordered_map>

class Solution {
public:
    std::unordered_map<int,Node*> cloned_neighbors;
    Node* cloneGraph(Node* node) {
        //create new node and new neighbors for the new node from the original node
        //for each neighbor of the newnode, perform the same process
        if (node == nullptr)
            return nullptr;
        Node * new_node = new Node(node->val);
        cloned_neighbors[node->val] = new_node;
        //cout << "node_val: " << node->val << endl;
        for (const auto& neighbor: node->neighbors) {
            auto iter = cloned_neighbors.find(neighbor->val);
            if (iter != cloned_neighbors.end())
                new_node->neighbors.push_back(iter->second);
            else {
                auto new_neighbor = cloneGraph(neighbor);
                new_node->neighbors.push_back(new_neighbor);
            }
        }
        return new_node;
    }
};