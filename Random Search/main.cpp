#include <bits/stdc++.h>

using namespace std;

typedef vector< pair<int, int> > vectorOfPair;

queue< vector<double> > saveVector;
int l;

double objectiveFunction(vector<double> vec) {
    int siz=vec.size();
    double sum = 0;
    for(int i=0; i<siz; ++i) {
        sum += vec[i]*vec[i];
    }

    return sum;
}

vector<double> randomVector(vectorOfPair searchSpace) {
    int siz = searchSpace.size();
    double r;
    vector<double> dvec;

    for(int i=0; i<siz; i++) {
        r = ((double) rand() / (RAND_MAX));
        dvec.push_back(searchSpace[i].first + ((searchSpace[i].second - searchSpace[i].first) * r));
    }

    return dvec;
}

vector<double> searchFunc(vectorOfPair searchSpace, int maxIter) {
    vector<double> best;
    for(int i=1; i<=maxIter; ++i) {
        vector<double> candidateVector = randomVector(searchSpace);
        double candidateCost = objectiveFunction(candidateVector);
        if(i==1 || candidateCost<best.back()) {
            saveVector.push(candidateVector);
            best.push_back(candidateCost);
        }
        cout << " > iteration = " << i << ", best = " << best.back() << endl;
        l = candidateVector.size();
        for(int i=0; i<l; ++i)
            cout << candidateVector[i] << "     ";
        cout << "\n\n";
    }

    return best;
}


int main()
{
    srand ( time(NULL) );

    int problemSize = 2, maxIter = 100;

    // search_space
    vectorOfPair searchSpace;
    for(int i=0; i<problemSize; ++i)
        searchSpace.push_back( make_pair(-5,5) );

    // best
    vector<double> best = searchFunc(searchSpace, maxIter);
    // print the best
    cout << "------------------" << endl;
    int siz = best.size();
    for(int i=0; i<siz; ++i) {
        cout << "Done. Best Solution: c = " << best[i] << endl;
        for(int j=0; j<l; ++j)
            cout << saveVector.front()[j] << "     ";
        cout << "\n\n";
        saveVector.pop();
    }

    return 0;
}
