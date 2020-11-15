	fill(dist, dist + n, INF);

    priority_queue<Vert> q;
    q.push({s, 0});
    dist[s] = 0;
    while (!q.empty()) {
        int v = q.top().v;
        int curd = q.top().dist;
        q.pop();
        if (curd > dist[v])
            continue;
        fx(e, g[v]) {
            int to = e.first;
            int cost = e.second;
            if (cost + curd < dist[to]) {
                dist[to] = cost + curd;
                q.push({to, dist[to]});
            }
        }
    }
    