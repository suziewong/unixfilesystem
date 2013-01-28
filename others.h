/*
	判断是否是用户？并且返回用户的编号
*/
int isUser(string username)
{
	fseek(fp,0,SEEK_SET);
	fread(files,sizeof(Fnode),1,fp);
	Fnode *f_system = (Fnode *)files;
	
	int user_num = f_system->usersnum;

	//User *user =(User *)files;
	
	//cout<<user->username<<endl;
	for(int i =0; i<user_num;i++)
	{
		fseek(fp,512*68+64*i,SEEK_SET);
		fread(files,sizeof(User),1,fp);
		User *user =(User *)files;
		if(user->username == username)
		{
			return user->user_id;
		}
	}
	return -1;
}
/*
	判断是否是组？并且返回组的编号
*/
int isGroup(string groupname)
{
	fseek(fp,512+64*7,SEEK_SET);
	fread(inodeblock,sizeof(Inode),1,fp);
	Inode *inode = (Inode *)inodeblock;
	
	int group_num = inode->ds;

	for(int i =0; i<group_num;i++)
	{
		fseek(fp,512*72+16*i,SEEK_SET);
		fread(files,sizeof(Group),1,fp);
		Group *group =(Group *)files;
		if(group->groupname == groupname)
		{
			return group->group_id;
		}
	}
	return -1;
}



