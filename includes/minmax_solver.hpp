#include <bits/stdc++.h>

#include "counting_tictac_base.hpp"
#include "transpose_table.hpp"

using namespace std;

#ifndef _MINMAX
#define _MINMAX
template<typename MoveT, typename TrTableType, size_t TrableSize>
class MiniMaxSolver : public GameTicTac<MoveT, TrTableType, TrableSize> {

	//TranspositionTable<TrTableType, TrableSize> tp_table_;
	//GameTicTac<MoveT> game_;
	public:

		MiniMaxSolver(int n) : GameTicTac<MoveT,TrTableType,TrableSize>(n) {
			//game_.Initialize(n);
		}

		int Solmaxi(int depth) {
			#if _DEBUG
			cerr << "In Solmaxi with depth: " << depth << endl;
			cerr << "Solmaxi Current state of the map:\n";
			Print_Matrix(GameTicTac<MoveT,TrTableType,TrableSize>::state_);
			cerr << "Current best move: " << GameTicTac<MoveT,TrTableType,TrableSize>::best_move.second << "with value of " << GameTicTac<MoveT,TrTableType,TrableSize>::best_move.first << endl;
			cerr << "Current scores: "; Print_pair(scores_); cerr << '\n';
			#endif

			if(depth == 0) return GameTicTac<MoveT,TrTableType,TrableSize>::EvaluateState().first - GameTicTac<MoveT,TrTableType,TrableSize>::EvaluateState().second;
			int maxi = -INF;
			FOR(i,(GameTicTac<MoveT,TrTableType,TrableSize>::n_)) {
				FOR(j,(GameTicTac<MoveT,TrTableType,TrableSize>::n_)) {
					if(GameTicTac<MoveT,TrTableType,TrableSize>::PossibleMove(MoveT{i,j})) {
						#if _DEBUG
						cerr << "Solmaxi do moves with depth : " << depth << endl;
						#endif
						GameTicTac<MoveT,TrTableType,TrableSize>::DoMove(MoveT{i,j}, true);
						int score = Solmini(depth - 1);
						maxi = std::max(maxi, score);
						GameTicTac<MoveT,TrTableType,TrableSize>::UndoMove(true);
						#if _DEBUG
						cerr << "Solmaxi Current state of the map:\n";
						Print_Matrix(GameTicTac<MoveT,TrTableType,TrableSize>::state_);
						#endif
					}
				}
			}

			if(maxi == -INF) return GameTicTac<MoveT,TrTableType,TrableSize>::EvaluateState().first - GameTicTac<MoveT,TrTableType,TrableSize>::EvaluateState().second;
			
			return maxi;
		}
		
		int Solmini(int depth) {
			#if _DEBUG
			cerr << "In Solmini with depth: " << depth << endl;
			cerr << "Solmini Current state of the map:\n";
			Print_Matrix(GameTicTac<MoveT,TrTableType,TrableSize>::state_);
			cerr << "Current best move: " << GameTicTac<MoveT,TrTableType,TrableSize>::best_move.second << "with value of " << GameTicTac<MoveT,TrTableType,TrableSize>::best_move.first << endl;
			cerr << "Current scores: "; Print_pair(scores_); cerr << '\n';
			#endif

			if(depth == 0) return GameTicTac<MoveT,TrTableType,TrableSize>::EvaluateState().first - GameTicTac<MoveT,TrTableType,TrableSize>::EvaluateState().second;
			int mini = INF;
			FOR(i,(GameTicTac<MoveT,TrTableType,TrableSize>::n_)) {
				FOR(j,(GameTicTac<MoveT,TrTableType,TrableSize>::n_)) {
					if(GameTicTac<MoveT,TrTableType,TrableSize>::PossibleMove(MoveT{i,j})) {
						#if _DEBUG
						cerr << "Solmini do moves with depth : " << depth << endl;
						#endif
						GameTicTac<MoveT,TrTableType,TrableSize>::DoMove(MoveT{i,j}, false);
						int score = Solmaxi(depth - 1);
						mini = std::min(mini, score);
						GameTicTac<MoveT,TrTableType,TrableSize>::UndoMove(false);
						#if _DEBUG
						cerr << "Solmini Current state of the map:\n";
						Print_Matrix(GameTicTac<MoveT,TrTableType,TrableSize>::state_);
						#endif
					}
				}
			}

			if(mini == INF) return GameTicTac<MoveT,TrTableType,TrableSize>::EvaluateState().first - GameTicTac<MoveT,TrTableType,TrableSize>::EvaluateState().second;

			
			return mini;
		}

		MoveT FindingBestMoveMinMax(int depth) {
			//int empty_places{0};
			//FOR(i,(GameTicTac<MoveT,TrTableType,TrableSize>::n_)) empty_places += std::count(all(GameTicTac<MoveT,TrTableType,TrableSize>::state_[i]), 0);

			FOR(i,(GameTicTac<MoveT,TrTableType,TrableSize>::n_)) {
				FOR(j,(GameTicTac<MoveT,TrTableType,TrableSize>::n_)) {
					if(GameTicTac<MoveT,TrTableType,TrableSize>::PossibleMove(MoveT{i,j})) {
						GameTicTac<MoveT,TrTableType,TrableSize>::DoMove(MoveT{i,j}, true);
						//int score = Solmini(std::min(depth - 1, empty_places - 1));
						int score = Solmini(depth - 1);

						if(GameTicTac<MoveT,TrTableType,TrableSize>::best_move.first <= score) {
							GameTicTac<MoveT,TrTableType,TrableSize>::best_move.first = score;
							GameTicTac<MoveT,TrTableType,TrableSize>::best_move.second = MoveT{i,j};
						}
						GameTicTac<MoveT,TrTableType,TrableSize>::UndoMove(true);
					}
				}
			}

			return GameTicTac<MoveT,TrTableType,TrableSize>::best_move.second;
		}	
};

#endif //_MINMAX
