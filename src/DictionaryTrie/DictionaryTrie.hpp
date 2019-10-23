/**
 * TODO: File Header
 *
 * Author:
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <string>
#include <utility>
#include <vector>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // TODO: add private members and helper methods here
    class TSTNode {
      public:
        TSTNode* left;
        TSTNode* right;
        TSTNode* middle;
	char const letter;
	unsigned int frequency;
	bool wordNode;

        TSTNode(const char &letter) : letter(letter){
		left = right = middle = 0;
		frequency = 0;
		wordNode = false;

	}
    };  
    TSTNode* root;
 
    vector<pair<string,unsigned int>> predictHelper(vector<pair<string, unsigned int>> wordsSoFar, TSTNode* curr, string prefix);   

  public:

    void deleteAll(TSTNode* node);

    /* TODO: add function header */
    DictionaryTrie();

    /* TODO: add function header */
    bool insert(string word, unsigned int freq);

    /* TODO: add function header */
    bool find(string word) const;

    /* TODO: add function header */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    ~DictionaryTrie();

};
struct CompareFrequency{
	bool operator()(pair<string, unsigned int> p1, pair<string, unsigned int> p2){
		if(p1.second == p2.second){
			return p1.first < p2.first;
		}
		return p1.second > p2.second;
	}
};



#endif  // DICTIONARY_TRIE_HPP
