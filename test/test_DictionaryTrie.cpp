/**
 * TODO: File HEADER
 *
 * Author:
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}

/* TODO */
TEST(DictTrieTests, FALSEFIND_TEST) {
    DictionaryTrie dict;
    bool temp = dict.insert("apple", 6);
    ASSERT_EQ(dict.find("banana"), false);
}
TEST(DictTrieTests, EMPTYSTRING_TEST) {
    DictionaryTrie dict;
    string empty = "";
    ASSERT_EQ(dict.insert(empty, 1), false);
}
TEST(DictTrieTests, EMPTYFIND_TEST) {
    DictionaryTrie dict;
    string empty = "";
    bool temp = dict.insert(empty, 2);
    ASSERT_EQ(dict.find(empty), false);
}
TEST(DictTrieTests, INSERTROOT_TEST) {
    DictionaryTrie dicti;
    bool temp;
    temp = dicti.insert("apple", 7);
    temp = dicti.insert("banana", 5);
    ASSERT_EQ(dicti.find("apple"), true);
}
TEST(DictTrieTests, FINDME_TEST) {
    DictionaryTrie dict;
    bool temp = dict.insert("carrot", 1);
    temp = dict.insert("banana", 2);
    temp = dict.insert("durian", 3);
    temp = dict.insert("cap", 4);
    temp = dict.insert("duran", 5);
    temp = dict.insert("carott", 6);
    temp = dict.insert("durc", 7);
    temp = dict.insert("durca", 8);
    ASSERT_EQ(dict.find("durca"), true);
}
TEST(DictTrieTests, FINDLIST_TEST) {
    DictionaryTrie dictii;
    bool temp;
    temp = dictii.insert("apple", 4);
    ASSERT_EQ(dictii.find("apple"), true);
}
TEST(DictTrieTests, PREDICT_EMPTY) {
    DictionaryTrie dict;
    vector<string> test;
    ASSERT_EQ(dict.predictCompletions("apple", 5), test);
}
TEST(DictTrieTests, PREDICTSORT_TEST) {
    DictionaryTrie dict;
    bool temp;
    temp = dict.insert("app", 4);
    temp = dict.insert("apps", 5);
    vector<string> test;
    test.push_back("apps");
    test.push_back("app");
    ASSERT_EQ(dict.predictCompletions("ap", 3), test);
}
TEST(DictTrieTests, PREDICTLIST_TEST) {
    DictionaryTrie dict;
    bool temp;
    temp = dict.insert("app", 3);
    temp = dict.insert("apc", 7);
    temp = dict.insert("apb", 8);
    temp = dict.insert("apa", 9);
    temp = dict.insert("apca", 1);
    temp = dict.insert("az", 2);
    temp = dict.insert("ay", 10);
    temp = dict.insert("azi", 1);
    vector<string> test = {"apa", "apb", "apc"};
    ASSERT_EQ(dict.predictCompletions("ap", 3), test);
}
TEST(DictTrieTests, PREDICSAME_TEST) {
    DictionaryTrie dict;
    bool temp;
    temp = dict.insert("apple", 6);
    temp = dict.insert("apples", 7);
    temp = dict.insert("applets", 5);
    temp = dict.insert("banana", 4);
    vector<string> test = {"apples"};
    ASSERT_EQ(dict.predictCompletions("apple", 1), test);
}
TEST(DictTrieTests, PREDICTLEFTMIDDLE_TEST) {
    DictionaryTrie dict;
    bool temp;
    temp = dict.insert("banana", 4);
    temp = dict.insert("apple", 4);
    vector<string> test = {"apple"};
    ASSERT_EQ(dict.predictCompletions("apple", 3), test);
}
TEST(DictTrieTests, PREDICTSAMEFREQ_TEST) {
    DictionaryTrie dict;
    bool temp;
    temp = dict.insert("applet", 3);
    temp = dict.insert("apb", 3);
    temp = dict.insert("apa", 3);
    vector<string> test = {"apa", "apb", "applet"};
    ASSERT_EQ(dict.predictCompletions("ap", 3), test);
}
TEST(DictTrieTests, BIGDATA_TEST) {
    DictionaryTrie dict;
    bool temp;
    temp = dict.insert("arm", 5);
    temp = dict.insert("yakuza", 654);
    temp = dict.insert("yak", 3);
    temp = dict.insert("burger", 213);
    temp = dict.insert("xyler", 8);
    temp = dict.insert("crap", 12);
    temp = dict.insert("cramp", 357);
    temp = dict.insert("zebra", 23);
    temp = dict.insert("ya", 1);
    temp = dict.insert("scatter", 57);
    temp = dict.insert("bird", 3);
    temp = dict.insert("birds", 68);
    temp = dict.insert("sword", 12);
    temp = dict.insert("shoot", 76);
    temp = dict.insert("tepid", 85);
    temp = dict.insert("red", 21);
    temp = dict.insert("potion", 456);
    temp = dict.insert("dracula", 32);
    temp = dict.insert("plant", 123);
    temp = dict.insert("tree", 8);
    temp = dict.insert("sharpen", 3);
    temp = dict.insert("fangs", 43);
    temp = dict.insert("pit", 57);
    temp = dict.insert("regulate", 12);
    temp = dict.insert("refrain", 57);
    temp = dict.insert("blue", 23);
    temp = dict.insert("cherry", 4675);
    temp = dict.insert("latch", 231);
    temp = dict.insert("honey", 23);
    temp = dict.insert("berry", 21);
    temp = dict.insert("vine", 6);
    vector<string> test = {"yakuza", "yak", "ya"};
    ASSERT_EQ(dict.predictCompletions("ya", 5), test);
}
TEST(DictTrieTests, UNDERMID_TEST) {
    DictionaryTrie dict;
    bool temp;
    temp = dict.insert("amo", 1);
    temp = dict.insert("amor", 2);
    temp = dict.insert("ame", 3);
    temp = dict.insert("ami", 4);
    temp = dict.insert("amie", 5);
    temp = dict.insert("ale", 3);
    temp = dict.insert("ape", 4);
    temp = dict.insert("are", 5);
    temp = dict.insert("amp", 5);
    vector<string> test = {"are", "ape", "ale"};
    ASSERT_EQ(dict.predictUnderscores("a_e", 3), test);
}
TEST(DictTrieTests, UNDERALL_TEST) {
    DictionaryTrie dict;
    bool temp;
    temp = dict.insert("amo", 1);
    temp = dict.insert("amor", 2);
    temp = dict.insert("ame", 3);
    temp = dict.insert("ami", 4);
    temp = dict.insert("amie", 5);
    temp = dict.insert("ale", 3);
    temp = dict.insert("ape", 4);
    temp = dict.insert("are", 5);
    temp = dict.insert("amp", 5);
    vector<string> test = {"amp", "are", "ami", "ape"};
    ASSERT_EQ(dict.predictUnderscores("___", 4), test);
}
