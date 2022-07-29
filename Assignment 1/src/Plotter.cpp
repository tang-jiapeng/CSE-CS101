#include "Plotter.h"
#include "strlib.h"
using namespace std;

void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    PenStyle style={1,"black"};
    double x0=0,y0=0,x1,y1;
    int penState=0;
    for(string line;getline(input,line);){
        Vector<string> results=stringSplit(line," ");
        string first=toLowerCase(results[0]);
        if(startsWith(first,"penup")){
            penState=0;
        }else if(startsWith(first,"pendown")){
            penState=1;
        }else if(startsWith(first,"moveabs")){
            if(penState==1){
                x1=stringToReal(results[1]);
                y1=stringToReal(results[2]);
                drawLine(x0,y0,x1,y1,style);
            }
            x0=stringToReal(results[1]);
            y0=stringToReal(results[2]);
        }else if(startsWith(first,"moverel")){
            if(penState==1){
                x1=x0+stringToReal(results[1]);
                y1=y0+stringToReal(results[2]);
                drawLine(x0,y0,x1,y1,style);
            }
            x0=x0+stringToReal(results[1]);
            y0=y0+stringToReal(results[2]);
        }else if(startsWith(first,"penwidth")){
            style.width=stringToReal(results[1]);
        }else if(startsWith(first,"penColor")){
            style.color=stringToReal(results[1]);
        }
    }
}
