/*******************************************************************************
 * Name        : powergrid.cpp
 * Author      : Byung Jeon
 * Date        : December 13, 2020
 * Description : Kruskal's Algorithm for Minimum Spanning Tree
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int find(int k, vector<int> mSet){
	if(mSet[k]==-1){
		return k;
	}
	else{
		return find(mSet[k],mSet);
	}
}

vector<vector<int>> kruskals(vector<vector<int>> sortedVector, unsigned int maxVert){
	vector<int> makeset(maxVert);
	vector<vector<int>> solution;
	for (unsigned int i=0;i<makeset.size();i++){
		makeset[i]=-1;
	}
	for (unsigned int i=0;i < sortedVector.size();i++){
		int x = sortedVector[i][0]-1;
		int y = sortedVector[i][1]-1;
		int xRoot=find(x,makeset);
		int yRoot=find(y,makeset);
		if(makeset[x]==-1 && makeset[y]==-1){
			makeset[y]=x;
			solution.push_back(sortedVector[i]);
		}
		else if(xRoot != yRoot){
			makeset[yRoot]=xRoot;
			solution.push_back(sortedVector[i]);
		}
	}
	return solution;
}

bool sort1(vector<int>&d1,vector<int>&d2){
	return d1[2]< d2[2];
}
bool sort2(vector<string>&d1,vector<string>&d2){
	return d1[0]< d2[0];
}
int displaySolution(vector<string> strName, vector<vector<int>> v, unsigned int maxV){
	vector<int> weights;
	for(unsigned int i=0; i<v.size();i++){
		weights.push_back(v[i][2]);
	}
	sort(v.begin(), v.end(),sort1);
	vector<vector<int>> sol=kruskals(v,maxV);
	if ((sol.size()+1) <maxV){
		cout<<"No solution."<<endl;
	}
	vector<vector<string>> solStrings;
	for (unsigned int i=0;i<sol.size();i++){
		vector<string> toPush;
		stringstream ss;
		ss << sol[i][2];
		string str = ss.str();
		toPush.push_back(strName[sol[i][3]]);
		toPush.push_back(str);
		ss.clear();
		solStrings.push_back(toPush);
	}
	int total=0;
		for (unsigned int i=0;i<sol.size();i++){
		total += sol[i][2];
	}
	cout<<"Total wire length (meters): "<< total<<endl;
	sort(solStrings.begin(),solStrings.end(),sort2);
	for(unsigned int i=0;i<solStrings.size();i++){
		cout<<solStrings[i][0]<<" ["<<solStrings[i][1]<<"]"<<endl;
	}
	return 0;
}


int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> lineFull;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
            lineFull.push_back(line);
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    unsigned int maxVertices;
    vector<string> streetnames;
    vector<vector<int>> successfulInts;
    for(unsigned int i=0;i<lineFull.size();i++){
    	vector<int> SuccessfulV;
    	if(lineFull.size()==2){
    		cout<<"No solution."<<endl;
    		return 0;
    	}
    	if(i==0){
    		stringstream vertices(lineFull[0]);
			int numVertices;
			vertices>>numVertices;
			vertices.clear();
			if (numVertices < 0){
				cerr<<"Error: Invalid number of vertices "<<"'"<<lineFull[i]<<"'"<< " on line "<< i+1<<"."<<endl;
				return 1;
			}
			else{
				maxVertices = numVertices;
			}
    	}
    	else{
    		vector<string> spltStrings;
    		char splt=',';
			istringstream split(lineFull[i]);
			for (string each; getline(split, each, splt);){
				spltStrings.push_back(each);
			}
			if (spltStrings.size()!=4){
				if (spltStrings.size()==3){
					cerr<<"Error: Invalid edge data '"<<spltStrings[0]<<","<<spltStrings[1]<<","<<spltStrings[2]<<"'"<< " on line "<< i+1<<"."<<endl;
					return 1;
				}
				if (spltStrings.size()==2){
					cerr<<"Error: Invalid edge data '"<<spltStrings[0]<<","<<spltStrings[1]<<"'"<< " on line "<< i+1<<"."<<endl;
					return 1;
				}
				if (spltStrings.size()==1){
					cerr<<"Error: Invalid edge data '"<<spltStrings[0]<<"'"<< " on line "<< i+1<<"."<<endl;
					return 1;
				}
			}
			stringstream vertice1(spltStrings[0]);
			unsigned int firstVertex;
			if(!(vertice1 >> firstVertex)){
				cerr<< "Error: Starting vertex "<<"'"<< spltStrings[0]<<"'"<< " on line "<<i+1<<" is not among valid values 1-"<<maxVertices<<"."<<endl;
				return 1;
			}
			if((firstVertex > maxVertices)){
				cerr<< "Error: Starting vertex "<<"'"<< firstVertex<<"'"<< " on line "<<i+1<<" is not among valid values 1-"<<maxVertices<<"."<<endl;
				return 1;
			}
			stringstream vertice2(spltStrings[1]);
			unsigned int secondVertex;
			if(!(vertice2 >> secondVertex)){
				cerr<< "Error: Ending vertex "<<"'"<< spltStrings[1]<<"'"<< " on line "<<i+1<<" is not among valid values 1-"<<maxVertices<<"."<<endl;
				return 1;
			}
			else if(secondVertex > maxVertices){
				cerr<< "Error: Ending vertex "<<"'"<< secondVertex<<"'"<< " on line "<<i+1<<" is not among valid values 1-"<<maxVertices<<"."<<endl;
				return 1;
			}
			stringstream lineWeight(spltStrings[2]);
			int weight;
			if(!(lineWeight >> weight) || (weight < 0)){
				cerr<<"Error: Invalid edge weight "<<"'"<<weight<<"'"<< " on line "<<i+1<<"."<<endl;
				return 1;
			}
			streetnames.push_back(spltStrings[3]);
			SuccessfulV.push_back(firstVertex);
			SuccessfulV.push_back(secondVertex);
			SuccessfulV.push_back(weight);
			SuccessfulV.push_back(i-1);
			successfulInts.push_back(SuccessfulV);
    	}
    }
    displaySolution(streetnames,successfulInts,maxVertices);
    return 0;
}
