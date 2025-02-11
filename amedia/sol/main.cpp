#include <fstream>
using namespace std;
ifstream cin("amedia.in");
ofstream cout("amedia.out");
int main()
{
    int n; cin >> n;
    if(n % 9 == 0) cout << n / 9;
    else cout << n / 9 + 1;
    return 0;
}
