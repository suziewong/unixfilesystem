#include<iostream>
#include<string>
#include<vector>
#include<map>
#define DEBUGS(a) cout<<#a<<"=="<<a<<endl
#pragma warning( disable : 4789)
#pragma warning( disable : 4786)
//#include "conf.h"
#include "func.h"
#include "shell.h"
using namespace std;
///Ö÷º¯Êý
int main()
{

	init();
	
	login();

	shell();
	
	return 0;
}