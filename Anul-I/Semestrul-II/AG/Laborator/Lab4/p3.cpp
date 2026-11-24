#include <fstream>
#include <vector>
#include <string>
#include <map>
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

void get_codes(Node* root, string code, map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = code;
    }
    get_codes(root->left, code + "0", codes);
    get_codes(root->right, code + "1", codes);
}

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    string text;
    char ch;
    while (fin.get(ch)) {
        text += ch;
    }
    if (text.empty()) return 0;
    map<char, int> freqs;
    for (char c : text) {
        freqs[c]++;
    }
    fout << freqs.size() << "\n";
    for (auto const& [c, f] : freqs) {
        fout << c << " " << f << "\n";
    }
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto const& [c, f] : freqs) {
        pq.push(new Node(f, c, c));
    }
    if (pq.size() == 1) {
        fout << string(text.length(), '0') << "\n";
        return 0;
    }
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        char min_c = min(left->min_char, right->min_char);
        pq.push(new Node(left->freq + right->freq, min_c, '\0', left, right));
    }
    map<char, string> codes;
    get_codes(pq.top(), "", codes);
    for (char c : text) {
        fout << codes[c];
    }
    fout << "\n";
    return 0;
}
