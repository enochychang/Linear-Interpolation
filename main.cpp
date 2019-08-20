#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;

void readData(const string &, vector<double> &, vector<double> &);
double interpolation(double, const vector<double> &, const vector<double> &);
bool isOrdered(const vector<double> &);
void reorder(vector<double> &, vector<double> &);

int main() {
  string fileName;

  cout << "Enter name of input data file: " << endl;
  cin >> fileName;

  vector<double> fPath;
  vector<double> coLift;

  readData(fileName, fPath, coLift);
  double fpAngle = 0.0;
  string loop = "yes";

  while (loop == "yes") {}
    cout << "Enter flight path angle: " << endl;
    cin >> fpAngle;

    if (!isOrdered(fPath) || !isOrdered(coLift)) {
      reorder(fPath, coLift);
    }

    interpolation(fpAngle, fPath, coLift);
    cout << "Would you like to enter again: " << endl;
    cin >> loop;

}

void readData(const string& fileName, vector<double>& fPath, vector<double>& coLift) {
  ifstream inFS;
  inFS.open(fileName);
  if (!inFS.is_open()) {
    cout << "Error opening " << fileName << endl;
    exit(1);
  }

  double temp1 = 0.0;
  double temp2 = 0.0;
  while (inFS >> temp1 && inFS >> temp2) {
      fPath.push_back(temp1);
      coLift.push_back(temp2);
  }

  inFS.close();
}

double interpolation(double b, const vector<double>& fPath, const vector<double>& coLift) {
  int a = 0, c = 0;
  for (int i = 0; i < fPath.size(); ++i) {
    if (fPath.at(i) == b) {
      return coLift.at(i);
    }
    else if (i != fPath.size() - 1) {
      if (fPath.at(i) < b && fPath.at(i + 1) > b) {
        a = i;
        c = i + 1;
        return ( coLift.at(a) + (b - a) ) / ( (c - a) * (coLift.at(c) - coLift.at(a)) );
      }
    }
  }
  return -1;
}

bool isOrdered(const vector<double>& orderTest) {
  for (unsigned int i = 0; i < orderTest.size() - 1; ++i) {
    if (orderTest.at(i) > orderTest.at(i + 1)) {
      return false;
    }
  }
  return true;
}

void reorder(vector<double>& fPath, vector<double>& coLift) {

}
