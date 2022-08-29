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
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

string encodeLettersAsDigits(string s) {
    string result;
    for (char c: toUpperCase(s)) {
        if (stringContains("AEIOUHWY", c)) {
            result += "0";
        } else if (stringContains("BFPV", c)) {
            result += "1";
        } else if (stringContains("CGJKQSXZ", c)) {
            result += "2";
        } else if (stringContains("DT", c)) {
            result += "3";
        } else if (c == 'L') {
            result += "4";
        } else if (stringContains("MN", c)) {
            result += "5";
        } else if (c == 'R') {
            result += "6";
        }
    }
    return result;
}

string coalesceAdjacentDuplicateDigits(string s) {
    string result;
    char prev = '\0';
    char curr;
    for (int i = 0; i < s.length(); i++) {
        curr = s[i];
        if (curr != prev) {
            result += curr;
            prev = curr;
        }
    }
    return result;
}

string removeZeros(string s) {
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '0') {
            result += s[i];
        }
    }
    return result;
}

string padZerosOrTruncate(string s) {
    string result;
    for (int i = 0; i < 4; i++) {
        if (i < s.length()) {
            result += s[i];
        } else {
            result += '0';
        }
    }
    return result;
}

/*
 * Encodes names according to phonetic structure.
 *
 * @param s The name to encode
 * @return Encoding with the first letter as upper case letter and the others as digits
 *
 * Normally, non-letter or empty strings are not valid input.
 * An empty string would be returned for both cases.
 */
string soundex(string s) {

    char firstLetter;
    string result;
    result = removeNonLetters(s);
    if (result == "") {
        return result;
    }
    firstLetter = result[0];
    result = encodeLettersAsDigits(result);
    result = coalesceAdjacentDuplicateDigits(result);
    result = toUpperCase(charToString(firstLetter)) + result.substr(1, result.length() - 1);
    result = removeZeros(result);
    result = padZerosOrTruncate(result);

    return result;
}


/*
 * Find surnames recorded in a file that have the same soundex with the user typed in surname
 *
 * @param filepath The path to the text file saving surnames
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

    string userInputSurname;
    string soundexOfInput;
    Vector<string> surnamesWithSameSoundex;
    while (true) {
        userInputSurname = getLine("Enter a surname (RETURN to quit)");
        soundexOfInput = soundex(userInputSurname);
        if (soundexOfInput.length() == 0) {
            break;
        }
        surnamesWithSameSoundex.clear();
        for (int i = 0; i < databaseNames.size(); i++) {
            if (soundexOfInput == soundex(databaseNames[i])) {
                surnamesWithSameSoundex.add(databaseNames[i]);
            }
        }
        surnamesWithSameSoundex.sort();
        cout << surnamesWithSameSoundex << endl;
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
STUDENT_TEST("Identify which inputs are mishandled by removeNonLetters") {
    EXPECT_EQUAL(removeNonLetters(""), "");
    EXPECT_EQUAL(removeNonLetters("*&%"), "");
    EXPECT_EQUAL(removeNonLetters("*CHEN"), "CHEN");
}

STUDENT_TEST("Test a helper function to encode letters as digits") {
    EXPECT_EQUAL(encodeLettersAsDigits(""), "");
    EXPECT_EQUAL(encodeLettersAsDigits("AEIOU"), "00000");
    EXPECT_EQUAL(encodeLettersAsDigits("ABCDLMR"), "0123456");
    EXPECT_EQUAL(encodeLettersAsDigits("RMLDCBA"), "6543210");
    EXPECT_EQUAL(encodeLettersAsDigits("AEIOUHWY"), "00000000");
    EXPECT_EQUAL(encodeLettersAsDigits("BFPV"), "1111");
    EXPECT_EQUAL(encodeLettersAsDigits("CGJKQSXZ"), "22222222");
    EXPECT_EQUAL(encodeLettersAsDigits("DT"), "33");
    EXPECT_EQUAL(encodeLettersAsDigits("L"), "4");
    EXPECT_EQUAL(encodeLettersAsDigits("MN"), "55");
    EXPECT_EQUAL(encodeLettersAsDigits("R"), "6");
}

STUDENT_TEST("Test a helper function to coalesce adjacent duplicate digits") {
    EXPECT_EQUAL(coalesceAdjacentDuplicateDigits(""), "");
    EXPECT_EQUAL(coalesceAdjacentDuplicateDigits("1111"), "1");
    EXPECT_EQUAL(coalesceAdjacentDuplicateDigits("112221335"), "12135");
}

STUDENT_TEST("Test a helper function to remove zeros") {
    EXPECT_EQUAL(removeZeros(""), "");
    EXPECT_EQUAL(removeZeros("C0000"), "C");
    EXPECT_EQUAL(removeZeros("A0405"), "A45");
}

PROVIDED_TEST("temp test for unfinished soundex") {
    EXPECT_EQUAL(soundex(""), "");
    EXPECT_EQUAL(soundex("AB"), "A100");
    EXPECT_EQUAL(soundex("A"), "A000");
}

