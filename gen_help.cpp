#include "lib2.cpp"

int main()
{
	string s;
	ifstream in("./help.txt");
	while(getline(in,s))
	{
		F(i,0,sz(s)-1) {
			if(s[i]=='\"') putchar('\\');
			putchar(s[i]);
		}
		putchar('\\'); putchar('n');
	}
}
