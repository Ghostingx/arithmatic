void prim(MGraph g, int v0, float &sum) {
    float lowcost[maxSize], vset[maxSize]; /*lowcost[maxSize]用于存储当前生成树到剩余各顶点最短边的权值，
    vset[maxSize]用于判断顶点是否并入生成树，vset[i]=1表示并入*/
    int i, j, k,v ;
    float min;
    v = v0;
    for (i = 0; i < g.n; ++i) {//lowcost存入v0到各顶点的权值，vset初始化
        lowcost[i] = g.edges[v0][i];
        vset[i] = 0;
    }
    vset[v0] = 1;//顶点v0并入树中
    sum = 0;     
    for (i = 0; i < g.n - 1; ++i)//访问剩余的n-1个顶点。以下注释是此循环第一趟的注释，其他的类似
    {
        min = INF;
        for(j=0;j<g.n;++j)//找到与v0相连的权值中的最小值
            if (vset[j] == 0 && lowcost[j] < min)
            {
                min = lowcost[j];
                k = j;
            }
        vset[k] = 1;//将顶点v并入树
        v = k;
        sum = sum + min;//sum记录最小生成树的权值

        //更新刚并入树的顶点v到剩余各顶点最短边的权值,与v0相比较
        for (j = 0; j < g.n; ++j)
            if (vset[j] == 0 && g.edges[v][j] < lowcost[j])
                lowcost[j] = g.edges[v][j];
    }
}
