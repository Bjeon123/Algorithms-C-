/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Anthony Grillo III
 * Date        : 10/02/2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
  vector <vector <int>> ways, result;
  if(num_stairs <= 0){
		ways.push_back(vector<int>());
		return ways;
	}
  else{
    for(int i=1; i<=3; i++){
			if(num_stairs >= i){
				result = get_ways(num_stairs - i);
				for(unsigned int j = 0;j < result.size();j++){
					result[j].push_back(i);
					ways.push_back(result[j]);
				}

			}
		}
		return ways;

  }
}

void display_ways(const vector< vector<int> > &ways) {
  int width;
  int n;
	for(unsigned int i = 0; i < ways.size(); i++){
		n = ways.size();
		width = 1;
		while(n >= 10){
			width++;
			n = n/10;
		}
		cout<<setw(width)<<i+1<< ". "<< "[";
		for(unsigned int j = ways[i].size()-1;j >= 1;j--){
			cout<<ways[i][j] << ", ";
		}
		cout<<ways[i][0] << "]"<<endl;
	}

}


int main(int argc, char * const argv[]) {
  if(argc != 2){
		cerr<<"Usage: ./stairclimber <number of stairs>"<< endl;
		return 1;
	}
  int num_stairs;
  istringstream iss(argv[1]);
  if(!(iss >> num_stairs) || num_stairs < 1) {
    cerr<<"Error: Number of stairs must be a positive integer."<<endl;
    return 1;
  }
  vector <vector<int>> ways = get_ways(num_stairs);
  if(ways.size() == 1){
		cout<<ways.size() <<" way to climb " <<num_stairs<< " stair."<<endl;
  }else{
		cout <<ways.size() <<" ways to climb "<<num_stairs<<" stairs."<<endl;
  }
  display_ways(ways);
  return 0;
}
