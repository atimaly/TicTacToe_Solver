#include <algorithm>
#include <bits/stdc++.h>
#include <random>

using namespace std;

using ll = long long int;

const int INF = std::numeric_limits<int>::max();
const bool DEBUG = true;

#define all(x) begin(x), end(x)
#define FOR(i,n) for(int i = 0; i < (n); ++i)
#define FORO(i,n) for(int i = 1; i < (n); ++i)
#define FORG(i,a,b) for(int i = (a); i <= (b); ++i)

template <class C>
void Print_vector(const C &Original, std::ostream &os = std::cerr) {
	for(const auto &v : Original) {
	    os << v << " ";
	}
	os << endl;
}

template <class C>
void Print_Matrix(const C &M, std::ostream &os = std::cerr) {
	for(auto &v : M) {
		for(auto &u : v) {
			os << u << " ";            
			}
	    os << endl;
	}
}

template<class T>
void Print_pair(const T &M, std::ostream &os = std::cerr) {
    os << "(" << M.first << " , " << M.second << " ) ";
}

template <class C>
void Print_vector_pairs(const C &Original, std::ostream &os = std::cerr) {
	for(const auto &v : Original) {
	    Print_pair(v, os);
	}
	os << endl;
}

template <class C>
void Print_vector_pairs_raw(const C &Original, std::ostream &os = std::cerr) {
	for(const auto &v : Original) {
	    os << v.first << " " << v.second << " ";
	}
	os << endl;
}

template<typename MoveT>
struct TrTEntry{

	uint64_t hash_key;
	uint16_t value_pos;
	MoveT opt_move;

};

template<typename T, size_t S>
class TranspositionTable{
	std::array<T, S> table_;
};

struct Move{
    int x,y;

	friend ostream& operator<<(std::ostream &os, const Move &m) {
		os << " ("<< m.x << ", " << m.y << ") ";
		return os;
	}
};

template<typename MoveT>
class GameTicTac{
    //Maximizer is always me

	public:
		int n_;
		vector<vector<int>> state_; //0 means empty, 1 means my sign, 2 enemy sign
		pair<double, double> scores_{0,0}; //first is me 
		vector<MoveT> moves_;
		pair<int,MoveT> best_move{-INF, MoveT{0,0}};


		GameTicTac(int n) : n_{n} {assert(n >= 1); state_.resize(n, vector<int>(n, 0));}

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
			
			map<pair<int,int>,bool> possible_pos;
			FORG(i, -2, 2) {
				FORG(j, -2, 2) {
					if((i == j || i == -j) && i != 0) 
						if(ValidIndex(m.x + i, m.y + j) && state_[m.x + i][m.y + j] == state_[m.x][m.y]) 
							possible_pos[std::make_pair(m.x + i, m.y + j)] = true;
				}
			}


			#if _DEBUG
			cerr << "\tPossible Positions:\n";
			for(auto &[v, p] : possible_pos) {
				cerr << "Pos: " << v.first << ", " << v.second << ", possibility: " << p << '\n';
			}
			#endif
			
			
			if(possible_pos[std::make_pair(m.x - 2, m.y - 2)] && possible_pos[std::make_pair(m.x - 1, m.y - 1)] ) ++mv_score;
			if(possible_pos[std::make_pair(m.x + 2, m.y + 2)] && possible_pos[std::make_pair(m.x + 1, m.y + 1)] ) ++mv_score;

			if(possible_pos[std::make_pair(m.x + 2, m.y - 2)] && possible_pos[std::make_pair(m.x + 1, m.y - 1)] ) ++mv_score;
			if(possible_pos[std::make_pair(m.x - 2, m.y + 2)] && possible_pos[std::make_pair(m.x - 1, m.y + 1)] ) ++mv_score;

			if(possible_pos[std::make_pair(m.x + 1, m.y + 1)] && possible_pos[std::make_pair(m.x - 1, m.y - 1)] ) ++mv_score;
			if(possible_pos[std::make_pair(m.x + 1, m.y - 1)] && possible_pos[std::make_pair(m.x - 1, m.y + 1)] ) ++mv_score;


