
#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define vs vector<string> 
#define setfind(a,b) a.find(b)!=a.end()
#define X first
#define Y second

/*
 Note: The first column in IR i.e, line numbers is 0-indexed
 Comma separated, without spaces
*/

const int INF=1e9;

vector<vector<string> > instructions;

set<string> all_variables;

vector<int> leaders;
vector<pair<int,int> > nodes;

set<string> keywords;//these are the reserved words used for the three address words.
set<string> ops_mth; // mathematical operators
set<string> ops_rel; // relational operators

map<string,pair<int,string> > SymbolTable;
vector<map<string,int> > NextUse;

vector<string> Registers;
map<string, string> RegisterDescriptor;
map<string, string> AddressDescriptor;

string AssemblyCode,DataSection,BssSection,TextSection;


void setRegisterDescriptor(string reg, string des){
	RegisterDescriptor[reg]=des;
}

string getRegisterDescriptor(string reg){
	return RegisterDescriptor[reg];
}

void setAddressDescriptor(string var, string des){
	AddressDescriptor[var]=des;
}

string getAddressDescriptor(string var){
	return AddressDescriptor[var];
}

// Lecture slide 29: Case 4? when is memory location returned?
string getRegister(int instr, string var){
	// Also, in X = Y op Z
	// if Y has no next use, then use the register of Y
	for(auto reg : Registers){
		if(getRegisterDescriptor(reg) == var){
			return reg;
		}
		if(getRegisterDescriptor(reg) == "NULL"){
			setRegisterDescriptor(reg, var);
			setAddressDescriptor(var, reg);
			return reg;
		}
	}
	string FarthestNextUse="";
	string var_;
	for(auto reg_ : Registers){
		var_ = getRegisterDescriptor(reg_);
		if(FarthestNextUse == "" || NextUse[instr][var_] > NextUse[instr][FarthestNextUse]){
			FarthestNextUse = var_;
		}
	}
	string reg_ = getAddressDescriptor(var_);
	// Spill this register reg_
	AssemblyCode+="movl "+reg_+", "+var_+"\n";
	setAddressDescriptor(var_, "mem");
	setAddressDescriptor(var, reg_);
	setRegisterDescriptor(reg_, var);
	return reg_;
}


int stringToInt(string s)
{
	int sign = 0;
	int i=0;
	if(s[0]=='-')
		sign = 1,i=1;
	int ret=0;
	for(;i<s.size();i++)
	{
		ret=ret*10+(s[i]-'0');
	}
	if(sign == 1)
		ret=-ret;
	return ret;
}

string intToString(int x)
{
	if(x==0)
		return "0";
	int sign = 0;
	if(x<0)
		sign = 1,x=-x;
	string ret="";
	while(x>0)
	{
		int d = x%10;
		x=x/10;
		ret=(char)('0'+d)+ret;
	}
	if(sign == 1)
		ret="-"+ret;
	return ret;
}

void init()
{
	keywords.insert("ifgoto");keywords.insert("goto");keywords.insert("return");
	keywords.insert("call");keywords.insert("print");keywords.insert("label");
	keywords.insert("<=");keywords.insert(">=");keywords.insert("==");
	keywords.insert(">");keywords.insert("<");keywords.insert("!=");
	keywords.insert("=");keywords.insert("function");keywords.insert("exit");

	ops_mth.insert("+");ops_mth.insert("-");ops_mth.insert("*");
	ops_mth.insert("/");ops_mth.insert("%");ops_rel.insert("&&");
	ops_rel.insert("||");ops_rel.insert("~");

	for(auto i : ops_mth)
		keywords.insert(i);

	for(auto i : ops_rel)
		keywords.insert(i);

	Registers.pb("%eax");Registers.pb("%ebx");
	Registers.pb("%ecx");Registers.pb("%edx");
}

vector<string> parse(string s){
	vector<string> vec;
	int n=(int)(s.size());
	string tmp="";
	for(int i=0; i<n; i++){
		if(s[i]==','){
			vec.pb(tmp);
			tmp="";
		}else{
			tmp=tmp+s[i];
		}
	}
	vec.pb(tmp);
	return vec;
}

