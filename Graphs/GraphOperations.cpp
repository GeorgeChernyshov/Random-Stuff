#include "../include/GraphOperations.h"

void Initialize()
{
    for(int i = 0; i < 1002; ++i) {
        for(int j = 0; j < 1002; ++j) {
            graph[i][j] = 0;
            if(i == j - 1) graph[i][j] = 1;
        }
    }
}

void GenerateGraph(int graphSize)
{
    int N = 2*graphSize - (graphSize/2);
    int M = graphSize + 1 - (graphSize/2);
    int m = graphSize/3;
    int degree[graphSize];
    double probability = graphSize;
    probability *= (M - m + 1);
    probability /= (N - m + 1);
    for(int i = 2; i <= m; ++i) {
        probability *= (M - m + i);
        probability /= (N - m + i);
    }
    degree[0] = (int)probability;
    for(int i = 1; i < graphSize; ++i) {
        probability *= (m - 1 + i);
        probability *= (N - M + 1 - i);
        probability /= i;
        probability /= (N - m + 1 - i);
        degree[i] = (int)probability;
    }
    std::cout << std::endl;
    for(int i = 0; i < graphSize; ++i)
        std::cout << degree[i] << " ";
    std::cout << std::endl;
    srand(time(NULL));
    for(int i = 0; i < graphSize; ++i) {
        while(degree[i]) {
            int index = rand() % (graphSize - i - 1);
            if(graph[i][i + index + 1] == 0) {
                graph[i][i + index + 1] = 1;
                degree[i]--;
            }
        }
    }
}

