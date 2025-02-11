#include <fstream>
using namespace std;
ifstream cin("arondat.in");
ofstream cout("arondat.out");
bool isPrime(int x)
{
    if(x<2) return false;
    if(x==2||x==3) return true;
    if(x%2==0||x%3==0) return false;
    for(int i = 5;i*i<=x;i+=6)
        if(x%i==0||x%(i+2)==0) return false;
    return true;
}
int sumaDivProp(int x)
{
    for(int i = 2;i*i<=x;i++)
        if(x % i == 0)
            return i + x/i;
}
int main()
{
    int n;
    cin >> n;
    while(!isPrime(n))
        n = sumaDivProp(n);
    cout << n;
    return 0;
}