/*
	将time_t转化为正常“的时间
*/
void get_time(time_t t) 
{
	char day[3],mon[3];
	int date,hour,min,second,year;
	//time_t t;
   time(&t);
//	b = time(0);
//	cout<<ctime(&b);
//		printf("sizeof(time_t) = %d\n", sizeof(time_t));
 // printf("Today's date and time: %s\n", ctime(&t));
//	printf("Today's date and time: %s\n", ctime(&b));
//	printf("sizeof(time_t) = %d\n", sizeof(time_t));
    sscanf(ctime(&t),"%s %s %i %i:%i:%i %i",&day,&mon,&date,&hour,&min,&second,&year );
    printf("             %s %i %i %i:%i",mon,date,year,hour,min);
 //  printf("The day of today is:%s\n",day);
 //   printf("Now the time is: %i:%i\n",hour,min);
 //   getchar();
}
/*
	设置文件屏蔽码
*/
void umask(string umaskcode="022")
{
	
	map<string,string> umaskmap;

	umaskmap["002"]="rwxrwxr-x";
	umaskmap["022"]="rwxr-xr-x";
	umaskmap["037"]="rwx-wx---";
	umaskmap["077"]="rwx------";
	umaskmap["000"]="rwxrwxrwx";
	string umask="rwxr-xr-x";
	if(umaskmap.count(umaskcode))
	{
		umask=umaskmap[umaskcode];
	}
	UMASK = umask;
	cout<<umask<<endl;
}
/*
	根据用户userid找到用户的名字
*/
string get_username(int userid)
{
	fseek(fp,0,SEEK_SET);
	fread(files,sizeof(Fnode),1,fp);
	Fnode *f_system = (Fnode *)files;
	
	int user_num = f_system->usersnum;

	//User *user =(User *)files;
	
	//cout<<user->username<<endl;
	for(int i =0; i<user_num;i++)
	{
		fseek(fp,512*68+64*i,SEEK_SET);
		fread(files,sizeof(User),1,fp);
		User *user =(User *)files;
		if(user->user_id == userid)
		{
			return user->username;
		}
	}
	return "nobody";
}
/*
	根据用户组groupid找到用户组的名字
*/
string get_groupname(int groupid)
{
	fseek(fp,512+64*7,SEEK_SET);
	fread(inodeblock,sizeof(Inode),1,fp);
	Inode *inode = (Inode *)inodeblock;
	
	int group_num = inode->ds;

	for(int i =0; i<group_num;i++)
	{
		fseek(fp,512*72+16*i,SEEK_SET);
		fread(files,sizeof(Group),1,fp);
		Group *group =(Group *)files;
		if(group->group_id == groupid)
		{
			return group->groupname;
		}
	}
	return "nobody";
}
/*
	验证权限
	传入参数	当前登录用户的USERID,GROUPID[全局变量],
				想操作的inodeid(文件inodeid,目录inodeid)
				想要进行的操作r=5,w=2,x=1
	返回值	0	可以操作
			-1	木有权限操作
*/
int get_auth(int inodeid,int authid)
{
	//0.判断是不是root,root拥有全部权限
	if(USERID == 0)
	{
		return 0;
	}
//	cout<<"偶的userID:  "<<USERID<<endl;
//	cout<<"偶的groupID: "<<GROUPID<<endl;
	fseek(fp,512+64*inodeid,SEEK_SET);
	fread(inodeblock,sizeof(Inode),1,fp);
	Inode *inode =(Inode *)inodeblock;
//	cout<<inode->permissions<<endl;
	//1.验证登录用户是不是文件拥有者，有无权限？
	if(inode->user_id == USERID)
	{
		switch(authid)
		{
			case 4:
			{
				if(inode->permissions[1] == 'r')
				return 0;
				break;
			}
			case 2:
			{
				if(inode->permissions[2] == 'w')
				return 0;
				break;
			}
			case 1:
			{
				if(inode->permissions[3] == 'x')
				return 0;
				break;
			}
		}
		return -1;
	}
	//2.验证登录用户在不在文件拥有组，有无权限?
	if(inode->group_id == GROUPID)
	{
		switch(authid)
		{
			case 4:
			{
				if(inode->permissions[4] == 'r')
				return 0;
				break;
			}
			case 2:
			{
				if(inode->permissions[5] == 'w')
				return 0;
				break;
			}
			case 1:
			{
				if(inode->permissions[6] == 'x')
				return 0;
				break;
			}
		}
		return -1;
	}
	//3.验证登录用户在所有人的权限？
	switch(authid)
		{
			case 4:
			{
				if(inode->permissions[7] == 'r')
				return 0;
				break;
			}
			case 2:
			{
				if(inode->permissions[8] == 'w')
				return 0;
				break;
			}
			case 1:
			{
				if(inode->permissions[9] == 'x')
				return 0;
				break;
			}
		}
	//上面3次全部失败
	return -1;
}
/*
	根据数字转换为字符权限
*/
string num2char(string permissions)
{
	map<string,string> pmap;
	pmap["755"]="rwxr-xr-x";
	pmap["000"]="---------";
	pmap["766"]="rwxrw-rw-";
	pmap["666"]="rw-rw-rw-";
	pmap["777"]="rwxrwxrwx";
	pmap["700"]="rwx------";
	pmap["770"]="rwxrwx---";
	pmap["333"]="-wx-wx-wx";

	if(pmap.count(permissions))
	{
		return pmap[permissions];
	}
	return "-1";
}
/*
	查询某个inode是否存在
	0 尚未分配
	-1 已经分配
*/
int isInode(int inodeid)
{
	 fseek(fp,0,SEEK_SET); 
	 fread(files,sizeof(char),512,fp);
	 Fnode *f_system=(Fnode *)files;
	 if(f_system->bitmap[inodeid] == 0)
	 {
			return 0;

	 }
	 else
	 {
		return -1;
	 }
}


int su(string username="root")
{
	//string username;
	string password;
	int i;
	cout<<"Welcome to use zjut's filesystem!\n";
	while(1)
	{	
		
		cout<<username<<"@zjut's password: ";
		cin>>password;

		fseek(fp,0,SEEK_SET);
		fread(files,sizeof(char),512,fp);
		Fnode *f_system =(Fnode *)files;
		int user_num =f_system->usersnum;

		for(i=0; i<user_num; i++)
		{
			fseek(fp,512*68+64*i,SEEK_SET);
		///这里不能对filesystem进行操作，或者别再初始化之后对filesystem进行操作
			fread(files,sizeof(User),1,fp);
			User *user =(User *)files;
			if(user->username==username && user->password==password)
			{
			//PWD = "/home/"+USERNAME;
				PWD = user->pwd;
				cout<<"welcome!\n";
				USERNAME = user->username;
				GROUPID = user->group_id;
				USERID = user->user_id;
				if(USERNAME == "root")
				{
					PS1="#";
				}
				df();
				time_t b=time(0);
				cout<<"你当前登录时间为:"<<ctime(&b)<<endl;
				return 0;
			}
			else
			{
				
			}
		}
		cout<<"密码错误\n";

	}
}
