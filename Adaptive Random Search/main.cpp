#include <bits/stdc++.h>

using namespace std;

typedef vector< pair<int, int> > vectorOfPair;

vector<double> currentVector, stepVector, bigStepVector;
double currentCost, stepCost, bigStepCost;

double objectiveFunction(vector<double> vec) {
    int siz=vec.size();
    double sum = 0;
    for(int i=0; i<siz; ++i) {
        sum += vec[i]*vec[i];
    }

    return sum;
}

vector<double> randomVector(vectorOfPair bounds) {
    int siz = bounds.size();
    double r;
    vector<double> dvec;

    for(int i=0; i<siz; i++) {
        r = ((double) rand() / (RAND_MAX));
        dvec.push_back(bounds[i].first + ((bounds[i].second - bounds[i].first) * r));
    }

    return dvec;
}

double largeStepSize(int i, double stepSize, double sFactor, double lFactor, int iterMult) {
    if(i > 0 && i%iterMult==0)
        return stepSize * lFactor;
    return stepSize * sFactor;
}

vector<double> takeStep(vectorOfPair bounds, vector<double> currentVect, double stepSize) {
    int siz = bounds.size();
    double r;
    vector<double> position;
    for(int i=0; i<siz; ++i) {
        double mn = max((double)bounds[i].first, currentVect[i]-stepSize);
        double mx = min((double)bounds[i].second, currentVect[i]+stepSize);
        r = ((double) rand() / (RAND_MAX));
        position.push_back(mn + ((mx-mn) * r));
    }

    return position;
}

void takeSteps(vectorOfPair bounds, vector<double> currentVect, double currentCst, double stepSize, double bigStepsize) {
    stepVector = takeStep(bounds, currentVect, stepSize); // takeStep
    stepCost = objectiveFunction(stepVector);
    bigStepVector = takeStep(bounds, currentVect, bigStepsize);
    bigStepCost = objectiveFunction(bigStepVector);
}

void searchFunc(int maxIter, vectorOfPair bounds, double initFactor, double sFactor, double lFactor, int iterMult, int maxNoImpr) {
    double stepSize = (bounds[0].second - bounds[0].first) * initFactor;
    int cnt = 0;
    currentVector = randomVector(bounds);
    currentCost = objectiveFunction(currentVector);
    for(int i=1; i<=maxIter; ++i) {
        double bigStepsize = largeStepSize(i, stepSize, sFactor, lFactor, iterMult);
        takeSteps(bounds, currentVector, currentCost, stepSize, bigStepsize);
        if(stepCost <= currentCost || bigStepCost <= currentCost) {
            if(bigStepCost <= stepCost) {
                stepSize = bigStepsize;
                currentCost = bigStepCost;
                currentVector = bigStepVector;
            }
            else {
                currentCost = stepCost;
                currentVector = stepVector;
            }
            cnt = 0;
        }
        else {
            cnt += 1;
            if(cnt >= maxNoImpr) {
                cnt = 0;
                stepSize = (stepSize/sFactor);
            }
        }
        cout << "> iteration " << i << ", best = " << currentCost << endl;
    }
}

int main()
{
    // problem configuration
    int problemSize = 2;
    vectorOfPair bounds;
    for(int i=0; i<problemSize; ++i)
        bounds.push_back( make_pair(-5,5) );

    // algorithm configuration
    int maxIter = 1000, iterMult = 10, maxNoImpr = 30;
    double initFactor = 0.05, sFactor = 1.3, lFactor = 3.0;

    // execute the algorithm
    searchFunc(maxIter, bounds, initFactor, sFactor, lFactor, iterMult, maxNoImpr);

    // print the best
    cout << "--------------\n";
    cout << "Done. Best Solution: c = " << currentCost << ", v = ";
    int l = currentVector.size();
    for(int i=0; i<l; ++i) {
        cout << currentVector[i] << "    " << endl;
    }

    return 0;
}
