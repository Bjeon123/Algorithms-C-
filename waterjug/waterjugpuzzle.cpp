/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Byung Jeon 
 * Date        : 10/16/2020
 * Description : Solves the infamous waterjug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

vector<string> directionsv;
void display_solution(State* solution){
	if (solution == nullptr){
		for (unsigned int i=0; i < directionsv.size(); i++){
			cout<< directionsv[i] << endl;
		};
	}
	else{
		string direction = solution->directions +  " " + solution->to_string();
		directionsv.insert(directionsv.begin(),direction);
		display_solution(solution->parent);
	}
}


bool waterjug_solution(State initial, State goal, State capacities){
	State* **visited = new State**[(capacities.a)+1];
		for(int i=0;i<(capacities.a)+1;++i){
			visited[i]=new State*[(capacities.b)+1];
			for(int j=0;j<(capacities.b)+1;j++){
			visited[i][j]=nullptr;
		}
	}
	queue<State*> q;
	q.push(&initial);
	while (!q.empty()){
		State* current = q.front();
		if ((current->a == goal.a)&&(current->b == goal.b)&&(current->c==goal.c)){
			display_solution(current);
			return true;
			break;
		}
		//1) pour C to A
		if ((current->a < capacities.a) && (current->c > 0)){
			int remaining_in_jug= capacities.a - current->a;
			if ((current->a + current->c)<=capacities.a){
				if (visited[current->a + current->c][current->b]==nullptr){
					string direction;
					if (current->c ==1){
						direction ="Pour "+ to_string(current->c) +" gallon from C to A.";
					}
					else{
						direction ="Pour "+ to_string(current->c) +" gallons from C to A.";
					}
					State *newJug = new State((current->a + current->c),current->b,0,direction);
					newJug-> parent = (current);
					visited[current->a + current->c][current->b]=newJug;
					q.push(newJug);
				}
			}
			else if(current->a + current->c > capacities.a){
				if (visited[capacities.a][current->b]==nullptr){
					string direction;
					if (remaining_in_jug ==1){
						direction ="Pour "+ to_string(remaining_in_jug) +" gallon from C to A.";
					}
					else{
						direction ="Pour "+ to_string(remaining_in_jug) +" gallons from C to A.";
					}
					State *newJug = new State((capacities.a),current->b,((current->c)-remaining_in_jug),direction);
					newJug -> parent = (current);
					visited[capacities.a][current->b]=newJug;
					q.push(newJug);
				}
			}
		}
		//2) pour B to A
		if ((current->a < capacities.a) && (current->b > 0)){
			int remaining_in_jug= capacities.a-current->a;
			if ((current->a + current->b)<=capacities.a){
				if (visited[current->a + current->b][0]==nullptr){
					string direction;
					if (current->b ==1){
						direction ="Pour "+ to_string(current->b) +" gallon from B to A.";
					}
					else{
						direction ="Pour "+ to_string(current->b) +" gallons from B to A.";
					}
					State *newJug = new State((current->a + current->b),0,current->c,direction);
					newJug->parent=(current);
					visited[current->a + current->b][0]=newJug;
					q.push(newJug);
				}
			}
			else if(current->a + current->b > capacities.a){
				if (visited[capacities.a][current->b-remaining_in_jug]==nullptr){
					string direction;
					if (remaining_in_jug ==1){
						direction ="Pour "+ to_string(remaining_in_jug) +" gallon from B to A.";
					}
					else{
						direction ="Pour "+ to_string(remaining_in_jug) +" gallons from B to A.";
					}
					State *newJug = new State((capacities.a),(current->b - remaining_in_jug),current->c,direction);
					newJug->parent=(current);
					visited[capacities.a][current->b - remaining_in_jug]=newJug;
					q.push(newJug);
				}
			}
		}
		//3) pour C to B
		if ((current->b < capacities.b) && (current->c > 0)){
			int remaining_in_jug= capacities.b - current-> b;
			if ((current->c + current->b)<=capacities.b){
				if (visited[current->a][current->c + current->b]==nullptr){
					string direction;
					if (current->c==1){
						direction ="Pour "+ to_string(current->c) +" gallon from C to B.";
					}
					else{
						direction ="Pour "+ to_string(current->c) +" gallons from C to B.";
					}
					State *newJug = new State((current->a),(current->c + current->b),0,direction);
					newJug->parent=(current);
					visited[current->a][current->c + current->b]=newJug;
					q.push(newJug);
				}
			}
			else if(current->c + current->b > capacities.b){
				if (visited[current->a][capacities.b]==nullptr){
					string direction;
					if(remaining_in_jug==1){
						direction ="Pour "+ to_string(remaining_in_jug) +" gallon from C to B.";
					}
					else{
						direction ="Pour "+ to_string(remaining_in_jug) +" gallons from C to B.";
					}
					State *newJug = new State((current->a),capacities.b,(current->c-remaining_in_jug),direction);
					visited[current->a][capacities.b]=newJug;
					newJug->parent=(current);
					q.push(newJug);
				}
			}
		}
		//4) Pour A to B
		if ((current->b < capacities.b) && (current->a > 0)){
			int remaining_in_jug= capacities.b- (current->b);
			if ((current->b + current->a)<=capacities.b){
				if (visited[0][current->b +current->a]==nullptr){
					string direction;
					if(current->a==1){
						direction ="Pour "+ to_string(current->a) +" gallon from A to B.";
					}
					else{
						direction ="Pour "+ to_string(current->a) +" gallons from A to B.";
					}
					State *newJug = new State(0,(current->a + current->b),current->c,direction);
					visited[0][current->a + current->b]=newJug;
					newJug->parent=(current);
					q.push(newJug);
				}
			}
			else if(current->a + current->b > capacities.b){
				if (visited[current-> a-remaining_in_jug][capacities.b]==nullptr){
					string direction;
					if(remaining_in_jug==1){
						direction = "Pour "+ to_string(remaining_in_jug) +" gallon from A to B.";
					}
					else{
						direction = "Pour "+ to_string(remaining_in_jug) +" gallons from A to B.";
					}
					State *newJug = new State((current->a-remaining_in_jug),capacities.b,current->c,direction);
					visited[(current->a-remaining_in_jug)][capacities.b]=newJug;
					newJug->parent=(current);
					q.push(newJug);
				}
			}
		}
		//5) Pour B to C
		if ((current->c < capacities.c) && (current->b > 0)){
			int remaining_in_jug= capacities.c-current->c;
			if ((current->b + current->c)<=capacities.c){
				if (visited[current->a][0]==nullptr){
					string direction;
					if (current->b==1){
						direction ="Pour "+ to_string(current->b) +" gallon from B to C.";
					}
					else{
						direction ="Pour "+ to_string(current->b) +" gallons from B to C.";
					}
					State *newJug=new State((current->a),0,(current->c + current->b),direction);
					visited[current->a][0]=newJug;
					newJug->parent=(current);
					q.push(newJug);
				}
			}
			else if(current->b + current->c > capacities.c){
				if (visited[current->a][current->b-remaining_in_jug]==nullptr){
					string direction;
					if (remaining_in_jug==1){
						direction ="Pour "+ to_string(remaining_in_jug) +" gallon from B to C.";
					}
					else{
						direction ="Pour "+ to_string(remaining_in_jug) +" gallons from B to C.";
					}
					State *newJug=new State((current->a),(current->b-remaining_in_jug),(capacities.c),direction);
					visited[current->a][current->b-remaining_in_jug]=newJug;
					newJug->parent=(current);
					q.push(newJug);
				}
			}
		}
		//6) Pour A to C
		if ((current->c < capacities.c) && (current->a > 0)){
			int remaining_in_jug= capacities.c-current->c;
			if ((current->a + current->c)<=capacities.c){
				if (visited[0][current->b]==nullptr){
					string direction;
					if (current->a==1){
						direction ="Pour "+ to_string(current->a) +" gallon from A to C.";
					}
					else{
						direction ="Pour "+ to_string(current->a) +" gallons from A to C.";
					}
					State *newJug=new State(0 ,current->b ,(current->c +current->a),direction);
					visited[0][current->b]=newJug;
					newJug->parent=(current);
					q.push(newJug);
				}
			}
			else if(current->a + current->c > capacities.c){
				if (visited[current->a - remaining_in_jug][current->b]==nullptr){
					string direction;
					if(remaining_in_jug==1){
						direction ="Pour "+ to_string(remaining_in_jug) +" gallon from A to C.";
					}
					else{
						direction ="Pour "+ to_string(remaining_in_jug) +" gallons from A to C.";
					}
					State *newJug=new State((current->a-remaining_in_jug),current->b,(capacities.c),direction);
					visited[current->a-remaining_in_jug][current->b]=newJug;
					newJug->parent=(current);
					q.push(newJug);
				}
			}
		}
		q.pop();
	}
	cout<<"No solution.";
	return false;
}



