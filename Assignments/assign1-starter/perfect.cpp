/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include <cmath>
#include "testing/SimpleTest.h"
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
long smarterSum(long n) {
    /* TODO: Fill in this function. */
    long total=0;
    if(n==1){
        return 0;
    }
    for(long div=1;div<=sqrt(n);div++){
        if(n%div==0){
            total+=div;
            if(n%(n/div)==0&&(n/div)!=n&&(n/div)!=div) {
                total+=(n/div);
            }
        }
    }
    return total;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
bool isPerfectSmarter(long n) {
    /* TODO: Fill in this function. */
    return (n != 0) && (n == smarterSum(n));
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void findPerfectsSmarter(long stop) {
     /* TODO: Fill in this function. */
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */

bool isPrime(long n){
    return (smarterSum(n)==1);
}

long findNthPerfectEuclid(long n) {
    /* TODO: Fill in this function. */
    long k=1,total=0;
    while(true){
        long m=pow(2,k)-1;
        if(isPrime(m)){
            total++;
            if(total==n) {
                return (pow(2,k)-1)*pow(2,k-1);
            }
        }
        k++;
    }
    return 0;
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

// TODO: add your student test cases here

STUDENT_TEST("Time trials of findPerfects on doubling input sizes by student"){
    TIME_OPERATION(20000,findPerfects(20000));
    TIME_OPERATION(40000,findPerfects(40000));
    TIME_OPERATION(80000,findPerfects(80000));
    TIME_OPERATION(160000,findPerfects(160000));
}

STUDENT_TEST("Check negative numbers aren't Perfect"){
    EXPECT(!isPerfect(-1));
    EXPECT(!isPerfect(-10));
    EXPECT(!isPerfect(-6));
}

STUDENT_TEST("Check smarterSum is true"){
    EXPECT_EQUAL(smarterSum(25),divisorSum(25));
    EXPECT_EQUAL(smarterSum(6),divisorSum(6));
    EXPECT_EQUAL(smarterSum(1),divisorSum(1));
}

STUDENT_TEST("Time trials of findPerfectsSmarter on doubling input sizes by student"){
    TIME_OPERATION(600000,findPerfectsSmarter(600000));
    TIME_OPERATION(1200000,findPerfectsSmarter(1200000));
    TIME_OPERATION(2400000,findPerfectsSmarter(2400000));
    TIME_OPERATION(4800000,findPerfectsSmarter(4800000));
}


STUDENT_TEST("Check findNthPerfectEuclid is true"){
    EXPECT(isPerfect(findNthPerfectEuclid(1)));
    EXPECT(isPerfect(findNthPerfectEuclid(2)));
    EXPECT(isPerfect(findNthPerfectEuclid(3)));
    EXPECT(isPerfect(findNthPerfectEuclid(5)));
}

