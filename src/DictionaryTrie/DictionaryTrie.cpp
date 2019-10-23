/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <algorithm>

/* TODO */
DictionaryTrie::DictionaryTrie() {
	root = nullptr;
}
/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) { 
	if(word.empty()){
			return false;
	}
	unsigned int i =0;
	if(!root){
		root = new TSTNode(word[i]);
		i++;
		TSTNode* curr = root;
		while(i < word.size()){
			curr->middle = new TSTNode(word[i]);
			curr = curr->middle;
			i++;
		}
		curr->wordNode = true;
		curr->frequency = freq;
		return true;
	}
	TSTNode* curr = root;
	while(i < word.size()){
		if(word[i] < curr->letter){
			if(curr->left){
				curr = curr->left;
			}
		        else{
				curr->left = new TSTNode(word[i]);
				curr = curr->left;
				i++;
				while(i < word.size()){
					curr->middle = new TSTNode(word[i]);
					curr = curr->middle;
					i++;
				}
				curr->wordNode = true;
				curr->frequency = freq;
				return true;
		        }
		}else if(curr->letter < word[i]){
			if(curr->right){
				curr = curr->right;
			}else{
				curr->right = new TSTNode(word[i]);
				curr = curr->right;
				i++;
				while(i < word.size()){
					curr->middle = new TSTNode(word[i]);
					curr = curr->middle;
					i++;
				}
				curr->wordNode = true;
				curr->frequency = freq;
				return true;
			}
		}else{
			if(i == (word.size()-1)){
				curr->wordNode = true;
				return true;
			}else{
				if(curr->middle){
					curr = curr->middle;
					i++;
				}else{
					i++;
					while(i < word.size()){
						curr->middle = new TSTNode(word[i]);
						curr = curr->middle;
						i++;
					}
					curr->wordNode = true;
					curr->frequency = freq;
					return true;
				}
			}
		}
	}
}

/* TODO */
bool DictionaryTrie::find(string word) const { 
	if(!root){
		return false;
	}
	TSTNode* curr = root;
	unsigned int i = 0;
	char letter = word[i];
	while(i < word.size()){
		if(letter < curr->letter){
			if(curr->left){
				curr = curr->left;
			}else{
				return false;
			}
		}else if(curr->letter < letter){
			if(curr->right){
				curr = curr->right;
			}else{
				return false;
			}
		}else{
			if((i == (word.size()-1)) && curr->wordNode){
				return true;
			}else{
				if(curr->middle){
					curr = curr->middle;
					i++;
					letter = word[i];
				}else{
					return false;
				}
			}
		}
	}
	return true;
}
/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
    		unsigned int numCompletions) {
	vector<string> predictions;
	vector<pair<string,unsigned int>> allPredicts;

	if(!root){
		return {};
	}
	
	TSTNode* curr = root;
	unsigned int i = 0;
	char letter = prefix[i];
	while(i < prefix.size()){
		if(letter < curr->letter){
			if(curr->left){
				curr = curr->left;
			}else{
				return {};
			}
		}else if(curr->letter < letter){
			if(curr->right){
				curr = curr->right;
			}else{
				return {};
			}
		}else{
			if((i == (prefix.size()-1)) && curr->wordNode){
				pair<string,unsigned int> predict = make_pair(prefix, curr->frequency);
				allPredicts.push_back(predict);
				i++;
				if(curr->middle){
					curr = curr->middle;
					i++;
				}else{
					predictions.push_back(prefix);
					return predictions; //change
				}
			}else{
				if(curr->middle){
					curr = curr->middle;
					i++;
					letter = prefix[i];
				}else{
					return {};
				}
			}
		}
	}
	allPredicts = predictHelper(allPredicts, curr, prefix+curr->letter);
	CompareFrequency compareFreq;
	sort(allPredicts.begin(), allPredicts.end(), compareFreq);
	if(allPredicts.size() < numCompletions){
		numCompletions = allPredicts.size();
	}	
	for(unsigned int i = 0; i < numCompletions ; i++){
		predictions.push_back(allPredicts[i].first);
	}
	return predictions;
}
vector<pair<string,unsigned int>> DictionaryTrie::predictHelper(vector<pair<string, unsigned int>> wordsSoFar, TSTNode* curr, string prefix){
	if(curr->wordNode){
		wordsSoFar.push_back(make_pair(prefix, curr->frequency));
	}
	if(curr->left){
		wordsSoFar = predictHelper(wordsSoFar, curr->left, prefix+(curr->left->letter));
	}
	if(curr->middle){
		wordsSoFar = predictHelper(wordsSoFar, curr->middle, prefix+(curr->middle->letter));
	}
	if(curr->right){
		wordsSoFar = predictHelper(wordsSoFar, curr->right, prefix+(curr->right->letter));
	}
	return wordsSoFar;
}
/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {
	deleteAll(root);
}
void DictionaryTrie::deleteAll(TSTNode* node){
	if(!node){
		return;
	}
	deleteAll(node->left);
	deleteAll(node->middle);
	deleteAll(node->right);
	delete node;
}
