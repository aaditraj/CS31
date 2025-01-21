//
//  main.cpp
//  Worksheet2
//
//  Created by Aaditya Raj on 10/11/24.
//

#include <iostream>
using namespace std;


void solvePuzzle( char encodedMsg[] ,char decodedMsg[] )
{
    for(int i=0; i < strlen(encodedMsg); i+=2) {
        decodedMsg[i/2] = encodedMsg[i];
    }
}

int main(int argc, const char * argv[]) {
    
    char encodedMsg[] = "BAAANPALNEA";
    char decodedMsg[100];
    cout << "Original Decoded Msg" << decodedMsg << endl;
    solvePuzzle(encodedMsg,decodedMsg);
    cout << "The decoded message is: " << decodedMsg << endl;
    return 0;
    
    
}
