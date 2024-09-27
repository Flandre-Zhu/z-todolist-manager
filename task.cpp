#include "lib2.cpp"

#define DATA_PATH "/home/z/task_data"

bool del[10000];
void print_help()
{
	puts("帮助文档\n\n[关于数据存档文件]\n位置: ~/task_data\n格式: {id:x,name:\"xx\",info:\"xx\",ddl:xx.xx,pri:xx,done:xx};\n- ddl为小数形式，例如 2024年9月30日下午2:30截止，ddl写作 240930.1430，用24小时制\n- ddl 为 1e9 时，表示这个没有 ddl，显示时会显示 \"none\"\n- done 用 t/f 表示是否已完成，显示时会显示 yes/no，pri 可以任意指定一个 1~99 内的数，\n- name和info必须有分号，否则报错\n- 存档文件中，这是自动生成的，和用户写的格式是一样的\n- 新建或修改任务时，每一项都不是必要的，没有填写的项会被设置为默认值\n- 默认值: {id:自动分配,name:\"noname\",info:\"\",ddl:1e9,pri:1,done:f}\n\n[关于用法]\n\ntask 或 task --help - 显示本帮助界面\ntask add - 新建任务，输入该命令后，用上述格式输入任务的信息\ntask modify [id] - 修改任务信息，同样需要输入命令后再输入\ntask count - 查看有多少任务\ntask list - 查看所有任务，不显示已完成的，默认不显示 info\n	task list [id] - 查看编号为id的任务\n	task list all  - 也显示已完成的，all 可简写为 a\n	task list detail - 显示info，可简写为d\n	task list sort ddl/pri - 按照ddl或pri排序显示\n	这些参数可以同时使用，不冲突\ntask next - 查看最近的还没完成的任务，可以加上detail参数显示info，加上all参数没用\ntask today - 查看今天的任务，按优先级从高到低输出，不显示已完成，可以加上all/detail参数\n	task today [date] - 指定日期date（格式同上），查看date这天的任务\ntask copy [id] - 将编号为id的任务做一个副本\ntask find [str] - 查找name或info中包含str子串的，可以加detail，加all没用\ntask remove [id1 id2 id3...] - 将编号为id1,id2,id3...的任务删除，可以写很多个id，remove可以简写为rm\n");
}
void process(int argc,char** argv)
{
	bool show_done=0,show_info=0;
	F(i,2,argc-1) 
	{
		if(!strcmp(argv[i],"a") || !strcmp(argv[i],"all")) show_done=1;
		if(!strcmp(argv[i],"d") || !strcmp(argv[i],"detail")) show_info=1;
	}

	if(argc==1) print_help();
	if(argc==2 && !strcmp(argv[1],"--help")) print_help();
	if(argc==2 && !strcmp(argv[1],"add"))
	{
		puts("enter task:");
		puts("format: {id:x,name:\"xx\",info:\"xx\",ddl:xx.xx,pri:xx,done:xx};");
		string s; getline(cin,s);
		t[++n]=task(s); t[n].id=n;
	}
	if(argc>=2 && !strcmp(argv[1],"modify"))
	{
		int id; sscanf(argv[2],"%d",&id);
		t[id].print();
		puts("enter modification:");
		puts("format: {id:x,name:\"xx\",info:\"xx\",ddl:xx.xx,pri:xx,done:xx};");
		string s; getline(cin,s);
		t[id].modify(s);
	}
	if(argc>=2 && !strcmp(argv[1],"list"))
	{
		F(i,2,argc-1)if(!strcmp(argv[i],"sort"))
		{
			if(!strcmp(argv[i+1],"ddl")) stable_sort(t+1,t+n+1,cmp_ddl);
			if(!strcmp(argv[i+1],"pri")) stable_sort(t+1,t+n+1,cmp_pri);
		}
		if(argc>=3 && isdigit(argv[2][0]))
		{
			int id; sscanf(argv[2],"%d",&id);
			t[id].print();
		}
		else write_user(show_done,show_info);
		sort(t+1,t+n+1,cmp_id);
	}
	if(argc==2 && !strcmp(argv[1],"next"))
	{
		double ti=getnowtime();
		stable_sort(t+1,t+n+1,cmp_ddl);
		F(i,1,n) if(t[i].ddl>ti+(1e-5) && !t[i].done) {t[i].print(show_info); break;}
		stable_sort(t+1,t+n+1,cmp_id);
	}
	if(argc>=2 && !strcmp(argv[1],"today"))
	{
		int ti=(int)getnowtime();
		if(argc>=3) sscanf(argv[2],"%d",&ti);
		stable_sort(t+1,t+n+1,cmp_pri);
		int cnt=0;
		F(i,1,n) if((int)t[i].ddl==ti && !(!show_done && t[i].done)) {++cnt;}
		printf("%d tasks:\n",cnt);
		F(i,1,n) if((int)t[i].ddl==ti && !(!show_done && t[i].done)) {t[i].print(show_info);}
		stable_sort(t+1,t+n+1,cmp_id);
	}
	if(argc>=2 && !strcmp(argv[1],"copy"))
	{
		int id; sscanf(argv[2],"%d",&id);
		t[++n]=t[id]; t[n].id=n;
	}
	if(argc>=2 && !strcmp(argv[1],"find"))
	{
		string s;
		if(argc>=3) s=argv[2];
		else getline(cin,s);
		F(i,1,n)if(t[i].name.find(s)!=string::npos || t[i].info.find(s)!=string::npos) t[i].print();
	}
	if(argc==2 && !strcmp(argv[1],"count"))
	{
		printf("tasks count: %d\n",n);
	}
	if(argc>=2 && (!strcmp(argv[1],"rm") || !strcmp(argv[1],"remove")))
	{
		MEM(del,0);
		F(i,2,argc-1)
		{
			int id; sscanf(argv[i],"%d",&id);
			t[id]=task(); del[id]=1;
		}
		int m=0; F(i,1,n)if(!del[i]) t[++m]=t[i],t[m].id=m;
		F(i,m+1,n) t[i]=task(); n=m;
	}
}
void flandre(int argc,char**argv)
{
	get_data(DATA_PATH);

	process(argc, argv);

	write_file(DATA_PATH);
}
#undef int
int main(int argc,char**argv)
{
	flandre(argc,argv);
	return 0;
}

