#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <json/json.h>
#include <cfgreader.h>

using namespace std;
int main(){
    cfgreader cfg("analysis.cfg");
    cout << cfg.json_path << endl;
    for (int i=0; i<cfg.datasets.size(); i++){
        cout << cfg.datasets[i] << endl;
    }
}