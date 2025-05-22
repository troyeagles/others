//m-coloring 문제
#include <iostream>

//입력 설명
//n: 구역의 개수(500 이하의 자연수)    m: 인접 정보의 개수(자연수)
//인접정보 m개: x, y -> 구역 x, y는 인접해있다. (x, y는 1이상 n이하의 자연수)

/*
4색 정리를 이용해
//(1) 최소한의 색상의 개수(a)와
//(2) 최소한의 색상만을 이용해 구역을 색칠하는 경우의 수(b)
를 구하자

최대 4개의 색을 이용해 색칠하는 경우의 수는 (4Pa)xb 이다
*/

#define MAX 501

using namespace std;

int n, m;
bool con[MAX][MAX]={0}; //연결 정보, con[x][y]: 구역 x, y가 연결되어 있는지
int color[MAX]={0};     //색칠 정보, 모든 색은 1~4 중 하나

int color_limit;
long long cnt=0;

void input()
{
    cin>>n>>m;
    for (int i=0;i<m;i++)
    {
        int x, y;
        cin>>x>>y;
        con[x][y]=con[y][x]=1;
    }
}

bool check(int idx)
{
    //color[idx]!=0 이다
    for(int i=1;i<=n;i++)
    {
        if (i==idx) continue; //자기 자신인 경우는 pass
        if(con[idx][i] && color[idx]==color[i]) return false; //인접하면서 색상이 같다면 false
    }
    
    return true;
}


void dfs(int idx) //idx를 색칠한 상태
{
    if(idx>n) //모든 구역을 조건에 맞게 색칠했다면
    {
        cnt++;
        return;
    }

    for(int i=1;i<=color_limit;i++)
    {
        color[idx]=i;
        if(check(idx)) dfs(idx+1); //가능하다면 그다음 구역을 색칠하기 위해 재귀호출
        color[idx]=0;
    }
}


void solve()
{
    //사용하는 색상 수를 1개에서 4개까지 늘려가며 최소한의 색상을 사용하는 경우를 구한다
    //1~color_limit 의 색상 사용
    for(int i=1;i<=4;i++) //4색 정리
    {
        color_limit=i;
        cnt=0;
        dfs(1);
        
        if(cnt>0) break; //가능하다면 끝내기
    }
}

void output()
{
    cout<<"최소한의 색상의 개수: "<<color_limit<<"\n";
    cout<<"최소한의 색상만을 이용해 모든 구역을 색칠하는 경우의 수: "<<cnt<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    input();
    solve();
    output();

    return 0;
}