bool isInteger(string s)
{
	int i=0;
	if(s[0]=='-')
	{
		i=1;
	}
	for( ; i < s.size(); i++)
		if(!('0'<=s[i]&&s[i]<='9'))
			return false;
	return true;
}


string getLocation(string var)
{
	if(isInteger(var))
	{
		return "$"+var;
	}
	string temp = getAddressDescriptor(var);
	if(temp == "mem")
		return var;
	else return temp;
}


string genx86(vector<string> instr){
	string x86 = "";
	int line_no  = stringToInt(instr[0]);
	string op = instr[1];
	//cout<<op<<endl;
	if(setfind(ops_mth,op))
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];
		//Finding the destination register
		/////////////
		//Addition
		if(op == "+")
		{
			//cout<<"in plus"<<endl;
			string destreg = getRegister(line_no,result);
			if(isInteger(operand1) && isInteger(operand2))
			{
				int op1 = stringToInt(operand1);
				int op2 = stringToInt(operand2);
				int res = (op1+op2);
				x86+="movl $"+intToString(res)+", "+destreg+"\n";
			}
			else
			{
				string lop1 = getLocation(operand1);
				string lop2 = getLocation(operand2);
				x86 += "movl "+lop1+", "+destreg+"\n";
				x86 += "addl "+lop2+", "+destreg+"\n";
			}
		}
		/////////////
		//Subtraction
		if(op == "-")
		{
			string destreg = getRegister(line_no,result);
			if(isInteger(operand1) && isInteger(operand2))
			{
				int op1 = stringToInt(operand1);
				int op2 = stringToInt(operand2);
				int res = (op1-op2);
				x86+="movl $"+intToString(res)+", "+destreg+"\n";
			}
			else
			{
				string lop1 = getLocation(operand1);
				string lop2 = getLocation(operand2);
				x86 += "movl "+lop1+", "+destreg+"\n";
				x86 += "subl "+lop2+", "+destreg+"\n";
			}
		}
		/////////////
		//Multiplication
		if(op == "*")
		{
			string destreg = getRegister(line_no,result);
			if(isInteger(operand1) && isInteger(operand2))
			{
				int op1 = stringToInt(operand1);
				int op2 = stringToInt(operand2);
				int res = (op1*op2);
				x86+="movl $"+intToString(res)+", "+destreg+"\n";
			}
			else
			{
				string lop1 = getLocation(operand1);
				string lop2 = getLocation(operand2);
				x86 += "movl "+lop1+", "+destreg+"\n";
				if(lop2[0] != '$'){
					x86 += "imul "+lop2+", "+destreg+"\n";
				}else{
					x86 += "imul "+lop2+", "+destreg+", "+destreg+"\n";
				}
			}
		}
		/////////////
		//Division
		if(op=="/")
		{
			if(getRegisterDescriptor("%eax")!="NULL")
			{
				x86+="movl %eax, "+getRegisterDescriptor("%eax")+"\n";
				setAddressDescriptor(getRegisterDescriptor("%eax"),"mem");
			}

			if(getRegisterDescriptor("%edx")!="NULL")
			{
				x86+="movl %edx, "+getRegisterDescriptor("%edx")+"\n";
				setAddressDescriptor(getRegisterDescriptor("%edx"),"mem");
			}


			x86 += "movl $0, %edx\n";
			//string destreg = getRegister(line_no,result);
			if(isInteger(operand1) && isInteger(operand2))
			{
				int op1 = stringToInt(operand1);
				int op2 = stringToInt(operand2);
				int res = (op1/op2);
				x86+="movl $"+intToString(res)+", "+"%eax"+"\n";
			}
			else
			{
				string lop1 = getLocation(operand1);
				string lop2 = getLocation(operand2);
				x86 += "movl "+lop1+", "+"%eax"+"\n";
				if(lop2[0]=='$'){
					if(getRegisterDescriptor("%ebx")!="NULL")
					{
						x86+="movl %ebx, "+getRegisterDescriptor("%ebx")+"\n";
						setAddressDescriptor(getRegisterDescriptor("%ebx"),"mem");
					}

					x86 += "movl "+lop2+", "+"%ebx"+"\n";
					x86 += "idiv %ebx\n";
					setRegisterDescriptor("%ebx","NULL");
				}
				else
				{
					x86 += "idiv "+lop2+"\n";
				}
			}
			setRegisterDescriptor("%edx","NULL");
			setRegisterDescriptor("%eax",result);
			setAddressDescriptor(result,"%eax");
		}
		/////////////
		//Modulus
		if(op=="%")
		{
			if(getRegisterDescriptor("%eax")!="NULL")
			{
				x86+="movl %eax, "+getRegisterDescriptor("%eax")+"\n";
				setAddressDescriptor(getRegisterDescriptor("%eax"),"mem");
			}

			if(getRegisterDescriptor("%edx")!="NULL")
			{
				x86+="movl %edx, "+getRegisterDescriptor("%edx")+"\n";
				setAddressDescriptor(getRegisterDescriptor("%edx"),"mem");
			}


			x86 += "movl $0, %edx\n";
			//string destreg = getRegister(line_no,result);
			if(isInteger(operand1) && isInteger(operand2))
			{
				int op1 = stringToInt(operand1);
				int op2 = stringToInt(operand2);
				int res = (op1%op2);
				x86+="movl $"+intToString(res)+", "+"%eax"+"\n";
			}
			else
			{
				string lop1 = getLocation(operand1);
				string lop2 = getLocation(operand2);
				x86 += "movl "+lop1+", "+"%eax"+"\n";
				if(lop2[0]=='$'){
					if(getRegisterDescriptor("%ebx")!="NULL")
					{
						x86+="movl %ebx, "+getRegisterDescriptor("%ebx")+"\n";
						setAddressDescriptor(getRegisterDescriptor("%ebx"),"mem");
					}

					x86 += "movl "+lop2+", "+"%ebx"+"\n";
					x86 += "idiv %ebx\n";
					setRegisterDescriptor("%ebx","NULL");
				}
				else
				{
					x86 += "idiv "+lop2+"\n";
				}
			}
			setRegisterDescriptor("%eax","NULL");
			setRegisterDescriptor("%edx",result);
			setAddressDescriptor(result,"%edx");
		}

	}
	else if(op == "print")
	{
		//print statement
		string operand = instr[2];
		string lop = getLocation(operand);
		x86 += "pushl "+lop+"\n"+"pushl $fmt_str\n"+"call printf\n";
	}

	return x86;
}

