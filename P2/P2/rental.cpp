//
//  rental.cpp
//  P2
//
//  Created by Aaditya Raj on 10/13/24.
//

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    
    // variables to be defined by user input
    int oStart, oEnd, days, startMonth;
    double rentCharge;
    string name;
    
    // string to output if user input is incorrect
    string output = "";
    
    //begin reading user input
    cout << "Odometer at start: ";
    cin >> oStart;
    
    if (oStart < 0) {
        output = "The starting odometer reading must not be negative.";
    }
    
    cout << "Odometer at end: ";
    cin >> oEnd;
    
    if (oEnd < oStart && output == "") {
        output = "The ending odometer reading must be at least as large as the starting reading.";
    }
        
    cout << "Rental days: ";
    cin >> days;
    
    if (days <= 0 && output == "") {
        output = "The number of rental days must be positive.";
    }
    
    cin.ignore(10000, '\n');
    
    cout << "Customer name: ";
    getline(cin, name);
    
    if (name == "" && output == "") {
        output = "You must enter a customer name.";
    }
    
    string YorN = "";
    
    cout << "Luxury car? (y/n): ";
    getline(cin, YorN);
    
    if (YorN != "y" && YorN != "n" && output == "") {
        output = "You must enter y or n.";
    }
    
    bool luxury = (YorN == "y") ? true : false;
    
    cout << "Starting month (1=Jan, 2=Feb, etc.):";
    cin >> startMonth;
    
    if ((startMonth < 1 || startMonth > 12) && output == "") {
        output = "The month number must be in the range 1 through 12.";
    }

    cout << "---" << endl;
    
    if (output == "") { // if user input is valid
        
        // begin calculating rental charge
        rentCharge = luxury ? 75 * days : 45 * days; // add base charge
        int milesDriven = oEnd - oStart;
        
        if (milesDriven > 100) {
            rentCharge += 33;
            milesDriven -= 100;
            
            double nextRate = ((startMonth == 12) || (startMonth >= 1 && startMonth <= 3)) ? .33 : .27;
            
            if (milesDriven >= 500) {
                rentCharge += 500 * nextRate;
                milesDriven -= 500;
                rentCharge += milesDriven * .21;
            } else {
                rentCharge += milesDriven * nextRate;
            }
            
        } else {
            rentCharge += milesDriven * 0.33;
        }
        
        
        cout << "The rental charge for " << name << " is $" << fixed << setprecision(2) << showpoint << rentCharge << endl;
        
    } else {
        cout << output << endl;
    }
    
    
}
