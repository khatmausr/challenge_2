#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define ALPHABET_SIZE 26

using namespace std;

struct Trie {
    Trie* nextC[ALPHABET_SIZE];
    bool endWord;
};

Trie* newNode() {
    Trie* t = new Trie;
    for (char i = 0; i < 26; ++i)
        t->nextC[i] = NULL;
    t->endWord = false;
    return t;
}

void put(Trie* root, string key) {
    Trie* curr = root;
    for (int i = 0; i < key.length(); ++i) {
        int index = key[i] - 'a';
        if (!curr->nextC[index])
            curr->nextC[index] = newNode();
        curr = curr->nextC[index];
    }
    curr->endWord = true;
}

Trie* createTrie(ifstream& dic) {
    Trie* root = newNode();
    string line;
    while (getline(dic, line))
        put(root, line);
    return root;
}

void search(vector<string>* v, Trie* root, bool* free, string letters, string str) {
    if (str.length() >= 3 && root->endWord)
        v->push_back(str);
    for (int i = 0; i < letters.length(); ++i) {
        if (free[i] && root->nextC[letters[i] - 'a']) {
            free[i] = false;
            str += letters[i];
            search(v, root->nextC[letters[i] - 'a'], free, letters, str);
            free[i] = true;
            str.erase(str.length() - 1, 1);
        }
    }
}

void wordGenerator(ofstream& fout, Trie* root, string letters) {
    vector<string> ans;
    bool* free = new bool[letters.length()];
    for (int i = 0; i < letters.length(); ++i)
        free[i] = true;

    for (int i = 0; i < letters.length(); ++i)
        search(&ans, root, free, letters, "");

    fout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i)
        fout << ans[i] << endl;

    delete[] free;
    free = NULL;
}

int main() {
    try {
        ifstream dic("Dic.txt");
        ifstream fin("input.txt");
        ofstream fout("output.txt");
        Trie* root = createTrie(dic);
        dic.close();
        string letters = "acep";
        wordGenerator(fout, root, letters);

        fin.close();
        fout.close();
    } catch (char* err) {
        cout << err << endl;
    }
    return 0;
}