# network-flow
A C++ implementation of Dinic's algorithm for max-flow. Here is a summary of operations:

* __FlowNetwork f(n, m)__: new network with n vertices (0 to n-1) and m directed edges,
* __f.add(x, y, c)__     : add directed edge from node x to node y with capacity c,
* __f.flow(s, t)__       : compute max-flow/min-cut from vertex s to vertex t.
