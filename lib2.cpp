#include "task_class.cpp"

void get_data(string path)
{
	ifstream in(path);
	if(!in) {puts("fuck! failed loading file!"); exit(0);}
	string s; getline(in,s);
	// s: {...};{...}; 保证最后有一个分号
	bool in_quote=0; n=0;
	string cur="";
	F(i,0,sz(s)-1)
	{
		if(s[i]=='\"') in_quote^=1;
		if(!in_quote && s[i]==';')
		{
			t[++n]=task(cur);
			cur=""; ++i;
		}
		cur+=s[i];
	}
}
void write_file(string path)
{
	FILE* f=fopen(path.c_str(),"w");
	F(i,1,n)
	{
		task T=t[i];
		fprintf(f,"{id:%d,name:\"%s\",info:\"%s\",ddl:%.4lf,pri:%d,done:%c};",T.id,T.name.c_str(),T.info.c_str(),T.ddl,T.pri,"ft"[T.done]);	
	}
}

void write_user(bool show_done,bool show_info) {
	int cnt=0;
	F(i,1,n) {
		if(!t[i].done || (t[i].done && show_done)) ++cnt;
	}
	printf("%d tasks:\n",cnt);
	F(i,1,n) {
		if(!t[i].done || (t[i].done && show_done)) t[i].print(show_info);
	}
}
