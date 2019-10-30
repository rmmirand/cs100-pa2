/**
 * TODO: File Header
 * Implementations of the methods declared in hpp file
 * inserts and finds words in the dictionary trie and
 * predicts completions of prefixes, as well as wildcard
 * blanks in given patters in order of greatest frequency to least.
 * also contains the destructor for the dictionary trie.
 *
 * Author: Rosa Miranda rmmirand@ucsd.edu
 *
 * priority queue, vector methods taken from cplusplus website
 * predictCompletions and max Below reference taken from Week 4
 * and Week 5 Discussion slides
 * DeleteAll helper method reference modified from helper method in PA1
 */
#include "DictionaryTrie.hpp"
#include <algorithm>
#include <iostream>
#include <queue>

/* TODO */
/* initializes Dictionary Trie*/
DictionaryTrie::DictionaryTrie() { root = nullptr; }
/* TODO */
/* inserts a word if not already in the Dictionary Trie,
 * returns true if succesful, otherwise false */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    if (word.empty()) {  // checks that words is valid
        return false;
    }
    unsigned int i = 0;
    if (!root) {  // checks if tree is empty
        root = new TSTNode(word[i]);
        i++;
        TSTNode* curr = root;
        setMax(curr, freq);
        while (i < word.size()) {
            curr->middle = new TSTNode(word[i]);
            curr = curr->middle;
            setMax(curr, freq);
            i++;
        }
        curr->wordNode = true;
        curr->frequency = freq;
        return true;
    }
    TSTNode* curr = root;
    if (find(word)) {  // checks if word is a duplicate
        return false;
    }
    while (i < word.size()) {
        if (word[i] < curr->letter) {  // if letter < node letter
            if (curr->left) {
                setMax(curr, freq);
                curr = curr->left;
            } else {
                setMax(curr, freq);  // if no left node, add new
                curr->left = new TSTNode(word[i]);
                curr = curr->left;
                return addMiddle(curr, word, i, freq);
            }
        } else if (curr->letter < word[i]) {  // if letter > node letter
            if (curr->right) {
                setMax(curr, freq);
                curr = curr->right;
            } else {  // if no right node, add new
                setMax(curr, freq);
                curr->right = new TSTNode(word[i]);
                curr = curr->right;
                return addMiddle(curr, word, i, freq);
            }
        } else {
            if (i == (word.size() -
                      1)) {  // if we reach end of word, set as wordNode
                if (!curr->wordNode) {
                    curr->wordNode = true;
                    curr->frequency = freq;
                    setMax(curr, freq);
                }
                return true;
            } else {
                if (curr->middle) {  // if letter = node letter, move down
                    setMax(curr, freq);
                    curr = curr->middle;
                    i++;
                } else {  // if no middle, add rest of word here
                    return addMiddle(curr, word, i, freq);
                }
            }
        }
    }
    return false;
}
/*adds remaining word down the middle*/
bool DictionaryTrie::addMiddle(TSTNode* curr, string word, unsigned int loc,
                               unsigned int freq) {
    loc++;
    setMax(curr, freq);
    while (loc < word.size()) {
        curr->middle = new TSTNode(word[loc]);
        curr = curr->middle;
        setMax(curr, freq);
        loc++;
    }
    curr->wordNode = true;
    curr->frequency = freq;
    return true;
}
/* sets a max node below indicator, updates current value if inserted word is
 * greater*/
