#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
using namespace std;
const int N=1001;
void logic();
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void setCursor(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}
void setsize(int col, int row)
{
	char cmd[64];
	sprintf(cmd, "mode con cols=%d lines=%d", col, row);
	system(cmd);
}
int string_to_num(string s){
	int num=0;
	for(int i=0;i<s.size();i++){
		if(s[i]>='0'&&s[i]<='9'){
			num=num*10+s[i]-'0';
		}
		else{
			return -1;
		}
	}
	return num;
}
/*
Error:undefined instruction 
not in valid instructions(not in read
x:not nature_num,too much or too few
*/
string command[N];
void read(int* max_cmd,int* cmds){
	setColor(9);
	cin>>*max_cmd;
	string s;
	cin.clear();
	getchar();
	for(int cnt=1;cnt<=*max_cmd;cnt++){
		setColor(9);
		cout<<cnt<<":";
		setColor(15);
		getline(cin,s);
		//cout<<s<<" "<<cnt<<endl;
		command[cnt]=s;
		string ss;
		int idx=-1;
		for(int i=0;i<s.size();i++){
		ss.clear();
			while(s[i]!=' '&&i<s.size()){
				ss+=s[i];
				i++;
			}
			if(idx==-1){
				if(ss=="inbox"){
					cmds[cnt]=0;
					idx=-2;
				}
				else if(ss=="outbox"){
					cmds[cnt]=1;
					idx=-2;
				}
				else if(ss=="add")idx=2;
				else if(ss=="sub")idx=3;
				else if(ss=="copyto")idx=4;
				else if(ss=="copyfrom")idx=5;
				else if(ss=="jump")idx=6;
				else if(ss=="jumpifzero")idx=7;
				else cmds[cnt]=-1;
			}
			else if(idx>=2){
				int X=string_to_num(ss);
				if(X==-1)cmds[cnt]=-1;
				else cmds[cnt]=idx+X*10;
				idx=-2;
			}
			else cmds[cnt]=-1;
		}
		if(idx!=-2)cmds[cnt]=-1;
	}
	logic();
	return ;
}
int level;//start from 0
int built_in_input[20][N];
int built_in_output[20][N];
bool built_in_valid[20][8];
int built_in_max_input[20];
int built_in_max_output[20];
int built_in_max_blank_place[20];
string built_in_content[20];
void init_ex(int* input_ex,int* output_ex,int* max_blank_place_ex,int* max_input_ex,int* max_output_ex){
	*max_input_ex=built_in_max_input[level];
	*max_output_ex=built_in_max_output[level];
	*max_blank_place_ex=built_in_max_blank_place[level];
	for(int i=0;i<*max_input_ex;i++)input_ex[i]=built_in_input[level][i];
	for(int i=0;i<*max_output_ex;i++)output_ex[i]=built_in_output[level][i];
}
void init_valid(bool* if_valid){
	for(int i=0;i<8;i++)if_valid[i]=built_in_valid[level][i];
}
int input_list[N],blank_place[N],output_list[N];
bool if_blank_place[N];
int cmds[N];
//input_list from 0,output_list from 0
//blank_place start from 0,cmds start from 1
bool valid_ex[N];//if user can use instruction
int input_ex[N],output_ex[N],max_blank_place_ex,max_input_ex,max_output_ex;//examples 
int idx=1,inhand_block,ptr_input=0,ptr_output=0;//idx:cmd right now
bool if_hand=0;//0 dont have inhand block
int max_cmd,max_level;
int ex;
void prtblock(int x,int y,int ans){
	setColor(15);
	setCursor(x,y);
	cout<<"+---+";
	setCursor(x,y+1);
	cout<<"|";
	setColor(2);
	if(ans>=0&&ans<=9)cout<<" "<<ans<<" ";
	else if(ans>=10&&ans<=99||ans<0&&ans>=-9)cout<<" "<<ans;
	else if(ans!=1e7)cout<<ans;
	else cout<<" X ";
	setColor(15);
	cout<<"|";
	setCursor(x,y+2);
	cout<<"+---+";
}
void prtinline(int x,int y){
	for(int i=ptr_input;i<max_input_ex;i++){
		prtblock(x,y+(i-ptr_input)*3,input_list[i]);
	}
	for(int i=0;i<ptr_input;i++){
		prtblock(x,y+(max_input_ex-ptr_input)*3+i*3,1e7);
	}
	setCursor(x-3,y);
	setColor(15);
	cout<<"IN";
}
void prtoutline(int x,int y){
	for(int i=0;i<ptr_output;i++){
		prtblock(x,y+i*3,output_list[i]);
	}
	setCursor(x+6,y);
	setColor(15);
	cout<<"OUT";
}
void prtblank(int x,int y){
	for(int i=0;i<max_blank_place_ex;i++){
		if(if_blank_place[i])prtblock(x+i*6,y,blank_place[i]);
		else prtblock(x+i*6,y,1e7); 
	}
	int cnt3=0;
	for(int i=x+2;i<=(max_blank_place_ex-1)*6+x+2;i+=6,cnt3++){
		setCursor(i,y+3);
		cout<<cnt3;
	}
}
void prtcode(int x,int y,int idx){
	setColor(15);
	for(int i=0;i<=29;i++){
		setCursor(x,i);
		cout<<"|";
	}
	setCursor(x+2,y);
	cout<<"==CODE==";
	for(int i=1;i<=max_cmd;i++){
		setCursor(x+2,y+i);
		if(i==idx){
			setColor(12);
			cout<<">";
		}
		setColor(9);
		cout<<i<<":";
		setColor(15);
		cout<<command[i];
	}
}
void prtrobot(int x,int y){
	if(if_hand){
		setColor(14);
		setCursor(x-2,y);
		cout<<"鸡你太美"; 
		setCursor(x-2,y+1);
		cout<<"鸡@||@美"; 
		setCursor(x-2,y+2);
		cout<<"鸡你太美"; 
		setCursor(x-2,y+3);
		cout<<"鸡    美"; 
		prtblock(x+6,y,inhand_block);
	}
	else{
		setColor(14);
		setCursor(x-2,y);
		cout<<"鸡你太美"; 
		setCursor(x-2,y+1);
		cout<<"鸡@||@美"; 
		setCursor(x-2,y+2);
		cout<<"鸡你太美"; 
		setCursor(x-2,y+3);
		cout<<"鸡    美";
	}
}
void prtscr(){
	system("cls");
	setColor(15);
	setCursor(0,0);
	cout<<"Level:"<<level+1;
	int _idx=idx-1;
	prtinline(3,1);
	prtoutline(80,1);
	prtcode(100,0,_idx);
	prtblank(16,25);
	int rx,ry;
	if(_idx!=0){
		if(cmds[_idx]%10==0){
			rx=11;
			ry=1;
		}
		if(cmds[_idx]%10==1){
			rx=74;
			ry=(ptr_output)*3-2;
		}
		if(cmds[_idx]%10==2||cmds[_idx]%10==3||cmds[_idx]%10==4||cmds[_idx]%10==5){
			int x=cmds[_idx]/10;
			rx=x*6+10;
			ry=21;
		}
	}
	else{
		rx=15;
		ry=5;
	}
	prtrobot(rx,ry);
}
void logic(){
	system("cls");
	/*ptr_output=2;
	prtrobot(15,5);
	system("pause");
	return ;*/
	/*for(int i=1;i<=max_cmd;i++)cout<<cmds[i]<<" ";
	cout<<endl;//debug
	for(int i=0;i<max_input_ex;i++)cout<<input_ex[i]<<" ";
	cout<<endl;
	for(int i=0;i<max_output_ex;i++)cout<<output_ex[i]<<" ";
	cout<<endl;*/
	
	int cnt=0;//total
	int err_flag=0;
	prtscr();
	Sleep(1000);
	while(1){
		cnt++;
		if(cnt>=1e7){//dead loop
			err_flag=1e7;
			break;
		}
		if(cmds[idx]==-1||cmds[idx]==0&&ptr_input>=max_input_ex){
			if(cmds[idx]==-1&&idx<=max_cmd)err_flag=idx;
			else prtscr();
			break;
		}//check break
		if(cmds[idx]==0){
			if(!valid_ex[0]){
				err_flag=idx;
				break;
			}
			if_hand=1;
			inhand_block=input_list[ptr_input++];
			idx++;
		}
		else if(cmds[idx]==1){
			if(!if_hand||!valid_ex[1]){
				err_flag=idx;
				break;
			}//check err
			if_hand=0;
			output_list[ptr_output++]=inhand_block;
			idx++;
		}
		else if(cmds[idx]%10==2){
			int x=cmds[idx]/10;
			if(!valid_ex[cmds[idx]%10]||!if_blank_place[x]||!if_hand||x>=max_blank_place_ex||x<0){
				err_flag=idx;
				break;
			}//check err;
			inhand_block+=blank_place[x];
			idx++;
		}
		else if(cmds[idx]%10==3){
			int x=cmds[idx]/10;
			if(!valid_ex[cmds[idx]%10]||!if_blank_place[x]||!if_hand||x>=max_blank_place_ex||x<0){
				err_flag=idx;
				break;
			}//check err;
			inhand_block-=blank_place[x];
			idx++;
		}
		else if(cmds[idx]%10==4){
			int x=cmds[idx]/10;
			if(!valid_ex[cmds[idx]%10]||!if_hand||x>=max_blank_place_ex||x<0){
				err_flag=idx;
				break;
			}//check err;
			blank_place[x]=inhand_block;
			if_blank_place[x]=1;
			idx++;
		}
		else if(cmds[idx]%10==5){
			int x=cmds[idx]/10;
			if(!valid_ex[cmds[idx]%10]||!if_blank_place[x]||x>=max_blank_place_ex||x<0){
				err_flag=idx;
				break;
			}//check err;
			inhand_block=blank_place[x];
			if_hand=1;
			idx++;
		}
		else if(cmds[idx]%10==6){
			int x=cmds[idx]/10;
			if(!valid_ex[cmds[idx]%10]||x>max_cmd||x<=0){
				err_flag=idx;
				break;
			}
			idx=x;
		}
		else if(cmds[idx]%10==7){
			int x=cmds[idx]/10;
			if(!valid_ex[cmds[idx]%10]||x>max_cmd||!if_hand||x<=0){
				err_flag=idx;
				break;
			}
			if(inhand_block==0)idx=x;
			else idx++;
		}
		prtscr();
		Sleep(1000);
	}
	if(!err_flag){
		if(ptr_output!=max_output_ex){
			system("cls");
			setColor(12);
			cout<<"Fail\n"<<"Total steps:"<<cnt-1;
			string tmp;
			tmp="Fail";
			MessageBox(NULL,tmp.c_str(),"Fail",MB_ICONERROR);
			//system("pause");
		}
		else{
			for(int i=0;i<ptr_output;i++){
				if(output_list[i]!=output_ex[i]){
					system("cls");
					setColor(12);
					cout<<"Fail\n"<<"Total steps:"<<cnt-1;
					string tmp;
					tmp="Fail";
					MessageBox(NULL,tmp.c_str(),"Fail",MB_ICONERROR);
					//system("pause");
					return ;
				}
			}
			system("cls");
			setColor(15);
			cout<<"Success\n"<<"Total steps:"<<cnt-1;
			string tmp;
			tmp="Success";
			if(level+1==ex&&max_level!=ex){
				cout<<"\nCongratulations!You've complete all levels!\nNow check maker's github account:54liujingcheng!";
			}
			if(level+1==max_level){
				max_level=min(level+2,ex);
				ofstream fout("user.txt");
				fout<<max_level;
				fout.close();
			}
			MessageBox(NULL,tmp.c_str(),"Success",MB_ICONINFORMATION);
			//system("pause");
		}
	}
	else {
		system("cls");
		setColor(12);
		cout<<"Error on instruction "<<err_flag;
		string tmp;
		tmp="Error on instruction "+to_string(err_flag);
		MessageBox(NULL,tmp.c_str(),"Error",MB_ICONERROR);
		//system("pause");
	}
	return ;
}
string cmdset[8]={"inbox","outbox","add","sub","copyto","copyfrom","jump","jumpifzero"};
void read_interface(){
	system("cls");
	setColor(15);
	cout<<"You select level ";
	setColor(12);
	cout<<level+1<<endl;
	setColor(15);
	cout<<"Level requirements:";
	setColor(12);
	cout<<built_in_content[level]<<endl;
	setColor(15);
	cout<<"There are "<<built_in_max_input[level]<<" input blocks:\n";
	setColor(9);
	for(int i=0;i<built_in_max_input[level];i++)cout<<built_in_input[level][i]<<" ";
	cout<<endl;
	setColor(15);
	cout<<"There are "<<built_in_max_output[level]<<" output blocks:\n";
	setColor(9);
	for(int i=0;i<built_in_max_output[level];i++)cout<<built_in_output[level][i]<<" ";
	cout<<endl;
	setColor(15);
	cout<<"And "<<built_in_max_blank_place[level]<<" available blank space\n";
	cout<<"Available instructions:";
	for(int i=0;i<8;i++){
		if(built_in_valid[level][i])cout<<cmdset[i]<<" ";
	}
	cout<<endl;
	cout<<"Enter number of lines, then enter your codes line by line\n";
	read(&max_cmd,cmds);
}
void main_interface(){
	setCursor(40,0);
	setColor(10);
	cout<<"Welcome to XiaoMing\'s Robot!\n";
	setCursor(80,1);
	setColor(15);
	cout<<"Made by Liujingcheng and Wangjiale\n";
	setCursor(0,2);
	ifstream fin("user.txt");
	fin>>max_level;
	fin.close();
	cout<<"We have "<<ex<<" levels now\n";
	cout<<"Your maximum level is "<<max_level<<"\nSelect one level and play!\n";
	setColor(9);
	for(int i=1;i<=max_level;i++){
		cout<<i<<endl;//5,6...,max_level+4
	}
	setColor(8);
	for(int i=max_level+1;i<=ex;i++)cout<<i<<endl;
	setColor(12);
	cout<<"EXIT";
	setCursor(6,5);
	cout<<"<";
	int _line=5;
	while(1){
		if(_kbhit()){
			int ch1=_getch();
			if(ch1==224){
				int ch2=_getch();
				if(ch2==72&&_line>5){
					setCursor(6,_line);
					cout<<" ";
					_line--;
					setCursor(6,_line);
					cout<<"<";
				}
				if(ch2==80&&_line<ex+5){
					setCursor(6,_line);
					cout<<" ";
					_line++;
					setCursor(6,_line);
					cout<<"<";
				}
			}
			if(ch1==13||ch1==' '){
				if(_line==ex+5){
					exit(0);
				}
				if(_line>=max_level+5){
					MessageBox(NULL,"Level locked","Error",MB_ICONERROR);
					break;
				}
				level=_line-5;
				if_hand=0;
				idx=1,ptr_input=0,ptr_output=0;
				max_cmd=0;
				memset(cmds,-1,sizeof(cmds));
				memset(if_blank_place,0,sizeof(if_blank_place));
				init_ex(input_ex,output_ex,&max_blank_place_ex,&max_input_ex,&max_output_ex);
				memcpy(input_list,input_ex,sizeof(input_ex));
				init_valid(valid_ex);
				read_interface();
				break;
			}
		}
	}
	system("cls");
	main_interface();
}
void getexample(){
	ifstream fin("exam.txt");
	fin>>ex;
	for(int i=0;i<ex;i++){
		fin>>built_in_max_input[i]>>built_in_max_output[i]>>built_in_max_blank_place[i];
		//cout<<built_in_max_input[i]<<" "<<built_in_max_output[i]<<" "<<built_in_max_blank_place[i]<<endl;
		for(int j=0;j<built_in_max_input[i];j++)fin>>built_in_input[i][j];
		for(int j=0;j<built_in_max_output[i];j++)fin>>built_in_output[i][j];
		for(int j=0;j<8;j++)fin>>built_in_valid[i][j];
		char shit;
		fin.get(shit);
		getline(fin,built_in_content[i]);
		//cout<<built_in_content[i]<<endl;
	}
	fin.close();
	return ;
}
int main(){
	SetConsoleTitle("XiaoMing\'s Robot");
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);
	cout.tie(0);
	/*
	-1 null cmd
	inbox: 0 pick fist block and discard block inhand
	outbox: 1 place block on out_list discard inhand block
			Error:dont have block inhand
	add X: 2 inhand block add X blank_place's block
			Error:dont have block in hand or in X or no X
	sub X:3 inhand block minus X blank_place's block to inhand block
			Error:dont have block in hand or in X or no X
	copyto X:4 copy block in hand to X blank_place and discard block in X previous
			Error dont have block inhand or no X
	copyfrom X:5 copy block in X to inhand block
			Error dont have X or no block in X
	jump X:6 jump to X cmd 
			Error dont have X cmd
	jumpifzero:7 if inhand block==0 then jump to X
			Error dont have X cmd or dont have inhand block
	cmd storation:0,1;X2,X3,X4...
	*/
	//here we init
	//example init
	getexample();
	//for(int i=0;i<built_in_max_input[2];i++)cout<<built_in_input[2][i]<<" ";
	//cout<<endl;
	main_interface();
}
