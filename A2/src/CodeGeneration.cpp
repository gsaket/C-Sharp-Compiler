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
	  The Labels in goto and ifgoto can be line numberes only!
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
string x86;
vector<pair<string,string> > array_list;

bool isInteger(string s);

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

string getRegister(int instr, string var, string operand1 = "$$", string operand2 = "$$"){
	for(auto reg : Registers){
		if(getRegisterDescriptor(reg) == var){
			if(var == operand1 || var == operand2)
				continue;
			return reg;
		}
		if(getRegisterDescriptor(reg) == "NULL"){
			//if(!isInteger(var))setRegisterDescriptor(reg, var);
			//if(!isInteger(var))setAddressDescriptor(var, reg);
			return reg;
		}
	}
	string FarthestNextUse="";
	string var_;
	for(auto reg_ : Registers){
		var_ = getRegisterDescriptor(reg_);
		if(var_ == operand1 || var_ == operand2)
			continue;
		if(FarthestNextUse == "" || NextUse[instr][var_] > NextUse[instr][FarthestNextUse]){
			FarthestNextUse = var_;
		}
	}
	string reg_ = getAddressDescriptor(var_);
	if(NextUse[instr][var_] == INF && operand2 != "$$"){
		//cerr<<var<<" "<<operand1<<" "<<operand2<<endl;
		return reg_;
	}
	// Spill this register reg_
	x86 += "movl "+reg_+", "+var_+"\n";
	setAddressDescriptor(var_, "mem");
	//if(!isInteger(var))setAddressDescriptor(var, reg_);
	//if(!isInteger(var))setRegisterDescriptor(reg_, var);
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
	keywords.insert("call");keywords.insert("print");keywords.insert("read");
	keywords.insert("<=");keywords.insert(">=");keywords.insert("==");
	keywords.insert(">");keywords.insert("<");keywords.insert("!=");
	keywords.insert("=");keywords.insert("function");keywords.insert("exit");
	//arrays
	keywords.insert("array");keywords.insert("member");keywords.insert("update");

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
	x86 = "";
	int line_no  = stringToInt(instr[0]);
	string op = instr[1];
	//cout<<op<<endl;
	if(setfind(ops_mth,op))
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];
		/////////////
		//Addition
		if(op == "+")
		{
			string destreg = getRegister(line_no,result,operand1,operand2);
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
				if(lop1 != destreg)
				x86 += "movl "+lop1+", "+destreg+"\n";
				x86 += "addl "+lop2+", "+destreg+"\n";
			}
			if(!isInteger(result))setAddressDescriptor(result, destreg);
			if(!isInteger(result))setRegisterDescriptor(destreg, result);
		}
		/////////////
		//Subtraction
		if(op == "-")
		{
			string destreg = getRegister(line_no,result,operand1,operand2);
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
			if(!isInteger(result))setAddressDescriptor(result, destreg);
			if(!isInteger(result))setRegisterDescriptor(destreg, result);
		}
		/////////////
		//Multiplication
		if(op == "*")
		{
			string destreg = getRegister(line_no,result,operand1,operand2);
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
			if(!isInteger(result))setAddressDescriptor(result, destreg);
			if(!isInteger(result))setRegisterDescriptor(destreg, result);
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
			//string destreg = getRegister(line_no,result,operand1,operand2);
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
			//string destreg = getRegister(line_no,result,operand1,operand2);
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
	/////////////
	// LEFT SHIFT
	else if(op=="<<")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];
		string destreg = getRegister(line_no,result,operand1,operand2);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int op1 = stringToInt(operand1);
			int op2 = stringToInt(operand2);
			int res = (op1<<op2);
			x86+="movl $"+intToString(res)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "shl "+lop2+", "+destreg+"\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	/////////////
	// SHIFT RIGHT
	else if(op==">>")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];
		string destreg = getRegister(line_no,result,operand1,operand2);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int op1 = stringToInt(operand1);
			int op2 = stringToInt(operand2);
			int res = (op1>>op2);
			x86+="movl $"+intToString(res)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "shr "+lop2+", "+destreg+"\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	/////////////
	// BITWISE AND
	else if(op=="&&")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];
		string destreg = getRegister(line_no,result,operand1,operand2);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int op1 = stringToInt(operand1);
			int op2 = stringToInt(operand2);
			int res = (op1&op2);
			x86+="movl $"+intToString(res)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "and "+lop2+", "+destreg+"\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	/////////////
	// BITWISE OR
	else if(op=="||")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];
		string destreg = getRegister(line_no,result,operand1,operand2);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int op1 = stringToInt(operand1);
			int op2 = stringToInt(operand2);
			int res = (op1|op2);
			x86+="movl $"+intToString(res)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "or "+lop2+", "+destreg+"\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	/////////////
	// NOT
	else if(op=="~")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		string destreg = getRegister(line_no,result,operand1);
		if(isInteger(operand1))
		{
			int op1 = stringToInt(operand1);
			int res = (~op1);
			x86+="movl $"+intToString(res)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "not "+destreg+"\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	//////////
	// LEQ
	else if(op == "<=")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];

		string destreg = getRegister(line_no,result,operand1,operand2);
		string LEQ = "LEQ"+intToString(line_no);
		string NLEQ = "NLEQ"+intToString(line_no);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int leqres = (stringToInt(operand1)<=stringToInt(operand2));
			x86 += "movl $"+intToString(leqres)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "cmpl "+lop2+", "+destreg+"\n";
			x86 += "jle "+LEQ+"\n";
			x86 += "movl $0, "+destreg+"\n";
			x86 += "jmp "+NLEQ+"\n";
			x86 += LEQ + ": \n";
			x86 += "movl $1, "+destreg+"\n";
			x86 += NLEQ +":\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	//////////
	// GEQ
	else if(op == ">=")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];

		string destreg = getRegister(line_no,result,operand1,operand2);
		string GEQ = "GEQ"+intToString(line_no);
		string NGEQ = "NGEQ"+intToString(line_no);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int leqres = (stringToInt(operand1)>=stringToInt(operand2));
			x86 += "movl $"+intToString(leqres)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "cmpl "+lop2+", "+destreg+"\n";
			x86 += "jge "+GEQ+"\n";
			x86 += "movl $0, "+destreg+"\n";
			x86 += "jmp "+NGEQ+"\n";
			x86 += GEQ + ": \n";
			x86 += "movl $1, "+destreg+"\n";
			x86 += NGEQ +":\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	//////////
	// EQ
	else if(op == "==")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];

		string destreg = getRegister(line_no,result,operand1,operand2);
		string EQ = "EQ"+intToString(line_no);
		string NEQ = "NEQ"+intToString(line_no);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int leqres = (stringToInt(operand1)==stringToInt(operand2));
			x86 += "movl $"+intToString(leqres)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "cmpl "+lop2+", "+destreg+"\n";
			x86 += "je "+EQ+"\n";
			x86 += "movl $0, "+destreg+"\n";
			x86 += "jmp "+NEQ+"\n";
			x86 += EQ + ": \n";
			x86 += "movl $1, "+destreg+"\n";
			x86 += NEQ +":\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	//////////
	// NEQ
	else if(op == "!=")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];

		string destreg = getRegister(line_no,result,operand1,operand2);
		string NEQ = "NEQ"+intToString(line_no);
		string NNEQ = "NNEQ"+intToString(line_no);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int leqres = (stringToInt(operand1)!=stringToInt(operand2));
			x86 += "movl $"+intToString(leqres)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "cmpl "+lop2+", "+destreg+"\n";
			x86 += "jne "+NEQ+"\n";
			x86 += "movl $0, "+destreg+"\n";
			x86 += "jmp "+NNEQ+"\n";
			x86 += NEQ + ": \n";
			x86 += "movl $1, "+destreg+"\n";
			x86 += NNEQ +":\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	//////////
	// LT
	else if(op == "<")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];

		string destreg = getRegister(line_no,result,operand1,operand2);
		string LT = "LT"+intToString(line_no);
		string NLT = "NLT"+intToString(line_no);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int leqres = (stringToInt(operand1)<stringToInt(operand2));
			x86 += "movl $"+intToString(leqres)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "cmpl "+lop2+", "+destreg+"\n";
			x86 += "jl "+LT+"\n";
			x86 += "movl $0, "+destreg+"\n";
			x86 += "jmp "+NLT+"\n";
			x86 += LT + ": \n";
			x86 += "movl $1, "+destreg+"\n";
			x86 += NLT +":\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	//////////
	// GT
	else if(op == ">")
	{
		string result, operand1, operand2;
		result = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];

		string destreg = getRegister(line_no,result,operand1,operand2);
		string GT = "GT"+intToString(line_no);
		string NGT = "NGT"+intToString(line_no);
		if(isInteger(operand1) && isInteger(operand2))
		{
			int leqres = (stringToInt(operand1)>stringToInt(operand2));
			x86 += "movl $"+intToString(leqres)+", "+destreg+"\n";
		}
		else
		{
			string lop1 = getLocation(operand1);
			string lop2 = getLocation(operand2);
			x86 += "movl "+lop1+", "+destreg+"\n";
			x86 += "cmpl "+lop2+", "+destreg+"\n";
			x86 += "jg "+GT+"\n";
			x86 += "movl $0, "+destreg+"\n";
			x86 += "jmp "+NGT+"\n";
			x86 += GT + ": \n";
			x86 += "movl $1, "+destreg+"\n";
			x86 += NGT +":\n";
		}
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	//////////
	// EQUALS
	else if(op == "=")
	{
		string result, operand1;
		result = instr[2];
		operand1 = instr[3];

		string destreg = getRegister(line_no,result,operand1);
		string lop1 = getLocation(operand1);
		x86 += "movl "+lop1+", "+destreg+"\n";
		if(!isInteger(result))setAddressDescriptor(result, destreg);
		if(!isInteger(result))setRegisterDescriptor(destreg, result);
	}
	//////////
	// ifgoto
	else if(op == "ifgoto")
	{
		string  relop,operand1,operand2,label;
		relop = instr[2];
		operand1 = instr[3];
		operand2 = instr[4];
		label = instr[5];
		string lop1 = getLocation(operand1);
		string lop2 = getLocation(operand2);
		string destreg = getRegister(line_no,operand1);
		if(lop1 == operand1 || lop1[0] == '$'){
			x86 += "movl "+lop1+", "+destreg+"\n";
			if(!isInteger(operand1))setAddressDescriptor(operand1, destreg);
			if(!isInteger(operand1))setRegisterDescriptor(destreg, operand1);
		}
		// Compare
		x86 += "cmpl "+lop2+", "+destreg+"\n";
		// Spilling the registers
		for(auto reg : Registers){
			if(getRegisterDescriptor(reg) != "NULL"){
				// spill this register into memory before jumping
				string var = getRegisterDescriptor(reg);
				x86 += "movl "+reg+", "+var+"\n";
				setRegisterDescriptor(reg, "NULL");
				setAddressDescriptor(var, "mem");
			}
		}
		label = "Node"+label;
		if (relop == "<="){
			x86 += "jle "+label+"\n";
		}
		else if(relop == ">="){
			x86 += "jge "+label+"\n";
		}
		else if(relop == "=="){
			x86 += "je "+label+"\n";
		}
		else if(relop == "<"){
			x86 += "jl "+label+"\n";
		}
		else if(relop == ">"){
			x86 += "jg "+label+"\n";
		}
		else if(relop == "!="){
			x86 += "jne "+label+"\n";
		}
	}
	//////////
	// goto
	else if(op == "goto")
	{
		string  label;
		label = instr[2];
		// Spilling the registers
		for(auto reg : Registers){
			if(getRegisterDescriptor(reg) != "NULL"){
				// spill this register into memory before jumping
				string var = getRegisterDescriptor(reg);
				x86 += "movl "+reg+", "+var+"\n";
				setRegisterDescriptor(reg, "NULL");
				setAddressDescriptor(var, "mem");
			}
		}
		label = "Node"+label;
		x86 += "jmp "+label+"\n";
	}
	//////////
	// call
	else if(op == "call")
	{
		// line, call, funct, return_variable
		string  func,rvar;
		func = instr[2];
		rvar = instr[3];
		// Spilling the registers
		for(auto reg : Registers){
			if(getRegisterDescriptor(reg) != "NULL"){
				// spill this register into memory before jumping
				string var = getRegisterDescriptor(reg);
				x86 += "movl "+reg+", "+var+"\n";
				setRegisterDescriptor(reg, "NULL");
				setAddressDescriptor(var, "mem");
			}
		}
		x86 += "call "+func+"\n";
		// If it is null then the return instr will also have null
		if(rvar != "NULL"){
			string lop = getLocation(rvar);
			x86 += "movl %eax, "+lop+"\n";
		}
	}
	//////////
	// function
	else if(op == "function")
	{
		// line, function, fname
		string  func;
		func = instr[2];
		x86 += ".globl "+func+"\n";
		x86 += ".type "+func+", @function\n";
		x86 += func+":\n";
		x86 += "pushl %ebp\n";
		x86 += "movl %esp, %ebp\n";
	}
	//////////
	// read
	else if(op == "read")
	{
		// line, read, var
		string  var;
		var = instr[2];
		// Spilling the registers
		for(auto reg : Registers){
			if(getRegisterDescriptor(reg) != "NULL"){
				// spill this register into memory before jumping
				string var = getRegisterDescriptor(reg);
				x86 += "movl "+reg+", "+var+"\n";
				setRegisterDescriptor(reg, "NULL");
				setAddressDescriptor(var, "mem");
			}
		}
		x86 += "pushl $"+var+"\n";
		x86 += "pushl $fmt_str_\n";
		x86 += "call scanf\n";
	}
	//////////
	// exit
	else if(op == "exit")
	{
		x86 += "call exit\n";
	}
	//////////
	// array declaration
	else if(op == "array")
	{
		string array_length = instr[2];
		string array_name = instr[3];
		array_list.pb(make_pair(array_name, array_length));
	}
	// Array Access
	else if(op == "member")
	{
		// line, member, variable, array_name, offset
		string variable, aName, offset;
		variable = instr[2];
		aName = instr[3];
		offset = instr[4];
		if(getRegisterDescriptor("%eax") != "NULL"){
			string tp =getRegisterDescriptor("%eax");
			x86 += "movl %eax, "+tp+"\n";
			setRegisterDescriptor("%eax", "NULL");
			setAddressDescriptor(tp, "mem");
		}
		if(getRegisterDescriptor("%ebx") != "NULL"){
			string tp =getRegisterDescriptor("%ebx");
			x86 += "movl %ebx, "+tp+"\n";
			setRegisterDescriptor("%ebx", "NULL");
			setAddressDescriptor(tp, "mem");
		}
		string lop = getLocation(offset);
		x86 += "movl $"+aName+", %ebx\n";
		x86 += "addl "+lop+", %ebx\n";
		x86+= "movl (%ebx), %eax\n";
		setRegisterDescriptor("%eax", variable);
		setAddressDescriptor(variable, "%eax");
	}
	//////////
	// Array Update
	else if(op == "update")
	{
		// line, update, value, array_name, offset
		string value, aName, offset;
		value = instr[2];
		aName = instr[3];
		offset = instr[4];
		if(getRegisterDescriptor("%eax") != "NULL"){
			string tp =getRegisterDescriptor("%eax");
			x86 += "movl %eax, "+tp+"\n";
			setRegisterDescriptor("%eax", "NULL");
			setAddressDescriptor(tp, "mem");
		}
		if(getRegisterDescriptor("%ebx") != "NULL"){
			string tp =getRegisterDescriptor("%ebx");
			x86 += "movl %ebx, "+tp+"\n";
			setRegisterDescriptor("%ebx", "NULL");
			setAddressDescriptor(tp, "mem");
		}
		string lop1 = getLocation(value);
		string lop2 = getLocation(offset);
		x86 += "movl "+lop1+", %eax\n";
		x86 += "movl $"+aName+", %ebx\n";
		x86+= "addl "+lop2+", %ebx\n";
		x86 += "movl %eax, (%ebx)\n";
	}
	//////////
	// return
	else if(op == "return")
	{
		// 1, return , val
		// Spilling the registers
		for(auto reg : Registers){
			if(getRegisterDescriptor(reg) != "NULL"){
				// spill this register into memory before jumping
				string var = getRegisterDescriptor(reg);
				x86 += "movl "+reg+", "+var+"\n";
				setRegisterDescriptor(reg, "NULL");
				setAddressDescriptor(var, "mem");
			}
		}
		string var = instr[2];
		if(var != "NULL"){
			string lop = getLocation(var);
			x86 += "movl "+lop+", %eax\n";
		}
		x86 += "movl %ebp, %esp\n";
		x86 += "popl %ebp\n";
		x86 += "ret\n";
	}
	//////////
	// print
	else if(op == "print")
	{
		//print statement
		string operand = instr[2];
		string lop = getLocation(operand);
		x86 += "pushl "+lop+"\n"+"pushl $fmt_str\n"+"call printf\n";
	}
	return x86;
}

