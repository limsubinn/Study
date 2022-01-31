//dijkstra.cpp

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

struct QD {
    int a, b, w, d; // edge, weight, distance
};

class PQ { // priority queue
    public:
        PQ(); // 초기화
        void Insert(QD x);
        QD Delete();
        QD Arr[1000];
        int cnt;
};

PQ::PQ()
{
    cnt = 0;
}

void PQ::Insert(QD x) {
    int i;
    QD temp;
    
    Arr[++cnt] = x;
    i = cnt;
    while (i > 1) {
        if (Arr[i].d < Arr[i/2].d) {
            temp = Arr[i]; Arr[i] = Arr[i/2]; Arr[i/2]=temp;
            i = i/2;
        }
        else
            break;
    }
    return;
}

QD PQ::Delete()
{
    QD ret, temp;
    int i;
    
    ret = Arr[1];
    if (cnt == 1) {
        cnt = 0;
    }
    else {
        Arr[1] = Arr[cnt]; cnt--;
        i = 1;
        while (true) {
            if (cnt >= i*2 + 1) {
                if (Arr[i].d > Arr[i*2].d || Arr[i].d > Arr[i*2+1].d) {
                    if (Arr[i].d < Arr[i*2+1].d) { // 왼쪽이 작은 경우
                        temp = Arr[i]; Arr[i] = Arr[i*2]; Arr[i*2]=temp;
                        i = i*2;
                    }
                    else {
                        temp = Arr[i]; Arr[i] = Arr[i*2+1]; Arr[i*2+1]=temp;
                        i = i*2 + 1;
                    }
                }
                else {
                    break;
                }
            }
            else if (cnt == i*2) { // 오른쪽 자식 노드 없음
                if (Arr[i].d > Arr[i*2].d) {
                    temp = Arr[i]; Arr[i] = Arr[i*2]; Arr[i*2]=temp;
                    i = i*2;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
    }
    return ret;
}

int main()
{
    PQ Q;
    pair <int, int> temp;
    QD t1, t2;
    vector <pair <int, int>> Edge[1000];
    int Mark[1000]; // distance
    int oi;
    int n, m, i, j, s, t, w;
    scanf("%d %d", &n, &m);
    for (i=0; i<m; i++) {
        scanf("%d %d %d", &s, &t, &w);
        temp.first=t; temp.second=w;
        Edge[s].push_back(temp);
        temp.first=s; temp.second=w;
        Edge[t].push_back(temp);
    }
    
    // main algorithm
    for (i=1; i<=n; i++) Mark[i] = 1000000; // 1000000 = infinity
    Mark[1] = 0;
    for (j=0; j<Edge[1].size(); j++) {
        t1.a = 1;
        t1.b = Edge[1][j].first;
        t1.w = Edge[1][j].second;
        t1.d = Mark[1] + Edge[1][j].second;
        Q.Insert(t1);
    }
    oi = 1;
    
    while (oi < n) {
        t1 = Q.Delete(); // a b w d
        if (Mark[t1.b] == 1000000) {
            oi++;
            Mark[t1.b] = t1.d;
            for (j=0; j<Edge[t1.b].size(); j++) {
                t2.a = t1.b;
                t2.b = Edge[t1.b][j].first;
                t2.w = Edge[t1.b][j].second;
                t2.d = Mark[t1.b] + Edge[t1.b][j].second;
                Q.Insert(t2);
            }
        }
    }
    for (i=1; i<=n; i++) printf("%d ", Mark[i]);
    printf("\n");
    return 0;
}
