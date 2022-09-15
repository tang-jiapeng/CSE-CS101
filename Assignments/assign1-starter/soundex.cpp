/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
#include <map>
#include <cmath>
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string removeNonLetters(string s) {
    string result="";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
map<char,int> mp;
void init(){
    mp['A']=mp['E']=mp['I']=mp['O']=0;
    mp['U']=mp['H']=mp['W']=mp['Y']=0;
    mp['B']=mp['F']=mp['P']=mp['V']=1;
    mp['C']=mp['G']=mp['J']=mp['K']=2;
    mp['Q']=mp['S']=mp['X']=mp['Z']=2;
    mp['D']=mp['T']=3;
    mp['L']=4;
    mp['M']=mp['N']=5;
    mp['R']=6;
}

string soundex(string s) {
    /* TODO: Fill in this function. */
    init();
    s=removeNonLetters(s);
    for(auto &str:s){
        str=toUpperCase(str);
    }
    string temp="";
    char first=s[0];
    for(auto str:s){
        temp+=integerToString(mp[str]);
    }
    string ans="";
    ans+=temp[0];
    for(int i=1;i<temp.size();i++){
        if(temp[i]=='0'||temp[i]==temp[i-1]){
            continue;
        }
        ans+=temp[i];
    }
    ans[0]=first;
    int Size=min((int)ans.size(),4);
    string result=ans.substr(0,Size);
    if(Size<4){
        for(int i=Size;i<4;i++) {
            result+='0';
        }
    }
    return result;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames

    /* TODO: Fill in the remainder of this function. */
    while(true){
        string name=getLine("Enter a surname (RETURN to quit): ");
        if(name.empty()) {
            cout<<"ALL done!"<<endl;
            break;
        }
        string temp=soundex(name);
        cout<<"Soundex code is "<<temp<<endl;
        Vector<string> ans;
        for(auto Name:databaseNames){
            if(soundex(Name)==temp){
                ans.add(Name);
            }
        }
        ans.sort();
        cout<<"Matches from database: " << ans <<endl;
    }
}

/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here

STUDENT_TEST("Check removeNonLetters is true"){
    string s="";
    string result=removeNonLetters(s);
    EXPECT_EQUAL(result,"");
    s="23123";
    result=removeNonLetters(s);
    EXPECT_EQUAL(result,"");
}
