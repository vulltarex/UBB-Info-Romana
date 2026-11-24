#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    int freq;
    char min_char;
    char ch;
    Node* left;
    Node* right;
    Node(int f, char mc, char c, Node* l = nullptr, Node* r = nullptr) : freq(f), min_char(mc), ch(c), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        if (a->freq != b->freq) return a->freq > b->freq;
        return a->min_char > b->min_char;
    }
};

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    string line;
    if (!getline(fin, line)) return 0;
    int n = stoi(line);
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < n; ++i) {
        getline(fin, line);
        char ch = line[0];
        int freq = stoi(line.substr(2));
        pq.push(new Node(freq, ch, ch));
    }
    string encoded;
    getline(fin, encoded);
    if (pq.size() == 1) {
        Node* root = pq.top();
        for (char c : encoded) {
            fout << root->ch;
        }
        return 0;
    }
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        char min_c = min(left->min_char, right->min_char);
        pq.push(new Node(left->freq + right->freq, min_c, '\0', left, right));
    }
    Node* root = pq.top();
    Node* curr = root;
    for (char bit : encoded) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;
        if (!curr->left && !curr->right) {
            fout << curr->ch;
            curr = root;
        }
    }
    return 0;
}
