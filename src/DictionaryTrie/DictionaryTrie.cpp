/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <algorithm>
#include <queue>

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
		setMax(curr, freq);
		while(i < word.size()){
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
	if(find(word)){
		return false;
	}
	while(i < word.size()){
		if(word[i] < curr->letter){
			if(curr->left){
				curr = curr->left;
			}
		        else{
				curr->left = new TSTNode(word[i]);
				curr = curr->left;
				setMax(curr, freq);
				i++;
				while(i < word.size()){
					curr->middle = new TSTNode(word[i]);
					curr = curr->middle;
					setMax(curr, freq);
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
				setMax(curr, freq);
				i++;
				while(i < word.size()){
					curr->middle = new TSTNode(word[i]);
					curr = curr->middle;
					setMax(curr, freq);
					i++;
				}
				curr->wordNode = true;
				curr->frequency = freq;
				return true;
			}
		}else{
			if(i == (word.size()-1)){
				if(!curr->wordNode){
					curr->wordNode = true;
					curr->frequency = freq;
					setMax(curr, freq);
				}
				return true;
			}else{
				if(curr->middle){
					setMax(curr, freq);
					curr = curr->middle;
					i++;
				}else{
					i++;
					while(i < word.size()){
						curr->middle = new TSTNode(word[i]);
						curr = curr->middle;
						setMax(curr, freq);
						i++;
					}
					curr->wordNode = true;
					curr->frequency = freq;
					return true;
				}
			}
		}
	}
	return false;
}
void DictionaryTrie::setMax(TSTNode* node, unsigned int newFreq){
	if(node->maxBelow < newFreq){
		node->maxBelow = newFreq;
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
	return false;
}
/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
    		unsigned int numCompletions) {
	vector<string> predictions;
	priority_queue<pair<string, unsigned int>, vector<pair<string, unsigned int>>, CompareFrequency> allPredicts;

	if(!root){
		return {};
	}
	if(numCompletions < 1){
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
			if((i == (prefix.size()-1) && curr->wordNode)){
				pair<string,unsigned int> predict = make_pair(prefix, curr->frequency);
				allPredicts.push(predict);
				if(!curr->middle){
					predictions.push_back(prefix);
					return predictions;
				}else{
					curr = curr->middle;
					break;
				}
			}else if((i == (prefix.size()-1))){
				i++;
				curr = curr->middle;
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
	allPredicts = predictHelper(allPredicts, curr, prefix, numCompletions);
	if(allPredicts.size() < numCompletions){
		numCompletions = allPredicts.size();
	}	
	for(unsigned int i = 0; i < numCompletions ; i++){
		predictions.push_back(allPredicts.top().first);
		allPredicts.pop();
	}
	reverse(predictions.begin(), predictions.end());
	return predictions;
}
priority_queue<pair<string, unsigned int>, vector<pair<string,unsigned int>>, CompareFrequency> DictionaryTrie::predictHelper(priority_queue<pair<string, unsigned int>, vector<pair<string, unsigned int>>, CompareFrequency> wordsSoFar, TSTNode* curr, string prefix, unsigned int numCompletions){
	if(wordsSoFar.size() == numCompletions){
		if(wordsSoFar.top().second > curr->maxBelow){
			return wordsSoFar;
		}
	}
	if(curr->wordNode){
		wordsSoFar.push(make_pair(prefix+curr->letter, curr->frequency));
		if(wordsSoFar.size() > numCompletions){
			wordsSoFar.pop();
		}		
	}
	if(curr->left){
		wordsSoFar = predictHelper(wordsSoFar, curr->left, prefix, numCompletions);
	}
	if(curr->middle){
		wordsSoFar = predictHelper(wordsSoFar, curr->middle, prefix+curr->letter, numCompletions);
	}
	if(curr->right){
		wordsSoFar = predictHelper(wordsSoFar, curr->right, prefix, numCompletions);
	}
	return wordsSoFar;
}
/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
	if(!root){
		return {};
	}
	TSTNode* curr = root;
	vector<string> topPredictions;
	priority_queue<pair<string, unsigned int>, vector<pair<string, unsigned int>>, CompareFrequency> allPredictions;
	string empty;
	allPredictions = scoreHelper(allPredictions, curr, pattern, 0, empty, numCompletions);
	if(allPredictions.size() < numCompletions){
		numCompletions = allPredictions.size();
	}
	for(unsigned int i = 0; i < numCompletions; i++){
		topPredictions.push_back(allPredictions.top().first);
		allPredictions.pop();
	}
	reverse(topPredictions.begin(), topPredictions.end());
    	return topPredictions;
}
priority_queue<pair<string, unsigned int>, vector<pair<string, unsigned int>>, CompareFrequency> DictionaryTrie::scoreHelper(priority_queue<pair<string, unsigned int>, vector<pair<string, unsigned int>>,CompareFrequency> wordsPredict, TSTNode* curr, string pattern, unsigned int loc, string wordBuilder, unsigned int numCompletions){
	if(!curr){
		return wordsPredict;
	}
	while(loc < pattern.size()){
		if(pattern[loc] == '_'){
			wordsPredict = scoreHelper(wordsPredict, curr->left, pattern, loc, wordBuilder, numCompletions);
			wordsPredict = scoreHelper(wordsPredict, curr->right, pattern, loc, wordBuilder, numCompletions);
			wordsPredict = scoreHelper(wordsPredict, curr->middle, pattern, loc+1, wordBuilder+(curr->letter), numCompletions);
			if(loc == pattern.size() - 1 && curr->wordNode){ 
				wordsPredict.push(make_pair(wordBuilder+(curr->letter), curr->frequency));
				if(wordsPredict.size() > numCompletions){
					wordsPredict.pop();
				}	
				return wordsPredict;
			}
		}else{
			if(pattern[loc] == curr->letter){
				if(loc == pattern.size() - 1 && curr->wordNode){ 
					wordsPredict.push(make_pair(wordBuilder+(curr->letter), curr->frequency));
					if(wordsPredict.size() > numCompletions){
						wordsPredict.pop();
					}	
					return wordsPredict;
				}else{
					wordsPredict = scoreHelper(wordsPredict, curr->middle, pattern, loc+1, wordBuilder+curr->letter, numCompletions);
				}
			}else if(pattern[loc] < curr->letter){
				wordsPredict = scoreHelper(wordsPredict, curr->left, pattern, loc, wordBuilder, numCompletions);
			}else{
				wordsPredict = scoreHelper(wordsPredict, curr->right, pattern, loc, wordBuilder, numCompletions);
			}
		}
		return wordsPredict;
	}
	return wordsPredict;
}
/*TODO */
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