int main(int argc,char * const argv[]) {
	if (argc != 7){
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	int check;
	int check2;
	istringstream iss(argv[3]);
	iss >>check;
	if (check == 0){
		cerr << "Error: Invalid capacity '0' for jug C." << endl;
		return 1;
	}
	iss.clear();
	for (int i=1; i<=6; i++){
		istringstream iss(argv[i]);
		if((!(iss >> check)) || check < 0){
			if(i==1){
				cerr << "Error: Invalid capacity " <<"'"<< argv[i] <<"'"<< " for jug A." << endl;
				return 1;
			}
			if(i==2){
				cerr << "Error: Invalid capacity " <<"'"<< argv[i] <<"'"<< " for jug B."<< endl;
				return 1;
			}
			if(i==3){
				cerr << "Error: Invalid capacity " <<"'"<< argv[i] <<"'"<< " for jug C."<< endl;
				return 1;
			}
			if(i==4){
				cerr << "Error: Invalid goal " <<"'"<< argv[i] <<"'"<< " for jug A." << endl;
				return 1;
			}
			if(i==5){
				cerr << "Error: Invalid goal " <<"'"<< argv[i] <<"'"<< " for jug B." << endl;
				return 1;
			}
			if(i==6){
				cerr << "Error: Invalid goal " <<"'"<< argv[i] <<"'"<< " for jug C." << endl;
				return 1;
			}
		}
		iss.clear();
	}
	for (int i=1; i<=3;i++){
		istringstream iss1(argv[i]);
		istringstream iss2(argv[i+3]);
		iss1 >> check;
		iss2 >> check2;
		if (i==1 && (check2 > check)){
			cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
			return 1;
		}
		if (i==2 && (check2 > check)){
			cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
			return 1;
		}
		if (i==3 && (check2 > check)){
			cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
			return 1;
		}
		iss1.clear();
		iss2.clear();
	}

	int goal1;
	int goal2;
	int goal3;
	int capC;
	istringstream iss1(argv[4]);
	istringstream iss2(argv[5]);
	istringstream iss3(argv[6]);
	istringstream iss4(argv[3]);
	iss1 >> goal1;
	iss2 >> goal2;
	iss3 >> goal3;
	iss4 >> capC;
	if ((goal1 + goal2 + goal3)!=capC){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C."<<endl;
		return 1;
	}
	int capB;
	int capA;

	istringstream iss5(argv[1]);
	istringstream iss6(argv[2]);
	iss5 >> capA;
	iss6 >> capB;

	State initial(0,0,capC,"Initial state.");
	State caps(capA,capB,capC,"capacities");
	State goal(goal1,goal2,goal3,"end");

	waterjug_solution(initial,goal,caps);
}
