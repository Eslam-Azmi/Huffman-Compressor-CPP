#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>

using namespace std;

void compress();
void decompress();

struct Node{
    int freq;
    char character;
    int id;
    Node* left;
    Node* right;

    Node (char character, int frequency, int id){
        this->character = character;
        freq = frequency;
        this->id = id;
        left = right = nullptr;
    }

    Node (int frequency, int id, Node* l, Node* r){
        character = '\0';
        freq = frequency;
        this->id = id;
        left = l;
        right = r;
    }

    bool isLeaf() {
        return (left == nullptr && right == nullptr);
    }
};

struct Compare {
    bool operator()(Node* a, Node* b){
        if (a->freq != b->freq) return a->freq > b->freq;
        return a->id > b->id;  
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

Node* buildTree(unordered_map<char, int>& counts){
    priority_queue<Node*, vector<Node*>, Compare> pq; 
    int nodeID = 1000;

    for (auto& pair : counts){
        Node* n = new Node(pair.first, pair.second, (int)(unsigned char)pair.first);
        pq.push(n);
    }

    while (pq.size() > 1){
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* parent = new Node(left->freq + right->freq, nodeID++, left, right);
        pq.push(parent);
    }
    return pq.top();
}

int main(){
    cout << "1. Compress \n2. Decompress\n Choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1){
        compress();
    }else if (choice == 2){
        decompress();
    }

    return 0; 
}

void compress(){
    // Reading the file and counting the frequency for each character
    string filename;

    cout << "Filename : ";
    getline(cin, filename);

    ifstream inFile;
    inFile.open(filename, ios::binary);

    if (inFile.fail()){
        cout << "No exist for this file!" << endl;
        return; 
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
    // Nodes for every unique character and putting them in priority queue(min)
    
    Node* root = buildTree(counts);

    // auto printTree = [&](auto self, Node* root, int indent) -> void {
    //     if (root == nullptr) return;
        
    //     self(self, root->left, indent + 1);
    //     cout << string(indent * 4, ' ') << root->freq << endl;
    //     self(self, root->right, indent + 1);
    // };
    // printTree(printTree, pq.top(), 0);

    // Making the Huffman tree for assigning code for every character 
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

    // Reseting the cursor for the target file
    inFile.clear();
    inFile.seekg(0, ios::beg);

    // Encoding every charater to thier assigned bits (comprission)
    string encodedString;
    while (inFile.get(c)){
        encodedString += Huffman[c];
    }

    ofstream outFile("compressed.huff", ios::binary);

    // Metadata for the decompressor (unique characters - frequincy for each char - length of bits)
    int mapSize = counts.size();
    outFile.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));

    for (auto const& [ch, freq] : counts){
        outFile.put(ch);
        outFile.write(reinterpret_cast<const char*>(&freq), sizeof(freq));
    }

    int totalBits = encodedString.length();
    outFile.write(reinterpret_cast<const char*>(&totalBits), sizeof(totalBits));

    // the body of the binary code with the padding 
    int bitCounter = 0;
    unsigned char byte = 0;
    for (char c : encodedString){
        bitCounter++;
        byte <<= 1; // making room for the next bit 
        if (c == '1') byte += 1;
        if (bitCounter == 8){
            outFile.put(byte);
            bitCounter = 0;
            byte = 0;
        }
    }

    if (bitCounter > 0){
        byte <<= (8 - bitCounter);
        outFile.put(byte);
    }
}

void decompress(){
    ifstream inFile("compressed.huff", ios::binary);
    
    int mapSize; 
    inFile.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));

    unordered_map<char, int> counts;
    for (int i = 0; i < mapSize; i++){
        char c = inFile.get();
        int freq;

        inFile.read(reinterpret_cast<char*>(&freq), sizeof(freq));
        counts[c] = freq;
    }

    int totalBits;
    inFile.read(reinterpret_cast<char*>(&totalBits), sizeof(totalBits));
    
    Node* root = buildTree(counts);

    ofstream outFile("decompressed.txt", ios::binary);

    Node* current = root; 
    int bitRead = 0;
    unsigned char byte;

    while (inFile.read(reinterpret_cast<char*>(&byte), 1)){
        for (int i = 7; i >= 0; i--){
            if (bitRead >= totalBits) break;
            if (((byte >> i) & 1) == 1){
                current = current->right;
            }else{
                current = current->left;
            }
            if (current->isLeaf()){
                outFile.put(current->character);
                current = root;
            }
            bitRead++;
        }
    }
}