"use strict";(self.webpackChunkgraaf=self.webpackChunkgraaf||[]).push([[515],{5235:(e,n,r)=>{r.r(n),r.d(n,{assets:()=>h,contentTitle:()=>l,default:()=>c,frontMatter:()=>a,metadata:()=>s,toc:()=>o});const s=JSON.parse('{"id":"algorithms/traversal/breadth-first-search","title":"Breadth First Search (BFS)","description":"Breadth First Search (BFS) Algorithm","source":"@site/docs/algorithms/traversal/breadth-first-search.md","sourceDirName":"algorithms/traversal","slug":"/algorithms/traversal/breadth-first-search","permalink":"/graaf/docs/algorithms/traversal/breadth-first-search","draft":false,"unlisted":false,"editUrl":"https://github.com/bobluppes/graaf/tree/main/docs/algorithms/traversal/breadth-first-search.md","tags":[],"version":"current","frontMatter":{},"sidebar":"algorithmSidebar","previous":{"title":"Traversal Algorithms","permalink":"/graaf/docs/category/traversal-algorithms"},"next":{"title":"Depth First Search (DFS)","permalink":"/graaf/docs/algorithms/traversal/depth-first-search"}}');var i=r(4848),t=r(8453);const a={},l="Breadth First Search (BFS)",h={},o=[{value:"Breadth First Search (BFS) Algorithm",id:"breadth-first-search-bfs-algorithm",level:2},{value:"BFS is particularly useful for:",id:"bfs-is-particularly-useful-for",level:3},{value:"Limitations of BFS:",id:"limitations-of-bfs",level:4},{value:"Complexity and Performance:",id:"complexity-and-performance",level:3},{value:"Syntax",id:"syntax",level:2},{value:"Explanation of Parameters:",id:"explanation-of-parameters",level:3}];function d(e){const n={a:"a",code:"code",h1:"h1",h2:"h2",h3:"h3",h4:"h4",header:"header",li:"li",ol:"ol",p:"p",pre:"pre",strong:"strong",ul:"ul",...(0,t.R)(),...e.components};return(0,i.jsxs)(i.Fragment,{children:[(0,i.jsx)(n.header,{children:(0,i.jsx)(n.h1,{id:"breadth-first-search-bfs",children:"Breadth First Search (BFS)"})}),"\n",(0,i.jsx)(n.h2,{id:"breadth-first-search-bfs-algorithm",children:"Breadth First Search (BFS) Algorithm"}),"\n",(0,i.jsx)(n.p,{children:"Breadth First Search (BFS) is a fundamental graph traversal algorithm used to explore and analyze graphs, be they\ndirected or undirected. It operates on the principle of visiting nodes in layers, starting from a given source node and\ngradually expanding outward to neighboring nodes at increasing distances. BFS ensures that all nodes at a particular\ndistance from the source are visited before moving on to nodes at a greater distance. This process continues until all\nreachable nodes have been visited, forming a breadth-first exploration of the graph."}),"\n",(0,i.jsx)(n.p,{children:"The BFS algorithm can be succinctly described using the following steps:"}),"\n",(0,i.jsxs)(n.ol,{children:["\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsx)(n.p,{children:"Begin by selecting a source node as the starting point of the traversal and enqueue it in a queue data structure."}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsx)(n.p,{children:"While the queue is not empty, repeat the following steps:"}),"\n",(0,i.jsxs)(n.ul,{children:["\n",(0,i.jsx)(n.li,{children:"a. Dequeue a node from the front of the queue."}),"\n",(0,i.jsx)(n.li,{children:"b. Process the dequeued node, which may involve examining its attributes, marking it as visited, or performing\nother relevant operations."}),"\n",(0,i.jsx)(n.li,{children:"c. Enqueue all unvisited neighbors of the dequeued node into the queue."}),"\n"]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsx)(n.p,{children:"Continue this process until the queue becomes empty, indicating that all reachable nodes have been visited."}),"\n"]}),"\n"]}),"\n",(0,i.jsx)(n.h3,{id:"bfs-is-particularly-useful-for",children:"BFS is particularly useful for:"}),"\n",(0,i.jsxs)(n.ul,{children:["\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsx)(n.p,{children:"P2P - Find neighbor nodes:"}),"\n",(0,i.jsxs)(n.ul,{children:["\n",(0,i.jsx)(n.li,{children:"Finds all neighbors, and then all neighbors of these neighbors."}),"\n"]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsx)(n.p,{children:"Search Engine Crawler:"}),"\n",(0,i.jsxs)(n.ul,{children:["\n",(0,i.jsx)(n.li,{children:"Helps in systematically crawling web pages, exploring links layer by layer."}),"\n"]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsx)(n.p,{children:"Garbage Collection:"}),"\n",(0,i.jsxs)(n.ul,{children:["\n",(0,i.jsx)(n.li,{children:"Identifies and marks reachable objects, propagating to related objects."}),"\n"]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsx)(n.p,{children:"Broadcasting in Networks:"}),"\n",(0,i.jsxs)(n.ul,{children:["\n",(0,i.jsx)(n.li,{children:"Efficiently distributes information across nodes in a network."}),"\n"]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsx)(n.p,{children:"Analyzing the Connectivity of Components:"}),"\n",(0,i.jsxs)(n.ul,{children:["\n",(0,i.jsx)(n.li,{children:"Determines the connected components in a graph."}),"\n"]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsx)(n.p,{children:"Solving Puzzles like the Sliding Tile Puzzle:"}),"\n",(0,i.jsxs)(n.ul,{children:["\n",(0,i.jsx)(n.li,{children:"Explores possible moves in a puzzle in a systematic manner."}),"\n"]}),"\n"]}),"\n"]}),"\n",(0,i.jsx)(n.h4,{id:"limitations-of-bfs",children:"Limitations of BFS:"}),"\n",(0,i.jsxs)(n.ol,{children:["\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsxs)(n.p,{children:[(0,i.jsx)(n.strong,{children:"Memory Usage:"})," BFS may consume significant memory resources, especially in graphs with many nodes or when\nsearching for paths in deep or complex graphs."]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsxs)(n.p,{children:[(0,i.jsx)(n.strong,{children:"Performance on Dense Graphs:"})," In dense graphs, where the number of edges is close to the maximum possible, BFS may\nnot perform as efficiently as other algorithms designed specifically for dense graphs."]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsxs)(n.p,{children:[(0,i.jsx)(n.strong,{children:"Unweighted Graphs:"})," BFS doesn't incorporate edge weights, which makes it less suitable for finding shortest paths\nin graphs with weighted edges."]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsxs)(n.p,{children:[(0,i.jsx)(n.strong,{children:"No Negative Weights:"})," BFS is not suited for graphs with negative edge weights, as it assumes that all edges have a\nnon-negative weight. This is because BFS relies on the property that it visits nodes in increasing order of distance\nfrom the source, and negative weights can lead to unexpected results."]}),"\n"]}),"\n",(0,i.jsxs)(n.li,{children:["\n",(0,i.jsxs)(n.p,{children:[(0,i.jsx)(n.strong,{children:"No Guarantee of Optimality:"})," While BFS can find the shortest path in an unweighted graph, it may not guarantee the\nshortest path in graphs with weighted edges or other more complex scenarios. Dijkstra's algorithm or the Bellman-Ford\nalgorithm are better suited for such cases."]}),"\n"]}),"\n"]}),"\n",(0,i.jsx)(n.h3,{id:"complexity-and-performance",children:"Complexity and Performance:"}),"\n",(0,i.jsxs)(n.p,{children:["The BFS algorithm is implemented with a priority queue and runs in ",(0,i.jsx)(n.code,{children:"O(|V| + |E|)"})," time complexity for connected graphs,\nwhere ",(0,i.jsx)(n.code,{children:"|E|"})," is the number of edges and ",(0,i.jsx)(n.code,{children:"|V|"})," the number of vertices in the graph."]}),"\n",(0,i.jsx)(n.p,{children:"In summary, Breadth First Search is a powerful and versatile algorithm for exploring graphs, but its limitations in\nhandling weighted graphs and negative edge weights should be considered. It provides a straightforward way to explore a\ngraph layer by layer and is particularly useful for unweighted graph scenarios and connectivity analysis."}),"\n",(0,i.jsx)(n.p,{children:(0,i.jsx)(n.a,{href:"https://en.wikipedia.org/wiki/Breadth-first_search",children:"wikipedia"})}),"\n",(0,i.jsx)(n.h2,{id:"syntax",children:"Syntax"}),"\n",(0,i.jsx)(n.p,{children:"The bfs_termination_strategy returns true when a certain condition is met, causing to terminate. The bfs_edge_callback\nis a function that is used as a callback during the BFS traversal to perform some action whenever an edge is traversed."}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-cpp",children:"template <\n    typename V, typename E, graph_type T,\n    typename EDGE_CALLBACK_T = detail::noop_callback,\n    typename SEARCH_TERMINATION_STRATEGY_T = detail::exhaustive_search_strategy>\n  requires std::invocable<EDGE_CALLBACK_T &, edge_id_t &> &&\n           std::is_invocable_r_v<bool, SEARCH_TERMINATION_STRATEGY_T &,\n                                 vertex_id_t>\nvoid breadth_first_traverse(\n    const graph<V, E, T> &graph, vertex_id_t start_vertex,\n    const EDGE_CALLBACK_T &edge_callback,\n    const SEARCH_TERMINATION_STRATEGY_T &search_termination_strategy =\n        SEARCH_TERMINATION_STRATEGY_T{});\n"})}),"\n",(0,i.jsx)(n.h3,{id:"explanation-of-parameters",children:"Explanation of Parameters:"}),"\n",(0,i.jsxs)(n.ul,{children:["\n",(0,i.jsxs)(n.li,{children:[(0,i.jsx)(n.strong,{children:"graph"}),": The graph to traverse. This parameter represents the graph data structure on which the traversal will be\nperformed."]}),"\n",(0,i.jsxs)(n.li,{children:[(0,i.jsx)(n.strong,{children:"start_vertex"}),": Vertex id where the traversal should be started. This parameter specifies the initial vertex from\nwhich the traversal begins."]}),"\n",(0,i.jsxs)(n.li,{children:[(0,i.jsx)(n.strong,{children:"edge_callback"}),": A callback function that is called for each traversed edge. It should be invocable with\nan ",(0,i.jsx)(n.code,{children:"edge_id_t"})," object, representing an edge in the graph."]}),"\n",(0,i.jsxs)(n.li,{children:[(0,i.jsx)(n.strong,{children:"search_termination_strategy"}),": A unary predicate that indicates whether the traversal should continue or not. The\ntraversal continues while this predicate returns ",(0,i.jsx)(n.code,{children:"false"}),". This parameter is optional and defaults to a predefined\nsearch termination strategy, which traverses the graph exhaustively."]}),"\n",(0,i.jsxs)(n.li,{children:[(0,i.jsx)(n.strong,{children:"return"}),": The provided code does not explicitly return a value. The traversal is performed by visiting vertices and\nedges in the graph based on the specified parameters."]}),"\n"]})]})}function c(e={}){const{wrapper:n}={...(0,t.R)(),...e.components};return n?(0,i.jsx)(n,{...e,children:(0,i.jsx)(d,{...e})}):d(e)}},8453:(e,n,r)=>{r.d(n,{R:()=>a,x:()=>l});var s=r(6540);const i={},t=s.createContext(i);function a(e){const n=s.useContext(t);return s.useMemo((function(){return"function"==typeof e?e(n):{...n,...e}}),[n,e])}function l(e){let n;return n=e.disableParentContext?"function"==typeof e.components?e.components(i):e.components||i:a(e.components),s.createElement(t.Provider,{value:n},e.children)}}}]);