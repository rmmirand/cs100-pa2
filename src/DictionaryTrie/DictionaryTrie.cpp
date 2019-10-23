/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>

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
	char letter = word[i];
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
    return {};
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
