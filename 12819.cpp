#include<iostream>
#include<cmath>
#include<queue>

using namespace std;

const int goalRow[] = {-1, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3};
const int goalCol[] = {-1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2};

class State{
    public:
        int puzzle[4][4];
        int heuristic;
        int currentMove;
        int prevMove;
        int ex,ey;//empty tile

        State(int puzzle[4][4]){
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    this->puzzle[i][j] = puzzle[i][j];
                }
            }
            ex = -1;
            ey = -1;
            currentMove = 0;
            prevMove = -1;
            
        }
        State(const State& s) {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    puzzle[i][j] = s.puzzle[i][j];
            currentMove = s.currentMove;
            prevMove = s.prevMove;
            ex = s.ex;
            ey = s.ey;
            heuristic = s.heuristic;
        }
        void setHeuristic(){
            int h=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    if(puzzle[i][j]){
                        int goalX = goalRow[puzzle[i][j]];
                        int goalY = goalCol[puzzle[i][j]];
                        //Manhattan distance
                        h += abs(goalX-i) + abs(goalY-j);

                        //Linear Conflict*2
                        if(i==goalX){
                            
                        }

                    }

                }
            }
        }
};

int main(void){



    return 0;
}