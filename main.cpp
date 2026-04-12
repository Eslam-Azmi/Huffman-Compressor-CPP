#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>

using namespace std;

struct Node{
    int freq;
    char character;
    Node* left;
    Node* right;

    Node (char character, int frequency){
        this->character = character;
        freq = frequency;
        left = right = nullptr;
    }

    Node (int frequency, Node* l, Node* r){
        character = '\0';
        freq = frequency;
        left = l;
        right = r;
    }

    bool isLeaf() {
        return (left == nullptr && right == nullptr);
    }
};

struct Compare {
    bool operator()(Node* a, Node* b){
        return a->freq > b->freq;  
    }
};

void generateHuffman(Node* root, string bits, unordered_map<char, string>& Huffman){
    if (root == nullptr) return;

    if (root->isLeaf()){
        Huffman[root->character] = bits;
        return;
    }
    
    generateHuffman(root->left, bits + "0", Huffman);
    generateHuffman(root->right, bits + "1", Huffman);
}

int main(){
    string filename;

    cout << "Filename : ";
    getline(cin, filename);

    ifstream inFile;
    inFile.open(filename);

    if (inFile.fail()){
        cout << "No exist for this file!" << endl;
        return 1; 
    }

    char c;
    unordered_map<char, int> counts;
    while (inFile.get(c)){
        counts[c]++;
    }

    for (auto& pair : counts) {
        string display;
        if (pair.first == ' ') display = "Space";
        else if (pair.first == '\n') display = "Newline";
        else if (pair.first == '\t') display = "Tab";
        else display = string(1, pair.first);

        cout << display << " : " << pair.second << endl;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq; 

    for (auto& pair : counts){
        Node* n = new Node(pair.first, pair.second);
        pq.push(n);
    }

    Node* root;
    while (pq.size() > 1){
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node(left->freq + right->freq, left, right);
        pq.push(parent);
    }
    root = pq.top();

    // auto printTree = [&](auto self, Node* root, int indent) -> void {
    //     if (root == nullptr) return;
        
    //     self(self, root->left, indent + 1);
    //     cout << string(indent * 4, ' ') << root->freq << endl;
    //     self(self, root->right, indent + 1);
    // };
    // printTree(printTree, pq.top(), 0);

    unordered_map<char, string> Huffman;

    generateHuffman(root, "", Huffman);

    cout << "Huffman : " << endl;
    for (auto& pair : Huffman) {
        string display;
        if (pair.first == ' ') display = "Space";
        else if (pair.first == '\n') display = "Newline";
        else display = string(1, pair.first);
        
        cout << display << " : " << pair.second << endl;
    }

    inFile.clear();
    return 0; 
}