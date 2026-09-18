window.BENCHMARK_DATA = {
  "lastUpdate": 1789770464746,
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
      }
    ]
  }
}