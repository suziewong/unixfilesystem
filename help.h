/*
	1.演示mkdir的时候 看inodeid
	然后rmdir一下，这个时候inode已经回收，然后再去创建mkdir看inodeid，一致的!
*/
void help(string shell)
{

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
	int ix;
	for(ix =0; ix != str.size(); ++ix)
	{
		if(shell.substr(0,shell.find_first_of(" ")) == str[ix])
		{
			break;
		}
	}
	cout<<"       "<<shell<<"    的帮助"<<endl;
	cout<<"============================\n";
	switch(ix)
	{
		case 0:
		{
			cout<<"ls        直接显示当前目录的信息\n";
			cout<<"ls /home  显示/home目录下的目录信息(相对路径，绝对路径均可)\n";
			cout<<"ls test   显示当前文本文件的信息\n";
			break;
		}
		case 1:
		{
			break;
		}
		case 11:
		{
			cout<<"chmod 755 /home  改变文件或者目录的权限\n";
			break;
		}
		case 12:
		{
			cout<<"chown suzie /home  改变文件拥有者\n";
			break;
		}
		case 13:
		{
			cout<<"chgrp zjut /home  改变文件所属组\n";
			break;
		}
		case 17:
		{
			cout<<"mk newfilename 512*7 a	在当前目录下创建一个大小为512*7的名字为newfilename 并且以a字母填充的文件\n";
		}
	}
}