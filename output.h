// input.h
#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
#include "output.h"
#include "variable.h"
using namespace std;

void output(){
    for(int i=0; i<route.size(); i++){
        for(int j=0; j<route.at(i).size(); j++){
            if(j==0) cout << "Route #" << i+1 << ": " << route.at(i).at(j);
            else cout << " " << route.at(i).at(j);
        }
        cout << endl;
    }
    cout << "cost " << cost << endl;
}

#endif // INPUT_H