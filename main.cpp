/*图的抽象数据类型*/

#include <iostream>

using namespace std;

#include <stack>

#include <queue>

const int MaxLen=20;

/*节点数组结合边链表形式的图*/
struct Edge {
    char adjvex;
    Edge *next;

    Edge() : adjvex(0), next(nullptr) {}
};

struct Vertex {
    char info;
    Edge *firstEdge;

    Vertex() : info(0), firstEdge(nullptr) {}
};

class ListGraph {
    Vertex *vertex;
    int vertexNum, edgeNum;
public:
    ListGraph() : vertex(nullptr), vertexNum(0), edgeNum(0) {};

    void initial();

    void showGraph();
};

void ListGraph::initial() {
    cin >> vertexNum >> edgeNum;
    vertex = new Vertex[vertexNum];
    /*节点赋值*/
    for (int i = 0; i < vertexNum; ++i) {
        cin >> vertex[i].info;
    }
    /*边赋值*/
    char head, tail;
    for (int j = 0; j < edgeNum; ++j) {
        cin >> head >> tail;
        Edge *e = new Edge;
        for (int i = 0; i < vertexNum; ++i) {
            if (vertex[i].info == tail) {
                e->adjvex = i;
            }
        }
        for (int k = 0; k < vertexNum; ++k) {
            if (vertex[k].info == head) {
                e->next = vertex[k].firstEdge;
                vertex[k].firstEdge = e;
            }
        }

    }

}

/*以’0 A-1-3-4-^‘呈现链表*/
void ListGraph::showGraph() {
    for (int i = 0; i < vertexNum; ++i) {
        cout << i << ' ' << vertex[i].info << '-';
        Edge *p = vertex[i].firstEdge;
        stack<int> t;
        while (p) {
            t.push(p->adjvex);
            p = p->next;
        }
        while (!t.empty()) {
            cout << t.top() << '-';
            t.pop();
        }
        cout << '^' << endl;
    }
}

/*邻接矩阵存储的图，存储数据类型为string类*/
class ArrayGraph {
    bool visited[MaxLen];
    string *data;
    int vNum;
    int eNum;
    int **vMatrix;
    char type;/*D--directed, U--undirected*/
    void DFS(int v);
    void BFS(int i);
public:
    ArrayGraph() : data(nullptr), vNum(0), eNum(0), vMatrix(nullptr), type('U'){};

    void initialByEdges();

    void showMatrix();
    void showVertix();

    void showDegree();

    void DFSTraverse();
    void BFSTraverse();

    void initialByMatrix();
    void connectedComponentNum();
};
void ArrayGraph::DFSTraverse() {
    for (bool & i : visited) {
        i=false;
    }
    for (int j = 0; j < vNum; ++j) {
        if(!visited[j])
        {
            DFS(j);
        }
    }
    cout<<endl;
}
void ArrayGraph::BFSTraverse() {
    for (int i = 0; i < vNum; ++i) {
        visited[i]=false;
    }
    BFS(0);
    cout<<endl;
}

/*先输入节点，再输入边的两个节点*/
void ArrayGraph::initialByEdges() {
    string s;
//    cin >> type;
    cin >> vNum;
    data = new string[vNum];
    vMatrix = new int *[vNum];
    /*初始化节点*/
    for (int i = 0; i < vNum; ++i) {
        cin >> data[i];
        vMatrix[i] = new int[vNum];
    }
    /*必须记得对矩阵进行初始化*/
    for (int l = 0; l < vNum; ++l) {
        for (int i = 0; i < vNum; ++i) {
            vMatrix[l][i]=0;
        }
    }
    cin >> eNum;
    string head, tail;
    /*初始化边*/
    for (int j = 0; j < eNum; ++j) {
        cin >> head >> tail;
        for (int i = 0; i < vNum; ++i) {
            for (int k = 0; k < vNum; ++k) {
                if (head == data[i] && tail == data[k]) {
                    vMatrix[i][k] = 1;
                    if (type == 'U') {
                        vMatrix[k][i] = 1;
                    }
                }
            }
        }
    }
}

void ArrayGraph::showMatrix() {
    for (int i = 0; i < vNum; ++i) {
        for (int j = 0; j < vNum; ++j) {
            cout << vMatrix[i][j];
            if(j!=vNum-1)
            {
                cout<< ' ';
            }
        }
        cout << endl;
    }
}
void ArrayGraph::showVertix() {
    for (int i = 0; i < vNum; ++i) {
        cout<<data[i];
        if(i!=vNum-1)
        {
            cout<<' ';
        }
    }
    cout<<endl;
}
void ArrayGraph::showDegree() {
    if (type == 'D') {
        int *inDegree = new int[vNum];
        int *outDegree = new int[vNum];
        for (int k = 0; k < vNum; ++k) {
            outDegree[k] = 0;
            inDegree[k] = 0;
        }
        for (int i = 0; i < vNum; ++i) {
            for (int j = 0; j < vNum; ++j) {
                if (vMatrix[i][j] == 1) {
                    outDegree[i]++;
                    inDegree[j]++;
                }
            }
        }
        for (int l = 0; l < vNum; ++l) {
            if (outDegree[l] + inDegree[l] != 0) {
                cout << data[l] << ": " << outDegree[l] << ' ' << inDegree[l] << " " << inDegree[l] + outDegree[l]
                     << endl;
            } else { cout << data[l] << endl; }
        }
    } else if (type == 'U') {
        int *degree = new int[vNum];
        for (int k = 0; k < vNum; ++k) {
            degree[k] = 0;
        }
        for (int i = 0; i < vNum; ++i) {
            for (int j = i; j < vNum; ++j) {
                if (vMatrix[i][j] == 1) {
                    degree[i]++;
                    degree[j]++;
                }
            }
        }
        for (int l = 0; l < vNum; ++l) {
            if (degree[l] != 0) {
                cout << data[l] << ": " << degree[l] << endl;
            } else { cout << data[l] << endl; }
        }
    }
}

void ArrayGraph::initialByMatrix() {
    cin>>vNum;
    for (int i = 0; i < vNum; ++i) {
        for (int j = 0; j < vNum; ++j) {
            cin>>vMatrix[i][j];
        }
    }
}

void ArrayGraph::DFS(int v) {
    cout<<v<<' ';
    for (int i = 0; i < vNum; ++i) {
        if(vMatrix[v][i]==1 && !visited[i])
        {
            DFS(i);
        }
    }
}
void ArrayGraph::BFS(int i) {
    queue<int> numQ;
    visited[i]=true;
//    cout<<i<<' ';
    numQ.push(i);
    while (!numQ.empty())
    {
        int t=numQ.front();
        numQ.pop();
        for (int j = 0; j < vNum; ++j) {
            if(vMatrix[t][j]==1 &&!visited[j])
            {
                visited[j]= true;
//                cout<<j<<' ';
                numQ.push(j);
            }
        }
    }
}
void ArrayGraph::connectedComponentNum() {
    int count=0;
    for (int i = 0; i < vNum; ++i) {
        visited[i]= false;
    }

    for (int j = 0; j < vNum; ++j) {
        if(!visited[j])
        {
            BFS(j);
            count++;
        }
    }
    cout<<count<<endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        ArrayGraph arrayGraph;
        arrayGraph.initialByEdges();
        arrayGraph.showVertix();
        arrayGraph.showMatrix();
        arrayGraph.connectedComponentNum();
        if(t!=0)
        {
            cout<<endl;
        }
    }
    return 0;
}