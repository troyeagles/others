//치킨 맥너겟 정리

/* 서로소인 자연수 m, n에 대해 am+bn (a, b는 음이아닌 정수) 꼴로 나타낼 수 없는 수의
최댓값은 mn-m-n 이며, 나타낼 수 없는 수의 개수는 (m-1)(n-1)/2 이다.

-> 나타낼 수 없는 수의 최댓값이 mn-m-n임은 아닌 상태에서 나타낼 수 없는 수의 개수를 구한다.
*/


#include <iostream>
#include <vector>

using namespace std;

vector<bool> pos;

int gcd(int a, int b)
{
    if(a%b==0) return b;
    else return gcd(b, a%b);
}

int main()
{
    int m, n;
    cin>>m>>n;
    
    if(gcd(m, n)!=1) return 1; //서로소가 아니면 return 1
    
    int M=(m*n)-m-n;
    
    pos.assign(M+1, 0);
    
    for(int a=0;a*m<M;a++)
    {
        for(int b=0;(a*m)+(b*n)<M;b++)
        {
            int k=(a*m)+(b*n);
            pos[k]=1;
        }
    }
    
    int pos_cnt=0;
    
    //개별 출력
    for(int i=1;i<=M;i++)
    {
        cout<<i<<": ";
        if(pos[i])
        {
            cout<<"O";
            pos_cnt++;
        }
        else cout<<"X";
        cout<<"\n";
    }
    
    cout<<"\n---------------\n";
    cout<<"possible: "<<pos_cnt<<"\n"; //가능한 개수
    cout<<"impossible: "<<M-pos_cnt; //불가능한 개수

    return 0;
}