void DictionaryTrie::setMax(TSTNode* node, unsigned int newFreq) {
    if (node->maxBelow < newFreq) {
        node->maxBelow = newFreq;
    }
}
/* TODO */
/* returns true if word in trie, false otherwise*/
bool DictionaryTrie::find(string word) const {
    if (!root) {
        return false;
    }
    TSTNode* curr = root;
    unsigned int i = 0;
    char letter = word[i];
    while (i < word.size()) {
        if (letter < curr->letter) {  // searches left
            if (curr->left) {
                curr = curr->left;
            } else {
                return false;
            }
        } else if (curr->letter < letter) {  // searches right
            if (curr->right) {
                curr = curr->right;
            } else {
                return false;
            }
        } else {  // searches middle
            if ((i == (word.size() - 1)) && curr->wordNode) {
                return true;
            } else {
                if (curr->middle) {
                    curr = curr->middle;
                    i++;
                    letter = word[i];
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}
/* TODO */
/* returns a vector with words containing prefix from greatest to least
 * frequency*/
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    vector<string> predictions;
    priority_queue<pair<string, unsigned int>,
                   vector<pair<string, unsigned int>>, CompareFrequency>
        allPredicts;

    if (!root) {
        return {};
    }
    if (numCompletions < 1) {
        return {};
    }
    TSTNode* curr = root;
    unsigned int i = 0;
    char letter = prefix[i];
    while (i < prefix.size()) {  // first finds indicated prefix in trie
        if (letter < curr->letter) {
            if (curr->left) {
                curr = curr->left;
            } else {
                return {};
            }
        } else if (curr->letter < letter) {
            if (curr->right) {
                curr = curr->right;
            } else {
                return {};
            }
        } else {
            if ((i == (prefix.size() - 1) && curr->wordNode)) {
                pair<string, unsigned int> predict =
                    make_pair(prefix, curr->frequency);
                allPredicts.push(predict);
                if (!curr->middle) {
                    predictions.push_back(prefix);
                    return predictions;
                } else {
                    curr = curr->middle;
                    break;
                }
            } else if ((i == (prefix.size() - 1))) {
                i++;
                curr = curr->middle;
            } else {
                if (curr->middle) {
                    curr = curr->middle;
                    i++;
                    letter = prefix[i];
                } else {
                    return {};
                }
            }
        }
    }
    // sends current node to helper to find rest of words matching descriptions
    allPredicts = predictHelper(allPredicts, curr, prefix, numCompletions);
    if (allPredicts.size() <
        numCompletions) {  // if found words < numCompletions
        numCompletions = allPredicts.size();
    }
    for (unsigned int i = 0; i < numCompletions; i++) {
        predictions.push_back(allPredicts.top().first);
        allPredicts.pop();
    }
    reverse(predictions.begin(), predictions.end());
    return predictions;
}
/*after initial found prefix, populates queue with matching words*/
priority_queue<pair<string, unsigned int>, vector<pair<string, unsigned int>>,
               CompareFrequency>
DictionaryTrie::predictHelper(
    priority_queue<pair<string, unsigned int>,
                   vector<pair<string, unsigned int>>, CompareFrequency>
        wordsSoFar,
    TSTNode* curr, string prefix, unsigned int numCompletions) {
    // determines if subtree should be searched
    if (wordsSoFar.size() == numCompletions) {
        if (wordsSoFar.top().second > curr->maxBelow) {
            return wordsSoFar;
        }
    }
    // inserts higher frequency into queue, sorts, pops out smallest
    if (curr->wordNode) {
        wordsSoFar.push(make_pair(prefix + curr->letter, curr->frequency));
        if (wordsSoFar.size() > numCompletions) {
            wordsSoFar.pop();
        }
    }
    if (curr->left) {
        wordsSoFar =
            predictHelper(wordsSoFar, curr->left, prefix, numCompletions);
    }
    if (curr->middle) {
        wordsSoFar = predictHelper(wordsSoFar, curr->middle,
                                   prefix + curr->letter, numCompletions);
    }
    if (curr->right) {
        wordsSoFar =
            predictHelper(wordsSoFar, curr->right, prefix, numCompletions);
    }
    return wordsSoFar;
}
/* TODO */
/* returns vector filles with wildcard predictions of words from
 * highest to lowest frequency */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    if (!root) {
        return {};
    }
    TSTNode* curr = root;
    vector<string> topPredictions;
    priority_queue<pair<string, unsigned int>,
                   vector<pair<string, unsigned int>>, CompareFrequency>
        allPredictions;
    string empty;
    // populates queue
    allPredictions =
        scoreHelper(allPredictions, curr, pattern, 0, empty, numCompletions);
    if (allPredictions.size() < numCompletions) {
        numCompletions = allPredictions.size();
    }
    // returns sorted vector
    for (unsigned int i = 0; i < numCompletions; i++) {
        topPredictions.push_back(allPredictions.top().first);
        allPredictions.pop();
    }
    reverse(topPredictions.begin(), topPredictions.end());
    return topPredictions;
}
/* helper method for predictUnderscores, finds all possible words that fill
 * blanks from highest to lowest frequencies*/
priority_queue<pair<string, unsigned int>, vector<pair<string, unsigned int>>,
               CompareFrequency>
DictionaryTrie::scoreHelper(
    priority_queue<pair<string, unsigned int>,
                   vector<pair<string, unsigned int>>, CompareFrequency>
        wordsPredict,
    TSTNode* curr, string pattern, unsigned int loc, string wordBuilder,
    unsigned int numCompletions) {
    if (!curr) {
        return wordsPredict;
    }
    while (loc < pattern.size()) {
        if (pattern[loc] == '_') {  // iterates through possible letters
            wordsPredict = scoreHelper(wordsPredict, curr->left, pattern, loc,
                                       wordBuilder, numCompletions);
            wordsPredict = scoreHelper(wordsPredict, curr->right, pattern, loc,
                                       wordBuilder, numCompletions);
            wordsPredict =
                scoreHelper(wordsPredict, curr->middle, pattern, loc + 1,
                            wordBuilder + (curr->letter), numCompletions);
            if (loc == pattern.size() - 1 && curr->wordNode) {
                wordsPredict.push(
                    make_pair(wordBuilder + (curr->letter), curr->frequency));
                if (wordsPredict.size() > numCompletions) {
                    wordsPredict.pop();
                }
                return wordsPredict;
            }
        } else {  // determines if given letters matches possible words
            if (pattern[loc] == curr->letter) {
                if (loc == pattern.size() - 1 && curr->wordNode) {
                    wordsPredict.push(make_pair(wordBuilder + (curr->letter),
                                                curr->frequency));
                    if (wordsPredict.size() > numCompletions) {
                        wordsPredict.pop();
                    }
                    return wordsPredict;
                } else {
                    wordsPredict = scoreHelper(
                        wordsPredict, curr->middle, pattern, loc + 1,
                        wordBuilder + curr->letter, numCompletions);
                }
            } else if (pattern[loc] < curr->letter) {
                wordsPredict = scoreHelper(wordsPredict, curr->left, pattern,
                                           loc, wordBuilder, numCompletions);
            } else {
                wordsPredict = scoreHelper(wordsPredict, curr->right, pattern,
                                           loc, wordBuilder, numCompletions);
            }
        }
        return wordsPredict;
    }
    return wordsPredict;
}
/*TODO */
/* Destructor helper method*/
DictionaryTrie::~DictionaryTrie() { deleteAll(root); }
void DictionaryTrie::deleteAll(TSTNode* node) {
    if (!node) {
        return;
    }
    deleteAll(node->left);
    deleteAll(node->middle);
    deleteAll(node->right);
    delete node;
}
