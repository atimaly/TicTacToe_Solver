 #include <algorithm>
 #include <bits/stdc++.h>
#include <cstddef>
#include <cstdint>
 #include <random>
  
#include "utility.hpp"
#include "transpose_table.hpp"

using namespace std;

#ifndef _GAMETICTAC
#define _GAMETICTAC
struct Move{
    int x,y;

	friend ostream& operator<<(std::ostream &os, const Move &m) {
		os << " ("<< m.x << ", " << m.y << ") ";
		return os;
	}
};
 
template<typename MoveT, typename TrTableType, size_t TrableSize>
class GameTicTac{
    //Maximizer is always me

	protected:
		int n_;
		vector<vector<int>> state_; //0 means empty, 1 means my sign, 2 enemy sign
		pair<double, double> scores_{0,0}; //first is me 
		vector<MoveT> moves_;
		pair<int,MoveT> best_move{-INF, MoveT{0,0}};
		const int window_{5};
		vector<vector<uint64_t>> zobrist_map;

		TranspositionTable<TrTableType, TrableSize> tp_table_;
		
	public:
		GameTicTac(int n) : n_{n} {
			assert(n >= 1); state_.resize(n, vector<int>(n, 0));
			InitializeZobristMap();
		}

		void Initialize(int n) {
			n_ = n;
			assert(n >= 1); 
			state_.resize(n_, vector<int>(n_, 0));
		}
		
		void InitializeZobristMap(int range_of_value = 10000) {
			//For every entry of the game assigns a random int number between 1 and range_of_value
			zobrist_map.resize(n_, vector<uint64_t>(n_, 0));
			std::random_device rd;  //Will be used to obtain a seed for the random number engine
			std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
			std::uniform_int_distribution<> distrib(1, range_of_value);
			for(auto &v : zobrist_map) for(auto &u : v) u = distrib(gen); 
		}

		uint64_t ZobristHashValue() {
			//Calculates the current states Zborist hash value
			//
			uint64_t value{0};
			FOR(i,n_) {
				FOR(j,n_) {
					switch (state_[i][j]) {
						case 1:
							value ^= zobrist_map[i][j];
							break;
						case 2:
							value ^= 3*zobrist_map[i][j];
					}
				}
			}
			return value;
		}

		bool ValidIndex(int x, int y) {
			if(x < 0 || x >= n_) return false;
			if(y < 0 || y >= n_) return false;
			return true;
		}

		double CalcMoveScore(const MoveT &m, bool maximizer) {
			double mv_score{0};

			#if _DEBUG
			cerr << "\tThe move to CalcMoveScore: ";
			cerr << m;
			#endif
			/*
			map<pair<int,int>,bool> possible_pos;
			FORG(i, -2, 2) {
				FORG(j, -2, 2) {
					if((i == j || i == -j) && i != 0) 
						if(ValidIndex(m.x + i, m.y + j) && state_[m.x + i][m.y + j] == state_[m.x][m.y]) 
							possible_pos[std::make_pair(m.x + i, m.y + j)] = true;
				}
			}
			*/
			pair<int,int> middle{2, 2};
			vector<vector<bool>> possible_pos(window_, vector<bool>(window_, false));
			FORG(i, -2, 2) {
				FORG(j, -2, 2) {
					if(ValidIndex(m.x + i, m.y + j)) {
						if(state_[m.x + i][m.y + j] == state_[m.x][m.y])
							possible_pos[middle.first + i][middle.second + j] = true;
					}
				}
			}

			#if _DEBUG
			cerr << "\t\nPossible Positions:\n";
			/*for(auto &[v, p] : possible_pos) {
				cerr << "Pos: " << v.first << ", " << v.second << ", possibility: " << p << '\n';
			}*/
			/*
			FOR(i,5) {
				FOR(j,5) {
					cerr << "Pos: " << i << ", " << j << ", possibility: " << possible_pos[i][j] << "\n";
				}
			}
			*/
			for(auto &v : possible_pos) {
				for(auto u : v) {
					cerr << u << " ";
				}
				cerr << endl;
			}
			cerr << "End of listing\n";
			#endif
			
			if(possible_pos[middle.first - 2][middle.second - 2] && possible_pos[middle.first - 1][middle.second - 1] ) ++mv_score; //lu left upper
			if(possible_pos[middle.first + 2][middle.second + 2] && possible_pos[middle.first + 1][middle.second + 1] ) ++mv_score; //rl right lower

			if(possible_pos[middle.first + 2][middle.second - 2] && possible_pos[middle.first + 1][middle.second - 1] ) ++mv_score; //left low
			if(possible_pos[middle.first - 2][middle.second + 2] && possible_pos[middle.first - 1][middle.second + 1] ) ++mv_score; //right upp

			if(possible_pos[middle.first - 1][middle.second] && possible_pos[middle.first - 2][middle.second] ) ++mv_score; //vertical upp
			if(possible_pos[middle.first + 1][middle.second] && possible_pos[middle.first + 2][middle.second] ) ++mv_score; //vertical low

			if(possible_pos[middle.first][middle.second -1] && possible_pos[middle.first][middle.second - 2] ) ++mv_score; //horizontal left
			if(possible_pos[middle.first][middle.second + 1] && possible_pos[middle.first][middle.second + 2] ) ++mv_score; //horizontal right

			if(possible_pos[middle.first + 1][middle.second + 1] && possible_pos[middle.first - 1][middle.second - 1] ) ++mv_score; //middle is move
			if(possible_pos[middle.first + 1][middle.second - 1] && possible_pos[middle.first - 1][middle.second + 1] ) ++mv_score; //middle is move
			if(possible_pos[middle.first][middle.second - 1] && possible_pos[middle.first][middle.second + 1] ) ++mv_score; //middle is move
			if(possible_pos[middle.first + 1][middle.second] && possible_pos[middle.first - 1][middle.second] ) ++mv_score; //middle is move


			return mv_score;
		}

