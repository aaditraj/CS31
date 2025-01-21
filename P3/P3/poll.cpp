//
//  main.cpp
//  P3
//
//  Created by Aaditya Raj on 10/24/24.
//

#include <iostream>
#include <cctype>
#include <cassert>
using namespace std;


bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NJ.NH.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool hasRightSyntax(string pollData) {
        
    string partyString = "";
        
    for (int i = 0; i < pollData.length(); i++) {
        char c = pollData[i];
        
        if (partyString.size() == 0) {
            if (!isalpha(c)) { // first character of prediction must be a letter
                return false;
            }
            partyString += c;
        } else {
            if (partyString.size() == 1) {
                if (!isdigit(c)) { // second character must be a digit
                    return false;
                }
                partyString += c;
            } else if (partyString.size() >= 2) {
                if (isdigit(c)) {
                    partyString += c;
                    if (partyString.size() > 3) {  // cannot have more than 2 digits in a prediction
                        return false;
                    }
                } else if (isalpha(c)) {
                    string stateCode = pollData.substr(i, 2); // this and next character must form valid state code
                    for (int i = 0; i < stateCode.length(); i++) {
                        stateCode[i] = toupper(stateCode[i]);
                    }
                    if (isValidUppercaseStateCode(stateCode)) {
                        partyString = "";
                        i++; // skip past second character of stateCode if it is valid
                    } else {
                        return false;
                    }
                } else {
                    return false; // any other character besides digit and letter unacceptable
                }
            }
        }
    }
    
    return (partyString.size() == 0); // to ensure there are no half predictions
    
}


int computeVotes(string pollData, char party, int& voteCount) {
    bool isPollData = hasRightSyntax(pollData);
    
    if (!isPollData) return 1;
    
    if (!isalpha(party)) return 3;
    
    bool newPrediction = true;
    
    bool partyMatch = false;
    
    string votes = "";
    
    int numberVotes = 0;
        
    for (int i = 0; i < pollData.length(); i++) {
        char c = pollData[i];
        
        if (newPrediction) { // beginning of a new prediction
            partyMatch = (toupper(c) == toupper(party));
            newPrediction = false;
        } else {
            if (isdigit(c)) {
                votes += c; // track the number of votes in a string
            } else if (isalpha(c)) {
                int votesCounted = 0;
                
                // convert votes string to a number
                if (votes.size() == 2) {
                    votesCounted += 10 * (votes[0] - 48);
                    votesCounted += votes[1] - 48;
                } else {
                    votesCounted += votes[0] - 48;
                }
                
                if (votesCounted == 0) return 2;
                
                if (partyMatch) numberVotes += votesCounted; // add votes only if correct party

                i++; // skip past second letter of state code to next prediction
                
                newPrediction = true;
                votes = "";
            }
        }
    }
    
    voteCount = numberVotes;
    
    return 0;
}


int main()
{
    
    assert(hasRightSyntax("R40TX")); // test a standard prediction
    assert(!hasRightSyntax("%40TX")); // test party is not a letter
    assert(!hasRightSyntax("R400TX")); // test more than three digits in votes
    assert(!hasRightSyntax("R40TT")); // test invalid state code
    assert(hasRightSyntax("R40TXD54CAr6Msd28nYL06UT")); // test multiple state predictions with both lower and uppercase letters
    
    int votes;
    votes = -999; // so we can detect whether computeVotes sets votes

    // test for different parties in poll data
    assert(computeVotes("R40TXD54CAr6Msd28nYL06UT", 'd', votes) == 0 && votes == 82);
    assert(computeVotes("R40TXD54CAr6Msd28nYL06UT", 'r', votes) == 0 && votes == 46);
    assert(computeVotes("R40TXD54CAr6Msd28nYL06UT", 'l', votes) == 0 && votes == 6);

    assert(computeVotes("RR40TX", 'r', votes) == 1  &&  votes == 6); // test for invalid poll data
    assert(computeVotes("R40TXD0CAr6Msd28nYL06UT", 'd', votes) == 2  &&  votes == 6); // test for 0 votes for at least 1 state
    assert(computeVotes("D54CA", '@', votes) == 3 && votes == 6); // test for invalid party parameter
    assert(computeVotes("", 'R', votes) == 0 &&  votes == 0); // test for empty poll data
    
    cout << "All tests succeeded" << endl;
    
}
