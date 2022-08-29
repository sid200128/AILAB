#include <bits/stdc++.h>

using namespace std;

vector<vector<vector<char>>> ans;

class Solution{
public:
    int evaluate(vector<vector<char>> board) {
        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
                if (board[row][0] == 'x') return 10;
                else if (board[row][0] == 'o') return -10;
            }
        }
        
        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
                if (board[0][col] == 'x') return 10;
                else if (board[0][col] == 'o') return -10;
            }
        }
        
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == 'x') return 10;
            else if (board[0][0] == 'o') return -10;
        }
        
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == 'x') return 10;
            else if (board[0][2] == 'o') return -10;
        }
    
        return 0;    
    }
    bool isMoveLeft(vector<vector<char>> board) {
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                if (board[i][j] == '_') return true;
            }
        }
        return false;
    }
    pair<vector<vector<int>>, int> minimax(vector<vector<char>> board, int depth, bool isMaximizer) {
        
        int score = evaluate(board);

        if (score == 10) {
            return {{}, score};
        }
        
        if (score == -10) {
            return {{}, score};
        }
        
        if (!isMoveLeft(board)) {
            return {{}, 0};
        }

        vector<int> move;
        vector<vector<int>> moves;


        if (isMaximizer) {
            int bestVal = INT32_MIN;
            for (int i = 0; i<3; i++) {
                for (int j = 0; j<3; j++) {
                    if (board[i][j] == '_') {
                        board[i][j] = 'x';
                        
                        pair<vector<vector<int>>, int> nextMove = minimax(board, depth+1, !isMaximizer);
                        int value = nextMove.second;

                        if (value > bestVal) {
                            moves = nextMove.first;
                            move = {i, j};
                        }
                        
                        bestVal = max(bestVal, value);
                        // alpha = max(alpha, bestVal);
                        // if (beta <= alpha) break;
                        board[i][j] = '_';
                    }
                }
            }
            moves.push_back(move);
            return {moves, bestVal};
        }

        int bestVal = INT32_MAX;
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'o';

                    pair<vector<vector<int>>, int> nextMove = minimax(board, depth+1, !isMaximizer);
                    int value = nextMove.second;

                    if (value < bestVal) {
                        moves = nextMove.first;
                        move = {i, j};
                    }

                    bestVal = min(bestVal, value);
                    // beta = min(beta, bestVal);
                    // if (beta <= alpha) break;
                    board[i][j] = '_';
                }
            }
        }
        moves.push_back(move);
        return {moves, bestVal};
    }
    vector<vector<int>> findBestMove(vector<vector<char>> board){
        vector<vector<int>> moves;
        vector<int> move;
        int bestVal = INT32_MIN;
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'x';
                    pair<vector<vector<int>>, int> nextMove = minimax(board, 0, false);
                    int curr = nextMove.second;
                    // int curr = minimax(board, 0, false);
                    if (curr > bestVal) {
                        moves = nextMove.first;
                        move = {i, j};
                        bestVal = curr;
                    }
                    board[i][j] = '_';
                }
            }
        }
        moves.push_back(move);
        return moves;
    }
};

//{ Driver Code Starts.

int main(){
    int t;
    cin>>t;
    while(t--){
        vector<vector<char>> board(3, vector<char> (3));
        for(int i = 0;i < 3;i++)
            cin>>board[i][0]>>board[i][1]>>board[i][2];
        
        Solution ob;
        vector<vector<int>> ans = ob.findBestMove(board);
        bool player = true;
        for (int i = ans.size()-1; i>=0; --i) {
            int x = ans[i][0], y = ans[i][1];
            if (player) {
                board[x][y] = 'x';
            } else {
                board[x][y] = 'o';
            }
            cout << "  |" << endl;
            cout << (player ? " MAX" : " MIN") << endl;
            cout << "  V" << endl;
            for (int i = 0; i < 3; i++) {
                cout << board[i][0] << " " << board[i][1] << " " << board[i][2] << endl;
            }
            player = !player;
        }
    }
    return 0;
}