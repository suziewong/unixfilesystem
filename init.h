
//创建一些必要的文件,这些文件有/ /bin /etc /etc/passwd /etc/etc/shadow /home 
void init_dir()
{
		// 第1个inode id=0,空闲盘块占用第66个
		Inode *inode=(Inode *)(filesystem+512);
		inode->inode_id = 0;
		inode->group_id = 0;
		inode->blockaddress[0] = 65;
		inode->filesize = 512;
		inode->blocknum = 1;
		inode->links =1;
		inode->user_id = 0; //root  用户ID为1
		char * permissons = "drwxrwxr-x";
		strcpy(inode->permissions,permissons);
		inode->mtime = time(0);
		inode->ds = 2;
		Directory *directory = (Directory *)(filesystem+512*65);
		char * filename ;
		filename = "home";
		strcpy(directory->filename,filename);
		directory->inode_id = 1;
		directory->parent_id = 0;
		filename = "/";
		strcpy(directory->parentfilename,filename);

		directory++;
		filename = "etc";
		strcpy(directory->filename,filename);
		directory->inode_id = 2;
		directory->parent_id = 0;
		filename = "/";
		strcpy(directory->parentfilename,filename);

		//第2个inode id=1 /home目录 占用第67个盘块
		inode=(Inode *)(filesystem+512+64);
		inode->inode_id = 0;
		inode->group_id = 0;
		inode->blockaddress[0] = 66;
		inode->filesize = 512;
		inode->blocknum = 1;
		inode->links =1;
		inode->user_id = 0; //root  用户ID为0
		permissons = "drwxr-xr-x";
		strcpy(inode->permissions,permissons);
		inode->mtime = time(0);
		inode->ds = 2;
		//第一个家目录
		directory = (Directory *)(filesystem+512*66);
		filename = "suzie";
		strcpy(directory->filename,filename);
		directory->inode_id = 4;
		directory->parent_id =1;
		filename="home";
		strcpy(directory->parentfilename,filename);
		//第二个家目录
		directory++;
		filename = "root";
		strcpy(directory->filename,filename);
		directory->inode_id = 6;
		directory->parent_id =1;
		filename="home";
		strcpy(directory->parentfilename,filename);



		//第3个inode id=2 /etc 目录 占用第68个
		inode=(Inode *)(filesystem+512+64*2);
		inode->inode_id = 2;
		inode->group_id = 0;
		inode->blockaddress[0] = 67;
		inode->filesize = 512;
		inode->blocknum = 1;
		inode->links =1;
		inode->user_id = 0; //root  用户ID为0
		permissons = "drwxrw-rw-";
		strcpy(inode->permissions,permissons);
		inode->mtime = time(0);
		inode->ds = 2;

		directory = (Directory *)(filesystem+512*67);
		filename = "passwd";
		strcpy(directory->filename,filename);
		directory->inode_id = 3;
		directory->parent_id =2;
		filename = "etc";
		strcpy(directory->parentfilename,filename);
		directory++;
		filename = "group";
		strcpy(directory->filename,filename);
		directory->inode_id = 7;
		directory->parent_id =2;
		filename = "etc";
		strcpy(directory->parentfilename,filename);

		//第4个inode id=3 /etc/passwd 占用第69个盘块
		inode=(Inode *)(filesystem+512+64*3);
		inode->inode_id = 3;
		inode->group_id = 0;
		inode->blockaddress[0] = 68;
		inode->filesize = 512;
		inode->blocknum = 1;
		inode->links =1;
		inode->user_id = 0; //root  用户ID为0
		permissons = "-rwxrw-rw-";
		strcpy(inode->permissions,permissons);
		inode->mtime = time(0);
		inode->ds = 2;
		//第一个默认用户suzie
		User *user =(User *)(filesystem+512*68);
		char *temp="root";
		strcpy(user->username,temp);
		temp="root";
		strcpy(user->password,temp);
		user->user_id = 0;
		user->group_id = 0;
		temp="/home/root";
		strcpy(user->pwd,temp);

		user++;
		temp="suzie";
		strcpy(user->username,temp);
		temp="123";
		strcpy(user->password,temp);
		user->user_id = 1;
		user->group_id = 1;
		temp="/home/suzie";
		strcpy(user->pwd,temp);
		///第2个默认用户root
	




		//第5个文件 id=4 /home/suzie 占用第70个盘块
		inode=(Inode *)(filesystem+512+64*4);
		inode->inode_id = 4;
		inode->group_id = 1;
		inode->blockaddress[0] = 69;
		inode->filesize = 512;
		inode->blocknum = 1;
		inode->links =1;
		inode->user_id = 1; //suzie  用户ID为1
		permissons = "drwxrw-rw-";
		strcpy(inode->permissions,permissons);
		inode->mtime = time(0);
		inode->ds = 1;
		
		directory = (Directory *)(filesystem+512*69);
		filename = "test";
		strcpy(directory->filename,filename);
		directory->inode_id = 5;
		directory->parent_id =4;
		filename = "suzie";
		strcpy(directory->parentfilename,filename);
		//第6个文件 id=5 /home/suzie/test 占用第71个
		inode=(Inode *)(filesystem+512+64*5);
		inode->inode_id = 5;
		inode->group_id = 1;
		inode->blockaddress[0] = 70;
		inode->filesize = 512;
		inode->blocknum = 1;
		inode->links =1;
		inode->user_id = 1; //suzie  用户ID为1
		permissons = "-rwxrw-rw-";
		strcpy(inode->permissions,permissons);
		inode->mtime = time(0);
		inode->ds = 0;

		//第7个文件 id=6 /home/root 占用第72个
		inode=(Inode *)(filesystem+512+64*6);
		inode->inode_id = 6;
		inode->group_id = 0;
		inode->blockaddress[0] = 71;
		inode->filesize = 512;
		inode->blocknum = 1;
		inode->links =1;
		inode->user_id = 0; //root  用户ID为0
		permissons = "drwxrw-rw-";
		strcpy(inode->permissions,permissons);
		inode->mtime = time(0);
		inode->ds = 0;
		//第8个默认文件 id=7 /etc/group 占用第73个
		inode=(Inode *)(filesystem+512+64*7);
		inode->inode_id = 7;
		inode->group_id = 0;
		inode->blockaddress[0] = 72;
		inode->filesize = 512;
		inode->blocknum = 1;
		inode->links =1;
		inode->user_id = 0; //root  用户ID为0
		permissons = "-rwxrw-rw-";
		strcpy(inode->permissions,permissons);
		inode->mtime = time(0);
		inode->ds = 2;
		
		//第一个 用户组root
		Group *group = (Group *)(filesystem+512*72);
		char *groupname = "root";
		strcpy(group->groupname,groupname);
		group->group_id=0;
		//第二个 用户组suzie
		group++;
		groupname = "zjut";
		strcpy(group->groupname,groupname);
		group->group_id=1;


}