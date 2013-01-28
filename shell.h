#include<iostream>
#include<string>
using namespace std;
#include "help.h"
void shell()
{
/*4.命令消息队列循环
		4.1 当用户输入exit退出
	*/
	string shell;
	vector<string>str(20);
	str[0]="ls";
	str[1]="exit";
	str[2]="clear";
	str[3]="df";
	str[4]="mkdir";
	str[5]="cat";
	str[6]="cd";
	str[7]="pwd";
	str[8]="passwd";
	str[9]="umask";
	str[10]="rmdir";
	str[11]="chmod";
	str[12]="chown";
	str[13]="chgrp";
	str[14]="mv";				//移动文件 或者改变文件名
	str[15]="cp";				//复制文件
	str[16]="rm";				//删除文件
	str[17]="mk";				//用来创建文件
	str[18]="ln";				//
	str[19]="su";
	int ix;
	while(1)
	{
		////获取一行SHELL语句	
		getline(cin,shell);
		while(shell == "" )
		{
			cout<<"["<<USERNAME<<"@"<<HOSTNAME<<" "<<PWD<<"] "<<PS1;
			getline(cin,shell);
		}
		
		for(ix =0; ix != str.size(); ++ix)
		{
			if(shell.substr(0,shell.find_first_of(" ")) == str[ix])
			{
				break;
			}
		}
		//cout<<shell.substr(shell.find_last_of(" ")+1,2)<<endl;
		
		if("-h" == shell.substr(shell.find_last_of(" ")+1,2))
		{	
			shell=shell.substr(0,shell.find_first_of(" "));
			help(shell);
		}
		else
		switch(ix)
		{
			
			case 0:
			{
				//ls列出目录和文件
				///遍历/  找到/etc  然后
				int inodeid;
				string temp;
				if(shell.find_first_of(" ") == string::npos)
				{
					inodeid = findinode(PWD);
					//cout<<inodeid;
					ls(inodeid);
				}
				else
				{
					//cout<<PWD;
					temp = shell.substr(shell.find_first_of(" ")+1,shell.length()-shell.find_first_of(" "));
					inodeid = findinode(temp);
					
					if(inodeid >= 0)
					{
					//cout<<inodeid;
						ls(inodeid,temp);
					}
					else
					{
						cout<<"木有找到"<<temp<<"这个东西"<<endl;
					}
				}
				break;
			}
			case 1:
			{
				exit_block_stack();
				sync();
				
				cout<<"用户 "<<USERNAME<<" 已经退出"<<endl;
				exit(0);
				break;
			}
			case 2:
			{
				////清屏
				system("cls");
				break;
			}
			case 3:
			{
				//显示文件系统的详细信息
				df();
				break;
			}
			case 4:
			{
				//创建文件目录
				string dirname;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"请输入要创建的目录的名字"<<endl;
				}
				else
				{
					dirname = shell.substr(shell.find_first_of(" ")+1,shell.length()-shell.find_first_of(" "));
					mkdir(dirname);
				}
				break;
			}
			case 5:
			{
				//显示文件系统的详细信息
				int inodeid;
				int is;
				string temp;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"你要cat 撒?"<<endl;
				}
				else
				{
					temp = shell.substr(shell.find_first_of(" ")+1,shell.length()-shell.find_first_of(" "));
					inodeid = findinode(temp);
					
					is = Isdir(inodeid);
				//	cout<<inodeid<<endl;
					if(is == 0)
					{
						cat(inodeid);
					}
					else
					{
						cout<<temp<<"是个目录"<<endl;
					}

				}
				
				break;
			}
			case 6:
			{
				////cd 改变文件目录需要设置
				cd(shell);
				/**/
				break;
			}
			case 7:
			{
				//显示文件系统的详细信息
				pwd();
				break;
			}
			case 8:
			{
				//修改用户密码
				int suss;
				string temp;
				if(shell.find_first_of(" ") == string::npos)
				{
					
				}
				else
				{
					temp = shell.substr(shell.find_first_of(" ")+1,shell.length()-shell.find_first_of(" "));

					//cout<<temp<<endl;
					suss = passwd(temp);
					if(suss == 0)
					{
						cout<<"修改密码成功\n";
						//cin.clear();
						/*
							但是使用cin.clear();是不对的，cin.clear()作用不是清空键盘缓冲区，而是清楚先前使用cin所设定的一些cin状态(例如设置输出宽度，格式等等)，清除缓冲区应该使用cin.ignore()。
							cin.ignore()的一个常用功能就是用来清除以回车结束的输入缓冲区的内容，消除上一次输入对下一次输入的影响。比如可以这么用：cin.ignore( 1024,   '\n'   );
							通常把第一个参数设置得足够大，这样实际上总是只有第二个参数   '\n'   起作用，所以这一句就是把回车（包括回车）之前的所以字符从输入缓冲（流）中清除出去
						
						*/
						cin.ignore();
					}
					else
					{
						cout<<"木有"<<temp<<"这个用户,无法修改密码"<<endl;
					}

				}
				break;
			}
			case 9:
			{
				//umask 设置文件默认权限
				string temp;
				if(shell.find_first_of(" ") == string::npos)
				{
					umask();
				}
				else
				{
					temp = shell.substr(shell.find_first_of(" ")+1,shell.length()-shell.find_first_of(" "));
					umask(temp);
				}
			
				break;
			}
			case 10:
			{
				//删除文件目录
				string dirname;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"请输入要删除的目录的名字"<<endl;
				}
				else
				{
					dirname = shell.substr(shell.find_first_of(" ")+1,shell.length()-shell.find_first_of(" "));
					rmdir(dirname);
				}
				break;
			}
			case 11:
			{
				//chmod 改变读写执行的权限rwx
				string permissions;
				string temp;
				int inodeid;
				int xx;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"缺少参数"<<endl;
				}
				else
				{
					permissions = shell.substr(shell.find_first_of(" ")+1,3);
					temp = shell.substr(shell.find_last_of(" ")+1,shell.length()-shell.find_last_of(" "));
				//	cout<<permissions<<endl;
				//	cout<<temp<<endl;
					inodeid = findinode(temp);

					if(inodeid != -1)
					{
						xx = chmod(permissions,inodeid);
						if(xx == 0)
						{
						
						}
						else
						{
							cout<<"修改权限失败,没有此类权限"<<endl;
						}
					}
					else
					{
						cout<<"修改权限失败"<<endl;
					}
				}
				break;
			}
			case 12:
			{
				//chown 改变拥有者
				string owner;
				string temp;
				int inodeid;
				int userid;
				int xx;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"缺少参数"<<endl;
				}
				else
				{
					xx = shell.find_first_of(" ");
					owner = shell.substr(xx+1,shell.find_first_of(" ",xx+1)-xx-1);
					temp = shell.substr(shell.find_last_of(" ")+1,shell.length()-shell.find_last_of(" "));
				//	cout<<permissions<<endl;
				//	cout<<owner<<endl;
					inodeid = findinode(temp);
					if(inodeid != -1)
					{
						userid = isUser(owner);
						if(userid >= 0)
						{
							chown(userid,inodeid);
						}
						else
						{
							cout<<"对不起木有这个用户"<<owner<<endl;
						}
					}
					else
					{
						cout<<"当前目录不存在"<<temp<<endl;
					}
				}
				break;
			}
			case 13:
			{
				//chgrp 改变文件所属组
				string group;
				string temp;
				int inodeid;
				int groupid;
				int xx;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"缺少参数"<<endl;
				}
				else
				{
					xx = shell.find_first_of(" ");
					group = shell.substr(xx+1,shell.find_first_of(" ",xx+1)-xx-1);
					temp = shell.substr(shell.find_last_of(" ")+1,shell.length()-shell.find_last_of(" "));
				//	cout<<permissions<<endl;
				//	cout<<owner<<endl;
					inodeid = findinode(temp);
					if(inodeid != -1)
					{
						groupid = isGroup(group);
						if(groupid >= 0)
						{
							chgrp(groupid,inodeid);
						}
						else
						{
							cout<<"对不起木有这个用户组 "<<group<<endl;
						}
					}
					else
					{
						cout<<"当前目录不存在"<<temp<<endl;
					}
				}
				break;
			}
			case 14:
			{
				//mv 改变文件名
				string filename;
				string newfilename;
				int xx,inodeid;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"缺少参数"<<endl;
				}
				else
				{
					xx = shell.find_first_of(" ");
					filename = shell.substr(xx+1,shell.find_first_of(" ",xx+1)-xx-1);
					newfilename = shell.substr(shell.find_last_of(" ")+1,shell.length()-shell.find_last_of(" "));
					//cout<<"改后的名字为"<<newfilename<<endl;

					inodeid = findinode(filename);
					if(inodeid != -1)
					{
						mv(inodeid,newfilename);
					}
					else
					{
						cout<<"当前目录不存在"<<filename<<endl;
					}
				}
				break;
			}
			case 15:
			{
				//cp 复制文件
				string filename;
				string newfilename;
				int xx,inodeid;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"缺少参数"<<endl;
				}
				else
				{
					xx = shell.find_first_of(" ");
					filename = shell.substr(xx+1,shell.find_first_of(" ",xx+1)-xx-1);
					newfilename = shell.substr(shell.find_last_of(" ")+1,shell.length()-shell.find_last_of(" "));
					//cout<<"改后的名字为"<<newfilename<<endl;

					inodeid = findinode(filename);
					if(inodeid != -1)
					{
						cp(inodeid,newfilename);
					}
					else
					{
						cout<<"当前目录不存在"<<filename<<endl;
					}
				}
				break;
			}
			case 16:
			{
				//rm 删除文件
				string filename;
				int inodeid;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"请输入要删除的目录的名字"<<endl;
				}
				else
				{
					filename = shell.substr(shell.find_first_of(" ")+1,shell.length()-shell.find_first_of(" "));
					inodeid = findinode(filename);
					rm(inodeid,filename);
				}
				break;
			}
			case 17:
			{
				//mk 创建文件
				string filename;
				int filesize;
				char filechar;
				cout<<"请输入文件名字: ";
				cin>>filename;
				cout<<"\n请输入文件大小: ";
				cin>>filesize;
				cout<<"\n请输入填充字符: ";
				cin>>filechar;
				mk(filename,filesize,filechar);
				cin.ignore();
				break;
			}
			case 18:
			{
				//ln 链接文件 2种情况,别忘了考虑删除的时候是当links ==0 的时候才会删除。
				string filename;
				string linkfilename;
				string link;
				int index,index2,index3,inodeid;
				if(shell.find_first_of(" ") == string::npos)
				{
					cout<<"缺少参数"<<endl;
				}
				else
				{
					index  = shell.find_first_of(" ");
					index2 = shell.find_first_of(" ",index+1);
					index3 = shell.find_last_of(" ");
					filename = shell.substr(index+1,index2-index-1);
					linkfilename = shell.substr(index2+1,index3-index2-1);
					link = shell.substr(index3+1,shell.length()-index3);
					inodeid = findinode(filename);
					if(inodeid != -1)
					{
						if(link=="-s")
						{
							cout<<"偶是软链接\n";
							ln(inodeid,filename,linkfilename,1);
						}
						else if(index2==index3)
						{
							cout<<"偶是硬链接\n";
							ln(inodeid,filename,linkfilename,0);
						}
						else
						{
							cout<<"对不起,没有这个选项(硬链接不加参数,软链接加-s)\n";
						}
					}
					else
					{
						cout<<"当前目录不存在"<<filename<<endl;
					}
				}
				break;
			}
			case 19:
			{
				string username;
				username = shell.substr(shell.find_first_of(" ")+1,shell.length()-shell.find_first_of(" "));
				if(isUser(username)>=0)
				{
					su(username);
				}
				else if(shell=="su")
				{
					su();
				}
				else
				{
					cout<<"不存在这个"<<username<<"用户"<<endl;
				}
				//su("root");
				cin.ignore();
				break;
			}
			default:
			{
				cout<<"木有这个指令\n";
			}
		}
		cout<<"["<<USERNAME<<"@"<<HOSTNAME<<" "<<PWD<<"] "<<PS1;
	//	cin.clear();
	//	cout.clear();
		
	}

}