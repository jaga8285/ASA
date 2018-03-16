#include <iostream>
#include <ctime>
#include <stack>
#include <vector>
#include <cstdlib>

using namespace std; 

struct edge{
    int id1, id2;
};

int visited=0;//pode ser substituido por static
void Tarjan_Visit(int currentVertex, edge *edges, int *d, int *low, bool *isVertexInStack, 
                    stack<int> *stack, int *edgeIndex, int *SCC){
    int index = edgeIndex[currentVertex];
    int adjacentVertex;
    d[currentVertex] = visited;
    low[currentVertex] = visited++;
    stack -> push(currentVertex);
    isVertexInStack[currentVertex] = true;
    while ((edges[index].id1-1) == currentVertex){
        adjacentVertex = edges[index].id2-1;
        //cout << "[DEBUG]" << "v =" << currentVertex << " adj= "<<adjacentVertex<<endl;
        if (d[adjacentVertex] == -1 || isVertexInStack[adjacentVertex]){
            //cout<<"hi"<<endl;
            if (d[adjacentVertex] == -1){
                //cout << "there"<<endl;
                Tarjan_Visit(adjacentVertex,edges, d, low, isVertexInStack, stack, edgeIndex, SCC);
            }
            low[currentVertex] = min(low[currentVertex],low[adjacentVertex]);
        }
        index++;
    }
    vector<int> currentSCC;
    int SCCid=-1;
    //cout<<"[DEBUG]V= "<<currentVertex<<" d= "<< d[currentVertex] << " low= "<< low[currentVertex]<< endl;
    if (d[currentVertex] == low[currentVertex]){
        do{
            adjacentVertex = stack -> top();
            currentSCC.push_back(stack -> top());
            if (SCCid==-1 || adjacentVertex < SCCid) SCCid = adjacentVertex;
            //cout << "[DEBUG]" << adjacentVertex<<endl;
            //foundSCC->push_back(adjacentVertex);
            stack -> pop();
            isVertexInStack[adjacentVertex]=false;
        }while(currentVertex != adjacentVertex);
        //SCCindex->push_back(foundSCC->size());
        for(auto iterator = currentSCC.begin(); iterator != currentSCC.end(); iterator++){
            SCC[*iterator]=SCCid;
        }
    }
    //cout<<"[DEBUG]stop"<<endl;
}
int main(){
    int N,M,i;
    scanf("%d\n%d",&N,&M);
    if (N<2){
        cerr<<"Argumento invalido: N menor que 2"<<endl;
        return 1;
    }
    if (M<1){
        cerr<<"Argumento invalido: M menor que 1"<<endl;
        return 1;
    }
    /*
    vector<int> *foundSCC = new vector<int>;
    vector<int> *SCCindex = new vector<int>;
    SCCindex->push_back(0);*/
    vector<edge> SCCedges;
    int d[N], low[N], SCC[N];
    stack<int> *Stack= new stack<int>();
    bool isVertexInStack[N];
    edge *edges = (edge *) malloc(sizeof(edge)*M) ;
    int edgeIndex[N];
    for(i=0; i<N; i++){
        isVertexInStack[i]=false;
        d[i]=-1;
        edgeIndex[i]=-1;
    }
    for(i = 0; i<M; i++){
        edge e;
        scanf("%d %d",&e.id1,&e.id2);
        edges[i]=e;
    }
    qsort(edges, M, sizeof(edge),[](const void* a, const void* b){
        if (((edge*)a)->id1==((edge*)b)->id1){
            return ((edge*)a)->id2 - ((edge*)b)->id2;
        }
        return ((edge*)a)->id1 - ((edge*)b)->id1;
    });

    for(int currentVertex=edges[0].id1,i=0; i<M; i++){
        if (edges[i].id1==currentVertex){
            edgeIndex[currentVertex-1]=i;
            currentVertex++;//doesnt work if there are gaps
        }
    }

    for(i=0;i<N;i++){
        if (d[i]==-1)
            Tarjan_Visit(i,edges, d, low, isVertexInStack, Stack, edgeIndex, SCC);
    }
    //SCCindex->pop_back();

   /* for(i=0; i<M; i++){
        cout << edges[i].id1  << " " << edges[i].id2 <<endl;
    }*/
    for(i=0; i<M; i++){
        edges[i].id1=SCC[edges[i].id1-1]+1;
        edges[i].id2=SCC[edges[i].id2-1]+1;
        if(edges[i].id1 != edges[i].id2 && (SCCedges.empty() || edges[i].id1 != SCCedges.back().id1 && edges[i].id2 != SCCedges.back().id2)){
            SCCedges.push_back(edges[i]);
        }
    }

/*
    for(i=0;i<N;i++){
        cout<<i +1 << " " << SCC[i]+1<<endl;
    }
  */  
    cout<<endl<<SCCedges.size()<<endl;
    for(i=0; i<SCCedges.size(); i++){
        cout << SCCedges[i].id1 << " " << SCCedges[i].id2 <<endl;
    }/* 
    for(i=0;i<N;i++){
        cout << i+1 << " -> " << edgeIndex[i] << endl;
    }*/

    
    return 0;
}