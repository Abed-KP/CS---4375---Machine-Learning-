#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
/*
  Abed Ahmed (ASA19005)
  09/10/2022
  HomeWork 2
 */

using namespace std;

const int MAX_LEN = 1000;
vector<double> rm(MAX_LEN);
vector<double> medv(MAX_LEN);

int readCSV();
double findSum(vector<double> vec);
double findMean(vector<double> vec);
double findMedian(vector<double> vec);
double findRange(vector<double> vec);
double findCovariance(vector<double> vec1, vector<double> vec2);
double findCorrelation(vector<double> vec1, vector<double> vec2, double covariance);

int main() {
    readCSV();
    cout << "The sum of the vector rm is: " << findSum(rm) << endl;
    cout << "The sum of the vector medv is: " << findSum(medv) << endl;

    cout << "The mean of the vector rm is: " << findMean(rm) << endl;
    cout << "The mean of the vector medv is: " << findMean(medv) << endl;

    cout << "The median of the vector rm is: " << findMedian(rm) << endl;
    cout << "The median of the vector medv is: " << findMedian(medv) << endl;

    cout << "The range of the vector rm is: " << findRange(rm) << endl;
    cout << "The range of the vector medv is: " << findRange(medv) << endl;

    double cov =  findCovariance(rm,medv);
    cout << "The covariance between the vectors rm and medv is: " << cov << endl;
    cout << "The covariance between the vectors rm and medv is: " << findCorrelation(rm,medv,cov) << endl;
}

double findSum(vector<double> vec){
    double sum = 0;
    for(double i: vec){
        sum += vec[i] ;
    }
    return sum;

}

double findMean(vector<double> vec){
    double sum = 0;
    for(double i: vec){
        sum += vec[i] ;
    }
    return sum / vec.size();
}

double findMedian(vector<double> vec){

    vector<double> dummy(vec);
    sort(dummy.begin(),dummy.end());

    int size = dummy.size();
    if(size % 2 == 1){
        return dummy[size / 2];
    }
    else{
        int mid1 = (size / 2) - 1;
        int mid2 = size / 2;
        return dummy[mid1] + dummy[mid2];
    }
}

double findRange(vector<double> vec){
    vector<double> dummy(vec);
    sort(dummy.begin(),dummy.end());

    int size = dummy.size();
    return dummy[size-1] - dummy[0];
}

double findCovariance(vector<double> vec1, vector<double> vec2){
    int size = vec1.size();
    double sum = 0;
    double mean1 = findMean(vec1);
    double mean2 = findMean(vec2);
    for(int i = 0; i < size; i++){
        sum += (vec1[i] - mean1) * (vec2[i] - mean2);
    }
    return sum / (size - 1);
}

double findCorrelation(vector<double> vec1, vector<double> vec2, double covariance){
    double sigma1 = sqrt(findCovariance(vec1,vec1));
    double sigma2 = sqrt(findCovariance(vec2,vec2));
    return (covariance) / (sigma1 * sigma2);
}


int readCSV(){
    ifstream inFS;
    string line;
    string rm_in, medv_in;
    cout << "Opening File Boston.csv" << endl;
    inFS.open("Boston.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file Boston.csv" <<endl;
        return 1;
    }

    cout << "Reading line 1" << endl;
    getline(inFS, line);

    cout << "heading: " << line << endl << endl;

    int numObservations = 0;
    while (inFS.good()){
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        numObservations++;
    }
    rm.resize(numObservations);
    medv.resize(numObservations);
}
