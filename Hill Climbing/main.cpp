#include <bits/stdc++.h>

using namespace std;

int candidateCost, neighborCost;
vector<char> candidateVector, neighborVector;

int onemax(vector<char> bitstring) {
    int cnt = 0;
    int l = bitstring.size();
    for(int i=0; i<l; ++i) {
        if(bitstring[i] == '1') cnt++;
    }

    return cnt;
}

vector<char> randomBitstring(int numBits) {
    vector<char> digits;
    double r;
    for(int i=0; i<numBits; ++i) {
        r = ((double) rand() / (RAND_MAX));
        if(r > 0.5) digits.push_back('1');
        else        digits.push_back('0');
    }

    return digits;
}

vector<char> randomNeighbor(vector<char> bitstring) {
    int pos = rand() % 65;
    bitstring[pos] = (bitstring[pos] == '1')? '0' : '1';

    return bitstring;
}

void searchFunc(int maxIterations, int numBits) {
    candidateVector = randomBitstring(numBits);
    candidateCost = onemax(candidateVector);
    for(int i=1; i<=numBits; ++i) {
        neighborVector = randomNeighbor(candidateVector);
        neighborCost = onemax(neighborVector);
        if(neighborCost >= candidateCost) {
            candidateVector = neighborVector;
            candidateCost = neighborCost;
        }
        cout << "> iteration " << i << ", best = " << candidateCost << endl;
        if(candidateCost == numBits)
            break;
    }
}

int main()
{
    srand ( time(NULL) );

    // problem configuration
    int numBits = 64;

    // algorithm configuration
    int maxIterations = 1000;

    // execute the algorithm
    searchFunc(maxIterations, numBits);

    // print the best
    cout << "Done. Best Solution: c = " << candidateCost << ", v = ";
    for(int i=0; i<numBits; ++i)
        cout << candidateVector[i];
    cout << endl;

    return 0;
}
