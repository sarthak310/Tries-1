//time: O(n), n = total chars in dict
//space: O(n)
class TrieNode {
    public: // not a good practice...data members should be in private and use getter/setter funcs to access them
    vector<TrieNode*> next;
    bool isWord;
    string theWord;
    //public:
    TrieNode() {
        next.resize(26);
        isWord = false;
        theWord = "";
    }
};
class Trie {
    public: // not a good practice...data members should be in private and use getter/setter funcs to access them
    TrieNode* root;
    //public:
    Trie() {
        root = new TrieNode();
    }
    void insert(string word) {
        TrieNode* curr = root;
        for(int i = 0; i < word.size(); i++) {
            if(curr -> next[word[i] - 'a'] == NULL) {
                curr -> next[word[i] - 'a'] = new TrieNode();
            }
            curr = curr -> next[word[i] - 'a'];
            if(i == word.size()-1) {
                curr -> isWord = true;
                curr -> theWord = word;
            }
        }
    }
};
class Solution {
    void longest(string &ans, int &maxlen, int count, TrieNode* root) {
        for(int i = 0; i < 26; i++) {
            if(root -> next[i] != NULL) {
                TrieNode* nextNode = root -> next[i];
                if(nextNode -> isWord == true) {
                    if(count + 1 > maxlen) {
                        ans = nextNode -> theWord;
                        maxlen = count + 1;
                    }
                    longest(ans, maxlen, count+1, nextNode);
                }
            }
        }
    }
public:
    string longestWord(vector<string>& words) {
        Trie trie;
        for(string word : words) {
            trie.insert(word);
        }
        string ans;
        int maxlen = 0;
        longest(ans, maxlen, 0, trie.root);
        return ans;
    }
};