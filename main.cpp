#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// using std::cout;
// using std::cin;
// using std::endl;
// using std::vector;
// using std::string;
// using std::ifstream;
using namespace std;

void readData(const string&, vector<double>&, vector<double>&);
double interpolation(double, const vector<double>&, const vector<double>&);
bool isOrdered(const vector<double>&);
void reorder(vector<double>&, vector<double>&);

int main() {

  string fileName;

  cout << "Enter name of input data file:" << endl;
  cout << endl;
  cin >> fileName;

  vector<double> fPath;
  vector<double> coLift;

  readData(fileName, fPath, coLift);

  double fpAngle = 0.0;
  string loop = "yes";

  while (loop == "yes") {
    cout << "Enter flight path angle: " << endl;
    cin >> fpAngle;

    if (!isOrdered(fPath) || !isOrdered(coLift)) {
      reorder(fPath, coLift);
    }

    cout << "Coefficient of Lift: " << interpolation(fpAngle, fPath, coLift) << endl;
    cout << "Would you like to enter again: " << endl;
    cin >> loop;
  }

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

  if (fPath.size() != 0 && coLift.size() != 0) {
    if (b < fPath.at(0) || b > fPath.at(fPath.size() - 1)) {
      return 0.0;
    }

    int a = 0, c = 0;

    for (unsigned int i = 0; i < fPath.size(); ++i) {
      if (fPath.at(i) == b) {
        return coLift.at(i);
      }
      else if (i != fPath.size() - 1) {// && (i + 1) < fPath.size()) {

          if (fPath.at(i) < b && fPath.at(i + 1) > b) {
            a = i;
            c = i + 1;

            return coLift.at(a) + ( b - fPath.at(a) ) / (fPath.at(c) - fPath.at(a) ) * ( coLift.at(c) - coLift.at(a));
          }
        }
    }
    return 0.0;
  }
  exit(-1);

}

bool isOrdered(const vector<double>& orderTest) {

  if (orderTest.size() != 0 && orderTest.size() != 1) {
    for (unsigned int i = 0; i < orderTest.size() - 1; ++i) {
      if (orderTest.at(i) > orderTest.at(i + 1)) {
        return false;
      }
    }
  }
  return true;

}

void reorder(vector<double>& fPath, vector<double>& coLift) {

  if (fPath.size() != 0 && coLift.size() != 0) {
    int indexSmallest = 0;
    double tempVal = 0.0;
    double tempLift = 0.0;

    for (unsigned int i = 0; i < fPath.size() - 1; ++i) {
      indexSmallest = i;
      for (unsigned int j = i + 1; j < fPath.size(); ++j) {
        if (fPath.at(indexSmallest) > fPath.at(j)) {
          indexSmallest = j;
        }
      }

      tempVal = fPath.at(i);
      fPath.at(i) = fPath.at(indexSmallest);
      fPath.at(indexSmallest) = tempVal;

      tempLift = coLift.at(i);
      coLift.at(i) = coLift.at(indexSmallest);
      coLift.at(indexSmallest) = tempLift;
    }
  }

}
