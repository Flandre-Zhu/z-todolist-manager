#include<bits/stdc++.h>
using namespace std;
#define F(i,l,r) for(int i=(l);i<=(r);++i)
#define D(i,r,l) for(int i=(r);i>=(l);--i)
#define MEM(x,a) memset(x,a,sizeof(x))
int I(){int x=0,f=0;char c=getchar(); while(!isdigit(c))f=(c=='-'),c=getchar(); while(isdigit(c))x=x*10+c-'0',c=getchar(); return f?-x:x;}
#define vi vector<int>
#define eb emplace_back
#define sz(x) ((int)x.size())
#define al(x) x.begin(),x.end()
#define pii pair<int,int>
#define fi first
#define se second
#define lwrb lower_bound
#define uprb upper_bound

double getnowtime()
{
    time_t currentTime = std::time(nullptr); // 获取当前时间戳
    tm* localTime = std::localtime(&currentTime); // 转换为本地时间
    // 格式化输出到年月日 时:分
    int y=localTime->tm_year;y%=100;
    int M=localTime->tm_mon+1;
    int d=localTime->tm_mday;
    int h=localTime->tm_hour;
    int m=localTime->tm_min;
    return (y*10000+M*100+d+0.01*h+0.0001*m);
}

string ddl_string(double ddl)
{
	if(ddl>1e7) return "none";
	char tmp[100];MEM(tmp,0); int p=0;
	tmp[p++]='2'; tmp[p++]='0';
	char s[20];MEM(s,0); sprintf(s,"%.4lf",ddl); // s: "xxxxxx.xxxx"
	char sep[10]=".. : "; 
	F(i,0,5){tmp[p++]=s[i];if(i&1)(tmp[p++])=(sep[i>>1]);}
	F(i,7,10){tmp[p++]=s[i];if(!(i&1))(tmp[p++])=(sep[(i-1)>>1]);}
	return string(tmp);
	// format: 20xx.xx.xx xx:xx
}

void space(int n) {F(i,1,n) putchar(' ');}
void table_head()
{
	printf("name"); space(21);
	printf(" id"); space(2);
	printf("pri"); space(3);
	printf("ddl"); space(15);
	printf("done\n");
}