void PrintGraph(int (&gr)[1002][1002], int graphSize)
{
    std::cout << std::endl;
    for(int i = 0; i < graphSize; ++i) {
        for(int j = 0; j < graphSize; ++j) {
            if(gr[i][j] < 1000000) {
                std::cout << gr[i][j] << " ";
                if(gr[i][j] < 100) {
                    std::cout << " ";
                    if(gr[i][j] < 10)
                        std::cout << " ";
                }
            } else {
                std::cout << "inf" << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Shimbell(int pathlength, int graphSize)
{
    int opt = -1;
    while(opt != 0 && opt != 1){
        std::cout << "Input 0 for minimum or 1 for maximum: ";
        std::cin >> opt;
    }
    int newgraph[1002][1002];
    for(int i = 0; i < graphSize; ++i)
        for(int j = 0; j < graphSize; ++j)
            newgraph[i][j] = graph[i][j];

    for(int l = 1; l < pathlength; ++l) {
        int tempgraph[1002][1002];
        for(int i = 0; i < graphSize; ++i) {
            for(int j = 0; j < graphSize; ++j) {
                tempgraph[i][j] = newgraph[i][j];
            }
        }
        for(int i = 0; i < graphSize; ++i) {
            for(int j = 0; j < graphSize; ++j) {
                newgraph[i][j] = opt ? 0 : 1000000;
                for(int k = 0; k < graphSize; ++k) {
                    if(tempgraph[i][k] + graph[k][j] < 1000000 && tempgraph[i][k] > 0)
                        newgraph[i][j] = opt ? std::max(newgraph[i][j], tempgraph[i][k] + graph[k][j])
                        : std::min(newgraph[i][j], tempgraph[i][k] + graph[k][j]);
                }
            }
        }
    }
    for(int i = 0; i < graphSize; ++i){
        for(int j = 0; j < graphSize; ++j){
            if(newgraph[i][j] == 0)
                newgraph[i][j] = 1000000;
        }
    }
    PrintGraph(newgraph, graphSize);
}

bool bfs(int v, int endv, int graphSize)
{
    for(int i = 0; i < graphSize; ++i) marked[i] = 0;
    std::queue<int> q;
    q.push(v);
    while(q.size() > 0){
        int x = q.front();
        marked[x] = 1;
        q.pop();
        for(int i = 0; i < graphSize; ++i)
            if(graph[x][i] < 1000000 && !marked[i]) q.push(i);
    }
    return marked[endv];
}

void GiveLengths(int graphSize)
{
    std::cout << "Graph Size = " << graphSize;
    PrintGraph(graph, graphSize);
    srand(time(NULL));
    for(int i = 0; i < graphSize; ++i){
        for(int j = 0; j < graphSize; ++j){
            if(graph[i][j] == 1){
                graph[i][j] = (rand() % 99) + 1;
            }else{
                graph[i][j] = 1000000;
            }
        }
    }

    std::cout << "\nGiving random path lengths\n";
    std::cout << "Updated graph:\n";
    PrintGraph(graph, graphSize);
    std::cout << std::endl;
}

int ReadGraph(std::string filename, int graphSize)
{
    std::ifstream ifs;
    ifs.open(filename.c_str());
    if(!ifs.good()){
        std::cout << "File does not exist. Ending program\n";
        return 0;
    }
    ifs >> graphSize;
    for(int i = 0; i < graphSize; ++i){
        for(int j = 0; j < graphSize; ++j){
            ifs >> graph[i][j];
        }
    }
    return graphSize;
}

void Floyd(int graphSize)
{
    for(int i = 0; i < graphSize; ++i)
        for(int j = 0; j < graphSize; ++j)
            floyd[i][j] = graph[i][j];

    int op = 0;
    for(int k = 0; k < graphSize; ++k){
        for(int i = 0; i < graphSize; ++i){
            for(int j = 0; j < graphSize; ++j){
                floyd[i][j] = std::min(floyd[i][j], floyd[i][k] + floyd[k][j]);
                op += 2;
            }
        }
    }
    PrintGraph(floyd, graphSize);
    std::cout << op << " operations\n";
}

void Dijkstra(int v, int graphSize)
{
    for(int i = 0; i < graphSize; i++){
        marked[i] = (i == v ? 1 : 0);
        distances[i] = (i == v ? 0 : 1000000);
    }
    int op = 0;
    for(int i = 0; i < graphSize; i++){
        std::pair<int, int> minimum(1000000, -1);
        op += 3;
        for(int j = 0; j < graphSize; j++){
            distances[j] = std::min(distances[j], distances[v] + graph[v][j]);
            op += 2;
            if(minimum.first >= distances[j] && !marked[j]){
                minimum.first = distances[j];
                minimum.second = j;
                op += 2;
            }
            op++;
        }
        marked[minimum.second] = 1;
        v = minimum.second;
        op += 2;
    }
    for(int i = 0; i < graphSize; i++){
        if(distances[i] < 1000000){
            std::cout << distances[i] << " ";
        }
        else{
            std::cout << "inf ";
        }
    }
    std::cout << std::endl;
    std::cout << op << " operations\n";
}

void FordBellman(int v, int graphSize)
{
    for(int i = 0; i < graphSize; i++){
        distances[i] = (i == v ? 0 : 1000000);
    }
    std::vector<Edge> edges;
    for(int i = 0 ; i < graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            if(graph[i][j] < 1000000){
            Edge e(i, j, graph[i][j]);
                edges.push_back(e);
            }
        }
    }
    int op = 0;
    for(int i = 0; i < graphSize; i++){
        for(int j = 0; j < edges.size(); j++){
            Edge edge = edges[j];
            op += 3;
            distances[edge.to] = std::min(distances[edge.to],
                distances[edge.from] + edge.length);
            op += 2;
        }
    }
    for(int i = 0; i < graphSize; i++){
        if(distances[i] < 1000000){
            std::cout << distances[i] << " ";
        }
        else{
            std::cout << "inf ";
        }
    }
    std::cout << std::endl;
    std::cout << op << " operations\n";
}

int get(int v, int op)
{
    if(parent[v] == v){
        op += 2;
        return v;
    }
    op += 2;
    return get(parent[v], op);
}

void Kruskal(int graphSize)
{
    for(int i = 0; i < graphSize; i++) parent[i] = i;
    int op = 0;
    std::vector<Edge> edges;
    for(int i = 0 ; i < graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            if(graph[i][j] < 1000000){
                Edge e(i, j, graph[i][j]);
                edges.push_back(e);
            }
            tree[i][j] = 1000000;
        }
    }
    std::sort(edges.begin(), edges.end());
    for(int t = 1; t < edges.size(); t *= 2) op++;
    op *= 3*graphSize;
    for(int k = 0; k < edges.size(); k++){
        Edge e = edges[k];
        op += 3;
        if(get(e.from, op) != get(e.to, op)){
            parent[get(e.to, op)] = e.from;
            tree[e.from][e.to] = e.length;
            tree[e.to][e.from] = e.length;
            op += 2;
        }
        op++;
    }
    PrintGraph(tree, graphSize);
    std::cout << op << " operations\n";
}

void Prim(int graphSize)
{
    int op = 0;
    int vertex = 0;
    std::list<Edge> edges;
    for(int i = 0; i < graphSize; i++) marked[i] = 0;
    for(int i = 0 ; i < graphSize; i++)
        for(int j = 0; j < graphSize; j++)
            tree[i][j] = 1000000;

    for(int i = 0; i < graphSize - 1; i++){
        marked[vertex] = 1;
        op++;
        for(int j = 0; j < graphSize; j++){
            if(graph[vertex][j] < 1000000 && !marked[j]){
                Edge e1(vertex, j, graph[vertex][j]);
                edges.push_back(e1);
                op += 4;
            }
            if(graph[j][vertex] < 1000000 && !marked[j]){
                Edge e1(j, vertex, graph[j][vertex]);
                edges.push_back(e1);
                op += 4;
            }
            op += 3;
        }
        Edge minedge(-1, -1, 1000000);
        op += 3;
        for(auto it = edges.begin(); it != edges.end(); it++){
            Edge edge = *it;
            op++;
            if((edge.length < minedge.length) && !(marked[edge.to] & marked[edge.from])){
                if(marked[edge.from]){
                    minedge.to = edge.to;
                    minedge.from = edge.from;
                    minedge.length = edge.length;
                    op += 3;
                } else {
                    minedge.to = edge.from;
                    minedge.from = edge.to;
                    minedge.length = edge.length;
                    op += 3;
                }
                op += 2;
            }
            op += 3;
        }
        tree[minedge.to][minedge.from] = minedge.length;
        tree[minedge.from][minedge.to] = minedge.length;
        op += 2;
        if(!marked[minedge.to]){
            vertex = minedge.to;
        } else {
            vertex = minedge.from;
        }
        marked[minedge.to] = 1;
        op += 4;
    }
    PrintGraph(tree, graphSize);
    std::cout << op << " operations\n";
}

void Kirhgoff(int graphSize)
{
    for(int i = 0; i < graphSize; i++){
        double deg = 0;
        for(int j = 0; j < graphSize; j++){
            if(graph[i][j] < 1000000 || graph[j][i] < 1000000){
                deg++;
                kMatrix[i][j] = -1;
            } else {
                kMatrix[i][j] = 0;
            }
        }
        kMatrix[i][i] = deg;
    }
    double ans = 1;
    for(int i = 0; i < graphSize - 1; i++){
        int k = i;
        for(int j = i + 1; j < graphSize - 1; j++){
            if(std::abs(kMatrix[j][i]) > std::abs(kMatrix[k][i])) k = j;
        }
        if(kMatrix[k][i] == 0){
            ans = 0;
            i = graphSize;
            break;
        }
        for(int j = 0; j < graphSize - 1; j++){
            double temp = kMatrix[k][j];
            kMatrix[k][j] = kMatrix[i][j];
            kMatrix[i][j] = temp;
        }
        if(i != k) ans = -ans;
        ans *= kMatrix[i][i];

        for(int j = i + 1; j < graphSize - 1; j++)
            kMatrix[i][j] /= kMatrix[i][i];

        for(int j = 0; j < graphSize - 1; j++)
            if(j != i && kMatrix[j][i] != 0)
                for(int k = i + 1; k < graphSize - 1; k++)
                    kMatrix[j][k] -= kMatrix[i][k] * kMatrix[j][i];
    }
    std::cout << std::abs(ans) << std::endl;
}

void dfs(int v, int graphSize)
{
    deg[v] = 0;
    for(int i = 0; i < graphSize; i++){
        int to = tree[v][i];
        if(to < 1000000){
            if(i != parent[v]){
                parent[i] = v;
                dfs(i, graphSize);
            }
            deg[v]++;
        }
    }
}

void Pruffer(int graphSize)
{
    for(int i = 0; i < graphSize; i++) parent[i] = -1;
    dfs(graphSize - 1, graphSize);

    int ptr = -1;
    for(int i = 0; i < graphSize; i++){
        if(deg[i] == 1 && ptr == -1) ptr = i;
    }
    std::vector<int> result;
    int leaf = ptr;
    for(int i = 0; i < graphSize - 2; i++){
        int next = parent[leaf];
        result.push_back(next);
        --deg[next];
        if(deg[next] == 1 && next < ptr){
            leaf = next;
        }
        else{
            ptr++;
            while(ptr < graphSize && deg[ptr] != 1) ++ptr;
            leaf = ptr;
        }
    }
    for(int i = 0; i < result.size(); ++i){
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i < graphSize; i++) deg[i] = 1;
    for(int i = 0; i < graphSize - 2; i++) ++deg[result[i]];

    ptr = 0;
    while(ptr < graphSize && deg[ptr] != 1) ++ptr;
    leaf = ptr;
    for(int i = 0; i < graphSize; i++)
        for(int j = 0; j < graphSize; j++)
            checktree[i][j] = 0;
    for(int i = 0; i < result.size(); ++i){
        int v = result[i];
        checktree[leaf][v] = 1;
        checktree[v][leaf] = 1;
        --deg[leaf];
        if(--deg[v] == 1 && v < ptr){
            leaf = v;
        } else {
            ++ptr;
            while(ptr < graphSize && deg[ptr] != 1) ++ptr;
            leaf = ptr;
        }
    }
    for(int i = 0; i < graphSize - 1; i++){
        if(deg[i] == 1){
            checktree[i][graphSize - 1] = 1;
            checktree[graphSize - 1][i] = 1;
        }
    }
    bool check = 1;
    for(int i = 0; i < graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            if(tree[i][j] == 1000000 && checktree[i][j] == 1) check = 0;
            if(tree[i][j] < 1000000 && checktree[i][j] == 0) check = 0;
        }
    }
    if(check){
        std::cout << "Code checked\n";
    } else {
        std::cout << "Error. Code is incorrect\n";
    }
}

void MakeHamilton(int graphSize)
{
    srand(time(NULL));
    for(int i = 0; i < graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            if(graph[i][j] < 1000000 || graph[j][i] < 1000000){
                cycles[i][j] = cycles[j][i] = std::min(graph[i][j], graph[j][i]);
            } else {
                cycles[i][j] = 1000000;
            }
        }
    }
    int x = (rand() % 99) + 1;
    cycles[0][graphSize - 1] = x;
    cycles[graphSize - 1][0] = x;
    for(int i = 0; i < graphSize; i++){
        full += (1 << i);
    }
    PrintGraph(cycles, graphSize);
    std::cout << std::endl;
}

