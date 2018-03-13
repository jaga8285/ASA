#include <iostream>
#include <ctime>

using namespace std; 


class vertex{
    private:
        int id;
        int d;
        int low;
        struct node{
            vertex* data;
            node* next;
            node(vertex v):next(NULL){}
        };
        node* adj;
    public:
        vertex(int idInicial):id(idInicial),d(0),low(0),adj(NULL){};
        void reset(){
            d=0;
            low=0;
        }
        int getId(){
            return id;
        }
        int getD(){
            return d;
        }
        int getLow(){
            return low;
        }
        node* getAdj(){
            return adj;
        }
        void addAdj(vertex v){
            if(adj =NULL){
                v
            }
            node* n;
            for(n=adj;n->next=!=NULL;n=n->next){}
            n=new node(v);
        }
        friend std::ostream &operator<<(std::ostream &os, const vertex &vertex) {
            cout << vertex.adj <<endl;
            os << " Vertice com id: " << vertex.id << " tem conexoes com ";
    
            for(node* n = vertex.adj; n!=NULL; n=n->next){
                cout<< n->data->getId();
                os << n->data->getId() << " ";
            }
            return os;
        }

};



int main(){
    int N,M,i;
    scanf("%d\n%d",&N,&M);
    vertex *vertices = (vertex *) malloc(sizeof(vertex)*N);
    for(i=0; i<N; i++){
        vertices[i] = vertex(i+1);
    }
    for(i = 0; i<M; i++){
        int id1, id2;
        scanf("%d %d",&id1,&id2);
        vertices[id1].addAdj(vertices[id2]);
    }
    cout << vertices[0];
    return 0;
}