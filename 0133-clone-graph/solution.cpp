/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<int, Node*> newNodes;
        if (node == nullptr) return nullptr;
        int r = node->val;
        queue<Node*> q;
        q.push(node);
        newNodes[r] = new Node(r);
        while(!q.empty()) {
            Node* cur = q.front(); q.pop();
            cout << "cur " << cur->val << endl;
            if (newNodes.contains(cur->val) && !newNodes[cur->val]->neighbors.empty()) continue;
            cout << "first time" << endl;
            for(Node* neighbour : cur->neighbors) {
                cout << "neighbour " << neighbour->val << endl;
                if (!newNodes.contains(neighbour->val)) {
                    cout << "first time neighbour " << endl;
                    newNodes[neighbour->val]  = new Node(neighbour->val);
                    q.push(neighbour);
                } 
                newNodes[cur->val]->neighbors.push_back(newNodes[neighbour->val]);
            }
        }
        return newNodes[r];
    }
};
