#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

string operatorsFrom(string str) {
    string forms="(){}[]";
    if(str.empty()){
        return "";
    } else if(forms.find(str[0])!=string::npos){
         return str[0]+operatorsFrom(str.substr(1));
    }else{
         return operatorsFrom(str.substr(1));
    }
}

bool operatorsAreMatched(string ops) {
    if(ops.empty()){
        return true;
    }else if(ops.find("()")!=string::npos){
        return operatorsAreMatched(ops.replace(ops.find("()"),2,""));
    }else if(ops.find("[]")!=string::npos){
        return operatorsAreMatched(ops.replace(ops.find("[]"),2,""));
    }else if(ops.find("{}")!=string::npos){
        return operatorsAreMatched(ops.replace(ops.find("{}"),2,""));
    }else {
        return false;
    }
}

bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

/* * * * * * STUDENT Cases * * * * * */

STUDENT_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3{}]()"), "[{}]()");
    EXPECT_EQUAL(operatorsFrom(")v(c[3{}]()"), ")([{}]()");
    EXPECT_EQUAL(operatorsFrom("vec"), "");
}

STUDENT_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}()[]"));
    EXPECT(!operatorsAreMatched("{[]({)}}"));
    EXPECT(!operatorsAreMatched("())("));
    EXPECT(!operatorsAreMatched("{[]ve({)}}"));
}
