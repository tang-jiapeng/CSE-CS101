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
#include "simpio.h"
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
    string cleanedToken;
    for(auto str : v) {
        cleanedToken=cleanToken(str);
        if (!cleanedToken.empty()) {
            tokens.add(cleanedToken);
        }
    }
    return tokens;
}

int buildIndex(string dbfile, Map<string, Set<string>>& index)
{
    ifstream in;
    if(!openFile(in,dbfile)){
        error("Cannot open file named " + dbfile);
    }
    Vector<string> lines;
    readEntireFile(in,lines);
    int numberlines=lines.size();
    Set<string> gathers;
    string website,websiteText;
    for(int i=0;i<numberlines;i+=2){
        website=lines.get(i);
        websiteText=lines.get(i+1);
        for(auto tokens : gatherTokens(websiteText)){
            gathers=index.get(tokens);
            gathers.add(website);
            index.put(tokens,gathers);
        }
    }
    return numberlines/2;
}


Set<string> findQueryMatches(Map<string, Set<string>>& index, string query)
{
    Set<string> result;
    string cleanedItem;
    for(auto stringItem : stringSplit(query, " ")){
        cleanedItem = cleanToken(stringItem);
        if(cleanedItem.size()){
            if(stringItem[0]=='+'){
                result.intersect(index.get(cleanedItem));
            }else if(stringItem[0]=='-'){
                result.difference(index.get(cleanedItem));
            }else {
                result.unionWith(index.get(cleanedItem));
            }
        }
    }
    return result;
}

void searchEngine(string dbfile)
{
    cout << "Stand by while building index..."<< endl;
    Map<string,Set<string>> index;
    int IndexNumbers=buildIndex(dbfile,index);

    cout<< "Indexed "<<IndexNumbers <<" pages containing "
                     <<index.size()<<" unique terms" <<endl;

    while(true){
        string input;
        input = getLine("Enter query sentence (RETURN/ENTER to quit):");
        if(!input.size()){
            break;
        }
        Set<string> matches;
        matches=findQueryMatches(index,input);
        cout << "Found "<<matches.size()<<" matching pages "<<endl
             <<matches<<endl;
    }
    cout<<"ALL done!"<<endl;
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

STUDENT_TEST("buildIndex from tiny.txt, websites containing fish") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> expectedWebsites = {"www.shoppinglist.com", "www.dr.seuss.net", "www.bigbadwolf.com"};
    EXPECT_EQUAL(index.get("fish"), expectedWebsites);
}

STUDENT_TEST("buildIndex from tiny.txt, websites containing bread") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> expectedWebsites = {"www.shoppinglist.com"};
    EXPECT_EQUAL(index.get("bread"), expectedWebsites);
}

STUDENT_TEST("buildIndex from tiny.txt, websites containing red") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> expectedWebsites = {"www.rainbow.org", "www.dr.seuss.net"};
    EXPECT_EQUAL(index.get("red"), expectedWebsites);
}

STUDENT_TEST("buildIndex from tiny.txt, websites containing red") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> expectedWebsites = {"www.rainbow.org", "www.dr.seuss.net"};
    EXPECT_EQUAL(index.get("red"), expectedWebsites);
}

STUDENT_TEST("buildIndex from tiny.txt, returned websites when using empty string as the query keyword") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> expectedWebsites = {};
    EXPECT_EQUAL(index.get(""), expectedWebsites);
}

STUDENT_TEST("Time trials of building inverted index for res/tiny.txt") {
    Map<string, Set<string>> index;
    TIME_OPERATION("tiny", buildIndex("res/tiny.txt", index));
}

STUDENT_TEST("Time trials of building inverted index for res/website.txt") {
    Map<string, Set<string>> index;
    TIME_OPERATION("tiny", buildIndex("res/website.txt", index));
}

STUDENT_TEST("findQueryMatches from tiny.txt, invalid queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesWithEmptyQuery = findQueryMatches(index, "");
    EXPECT_EQUAL(matchesWithEmptyQuery.size(), 0);
    Set<string> matchesWithInvalid1 = findQueryMatches(index, "&$1 +123 -%#");
    EXPECT_EQUAL(matchesWithInvalid1.size(), 0);
    Set<string> matchesWithInvalid2 = findQueryMatches(index, "+=-&$1 +123 +%#");
}

STUDENT_TEST("findQueryMatches from tiny.txt, compound queries interleaved with invalid terms") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red +&34 fish -**88");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "+-*)( red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "--+*&^ red -fish +-+134");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}

STUDENT_TEST("findQueryMatches from tiny.txt, matches of compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matches1 = findQueryMatches(index, "fish -+bread I**");
    Set<string> expectedMatches1 = {"www.dr.seuss.net", "www.bigbadwolf.com"};
    EXPECT_EQUAL(matches1, expectedMatches1);
    Set<string> matches2 = findQueryMatches(index, "red -blue +green");
    Set<string> expectedMatches2 = {};
    EXPECT_EQUAL(matches2, expectedMatches2);
    Set<string> matches3 = findQueryMatches(index, "red -blue green");
    Set<string> expectedMatches3 = {"www.rainbow.org"};
    EXPECT_EQUAL(matches3, expectedMatches3);
}
