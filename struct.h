#include<bitset>
#include<stack>
using namespace std;
/*
	inode
	节点的结构
*/
typedef struct Inode{
	int inode_id;			//i节点号
	int user_id;			//用户组ID
	int group_id;			//所属组ID
	char permissions[10];	//权限rwxrwxrwx
	time_t mtime;			//上一次文件内容变动的时间
	int filesize;			//文件大小
	int blocknum;			//文件所使用的磁盘块的实际数目
	int blockaddress[6];	//文件数据block的位置,前4个为直接，第5个为一次间接,第6个为2次间接
	short links;			//链接数，即有多少文件名指向这个inode
	short ds;
}Inode;

/*
	fnode
	超级块的结构
*/
typedef struct Fnode{
	char *fsname;			//文件系统名字
	int fssize;				//文件系统大小
	int empty;				//文件系统空闲盘块大小
	int usersnum;			//用户数目
	bitset<512> bitmap;		//位示图
	int blockstack[10];		//磁盘空闲块栈
}Fnode;
/*
	Directory
	文件目录块的结构
	

*/
typedef struct Directory{
	char filename[14];			//目录名
	short inode_id;				//目录inodeid
	char parentfilename[14];	//父目录名
	short parent_id;			//父目录inodeid
}Directory;
/*
	User
	用户文件的目录结构
*/
typedef struct User{
	char username[16];		//用户名
	char password[16];		//用户密码
	int user_id;			//用户ID
	int group_id;			//用户组ID
	int others;				//其他字段
	char pwd[20];			//用户密码
}User;

/*
	临时空闲盘块栈结构
*/
typedef struct BlockStack{
	int blockstack[10];		//空闲盘块栈
}BlockStack;

/*
	Group
	用户组的目录结构
*/
typedef struct Group{
	int group_id;			//用户组ID
	char groupname[12];		//用户组名
}Group;
/*
	文件块的结构
*/
typedef struct File{
	char filechar[512];		//字节
}File;
/*
	索引结构	
*/
typedef struct Index{
	int blockaddress[128];	//索引盘块
}Index;
