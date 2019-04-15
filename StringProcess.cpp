#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

const char DELIM = ',';

bool isalnumeric(const string &input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isalnum(input[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    // input txt file
    ifstream fin("FLIGHT_DATA.TXT");
    ofstream fout("processed_string.txt");
    if (!fin.is_open()) {
        cout << "Error opening file" << endl;
    }
    
    vector< vector<string> > data;
    string header;
    getline(fin, header);
    fout << "Time, " << "acc_x, " << "acc_y, " << "acc_y, " << "Latitude, " << " Longitude, " << "Altitude, " << endl;
    
    string currentline;
    // parse strings
    while(fin >> currentline) {
        vector<string> temp;
        if (currentline.find("GPGGA") != string::npos) {
            string timeString = currentline;
            stringstream time(timeString);
            getline( time, timeString, DELIM );
            temp.push_back(timeString + ",");
            
            // sets up for acc pos
            for (int i = 0; i < 9; i++) {
                getline( time, timeString, DELIM );
            }
            
            // save next three vals for mpu
            temp.push_back(timeString + ", ");
            getline( time, timeString, DELIM );
            temp.push_back(timeString + ", ");
            getline( time, timeString, DELIM );
            temp.push_back(timeString + ", ");
            
            currentline = currentline.substr(currentline.find("GPGGA")+5);
            stringstream ss(currentline);
            
            vector<string> lineVector;
            while(getline( ss, currentline, DELIM )) {
                lineVector.push_back(currentline);
            }
            
            for (int i = 0; i < lineVector.size(); i++) {
                if (lineVector[i] == "N") {
//                    temp.push_back(lineVector[i-2] + ",");
                    temp.push_back(lineVector[i-1] + ",");
                } else if (lineVector[i] == "W") {
                    temp.push_back(lineVector[i-1] + ",");
                } else if (lineVector[i] == "M") {
                    temp.push_back(lineVector[i-1] + ",");
                }
            }
        }
        if (temp.size() == 7) {
            data.push_back(temp);
        }
        
//        pos++;
    }
    
    // save all data to file
    for (int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data[i].size(); j++) {
            cout << data[i][j] << " ";
            fout << data[i][j] << " ";
        }
        cout << endl;
        fout << endl;
    }
    
    fout.close();
    return 0;
}