			return mv_score;
		}

		void DoMove(const MoveT &m, bool maximizer) {
			#if _DEBUG
			cerr << "DoMove for: " << maximizer << endl;
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

		int Solmaxi(int depth) {
			#if _DEBUG
			cerr << "In Solmaxi with depth: " << depth << endl;
			cerr << "Solmaxi Current state of the map:\n";
			Print_Matrix(state_);
			cerr << "Current best move: " << best_move.second << "with value of " << best_move.first << endl;
			cerr << "Current scores: "; Print_pair(scores_); 
			#endif

			if(depth == 0) return EvaluateState().first - EvaluateState().second;
			int maxi = -INF;
			FOR(i, n_) {
				FOR(j, n_) {
					if(PossibleMove(MoveT{i,j})) {
						#if _DEBUG
						cerr << "Solmaxi do moves with depth : " << depth << endl;
						#endif
						DoMove(MoveT{i,j}, true);
						int score = Solmini(depth - 1);
						maxi = std::max(maxi, score);
						UndoMove(true);
						#if _DEBUG
						cerr << "Solmaxi Current state of the map:\n";
						Print_Matrix(state_);
						#endif
					}
				}
			}
			
			return maxi;
		}
	
		int Solmini(int depth) {
			#if _DEBUG
			cerr << "In Solmini with depth: " << depth << endl;
			cerr << "Solmini Current state of the map:\n";
			Print_Matrix(state_);
			cerr << "Current best move: " << best_move.second << "with value of " << best_move.first << endl;
			cerr << "Current scores: "; Print_pair(scores_);
			#endif

			if(depth == 0) return EvaluateState().first - EvaluateState().second;
			int mini = INF;
			FOR(i, n_) {
				FOR(j, n_) {
					if(PossibleMove(MoveT{i,j})) {
						#if _DEBUG
						cerr << "Solmini do moves with depth : " << depth << endl;
						#endif
						DoMove(MoveT{i,j}, false);
						int score = Solmaxi(depth - 1);
						mini = std::min(mini, score);
						UndoMove(false);
						#if _DEBUG
						cerr << "Solmini Current state of the map:\n";
						Print_Matrix(state_);
						#endif
					}
				}
			}
			
			return mini;
		}

		MoveT FindingBestMove(int depth) {
			FOR(i, n_) {
				FOR(j, n_) {
					if(PossibleMove(MoveT{i,j})) {
						DoMove(MoveT{i,j}, true);
						int score = Solmini(depth - 1);
						if(best_move.first <= score) {
							best_move.first = score;
							best_move.second = MoveT{i,j};
						}
						UndoMove(true);
					}
				}
			}

			return best_move.second;
		}


		void OptimalGamePlay(bool starter_maxim) {
			//starter_maxim is true if the starting player is the maximizer (me)
			int depth = 1;
			FOR(_i,n_*n_) {
				Solmaxi(depth);
				#if _DEBUG
				cerr << "Current best move for: " << starter_maxim << " is " << best_move.second << " with value of " << best_move.first << '\n';
				#endif
				DoMove(best_move.second, starter_maxim);
				best_move = pair<int, MoveT>{-INF, MoveT{0,0}};
				starter_maxim = !starter_maxim;
				#if _DEBUG
				cerr << "Current state of the map:\n";
				Print_Matrix(state_);
				#endif
			}

		}
		
		void PrintData(std::ostream& os = std::cerr) {
			os << "\n\n-----------------PRINTDATA BEGIN----------------\n";
			os << "State of the game:\n";
			Print_Matrix(state_, os);
			os << "The current score is "; Print_pair(scores_, os);
			os << "\nCurrent move list is: "; Print_vector(moves_, os);
			os << "Current best move is: " << best_move.second << " with value of: " << best_move.first << '\n';
			os << "\n\n-----------------PRINTDATA END----------------\n";
		}
};

template<typename MoveT, typename TrTableType, size_t TrableSize>
class MiniMaxSolver : public GameTicTac<MoveT> {

	TranspositionTable<TrTableType, TrableSize> tp_table_;
/*	
	int Solmaxi(int depth) {
		if(depth == 0) return GameTicTac<MoveT>::EvaluateState().first;
		int maxi = -INF;
		FOR(i, GameTicTac<MoveT>::n_) {
			FOR(j, GameTicTac<MoveT>::n_) {
				if(PossibleMove(MoveT{i,j})) {
					DoMove(MoveT{i,j}, true);
					int score = Solmini(depth - 1);
					if(best_move.first < score) {
						best_move.first = score;
						best_move.second = MoveT{i,j};
					}
					maxi = std::max(maxi, score);
					UndoMove(MoveT{i,j}, true);
				}
			}
		}
		
		return maxi;
	}
	
	int Solmini(int depth) {
		if(depth == 0) return GameTicTac<MoveT>::EvaluateState().first;
		int mini = INF;
		FOR(i, GameTicTac<MoveT>::n_) {
			FOR(j, GameTicTac<MoveT>::n_) {
				if(PossibleMove(MoveT{i,j})) {
					DoMove(MoveT{i,j}, false);
					int score = Solmaxi(depth - 1);
					mini = std::min(mini, score);
					UndoMove(MoveT{i,j}, false);
				}
			}
		}
		
		return mini;
	}
	*/
	//AlphaBetaSolver() {}
	/*
	int maxi( int depth ) {
    if ( depth == 0 ) return evaluate();
    int max = -oo;
    for ( all moves) {
        score = mini( depth - 1 );
        if( score > max )
            max = score;
    }
    return max;
	}

	int mini( int depth ) {
		if ( depth == 0 ) return -evaluate();
		int min = +oo;
		for ( all moves) {
			score = maxi( depth - 1 );
			if( score < min )
				min = score;
		}
		return min;
	}
	*/



	
};

template<typename GameT, typename MoveT, typename TrTableType, size_t TrableSize>
class AlphaBetaSolver : public GameTicTac<MoveT> {

	TranspositionTable<TrTableType, TrableSize> tp_table_;

	//AlphaBetaSolver() {}


};

int main() {
	//int n; cin >> n;
	/*
	GameTicTac<Move> g(4);
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
	g.Solmaxi(2);
	g.PrintData();*/

	int n = 3;
	GameTicTac<Move> g_2(n);
	//g_2.OptimalGamePlay(true);
	FOR(i,n*n) {
		cout << "Give me the move: " << endl;
		int x,y; cin >> x >> y;
		g_2.DoMove(Move{x,y}, false);
		g_2.FindingBestMove(3);
		cout << "\n---------DO BEST MOVE FOR AI BEGIN-----------\n";
		g_2.DoMove(g_2.best_move.second, true);
		g_2.best_move = pair<int, Move>{-INF, Move{0,0}};
		cout << "\n---------DO BEST MOVE FOR AI END-----------\n";
		g_2.PrintData();
	}

}