		void DoMove(const MoveT &m, bool maximizer) {
			#if _DEBUG
			cerr << "DoMove for: " << maximizer << endl;
			#endif
			#if _FIGHTTEST
			assert(state_[m.x][m.y] == 0);
			#endif
			if(maximizer) {
				state_[m.x][m.y] = 1;
				scores_.first += CalcMoveScore(m, maximizer);
			}
			else {
				state_[m.x][m.y] = 2;
				scores_.second += CalcMoveScore(m, maximizer);
			}
			
			moves_.push_back(m);
		}

		void UndoMove(bool maximizer) {
			#if _DEBUG
			cerr << "UndoMove for: " << maximizer << endl;
			#endif
			int m_s = static_cast<int>(moves_.size());
			assert(m_s >= 1);
			MoveT v = moves_[m_s-1];
			if(maximizer) scores_.first -= CalcMoveScore(v, maximizer);
			else scores_.second  -= CalcMoveScore(v, maximizer);

			state_[v.x][v.y] = 0;
			moves_.pop_back();
		}

		pair<double, double> EvaluateState() {
			return scores_;
		}

		bool PossibleMove(const MoveT &m) {
			if(state_[m.x][m.y] == 0) return true;
			return false;
		}

		vector<pair<int,int>> PossibleMoves() const {
			vector<pair<int,int>> ps;
			FOR(i,n_) {
				FOR(j,n_) {
					if(state_[i][j] == 0) ps.push_back(make_pair(i,j));
				}
			}
			return ps;
		}

		pair<int, MoveT> BestMoveCurr() {
			return best_move;
		}

		void PlayingBestMove(bool maximizer) {
			DoMove(best_move.second, maximizer);
			best_move = pair<int, MoveT>{-INF, MoveT{0,0}};
		}


		bool IsGameOver() {
			int empty_places{0};
			FOR(i,n_) empty_places += std::count(all(state_[i]), 0);
			return empty_places == 0 ? true : false;
		}

		
		void PrintData(std::ostream& os = std::cerr) {
			os << "\n\n-----------------PRINTDATA BEGIN----------------\n";
			os << "State of the game:\n";
			Print_Matrix(state_, os);
			os << "The current score is "; Print_pair(scores_, os);
			os << "\nCurrent move list is: "; Print_vector(moves_, os);
			os << "Current best move is: " << best_move.second << " with value of: " << best_move.first << '\n';
			os << "The Zobrist Map:\n";
			Print_Matrix(zobrist_map);
			os << "Zobrist hash value of the state_: " << ZobristHashValue() << endl;
			os << "\n\n-----------------PRINTDATA END----------------\n";
		}
};
#endif //_GAMETICTAC



