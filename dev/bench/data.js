window.BENCHMARK_DATA = {
  "lastUpdate": 1789905164754,
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
      },
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
          "id": "b2f551d76a5687db26541901d6c9b9406390d87e",
          "message": "ci: merge benchmark tracking into the documentation workflow (#429)\n\n* ci: merge benchmark tracking into the documentation workflow\n\nbenchmarks.yml and documentation.yml both push to GitHub Pages\nbranches on every push to main, but as two independent workflows they\ncould race: a push touching both perf/ and docs could have\ndocumentation.yml read benchmark-data before the concurrently-running\nbenchmark job finished writing to it, publishing a stale chart.\nneeds: only orders jobs within a single workflow, so the two are\nmerged here into one, with a change-detection job gating whether\nbenchmark actually runs (mirroring the old path filter) and\ndocumentation always running last via needs: [changes, benchmark].\n\ndocumentation now also stitches the benchmark-data branch's generated\nchart into the published site under /benchmarks/, since gh-pages only\nsupports one published source and is already the docs' site - a\nseparate branch is still used to store benchmark history because\ndocumentation's deploy step force-pushes (wipes) gh-pages on every\nrun, which would otherwise destroy that history.\n\ndocumentation runs with if: always(), so it deploys regardless of\nwhether benchmark ran, was skipped, or failed - a benchmark regression\nor a flaky dataset download shouldn't hold the docs site hostage. If\nbenchmark does fail, its failure still isn't hidden: GitHub marks the\noverall workflow run's conclusion as failed if any job in it failed,\nregardless of what a later if-always() job does, so it remains clearly\nvisible without blocking the docs deploy.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* review: rename workflow file and trim comments\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n---------\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-18T19:05:25+02:00",
          "tree_id": "702ff431ba1e1a4deb9b1e96ef7fa87884436212",
          "url": "https://github.com/bobluppes/graaf/commit/b2f551d76a5687db26541901d6c9b9406390d87e"
        },
        "date": 1789751512140,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 171462.07656433704,
            "unit": "ns/iter",
            "extra": "iterations: 4075\ncpu: 171454.8726380381 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 977532.8758714759,
            "unit": "ns/iter",
            "extra": "iterations: 717\ncpu: 977695.9567642958 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 2655687.2255635457,
            "unit": "ns/iter",
            "extra": "iterations: 266\ncpu: 2655354.909774447 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 195826.84234486255,
            "unit": "ns/iter",
            "extra": "iterations: 3514\ncpu: 195785.90751280577 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 1159382.0576601475,
            "unit": "ns/iter",
            "extra": "iterations: 607\ncpu: 1159499.9505766113 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 3092743.365298055,
            "unit": "ns/iter",
            "extra": "iterations: 219\ncpu: 3092679.4155251216 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 40621.62868148234,
            "unit": "ns/iter",
            "extra": "iterations: 16875\ncpu: 40589.864592592596 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 175713.00866667152,
            "unit": "ns/iter",
            "extra": "iterations: 3000\ncpu: 175511.35500000056 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 1371386.772500003,
            "unit": "ns/iter",
            "extra": "iterations: 400\ncpu: 1369499.5675000008 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 10628116.34782589,
            "unit": "ns/iter",
            "extra": "iterations: 69\ncpu: 10621197.550724635 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 63638962.09090957,
            "unit": "ns/iter",
            "extra": "iterations: 11\ncpu: 63608172.181818224 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 564021087.0000147,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 563883776.0000008 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 77811.97835497839,
            "unit": "ns/iter",
            "extra": "iterations: 9009\ncpu: 77671.12953712956 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 296547.11725956306,
            "unit": "ns/iter",
            "extra": "iterations: 2277\ncpu: 296054.4602547212 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 2461686.2964285654,
            "unit": "ns/iter",
            "extra": "iterations: 280\ncpu: 2457612.5785714253 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 20070030.425000597,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 20037258.924999967 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 137913681.4285695,
            "unit": "ns/iter",
            "extra": "iterations: 7\ncpu: 137699503.57142845 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 683250271.0000199,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 683055139.0000004 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 198828721.74999022,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 198793579.00000018 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 287030723.66666526,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 286999430.333329 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 190877236.7499978,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 190856029.99999908 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 266780247.33333436,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 266207226.00000593 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09510093353350846,
            "unit": "ms/iter",
            "extra": "iterations: 7327\ncpu: 0.09509030803876002 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.5964036245352036,
            "unit": "ms/iter",
            "extra": "iterations: 269\ncpu: 2.595922018587338 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 330.9076849999997,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 330.8829494999941 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 4233.574697999984,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4233.090951999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.21437944318529895,
            "unit": "ms/iter",
            "extra": "iterations: 3265\ncpu: 0.21435181408881906 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 3.6117827422680016,
            "unit": "ms/iter",
            "extra": "iterations: 194\ncpu: 3.6113924072165178 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 336.6046135000147,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 336.51790049999875 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 4250.924467000004,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4250.117005999982 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.8886943354350152,
            "unit": "ms/iter",
            "extra": "iterations: 793\ncpu: 0.8885989861286333 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 11.130618079365586,
            "unit": "ms/iter",
            "extra": "iterations: 63\ncpu: 11.128700730158663 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 454.4128585000067,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 454.32182449999914 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 4550.432069999999,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4547.274109999989 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.13156865692364197,
            "unit": "ms/iter",
            "extra": "iterations: 5474\ncpu: 0.13155735367190455 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.7955011752987415,
            "unit": "ms/iter",
            "extra": "iterations: 251\ncpu: 2.795280402390367 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 330.5267165000032,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 330.49749250000104 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 4259.4322700000475,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4258.827118999989 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.2965380501285428,
            "unit": "ms/iter",
            "extra": "iterations: 2334\ncpu: 0.2961991392459374 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 4.510270266666449,
            "unit": "ms/iter",
            "extra": "iterations: 165\ncpu: 4.509341715151487 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 350.6291879999992,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 350.594588000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 4302.980712000021,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4302.411877999986 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.3323939515503245,
            "unit": "ms/iter",
            "extra": "iterations: 516\ncpu: 1.3322357325581153 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 13.703969588235333,
            "unit": "ms/iter",
            "extra": "iterations: 51\ncpu: 13.702297294117319 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 475.36845049998533,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 474.16371950001235 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 4587.443457999996,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4586.912139999981 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 9.228944272727155,
            "unit": "ms/iter",
            "extra": "iterations: 77\ncpu: 9.228130532467542 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 363.1646820000185,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 363.11271799999645 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 1278.5297859999787,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1278.3782710000082 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.25277725366203224,
            "unit": "ms/iter",
            "extra": "iterations: 2799\ncpu: 0.25202340121471656 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 4.031487406976783,
            "unit": "ms/iter",
            "extra": "iterations: 172\ncpu: 4.031204191860597 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 347.59153400000287,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 347.53058249999924 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 4298.996668000029,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4298.5414550000205 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.5802574820627995,
            "unit": "ms/iter",
            "extra": "iterations: 446\ncpu: 1.5802207892377023 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 22.63483222222257,
            "unit": "ms/iter",
            "extra": "iterations: 27\ncpu: 22.6307657777772 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 524.2704939999498,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 524.2213730000174 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 4928.665233999993,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4924.530903999994 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.36119958967807075,
            "unit": "ms/iter",
            "extra": "iterations: 1957\ncpu: 0.36117603934592724 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 4.817610719178229,
            "unit": "ms/iter",
            "extra": "iterations: 146\ncpu: 4.817257732876853 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 354.5877030000213,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 354.56086349999794 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 4306.163857000001,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4302.676501999997 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.8261459974093959,
            "unit": "ms/iter",
            "extra": "iterations: 386\ncpu: 1.8260288471502444 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 33.97941928571548,
            "unit": "ms/iter",
            "extra": "iterations: 21\ncpu: 33.97365899999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 639.0886709999677,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 639.0183559999798 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 5085.072045000004,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 5081.264138000023 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.6299437426636403,
            "unit": "ms/iter",
            "extra": "iterations: 1329\ncpu: 0.6299104018058793 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 9.5846980289857,
            "unit": "ms/iter",
            "extra": "iterations: 69\ncpu: 9.583395797101506 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 414.42294300000526,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 414.3964984999968 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 4416.681253999968,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4416.131879999994 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.7069122226962479,
            "unit": "ms/iter",
            "extra": "iterations: 1172\ncpu: 0.7068739095563138 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 9.277261560606231,
            "unit": "ms/iter",
            "extra": "iterations: 66\ncpu: 9.275733909091018 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 408.3925209999961,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 408.35511099999167 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 4338.859609999986,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4338.319342999995 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3760924401.000011,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3760465328.9999986 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 4103306884.0000057,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4102777783.999954 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 6112888466.000015,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6111359373.000028 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 6763641796.999991,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6762784201.999977 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 1899484201.000007,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1899254390.9999995 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 1722078865.0000145,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1720907065.9999952 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 5266779549.000034,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5265848265.999978 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 3605469857.9999924,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3604953038.000019 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 449547195.5000312,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 449488801.4999958 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 503306517.0000555,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 503252354.00003976 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 3341691867.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3339171195.0000057 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 3107858559.0000787,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3107379918.000049 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "1b2593565ff7be55d337183af8e51213ef9ca604",
          "message": "perf: mark vertices as seen on enqueue in breadth_first_traverse (#430)\n\nMarking on dequeue let a vertex be enqueued (and its neighbors rescanned)\nonce per already-queued predecessor. Marking on discovery bounds the queue\nto one entry per vertex and fires the edge callback once per tree edge.\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-18T19:39:46+02:00",
          "tree_id": "c4a2ae4576388f28b39fd261e251a4e2db8a7006",
          "url": "https://github.com/bobluppes/graaf/commit/1b2593565ff7be55d337183af8e51213ef9ca604"
        },
        "date": 1789753588859,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 179848.25248818542,
            "unit": "ns/iter",
            "extra": "iterations: 3818\ncpu: 179845.0094290215 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 1027587.7595307092,
            "unit": "ns/iter",
            "extra": "iterations: 682\ncpu: 1027542.6378299166 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 2631254.511278208,
            "unit": "ns/iter",
            "extra": "iterations: 266\ncpu: 2630853.8421052536 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 202476.2370393183,
            "unit": "ns/iter",
            "extra": "iterations: 3337\ncpu: 202405.16272100314 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 1174524.8879597096,
            "unit": "ns/iter",
            "extra": "iterations: 598\ncpu: 1174561.8695652366 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 3014923.236607363,
            "unit": "ns/iter",
            "extra": "iterations: 224\ncpu: 3014531.1785713746 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 38516.0252134783,
            "unit": "ns/iter",
            "extra": "iterations: 17332\ncpu: 38495.790445418854 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 161871.44459161093,
            "unit": "ns/iter",
            "extra": "iterations: 4530\ncpu: 161666.75496688773 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 1376363.0475,
            "unit": "ns/iter",
            "extra": "iterations: 400\ncpu: 1375194.512500002 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 10736098.62000012,
            "unit": "ns/iter",
            "extra": "iterations: 50\ncpu: 10726693.439999977 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 77288774.38461596,
            "unit": "ns/iter",
            "extra": "iterations: 13\ncpu: 77234278.61538458 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 506047246.9999979,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 506020106.00000113 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 73883.8346680729,
            "unit": "ns/iter",
            "extra": "iterations: 9490\ncpu: 73792.97681770277 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 294502.458406304,
            "unit": "ns/iter",
            "extra": "iterations: 2284\ncpu: 294113.019702277 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 2383711.8809523843,
            "unit": "ns/iter",
            "extra": "iterations: 294\ncpu: 2381027.7925169966 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 19302936.54999993,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 19279922.6 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 138223337.25000036,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 138070246.8749999 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 728346020.999993,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 728297982.0000008 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 46736505.333333865,
            "unit": "ns/iter",
            "extra": "iterations: 15\ncpu: 46734434.06666659 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 10083966.26388909,
            "unit": "ns/iter",
            "extra": "iterations: 72\ncpu: 10083153.333333232 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 12828890.428571478,
            "unit": "ns/iter",
            "extra": "iterations: 42\ncpu: 12827199.499999966 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 1119967.4569105923,
            "unit": "ns/iter",
            "extra": "iterations: 615\ncpu: 1119854.957723587 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09164491226229596,
            "unit": "ms/iter",
            "extra": "iterations: 7625\ncpu: 0.09163663147540722 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.268473540453069,
            "unit": "ms/iter",
            "extra": "iterations: 309\ncpu: 2.2682766990292067 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 619.5692409999936,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 619.5275149999873 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 3836.446568000014,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3836.1535509999953 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.2225996318124155,
            "unit": "ms/iter",
            "extra": "iterations: 3156\ncpu: 0.22258583491761072 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 3.1520611214952483,
            "unit": "ms/iter",
            "extra": "iterations: 214\ncpu: 3.1518122242989786 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 631.7707869999936,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 631.7388530000017 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 3860.206811000012,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3857.553208000013 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 1.1260662209677306,
            "unit": "ms/iter",
            "extra": "iterations: 620\ncpu: 1.125969909677387 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 10.901171298507283,
            "unit": "ms/iter",
            "extra": "iterations: 67\ncpu: 10.900259268656901 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 720.7985549999876,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 720.7704859999922 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 4052.549827000007,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4049.4928570000184 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.12325847616534583,
            "unit": "ms/iter",
            "extra": "iterations: 5685\ncpu: 0.12324993825857584 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.4946556985815516,
            "unit": "ms/iter",
            "extra": "iterations: 282\ncpu: 2.4944881063829993 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 616.9058469999982,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 616.8360039999925 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 3789.2048070000046,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3788.7669110000106 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.32345136119945644,
            "unit": "ms/iter",
            "extra": "iterations: 2201\ncpu: 0.3234091735574795 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.7864555597825924,
            "unit": "ms/iter",
            "extra": "iterations: 184\ncpu: 3.7859994565216937 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 659.1566619999867,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 659.0187509999907 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 3889.2691599999694,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3886.4692779999928 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.6015533931035024,
            "unit": "ms/iter",
            "extra": "iterations: 435\ncpu: 1.6013987264367795 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 12.7107569272725,
            "unit": "ms/iter",
            "extra": "iterations: 55\ncpu: 12.710142127272919 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 743.4890669999845,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 743.4060610000017 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 4065.9545440000215,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4065.4406270000154 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 6.502632363636642,
            "unit": "ms/iter",
            "extra": "iterations: 110\ncpu: 6.491861218181715 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 303.8159650000125,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 303.7959604999969 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 1143.2684420000214,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1143.1075480000175 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.27083696371439137,
            "unit": "ms/iter",
            "extra": "iterations: 2563\ncpu: 0.27079489114318667 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.672199036842166,
            "unit": "ms/iter",
            "extra": "iterations: 190\ncpu: 3.671713547368421 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 650.4072039999755,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 650.3649599999903 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 3902.622244999975,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3901.785227000005 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.673254346988015,
            "unit": "ms/iter",
            "extra": "iterations: 415\ncpu: 1.6731471204819621 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 28.587248166665802,
            "unit": "ms/iter",
            "extra": "iterations: 24\ncpu: 28.58642366666686 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 902.0882959999881,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 901.9650369999965 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 4352.007791000005,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4351.5153209999935 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.39580089704212,
            "unit": "ms/iter",
            "extra": "iterations: 1758\ncpu: 0.3957851194539133 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 4.341695888198606,
            "unit": "ms/iter",
            "extra": "iterations: 161\ncpu: 4.336159180124196 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 657.7770220000048,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 657.6896770000076 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 3857.8688100000136,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3857.435745999993 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.9456601994535692,
            "unit": "ms/iter",
            "extra": "iterations: 366\ncpu: 1.9454577076502322 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 31.579646521740177,
            "unit": "ms/iter",
            "extra": "iterations: 23\ncpu: 31.574608173913347 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 900.4618700000151,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 900.3518849999921 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 4461.301810000009,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4458.27326600002 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.6148288557783734,
            "unit": "ms/iter",
            "extra": "iterations: 1047\ncpu: 0.6147400601719255 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 8.19678847761143,
            "unit": "ms/iter",
            "extra": "iterations: 67\ncpu: 8.195854895522368 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 702.6211709999757,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 702.2643450000032 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 4050.1922729999933,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4049.764147000019 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.8989459820051542,
            "unit": "ms/iter",
            "extra": "iterations: 778\ncpu: 0.8988776079691742 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 8.46801470588215,
            "unit": "ms/iter",
            "extra": "iterations: 85\ncpu: 8.438022882353046 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 748.4838979999608,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 748.3510940000144 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 4111.319711000022,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 4110.870181999985 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3583137055.0000086,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3582634444.9999967 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3871166385.0000377,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3870450622.9999537 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 5829855244.000044,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5829074117.000005 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 6208686052.000019,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6207825004.999961 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 1795697814.00005,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1795355538.9999564 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 1512243935.9999475,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1512038998.9999695 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 4746888367.999987,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4744872620.000024 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 3200150610.9999695,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3199762489.999955 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 338134349.49999535,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 338098537.50000226 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 491444693.9999948,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 491389463.50001335 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 2717878671.000051,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2714708621.999989 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 2586678796.000001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2586358275.000009 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "d7a070b460d1231044beaeb660d728c068f266de",
          "message": "perf: run the BFS benchmarks on the full datasets (#431)\n\nWith BFS marking vertices as seen on enqueue, an exhaustive traversal over\nthe full giant component takes well under a second, so the subgraph caps\nand the comments justifying them are no longer needed. The BFS benchmarks\nnow load the graph like the other benchmarks instead of going through\nconstruct_connected_subgraph (still used by the Prim benchmarks). Graaf and\nBoost benchmarks change together so they stay comparable.\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-18T20:17:03+02:00",
          "tree_id": "014b6f99d3add12d3e453f0d54052975964b4d7e",
          "url": "https://github.com/bobluppes/graaf/commit/d7a070b460d1231044beaeb660d728c068f266de"
        },
        "date": 1789755710194,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 174647.71574233496,
            "unit": "ns/iter",
            "extra": "iterations: 4021\ncpu: 174648.91892564102 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 1018497.8231102509,
            "unit": "ns/iter",
            "extra": "iterations: 701\ncpu: 1018169.1497860261 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 2627597.144981607,
            "unit": "ns/iter",
            "extra": "iterations: 269\ncpu: 2627307.99999999 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 195009.18903128308,
            "unit": "ns/iter",
            "extra": "iterations: 3592\ncpu: 194947.89253897566 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 1185947.6779089104,
            "unit": "ns/iter",
            "extra": "iterations: 593\ncpu: 1185793.7470489058 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 3012026.5633185157,
            "unit": "ns/iter",
            "extra": "iterations: 229\ncpu: 3011282.510917037 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 37331.80471719156,
            "unit": "ns/iter",
            "extra": "iterations: 17892\ncpu: 37327.03079588644 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 157784.2128496497,
            "unit": "ns/iter",
            "extra": "iterations: 4576\ncpu: 157750.97639860146 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 1314843.3299999952,
            "unit": "ns/iter",
            "extra": "iterations: 400\ncpu: 1314717.6050000018 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 10587896.160000127,
            "unit": "ns/iter",
            "extra": "iterations: 50\ncpu: 10585999.800000004 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 76065970.23076981,
            "unit": "ns/iter",
            "extra": "iterations: 13\ncpu: 76049915.6153846 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 280641627.33333355,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 280583145.0000002 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 70168.73661941964,
            "unit": "ns/iter",
            "extra": "iterations: 9454\ncpu: 70158.05235879017 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 298937.9587813651,
            "unit": "ns/iter",
            "extra": "iterations: 2232\ncpu: 298902.9928315417 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 2441738.1602787427,
            "unit": "ns/iter",
            "extra": "iterations: 287\ncpu: 2441057.8919860604 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 19559537.350000154,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 19556269.07500001 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 136869021.71428576,
            "unit": "ns/iter",
            "extra": "iterations: 7\ncpu: 136863779.42857167 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 702155498.0000104,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 702057086 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1845197737.0000064,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1844968651.0000021 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 1600367790.9999964,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1600173904.9999983 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 1489221030.9999995,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1489067030.000001 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 1549704753.0000002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1549543397.0000007 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.0873249657044173,
            "unit": "ms/iter",
            "extra": "iterations: 8106\ncpu: 0.08731462188502351 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.13216054968945,
            "unit": "ms/iter",
            "extra": "iterations: 322\ncpu: 2.1314460465838576 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 432.80481500000434,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 432.7316835000019 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 2757.9793310000014,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2757.813965000004 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.2146666092796095,
            "unit": "ms/iter",
            "extra": "iterations: 3276\ncpu: 0.2146175497557999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 3.061227323275885,
            "unit": "ms/iter",
            "extra": "iterations: 232\ncpu: 3.06108178879309 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 280.57502000000056,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 280.5459974999991 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 3158.734220000014,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3158.407648000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.9130088227684442,
            "unit": "ms/iter",
            "extra": "iterations: 773\ncpu: 0.9128501526520125 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 6.8611442962961,
            "unit": "ms/iter",
            "extra": "iterations: 81\ncpu: 6.859985086419786 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 195.56663866666213,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 195.5342490000002 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 1805.1392019999923,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1805.0231290000056 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.11117229759503496,
            "unit": "ms/iter",
            "extra": "iterations: 6445\ncpu: 0.1111624454615961 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.1808748559556617,
            "unit": "ms/iter",
            "extra": "iterations: 361\ncpu: 2.180739019390574 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 230.7848779999991,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 230.76428083333175 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 2253.725532000004,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2253.5642339999954 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.3135091938053019,
            "unit": "ms/iter",
            "extra": "iterations: 2260\ncpu: 0.31350002300884694 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.588796847715767,
            "unit": "ms/iter",
            "extra": "iterations: 197\ncpu: 3.588432101522793 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 285.67937724999837,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 285.6645322499993 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 2657.432258,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2657.2436539999985 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.4259288919449955,
            "unit": "ms/iter",
            "extra": "iterations: 509\ncpu: 1.425761831041274 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 10.826234750000197,
            "unit": "ms/iter",
            "extra": "iterations: 60\ncpu: 10.824239066666763 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 615.3378239999938,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 615.2640330000025 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 3543.939080000001,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3543.7117889999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 5.526690267857047,
            "unit": "ms/iter",
            "extra": "iterations: 112\ncpu: 5.526386366071406 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 299.74074766666564,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 299.70295766666766 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 985.2444540000249,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 985.0980450000009 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.2647187826742045,
            "unit": "ms/iter",
            "extra": "iterations: 2655\ncpu: 0.2646959698681747 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.2434558413461954,
            "unit": "ms/iter",
            "extra": "iterations: 208\ncpu: 3.243109379807694 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 306.1096310000124,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 306.09666299999816 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 2834.3161800000016,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2834.049098999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.4197234457593677,
            "unit": "ms/iter",
            "extra": "iterations: 507\ncpu: 1.4196429151873766 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 23.90377999999974,
            "unit": "ms/iter",
            "extra": "iterations: 35\ncpu: 23.89993368571441 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 630.2451070000075,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 630.2213559999927 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 3194.4736700000076,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3194.0795119999875 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.3827765601524161,
            "unit": "ms/iter",
            "extra": "iterations: 1837\ncpu: 0.3827234921066964 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 3.874490983240288,
            "unit": "ms/iter",
            "extra": "iterations: 179\ncpu: 3.874199754189928 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 128.05466519999982,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 128.03769840000143 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 2158.2017960000144,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2157.9020400000104 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.4281681243042357,
            "unit": "ms/iter",
            "extra": "iterations: 539\ncpu: 1.4279354415584307 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 28.614061629629834,
            "unit": "ms/iter",
            "extra": "iterations: 27\ncpu: 28.61082700000008 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 681.2809319999928,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 681.1750459999928 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 3936.0832119999995,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3935.536182000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.3802709962063797,
            "unit": "ms/iter",
            "extra": "iterations: 1318\ncpu: 0.3802289021244371 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 7.261696560000246,
            "unit": "ms/iter",
            "extra": "iterations: 75\ncpu: 7.260679586666659 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 205.16568000000035,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 205.13324750000095 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 2494.9620749999895,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2494.665872999988 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.6747569940017075,
            "unit": "ms/iter",
            "extra": "iterations: 1167\ncpu: 0.6746676041131179 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 7.150567479674773,
            "unit": "ms/iter",
            "extra": "iterations: 123\ncpu: 7.1486944146341065 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 647.3200779999786,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 647.2904010000065 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 3751.2380860000007,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3750.79178 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3419011001.0000014,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3418566445.0000105 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3817366368.9999843,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3816754983.999999 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 5201976473.000002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5201218880.999989 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5774325505.000008,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5773553140.000018 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 1708369150.9999995,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1708104016.0000215 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 1483956720.000009,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1483756755.9999912 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 3952518900.000001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3951965665.000017 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2862578720.999977,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2862293684.000008 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 419748297.5000071,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 419696279.9999966 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 461956926.49999386,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 461896608.4999983 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 2910250560.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2908687574.9999876 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 2700773986.999991,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2700493010.0000024 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "8ff0cd0a0bf6ac53012dbd002e4713849bff6e52",
          "message": "perf: store neighbor lists as contiguous vectors (#434)\n\n* perf: store neighbor lists as contiguous vectors\n\nIterating an unordered_set of neighbors means chasing a heap node per\nelement. A vector keeps them contiguous, which speeds up every traversal\nand neighbor-scanning algorithm. get_neighbors() also does a single hash\nlookup instead of two.\n\nThe neighbors type alias is renamed from vertices_t to neighbors_t and is\nnow a std::vector, so neighbors are listed in edge insertion order and\nlookups by membership are linear.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* style: clang-format coloring_assertions.h\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* review: don't document or test neighbor ordering\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n---------\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-18T21:01:03+02:00",
          "tree_id": "1931f64f7dcd456849503897106b36337b72ab13",
          "url": "https://github.com/bobluppes/graaf/commit/8ff0cd0a0bf6ac53012dbd002e4713849bff6e52"
        },
        "date": 1789758311769,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 121176.01274251504,
            "unit": "ns/iter",
            "extra": "iterations: 5258\ncpu: 121160.05990871054 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 640975.3041894095,
            "unit": "ns/iter",
            "extra": "iterations: 1098\ncpu: 640944.6448087472 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1557129.2416848121,
            "unit": "ns/iter",
            "extra": "iterations: 451\ncpu: 1557109.2572062209 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 145187.79479240614,
            "unit": "ns/iter",
            "extra": "iterations: 4839\ncpu: 145161.2254598044 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 773916.289357061,
            "unit": "ns/iter",
            "extra": "iterations: 902\ncpu: 773908.8237250498 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 1955790.9777154806,
            "unit": "ns/iter",
            "extra": "iterations: 359\ncpu: 1955817.8328690429 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 37547.69081580882,
            "unit": "ns/iter",
            "extra": "iterations: 17737\ncpu: 37504.4590968033 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 158855.33100472466,
            "unit": "ns/iter",
            "extra": "iterations: 4867\ncpu: 158571.7318676802 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 1286307.1647254415,
            "unit": "ns/iter",
            "extra": "iterations: 601\ncpu: 1284559.7138103156 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 11199743.560000002,
            "unit": "ns/iter",
            "extra": "iterations: 50\ncpu: 11180728.339999996 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 79230809.99999963,
            "unit": "ns/iter",
            "extra": "iterations: 13\ncpu: 79141482.76923072 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 255359314.00000322,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 255338008.9999999 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 76568.9854138049,
            "unit": "ns/iter",
            "extra": "iterations: 9461\ncpu: 76437.44043969986 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 309761.38119227835,
            "unit": "ns/iter",
            "extra": "iterations: 2382\ncpu: 309154.8157010924 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 2520828.355400696,
            "unit": "ns/iter",
            "extra": "iterations: 287\ncpu: 2516637.7700348417 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 20754746.000000067,
            "unit": "ns/iter",
            "extra": "iterations: 30\ncpu: 20719600.299999997 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 142011632.1428578,
            "unit": "ns/iter",
            "extra": "iterations: 7\ncpu: 141838018.71428564 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 836035459.9999908,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 836031953.9999992 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1570887544.0000014,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1570770068.999998 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 777215323.9999965,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 777151078.0000029 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 980671319.999999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 980619648.0000011 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 675961818.0000046,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 675901879.0000013 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.10417870132939488,
            "unit": "ms/iter",
            "extra": "iterations: 6770\ncpu: 0.10417708892171278 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.237791972136216,
            "unit": "ms/iter",
            "extra": "iterations: 323\ncpu: 2.2376682136222956 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 362.23271249999556,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 362.1573789999992 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 2186.062438999997,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2185.8603929999986 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.24480222544951483,
            "unit": "ms/iter",
            "extra": "iterations: 2892\ncpu: 0.24477511964038665 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 3.274671529126197,
            "unit": "ms/iter",
            "extra": "iterations: 206\ncpu: 3.2743991407767035 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 274.6503550000057,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 274.6192245000003 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 2019.3347360000048,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2019.2415850000032 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.724379760373424,
            "unit": "ms/iter",
            "extra": "iterations: 964\ncpu: 0.7243801275933566 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 8.171689024096512,
            "unit": "ms/iter",
            "extra": "iterations: 83\ncpu: 8.171238746987934 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 295.57888899999796,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 295.56217700000076 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 1587.1601940000062,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1587.0877730000004 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.12851563745247224,
            "unit": "ms/iter",
            "extra": "iterations: 5260\ncpu: 0.128507189353613 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.253789794871768,
            "unit": "ms/iter",
            "extra": "iterations: 351\ncpu: 2.2535694729344864 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 261.4443650000074,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 261.42633599999954 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 1670.2428600000019,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1670.1618019999955 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.3340667317756999,
            "unit": "ms/iter",
            "extra": "iterations: 2140\ncpu: 0.33403014579439577 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.7173962063490915,
            "unit": "ms/iter",
            "extra": "iterations: 189\ncpu: 3.7173544761904616 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 263.71957333333285,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 263.705293000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 1556.890433999996,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1556.8241029999967 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.1907645976231045,
            "unit": "ms/iter",
            "extra": "iterations: 589\ncpu: 1.1907295517826806 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 10.412441196969484,
            "unit": "ms/iter",
            "extra": "iterations: 66\ncpu: 10.412190333333411 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 388.38774500000284,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 388.3686930000039 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 1677.5153439999997,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1677.4160770000037 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 7.686669695652078,
            "unit": "ms/iter",
            "extra": "iterations: 92\ncpu: 7.686369891304392 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 253.98700900000412,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 253.9671660000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 988.6819900000035,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 988.6451929999964 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.27735570279857813,
            "unit": "ms/iter",
            "extra": "iterations: 2537\ncpu: 0.27735508119826596 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.4506903284313566,
            "unit": "ms/iter",
            "extra": "iterations: 204\ncpu: 3.4505236029411583 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 185.6540234000022,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 185.62444119999952 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 1369.5678840000198,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1369.3744889999948 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.0510628858447342,
            "unit": "ms/iter",
            "extra": "iterations: 657\ncpu: 1.0508838143074544 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 13.87912423529444,
            "unit": "ms/iter",
            "extra": "iterations: 51\ncpu: 13.878250607843135 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 360.77905150000333,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 360.77449849999965 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 1803.2585210000036,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1803.1752819999979 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.39536789178469417,
            "unit": "ms/iter",
            "extra": "iterations: 1765\ncpu: 0.39535155807365324 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 4.4886869030302945,
            "unit": "ms/iter",
            "extra": "iterations: 165\ncpu: 4.488359248484795 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 373.5576254999984,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 373.5480469999999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 2146.4791520000117,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2146.357851999994 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.343461885658884,
            "unit": "ms/iter",
            "extra": "iterations: 516\ncpu: 1.3433830193798504 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 20.34435632352975,
            "unit": "ms/iter",
            "extra": "iterations: 34\ncpu: 20.342891558823673 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 463.6597375000093,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 463.64686350000284 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 2373.9286020000063,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2373.7991469999997 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.5864825590650619,
            "unit": "ms/iter",
            "extra": "iterations: 3166\ncpu: 0.5864520840176846 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 9.10363328409115,
            "unit": "ms/iter",
            "extra": "iterations: 88\ncpu: 9.103409125000022 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 404.10811750000164,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 404.0810949999951 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 2083.0163669999993,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2082.877583999988 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.8296116175115058,
            "unit": "ms/iter",
            "extra": "iterations: 1519\ncpu: 0.8295729795918362 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 7.878300545454535,
            "unit": "ms/iter",
            "extra": "iterations: 88\ncpu: 7.87829056818187 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 378.4206139999924,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 378.39085500000164 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 1453.666577000007,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1453.6125959999993 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3291226512.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3291103875.000005 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3030964807.000004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3030828976.9999986 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4671972138.000001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4671774481 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 4750242406.000012,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4749281311.000004 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 1080031530.0000136,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1080017705.0000172 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 597025556.9999949,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 596993273.0000095 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 3649237988.9999995,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3649032330.0000114 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 3065558137.0000105,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3062224686.0000076 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 229846533.33333918,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 229821780.9999983 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 235880677.33334127,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 235871537.33332872 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 2101855247.9999926,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2101768601.0000033 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1386587527.0000174,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1386537689.999983 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "758c871b0555fccf92eb065b6a1012a5866480dc",
          "message": "refactor: remove add_vertex(vertex, id) so the graph owns id assignment (#436)\n\n* refactor: remove add_vertex(vertex, id) so the graph owns id assignment\n\nThe graph now always assigns vertex ids itself, keeping them dense.\nget_transposed_graph() preserves ids across the transpose via a private,\nfriend-only hook rather than the public overload. Perf benchmark harness\nutilities that relied on caller-chosen ids now keep a local\nexternal-id-to-vertex-id map instead.\n\nCloses #432\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* fix: address review feedback and clang-format violations\n\nKeep the id-ownership rationale in graph.h general (fine-grained id\ncontrol for befriended algorithms) instead of tying it to\nget_transposed_graph specifically, and drop \"densely packed\" as public\nrationale since id-assignment strategy is an implementation detail we\nwant to keep free to change.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n---------\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-18T23:42:35+02:00",
          "tree_id": "280c214e4e42e7491fed1972f290fa270889b9c6",
          "url": "https://github.com/bobluppes/graaf/commit/758c871b0555fccf92eb065b6a1012a5866480dc"
        },
        "date": 1789767992956,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 120181.6239209448,
            "unit": "ns/iter",
            "extra": "iterations: 5794\ncpu: 120160.23627891006 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 716224.0770007103,
            "unit": "ns/iter",
            "extra": "iterations: 987\ncpu: 716282.278622094 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1813530.174479272,
            "unit": "ns/iter",
            "extra": "iterations: 384\ncpu: 1813218.458333342 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 144763.71637763883,
            "unit": "ns/iter",
            "extra": "iterations: 4848\ncpu: 144730.5856023178 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 899672.5488431901,
            "unit": "ns/iter",
            "extra": "iterations: 778\ncpu: 899653.7287917786 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 2254722.148386775,
            "unit": "ns/iter",
            "extra": "iterations: 310\ncpu: 2254413.993548377 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 37228.42091675638,
            "unit": "ns/iter",
            "extra": "iterations: 17431\ncpu: 37201.13453043427 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 157320.80974325468,
            "unit": "ns/iter",
            "extra": "iterations: 4557\ncpu: 157154.51503181917 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 1312458.4850000076,
            "unit": "ns/iter",
            "extra": "iterations: 400\ncpu: 1311140.0350000001 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 10355552.799999638,
            "unit": "ns/iter",
            "extra": "iterations: 60\ncpu: 10343250.300000021 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 71970259.92857066,
            "unit": "ns/iter",
            "extra": "iterations: 14\ncpu: 71907498.64285716 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 512946360.9999902,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 512787124.9999991 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 74512.01598295079,
            "unit": "ns/iter",
            "extra": "iterations: 9385\ncpu: 74416.80788492292 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 298063.9123733963,
            "unit": "ns/iter",
            "extra": "iterations: 2271\ncpu: 297716.3425803614 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 2432279.402061804,
            "unit": "ns/iter",
            "extra": "iterations: 291\ncpu: 2429108.9862542986 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 19441650.49999995,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 19414723.474999994 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 137540303.75000072,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 137362463.12500012 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 725034858.000015,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 724981059.000001 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1349769705,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1349645200.0000012 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 706746156.0000083,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 706669323.9999964 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 812724550.0000129,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 812652577.0000014 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 523373082.99999565,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 523295410.0000029 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09333192343480194,
            "unit": "ms/iter",
            "extra": "iterations: 7523\ncpu: 0.09332563152997468 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.074065536809805,
            "unit": "ms/iter",
            "extra": "iterations: 326\ncpu: 2.0738875582822165 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 503.4184620000133,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 503.3633199999983 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 3320.8822050000035,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3320.6516770000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.2235863992248097,
            "unit": "ms/iter",
            "extra": "iterations: 3096\ncpu: 0.22357364534883883 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 3.0088068026316748,
            "unit": "ms/iter",
            "extra": "iterations: 228\ncpu: 3.008578807017521 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 425.5371720000056,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 425.5137170000012 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 3187.4451440000084,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3187.2211869999987 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.8343380738498659,
            "unit": "ms/iter",
            "extra": "iterations: 826\ncpu: 0.8342913680387387 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 8.397551129411674,
            "unit": "ms/iter",
            "extra": "iterations: 85\ncpu: 8.396705352941199 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 454.7349095000044,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 454.6886167499995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 2865.552543000007,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2865.318737000003 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.11548173923127633,
            "unit": "ms/iter",
            "extra": "iterations: 6036\ncpu: 0.11547048856858783 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.0741546720430395,
            "unit": "ms/iter",
            "extra": "iterations: 372\ncpu: 2.0739268790322436 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 229.6592520000047,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 229.63707000000255 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 2138.9565470000207,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2138.7223579999954 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.32558510301623594,
            "unit": "ms/iter",
            "extra": "iterations: 2155\ncpu: 0.3255593429234321 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.4100476108375206,
            "unit": "ms/iter",
            "extra": "iterations: 203\ncpu: 3.409686389162578 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 231.3735931999986,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 231.34745039999984 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 2793.6152339999862,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2793.3969890000017 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.3415661973684052,
            "unit": "ms/iter",
            "extra": "iterations: 532\ncpu: 1.3414907499999789 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 9.944110546875162,
            "unit": "ms/iter",
            "extra": "iterations: 64\ncpu: 9.943103906250084 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 407.58807899999283,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 407.5526620000005 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 2688.752416,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2688.580223999992 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 5.762284133333264,
            "unit": "ms/iter",
            "extra": "iterations: 135\ncpu: 5.761229881481448 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 238.2867645000033,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 238.27130824999898 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 817.7647830000296,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 817.682241 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.2648851253811072,
            "unit": "ms/iter",
            "extra": "iterations: 2624\ncpu: 0.2648658669969515 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.2907582452828743,
            "unit": "ms/iter",
            "extra": "iterations: 212\ncpu: 3.2906095283019052 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 364.25449349999894,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 364.22283600000327 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 2785.0082369999996,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2784.7688519999992 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.0653999597522512,
            "unit": "ms/iter",
            "extra": "iterations: 646\ncpu: 1.0652127554179383 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 14.884653480768643,
            "unit": "ms/iter",
            "extra": "iterations: 52\ncpu: 14.88388001923068 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 609.3882289999897,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 609.3206279999919 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 3161.5728560000207,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3161.3384730000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.3925363545505132,
            "unit": "ms/iter",
            "extra": "iterations: 1791\ncpu: 0.3925007811278606 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 4.174543249999847,
            "unit": "ms/iter",
            "extra": "iterations: 168\ncpu: 4.1744334761905035 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 506.3438199999837,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 506.28260799999225 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 3386.265699999967,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3385.9758600000023 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.5904482476636048,
            "unit": "ms/iter",
            "extra": "iterations: 428\ncpu: 1.5903017710280571 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 19.468882242425465,
            "unit": "ms/iter",
            "extra": "iterations: 33\ncpu: 19.468184818181857 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 443.64782649998347,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 443.6056225000016 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 3331.157582000003,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3330.883897000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.548153923999962,
            "unit": "ms/iter",
            "extra": "iterations: 1000\ncpu: 0.5480968309999952 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 7.0963221636361595,
            "unit": "ms/iter",
            "extra": "iterations: 110\ncpu: 7.096001118181825 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 355.51894200000334,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 355.48130450000315 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 2505.2808119999668,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2505.1094889999918 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.548744598755842,
            "unit": "ms/iter",
            "extra": "iterations: 1286\ncpu: 0.548695832037328 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 8.373545558822904,
            "unit": "ms/iter",
            "extra": "iterations: 68\ncpu: 8.373035382352946 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 384.30839600002287,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 384.30314449999514 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 1937.8455949999989,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1937.71137600001 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3135881951.999977,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3135620138.9999967 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3768581535.999999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3766489645.000007 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4794256663.999989,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4793838708.999999 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5630560971.000023,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5628995975.00001 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 764624507.9999971,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 764599914.9999909 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 502240591.0000316,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 502210009.99999887 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 2909465826.00003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2908900622.0000043 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2648110904.0000205,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2647760224.000024 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 205320779.3333248,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 205288085.66666612 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 234505799.33334363,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 234478619.6666651 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1483937465.9999862,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1483818740.9999933 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1166111946.000001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1166044956.0000074 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "64a3a9bddf5ad99524118928d5980192db24d364",
          "message": "refactor: reuse vertex ids freed by remove_vertex (#437)\n\n* refactor: reuse vertex ids freed by remove_vertex\n\nadd_vertex() now hands out ids freed by remove_vertex() before growing\npast the current high-water mark, so a graph under sustained add/remove\nchurn stays bounded by its concurrently-live vertex count rather than\nthe total number of vertices ever created. This is a prerequisite for\nswitching vertex storage to a contiguous, id-indexed container (#433).\n\nIds are not stable past a vertex's removal: a freed id may be handed\nout to a different vertex afterwards. Documented as part of the public\nadd_vertex()/remove_vertex() contract.\n\nCloses #435\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* fix: address review feedback on vertex id reuse\n\nMove free_vertex_ids_ above vertex_id_supplier_ to keep the two id\nbookkeeping members grouped together. Document and test why the\nwhile loop scanning for a free id is still required: add_vertex_with_id()\n(used by get_transposed_graph()) inserts directly, bypassing both\nfree_vertex_ids_ and vertex_id_supplier_, so the supplier can lag behind\nids that already exist and a single increment isn't always enough.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* fix: make the transpose id-collision test assert what it claims\n\nThe previous version's only real assertion was the vertex count; the\nhas_vertex() check was tautological (add_vertex() just inserted at\nthat id) and the three original ids were discarded via\n[[maybe_unused]] instead of being checked against.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* fix: keep the transpose id-collision test comment high level\n\nDrop the explanation of emplace()'s no-op-on-existing-key semantics -\nthat's an unordered_map implementation detail, not something the test\nneeds to justify its assertions.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n---------\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-19T00:23:32+02:00",
          "tree_id": "2affa7da888b4d4fb82974f36b508479187b806d",
          "url": "https://github.com/bobluppes/graaf/commit/64a3a9bddf5ad99524118928d5980192db24d364"
        },
        "date": 1789770463791,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 120929.9847832129,
            "unit": "ns/iter",
            "extra": "iterations: 5783\ncpu: 120930.6787134703 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 719764.6578148324,
            "unit": "ns/iter",
            "extra": "iterations: 979\ncpu: 719735.2155260522 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1844253.3550887557,
            "unit": "ns/iter",
            "extra": "iterations: 383\ncpu: 1843989.054830283 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 146382.08681719092,
            "unit": "ns/iter",
            "extra": "iterations: 4665\ncpu: 146391.2006430887 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 897860.0855674067,
            "unit": "ns/iter",
            "extra": "iterations: 783\ncpu: 897898.8825031698 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 2283768.27973866,
            "unit": "ns/iter",
            "extra": "iterations: 311\ncpu: 2283420.9035370126 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 38492.195120568744,
            "unit": "ns/iter",
            "extra": "iterations: 17625\ncpu: 38491.54377304968 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 160786.80251430342,
            "unit": "ns/iter",
            "extra": "iterations: 4375\ncpu: 160769.4710857146 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 1336890.935000099,
            "unit": "ns/iter",
            "extra": "iterations: 400\ncpu: 1336828.3925 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 10722838.399999546,
            "unit": "ns/iter",
            "extra": "iterations: 50\ncpu: 10721803.879999997 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 77463200.07691583,
            "unit": "ns/iter",
            "extra": "iterations: 13\ncpu: 77456932.84615384 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 506362139.9999647,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 506276782.0000005 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 74913.20554787802,
            "unit": "ns/iter",
            "extra": "iterations: 9409\ncpu: 74908.53225635033 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 297702.377748485,
            "unit": "ns/iter",
            "extra": "iterations: 2274\ncpu: 297693.7717678096 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 2398312.361203982,
            "unit": "ns/iter",
            "extra": "iterations: 299\ncpu: 2398088.0668896376 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 19411727.924997993,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 19410728.199999917 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 138665394.0000002,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 138654886.99999994 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 733751822.9999205,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 733670636.9999994 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1369235823.9999294,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1369120791.999997 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 723522193.000008,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 723397128.000002 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 828925160.9999155,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 828872430.000004 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 571747844.000015,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 571647566.9999994 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09371856712656117,
            "unit": "ms/iter",
            "extra": "iterations: 7538\ncpu: 0.09370328349694879 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.147042774691463,
            "unit": "ms/iter",
            "extra": "iterations: 324\ncpu: 2.1468653425926 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 534.8561800000198,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 534.7875920000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 3303.488207999976,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3303.211324000003 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.22457792602123947,
            "unit": "ms/iter",
            "extra": "iterations: 3109\ncpu: 0.2245584708909626 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 3.0696586133333565,
            "unit": "ms/iter",
            "extra": "iterations: 225\ncpu: 3.0694498222222126 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 449.25255950005294,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 449.1990085000026 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 3173.7644070000215,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3173.4621270000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.8453505235731977,
            "unit": "ms/iter",
            "extra": "iterations: 806\ncpu: 0.8452345595533476 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 8.554135611764062,
            "unit": "ms/iter",
            "extra": "iterations: 85\ncpu: 8.55335825882356 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 564.4077250000237,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 564.3062279999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 2492.0249459999013,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2491.759803000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.1167820114842472,
            "unit": "ms/iter",
            "extra": "iterations: 5747\ncpu: 0.11677629284844315 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.091447790960334,
            "unit": "ms/iter",
            "extra": "iterations: 354\ncpu: 2.0913113926553546 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 144.12590499999092,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 144.12308816666788 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 2408.7593230000266,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2408.3761060000056 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.33563865741175775,
            "unit": "ms/iter",
            "extra": "iterations: 2125\ncpu: 0.3355871524705863 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.523437551020764,
            "unit": "ms/iter",
            "extra": "iterations: 196\ncpu: 3.522877724489763 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 147.92082399998208,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 147.90229999999838 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 2312.218707999932,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2312.0252959999875 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.2440365657656347,
            "unit": "ms/iter",
            "extra": "iterations: 555\ncpu: 1.2438430846846888 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 10.530600436619723,
            "unit": "ms/iter",
            "extra": "iterations: 71\ncpu: 10.529703802816925 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 307.6289573333118,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 307.58486999999946 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 2532.8232169999865,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2532.5429600000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 5.982462299999725,
            "unit": "ms/iter",
            "extra": "iterations: 100\ncpu: 5.982213730000012 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 235.3861936666893,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 235.36785600000107 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 857.8970229999641,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 857.8416969999978 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.271690741285826,
            "unit": "ms/iter",
            "extra": "iterations: 2582\ncpu: 0.27166251859024104 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.3135269850746947,
            "unit": "ms/iter",
            "extra": "iterations: 201\ncpu: 3.31307771641787 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 141.62593160001506,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 141.62153039999907 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 1982.340077999993,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1982.1317960000044 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.0876748122205042,
            "unit": "ms/iter",
            "extra": "iterations: 671\ncpu: 1.0875775245901635 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 14.738731100001132,
            "unit": "ms/iter",
            "extra": "iterations: 50\ncpu: 14.738310339999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 546.268591999933,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 546.1870410000103 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 3419.3544070000144,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3419.019891000005 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.40498297638249403,
            "unit": "ms/iter",
            "extra": "iterations: 1736\ncpu: 0.40492836290322104 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 4.034748106508867,
            "unit": "ms/iter",
            "extra": "iterations: 169\ncpu: 4.0343446982248485 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 339.8961783333334,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 339.8664043333355 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 2609.472903999972,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2609.1804050000037 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.5779547963801,
            "unit": "ms/iter",
            "extra": "iterations: 442\ncpu: 1.5776868144796268 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 20.307045470588037,
            "unit": "ms/iter",
            "extra": "iterations: 34\ncpu: 20.3067668823531 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 720.1358099999879,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 720.057330000003 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 3618.0075220000845,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3617.694240999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.49039958555135593,
            "unit": "ms/iter",
            "extra": "iterations: 1315\ncpu: 0.49032057338403184 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 5.610914431372294,
            "unit": "ms/iter",
            "extra": "iterations: 102\ncpu: 5.610796450980476 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 570.7541040000024,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 570.6530310000062 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 3437.9986840000356,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3437.7055530000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.734170334519477,
            "unit": "ms/iter",
            "extra": "iterations: 843\ncpu: 0.734036790035593 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 9.036954741935505,
            "unit": "ms/iter",
            "extra": "iterations: 93\ncpu: 9.036021462365596 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 321.09517933334547,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 321.06089233333535 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 2699.383606999959,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2699.1094730000073 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3263959825.000029,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3263646897.000001 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 4158763861.0000114,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4158367098.0000134 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 5004632226.000012,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5004154324.999973 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5790786584.999978,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5788546700.999973 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 781539479.0000027,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 781410451.9999887 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 502040089.0000474,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 502033604.99997985 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 2981451338.0000563,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2981107374.000004 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2721991081.000056,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2721661454.000014 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 218582919.33335748,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 218566588.9999958 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 264967926.66667566,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 263899791.00000003 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1631364351.000002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1631204911.999987 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1269531530.9999843,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1269436684.999988 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "3f83193f079aed8af68f28d28baf9e4022554b94",
          "message": "perf: store vertices in a dense vector indexed by id (#438)\n\n* perf: store vertices in a dense vector indexed by id\n\nFirst of two staged changes for #433 (adjacency storage is a planned\nfollow-up). vertices_ moves from unordered_map<vertex_id_t, VERTEX_T>\nto vector<optional<VERTEX_T>>, indexed directly by id - viable now that\nids are always graph-owned and kept dense (#432, #435). has_vertex()\nand get_vertex() become a bounds check plus direct index instead of a\nhash lookup. vertex_count() gets its own counter since vertices_.size()\nnow counts tombstoned slots too.\n\nget_vertices() moves from returning a direct reference to the internal\nmap (every real caller only ever destructured (id, value) pairs or, in\none case, called .size() when vertex_count() already existed for that)\nto a lazy std::ranges view yielding the same (id, value) shape. This\nalso means the accessor's return type no longer has to change again\nthe next time internal storage does.\n\nBenchmarked with perf/graaflib/add_vertex_benchmark.cpp (Release):\nbm_add_primitive_numeric_vertex is 3.6-4.6x faster across the 1K-10M\nrange; bm_add_user_defined_vertex (a type with real move cost) is\n1.1-1.6x faster.\n\nOne test (GreedyGraphColoringTest.BasicGraphColoring) hardcoded the\nexact coloring produced by the old map's iteration order rather than\nverifying properness like its sibling tests already do - fixed to use\nis_proper_coloring(), matching the established pattern.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* fix: address review feedback on dense vertex storage\n\n- Replace the composed std::views pipeline behind get_vertices() with a\n  hand-rolled vertex_view/iterator: std::views::filter's begin() caches\n  state and can't be const, which meant the previous implementation\n  could only be iterated directly, not stored in a const variable as a\n  read-only view should support. The new view has const begin()/end(),\n  works with std::ranges algorithms (e.g. vertex_properties.tpp's\n  count_if), and is verified with a new regression test covering both\n  const-by-value and const-by-reference storage.\n- Move get_vertices()'s implementation out of graph.h into graph.tpp,\n  matching how every other non-trivial member is defined.\n- remove_vertex() now returns immediately for an id that was never\n  assigned, instead of still scanning every entry in adjacency_list_\n  looking for a neighbor reference that can't exist.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* fix: trim remove_vertex() early-return comment\n\nState the invariant, not the hypothetical consequence of skipping it.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n---------\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-19T13:52:25+02:00",
          "tree_id": "b2fc33ae9d94e8b57d0ef0ca2c6588ba2bbd9bdf",
          "url": "https://github.com/bobluppes/graaf/commit/3f83193f079aed8af68f28d28baf9e4022554b94"
        },
        "date": 1789818983216,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 111450.75059039949,
            "unit": "ns/iter",
            "extra": "iterations: 6351\ncpu: 111459.33632498806 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 588213.3241200832,
            "unit": "ns/iter",
            "extra": "iterations: 1194\ncpu: 588311.3308207705 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1700504.2046515576,
            "unit": "ns/iter",
            "extra": "iterations: 430\ncpu: 1700574.9976744258 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 134347.3155673758,
            "unit": "ns/iter",
            "extra": "iterations: 5216\ncpu: 134333.51399540072 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 748670.56791444,
            "unit": "ns/iter",
            "extra": "iterations: 935\ncpu: 748779.2192513192 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 2043000.2588235938,
            "unit": "ns/iter",
            "extra": "iterations: 340\ncpu: 2042990.958823514 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 4980.482663008416,
            "unit": "ns/iter",
            "extra": "iterations: 137769\ncpu: 4979.560089715393 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 20107.81063860021,
            "unit": "ns/iter",
            "extra": "iterations: 35155\ncpu: 20104.139325842694 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 152720.94681267053,
            "unit": "ns/iter",
            "extra": "iterations: 5114\ncpu: 152707.2199843567 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 1249253.7307060675,
            "unit": "ns/iter",
            "extra": "iterations: 609\ncpu: 1249191.0394088668 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 10145067.40845068,
            "unit": "ns/iter",
            "extra": "iterations: 71\ncpu: 10143541.239436615 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 49491008.28571318,
            "unit": "ns/iter",
            "extra": "iterations: 14\ncpu: 49489186.428571336 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 34733.55710516275,
            "unit": "ns/iter",
            "extra": "iterations: 15918\ncpu: 34692.92737781125 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 172680.42811561815,
            "unit": "ns/iter",
            "extra": "iterations: 5328\ncpu: 172408.51163663657 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 1133682.1769547407,
            "unit": "ns/iter",
            "extra": "iterations: 486\ncpu: 1132762.907407409 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 10951047.340000175,
            "unit": "ns/iter",
            "extra": "iterations: 50\ncpu: 10932852.860000005 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 74598628.37499997,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 74520680.37500003 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 435519394.5000053,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 435157872.4999996 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1293168856.9999835,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1292991469.0000005 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 700609318.000005,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 700511333.999998 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 788432701.000005,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 788409741.9999989 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 582067166.999991,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 582034378.000003 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.0946285214410541,
            "unit": "ms/iter",
            "extra": "iterations: 7439\ncpu: 0.09462018604651225 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.126788976261162,
            "unit": "ms/iter",
            "extra": "iterations: 337\ncpu: 2.126649507418415 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 428.00344600000057,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 427.9774459999999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 3174.0279789999877,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3173.7164960000046 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.22558840735916788,
            "unit": "ms/iter",
            "extra": "iterations: 3071\ncpu: 0.22557070400521018 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 3.1858911288888216,
            "unit": "ms/iter",
            "extra": "iterations: 225\ncpu: 3.1857408888888648 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 557.3863420000009,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 557.3681970000024 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 3257.4221449999923,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3257.086964000003 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.7681008134592628,
            "unit": "ms/iter",
            "extra": "iterations: 847\ncpu: 0.7680296328217264 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 7.532545443037674,
            "unit": "ms/iter",
            "extra": "iterations: 79\ncpu: 7.5310104556961655 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 190.65671299999565,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 190.64547674999943 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 1919.1749270000003,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1919.0274589999988 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.11879085198615266,
            "unit": "ms/iter",
            "extra": "iterations: 6067\ncpu: 0.11878200164826176 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.1611056234567383,
            "unit": "ms/iter",
            "extra": "iterations: 324\ncpu: 2.161017249999994 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 152.2738048000008,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 152.2633342000006 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 1660.8658970000079,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1660.7090029999938 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.32156878094800423,
            "unit": "ms/iter",
            "extra": "iterations: 2173\ncpu: 0.3215386304647933 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.711027026315755,
            "unit": "ms/iter",
            "extra": "iterations: 190\ncpu: 3.710817673684262 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 377.116991500003,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 377.0980159999979 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 2879.7273090000035,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2879.5832200000004 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.2676962468239403,
            "unit": "ms/iter",
            "extra": "iterations: 551\ncpu: 1.2676066152449852 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 10.632464342856858,
            "unit": "ms/iter",
            "extra": "iterations: 70\ncpu: 10.632043342857246 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 639.9635680000131,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 639.9192020000015 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 3728.4401059999936,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3728.191713000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 5.3799070756301415,
            "unit": "ms/iter",
            "extra": "iterations: 119\ncpu: 5.37947687394952 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 232.06832625000118,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 232.0476902500026 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 783.1104129999744,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 782.1200070000032 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.26697245157614446,
            "unit": "ms/iter",
            "extra": "iterations: 2633\ncpu: 0.2669476942650976 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.275733219626169,
            "unit": "ms/iter",
            "extra": "iterations: 214\ncpu: 3.2756145420560676 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 504.6516883333349,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 504.61548033333275 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 3539.9882649999768,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3539.720951999996 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.2474347540395418,
            "unit": "ms/iter",
            "extra": "iterations: 557\ncpu: 1.2473362190305255 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 16.22482430952454,
            "unit": "ms/iter",
            "extra": "iterations: 42\ncpu: 16.222337000000056 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 541.1829090000424,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 541.1818179999983 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 3349.052676000042,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3348.691682999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.3900449259259395,
            "unit": "ms/iter",
            "extra": "iterations: 1782\ncpu: 0.390020904601571 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 4.179156162650661,
            "unit": "ms/iter",
            "extra": "iterations: 166\ncpu: 4.178665415662682 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 556.4179450000211,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 556.4065039999946 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 3430.5754160000106,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3430.2337639999932 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.504559147126421,
            "unit": "ms/iter",
            "extra": "iterations: 435\ncpu: 1.5044500666666583 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 19.057789666665787,
            "unit": "ms/iter",
            "extra": "iterations: 36\ncpu: 19.05641408333341 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 431.1881595000102,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 431.14972400000084 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 2307.1970450000094,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2307.006259000005 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.4947849180529835,
            "unit": "ms/iter",
            "extra": "iterations: 1623\ncpu: 0.49475645471349783 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 7.906781115789392,
            "unit": "ms/iter",
            "extra": "iterations: 95\ncpu: 7.905418494736768 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 572.7478640000072,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 572.7374330000004 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 3421.130940000012,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3419.512016999988 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.5880805010000358,
            "unit": "ms/iter",
            "extra": "iterations: 1000\ncpu: 0.5880417580000028 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 7.094259225806293,
            "unit": "ms/iter",
            "extra": "iterations: 93\ncpu: 7.093754096774224 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 391.53530100000467,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 391.4996664999961 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 2974.061013000039,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2973.8178489999996 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3134078030.000012,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3133780438.0000024 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3833603252.9999785,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3831584033.000013 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4905839638.999965,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4905381616 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5700451168.00003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5697374575.999988 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 701048140.0000117,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 700943812.0000198 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 488113503.4999886,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 488061095.49998665 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 2715193522.0000496,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2714828569.0000196 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2654003659.0000114,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2651448306.00002 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 219853408.249989,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 219833978.24999428 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 260543684.33333746,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 260533832.3333323 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1567336275.999992,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1567152971.0000129 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1206732009.9999962,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1204045976.9999926 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "4b3042e995f5bede4a793bfbf6a1fdbf3ac204ab",
          "message": "perf: store adjacency in a dense vector indexed by id (#442)\n\nSecond of two staged changes for #433 (vertex storage landed in #438).\nedges_ stays a hash map, unchanged - out of scope for this issue, see\nthe PR discussion on #438 for why.\n\nadjacency_list_ moves from unordered_map<vertex_id_t, neighbors_t> to\nvector<neighbors_t>, indexed directly by id and resized in lockstep\nwith vertices_ (grown together in add_vertex()/add_vertex_with_id(),\nnever shrunk - a removed vertex's slot is cleared, not erased, mirroring\nhow vertices_ tombstones a removed vertex rather than erasing its\nslot). get_neighbors() becomes a bounds check plus direct index instead\nof a hash lookup.\n\nremove_vertex()'s neighbor-cleanup scan now uses std::erase()'s return\nvalue to skip the edges_ lookup entirely for every vertex that wasn't\nactually connected to the one being removed, rather than always\nattempting it - a correctness-preserving tightening of the same loop\nthis PR already has to touch for the container swap (same principle\nthe #438 review applied to the early-return case).\n\nBenchmarked with perf/graaflib/add_edge_benchmark.cpp (Release):\nbm_add_primitive_numeric_edge is 1.4-1.5x faster, bm_add_user_defined_edge\nis 1.25-1.4x faster. bm_breadth_first_search on web-Google/web-BerkStan\nis flat - expected, since #434 already made the per-vertex neighbor\nlists contiguous, so this change only removes one hash lookup per\nvertex visited, which is amortized away by scanning that vertex's\n(already-contiguous) edge list on graphs with real average degree.\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-19T14:34:59+02:00",
          "tree_id": "f15f459467ad9cdef2d12bf7416fc63d5e647498",
          "url": "https://github.com/bobluppes/graaf/commit/4b3042e995f5bede4a793bfbf6a1fdbf3ac204ab"
        },
        "date": 1789821550619,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 56199.513775513544,
            "unit": "ns/iter",
            "extra": "iterations: 11651\ncpu: 56192.97759848918 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 309240.7510651849,
            "unit": "ns/iter",
            "extra": "iterations: 2113\ncpu: 309207.10411736666 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 838933.2562746014,
            "unit": "ns/iter",
            "extra": "iterations: 757\ncpu: 839087.5482166541 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 74008.8785249227,
            "unit": "ns/iter",
            "extra": "iterations: 8759\ncpu: 74013.75282566443 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 432098.11090103944,
            "unit": "ns/iter",
            "extra": "iterations: 1587\ncpu: 432131.6635160606 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 1185752.1182606018,
            "unit": "ns/iter",
            "extra": "iterations: 575\ncpu: 1185776.7704347689 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 8651.415781437303,
            "unit": "ns/iter",
            "extra": "iterations: 60907\ncpu: 8639.856683139877 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 34341.43308136911,
            "unit": "ns/iter",
            "extra": "iterations: 15743\ncpu: 34332.78396747759 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 350589.35524125956,
            "unit": "ns/iter",
            "extra": "iterations: 2404\ncpu: 350512.4579866886 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 2984690.3800737527,
            "unit": "ns/iter",
            "extra": "iterations: 271\ncpu: 2984532.4833948314 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 19336489.09375041,
            "unit": "ns/iter",
            "extra": "iterations: 32\ncpu: 19333659.031250007 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 88418537.9999991,
            "unit": "ns/iter",
            "extra": "iterations: 6\ncpu: 88389047.9999998 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 37927.04922978181,
            "unit": "ns/iter",
            "extra": "iterations: 15580\ncpu: 37920.22792041069 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 168012.2585526312,
            "unit": "ns/iter",
            "extra": "iterations: 6080\ncpu: 167988.64901315802 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 1282005.2380952856,
            "unit": "ns/iter",
            "extra": "iterations: 462\ncpu: 1281866.5714285688 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 11270182.719999867,
            "unit": "ns/iter",
            "extra": "iterations: 50\ncpu: 11267387.540000016 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 86648927.1000006,
            "unit": "ns/iter",
            "extra": "iterations: 10\ncpu: 86618993.99999982 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 330066161.9999943,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 329991959.49999917 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1634110866.0000145,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1633893171.0000005 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 940448485.0000472,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 940372553.9999996 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 999178782.0000013,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 999025582.0000015 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 740919729.0000407,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 740861273.0000001 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.08294741600703687,
            "unit": "ms/iter",
            "extra": "iterations: 9096\ncpu: 0.08293157464819749 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.069609653333373,
            "unit": "ms/iter",
            "extra": "iterations: 375\ncpu: 2.069423336 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 132.93108800000178,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 132.9120795000011 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 2165.940433000003,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2165.6462619999957 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.18024317317769997,
            "unit": "ms/iter",
            "extra": "iterations: 4198\ncpu: 0.18021672224869031 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 2.8355129670328325,
            "unit": "ms/iter",
            "extra": "iterations: 273\ncpu: 2.8349498461538376 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 96.96736114286101,
            "unit": "ms/iter",
            "extra": "iterations: 7\ncpu: 96.95843100000039 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 584.9848150000412,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 584.899489999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.5627396304909548,
            "unit": "ms/iter",
            "extra": "iterations: 1161\ncpu: 0.5626509285099057 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 6.700493934959272,
            "unit": "ms/iter",
            "extra": "iterations: 123\ncpu: 6.699569512195157 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 175.91899766667515,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 175.11518899999837 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 772.3749250000083,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 772.278301 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.1017252494028396,
            "unit": "ms/iter",
            "extra": "iterations: 7117\ncpu: 0.10170673429815924 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.1565394500000554,
            "unit": "ms/iter",
            "extra": "iterations: 340\ncpu: 2.1561643029411632 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 123.10851539999703,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 123.09617859999946 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 1096.7983520000075,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1096.6069340000004 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.22624579598309255,
            "unit": "ms/iter",
            "extra": "iterations: 2838\ncpu: 0.22621014270613132 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.2641241617647117,
            "unit": "ms/iter",
            "extra": "iterations: 204\ncpu: 3.2635062696078205 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 202.3224533333329,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 202.29809466666873 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 2595.7147150000424,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2591.894283000002 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.0021368090787648,
            "unit": "ms/iter",
            "extra": "iterations: 749\ncpu: 1.0020190200267016 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 9.040624585713886,
            "unit": "ms/iter",
            "extra": "iterations: 70\ncpu: 9.038503485714143 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 207.59227800001176,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 207.5581489999981 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 2423.9847709999935,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2423.6111760000085 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 5.991876076190498,
            "unit": "ms/iter",
            "extra": "iterations: 105\ncpu: 5.990953647619113 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 330.25688766665934,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 330.21953666666565 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 1026.0696930000108,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1025.8695400000022 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.21424951498868838,
            "unit": "ms/iter",
            "extra": "iterations: 3536\ncpu: 0.21392342958144908 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.295480012658206,
            "unit": "ms/iter",
            "extra": "iterations: 237\ncpu: 3.294860949367082 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 168.79843825000762,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 168.77018100000285 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 2349.5734420000076,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2349.2577739999942 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.0372141043613827,
            "unit": "ms/iter",
            "extra": "iterations: 642\ncpu: 1.0371124283488982 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 16.573788266667734,
            "unit": "ms/iter",
            "extra": "iterations: 45\ncpu: 16.569337977777664 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 241.80809033333617,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 241.79346566666973 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 1168.1639229999519,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1167.932214000004 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.2987281902349124,
            "unit": "ms/iter",
            "extra": "iterations: 2171\ncpu: 0.29869679502533425 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 3.7219172471907314,
            "unit": "ms/iter",
            "extra": "iterations: 178\ncpu: 3.719413943820235 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 134.5122357499946,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 134.4929239999999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 1376.1229919999778,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1375.929309 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.1010588153365082,
            "unit": "ms/iter",
            "extra": "iterations: 639\ncpu: 1.1009309796557045 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 17.556469942857284,
            "unit": "ms/iter",
            "extra": "iterations: 35\ncpu: 17.55387305714302 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 223.23373933333338,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 223.19178933333225 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 1081.2203119999708,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1081.020129999999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.5817730843315881,
            "unit": "ms/iter",
            "extra": "iterations: 2087\ncpu: 0.5816669132726392 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 7.528295355371498,
            "unit": "ms/iter",
            "extra": "iterations: 121\ncpu: 7.52731928925619 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 177.5228712500052,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 177.49659200000067 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 1875.4240129999857,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1875.1255509999964 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.6230098460000022,
            "unit": "ms/iter",
            "extra": "iterations: 1000\ncpu: 0.6229693629999957 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 7.847171725663542,
            "unit": "ms/iter",
            "extra": "iterations: 113\ncpu: 7.845954539823046 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 211.4099883333438,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 211.36521800000216 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 2266.011037999988,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2265.6371639999975 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 4156069151.999986,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4155479425.9999995 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 5071485827.000004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5070823642.000008 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 6487661887.999991,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6486206654.9999895 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 8031862741.999987,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8029714178.999995 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 998841448.9999968,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 998684201.0000032 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 660318715.9999493,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 660208506.0000036 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 3843580721.0000234,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3843031547.999999 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 3358951042.9999905,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3358224110.000009 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 302888208.00001305,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 302858564.99999875 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 337937073.0000062,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 337851049.50000286 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1996073633.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1995799390.000002 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1532250165.999983,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1532029198.0000036 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "5886b6c4a02d3a33e15a94059db51c418f8c7623",
          "message": "perf: grow adjacency_list_ lazily in add_edge, not eagerly in add_vertex (#446)\n\n#442 made add_vertex()/add_vertex_with_id() grow adjacency_list_ in\nlockstep with vertices_ on every new vertex. Workloads that add many\nvertices but few or no edges (e.g. bm_add_primitive_numeric_vertex,\nwhich adds zero edges) paid for that growth without ever using it,\nregressing add_vertex by 2.7-4.2x versus #438 and, for\nbm_add_user_defined_vertex at scale, ending up slower than the\noriginal unordered_map baseline (#432-era) it replaced.\n\nadjacency_list_ now grows lazily in add_edge(), the first place a\ngiven vertex actually needs a neighbor slot. remove_vertex() gets a\nbounds guard since adjacency_list_ can now be smaller than vertices_\nfor vertices that never had an edge; get_neighbors() already handled\n\"no slot yet\" correctly via its existing bounds check, so it needed no\nchange.\n\nBenchmarked (Release) at three points - before #438, after #438, after\n#442 (main) - against this fix, using perf/graaflib/add_vertex_benchmark.cpp:\n\n                                          post-438   post-442(main)   fixed\nbm_add_primitive_numeric_vertex/10M      205.1ms    742.1ms          167.2ms\nbm_add_primitive_numeric_vertex/2M        46.0ms    122.9ms           34.4ms\nbm_add_user_defined_vertex/10M           868.5ms   1578.5ms          938.4ms\n\nThe fix matches or slightly beats #438 across the board. Re-verified\nadd_edge_benchmark and the BFS benchmarks (what #442 was actually\nmeant to speed up) are unaffected by moving the resize call.\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-19T16:58:17+02:00",
          "tree_id": "a886dce50630bca2528f65a021c823e33b9c3a86",
          "url": "https://github.com/bobluppes/graaf/commit/5886b6c4a02d3a33e15a94059db51c418f8c7623"
        },
        "date": 1789830135831,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 78530.50306751429,
            "unit": "ns/iter",
            "extra": "iterations: 8965\ncpu: 78525.44450641367 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 402339.25072048337,
            "unit": "ns/iter",
            "extra": "iterations: 1735\ncpu: 402354.15907781007 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1136713.7078852642,
            "unit": "ns/iter",
            "extra": "iterations: 558\ncpu: 1136592.0949820827 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 102991.94603317225,
            "unit": "ns/iter",
            "extra": "iterations: 6819\ncpu: 103002.06188590579 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 563545.4457831488,
            "unit": "ns/iter",
            "extra": "iterations: 1245\ncpu: 563628.1999999962 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 1603550.1281405424,
            "unit": "ns/iter",
            "extra": "iterations: 398\ncpu: 1603350.3090452333 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 5216.906908013511,
            "unit": "ns/iter",
            "extra": "iterations: 135683\ncpu: 5216.1030490186695 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 20596.890718648294,
            "unit": "ns/iter",
            "extra": "iterations: 35038\ncpu: 20593.95947257264 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 155382.11657165314,
            "unit": "ns/iter",
            "extra": "iterations: 5087\ncpu: 155352.2439551797 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 1272033.5369127556,
            "unit": "ns/iter",
            "extra": "iterations: 596\ncpu: 1271687.208053691 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 9023894.393442472,
            "unit": "ns/iter",
            "extra": "iterations: 61\ncpu: 9022656.147540972 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 47458118.24999979,
            "unit": "ns/iter",
            "extra": "iterations: 16\ncpu: 47452427.06249997 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 34494.10803149544,
            "unit": "ns/iter",
            "extra": "iterations: 15875\ncpu: 34462.54607874009 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 176583.79454320064,
            "unit": "ns/iter",
            "extra": "iterations: 4838\ncpu: 176322.9508061183 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 1399763.5149999964,
            "unit": "ns/iter",
            "extra": "iterations: 400\ncpu: 1396732.9475000012 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 11562699.875000052,
            "unit": "ns/iter",
            "extra": "iterations: 72\ncpu: 11544598.472222222 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 75491771.12499984,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 75396335.87499984 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 391503837.99999845,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 391133038.4999996 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1206430318.0000024,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1206307272 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 670728847.999996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 670622242.0000004 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 731975767.0000087,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 731904189.9999945 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 542802581.0000037,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 542786497.0000015 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09328172511342386,
            "unit": "ms/iter",
            "extra": "iterations: 7494\ncpu: 0.0932710886042163 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.099920195266295,
            "unit": "ms/iter",
            "extra": "iterations: 338\ncpu: 2.0997196094674684 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 395.1220195000005,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 395.06179600000024 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 2929.585297000003,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2929.259243000004 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.22116611473880812,
            "unit": "ms/iter",
            "extra": "iterations: 3216\ncpu: 0.22114396548507353 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 2.913411891666643,
            "unit": "ms/iter",
            "extra": "iterations: 240\ncpu: 2.913301895833313 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 449.95789100000394,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 449.90117849999933 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 3100.101596000002,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3099.8074270000016 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.7942357745208695,
            "unit": "ms/iter",
            "extra": "iterations: 887\ncpu: 0.7941407508455475 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 7.595749968421136,
            "unit": "ms/iter",
            "extra": "iterations: 95\ncpu: 7.595565210526296 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 185.80283940000015,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 185.77385960000043 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 2126.697194000002,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2126.446223000002 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.11540189452752316,
            "unit": "ms/iter",
            "extra": "iterations: 6286\ncpu: 0.11539332437161966 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.1475815014245043,
            "unit": "ms/iter",
            "extra": "iterations: 351\ncpu: 2.1473289886039897 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 517.8968200000043,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 517.8394979999972 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 3486.365019999994,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3486.0215440000034 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.31633923398455,
            "unit": "ms/iter",
            "extra": "iterations: 2201\ncpu: 0.3163166328941373 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.5961173897435517,
            "unit": "ms/iter",
            "extra": "iterations: 195\ncpu: 3.595950241025656 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 561.8164099999916,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 561.7597469999964 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 3492.996181999999,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3492.8287209999953 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.3462835000000326,
            "unit": "ms/iter",
            "extra": "iterations: 516\ncpu: 1.3461999631782935 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 10.603877968749842,
            "unit": "ms/iter",
            "extra": "iterations: 64\ncpu: 10.603516187499995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 576.7628589999845,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 576.7103449999951 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 3373.311521000005,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3373.092278999991 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 4.6709005853658505,
            "unit": "ms/iter",
            "extra": "iterations: 123\ncpu: 4.669983569105692 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 250.9667777500013,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 250.95399849999822 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 771.3765489999957,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 771.2526650000058 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.26403650812854446,
            "unit": "ms/iter",
            "extra": "iterations: 2645\ncpu: 0.26401831568998163 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.247572600938883,
            "unit": "ms/iter",
            "extra": "iterations: 213\ncpu: 3.247369169014131 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 494.079811000006,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 494.0505444999985 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 3041.6799580000034,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3041.5148219999965 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.3233755641026006,
            "unit": "ms/iter",
            "extra": "iterations: 546\ncpu: 1.3232169249084207 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 16.665891181817987,
            "unit": "ms/iter",
            "extra": "iterations: 44\ncpu: 16.664483704545642 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 393.64621533332905,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 393.6159909999996 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 3735.237256000005,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3735.0214660000065 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.3869519944536926,
            "unit": "ms/iter",
            "extra": "iterations: 1803\ncpu: 0.3869423926788744 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 3.92768673888892,
            "unit": "ms/iter",
            "extra": "iterations: 180\ncpu: 3.9274330666666892 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 526.362038000002,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 526.3421780000073 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 3481.4663690000034,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3481.2442900000065 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.6212899467592399,
            "unit": "ms/iter",
            "extra": "iterations: 432\ncpu: 1.6212462893518718 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 18.937959194444275,
            "unit": "ms/iter",
            "extra": "iterations: 36\ncpu: 18.93594677777778 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 285.8072544999999,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 285.79431749999884 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 2794.5963429999947,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2794.405698999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.4576558841262378,
            "unit": "ms/iter",
            "extra": "iterations: 2123\ncpu: 0.45761076401318873 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 8.612670618556574,
            "unit": "ms/iter",
            "extra": "iterations: 97\ncpu: 8.611969185567045 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 204.92480200000074,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 204.91313150000323 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 1965.2554890000147,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1965.0981009999953 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.6144358074608799,
            "unit": "ms/iter",
            "extra": "iterations: 831\ncpu: 0.6143741877256274 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 8.907765560606066,
            "unit": "ms/iter",
            "extra": "iterations: 132\ncpu: 8.90705765151515 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 579.2048710000017,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 579.1460100000023 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 2826.230205999991,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2826.0093570000035 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3030465413.000002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3030137594.9999995 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3835468936.0000124,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3835106596.000003 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4877498587.000019,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4876499701 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5854021555.000003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5851650587.000023 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 712913331.9999994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 712886298.0000008 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 459323738.50000376,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 459287040.5000014 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 2809944814.000005,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2809626265.00002 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2690934145,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2690632329.9999995 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 203246442.99999762,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 202480623.5000014 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 276334751.666667,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 275472644.6666685 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1345628320.000003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1345495240.9999804 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1090367196.9999778,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1090276138.9999967 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "802ff1e405af2afc6478d5442ed299fecc835b8d",
          "message": "perf(ci): pin bron_kerbosch benchmark RNG seed for reproducibility (#447)\n\n* perf(ci): pin bron_kerbosch benchmark RNG seed for reproducibility\n\nbron_kerbosh_random_cliques and bron_kerbosh_connected_random_cliques\nseeded their std::mt19937 from std::random_device, i.e. real OS\nentropy - a different seed, and therefore a different randomly\ngenerated input graph, on every process run. bron_kerbosch's runtime\nis highly sensitive to the exact clique-size distribution of its\ninput, so this made the two benchmarks' timing vary run to run for\nreasons entirely unrelated to any code change, indistinguishable from\nan actual regression when tracked over time in CI.\n\nSwitched to a fixed seed. Verified by running the affected benchmarks\ntwice: timing variance between runs is now within normal system noise\ninstead of the swings a different random graph would produce.\n\nThe other two bron_kerbosch benchmark variants (bron_kerbosh_cliques,\nbron_kerbosh_connected_cliques) already use a fixed clique size from\nbenchmark parameters and were already deterministic - unaffected.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* fix: shorten RNG seed comment\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n---------\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-19T17:00:32+02:00",
          "tree_id": "519aa5e7e859db41d08068e3493a581615e93bca",
          "url": "https://github.com/bobluppes/graaf/commit/802ff1e405af2afc6478d5442ed299fecc835b8d"
        },
        "date": 1789830277489,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 80330.73159279005,
            "unit": "ns/iter",
            "extra": "iterations: 9005\ncpu: 80325.15846751846 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 403392.27198850206,
            "unit": "ns/iter",
            "extra": "iterations: 1728\ncpu: 403382.0555555537 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1139890.3357271992,
            "unit": "ns/iter",
            "extra": "iterations: 557\ncpu: 1139654.2262118459 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 102690.1411615497,
            "unit": "ns/iter",
            "extra": "iterations: 6829\ncpu: 102699.64723971114 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 583860.9135657928,
            "unit": "ns/iter",
            "extra": "iterations: 1238\ncpu: 583932.4676898274 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 1725478.424661153,
            "unit": "ns/iter",
            "extra": "iterations: 438\ncpu: 1725511.3493150887 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 5168.847461157166,
            "unit": "ns/iter",
            "extra": "iterations: 134451\ncpu: 5167.714609783493 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 21070.845235412933,
            "unit": "ns/iter",
            "extra": "iterations: 35512\ncpu: 21069.728964856953 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 157282.51273886545,
            "unit": "ns/iter",
            "extra": "iterations: 5024\ncpu: 157251.46297770727 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 1259436.303986977,
            "unit": "ns/iter",
            "extra": "iterations: 602\ncpu: 1259274.991694352 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 10230054.35211058,
            "unit": "ns/iter",
            "extra": "iterations: 71\ncpu: 10229053.633802835 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 48120249.99999665,
            "unit": "ns/iter",
            "extra": "iterations: 16\ncpu: 48111023.31250006 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 34303.58925313529,
            "unit": "ns/iter",
            "extra": "iterations: 15893\ncpu: 34297.46290819862 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 174576.24490216273,
            "unit": "ns/iter",
            "extra": "iterations: 4855\ncpu: 174547.8160659115 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 1362561.4275002817,
            "unit": "ns/iter",
            "extra": "iterations: 400\ncpu: 1362307.2949999983 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 11354436.633802166,
            "unit": "ns/iter",
            "extra": "iterations: 71\ncpu: 11353773.394366188 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 74854018.24999371,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 74849719.875 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 386205419.5000155,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 386092391.50000006 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1310791893.9999764,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1310660300.9999986 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 731014101.0000279,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 730945321.9999967 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 811572511.9998842,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 811469623.0000007 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 591797662.00009,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 591755517.9999994 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09402453595913442,
            "unit": "ms/iter",
            "extra": "iterations: 7439\ncpu: 0.09401459739212231 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.1254206964287157,
            "unit": "ms/iter",
            "extra": "iterations: 336\ncpu: 2.125364235119035 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 373.7901160000092,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 373.67009500000137 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 3095.266436999964,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3095.0023569999985 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.21898027662816186,
            "unit": "ms/iter",
            "extra": "iterations: 3286\ncpu: 0.2189574230066944 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 3.030909163090136,
            "unit": "ms/iter",
            "extra": "iterations: 233\ncpu: 3.0306753390557732 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 445.0399570000627,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 445.00724599999944 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 3220.211473000063,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3219.695700999999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.7764151550117804,
            "unit": "ms/iter",
            "extra": "iterations: 858\ncpu: 0.7763781689976741 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 6.776473588888621,
            "unit": "ms/iter",
            "extra": "iterations: 90\ncpu: 6.776197733333333 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 165.4526049999845,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 165.43960599999963 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 2089.797661000148,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2089.643144 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.11767448098824715,
            "unit": "ms/iter",
            "extra": "iterations: 5707\ncpu: 0.11766593937270083 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.031752297450444,
            "unit": "ms/iter",
            "extra": "iterations: 353\ncpu: 2.0313407478753494 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 188.11287800002674,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 188.09820825000045 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 2222.121704000074,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2221.8963309999963 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.30695191551191686,
            "unit": "ms/iter",
            "extra": "iterations: 2237\ncpu: 0.3069033996423764 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.4049516616161064,
            "unit": "ms/iter",
            "extra": "iterations: 198\ncpu: 3.4047199393939285 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 545.2796049999051,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 545.2044230000013 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 3531.4888609998434,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3531.268620999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.3598500468749997,
            "unit": "ms/iter",
            "extra": "iterations: 512\ncpu: 1.3595692441406293 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 12.05840544262397,
            "unit": "ms/iter",
            "extra": "iterations: 61\ncpu: 12.05730272131153 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 626.8186559998412,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 626.7413349999913 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 3711.246613999947,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3710.9086669999983 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 4.963342355372972,
            "unit": "ms/iter",
            "extra": "iterations: 121\ncpu: 4.962533595041363 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 256.73343049999175,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 256.7153395000013 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 792.9985480000141,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 792.918990000004 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.2646789095022645,
            "unit": "ms/iter",
            "extra": "iterations: 2652\ncpu: 0.26464218212669705 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.2260451990745658,
            "unit": "ms/iter",
            "extra": "iterations: 216\ncpu: 3.2258182407407605 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 522.3202890000493,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 522.2454744999965 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 3327.4091359999147,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3327.1356900000055 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.3446709624766275,
            "unit": "ms/iter",
            "extra": "iterations: 533\ncpu: 1.3446383302063916 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 16.16385062856612,
            "unit": "ms/iter",
            "extra": "iterations: 35\ncpu: 16.160823828571683 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 591.1419589999696,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 591.1109670000059 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 3509.6477699999014,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3509.3210819999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.3857041692391894,
            "unit": "ms/iter",
            "extra": "iterations: 1814\ncpu: 0.3856789355016555 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 3.732210300000184,
            "unit": "ms/iter",
            "extra": "iterations: 180\ncpu: 3.7317122611110816 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 238.64023200002293,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 238.61816049999973 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 2388.447840000026,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2388.276976 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.2771525904762322,
            "unit": "ms/iter",
            "extra": "iterations: 525\ncpu: 1.2771110876190592 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 20.08321064864823,
            "unit": "ms/iter",
            "extra": "iterations: 37\ncpu: 20.081758972973045 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 489.96282099994914,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 489.9220984999957 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 3136.4297439999973,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3136.0166700000036 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.45069739533200254,
            "unit": "ms/iter",
            "extra": "iterations: 1371\ncpu: 0.450665545587169 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 6.069437765217631,
            "unit": "ms/iter",
            "extra": "iterations: 115\ncpu: 6.068663486956523 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 548.6447460000363,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 548.6331549999903 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 3456.8722849999176,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3456.545348000006 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.6959189340000194,
            "unit": "ms/iter",
            "extra": "iterations: 1000\ncpu: 0.695893390000009 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 8.947308048779478,
            "unit": "ms/iter",
            "extra": "iterations: 82\ncpu: 8.946546902439072 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 552.171941999859,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 552.0472380000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 3658.0503549998866,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3657.7256670000083 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3317501337.000067,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3317115227.0000024 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3874051100.0000877,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3873106641.000021 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 5419464262.000019,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5418944831.999994 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 6496755513.999915,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6495719659.999991 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 829399560.9999456,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 829324658.9999796 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 564568683.0000614,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 564544018.0000207 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 3080206651.0000257,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3079993986.0000052 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2790262158.9998946,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2789994979.999989 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 229805570.6667128,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 229794438.6666681 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 318116560.666643,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 318085966.3333327 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1718091239.0001595,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1714799544.000016 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1288373825.0000079,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1288251005.0000064 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "49699333+dependabot[bot]@users.noreply.github.com",
            "name": "dependabot[bot]",
            "username": "dependabot[bot]"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "7316ef892c929ce3132b9918224811c62d5d6952",
          "message": "build(deps): bump dorny/paths-filter from 3 to 4 (#441)\n\nBumps [dorny/paths-filter](https://github.com/dorny/paths-filter) from 3 to 4.\n- [Release notes](https://github.com/dorny/paths-filter/releases)\n- [Changelog](https://github.com/dorny/paths-filter/blob/master/CHANGELOG.md)\n- [Commits](https://github.com/dorny/paths-filter/compare/v3...v4)\n\n---\nupdated-dependencies:\n- dependency-name: dorny/paths-filter\n  dependency-version: '4'\n  dependency-type: direct:production\n  update-type: version-update:semver-major\n...\n\nSigned-off-by: dependabot[bot] <support@github.com>\nCo-authored-by: dependabot[bot] <49699333+dependabot[bot]@users.noreply.github.com>",
          "timestamp": "2026-09-19T17:01:31+02:00",
          "tree_id": "97a5679ad62f84e48b34ddeb18eab20423a8e83c",
          "url": "https://github.com/bobluppes/graaf/commit/7316ef892c929ce3132b9918224811c62d5d6952"
        },
        "date": 1789830297727,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 62618.93362956212,
            "unit": "ns/iter",
            "extra": "iterations: 11029\ncpu: 62626.7610844136 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 326799.5431279926,
            "unit": "ns/iter",
            "extra": "iterations: 2110\ncpu: 326767.0985782008 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 832695.062162297,
            "unit": "ns/iter",
            "extra": "iterations: 740\ncpu: 832774.6351351277 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 83646.19030397257,
            "unit": "ns/iter",
            "extra": "iterations: 8292\ncpu: 83654.76386878554 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 435831.0113707401,
            "unit": "ns/iter",
            "extra": "iterations: 1583\ncpu: 435806.1629816788 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 1110311.1586536649,
            "unit": "ns/iter",
            "extra": "iterations: 624\ncpu: 1110411.7724358807 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 6196.958480139242,
            "unit": "ns/iter",
            "extra": "iterations: 136802\ncpu: 6196.968114501246 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 25023.20543010249,
            "unit": "ns/iter",
            "extra": "iterations: 34143\ncpu: 25025.35319099084 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 173347.87857394948,
            "unit": "ns/iter",
            "extra": "iterations: 5666\ncpu: 173308.60642428527 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 1455228.7908805087,
            "unit": "ns/iter",
            "extra": "iterations: 636\ncpu: 1454744.756289308 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 12384407.704225298,
            "unit": "ns/iter",
            "extra": "iterations: 71\ncpu: 12384946.746478861 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 61620000.142857485,
            "unit": "ns/iter",
            "extra": "iterations: 14\ncpu: 61606909.07142856 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 38363.42889340831,
            "unit": "ns/iter",
            "extra": "iterations: 18191\ncpu: 38362.8389863119 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 158772.77195656532,
            "unit": "ns/iter",
            "extra": "iterations: 5249\ncpu: 158781.91274528494 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 1240009.9721485374,
            "unit": "ns/iter",
            "extra": "iterations: 754\ncpu: 1240010.7519893893 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 9708529.689189203,
            "unit": "ns/iter",
            "extra": "iterations: 74\ncpu: 9706112.013513496 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 79651583.4444449,
            "unit": "ns/iter",
            "extra": "iterations: 9\ncpu: 79626592.77777778 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 383300137.5000009,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 383243063.5000001 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 787880028.0000178,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 787841998.0000011 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 508098092.00001156,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 508101066.00000185 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 528578330.9999914,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 528584177.0000026 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 355168209.5000075,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 355164894.9999979 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.0713176306285963,
            "unit": "ms/iter",
            "extra": "iterations: 8861\ncpu: 0.0713216254373096 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 1.5812730022573462,
            "unit": "ms/iter",
            "extra": "iterations: 443\ncpu: 1.5812951038374738 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 194.2081040000005,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 194.2101575999999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 1410.4581080000003,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1410.4779450000037 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.18691698115239994,
            "unit": "ms/iter",
            "extra": "iterations: 3714\ncpu: 0.18692649273021048 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 2.589559822641424,
            "unit": "ms/iter",
            "extra": "iterations: 265\ncpu: 2.5896068943396244 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 334.8764084999942,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 334.8940979999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 2017.060215000015,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2017.083233000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.6197856130198875,
            "unit": "ms/iter",
            "extra": "iterations: 1106\ncpu: 0.6197881699819189 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 6.924960277227582,
            "unit": "ms/iter",
            "extra": "iterations: 101\ncpu: 6.925044920792082 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 334.8703519999958,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 334.87005950000184 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 2102.7000660000112,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2102.740673999996 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.10765644098411817,
            "unit": "ms/iter",
            "extra": "iterations: 6422\ncpu: 0.10765760121457514 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 1.9610889235293631,
            "unit": "ms/iter",
            "extra": "iterations: 340\ncpu: 1.9611122823529445 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 232.92651366666442,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 232.93386033333263 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 1261.6991509999878,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1261.744297 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.2644573725788114,
            "unit": "ms/iter",
            "extra": "iterations: 2633\ncpu: 0.2644682419293588 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 2.9715553292181003,
            "unit": "ms/iter",
            "extra": "iterations: 243\ncpu: 2.9715839547325036 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 277.78645675000035,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 277.79657625000095 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 1919.0420870000082,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1919.1022480000015 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 0.9645223802228716,
            "unit": "ms/iter",
            "extra": "iterations: 718\ncpu: 0.9645321086350965 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 8.045064628204885,
            "unit": "ms/iter",
            "extra": "iterations: 78\ncpu: 8.045113858974455 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 249.3527613333318,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 249.35362166666644 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 1289.1256600000247,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1289.1742030000019 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 6.673757692857001,
            "unit": "ms/iter",
            "extra": "iterations: 140\ncpu: 6.673725621428567 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 196.50892933333353,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 196.5130216666656 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 870.4315059999885,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 870.4371179999981 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.20529262067955312,
            "unit": "ms/iter",
            "extra": "iterations: 3414\ncpu: 0.2052960251903926 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 2.7065041960000826,
            "unit": "ms/iter",
            "extra": "iterations: 250\ncpu: 2.7062530799999536 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 146.65325940000002,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 146.65094039999929 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 844.2319440000006,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 844.2389880000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 0.7736078176914849,
            "unit": "ms/iter",
            "extra": "iterations: 927\ncpu: 0.7736505728155297 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 14.013958790322308,
            "unit": "ms/iter",
            "extra": "iterations: 62\ncpu: 14.013852564516121 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 385.9364765000066,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 385.9497609999991 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 1160.4492090000065,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1160.4628140000132 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.3040079268292766,
            "unit": "ms/iter",
            "extra": "iterations: 2296\ncpu: 0.3040178466898951 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 3.4164292920792994,
            "unit": "ms/iter",
            "extra": "iterations: 202\ncpu: 3.4165458019802037 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 297.3962084999968,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 297.3996174999982 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 1117.3842739999884,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1117.42151899999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 0.9799794584415843,
            "unit": "ms/iter",
            "extra": "iterations: 770\ncpu: 0.9787202909090827 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 16.82743169047623,
            "unit": "ms/iter",
            "extra": "iterations: 42\ncpu: 16.82783202380936 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 368.8034729999998,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 368.80319549999996 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 1647.5690950000228,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1647.5831289999974 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.6374652537643873,
            "unit": "ms/iter",
            "extra": "iterations: 2258\ncpu: 0.6374523906111648 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 5.630164336283005,
            "unit": "ms/iter",
            "extra": "iterations: 113\ncpu: 5.630165938053206 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 242.2630373333353,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 242.27249866666511 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 2021.4244560000054,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2021.4430010000087 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.38570575771370397,
            "unit": "ms/iter",
            "extra": "iterations: 1977\ncpu: 0.3853089448659594 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 8.396708941747532,
            "unit": "ms/iter",
            "extra": "iterations: 103\ncpu: 8.39658251456316 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 224.94501866666874,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 224.94017199999897 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 1409.5839860000012,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1409.5878830000004 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 2570269536.000012,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2567084655.0000024 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3058237993.0000057,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3058298446.9999986 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4053364157.999994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4050506295.9999948 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 4770558007.999994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4770627992.99999 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 501999174.0000051,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 502006186.0000027 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 389320394.99999857,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 389341260.99999845 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 2593859301.9999986,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2593788289.0000024 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2547516317.000003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2547528042.0000105 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 136944049.50000206,
            "unit": "ns/iter",
            "extra": "iterations: 6\ncpu: 136946884.83333078 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 145794643.19999716,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 145791443.80000457 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1104709318.0000048,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1104706542.0000024 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 887620399.0000136,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 887615034.9999819 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "49699333+dependabot[bot]@users.noreply.github.com",
            "name": "dependabot[bot]",
            "username": "dependabot[bot]"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "33731fd356418ed1a9b0f6ad6df7075f8a5fd2d9",
          "message": "build(deps): bump actions/cache from 4 to 6 (#440)\n\nBumps [actions/cache](https://github.com/actions/cache) from 4 to 6.\n- [Release notes](https://github.com/actions/cache/releases)\n- [Changelog](https://github.com/actions/cache/blob/main/RELEASES.md)\n- [Commits](https://github.com/actions/cache/compare/v4...v6)\n\n---\nupdated-dependencies:\n- dependency-name: actions/cache\n  dependency-version: '6'\n  dependency-type: direct:production\n  update-type: version-update:semver-major\n...\n\nSigned-off-by: dependabot[bot] <support@github.com>\nCo-authored-by: dependabot[bot] <49699333+dependabot[bot]@users.noreply.github.com>",
          "timestamp": "2026-09-19T17:03:08+02:00",
          "tree_id": "6c359b2ac0c959aebe8f2a4e4f50d1b5b5668770",
          "url": "https://github.com/bobluppes/graaf/commit/33731fd356418ed1a9b0f6ad6df7075f8a5fd2d9"
        },
        "date": 1789830437368,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 79460.81865382653,
            "unit": "ns/iter",
            "extra": "iterations: 8856\ncpu: 79461.60569105671 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 405776.9700531439,
            "unit": "ns/iter",
            "extra": "iterations: 1703\ncpu: 405993.2113916678 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1154833.622467735,
            "unit": "ns/iter",
            "extra": "iterations: 543\ncpu: 1154889.8802946557 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 105138.32448284885,
            "unit": "ns/iter",
            "extra": "iterations: 6817\ncpu: 105134.7632389621 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 571806.1404219758,
            "unit": "ns/iter",
            "extra": "iterations: 1232\ncpu: 571866.1030844315 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 1791894.074942101,
            "unit": "ns/iter",
            "extra": "iterations: 427\ncpu: 1791811.8594847643 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 4307.992917572856,
            "unit": "ns/iter",
            "extra": "iterations: 129193\ncpu: 4307.139117444443 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 20696.377029622545,
            "unit": "ns/iter",
            "extra": "iterations: 34366\ncpu: 20692.214601641175 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 158934.26102503372,
            "unit": "ns/iter",
            "extra": "iterations: 5034\ncpu: 158921.56475963452 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 1296011.793277355,
            "unit": "ns/iter",
            "extra": "iterations: 595\ncpu: 1295487.0621848747 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 10585101.794117607,
            "unit": "ns/iter",
            "extra": "iterations: 68\ncpu: 10583090.764705878 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 50086485.933331914,
            "unit": "ns/iter",
            "extra": "iterations: 15\ncpu: 50077081.26666668 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 34404.37999747734,
            "unit": "ns/iter",
            "extra": "iterations: 15858\ncpu: 34398.651153991676 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 175470.64128421526,
            "unit": "ns/iter",
            "extra": "iterations: 4859\ncpu: 175447.77999588396 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 1367819.397500014,
            "unit": "ns/iter",
            "extra": "iterations: 400\ncpu: 1367636.5325000007 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 10981388.499999411,
            "unit": "ns/iter",
            "extra": "iterations: 50\ncpu: 10978787.200000007 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 73897540.3750004,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 73869541.1250001 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 390243672.9999863,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 390207409.0000003 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1282637686.9999762,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1282521663.9999971 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 751520705.0000186,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 751453138.9999988 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 795466451.999971,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 795332174.0000021 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 596329002.9999939,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 596281228.0000023 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09502678074793589,
            "unit": "ms/iter",
            "extra": "iterations: 7407\ncpu: 0.0950134911570139 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.1410460738460504,
            "unit": "ms/iter",
            "extra": "iterations: 325\ncpu: 2.1408873199999987 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 418.5569340000086,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 418.4166729999994 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 3070.987104999972,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3070.208835999999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.22020670841178572,
            "unit": "ms/iter",
            "extra": "iterations: 3186\ncpu: 0.22017644569993639 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 2.944857567226915,
            "unit": "ms/iter",
            "extra": "iterations: 238\ncpu: 2.944601693277301 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 466.9583995000153,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 466.91255049999825 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 3108.852490000004,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3108.451758000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.8182754165680243,
            "unit": "ms/iter",
            "extra": "iterations: 845\ncpu: 0.8182401218934909 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 6.983077288888732,
            "unit": "ms/iter",
            "extra": "iterations: 90\ncpu: 6.982228211111084 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 561.2932374999957,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 560.5784609999987 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 3336.274711000044,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3335.808281999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.11512400900738853,
            "unit": "ms/iter",
            "extra": "iterations: 5551\ncpu: 0.11512184759502819 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.019015684057992,
            "unit": "ms/iter",
            "extra": "iterations: 345\ncpu: 2.0186859130434924 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 211.4575973333217,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 211.44873033333292 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 2651.965966999967,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2651.7111610000015 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.3161137797376745,
            "unit": "ms/iter",
            "extra": "iterations: 2211\ncpu: 0.31592245861601226 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.45388203608263,
            "unit": "ms/iter",
            "extra": "iterations: 194\ncpu: 3.45355085051543 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 576.6991899999994,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 576.6411280000057 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 3483.3777609999856,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3483.043035000009 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.3482201274509371,
            "unit": "ms/iter",
            "extra": "iterations: 510\ncpu: 1.3480970647058692 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 11.436945393443164,
            "unit": "ms/iter",
            "extra": "iterations: 61\ncpu: 11.435163737704986 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 625.5547509999815,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 625.4706269999986 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 3647.013782999977,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3643.812462 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 5.204525857142922,
            "unit": "ms/iter",
            "extra": "iterations: 119\ncpu: 5.204414613445374 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 262.6246352500061,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 262.60178874999696 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 765.9326479999891,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 765.865821999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.2643698383233537,
            "unit": "ms/iter",
            "extra": "iterations: 2672\ncpu: 0.2643299902694592 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.2272989626169655,
            "unit": "ms/iter",
            "extra": "iterations: 214\ncpu: 3.2270106121495408 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 539.8736580000332,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 539.8295869999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 3365.9367110000176,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3362.432681000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.2554084339963725,
            "unit": "ms/iter",
            "extra": "iterations: 553\ncpu: 1.2553651844484648 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 18.200623771429036,
            "unit": "ms/iter",
            "extra": "iterations: 35\ncpu: 18.20021639999985 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 334.6475109999858,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 334.6125905000008 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 3630.401859000017,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3629.983441999997 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.38316105753425567,
            "unit": "ms/iter",
            "extra": "iterations: 1825\ncpu: 0.38316154958904025 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 3.9164822802198223,
            "unit": "ms/iter",
            "extra": "iterations: 182\ncpu: 3.916256456043897 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 530.2047599999469,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 526.9220249999904 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 3332.9466769999954,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3332.658950999999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.5887608898876524,
            "unit": "ms/iter",
            "extra": "iterations: 445\ncpu: 1.5887379438202303 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 23.408298727273095,
            "unit": "ms/iter",
            "extra": "iterations: 33\ncpu: 23.405267818182036 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 638.2464640000194,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 638.1944780000026 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 3288.293846999977,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3287.986115999999 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.8204562395247103,
            "unit": "ms/iter",
            "extra": "iterations: 1599\ncpu: 0.8185620343965015 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 5.94802465714327,
            "unit": "ms/iter",
            "extra": "iterations: 105\ncpu: 5.947431628571497 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 505.8100439999862,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 505.7966029999932 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 2641.7149119999976,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2641.455031999996 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.5358767220076939,
            "unit": "ms/iter",
            "extra": "iterations: 1554\ncpu: 0.5358525849420875 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 8.605814687500176,
            "unit": "ms/iter",
            "extra": "iterations: 96\ncpu: 8.604771364583375 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 271.9051585000045,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 271.90478349999836 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 2325.4287290000093,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2324.665048 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3299742173.0000267,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3299354346.9999905 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 4423144159.999992,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4422744219.000009 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 5097356098.000034,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5094098212.999995 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 6186088630.000029,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6185533136.000004 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 796401715.0000018,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 793222401.9999979 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 482706681.5000194,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 482650301.9999961 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 2925791296,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2925393087.999993 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2846927451.9999886,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2846617713.0000005 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 228485227.00000253,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 228428650.33333245 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 275926407.6666644,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 275908621.6666636 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1468370274.9999838,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1468195202.000004 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1115377352.9999852,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1115232182.9999893 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "49699333+dependabot[bot]@users.noreply.github.com",
            "name": "dependabot[bot]",
            "username": "dependabot[bot]"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "57234b475fd76e67edc9df9af5b5e4ab0cc1e69f",
          "message": "build(deps): bump benchmark-action/github-action-benchmark (#439)\n\nBumps [benchmark-action/github-action-benchmark](https://github.com/benchmark-action/github-action-benchmark) from 1.22.1 to 1.22.2.\n- [Release notes](https://github.com/benchmark-action/github-action-benchmark/releases)\n- [Changelog](https://github.com/benchmark-action/github-action-benchmark/blob/master/CHANGELOG.md)\n- [Commits](https://github.com/benchmark-action/github-action-benchmark/compare/v1.22.1...v1.22.2)\n\n---\nupdated-dependencies:\n- dependency-name: benchmark-action/github-action-benchmark\n  dependency-version: 1.22.2\n  dependency-type: direct:production\n  update-type: version-update:semver-patch\n...\n\nSigned-off-by: dependabot[bot] <support@github.com>\nCo-authored-by: dependabot[bot] <49699333+dependabot[bot]@users.noreply.github.com>",
          "timestamp": "2026-09-19T17:03:46+02:00",
          "tree_id": "9f273bae262c8160ef13a9f74035a9cbae7d5991",
          "url": "https://github.com/bobluppes/graaf/commit/57234b475fd76e67edc9df9af5b5e4ab0cc1e69f"
        },
        "date": 1789830463260,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 78389.35841959536,
            "unit": "ns/iter",
            "extra": "iterations: 9062\ncpu: 78406.0172147431 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 399267.28457559296,
            "unit": "ns/iter",
            "extra": "iterations: 1757\ncpu: 399321.41889585037 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1244316.5742381823,
            "unit": "ns/iter",
            "extra": "iterations: 559\ncpu: 1244393.481216463 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 101258.11991928336,
            "unit": "ns/iter",
            "extra": "iterations: 6963\ncpu: 101265.28579634994 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 556728.9369517767,
            "unit": "ns/iter",
            "extra": "iterations: 1253\ncpu: 556859.4836392864 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 1735991.6045989096,
            "unit": "ns/iter",
            "extra": "iterations: 435\ncpu: 1736086.7908045838 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 4980.743629093301,
            "unit": "ns/iter",
            "extra": "iterations: 138795\ncpu: 4979.8686768255375 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 20174.094057063514,
            "unit": "ns/iter",
            "extra": "iterations: 35925\ncpu: 20171.835017397334 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 153945.47506356714,
            "unit": "ns/iter",
            "extra": "iterations: 5113\ncpu: 153872.16937218865 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 1262890.612211237,
            "unit": "ns/iter",
            "extra": "iterations: 606\ncpu: 1262790.6650165021 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 10184695.625000019,
            "unit": "ns/iter",
            "extra": "iterations: 72\ncpu: 10182128.027777774 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 47751246.12499937,
            "unit": "ns/iter",
            "extra": "iterations: 16\ncpu: 47740775.18749997 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 34204.84457838732,
            "unit": "ns/iter",
            "extra": "iterations: 16259\ncpu: 34199.87754474446 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 168445.9988919666,
            "unit": "ns/iter",
            "extra": "iterations: 5415\ncpu: 168409.4265927978 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 1119766.8967610863,
            "unit": "ns/iter",
            "extra": "iterations: 494\ncpu: 1119439.190283402 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 10708342.300000027,
            "unit": "ns/iter",
            "extra": "iterations: 50\ncpu: 10705791.500000004 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 73160396.75000142,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 73153795.12500009 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 386592777.0000042,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 386553100.5000005 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 1182046740.000004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1181912114.9999993 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 660466646.0000032,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 660360633.9999999 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 677737119.999989,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 677641586 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 515885163.9999966,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 515844106.9999995 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09350055482661708,
            "unit": "ms/iter",
            "extra": "iterations: 7469\ncpu: 0.09348957209800528 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 2.063896533527719,
            "unit": "ms/iter",
            "extra": "iterations: 343\ncpu: 2.063653341107856 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 330.166299499993,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 330.13693550000056 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 2892.008556999997,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2891.5755800000015 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.2202040819466186,
            "unit": "ms/iter",
            "extra": "iterations: 3185\ncpu: 0.22018193689167953 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 2.9148950912862728,
            "unit": "ms/iter",
            "extra": "iterations: 241\ncpu: 2.914571319502096 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 442.5577485000076,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 442.52826700000014 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 3076.7910430000143,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3076.5274509999967 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.7866811512792183,
            "unit": "ms/iter",
            "extra": "iterations: 899\ncpu: 0.7866064249165792 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 6.812544218750105,
            "unit": "ms/iter",
            "extra": "iterations: 96\ncpu: 6.812148687499982 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 545.3452890000108,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 545.293658999995 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 3385.561972000005,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3385.315394000003 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.1148224890753374,
            "unit": "ms/iter",
            "extra": "iterations: 5721\ncpu: 0.11481364621569612 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 1.9941596103152222,
            "unit": "ms/iter",
            "extra": "iterations: 349\ncpu: 1.9938835214899764 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 207.46602375000123,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 207.45118424999907 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 2601.424202000004,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2601.183829 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.316957600181318,
            "unit": "ms/iter",
            "extra": "iterations: 2206\ncpu: 0.31694615684496596 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.408293472361736,
            "unit": "ms/iter",
            "extra": "iterations: 199\ncpu: 3.4078487989949933 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 542.6064760000031,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 542.6014800000019 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 3435.8666319999998,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3435.511453999993 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.334193243294981,
            "unit": "ms/iter",
            "extra": "iterations: 522\ncpu: 1.3340651436781683 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 10.909310812500017,
            "unit": "ms/iter",
            "extra": "iterations: 64\ncpu: 10.908284187500117 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 616.525361000015,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 616.4286839999988 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 3573.694684000003,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3573.391848 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 4.926586507812525,
            "unit": "ms/iter",
            "extra": "iterations: 128\ncpu: 4.926180234374966 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 245.4584040000043,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 245.42459625000035 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 721.4413469999954,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 721.3839220000011 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.2644174047619081,
            "unit": "ms/iter",
            "extra": "iterations: 2646\ncpu: 0.26439157294028676 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.2387377710281653,
            "unit": "ms/iter",
            "extra": "iterations: 214\ncpu: 3.2384145373831896 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 425.6897124999739,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 425.64592800000156 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 3097.4046609999846,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3097.0385200000123 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.2801610628365994,
            "unit": "ms/iter",
            "extra": "iterations: 557\ncpu: 1.2800888025134756 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 15.670329069768139,
            "unit": "ms/iter",
            "extra": "iterations: 43\ncpu: 15.668630023255808 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 609.2787310000176,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 609.2111730000056 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 3218.7064909999776,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3218.343809999993 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.3843905418261448,
            "unit": "ms/iter",
            "extra": "iterations: 1829\ncpu: 0.3843436232914175 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 3.896656176470605,
            "unit": "ms/iter",
            "extra": "iterations: 187\ncpu: 3.8960506096257173 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 267.5803129999963,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 267.57274349999705 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 2187.043143999972,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2186.8302259999978 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.2836228690036975,
            "unit": "ms/iter",
            "extra": "iterations: 542\ncpu: 1.2834269317343294 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 20.27081263888893,
            "unit": "ms/iter",
            "extra": "iterations: 36\ncpu: 20.26991863888878 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 513.5351300000082,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 513.4871544999982 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 2283.5919240000067,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2283.43562900001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.7904122406613663,
            "unit": "ms/iter",
            "extra": "iterations: 1633\ncpu: 0.7903376344151907 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 6.267412660377577,
            "unit": "ms/iter",
            "extra": "iterations: 106\ncpu: 6.266975801886828 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 559.6306790000085,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 559.5640960000026 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 3352.706516000012,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3352.514470999992 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.5137827390745354,
            "unit": "ms/iter",
            "extra": "iterations: 1556\ncpu: 0.5137463553984624 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 8.234109596330216,
            "unit": "ms/iter",
            "extra": "iterations: 109\ncpu: 8.23352834862394 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 573.2337819999884,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 573.2004510000053 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 3337.0382800000016,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3336.7262390000005 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3115293456.0000176,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3114895869.999998 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3793185526.000002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3792446499.999997 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4789504346.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4789004462.000009 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5417248416.999996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5414987455.000016 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 678216683.0000165,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 678162217.9999828 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 440847536.50000155,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 440781163.49999166 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 2697938165.999972,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2697704916.9999814 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2588290386.9999723,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2587967034.000002 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 192000331.74999475,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 191967734.00000212 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 230011425.33333525,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 229994040.33332857 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1288218164.9999893,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1288147780.9999921 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 991091231.9999739,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 991005715.9999894 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "4e929896aace2c0b75f4db78d19732436cc95205",
          "message": "perf: replace BFS's unordered_set with a plain, densely-indexed vector<bool> (#449)\n\n* perf: introduce dense vertex-id bookkeeping and convert BFS as pilot\n\nFirst of a staged series for #443. Adds graaf::algorithm::detail's\nvertex_id_set and vertex_id_map<T>, drop-in replacements for\nstd::unordered_set<vertex_id_t>/std::unordered_map<vertex_id_t, T>\nbacked by a vector<bool>/vector<optional<T>> indexed directly by id\ninstead of hashing. Both grow lazily (matching graph's own storage\nstrategy, see #446) rather than requiring a size hint up front, so no\nnew public API on graph is needed.\n\nbreadth_first_traverse() converts as the pilot: seen_vertices moves\nfrom unordered_set to vertex_id_set. Remaining algorithms (Dijkstra,\nPrim, Kruskal's union-find, coloring, SCC, topological sort, cycle\ndetection, A*, Bellman-Ford, Floyd-Warshall, Bron-Kerbosch) are left\nfor follow-up PRs, each benchmarked individually, per the issue's own\nstaging recommendation.\n\nBenchmarked (Release, perf/graaflib/breadth_first_search_benchmark.cpp,\nreal datasets):\n\n                              before        after      speedup\nweb_google                 3327.9ms     1258.4ms       2.64x\nweb_berkstan                2879.7ms     1462.0ms       1.97x\n\nAlso narrows the gap against the Boost.Graph comparison target\n(perf/boost, GRAAF_BUILD_BOOST_PERF): web_google from 4.95x to 3.27x,\nweb_berkstan from 12.59x to 8.60x.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* simplify: drop the shared vertex-id storage type, use a local vector in BFS\n\nPer review: the vertex_id_set/vertex_id_map<T> wrapper types added\ncomplexity (a new header, a new class hierarchy, a dedicated test\nfile) to solve a problem that didn't need solving generically yet -\nonly one caller (BFS) exists so far, and \"three similar lines\" isn't\npremature-abstraction territory until there's a second and third use\nto actually share.\n\nAlso dropped the idea of adding a graph::vertex_id_upper_bound()-style\nmethod to pre-size these vectors: it would leak graph's internal id\nbookkeeping into its public API for the sole benefit of callers\nwanting a size hint, which graph has no reason to care about.\n\nEvery algorithm entry point takes the graph by const reference, so it\ncan't be mutated mid-algorithm - there's no incremental-growth hazard\nhere the way there was for graph's own add_vertex() (#446). BFS's\nseen_vertices is now a plain std::vector<bool>, grown lazily by a\nsmall local helper scoped to breadth_first_traverse() itself, with no\nnew files and no new public surface anywhere.\n\nRe-benchmarked (Release, real datasets) to confirm this has the same\nperformance as the wrapper-type version, i.e. the abstraction was\nadding zero benefit:\n\n                        unordered_set   vertex_id_set   plain vector<bool>\nweb_google                3327.9ms        1258.4ms          1326.1ms\nweb_berkstan               2879.7ms        1462.0ms          1470.0ms\n\nWithin noise of each other, both ~2-2.6x faster than the original\nunordered_set.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* fix: rename mark_seen to try_mark_seen\n\nThe bool return (whether id was newly marked) wasn't obvious from the\nname. try_ prefix matches the same convention as try_emplace/try_lock:\nan attempted action whose return indicates whether it took effect.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n---------\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-19T21:36:58+02:00",
          "tree_id": "e7d158f5dab122287b1b63c63e46a17043efca66",
          "url": "https://github.com/bobluppes/graaf/commit/4e929896aace2c0b75f4db78d19732436cc95205"
        },
        "date": 1789846852414,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 75704.66060976258,
            "unit": "ns/iter",
            "extra": "iterations: 9411\ncpu: 75703.95175858027 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 384315.4894678511,
            "unit": "ns/iter",
            "extra": "iterations: 1804\ncpu: 384324.60698447726 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1033610.150456091,
            "unit": "ns/iter",
            "extra": "iterations: 658\ncpu: 1033449.250759884 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 97354.77979635373,
            "unit": "ns/iter",
            "extra": "iterations: 7266\ncpu: 97358.70396366675 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 502945.25305546477,
            "unit": "ns/iter",
            "extra": "iterations: 1391\ncpu: 502934.3156003037 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 1361226.1966607799,
            "unit": "ns/iter",
            "extra": "iterations: 539\ncpu: 1361258.202226354 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 5380.782059693101,
            "unit": "ns/iter",
            "extra": "iterations: 117367\ncpu: 5378.435429038827 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 21660.753157209812,
            "unit": "ns/iter",
            "extra": "iterations: 28427\ncpu: 21651.596580715497 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 215172.69469835664,
            "unit": "ns/iter",
            "extra": "iterations: 4376\ncpu: 215162.89396709332 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 1307481.0254902132,
            "unit": "ns/iter",
            "extra": "iterations: 510\ncpu: 1307078.0509803928 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 10850394.56896565,
            "unit": "ns/iter",
            "extra": "iterations: 58\ncpu: 10849399.741379302 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 51848535.75000048,
            "unit": "ns/iter",
            "extra": "iterations: 12\ncpu: 51825833.24999997 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 35765.01303755569,
            "unit": "ns/iter",
            "extra": "iterations: 15417\ncpu: 35739.125056755474 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 197274.93611111163,
            "unit": "ns/iter",
            "extra": "iterations: 4320\ncpu: 196873.60856481487 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 1517303.2379421347,
            "unit": "ns/iter",
            "extra": "iterations: 622\ncpu: 1513132.14630225 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 11308483.859999966,
            "unit": "ns/iter",
            "extra": "iterations: 50\ncpu: 11280176.33999999 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 75374530.57142939,
            "unit": "ns/iter",
            "extra": "iterations: 7\ncpu: 75343734.85714291 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 426381580.0000046,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 425839968 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 534160748.99999446,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 534105119.9999995 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 367127812.0000068,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 367092981.00000256 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 151528435.39999878,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 151523239.39999944 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 117023077.50000073,
            "unit": "ns/iter",
            "extra": "iterations: 6\ncpu: 117010965.16666709 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09410282932816633,
            "unit": "ms/iter",
            "extra": "iterations: 7740\ncpu: 0.09409568863049092 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 1.7037472572115375,
            "unit": "ms/iter",
            "extra": "iterations: 416\ncpu: 1.7036513870192225 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 136.60004280000067,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 136.59695380000016 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 937.4660259999956,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 937.4174499999981 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.24036181877133278,
            "unit": "ms/iter",
            "extra": "iterations: 2930\ncpu: 0.24035112218429852 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 2.876242850806447,
            "unit": "ms/iter",
            "extra": "iterations: 248\ncpu: 2.8760085725806674 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 174.4041430000003,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 174.3909229999989 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 1150.8929640000076,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1150.8353239999992 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.6709775477338378,
            "unit": "ms/iter",
            "extra": "iterations: 1037\ncpu: 0.6709560983606561 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 8.914067855670137,
            "unit": "ms/iter",
            "extra": "iterations: 97\ncpu: 8.91388939175253 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 369.98708600000185,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 369.9699539999983 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 2100.0174569999926,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2099.9266839999964 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.129580349047883,
            "unit": "ms/iter",
            "extra": "iterations: 5409\ncpu: 0.1295767648363846 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.320651371237458,
            "unit": "ms/iter",
            "extra": "iterations: 299\ncpu: 2.320479963210695 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 138.53683880000176,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 138.5323308000011 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 749.7742779999896,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 749.7067840000043 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.3271949542056133,
            "unit": "ms/iter",
            "extra": "iterations: 2140\ncpu: 0.3271894887850453 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.4112623140096914,
            "unit": "ms/iter",
            "extra": "iterations: 207\ncpu: 3.4110121594202862 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 150.53911139999911,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 150.5354206000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 1979.503508999997,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1979.3910930000038 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.1507151833060525,
            "unit": "ms/iter",
            "extra": "iterations: 611\ncpu: 1.1506249738134193 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 9.158859735294262,
            "unit": "ms/iter",
            "extra": "iterations: 68\ncpu: 9.158884529411766 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 229.30780866667533,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 229.30242233333092 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 1165.0324800000078,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1164.9681669999977 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 6.685005913669088,
            "unit": "ms/iter",
            "extra": "iterations: 139\ncpu: 6.684548611510779 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 229.32746766665937,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 229.32095366666752 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 934.678028999997,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 934.5661619999959 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.2604252495316539,
            "unit": "ms/iter",
            "extra": "iterations: 2669\ncpu: 0.2604182071937026 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.178244778280465,
            "unit": "ms/iter",
            "extra": "iterations: 221\ncpu: 3.178129719457061 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 189.40356674999492,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 189.3933817500013 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 1223.451744000016,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1223.3834939999895 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 0.8631483628938048,
            "unit": "ms/iter",
            "extra": "iterations: 857\ncpu: 0.8631104375729389 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 12.834147070175337,
            "unit": "ms/iter",
            "extra": "iterations: 57\ncpu: 12.833346701754316 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 470.700769000004,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 470.6340369999964 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 2312.2977230000006,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2312.1729819999928 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.36964211384286194,
            "unit": "ms/iter",
            "extra": "iterations: 1871\ncpu: 0.3696273853554244 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 4.027488807017603,
            "unit": "ms/iter",
            "extra": "iterations: 171\ncpu: 4.027288836257299 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 342.0649606666662,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 342.0446209999994 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 2153.090638999998,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2152.9423220000012 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.0189017833333265,
            "unit": "ms/iter",
            "extra": "iterations: 660\ncpu: 1.0188622909090839 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 19.625230315789484,
            "unit": "ms/iter",
            "extra": "iterations: 38\ncpu: 19.624178842105408 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 493.19828700001267,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 493.16698599999853 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 2691.553421999998,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2691.3686559999946 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.750379024841138,
            "unit": "ms/iter",
            "extra": "iterations: 1731\ncpu: 0.7503125649913377 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 5.818690981981887,
            "unit": "ms/iter",
            "extra": "iterations: 111\ncpu: 5.8182396576577 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 424.8895385000111,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 424.8658094999982 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 2426.98921600001,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2426.7841439999956 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.4268321307077521,
            "unit": "ms/iter",
            "extra": "iterations: 1752\ncpu: 0.4268120479452104 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 9.575777244444339,
            "unit": "ms/iter",
            "extra": "iterations: 90\ncpu: 9.575495833333353 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 388.2276380000036,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 388.19876699999867 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 2273.872636999982,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2273.7811470000083 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 2995689983.0000052,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2995506058.9999933 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3641467379.9999948,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3641231749.9999886 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4583566633.999993,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4583308107.999997 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5391698867.999991,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5391175352.999994 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 716492823.9999995,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 716478674.9999905 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 483944060.4999936,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 483917392.9999987 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 3015641642.00002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3015376587.00002 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 3073673907,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3073370149.999988 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 182141048.24999565,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 182132132.74999872 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 206262941.66666523,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 206264087.33333316 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1481440034.000002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1481325273.9999995 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1149897709.0000153,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1148576864.9999955 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "2vir.sharma@gmail.com",
            "name": "Vir-007",
            "username": "Vir-007"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "7d5752d431d7dc69e3886a3025ac58a85680d94e",
          "message": "feat: add PageRank algorithm (#448)\n\nAdds `pagerank` for directed graphs under a new ranking category, with a\nconfigurable damping factor, convergence tolerance and iteration limit.\nDangling vertices redistribute their rank uniformly so the ranks always\nsum to one. Invalid parameters throw std::invalid_argument; failing to\nconverge within the iteration limit returns std::nullopt.\n\nCo-authored-by: Claude Opus 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-19T22:19:26+02:00",
          "tree_id": "f2f34d3145ebb7563e4e41814ced353ddcfba864",
          "url": "https://github.com/bobluppes/graaf/commit/7d5752d431d7dc69e3886a3025ac58a85680d94e"
        },
        "date": 1789849392533,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 48284.68655891161,
            "unit": "ns/iter",
            "extra": "iterations: 14612\ncpu: 48274.62092800448 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 238639.8026936104,
            "unit": "ns/iter",
            "extra": "iterations: 2970\ncpu: 238604.71717171685 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 688828.699009965,
            "unit": "ns/iter",
            "extra": "iterations: 1010\ncpu: 688775.365346523 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 54762.1644399786,
            "unit": "ns/iter",
            "extra": "iterations: 12649\ncpu: 54762.699106647015 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 296604.0632645473,
            "unit": "ns/iter",
            "extra": "iterations: 2371\ncpu: 296593.8616617468 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 833753.288114108,
            "unit": "ns/iter",
            "extra": "iterations: 774\ncpu: 833819.1666666447 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 2449.033944658304,
            "unit": "ns/iter",
            "extra": "iterations: 263635\ncpu: 2448.8969408462463 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 10142.10969974997,
            "unit": "ns/iter",
            "extra": "iterations: 60383\ncpu: 10140.620472649596 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 97809.60566981632,
            "unit": "ns/iter",
            "extra": "iterations: 8995\ncpu: 97787.66903835461 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 806579.9325095052,
            "unit": "ns/iter",
            "extra": "iterations: 1052\ncpu: 806264.7290874531 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 5189172.555555516,
            "unit": "ns/iter",
            "extra": "iterations: 117\ncpu: 5187087.940170938 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 24555647.30769256,
            "unit": "ns/iter",
            "extra": "iterations: 26\ncpu: 24553692.999999996 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 22056.56587724562,
            "unit": "ns/iter",
            "extra": "iterations: 28333\ncpu: 21990.635478064436 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 87252.65862758168,
            "unit": "ns/iter",
            "extra": "iterations: 7505\ncpu: 87064.89273817465 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 717227.4739756286,
            "unit": "ns/iter",
            "extra": "iterations: 903\ncpu: 715774.7519379836 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 5758858.636363585,
            "unit": "ns/iter",
            "extra": "iterations: 110\ncpu: 5743134.163636364 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 47055554.19999996,
            "unit": "ns/iter",
            "extra": "iterations: 15\ncpu: 46917430.39999991 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 254480372.499998,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 254016656.50000104 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 527802903.99999785,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 527725013.5000013 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 365457426.5000008,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 365372251.4999984 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 133081524.79999933,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 133070707.59999959 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 90741587.37500149,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 90730785.12500033 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.05288122959849282,
            "unit": "ms/iter",
            "extra": "iterations: 13798\ncpu: 0.052877073343962765 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 1.0359038238410736,
            "unit": "ms/iter",
            "extra": "iterations: 755\ncpu: 1.0357096847682135 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 81.1688784444442,
            "unit": "ms/iter",
            "extra": "iterations: 9\ncpu: 81.15055111111107 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 1838.2884819999958,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 1838.0912639999992 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.1128301885732648,
            "unit": "ms/iter",
            "extra": "iterations: 6231\ncpu: 0.11282188589311438 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 1.7615697892030673,
            "unit": "ms/iter",
            "extra": "iterations: 389\ncpu: 1.761423321336753 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 113.33986766666726,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 113.33315116666635 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 1668.0196319999823,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1667.842725000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.38190669688693274,
            "unit": "ms/iter",
            "extra": "iterations: 1831\ncpu: 0.3818773648279606 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 5.099606360000166,
            "unit": "ms/iter",
            "extra": "iterations: 100\ncpu: 5.0991245999999535 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 129.37333333333356,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 129.36117650000037 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 1030.031001999987,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1029.9491059999966 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.063704140947876,
            "unit": "ms/iter",
            "extra": "iterations: 9727\ncpu: 0.06369891425927872 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 1.1702738873873864,
            "unit": "ms/iter",
            "extra": "iterations: 666\ncpu: 1.1701766666666713 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 75.7445094000019,
            "unit": "ms/iter",
            "extra": "iterations: 10\ncpu: 75.7383308999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 535.1540405000037,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 535.108165999997 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.15585241642619385,
            "unit": "ms/iter",
            "extra": "iterations: 4505\ncpu: 0.1558391438401787 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 2.0461614228723377,
            "unit": "ms/iter",
            "extra": "iterations: 376\ncpu: 2.046009244680852 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 142.63213300000075,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 142.62461639999913 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 2148.0792350000115,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2147.8755440000014 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 0.6173107461746237,
            "unit": "ms/iter",
            "extra": "iterations: 1111\ncpu: 0.6172756588658869 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 6.129404732142772,
            "unit": "ms/iter",
            "extra": "iterations: 112\ncpu: 6.128980285714292 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 174.73307725000353,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 174.71411900000078 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 1830.5929509999999,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1830.4464809999956 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 4.42382938690466,
            "unit": "ms/iter",
            "extra": "iterations: 168\ncpu: 4.423150434523782 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 219.84461666665803,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 219.8254850000012 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 855.378112000011,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 855.2646440000018 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.1279328616455974,
            "unit": "ms/iter",
            "extra": "iterations: 5457\ncpu: 0.12792264760857805 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 1.7373974187192427,
            "unit": "ms/iter",
            "extra": "iterations: 406\ncpu: 1.737238113300486 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 79.08088687500126,
            "unit": "ms/iter",
            "extra": "iterations: 8\ncpu: 79.07625275000107 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 509.8054725000054,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 509.75453600000264 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 0.481373006211181,
            "unit": "ms/iter",
            "extra": "iterations: 1449\ncpu: 0.48129841545894014 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 11.443659947368483,
            "unit": "ms/iter",
            "extra": "iterations: 76\ncpu: 11.442153947368595 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 160.07981125000015,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 160.0678317499984 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 1994.1819590000023,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1993.973006999994 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.19291764954682755,
            "unit": "ms/iter",
            "extra": "iterations: 3641\ncpu: 0.1929019884647053 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 2.340449418604628,
            "unit": "ms/iter",
            "extra": "iterations: 301\ncpu: 2.340287548172761 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 147.0602155999984,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 147.04304020000052 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 1887.6480630000003,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1887.5168299999955 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 0.7528063300546546,
            "unit": "ms/iter",
            "extra": "iterations: 915\ncpu: 0.7527741967213105 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 10.704352345454605,
            "unit": "ms/iter",
            "extra": "iterations: 55\ncpu: 10.702966963636516 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 169.1899922500042,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 169.17077500000133 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 1188.401429999999,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1188.3159970000038 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.48180154650437024,
            "unit": "ms/iter",
            "extra": "iterations: 3204\ncpu: 0.481744563670416 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 4.017310857142726,
            "unit": "ms/iter",
            "extra": "iterations: 168\ncpu: 4.016810142857115 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 113.84255042857002,
            "unit": "ms/iter",
            "extra": "iterations: 7\ncpu: 113.83047642857288 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 870.652290999999,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 870.5717069999963 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.30092368667810054,
            "unit": "ms/iter",
            "extra": "iterations: 1749\ncpu: 0.3008784259576876 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 4.839442285714313,
            "unit": "ms/iter",
            "extra": "iterations: 119\ncpu: 4.839077966386472 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 118.09514814285649,
            "unit": "ms/iter",
            "extra": "iterations: 7\ncpu: 118.08876742857218 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 584.2084549999811,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 584.1174780000102 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 2945449155.0000057,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2945137564.0000067 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3210940618.9999847,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3210542008.999994 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4613783331.999997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4612275029.999992 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5077834775.000013,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5077222278.000008 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 676791460.000004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 676748407.0000051 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 440724483.5000057,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 440529559.4999998 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 2587111329.999999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2586801954.9999986 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 2459662086.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2459365114.999997 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 166260204.25000122,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 166238797.7499975 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 211803759.99999985,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 211770691.99999702 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1240472531.999984,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1240271441.0000045 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 927560074.000013,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 927486441.0000135 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "de4a2d402e4ad76e4211cb2402fd23b62bfa6dce",
          "message": "perf: back kruskal's union-find with vectors instead of unordered_map (#451)\n\n* perf: back kruskal's union-find with vectors instead of unordered_map\n\nSecond of a staged series for #443 (BFS landed in #449).\n\nparent/rank move from unordered_map<vertex_id_t, vertex_id_t> to\nvector<vertex_id_t>, indexed directly by id. do_make_set() is called\nonce per vertex up front (before any find/merge), so by the time a\nvertex_id_t reaches do_find_set()/do_merge_sets() its slot already\nexists - no lazy growth needed in either of those, only in\ndo_make_set() itself.\n\nUnion-find is a textbook case for this: it's designed around O(a(n))\namortized find/union assuming array-backed storage with path\ncompression; wrapping it in a hash map adds a hash + bucket-chain\nlookup to what's supposed to be close to a raw array access, on every\nsingle edge processed.\n\nBenchmarked (Release, perf/graaflib/kruskal_benchmark.cpp, real\ndatasets):\n\n                        before        after      speedup\nweb_google            6878.5ms     2252.3ms       3.05x\nweb_berkstan          5356.7ms     2684.2ms       2.00x\n\nNarrows the gap against the Boost.Graph comparison target\n(perf/boost, GRAAF_BUILD_BOOST_PERF):\n- web_google: 3.48x -> 1.14x\n- web_berkstan: 3.20x -> 1.60x\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* docs: trim kruskal DSU comment to only explain what was done\n\n---------\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-20T13:48:31+02:00",
          "tree_id": "d3e6d749dbbf59d6fb202d97769ad1bd6560e2e9",
          "url": "https://github.com/bobluppes/graaf/commit/de4a2d402e4ad76e4211cb2402fd23b62bfa6dce"
        },
        "date": 1789905118883,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 42376.28659682085,
            "unit": "ns/iter",
            "extra": "iterations: 16511\ncpu: 42366.64672036885 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 225049.6599999275,
            "unit": "ns/iter",
            "extra": "iterations: 3100\ncpu: 224992.61064515778 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 580727.4785893746,
            "unit": "ns/iter",
            "extra": "iterations: 1191\ncpu: 580807.3442485279 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 57042.58465030401,
            "unit": "ns/iter",
            "extra": "iterations: 12782\ncpu: 57035.7281333101 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 306596.55323974625,
            "unit": "ns/iter",
            "extra": "iterations: 2207\ncpu: 306675.8350702368 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 952371.9070903762,
            "unit": "ns/iter",
            "extra": "iterations: 818\ncpu: 952400.889975569 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 2416.3961995971595,
            "unit": "ns/iter",
            "extra": "iterations: 263130\ncpu: 2416.1199635161342 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 10181.40936127068,
            "unit": "ns/iter",
            "extra": "iterations: 59180\ncpu: 10177.489185535662 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 98894.07878186039,
            "unit": "ns/iter",
            "extra": "iterations: 9063\ncpu: 98871.57696127119 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 807583.2306220076,
            "unit": "ns/iter",
            "extra": "iterations: 1045\ncpu: 807438.7732057407 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 5130864.289256171,
            "unit": "ns/iter",
            "extra": "iterations: 121\ncpu: 5128697.338842978 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 31168002.111111075,
            "unit": "ns/iter",
            "extra": "iterations: 27\ncpu: 31072149.555555552 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 21797.323364873315,
            "unit": "ns/iter",
            "extra": "iterations: 28958\ncpu: 21794.373057531557 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 86135.92286465221,
            "unit": "ns/iter",
            "extra": "iterations: 7610\ncpu: 86090.29461235201 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 694937.5527747587,
            "unit": "ns/iter",
            "extra": "iterations: 919\ncpu: 694761.6583242666 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 5618133.660714239,
            "unit": "ns/iter",
            "extra": "iterations: 112\ncpu: 5617496.946428594 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 46775983.21428584,
            "unit": "ns/iter",
            "extra": "iterations: 14\ncpu: 46740821.71428573 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 200346511.3333315,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 200281611.33333337 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 506527466.0000085,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 506474110.9999993 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 406015031.4999973,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 405941929.00000083 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 140604923.99999875,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 140571762.40000048 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 97496448.99999867,
            "unit": "ns/iter",
            "extra": "iterations: 7\ncpu: 97485272.00000012 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.05355444048414642,
            "unit": "ms/iter",
            "extra": "iterations: 13467\ncpu: 0.05355209281948509 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 1.0518465461741264,
            "unit": "ms/iter",
            "extra": "iterations: 758\ncpu: 1.0516783627968365 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 81.9860403333321,
            "unit": "ms/iter",
            "extra": "iterations: 9\ncpu: 81.97689088888893 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 525.0705339999939,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 525.0393190000011 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.11654647435237657,
            "unit": "ms/iter",
            "extra": "iterations: 5829\ncpu: 0.11653575484645716 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 1.8033112748815103,
            "unit": "ms/iter",
            "extra": "iterations: 422\ncpu: 1.803228168246441 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 126.8100956000012,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 126.79952720000074 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 1637.3778990000005,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1637.1234730000026 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.40216340877598,
            "unit": "ms/iter",
            "extra": "iterations: 1732\ncpu: 0.4020865161662851 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 5.776130905797059,
            "unit": "ms/iter",
            "extra": "iterations: 138\ncpu: 5.775561623188398 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 98.31755433333218,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 98.30153833333337 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 541.6444329999877,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 541.5916420000002 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.06879308702731927,
            "unit": "ms/iter",
            "extra": "iterations: 11054\ncpu: 0.06878816491767695 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 1.3013334112769575,
            "unit": "ms/iter",
            "extra": "iterations: 603\ncpu: 1.3011540066335052 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 156.0974162000008,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 156.08193220000004 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 1788.874469999996,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1788.7072449999978 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.17775035678866655,
            "unit": "ms/iter",
            "extra": "iterations: 4235\ncpu: 0.17773710649350558 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 2.1969719776357635,
            "unit": "ms/iter",
            "extra": "iterations: 313\ncpu: 2.1968612236421836 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 117.13534179999954,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 117.12653599999926 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 1343.6092110000004,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1343.456394999997 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 0.6542723250714945,
            "unit": "ms/iter",
            "extra": "iterations: 1049\ncpu: 0.6542154957102034 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 6.517623570093391,
            "unit": "ms/iter",
            "extra": "iterations: 107\ncpu: 6.516672570093495 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 161.1285573999993,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 161.11741899999998 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 1444.2246119999993,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1444.0582339999964 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 4.164518343749979,
            "unit": "ms/iter",
            "extra": "iterations: 128\ncpu: 4.164381687499996 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 275.5246693333315,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 275.50211433333044 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 837.3660079999894,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 837.2750310000043 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.14210173978450727,
            "unit": "ms/iter",
            "extra": "iterations: 4919\ncpu: 0.14209276397641601 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 1.992923510324481,
            "unit": "ms/iter",
            "extra": "iterations: 339\ncpu: 1.9926115486725848 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 127.71090916666594,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 127.69965616666686 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 1655.390975000003,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1655.2462279999959 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 0.5999147970765185,
            "unit": "ms/iter",
            "extra": "iterations: 1163\ncpu: 0.5998779045571804 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 14.367380031250043,
            "unit": "ms/iter",
            "extra": "iterations: 64\ncpu: 14.365062671874984 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 133.88071259999776,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 133.87401980000107 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 664.8072300000081,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 664.7050390000118 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.19740157737104805,
            "unit": "ms/iter",
            "extra": "iterations: 3606\ncpu: 0.1973889869661689 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 2.3116641545741206,
            "unit": "ms/iter",
            "extra": "iterations: 317\ncpu: 2.3112939179810787 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 152.50134919999994,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 152.49014160000058 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 1583.2487830000018,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1583.1037869999989 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 0.7231003732912806,
            "unit": "ms/iter",
            "extra": "iterations: 951\ncpu: 0.7230681829653006 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 19.101671485714178,
            "unit": "ms/iter",
            "extra": "iterations: 35\ncpu: 19.09726568571435 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 243.71553799999882,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 243.6967266666651 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 2382.116763000013,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2381.8328020000054 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.49308800838980393,
            "unit": "ms/iter",
            "extra": "iterations: 3099\ncpu: 0.4930542597612109 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 4.516990160000042,
            "unit": "ms/iter",
            "extra": "iterations: 175\ncpu: 4.516776108571402 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 166.07586349999792,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 166.06423500000034 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 1671.0056729999962,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1670.8156119999985 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.30657023559037644,
            "unit": "ms/iter",
            "extra": "iterations: 1787\ncpu: 0.3065276351426989 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 5.094190254098175,
            "unit": "ms/iter",
            "extra": "iterations: 122\ncpu: 5.093682008196708 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 163.2644049999996,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 163.2381112499992 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 2248.873695000015,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2248.5811840000024 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3077320361.0000052,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3076922514.0000033 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3657365802.0000153,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3657001145.999999 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4744141812.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4743550654.000004 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5344714083.999974,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5344132455.999997 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 730474466.0000039,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 730382431.9999989 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 495256120.9999971,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 495198002.500004 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 1039796109.9999975,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1039719681.9999976 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 1350803264.9999962,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1350631047.9999967 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 181748948.24999654,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 181731226.25000104 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 223578906.99999908,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 223523880.66666624 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1371345760.9999864,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1371191021.0000155 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1072143662.000002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1071954955.0000238 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "9b9e63fe7774b6a781a50af8d4791dba2ff98986",
          "message": "perf: back prim's tree-membership map with a vector instead of unordered_map (#452)\n\n* perf: back prim's tree-membership map with a vector instead of unordered_map\n\nThird of a staged series for #443 (BFS landed in #449, Kruskal in #451).\n\ntree_node_for_vertex moves from unordered_map<vertex_id_t, tree_node_t*>\nto vector<tree_node_t*>, indexed directly by id. Unlike Kruskal's\nunion-find (all vertices known up front), Prim discovers vertices\nincrementally as the frontier grows, so this needs the same lazy-growth\nshape as BFS's seen_vertices - except the vector needs to distinguish\n\"not yet in the tree\" from \"in the tree\", so it's grown with nullptr\nas the not-present sentinel instead of vector<bool>.\n\nMembership checks (in_tree()) never grow the vector - an id past the\ncurrent size is definitionally not in the tree yet, so a plain bounds\ncheck answers \"not present\" without allocating a slot for a vertex\nthat's only being queried, not inserted. Only add_to_tree() grows.\nvertices_in_tree tracks the live count separately, since (unlike an\nunordered_map) a vector's size includes null-filled slots.\n\nBenchmarked (Release, perf/graaflib/prim_benchmark.cpp, real datasets):\n\n                        before        after      speedup\nweb_google             410.2ms      296.0ms       1.39x\nweb_berkstan            433.0ms      308.5ms       1.40x\n\nNarrows the gap against the Boost.Graph comparison target\n(perf/boost, GRAAF_BUILD_BOOST_PERF):\n- web_google: 2.78x -> 2.01x\n- web_berkstan: 2.60x -> 1.85x\n\nSmaller win than Kruskal's, as expected: prim_minimum_spanning_tree()\nstill pays for a separate graph.get_edge() hash lookup per candidate\nedge on top of this - that's #444's scope, not this one.\n\nCo-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>\n\n* docs: trim prim tree-membership comment to only explain what was done\n\n---------\n\nCo-authored-by: Claude Sonnet 5 <noreply@anthropic.com>",
          "timestamp": "2026-09-20T13:48:50+02:00",
          "tree_id": "bab3dc17baef6f6221fe69edc5b45212baff1e98",
          "url": "https://github.com/bobluppes/graaf/commit/9b9e63fe7774b6a781a50af8d4791dba2ff98986"
        },
        "date": 1789905163400,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_add_primitive_numeric_edge/1000",
            "value": 84685.3247411202,
            "unit": "ns/iter",
            "extra": "iterations: 8302\ncpu: 84684.40881715209 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/4096",
            "value": 425915.4684465609,
            "unit": "ns/iter",
            "extra": "iterations: 1648\ncpu: 426032.9435679597 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_edge/10000",
            "value": 1277714.5086047256,
            "unit": "ns/iter",
            "extra": "iterations: 523\ncpu: 1277631.3594646468 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/1000",
            "value": 101518.02745097817,
            "unit": "ns/iter",
            "extra": "iterations: 6885\ncpu: 101503.55686274439 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/4096",
            "value": 561738.2534086205,
            "unit": "ns/iter",
            "extra": "iterations: 1247\ncpu: 561779.2405773853 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_edge/10000",
            "value": 1598225.3865335414,
            "unit": "ns/iter",
            "extra": "iterations: 401\ncpu: 1598038.0074812968 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/1000",
            "value": 5058.385626924643,
            "unit": "ns/iter",
            "extra": "iterations: 137034\ncpu: 5055.652619058047 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/4096",
            "value": 20201.07865420758,
            "unit": "ns/iter",
            "extra": "iterations: 35637\ncpu: 20100.868226842875 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/32768",
            "value": 154910.54577672516,
            "unit": "ns/iter",
            "extra": "iterations: 5079\ncpu: 154895.59775546347 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/262144",
            "value": 1254926.7275747212,
            "unit": "ns/iter",
            "extra": "iterations: 602\ncpu: 1254464.3837209293 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/2097152",
            "value": 10217093.830985831,
            "unit": "ns/iter",
            "extra": "iterations: 71\ncpu: 10215916.859154936 ns\nthreads: 1"
          },
          {
            "name": "bm_add_primitive_numeric_vertex/10000000",
            "value": 47875754.18750123,
            "unit": "ns/iter",
            "extra": "iterations: 16\ncpu: 47857313.18750008 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/1000",
            "value": 34324.82688823618,
            "unit": "ns/iter",
            "extra": "iterations: 16007\ncpu: 34311.547323046165 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/4096",
            "value": 173607.15540540832,
            "unit": "ns/iter",
            "extra": "iterations: 4884\ncpu: 173574.81285831297 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/32768",
            "value": 1355245.9999999655,
            "unit": "ns/iter",
            "extra": "iterations: 400\ncpu: 1354762.075 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/262144",
            "value": 11294702.680555385,
            "unit": "ns/iter",
            "extra": "iterations: 72\ncpu: 11293950.61111111 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/2097152",
            "value": 74670124.87499858,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 74660809.25000007 ns\nthreads: 1"
          },
          {
            "name": "bm_add_user_defined_vertex/10000000",
            "value": 386200291.50000334,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 386160930.4999991 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_google",
            "value": 500985384.0000176,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 500944373.99999946 ns\nthreads: 1"
          },
          {
            "name": "bm_bfs_shortest_path/web_berkstan",
            "value": 356086077.9999899,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 356053357.0000004 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_google",
            "value": 130195484.00000502,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 130177872.75000003 ns\nthreads: 1"
          },
          {
            "name": "bm_breadth_first_search/web_berkstan",
            "value": 91256851.12499937,
            "unit": "ns/iter",
            "extra": "iterations: 8\ncpu: 91246059.62499999 ns\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/2",
            "value": 0.09219979532310583,
            "unit": "ms/iter",
            "extra": "iterations: 7954\ncpu: 0.09219837138546629 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/2",
            "value": 1.6967267067307454,
            "unit": "ms/iter",
            "extra": "iterations: 416\ncpu: 1.6966065745192334 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/2",
            "value": 125.14669233333582,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 125.12998183333343 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/2",
            "value": 1737.600907000001,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1737.4826720000058 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/8",
            "value": 0.20196837731958753,
            "unit": "ms/iter",
            "extra": "iterations: 3395\ncpu: 0.2019418347569948 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/8",
            "value": 2.6590551310860686,
            "unit": "ms/iter",
            "extra": "iterations: 267\ncpu: 2.658918606741566 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/8",
            "value": 245.48087824999953,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 245.4636467500002 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/8",
            "value": 1604.6891530000096,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1604.5859809999997 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/32",
            "value": 0.7431861467793255,
            "unit": "ms/iter",
            "extra": "iterations: 947\ncpu: 0.7431497022175335 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/32",
            "value": 9.293394640449508,
            "unit": "ms/iter",
            "extra": "iterations: 89\ncpu: 9.29289829213483 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/32",
            "value": 519.5640649999973,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 519.4775609999951 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/32",
            "value": 3195.614092999989,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3195.4107170000016 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/2",
            "value": 0.12291844222338896,
            "unit": "ms/iter",
            "extra": "iterations: 5703\ncpu: 0.12290765719796658 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/2",
            "value": 2.1916428424437573,
            "unit": "ms/iter",
            "extra": "iterations: 311\ncpu: 2.191556389067538 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/2",
            "value": 124.95420779999904,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 124.9404362000007 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/2",
            "value": 1378.7011800000073,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1378.617888000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/8",
            "value": 0.3070111853315671,
            "unit": "ms/iter",
            "extra": "iterations: 2277\ncpu: 0.30698379490557653 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/8",
            "value": 3.189936315068441,
            "unit": "ms/iter",
            "extra": "iterations: 219\ncpu: 3.1898807853881372 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/8",
            "value": 381.60913649999867,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 381.5809851666666 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/8",
            "value": 3224.355513000006,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3220.8359990000017 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/32",
            "value": 1.339360149712098,
            "unit": "ms/iter",
            "extra": "iterations: 521\ncpu: 1.3392506660268673 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/32",
            "value": 9.474938873015816,
            "unit": "ms/iter",
            "extra": "iterations: 63\ncpu: 9.468289619047619 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/32",
            "value": 214.94860500000357,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 214.93395425000017 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/32",
            "value": 1898.5663789999876,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1898.411944000003 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/1000",
            "value": 5.087655060000031,
            "unit": "ms/iter",
            "extra": "iterations: 100\ncpu: 5.086743850000062 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/1000",
            "value": 208.46831800000132,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 208.43944533333078 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/1000/1000",
            "value": 803.3579380000049,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 803.2454680000001 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/10",
            "value": 0.2565771464646531,
            "unit": "ms/iter",
            "extra": "iterations: 2772\ncpu: 0.25657095418470477 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/10",
            "value": 3.0628895726872463,
            "unit": "ms/iter",
            "extra": "iterations: 227\ncpu: 3.06284134361231 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/10",
            "value": 127.23730766666581,
            "unit": "ms/iter",
            "extra": "iterations: 6\ncpu: 127.22984933333237 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/10",
            "value": 1906.4436479999927,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1906.2534959999907 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/100/60",
            "value": 1.0668015266853919,
            "unit": "ms/iter",
            "extra": "iterations: 712\ncpu: 1.066677341292137 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/512/60",
            "value": 14.98152972916659,
            "unit": "ms/iter",
            "extra": "iterations: 48\ncpu: 14.980924645833523 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/4096/60",
            "value": 596.5260440000009,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 596.447296000008 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_cliques/10000/60",
            "value": 3496.0109410000086,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3495.7740039999976 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/10",
            "value": 0.38025578614623284,
            "unit": "ms/iter",
            "extra": "iterations: 1819\ncpu: 0.3802418152831274 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/10",
            "value": 3.853008994413354,
            "unit": "ms/iter",
            "extra": "iterations: 179\ncpu: 3.852648592178748 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/10",
            "value": 162.8917542499977,
            "unit": "ms/iter",
            "extra": "iterations: 4\ncpu: 162.88727649999757 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/10",
            "value": 1723.2846999999936,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1723.1594189999983 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/100/60",
            "value": 1.2353639876325047,
            "unit": "ms/iter",
            "extra": "iterations: 566\ncpu: 1.2353059240282809 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/512/60",
            "value": 22.08515009374956,
            "unit": "ms/iter",
            "extra": "iterations: 32\ncpu: 22.0817027812501 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/4096/60",
            "value": 376.1133404999981,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 376.0748970000023 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_cliques/10000/60",
            "value": 2327.197769999998,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2326.9722109999975 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/100",
            "value": 0.7740299768170538,
            "unit": "ms/iter",
            "extra": "iterations: 1596\ncpu: 0.7739966447368423 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/512",
            "value": 5.669402775000047,
            "unit": "ms/iter",
            "extra": "iterations: 120\ncpu: 5.668865233333402 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/4096",
            "value": 500.0937190000059,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 500.03105700000106 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_random_cliques/10000",
            "value": 3224.7217489999966,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3224.4227900000055 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/100",
            "value": 0.5615616922572314,
            "unit": "ms/iter",
            "extra": "iterations: 1524\ncpu: 0.5615260492126002 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/512",
            "value": 8.255884917525808,
            "unit": "ms/iter",
            "extra": "iterations: 97\ncpu: 8.254950690721593 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/4096",
            "value": 209.50535833333106,
            "unit": "ms/iter",
            "extra": "iterations: 3\ncpu: 209.49729699999864 ms\nthreads: 1"
          },
          {
            "name": "bron_kerbosh_connected_random_cliques/10000",
            "value": 2134.045858999997,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2131.281647000009 ms\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_google",
            "value": 3045243716.0000157,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3044996180.9999876 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_path/web_berkstan",
            "value": 3775068038.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3774698290.999993 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_google",
            "value": 4761039176.000026,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4758310163.999994 ns\nthreads: 1"
          },
          {
            "name": "bm_dijkstra_shortest_paths/web_berkstan",
            "value": 5662963890.000014,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5662394513.00001 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_google",
            "value": 705519904.9999601,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 705459197.9999998 ns\nthreads: 1"
          },
          {
            "name": "bm_greedy_graph_coloring/web_berkstan",
            "value": 439383610.9999825,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 439327089.4999972 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_google",
            "value": 1035516377.9999543,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1035447928.0000248 ns\nthreads: 1"
          },
          {
            "name": "bm_kruskal/web_berkstan",
            "value": 1369357849.000039,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1369176930.000009 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_google",
            "value": 143246710.20000324,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 143231514.99999654 ns\nthreads: 1"
          },
          {
            "name": "bm_prim/web_berkstan",
            "value": 190461925.50000286,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 190450337.75000066 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_google",
            "value": 1342351817.9999974,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1342137500.000007 ns\nthreads: 1"
          },
          {
            "name": "bm_welsh_powell_coloring/web_berkstan",
            "value": 1040305617.9999908,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1037630293.0000066 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}