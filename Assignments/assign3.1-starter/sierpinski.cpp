#include <iostream>    // for cout, endl
#include "recursion.h"
#include "testing/SimpleTest.h"
using namespace std;

void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

int drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    if(order == 0){
        fillBlackTriangle(window,one,two,three);
        return 1;
    }else {
        int count=0;
        GPoint p12=GPoint((one.x+two.x)/2.0,(one.y+two.y)/2.0);
        GPoint p13=GPoint((one.x+three.x)/2.0,(one.y+three.y)/2.0);
        GPoint p23=GPoint((two.x+three.x)/2.0,(two.y+three.y)/2.0);
        count+=drawSierpinskiTriangle(window,one,p12,p13,order-1);
        count+=drawSierpinskiTriangle(window,p12,two,p23,order-1);
        count+=drawSierpinskiTriangle(window,p13,p23,three,order-1);
        return count;
    }
}


/* * * * * * Test Cases * * * * * */

/*
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all testing
 * via the interactive demo.
 */

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runInteractiveDemo();
}

