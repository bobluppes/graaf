#pragma once
#include <queue>
#include <limits>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <numeric>

#include "duan_shortest_paths.h"

namespace graaf::algorithm {

namespace detail {

inline void ensure_non_negative(double w, vertex_id_t u, vertex_id_t v) {
  if (w < 0) {
    std::ostringstream error_msg;
    error_msg << "Negative edge weight [" << w << "] between vertices [" << u
              << "] -> [" << v << "].";
    throw std::invalid_argument{error_msg.str()};
  }
}

}  // namespace detail

template <typename V, typename E, graph_type T, typename WEIGHT_T>
[[nodiscard]] std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
duan_shortest_paths(const graph<V, E, T>& g, vertex_id_t s, int k_param) {
  using DistT = double;
  const int n = static_cast<int>(g.vertex_count());
  if (n == 0) return {};

  // Map original vertex ids to compact [0..n)
  std::vector<vertex_id_t> id_of; id_of.reserve(n);
  for (const auto& [vid, _] : g.get_vertices()) id_of.push_back(vid);
  std::unordered_map<vertex_id_t,int> idx_of; idx_of.reserve(n*2);
  for (int i=0;i<n;++i) idx_of[id_of[i]] = i;
  if (!idx_of.contains(s)) return {};

  // Dist/Pred arrays
  const DistT INF = std::numeric_limits<DistT>::infinity();
  std::vector<DistT> db(n, INF);
  std::vector<int> pred(n, -1);
  const int s_idx = idx_of[s];
  db[s_idx] = 0;

  // Choose parameters k and t (if not provided)
  auto logn = std::log(std::max(2, n));
  int k = (k_param > 0) ? k_param : std::max(1, static_cast<int>(std::floor(std::pow(logn, 1.0/3.0))))
  ;
  int t = std::max(1, static_cast<int>(std::floor(std::pow(logn, 2.0/3.0))))
  ;

  auto for_each_relax = [&](int u, DistT du, auto&& relax) {
    const auto uid = id_of[u];
    for (const auto vid : g.get_neighbors(uid)) {
      DistT w = static_cast<DistT>(get_weight(g.get_edge(uid, vid)));
      detail::ensure_non_negative(w, uid, vid);
      relax(idx_of[vid], du + w);
    }
  };

  auto k_round_bf = [&](const std::vector<int>& S, std::vector<char>& inS){
    std::vector<int> cur = S, nxt; nxt.reserve(S.size());
    for (int it=0; it<k; ++it) {
      nxt.clear();
      for (int u: cur) {
        const DistT du = db[u];
        for_each_relax(u, du, [&](int v, DistT nd){
          if (nd < db[v]) { db[v] = nd; pred[v] = u; if (!inS[v]) { inS[v]=1; nxt.push_back(v);} }
        });
      }
      for (int u: cur) inS[u] = 0;
      cur.swap(nxt);
    }
  };

  struct BMSSPResult { DistT Bprime; std::vector<int> U; bool success; };
  auto bmssp = [&](int ell, DistT B, const std::vector<int>& S)->BMSSPResult {
    std::vector<char> inS(n,0);
    for (int u: S) inS[u]=1;
    k_round_bf(S, inS);

    std::vector<int> pivots; pivots.reserve(S.size());
    {
      std::vector<int> cnt(n,0);
      for (int u: S){
        const auto uid = id_of[u];
        for (const auto vid : g.get_neighbors(uid)) {
          int v = idx_of[vid];
          if (db[v] < INF && db[u] + static_cast<DistT>(get_weight(g.get_edge(uid, vid))) <= B) {
            if (++cnt[u] == k) { pivots.push_back(u); break; }
          }
        }
      }
    }

    std::vector<char> seen(n,0), done(n,0);
    std::vector<int> U; U.reserve(std::min(n, (int)pivots.size()*k));
    DistT Bprime = B;

    using P = std::pair<DistT,int>; struct Cmp{bool operator()(const P&a,const P&b)const{return a.first>b.first;}};
    std::vector<P> heap; heap.reserve(pivots.size()*k + 1);
    for (int u: pivots) if (db[u] < B) { heap.emplace_back(db[u], u); }
    std::make_heap(heap.begin(), heap.end(), Cmp{});

    const int targetU = std::max(1, k*k * (int)std::pow(2.0, ell * (double)t));
    while(!heap.empty() && (int)U.size() < targetU) {
      std::pop_heap(heap.begin(), heap.end(), Cmp{});
      auto [du,u] = heap.back(); heap.pop_back();
      if (seen[u] || du>=B) continue; seen[u]=1; done[u]=1; U.push_back(u);
      for_each_relax(u, du, [&](int v, DistT nd){
        if (nd < db[v]) { db[v]=nd; pred[v]=u; heap.emplace_back(nd,v); std::push_heap(heap.begin(), heap.end(), Cmp{}); }
      });
    }

    bool success = ((int)U.size() >= targetU) ? false : true;
    if (!success) {
      for (int u: U) Bprime = std::min(Bprime, db[u]);
    }
    return {Bprime, U, success};
  };

  std::vector<int> all(n); std::iota(all.begin(), all.end(), 0);

  struct Frame { int ell; DistT b; DistT B; std::vector<int> W; };
  std::vector<Frame> stack;
  stack.push_back(Frame{0, 0.0, std::numeric_limits<DistT>::infinity(), all});

  while(!stack.empty()){
    Frame fr = std::move(stack.back()); stack.pop_back();
    std::vector<int> S; S.reserve(fr.W.size());
    for (int v: fr.W) if (db[v] >= fr.b && db[v] < fr.B) S.push_back(v);
    if (S.empty()) continue;

    auto res = bmssp(fr.ell, fr.B, S);
    if (res.success) {
      std::vector<int> R; R.reserve(fr.W.size());
      for (int v: fr.W) if (!(db[v] < res.Bprime)) R.push_back(v);
      if (R.empty()) continue;
      const int buckets = std::min((int)R.size(), 1<<std::min(20, t));
      std::vector<int> order = R;
      std::nth_element(order.begin(), order.begin(), order.end(), [&](int a,int b){return db[a]<db[b];});
      std::sort(order.begin(), order.end(), [&](int a,int b){return db[a]<db[b];});
      int per = std::max(1, (int)order.size()/buckets);
      for (int i=0;i<buckets;++i){
        int L = i*per, Rr = (i==buckets-1)? (int)order.size() : (i+1)*per;
        if (L>=Rr) continue;
        DistT lb = db[ order[L] ]; DistT ub = db[ order[Rr-1] ] + std::numeric_limits<DistT>::epsilon();
        std::vector<int> Wi(order.begin()+L, order.begin()+Rr);
        stack.push_back(Frame{fr.ell+1, lb, ub, std::move(Wi)});
      }
    } else {
      std::vector<int> Wnext; Wnext.reserve(fr.W.size());
      std::vector<char> inU(n,0); for (int u: res.U) inU[u]=1;
      for (int v: fr.W) if (!inU[v]) Wnext.push_back(v);
      stack.push_back(Frame{fr.ell, fr.b, res.Bprime, std::move(Wnext)});
    }
  }

  // Build results from db/pred
  std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>> out; out.reserve(n);
  for (int v=0; v<n; ++v) if (std::isfinite(db[v])) {
    graph_path<WEIGHT_T> gp{}; gp.total_weight = static_cast<WEIGHT_T>(db[v]);
    std::vector<vertex_id_t> rev; rev.reserve(8);
    int cur=v; while (cur!=-1) { rev.push_back(id_of[cur]); if (cur==s_idx) break; cur = pred[cur]; }
    std::reverse(rev.begin(), rev.end()); gp.vertices.assign(rev.begin(), rev.end()); out[id_of[v]] = std::move(gp);
  }
  return out;
}

}  // namespace graaf::algorithm
