/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>

/* TODO */
DictionaryTrie::DictionaryTrie() {
}


/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) { 
	if(word.empty()){
			return false;
	}
	if(!root){
		root = new TSTNode(word[0]);
		return(insertHelper(root, word, freq, 1));
	}
	else{
		if(find(word)){
			return false;
		}
		TSTNode* node = root;
		for(unsigned int i = 0; i < word.size(); i++){
			node = insertRecurser(node, word[i]);
			if(word[i] == node->letter){
				if(node->middle){
					node = node->middle;
				}else{
					node->middle = new TSTNode(word[i]);
					return insertHelper(node->middle, word, freq, i);
				}
			}else if(word[i] < node->letter){
				node->left = new TSTNode(word[i]);
				return insertHelper(node->middle,word,freq,i);
			}else{
				node->right = new TSTNode(word[i]);
				return insertHelper(node->middle, word, freq, i);
			}
		}
	}
	return false; 
}
DictionaryTrie::TSTNode* DictionaryTrie::insertRecurser(TSTNode* node, char letter)const{
	TSTNode* currNode = node;
	if(letter < node->letter && node->left){
		currNode = insertRecurser(node->left, letter);
	}else if(node->letter < letter && node->right){
		currNode = insertRecurser(node->right, letter);
	}else{
		return currNode;
	}
	return currNode;
}
bool DictionaryTrie::insertHelper(TSTNode* node, string word, unsigned int freq, unsigned int loc)const{
	for(unsigned int i = loc; i < word.size(); i++){
		node->middle = new TSTNode(word[i]);
		node = node->middle;
	}
	node->wordNode = true;
	node->frequency = freq;
	return true;
}

/* TODO */
bool DictionaryTrie::find(string word) const { 
/*	if(!root){
		return false;
	}
	TSTNode* curr = root;
	for(unsigned int i = 0; i < word.size()-1; i++){
		if(findHelper(curr, word[i])){
			curr = curr->middle;
		}else{
			return false;
		}
	}
	if(curr->wordNode && curr->letter == word[word.size()-1]){
		return true;
	}
	return false; 
*/	
	TSTNode* place = root;
	unsigned int wordBit = 0;
	while(wordBit < word.size()){
		if(word[wordBit] < place->letter){
			if(place->left){
				place = place->left;
			}
			else{
				return false;
			}
		}else if(place->letter < word[wordBit]){
			if(place->right){
				place = place->right;
			}else{
				return false;
			}
		}else{
		   
			if(place->middle){
				place = place->middle;
			}else{
				return false;
			}
		}
	}
}
bool DictionaryTrie::findHelper(TSTNode* node, char lettre) const {
/*	if(!node){
		return false;
	}
	if(lettre < node->letter){
		if(node->left){
			return(findHelper(node->left, lettre));
		}
	}else if(node->letter < lettre){
		if(node->right){
			return(findHelper(node->right, lettre));
		}else{
			return false;
		}
	}else if(node->letter != lettre){
		return false;
	}else{
		return true;
	}
return false;	
}*/
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
DictionaryTrie::~DictionaryTrie() {/**deleteAll(root)**/}
