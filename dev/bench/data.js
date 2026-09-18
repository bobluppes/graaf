window.BENCHMARK_DATA = {
  "lastUpdate": 1789750290403,
  "repoUrl": "https://github.com/bobluppes/graaf",
  "entries": {
    "Benchmark": [
      {
        "commit": {
          "author": {
            "email": "bobluppes@gmail.com",
            "name": "Bob Luppes",
            "username": "bobluppes"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "6e31991eb76ae1994ba84448eb70256091b722a5",
          "message": "ci: track benchmark history on main and flag regressions (#405)\n\nRuns the Graaf_perf benchmarks on every push to main that touches\nsource (include/**, perf/**, CMakeLists.txt) and stores results with\nbenchmark-action/github-action-benchmark on a dedicated benchmark-data\nbranch (kept separate from gh-pages, which the docs deploy force-pushes\nand would otherwise wipe on every deploy), posting a commit comment on\nregressions past 150% (fail-on-alert left off for now).\n\nDatasets are downloaded for real (GRAAF_DOWNLOAD_PERF_DATASETS=ON) so\nthe full Graaf benchmark suite runs, including Kruskal/Prim - and\ncached across runs since they rarely change, to avoid hammering\nStanford SNAP's servers on every push. Boost benchmarks are unaffected\nsince this only builds/runs the Graaf_perf target, never Graaf_perf_boost.\n\nBigO/RMS complexity aggregate rows (from bron_kerbosch_benchmark.cpp's\n->Complexity() calls) are stripped before handing the JSON to the\naction, since they aren't per-run timings and aren't something we want\ntracked as a benchmark result over time.\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-18T18:45:16+02:00",
          "tree_id": "97a183ebc76594a74bbe32b704750d5df401754d",
          "url": "https://github.com/bobluppes/graaf/commit/6e31991eb76ae1994ba84448eb70256091b722a5"
        },
        "date": 1789750289705,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 172929.20098307083,
            "unit": "ns/iter",
            "extra": "iterations: 4070\ncpu: 172952.40859950875 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 983143.1430569359,
            "unit": "ns/iter",
            "extra": "iterations: 713\ncpu: 983445.0546984503 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 2615627.8239670754,
            "unit": "ns/iter",
            "extra": "iterations: 267\ncpu: 2615853.7865168657 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 195562.4499862561,
            "unit": "ns/iter",
            "extra": "iterations: 3589\ncpu: 195594.0072443462 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 1141879.1073185084,
            "unit": "ns/iter",
            "extra": "iterations: 615\ncpu: 1142133.152845535 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 3032645.29729536,
            "unit": "ns/iter",
            "extra": "iterations: 222\ncpu: 3032918.2432432375 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 40812.743828433384,
            "unit": "ns/iter",
            "extra": "iterations: 16973\ncpu: 40808.36599304777 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 174730.2956666772,
            "unit": "ns/iter",
            "extra": "iterations: 3000\ncpu: 174709.70099999997 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 1291240.030357191,
            "unit": "ns/iter",
            "extra": "iterations: 560\ncpu: 1291043.1964285714 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 10618088.671641707,
            "unit": "ns/iter",
            "extra": "iterations: 67\ncpu: 10616778.2835821 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 78837072.16666381,
            "unit": "ns/iter",
            "extra": "iterations: 12\ncpu: 78810342.50000004 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 555627578.9999745,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 555598591.999999 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 75365.15969092057,
            "unit": "ns/iter",
            "extra": "iterations: 9318\ncpu: 75353.22816054952 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 298843.6436427504,
            "unit": "ns/iter",
            "extra": "iterations: 2273\ncpu: 298843.20017597894 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 2467359.710801298,
            "unit": "ns/iter",
            "extra": "iterations: 287\ncpu: 2467181.428571424 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 19573578.750001274,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 19570819.299999975 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 135663876.1428631,
            "unit": "ns/iter",
            "extra": "iterations: 7\ncpu: 135654180.4285715 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 683869771.99998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 683798259.9999996 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 168969803.5000049,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 168941682.9999999 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 281330266.3333085,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 281314938.9999978 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 148521739.19998676,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 148504110.99999973 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 264825554.33331832,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 264801574.33333316 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09559143175375207,
            "unit": "ms/iter",
            "extra": "iterations: 7407\ncpu: 0.0955820241663305 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.5020404214286276,
            "unit": "ms/iter",
            "extra": "iterations: 280\ncpu: 2.501681182142842 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 330.7471670000268,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 330.7157874999973 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 4199.14810299997,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4196.3513339999845 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.21244383165908173,
            "unit": "ms/iter",
            "extra": "iterations: 3285\ncpu: 0.21242114063927323 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 3.5412562828278538,
            "unit": "ms/iter",
            "extra": "iterations: 198\ncpu: 3.541028151515189 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 338.22767800000975,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 338.19836350001253 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 4274.240925999948,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4272.304481999981 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.8917437141042214,
            "unit": "ms/iter",
            "extra": "iterations: 787\ncpu: 0.8917100076238947 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 9.615818847223068,
            "unit": "ms/iter",
            "extra": "iterations: 72\ncpu: 9.587094652777653 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 451.3880934999861,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 451.35776800000826 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 4515.635954999993,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4515.162873999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.13015466113138063,
            "unit": "ms/iter",
            "extra": "iterations: 5480\ncpu: 0.13014565802919992 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.7575738464569564,
            "unit": "ms/iter",
            "extra": "iterations: 254\ncpu: 2.7572388031496606 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 333.28826900003605,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 333.26705600001105 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 4287.466633000008,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4285.683089000003 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.29331473545412845,
            "unit": "ms/iter",
            "extra": "iterations: 2389\ncpu: 0.2932948576810463 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 4.2491904819281086,
            "unit": "ms/iter",
            "extra": "iterations: 166\ncpu: 4.248855289156642 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 351.7009944999927,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 351.6629619999918 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 4303.876309999964,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4302.595249999996 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.3709237035573008,
            "unit": "ms/iter",
            "extra": "iterations: 506\ncpu: 1.3708364584980253 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 12.332816561403186,
            "unit": "ms/iter",
            "extra": "iterations: 57\ncpu: 12.331794210526045 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 469.8277180000332,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 469.78719300000193 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 4543.776696000009,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4543.319300000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 7.768631032966688,
            "unit": "ms/iter",
            "extra": "iterations: 91\ncpu: 7.767518373626571 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 338.67375950001133,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 338.66759449999506 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 1168.9489589999766,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1168.8302900000167 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.25257672266473075,
            "unit": "ms/iter",
            "extra": "iterations: 2762\ncpu: 0.252542581100653 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.948999432584208,
            "unit": "ms/iter",
            "extra": "iterations: 178\ncpu: 3.9485052977528183 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 345.8986985000365,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 345.85538000000327 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 4250.929959000018,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4247.907457999986 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.5842095698447574,
            "unit": "ms/iter",
            "extra": "iterations: 451\ncpu: 1.5840624611973455 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 27.154318124999577,
            "unit": "ms/iter",
            "extra": "iterations: 32\ncpu: 27.15048384374974 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 535.1325150001003,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 535.0702440000248 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 4707.4280819999785,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4706.962435000009 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.368251764643781,
            "unit": "ms/iter",
            "extra": "iterations: 1895\ncpu: 0.3682053699208454 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 4.803852210884265,
            "unit": "ms/iter",
            "extra": "iterations: 147\ncpu: 4.791895639455748 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 353.4117455000114,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 353.38960549999854 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 4243.092356000034,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4242.749354000011 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.8344515848563288,
            "unit": "ms/iter",
            "extra": "iterations: 383\ncpu: 1.8341724621410564 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 30.906960727272484,
            "unit": "ms/iter",
            "extra": "iterations: 22\ncpu: 30.901925090908186 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 597.1954730000562,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 597.186908999987 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 4877.065626999979,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4873.47358400001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.8026752279999982,
            "unit": "ms/iter",
            "extra": "iterations: 1000\ncpu: 0.8026172680000059 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 10.112066999999477,
            "unit": "ms/iter",
            "extra": "iterations: 83\ncpu: 10.110769722891485 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 408.26723250000896,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 408.2295469999906 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 4372.740363999924,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4369.043490999985 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.6094273169999269,
            "unit": "ms/iter",
            "extra": "iterations: 1000\ncpu: 0.6093948689999991 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 9.740260350648802,
            "unit": "ms/iter",
            "extra": "iterations: 77\ncpu: 9.739385961039149 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 410.3469429999791,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 410.2996860000019 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 4428.301633000046,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4427.86623500001 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3510072988.000047,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3509670735.0000143 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3784563991.000027,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3784215080.999985 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 5356976452.999902,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5354052939.000013 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5980324186.999951,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5979807788.000016 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 1806658747.0000286,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1806425206.9999895 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 1640858894.0000753,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1639553726.0000026 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 4331834639.000022,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4331369389.999991 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 3267742762.0000114,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3267355809.9999695 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 368745032.49998724,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 368716683.0000024 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 472575721.9999878,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 472522018.0000065 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 2978957203.00005,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2978630246.000023 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 2918716250.999978,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2916228834.99997 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}