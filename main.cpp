/* The wind-tunnel test data consists of some number of tested flight-path
angles and their corresponding coefficient of lift. Using this data, we can
estimate, using linear interpolation, the coefficient of lift for a flight-path
angle within the bounds of the data set, even if that particular flight-path
angle was not tested. If we want to find the coefficient of lift for flight-path
angle b, we find flight-path angles a and c such that a < b < c

If flight-path b already exists in the given data set, then you do not need to
use linear interpolation. However, if it doesn't exist, then linear
interpolation assumes a straight line exists between f(a) and f(c).
(In this case, f(a) is the coefficient of lift for flight-path angle a and f(c)
is the coefficient of lift for flight-path angle c.)
To find f(b), use the formula: f(b) = f(a) + (b - a)/(c - a)(f(c) - f(a)) */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;

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

/* Passes in the name of a file and two vectors (double) and stores in the first
vector the flight-path angles (first column) and in the second vector the
corresponding coefficients of lift (2nd column). If the file does not open
properly, this function should output an error message and then call the exit
function passing it an exit value of 1. */
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

/* Passes in the requested flight-path angle along with the 2 vectors of data
(flight-path angles and corresponding coefficients of lift) and returns the
corresponding coefficient of lift. */
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
      else if (i != fPath.size() - 1) {
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

/* Passes in the vector of flight-path angles and returns true if it stores the
angles are in ascending order, otherwise returns false. */
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

/* Passes in both vectors of data and then reorders the data so that the
flight-path angles are in ascending order while maintaining the correspondence
between the flight-path angles and their corresponding coefficients of lift. */
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