int main(int argc, char** argv){

	char name[30];
	strcpy(name,argv[1]);
	string inputFile = "";
	int len = strlen(name);
	for(int i=0;i<len;i++)
		inputFile+=name[i];
	ifstream fin(inputFile.c_str());

	while(!fin.eof()){
		string OneInstr;
		getline(fin, OneInstr);
		if(OneInstr == "")continue;
		instructions.pb(parse(OneInstr));
	}


	//initialize keywords and operations
	init();

	int NumInstr=(int)(instructions.size());


	leaders.pb(0);

	for(int i=0; i<NumInstr; i++){ 

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
		if(instructions[i][1] == "function"){
			leaders.pb(i);
		}
		if(instructions[i][1] == "call"){
			if(i+1 < NumInstr)leaders.pb(i+1);
		}
	}
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

	//remove functions from the list of variables
	for(int i=0;i<NumInstr;i++)
	{
		if(instructions[i].size()>1){
			if(instructions[i][1] == "function")
			{
				string funcname = instructions[i][2];
				all_variables.erase(funcname);
			}
			if(instructions[i][1] == "array"){
				string aName= instructions[i][2];
				if(all_variables.find(aName)!=all_variables.end())
				all_variables.erase(aName); //#arjun
				aName= instructions[i][3];
				if(all_variables.find(aName)!=all_variables.end())
				all_variables.erase(aName); //#arjun
			}
		}
	}


	sort(leaders.begin(), leaders.end());
	leaders.erase(unique(leaders.begin(), leaders.end()), leaders.end());
	int NumLeaders = (int)(leaders.size());
	for(int i=0; i<NumLeaders-1; i++){
		nodes.pb(mp(leaders[i], leaders[i+1]-1));
	}
	nodes.pb(mp(leaders[NumLeaders-1], NumInstr-1));
	int NumNodes = (int)(nodes.size());

	NextUse.resize(NumInstr);

	for(int nd=0; nd<NumNodes; nd++){
		for(auto idx : all_variables)
			SymbolTable[idx]=mp(INF,"Dead"); //check
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
					SymbolTable[a]=mp(INF, "Dead");
				if(setfind(all_variables,b))
					SymbolTable[b]=mp(instr, "Live");
			}
		}
	}
	AssemblyCode="";
	DataSection=".section .data\n";
	for(auto var : all_variables){
		DataSection+=var+":\n.int 0\n";
	}
	DataSection+="fmt_str:\n.ascii \"%d\\n\\0\"\n";
	DataSection+="fmt_str_:\n.ascii \"%d\"\n";
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

		for(int instr=nodes[nd].X; instr<=nodes[nd].Y; instr++){
			TextSection+=genx86(instructions[instr]);
		}
		for(auto reg : Registers){
			if(getRegisterDescriptor(reg) != "NULL"){
				// spill this register into memory before jumping
				string var = getRegisterDescriptor(reg);
				TextSection += "movl "+reg+", "+var+"\n";
				setRegisterDescriptor(reg, "NULL");
				setAddressDescriptor(var, "mem");
			}
		}
	}
	// Adding array declaration
	for(auto ite : array_list){
		DataSection += ite.X+":\n.int ";
		int ilen=stringToInt(ite.Y);
		for(int i=0;i<ilen-1;i++){
			DataSection += "0, ";
		}
		DataSection += "0\n";
	}
	AssemblyCode+=DataSection+BssSection+TextSection;
	//string outputFile = inputFile+".s";
	//ofstream fout(outputFile.c_str());
	cout<<AssemblyCode<<endl;
	//fout.close();
	return 0;
}
