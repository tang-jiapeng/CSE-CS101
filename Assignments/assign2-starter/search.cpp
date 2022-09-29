// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "strlib.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;


string cleanToken(string s)
{
    int pos = 0;
    while(ispunct(s[pos])) {
        pos++;
    }
    s=s.substr(pos);
    pos=s.length()-1;
    while(ispunct(s[pos])){
        pos--;
    }
    s=s.substr(0,pos+1);
    int count = 0;
    for(auto &str : s){
        if(isalpha(str)){
            count++;
        }
        str=toLowerCase(str);
    }
    if(!count) return "";
    return s;
}

Set<string> gatherTokens(string text)
{
    Set<string> tokens;
    Vector<string> v=stringSplit(text," ");
    for(auto str : v) {
        if(tokens.contains(str)){
            continue;
        }
        str=cleanToken(str);
        tokens.add(str);
    }
    return tokens;
}

int buildIndex(string dbfile, Map<string, Set<string>>& index)
{

    return 0;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query)
{
    Set<string> result;
    // TODO: your code here
    return result;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void searchEngine(string dbfile)
{
    // TODO: your code here
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on strings with no punctuation at beginning or end") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS*106B"), "cs*106b");
}

PROVIDED_TEST("cleanToken on strings with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
}

PROVIDED_TEST("cleanToken on non-word strings (no letters)"){
    EXPECT_EQUAL(cleanToken("106"), "");
    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs*106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 5 unique words, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 5);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 11);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here
STUDENT_TEST("check cleanToken is true"){
    EXPECT_EQUAL(cleanToken("section"),"section");
    EXPECT_EQUAL(cleanToken("section/"),"section");
    EXPECT_EQUAL(cleanToken("secti'on"),"secti'on");
    EXPECT_EQUAL(cleanToken("<<>>section>>>"),"section");
    EXPECT_EQUAL(cleanToken("section-10"),"section-10");
    EXPECT_EQUAL(cleanToken("sECTION"),"section");
    EXPECT_EQUAL(cleanToken("<<1sEcTion-10>>"),"1section-10");
    EXPECT_EQUAL(cleanToken("132132>><<?!"""),"");
}

STUDENT_TEST("check gatherTokens is true"){
    Set<string> expected = {"i", "love", "cs*106b"};
    EXPECT_EQUAL(gatherTokens("I !_love_!    CS*106B!"), expected);
    Set<string> expected1 = {"i", "love", "cs*106b"};
    EXPECT_EQUAL(gatherTokens("I !_love_! love I loVE__   __CS*106B!"), expected1);
}
