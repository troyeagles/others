//a(n): n을 3이상의 홀수들의 합으로 표현하는 방법의 수 점화식 구하기
/*

//a(n)=a(n-3)+a(n-5)+a(n-7) ..... (정의에 의해 확인됨)
//a(n)=a(n-2)+a(n-3) 의
결과가 동일할 것인가?

->  a(1)~a(MAX) 까지 출력하며 동일하지 않은 수(mismatch) 값을 맨 마지막에 출력한다.
*/

#include <iostream>
#include <vector>
#include <cmath>

#define ll long long

using namespace std;

int MAX=20;          //limit variable
int output_width=3;  //output option variable

vector<ll> v1, v2;


ll func_1(int x)  //a(n)=a(n-3)+a(n-5)+a(n-7) .....
{
    ll rtn=0;
    
    for(int i=x-3;i>=0;i-=2) rtn+=v1[i];
    
    return rtn;
}


ll func_2(int x)  //a(n)=a(n-2)+a(n-3)
{
    return v2[x-2]+v2[x-3];
}


void solve()
{
    //초기값 설정
    v1[0]=1;
    v2[0]=1;
    v1[1]=0;
    v2[1]=0;
    v1[2]=0;
    v2[2]=0;
    
    
    //a(n)=a(n-3)+a(n-5)+a(n-7) .....
    for(int i=3;i<=MAX;i++) v1[i]=func_1(i);
    
    
    //a(n)=a(n-2)+a(n-3)
    for(int i=3;i<=MAX;i++) v2[i]=func_2(i);
}


void output()
{
    int take_output_width=log(MAX);
    
    int mismatch=0; //불일치할 경우
    
    //출력
    for(int i=1;i<=MAX;i++)
    {
        cout<<"#";
        cout.width(take_output_width);
        cout<<left<<i<<": ";
        
        cout.width(output_width);
        cout<<left<<v1[i];
        cout<<left<<v2[i];
        
        if(v1[i]!=v2[i])
        {
            cout<<"  **mismatch**  ";
            mismatch++;
        }
        
        cout<<"\n";
    }
    
    cout<<"----------------------------------\n";
    cout<<"finsihed successfully. mismatch: "<<mismatch;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    
    v1.resize(MAX+1);
    v2.resize(MAX+1);
    
    solve();
    
    output();

    return 0;
}
