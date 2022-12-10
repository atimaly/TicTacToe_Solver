#include <bits/stdc++.h>

#ifndef _UTILITY
#define _UTILITY
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
         os << std::endl;
 }
 
 template <class C>
 void Print_Matrix(const C &M, std::ostream &os = std::cerr) {
         for(auto &v : M) {
                 for(auto &u : v) {
                         os << u << " ";            
                         }
             os << std::endl;
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
         os << std::endl;
 }
 
 template <class C>
 void Print_vector_pairs_raw(const C &Original, std::ostream &os = std::cerr) {
         for(const auto &v : Original) {
             os << v.first << " " << v.second << " ";
         }
         os << std::endl;
 }
#endif //_UTILITY

