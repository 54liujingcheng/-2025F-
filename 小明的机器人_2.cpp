#include<bits/stdc++.h>
using namespace std;
const int N=1001;
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
void read(int* max_cmd,int* err_flag,int* cmds){
	cin>>*max_cmd;
	string s;
	getchar();
	for(int cnt=1;cnt<=*max_cmd;cnt++){
		getline(cin,s);
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
	return ;
}
int level;//start from 0
int built_in_input[20][N]={{1,2},{3,9,5,1,-2,-2,9,-9},{6,2,7,7,-9,3,-3,-3}};
int built_in_output[20][N]={{1,2},{-6,6,4,-4,0,0,18,-18},{7,-3}};
bool built_in_valid[20][N]={{1,1,0,0,0,0,0,0},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1}};
int built_in_max_input[20]={2,8,8};
int built_in_max_output[20]={2,8,2};
int built_in_max_blank_place[20]={0,3,3};
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
int main(){
	cin>>level;
	level--;
	if(level<0||level>2){
		cout<<"Error level\n";
	}
	int input_list[N],blank_place[N],output_list[N];
	bool if_blank_place[N];
	int cmds[N];
	//input_list from 0,output_list from 0
	//blank_place start from 0,cmds start from 1
	bool valid_ex[N];//if user can use instruction//not used now
	int input_ex[N],output_ex[N],max_blank_place_ex,max_input_ex,max_output_ex;//examples
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
	memset(cmds,-1,sizeof(cmds));
	memset(if_blank_place,0,sizeof(if_blank_place));
	int max_cmd;
	int err_flag=0;
	//example init
	init_ex(input_ex,output_ex,&max_blank_place_ex,&max_input_ex,&max_output_ex);
	memcpy(input_list,input_ex,sizeof(input_ex));
	init_valid(valid_ex);
	//read
	read(&max_cmd,&err_flag,cmds);
	int idx=1,inhand_block,ptr_input=0,ptr_output=0;//idx:cmd right now
	bool if_hand=0;//0 dont have inhand block
	int cnt=0;//total
	
	/*for(int i=1;i<=max_cmd;i++)cout<<cmds[i]<<" ";
	cout<<endl;//debug
	for(int i=0;i<max_input_ex;i++)cout<<input_ex[i]<<" ";
	cout<<endl;
	for(int i=0;i<max_output_ex;i++)cout<<output_ex[i]<<" ";
	cout<<endl;*/

	while(1){
		
		/*cout<<"--------\n";
		cout<<inhand_block<<" "<<idx<<" "<<cnt<<" "<<cmds[idx]<<endl;
		for(int i=0;i<max_blank_place_ex;i++)cout<<blank_place[i]<<" ";
		cout<<endl;
		for(int i=0;i<ptr_output;i++)cout<<output_list[i]<<" ";
		cout<<endl;//debug
		cout<<"--------\n";*/
		
		cnt++;
		if(cnt>=1e7){//dead loop
			err_flag=1e7;
			break;
		}
		if(cmds[idx]==-1||cmds[idx]==0&&ptr_input>=max_input_ex){
			if(cmds[idx]==-1&&idx<=max_cmd)err_flag=idx;
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
	}
	if(!err_flag){
		if(ptr_output!=max_output_ex)cout<<"Fail";
		else{
			for(int i=0;i<ptr_output;i++){
				if(output_list[i]!=output_ex[i]){
					cout<<"Fail";
					return 0;
				}
			}
			cout<<"Success";
		}
	}
	else cout<<"Error on instruction "<<err_flag;
	//check output
}