int main(){
	ifstream fin("test1");
	while(!fin.eof()){
		string OneInstr;
		getline(fin, OneInstr);
		if(OneInstr == "")continue;
		instructions.pb(parse(OneInstr));
	}
	

	//initialize keywords and operations
	init();
	//cout<<"Init done"<<endl;
	int NumInstr=(int)(instructions.size());

	/*
	 *for(int i=0;i<NumInstr;i++){
	 *    for(int j=0;j<instructions[i].size();j++){
	 *        cout<<instructions[i][j]<<" -- ";
	 *    }
	 *    cout<<endl;
	 *}
	 */

	leaders.pb(0);
	//cout<<"Number of Instructions are: "<<NumInstr<<endl;
	for(int i=0; i<NumInstr; i++){
		//cout<<i<<" ****"<<endl;
		if(instructions[i][1] == "ifgoto"){
			int si=(int)(instructions[i].size());
			string GoInstr=instructions[i][si-1];
			int NxtInstr=i+1;
			//convert GoInstr to int
			leaders.pb(stringToInt(GoInstr));
			if(NxtInstr<NumInstr)leaders.pb(NxtInstr);
		}
		if(instructions[i][1] == "goto"){
			int si=(int)(instructions[i].size());
			string GoInstr=instructions[i][si-1];
			int NxtInstr=i+1;
			leaders.pb(stringToInt(GoInstr));
			if(NxtInstr<NumInstr)leaders.pb(NxtInstr);
		}
		if(instructions[i][1] == "label"){
			leaders.pb(i);
		}
	}
	//cout<<"Leaders made"<<endl;
	//make the set of all variables
	for(int i=0;i<NumInstr;i++)
	{
		for(auto idx : instructions[i])
		{
			if(keywords.find(idx) == keywords.end())
			{
				if(!isInteger(idx))
					all_variables.insert(idx);
			}
		}
	}
	//cout<<"All variables done"<<endl;

	sort(leaders.begin(), leaders.end());
	leaders.erase(unique(leaders.begin(), leaders.end()), leaders.end());
	int NumLeaders = (int)(leaders.size());
	for(int i=0; i<NumLeaders-1; i++){
		nodes.pb(mp(leaders[i], leaders[i+1]-1));
	}
	nodes.pb(mp(leaders[NumLeaders-1], NumInstr-1));
	int NumNodes = (int)(nodes.size());

	//cout<<nodes[0].X<<" "<<nodes[0].Y<<"****"<<endl;

	NextUse.resize(NumInstr);

	//cout<<"Number of nodes is "<<NumNodes<<endl;

	for(int nd=0; nd<NumNodes; nd++){
		for(auto idx : all_variables)
			SymbolTable[idx]=mp(INF,"Dead");
		for(int instr=nodes[nd].Y; instr>=nodes[nd].X; instr--){
			vector<string> InstrLine = instructions[instr];
			string Operator = InstrLine[1];
			for(auto var : all_variables){
				NextUse[instr][var] = SymbolTable[var].X;
			}
			if(ops_mth.find(Operator) != ops_mth.end())
			{
				//math operator
				string a,b,c;//a = b op c
				assert(InstrLine.size() == 5);
				a = InstrLine[2];
				b = InstrLine[3];
				c = InstrLine[4];
				if(setfind(all_variables,a))
					SymbolTable[a]=mp(INF, "Dead");
				if(setfind(all_variables,b))
					SymbolTable[b]=mp(instr, "Live");
				if(setfind(all_variables,c))
					SymbolTable[c]=mp(instr, "Live");
			}
			else if(Operator == "ifgoto")
			{
				string a = InstrLine[3];
				string b = InstrLine[4];
				if(setfind(all_variables,a))
					SymbolTable[a]=mp(instr, "Live");
				if(setfind(all_variables,b))
					SymbolTable[b]=mp(instr, "Live");
			}
			else if(Operator == "print")
			{
				string a = InstrLine[2];
				if(setfind(all_variables,a))
					SymbolTable[a] = mp(instr, "Live");
			}
			else if(Operator == "=")
			{
				string a = InstrLine[2];
				string b = InstrLine[3];
				if(setfind(all_variables,a))
					SymbolTable[a]=mp(instr, "Live");
				if(setfind(all_variables,b))
					SymbolTable[b]=mp(instr, "Live");
			}
		}
	}
	//cout<<"Made symboltable"<<endl;
	AssemblyCode="";
	DataSection=".section .data\n";
	for(auto var : all_variables){
		DataSection+=var+":\n.int 0\n";
	}
	DataSection+="fmt_str:\n.ascii \"%d\\n\\0\"\n";
	BssSection=".section .bss\n";
	TextSection=".section .text\n.globl main\nmain:\n";
	for(int nd=0; nd<NumNodes; nd++){
		for(auto var : all_variables){
			setAddressDescriptor(var, "mem");
		}
		for(auto reg : Registers){
			setRegisterDescriptor(reg, "NULL");
		}
		//nodes[nd].X to nodes[nd].Y 0-indexed instruction numbers
		TextSection+="Node"+intToString(nodes[nd].X)+":\n";

		//cout<<nodes[nd].X<<" "<<nodes[nd].Y<<endl;
		for(int instr=nodes[nd].X; instr<=nodes[nd].Y; instr++){
			//cout<<"Instruction number "<<instr<<endl;
			TextSection+=genx86(instructions[instr]);
			// clean(instructions[instr])
			// if variables dead after this change RegisterDescriptor
		}
		// Should we put data in all registers into memory after each basic block?
	}
	AssemblyCode+=DataSection+BssSection+TextSection;
	cout<<AssemblyCode<<endl;
	return 0;
}
