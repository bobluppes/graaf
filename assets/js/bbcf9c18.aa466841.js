"use strict";(self.webpackChunkgraaf=self.webpackChunkgraaf||[]).push([[191],{1324:(e,t,s)=>{s.r(t),s.d(t,{assets:()=>o,contentTitle:()=>i,default:()=>c,frontMatter:()=>h,metadata:()=>r,toc:()=>d});const r=JSON.parse('{"id":"algorithms/shortest-path/bfs-based-shortest-path","title":"BFS Based Shortest Path","description":"Breadth-First Search (BFS) is a graph traversal algorithm that efficiently finds the shortest","source":"@site/docs/algorithms/shortest-path/bfs-based-shortest-path.md","sourceDirName":"algorithms/shortest-path","slug":"/algorithms/shortest-path/bfs-based-shortest-path","permalink":"/graaf/docs/algorithms/shortest-path/bfs-based-shortest-path","draft":false,"unlisted":false,"editUrl":"https://github.com/bobluppes/graaf/tree/main/docs/algorithms/shortest-path/bfs-based-shortest-path.md","tags":[],"version":"current","frontMatter":{},"sidebar":"algorithmSidebar","previous":{"title":"Bellman-Ford Shortest Path","permalink":"/graaf/docs/algorithms/shortest-path/bellman-ford"},"next":{"title":"Dijkstra Shortest Path","permalink":"/graaf/docs/algorithms/shortest-path/dijkstra"}}');var a=s(4848),n=s(8453);const h={},i="BFS Based Shortest Path",o={},d=[{value:"Syntax",id:"syntax",level:2}];function l(e){const t={a:"a",code:"code",h1:"h1",h2:"h2",header:"header",li:"li",p:"p",pre:"pre",strong:"strong",ul:"ul",...(0,n.R)(),...e.components};return(0,a.jsxs)(a.Fragment,{children:[(0,a.jsx)(t.header,{children:(0,a.jsx)(t.h1,{id:"bfs-based-shortest-path",children:"BFS Based Shortest Path"})}),"\n",(0,a.jsxs)(t.p,{children:["Breadth-First Search (BFS) is a graph traversal algorithm that efficiently finds the shortest\npath between two vertices in an ",(0,a.jsx)(t.strong,{children:"unweighted graph"})," by exploring vertices level by level,\nguaranteeing the shortest path, and has a time complexity of ",(0,a.jsx)(t.code,{children:"O(|E| + |V|)"}),",\nwhere ",(0,a.jsx)(t.code,{children:"|V|"})," is the number of vertices and ",(0,a.jsx)(t.code,{children:"|E|"})," is the number of edges in the graph.\nBFS uses a queue to iteratively visit neighboring vertices from the source\nvertex, ensuring that the shortest path is discovered before longer paths."]}),"\n",(0,a.jsx)(t.p,{children:(0,a.jsx)(t.a,{href:"https://en.wikipedia.org/wiki/Breadth-first_search",children:"wikipedia"})}),"\n",(0,a.jsx)(t.h2,{id:"syntax",children:"Syntax"}),"\n",(0,a.jsx)(t.p,{children:"Calculates the shortest path between one start_vertex and one\nend_vertex using BFS. This does not consider edge weights."}),"\n",(0,a.jsx)(t.pre,{children:(0,a.jsx)(t.code,{className:"language-cpp",children:"template <typename V, typename E, graph_type T, typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>\nstd::optional<graph_path<WEIGHT_T>> bfs_shortest_path(\n    const graph<V, E, T>& graph, vertex_id_t start_vertex, vertex_id_t end_vertex);\n"})}),"\n",(0,a.jsxs)(t.ul,{children:["\n",(0,a.jsxs)(t.li,{children:[(0,a.jsx)(t.strong,{children:"graph"})," The graph to extract shortest path from."]}),"\n",(0,a.jsxs)(t.li,{children:[(0,a.jsx)(t.strong,{children:"start_vertex"})," Vertex id where the shortest path should start."]}),"\n",(0,a.jsxs)(t.li,{children:[(0,a.jsx)(t.strong,{children:"end_vertex"})," Vertex id where the shortest path should end."]}),"\n",(0,a.jsxs)(t.li,{children:[(0,a.jsx)(t.strong,{children:"return"})," An optional with the shortest path (list of vertices) if found."]}),"\n"]})]})}function c(e={}){const{wrapper:t}={...(0,n.R)(),...e.components};return t?(0,a.jsx)(t,{...e,children:(0,a.jsx)(l,{...e})}):l(e)}},8453:(e,t,s)=>{s.d(t,{R:()=>h,x:()=>i});var r=s(6540);const a={},n=r.createContext(a);function h(e){const t=r.useContext(n);return r.useMemo((function(){return"function"==typeof e?e(t):{...t,...e}}),[t,e])}function i(e){let t;return t=e.disableParentContext?"function"==typeof e.components?e.components(a):e.components||a:h(e.components),r.createElement(n.Provider,{value:t},e.children)}}}]);