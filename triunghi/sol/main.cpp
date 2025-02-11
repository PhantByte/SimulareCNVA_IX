#include <fstream>
using namespace std;
ifstream cin("triunghi.in");
ofstream cout("triunghi.out");
const int mxN = 4e6;
int ciur[mxN+1];
void build_ciur()
{
    ciur[0] = ciur[1] = 1;
    for(int i = 4;i<=mxN;i+=2)
        ciur[i] = 1;
    for(int i = 3;i*i<=mxN;i+=2)
        if(ciur[i] == 0)
            for(int j = i*i;j<=mxN;j+=2*i)
                ciur[j] = 1;
}
int main()
{
    int cerinta;
    cin>>cerinta;
    if(cerinta==1)
    {
        int n ; cin>>n;
        cout<<1LL*n*(n+1)*(2*n+1)/6;
    }
    if(cerinta==2)
    {
        int n; cin>>n;
        int st = 1, dr = 2001, mid, sol1 = 0;
        while(st<=dr)
        {
            mid = (st + dr) / 2;
            if(mid*(mid+1)*(2*mid+1) / 6 < n)
                st = mid+1, sol1 = mid; 
            else dr = mid-1;
        }
        cout<<sol1+1<<' ';
        ///sol1 = cate zile complete sunt inainte.
        n -= (sol1*(sol1+1)*(2*sol1+1)/6); 
        ///Acum ramane de aflat pe ce nivel se afla n in ziua respectiva.
        
        st = 1, dr = 2001; int sol2 = 0;
        while(st<=dr)
        {
            mid = (st+dr)/2;
            if(mid*mid<n)
                st = mid+1, sol2 = mid;
            else dr = mid-1;
        }
        
        cout<<sol2+1;
    }
    if(cerinta==3)
    {
        int n ; cin>>n;
        build_ciur();
        
        for(int i = 2;i<=mxN;i++)
            ciur[i]+=ciur[i-1];
    
        int sol = 0;
        for(int i = 1;i<=n;i++)
            sol+= i*i - ciur[i*i];
        cout<<sol<<'\n';
    }
    return 0;
}