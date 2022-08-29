/*
 * CS106B Section Handout Test Harness: Section 1
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Originally codified by Trip Master
 * and Nick Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "string.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
using namespace std;

int getMatches (string s1, string s2);

/**
 * @brief bestIndexInSequence - returns the index within
 * SEQUENCE with the most base-pair matches
 * @param sequence - a string sequence of ATCG bases.
 * @param sample - a smaller sequence of ATCG bases that
 * we are comparing against subsequences of SEQUENCE to
 * find the index that results in the most matches.
 * @return - the integer value signifying the index with
 * the most base pair matches.
 *
 *
 * As a reference, A matches with T, C matches with G
 */
int bestIndexInSequence (string sequence, string sample) {
    int bestMatches = -1;
    int bestIndex = 0;
    for (int i = 0; i < sequence.length(); i++) {
        int numMatches = getMatches(sequence.substr(i, sample.length()), sample);
        if (numMatches >= bestMatches) {
            bestIndex = i;
        }
    }
    return bestIndex;
}

/**
 * @brief getMatches - returns the number of ATCG matches between s1 and s2.
 * Assumes s1 and s2 are the same length.
 * @param s1 - the first string, representing a portion of SEQUENCE.
 * @param s2 - the second string, equivalent to SAMPLE.
 * @return - the integer value signifying how many AT or CG pairs exist between
 * the two strings.
 */
int getMatches (string s1, string s2) {
    int numMatches = 0;
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] == s2[i]) numMatches++;
    }

    return numMatches;
}

/* * * * * Tests Below This Point * * * * */

STUDENT_TEST("TODO: what am I testing!"){
    // TODO: Fill in this test!
}

