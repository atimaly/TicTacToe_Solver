#include <bits/stdc++.h>

#include "minmax_solver.hpp"

using namespace std;

int main() {
	//int n; cin >> n;
	/*
	GameTicTac<Move> g(3);
	g.PrintData();
	g.DoMove(Move{1,1}, true);
	g.PrintData();
	g.DoMove(Move{0,2}, true);
	g.DoMove(Move{2,0}, true);
	g.DoMove(Move{0,0}, false);
	g.PrintData();
	g.UndoMove(false);
	g.UndoMove(true);
	g.PrintData();
	g.FindingBestMove(2);
	g.PrintData();
	*/
	/*
	int n = 4;
	GameTicTac<Move> g_2(n);
	//g_2.OptimalGamePlay(true);
	while(!g_2.IsGameOver()) {
		cout << "Give me the move: " << endl;
		int x,y; cin >> x >> y;
		g_2.DoMove(Move{x,y}, false);
		g_2.FindingBestMoveMinMax(5);
		cout << "\n---------DO BEST MOVE FOR AI BEGIN-----------\n";
		//cout << "current bet move's score is: " << g_2.best_move.first << endl;
		//g_2.DoMove(g_2.best_move.second, true);
		//g_2.best_move = pair<int, Move>{-INF, Move{0,0}};
		pair<int, Move> b_m = g_2.BestMoveCurr();
		cout << "Current best move is: " << b_m.second << " with value of " << b_m.first << endl;
		g_2.PlayingBestMove(true);
		cout << "\n---------DO BEST MOVE FOR AI END-----------\n";
		g_2.PrintData();
	}
	*/
	
	int n = 3; cout << "Give me the size(n*n) of the Tic Tac Toe game: n = "; cin >> n;
	MiniMaxSolver<Move, TrTEntry<Move>, 100> test(n);
	

	while(!test.IsGameOver()) {
		cout << "Give me the move: " << endl;
		int x,y; cin >> x >> y;
		test.DoMove(Move{x,y}, false);
		test.FindingBestMoveMinMax(5);
		cout << "\n---------DO BEST MOVE FOR AI BEGIN-----------\n";
		//cout << "current bet move's score is: " << test.best_move.first << endl;
		//test.DoMove(test.best_move.second, true);
		//test.best_move = pair<int, Move>{-INF, Move{0,0}};
		pair<int, Move> b_m = test.BestMoveCurr();
		cout << "Current best move is: " << b_m.second << " with value of " << b_m.first << endl;
		test.PlayingBestMove(true);
		cout << "\n---------DO BEST MOVE FOR AI END-----------\n";
		test.PrintData(true);

	}
	
}
