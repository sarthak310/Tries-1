//time: O(n)
//space: O(n)
class Solution {
    class TrieNode {
    public:
        vector<TrieNode*> next;
        bool isWord;
        TrieNode() {
            isWord = false;
            next.resize(26);
        }
    };
    TrieNode* root;
    void makeTrie(vector<string>& dictionary) {
        for(string s : dictionary) {
            TrieNode* curr = root;
            for(int i = 0; i < s.length(); i++) {
                char c = s[i];
                if(curr -> next[c-'a'] == NULL)
                curr -> next[c-'a'] = new TrieNode();
                curr = curr -> next[c-'a'];
            }
            curr -> isWord = true;
        }
    }
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        root = new TrieNode();
        makeTrie(dictionary);
        string result = "";
        TrieNode* curr = root;
        string word = "";
        for(int i = 0; i < sentence.length(); i++) { // this is complex...should have just split the string into array of words - see editorial below
            cout<<"curr: "<<sentence[i]<<endl;
            if(sentence[i] == ' ') {
                result += word + " ";
                word = "";
                curr = root;
            }
            else {
                if(curr -> next[sentence[i] - 'a'] == NULL) {
                    result += word;
                    word = "";
                    curr = root;
                    while(sentence[i] != ' ' && i < sentence.length()) {
                        result += sentence[i];
                        i++;
                    }
                    if(sentence[i] == ' ') result += " ";
                }
                else {
                    word += sentence[i];
                    curr = curr -> next[sentence[i] - 'a'];
                    if(curr -> isWord == true) {
                        cout<<sentence[i]<<endl;
                        result += word;
                        word = "";
                        curr = root;
                        while(sentence[i] != ' ' && i < sentence.length()) {
                            i++;
                        }
                        if(sentence[i] == ' ') result += " ";
                        cout<<result<<endl;
                    }
                }
            }
        }
        return result += word;
    }
};

//editorial
/*
class TrieNode {
public:
    bool isEnd;
    vector<TrieNode*> children;

    TrieNode() : children(26, nullptr) { isEnd = false; }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children[c - 'a'] == nullptr) {
                current->children[c - 'a'] = new TrieNode();
            }
            current = current->children[c - 'a'];
        }
        current->isEnd = true;
    }

    // Find the shortest root of the word in the trie
    string shortestRoot(string word) {
        TrieNode* current = root;
        for (int i = 0; i < word.length(); ++i) {
            char c = word[i];
            if (current->children[c - 'a'] == nullptr) {
                // There is not a corresponding root in the trie
                return word;
            }
            current = current->children[c - 'a'];
            if (current->isEnd) {
                return word.substr(0, i + 1);
            }
        }
        // There is not a corresponding root in the trie
        return word;
    }
};

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        istringstream sStream(sentence);

        Trie dictTrie;
        for (string word : dictionary) {
            dictTrie.insert(word);
        }

        // Replace each word in sentence with the corresponding shortest root
        string word;
        string newSentence;
        while (getline(sStream, word, ' ')) {
            newSentence += dictTrie.shortestRoot(word) + " ";
        }

        newSentence.pop_back();  // remove extra space
        return newSentence;
    }
};
*/