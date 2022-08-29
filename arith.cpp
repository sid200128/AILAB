#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int n;
    int m;
    unordered_map<char, int> charMap;
    vector<bool> usedDigits;
    
    bool solve (vector<string>& words, string result, int pos, int idx, int bal) {
        
        if (pos == n) {
            for (auto& x: charMap) {
                cout << x.first << " " << x.second << endl;
            }
            return bal == 0;
        }
        
        if (idx == m) {
            
            if (charMap.find(result[pos]) == charMap.end() && usedDigits[bal % 10] == false) {
                if (bal % 10 == 0 && pos + 1 == n) return false;
                charMap[result[pos]] = bal % 10;
                usedDigits[bal % 10] = true;
                bool temp = solve(words, result, pos+1, 0, bal / 10);
                charMap.erase(result[pos]);
                usedDigits[bal % 10] = false;
                return temp;
            } else if (charMap.find(result[pos]) != charMap.end() && charMap[result[pos]] == bal % 10) {
                if (pos + 1 == n && charMap[result[pos]] == 0) return false;
                return solve(words, result, pos+1, 0, bal / 10);
            } else {
                return false;
            }

        }
        
        string word = words[idx];
        
        if (pos >= word.size()) return solve(words, result, pos, idx+1, bal);
        
        // int len = words[idx].size();
        
        char letter = word[pos];
        
        
        if (charMap.find(letter) != charMap.end()) {
            // leading zero
            if (pos+1 == word.size() && word.size() > 1 && charMap[letter] == 0) return false;
            return solve(words, result, pos, idx+1, bal + charMap[letter]);
        }
        
        for (int i = 0; i<=9; i++) {
            if (pos + 1 == word.size() && i == 0 && word.size() > 1) continue;
            if (usedDigits[i]) continue;
            usedDigits[i] = true;
            charMap[letter] = i;
            bool temp = solve(words, result, pos, idx+1, bal + i);
            usedDigits[i] = false;
            charMap.erase(letter);
            if (temp) return true;
        }
        return false;
    }
    
    bool isSolvable(vector<string>& words, string result) {
        
        for (string word: words) {
            if (word.size() > result.size()) return false;
        }
        
        // represents number of words in words vector including result
        m = words.size();
        
        // represents length of longest word in words
        n = result.size();
        
        for (string& word: words) {
            reverse(word.begin(), word.end());
        }
        
        reverse(result.begin(), result.end());
        
        usedDigits.resize(10, false);
        
        return solve(words, result, 0, 0, 0);
    }
};


int main() {
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i<n; i++) {
        cin >> words[i];
    }
    string result;
    cin >> result;
    Solution ob;
    bool ans = ob.isSolvable(words, result);
    cout << (ans == true ? "True" : "False") << endl;
    return 0;
}