void Hamilton(int graphSize, int A, int v)
{
    int cur = numb;
    for(int i = 0; i < graphSize; i++){
        if(cycles[v][i] < 1000000 && !(A & (1 << i))){
            Hamilton(graphSize, (A | (1 << i)), i);
        }
    }
    if((A == full) && (cycles[v][0] < 1000000)){
        hamc.push_back(std::vector<int>());
        hamc[numb++].push_back(cycles[v][0]);
    }
    while(cur < numb){
        hamc[cur][0] += cycles[v][hamc[cur][hamc[cur].size() - 1]];
        hamc[cur++].push_back(v);
    }
}

void PrintHamilton()
{
    std::pair<int, int> m(1000000, -1);
    for(int i = 0; i < hamc.size(); i++){
        std::cout << 0 << " ";
        for(int j = 1; j < hamc[i].size(); j++){
            std::cout << hamc[i][j] << " ";
        }
        std::cout << hamc[i][0] << std::endl;
        if(hamc[i][0] <= m.first){
            m.first = hamc[i][0];
            m.second = i;
        }
    }
    std::cout << std::endl << std::endl;
    for(int i = 0; i < hamc[m.second].size(); ++i){
        std::cout << hamc[m.second][i] << " ";
    }
    std::cout << std::endl;
}

