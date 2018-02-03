#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define vs vector<string> 
#define setfind(a,b) a.find(b)!=a.end()
#define X first
#define Y second

/*
 *Note: The first column in IR i.e, line numbers is 0-indexed
 */

const int INF=1e9;

vector<vector<string> > instructions;

set<string> all_variables;

vector<int> leaders;
vector<pair<int,int> > nodes;

set<string> keywords;//these are the reserved words used for the three address words.
set<string> ops_mth; // mathematical operators
set<string> ops_rel; // relational operators

vector<map<string,int> > NextUse;

int stringToInt(string s)
{
	int ret=0;
	for(int i=0;i<s.size();i++)
	{
		ret=ret*10+(s[i]-'0');
	}
	return ret;
}

void init()
{
	keywords.insert("ifgoto");
	keywords.insert("goto");
	keywords.insert("return");
	keywords.insert("call");
	keywords.insert("print");
	keywords.insert("label");
	keywords.insert("<=");
	keywords.insert(">=");
	keywords.insert("==");
	keywords.insert(">");
	keywords.insert("<");
	keywords.insert("!=");
	keywords.insert("=");
	keywords.insert("function");
	keywords.insert("exit");

	ops_mth.insert("+");
	ops_mth.insert("-");
	ops_mth.insert("*");
	ops_mth.insert("/");
	ops_mth.insert("%");
	
	ops_rel.insert("&&");
	ops_rel.insert("||");
	ops_rel.insert("~");

	for(auto i : ops_mth)
		keywords.insert(i);

	for(auto i : ops_rel)
		keywords.insert(i);
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
	for(int i = 0 ; i < s.size(); i++)
		if(!('0'<=s[i]&&s[i]<='9'))
			return false;
	return true;
}

int main(){
	ifstream fin("test");
	while(!fin.eof()){
		string OneInstr;
		getline(fin, OneInstr);
		if(OneInstr == "")continue;
		instructions.pb(parse(OneInstr));
	}


	//initialize keywords and operations
	init();

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
		if(instructions[i][1] == "label"){
			leaders.pb(i);
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
					all_variables.insert("idx");
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
		map<string,int> cur;
		for(auto idx : all_variables)
			cur[idx]=INF;
		for(int instr=nodes[nd].Y; instr>=nodes[nd].X; instr--){
			vector<string> InstrLine = instructions[instr];
			string Operator = InstrLine[1];
			NextUse[instr] = cur;
			if(ops_mth.find(Operator) != ops_mth.end())
			{
				//math operator
				string a,b,c;//a = b op c
				assert(InstrLine.size() == 5);
				a = InstrLine[2];
				b = InstrLine[3];
				c = InstrLine[4];
				if(setfind(all_variables,a))
					cur[a]=INF;
				if(setfind(all_variables,b))
					cur[b]=instr;
				if(setfind(all_variables,c))
					cur[c]=instr;
			}
			else if(Operator == "ifgoto")
			{
				string a = InstrLine[3];
				string b = InstrLine[4];
				if(setfind(all_variables,a))
					cur[a]=instr;
				if(setfind(all_variables,b))
					cur[b]=instr;
			}
			else if(Operator == "print")
			{
				string a = InstrLine[2];
				if(setfind(all_variables,a))
					cur[a] = instr;
			}
			else if(Operator == "=")
			{
				string a = InstrLine[2];
				string b = InstrLine[3];
				if(setfind(all_variables,a))
					cur[a]=INF;
				if(setfind(all_variables,b))
					cur[b]=instr;
			}
		}
	}
	return 0;
}
