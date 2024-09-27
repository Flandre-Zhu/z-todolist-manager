#include "lib.cpp"

class task
{
public:
	int id,pri; string name,info;
	double ddl; bool done;
	void default_set(){id=0;pri=1;ddl=1e9;done=0;name="noname";info="";}
	task() {default_set();}
	void modify(string s)
	{
		string t="";
		F(i,0,sz(s)-1)
		{
			if(s[i]=='{' or s[i]=='}' or s[i]==',') continue;
			if(s.substr(i,2)=="id") {i+=3; sscanf(s.c_str()+i,"%d",&id); while(isdigit(s[i]))++i;}
			if(s.substr(i,4)=="name") {i+=5; ++i; t=""; while(s[i]!='\"') t+=s[i++]; ++i; name=t;}
			if(s.substr(i,4)=="info") {i+=5; ++i; t=""; while(s[i]!='\"') t+=s[i++]; ++i; info=t;}
			if(s.substr(i,3)=="ddl") {i+=4; sscanf(s.c_str()+i,"%lf",&ddl); while(isdigit(s[i]) or s[i]=='.')++i;}
			if(s.substr(i,3)=="pri") {i+=4; sscanf(s.c_str()+i,"%d",&pri); while(isdigit(s[i]))++i;}
			if(s.substr(i,4)=="done") {i+=5; done=(s[i]=='t'); ++i;}
		}
	}
	task(string s) {default_set();modify(s);}
	void print_long()
	{
		printf("id: %d\n",id);
		printf("name: %s\n",name.c_str());
		printf("info: %s\n",info.c_str());
		printf("ddl: %s\n",ddl_string(ddl).c_str());
		printf("priority: %d\n",pri);
		printf("done: %s\n",(done)?"YES":"NO");
		puts("=======================================================");
	}
	void print(bool show_info=0)
	{
		table_head();
		if(sz(name)<=20) printf("%s",name.c_str()),space(25-sz(name));
		else F(i,0,19) putchar(name[i]);
		printf("%3d",id); space(2);
		printf("%2d",pri); space(4);
		string sddl=ddl_string(ddl);
		printf("%s",sddl.c_str()); space(18-sz(sddl));
		printf("%s\n",(done)?"YES":"NO");
		F(i,20,sz(name)-1) {putchar(name[i]); if((i+1)%20==0 or i==sz(name)-1) puts("");}
		puts("");
		if(show_info) printf("info: %s\n",info.c_str());
	}
}t[10000];
int n=0;
bool cmp_ddl(task a,task b){return a.ddl<b.ddl || (fabs(a.ddl-b.ddl)<1e-5 && a.pri>b.pri);}
bool cmp_pri(task a,task b){return a.pri>b.pri;}
bool cmp_id(task a,task b){return a.id<b.id;}