void MakeEuler(int graphSize)
{
    srand(time(NULL));
    int left = -1, right = -1;
    for(int i = 0; i < graphSize; i++){
        deg[i] = 0;
        for(int j = 0; j < graphSize; j++)
            if(cycles[i][j] < 1000000)
                deg[i]++;
        if(deg[i] & 1){
            if(left == -1){
                left = i;
            } else {
                right = i;
                if(cycles[left][right] == 1000000){
                    int value = (rand() % 99) + 1;
                    cycles[left][right] = value;
                    cycles[right][left] = value;
                } else {
                    cycles[left][right] = cycles[right][left] = 1000000;
                }
                left = -1;
                right = -1;
            }
        }
    }
    std::cout << "New graph\n";
    PrintGraph(cycles, graphSize);
}

void Euler(int graphSize)
{
    std::vector<Edge> edges;
    std::vector<int> connect[1002];
    for(int i = 0 ; i < graphSize; i++){
        for(int j = i + 1; j < graphSize; j++){
            if(cycles[i][j] < 1000000){
                Edge e(i, j, graph[i][j]);
                connect[i].push_back(edges.size());
                connect[j].push_back(edges.size());
                edges.push_back(e);
            }
            tree[i][j] = 1000000;
        }
    }
    std::vector<int> mark(edges.size(), 0);
    std::stack<int> s;
    s.push(edges[0].from);
    s.push(edges[0].to);
    mark[0] = 1;
    while(s.size() > 0){
        int v = s.top();
        for(int i = 0; i < connect[v].size(); i++){
            if(!mark[connect[v][i]]){
                mark[connect[v][i]] = 1;
                Edge e = edges[connect[v][i]];
                if(e.from == v){
                    s.push(e.to);
                } else if(e.to == v){
                    s.push(e.from);
                }
                i = connect[v].size();;
            }
        }
        if(v == s.top()){
            std::cout << v << " ";
            s.pop();
        }
    }
    std::cout << std::endl;
}

