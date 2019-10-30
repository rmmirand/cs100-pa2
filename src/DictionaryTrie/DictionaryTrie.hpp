/**
 * Declaration of methods and variables of Dictionary Trie
 * Declerations and methods of Ternary Trie Nodes for Dictionary
 * Declaration of comparator for priority queue use.
 *
 * Author: Rosa Miranda
 *
 * comparator reference taken from PA1 BST node comparator
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */

/* comparator for sorting strings by their frequencies
 * from grestest to smallest */
class CompareFrequency {
  public:
    bool operator()(pair<string, unsigned int> p1,
                    pair<string, unsigned int> p2) {
        if (p1.second == p2.second) {
            return p1.first < p2.first;
        }
        return p1.second > p2.second;
    }
};

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
        unsigned int maxBelow;
        bool wordNode;

        TSTNode(const char& letter) : letter(letter) {
            left = right = middle = 0;
            frequency = maxBelow = 0;
            wordNode = false;
        }
    };
    TSTNode* root;
    /* helper method for predictCompletions */
    priority_queue<pair<string, unsigned int>,
                   vector<pair<string, unsigned int>>, CompareFrequency>
    predictHelper(
        priority_queue<pair<string, unsigned int>,
                       vector<pair<string, unsigned int>>, CompareFrequency>
            wordsSoFar,
        TSTNode* curr, string prefix, unsigned int numCompletions);
    /* helper method for predictUnderscores */
    priority_queue<pair<string, unsigned int>,
                   vector<pair<string, unsigned int>>, CompareFrequency>
    scoreHelper(
        priority_queue<pair<string, unsigned int>,
                       vector<pair<string, unsigned int>>, CompareFrequency>
            wordsPredict,
        TSTNode* curr, string patter, unsigned int loc, string wordBuilder,
        unsigned int numCompletions);
    /* helper method for destructor */
    void deleteAll(TSTNode* node);
    /* helper method for setting maxBelow value */
    void setMax(TSTNode* node, unsigned int newFreq);
    /* helper method to create remaining letter nodes in a new word*/
    bool addMiddle(TSTNode* curr, string word, unsigned int loc,
                   unsigned int freq);

  public:
    /* TODO: add function header */
    /* initiliazes Dictionary Trie Tree */
    DictionaryTrie();

    /* TODO: add function header */
    /* inserts a new word into a tree, returns true if successful*/
    bool insert(string word, unsigned int freq);

    /* TODO: add function header */
    /* returns true if word is in the tree, false if not*/
    bool find(string word) const;

    /* TODO: add function header */
    /* returns a vector of numCompletions of the words with the given prefix
     * in order of greatest frequency to smallest */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    /* returns a vector of numCompletions of the words with that match the
     * given pattern, with the underscores filled in with possible characters
     * that make up valid words in the dictionary trie from greatest to smallest
     * frequency */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    /* Dictionary Trie tree destructor, deletes all nodes in the tree */
    ~DictionaryTrie();
};
#endif  // DICTIONARY_TRIE_HPP
