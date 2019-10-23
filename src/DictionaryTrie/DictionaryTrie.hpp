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


  public:
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

    //Helper functions
    TSTNode* insertRecurser(TSTNode* node, char letter) const;
    bool insertHelper(TSTNode* node, string word, unsigned int freq, unsigned int loc) const;
    bool findHelper(TSTNode* node, char lettre) const;
 
};


#endif  // DICTIONARY_TRIE_HPP