void InitializeFlows(int graphSize)
{
    for(int i = 0; i < graphSize; i++) head[i] = -1;
    for(int i = 0; i < graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            if(graph[i][j] < 1000000){
                cap[i][j] = ((rand() % 99) + 1);
                FlowEdge e1(i, j, graph[i][j], cap[i][j], head[i]);
                head[i] = flowedges.size();
                flowedges.push_back(e1);
                FlowEdge e2(j, i, -graph[i][j], 0, head[j]);
                head[j] = flowedges.size();
                flowedges.push_back(e2);
            } else {
                cap[i][j] = 0;
            }
            flows[i][j] = 0;
        }
    }
    std::cout << "Capacities\n";
    PrintGraph(cap, graphSize);
    FindMaxFlow(graphSize);
    for(int i = 0; i < flowedges.size(); i++){
        flowedges[i].flow  = 0;
    }
}

void FindMincostFlow(int graphSize)
{
    int total = 0;
    for(int i = 0; i < graphSize; ++i) prev[i] = -1;
    for(int k = 1; k; k /= 2){
        while(FlowFordBellman(graphSize, k) && k <= flow){
            BuildFlow(graphSize - 1, k);
            for(int i = 0; i < graphSize; ++i) prev[i] = -1;
            total += (k*distances[graphSize - 1]);
            flow -= k;
        }
        for(int i = 0; i < graphSize; ++i) prev[i] = -1;
    }
    for(int i = 0; i < graphSize; ++i){
        for(int j = 0; j < graphSize; ++j){
            flows[i][j] = 0;
        }
    }
    for(int i = 0; i < flowedges.size(); ++i){
        FlowEdge edge = flowedges[i];
        if(edge.capacity > 0){
            flows[edge.from][edge.to] = edge.flow;
        }
    }
    PrintGraph(flows, graphSize);
    std::cout << "Total cost: " << total << std::endl;
}

void FindMaxFlow(int graphSize)
{
    maxflow = 0;
    for(int k = (1 << 10); k; k /= 2){
        while(Flowdfs(graphSize, k, 0)){
            cc++;
            maxflow += k;
        }
        cc++;
    }
    flow = (maxflow*2)/3;
    std::cout << "\nMax flow is " << maxflow;
    std::cout << "\nSearching for a " << flow << " flow\n";
}

bool Flowdfs(int graphSize, int fl, int v)
{
    if(v == graphSize - 1)
        return 1;
    fm[v] = cc;
    for(int i = head[v]; i != -1; i = flowedges[i].next){
        if((flowedges[i].flow + fl <= flowedges[i].capacity)
        && (fm[flowedges[i].to] != cc)
        && (Flowdfs(graphSize, fl, flowedges[i].to))){
            flowedges[i].flow += fl;
            flowedges[i^1].flow -= fl;
            return 1;
        }
    }
    return 0;
}

bool FlowFordBellman(int graphSize, int fl)
{
    for(int i = 1; i < graphSize; i++){
        distances[i] = 1000000;
    }
    distances[0] = 0;
    for(int i = 0; i < graphSize - 1; i++){
        for(int j = 0; j < flowedges.size(); j++){
            FlowEdge edge = flowedges[j];
            if(edge.capacity - edge.flow >= fl){
                if(distances[edge.to] > distances[edge.from] + edge.length){
                    distances[edge.to] = distances[edge.from] + edge.length;
                    prev[edge.to] = edge.from;
                }
            }
        }
    }
    return (distances[graphSize - 1] < 1000000);
}

void BuildFlow(int v, int fl)
{
    for(int i = prev[v]; i != -1; i = prev[i]){
        for(int e = head[i]; e != -1; e = flowedges[e].next){
            FlowEdge edge = flowedges[e];
            if((distances[edge.to] == distances[edge.from] + edge.length) && v == edge.to){
                flowedges[e].flow += fl;
                flowedges[e^1].flow -= fl;
            }
        }
        v = i;
    }
}
