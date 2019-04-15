//
//  curvature.cpp
//  engr100-final
//
//  Created by Arthur Zhang on 4/2/19.
//  Copyright © 2019 ArthurKZhang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream fin("processed_string.txt");
    if (!fin.is_open()) {
        cout << "Error opening file, closing" << endl;
    }
    string header;
    // removes top line
    getline(fin, header);
    fstream fout("curvature.txt");
    fout << "Time, Curvature, " << endl;
    vector< vector<double> > data;
    
    
    
    
    
    
}

void loadData(vector< vector<double> > &data, ifstream &fin) {
    string time, acc_x, acc_y, acc_z, latitude, longitude, altitude;
    while (fin >>)
}


