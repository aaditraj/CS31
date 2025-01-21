//
//  main.cpp
//  P4
//
//  Created by Aaditya Raj on 11/4/24.
//

#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

// Notwithstanding each function's behavior described below, all functions that return an int must return −1 if they are passed any bad arguments (e.g. a negative array size, or a position that would require looking at the contents of an element past the last element we're interested in). Unless otherwise noted, passing 0 to the function as the array size is not itself an error; it merely indicates the function should examine no elements of the array.

int appendToAll(string a[], int n, string value) {
    
    if (n < 0) return -1;
    
    for (int i = 0; i < n; i++) {
        a[i] = a[i] + value;
    }
    
    return n;
}

int lookup(const string a[], int n, string target) {
    
    if (n < 0) return -1;
    
    for (int i = 0; i < n; i++) {
        if (a[i] == target) return i;
    }
    
    return -1;
}

int positionOfMax(const string a[], int n) {
    
    if (n <= 0) return -1;
    
    string greatest = "";
    int pos = 0;
    
    
    for (int i = 0; i < n; i++) {
        if (greatest == "" || a[i] >= greatest) {
            greatest = a[i];
            pos = i;
        }
    }
    
    return pos;
    
    
}


int rotateLeft(string a[], int n, int pos) {
    
    if (n <= 0 || pos >= n) return -1;
    
    string temp = a[pos];
    
    for (int i = pos; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    
    a[n - 1] = temp;
    
    return pos;
}


int countRuns(const string a[], int n) {
    
    if (n < 0) return -1;
    
    if (n == 0) return 0;
    
    int runs = 0;
    
    for (int i = 0; i < n - 1; i++) {
        if (a[i] != a[i+1]) {
            runs++;
        }
    }
    runs++;
    
    return runs;
}


int flip(string a[], int n) {
    
    if (n < 0) return -1;
    
    for (int i = 0; i < n / 2; i++) {
        string swap = a[n - 1 - i];
        
        a[n - 1 - i] = a[i];
        a[i] = swap;
    }
    
    return n;
}


int differ(const string a1[], int n1, const string a2[], int n2) {
    
    if (n1 < 0 || n2 < 0) return -1;
    
    int max = (n1 < n2) ? n1 : n2;
    for (int i = 0; i < max; i++) {
        if (a1[i] != a2[i]) {
            return i;
        }
    }
    
    return max;
}


int subsequence(const string a1[], int n1, const string a2[], int n2) {
    
    if (n1 < 0 || n2 < 0) return -1;
    
    int j = 0;
    int start = 0;
    
    for (int i = 0; i < n1; i++) {
        if (a1[i] == a2[j]) {
            if (j == 0) start = i;
            j++;
            if (j == n2) {
                return start;
            }
        } else {
            j = 0;
            i = start;
        }
    }
    
    return -1;
}


int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    
    if (n1 < 0 || n2 < 0) return -1;
    
    for (int i = 0; i < n1; i++) {
        if (lookup(a2, n2, a1[i]) != -1) {
            return i;
        }
    }
    
    return -1;
}

int separate(string a[], int n, string separator) {
    
    if (n < 0) return -1;
    
    int numRotations = 0;
    int index = n;
    
    for (int i = 0; i < n; i++) {
        if (a[i] > separator) {
            if (n - i == numRotations) {
                index = i;
                break;
            }
            rotateLeft(a, n, i);
            i--;
            numRotations++;
        }
    }
    
    return index;
}


int main(int argc, const char * argv[]) {
    
    string h[7] = { "melania", "kamala", "donald", "tim", "", "doug", "jd" };
    assert(lookup(h, 7, "doug") == 5);
    assert(lookup(h, 2, "donald") == -1);
    assert(lookup(h, 0, "doug") == -1);
    assert(lookup(h, -1, "donald") == -1);
    assert(appendToAll(h, 7, "?") == 7 && h[0] == "melania?" && h[3] == "tim?");
    assert(appendToAll(h, -1, "?") == -1);
    assert(positionOfMax(h, 7) == 3);
    assert(positionOfMax(h, 3) == 0);
    assert(positionOfMax(h, -1) == -1);
    assert(rotateLeft(h, 7, 0) == 0 && h[1] == "donald?" && h[3] == "?");
    
    
    for (int i = 0; i < 7; i++) {
        cout << h[i] << ", ";
    }
    
    
    assert(rotateLeft(h, 7, 8) == -1);
    assert(rotateLeft(h, 7, -1) == -1);
    assert(countRuns(h, 7) == 7);
    assert(countRuns(h, 2) == 2);
    assert(countRuns(h, -1) == -1);
    assert(countRuns(h, 0) == 0);
    
    for (int i = 0; i < 7; i++) {
        cout << h[i] << ", ";
    }
    
    assert(flip(h, 7) == 7 && h[0] == "" && h[2] == "jd?");

    cout << "All tests succeeded" << endl;
    
    
}
