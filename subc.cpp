#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <fstream>

using namespace std;

string read_file(const char* filename) { 
	std::ifstream in(filename);
	if (in.is_open()) {
		std::string contents((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());
		return contents;
	}
	return "null";
}

void printTokens(vector<string>& tokens, vector<string>& types) {
	for (int i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << "-" << types[i] << endl;
	}
	cout << tokens.size() << endl;
}

vector<string> tlex(char* text, int sz) {
	int last = 0;
	int idx = 0;
	vector<string> tokens;
	vector<string> types;

	while (idx < sz) {
		if (text[idx] == '.') {
			int start = idx;
			if (text[idx + 1] == '.') {
				idx++;
				string raw(text, idx + 1);
				string tok = raw.substr(start, 2);
				tokens.push_back(tok);
				types.push_back("caseexpression");
			}
			else {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("period");
			}
		}
		if (text[idx] == ' ' || '\t' || '\n') { //Whitespace - Skip

		}
		if (text[idx] == '{') { //Comment - Skip
			while (text[idx] != '}') {
				idx++;
			}
		}
		if (text[idx] == '#') { //Comment - Skip
			while (text[idx] != '\n') {
				idx++;
			}
		}
		if (isdigit(text[idx])) {
			int start = idx;
			while (isdigit(text[idx])) {
				idx++;
			}
			string raw(text, idx);
			string tok = raw.substr(start, idx);
			tokens.push_back(tok);
			types.push_back("integer");
			idx--;//////////////////////
		}
		if (text[idx] == 39) {
			if (text[idx + 2] == 39) {
				string tok(1, text[idx + 1]);
				tokens.push_back(tok);
				types.push_back("char");
			}
			else {
				cout << "error" << endl;
			}
			idx = idx + 2;
		}
		if (text[idx] == 34) {
			int start = idx + 1;
			idx++;
			while (text[idx] != 34) {
				idx++;
			}
			string raw(text, idx - 1);
			string tok = raw.substr(start, idx - 1);
			tokens.push_back(tok);
			types.push_back("string");
		}
		if (isalpha(text[idx]) || text[idx] == 95) {
			int start = idx;
			while (isalpha(text[idx]) || isdigit(text[idx]) || text[idx] == 95) {
				idx++;
			}
			string raw(text, idx);
			string tok = raw.substr(start, idx);
			tokens.push_back(tok);
			if (tok == "program") {
				types.push_back("program");
			}
			else if (tok == "var") {
				types.push_back("var");
			}
			else if (tok == "const") {
				types.push_back("const");
			}
			else if (tok == "type") {
				types.push_back("type");
			}
			else if (tok == "function") {
				types.push_back("function");
			}
			else if (tok == "return") {
				types.push_back("return");
			}
			else if (tok == "begin") {
				types.push_back("begin");
			}
			else if (tok == "end") {
				types.push_back("end");
			}
			else if (tok == "output") {
				types.push_back("output");
			}
			else if (tok == "if") {
				types.push_back("if");
			}
			else if (tok == "then") {
				types.push_back("then");
			}
			else if (tok == "else") {
				types.push_back("else");
			}
			else if (tok == "while") {
				types.push_back("while");
			}
			else if (tok == "do") {
				types.push_back("do");
			}
			else if (tok == "case") {
				types.push_back("case");
			}
			else if (tok == "of") {
				types.push_back("of");
			}
			else if (tok == "otherwise") {
				types.push_back("otherwise");
			}
			else if (tok == "repeat") {
				types.push_back("repeat");
			}
			else if (tok == "for") {
				types.push_back("for");
			}
			else if (tok == "until") {
				types.push_back("until");
			}
			else if (tok == "loop") {
				types.push_back("loop");
			}
			else if (tok == "pool") {
				types.push_back("pool");
			}
			else if (tok == "exit") {
				types.push_back("exit");
			}
			else if (tok == "mod") {
				types.push_back("mod");
			}
			else if (tok == "and") {
				types.push_back("and");
			}
			else if (tok == "or") {
				types.push_back("or");
			}
			else if (tok == "not") {
				types.push_back("not");
			}
			else if (tok == "not") {
				types.push_back("not");
			}
			else if (tok == "read") {
				types.push_back("read");
			}
			else if (tok == "succ") {
				types.push_back("succ");
			}
			else if (tok == "pred") {
				types.push_back("pred");
			}
			else if (tok == "chr") {
				types.push_back("chr");
			}
			else if (tok == "ord") {
				types.push_back("ord");
			}
			else if (tok == "eof") {
				types.push_back("eof");
			}
			else {
				types.push_back("identifier");
			}
			idx--;
		}
		if (text[idx] == ';') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("semicolon");
		}
		if (text[idx] == ',') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("comma");
		}
		if (text[idx] == ':') {
			int start = idx;
			if (text[idx + 1] == '=') {
				idx++;
				if (text[idx + 1] == ':') {
					idx++;
					types.push_back("swap");
				}
				else {
					types.push_back("assignmentoperator");
				}
				string raw(text, idx + 1);
				string tok = raw.substr(start, idx + 1);
				tokens.push_back(tok);
			}
			else {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("colon");
			}
		}
		if (text[idx] == '(') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("openingbracket");
		}
		if (text[idx] == ')') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("closingbracket");
		}
		if (text[idx] == '+') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("plus");
		}
		if (text[idx] == '-') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("minus");
		}
		if (text[idx] == '*') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("multiply");
		}
		if (text[idx] == '/') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("divide");
		}
		if (text[idx] == '=') {
			if (text[idx - 1] != ':') {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("equal");
			}
		}
		if (text[idx] == '>') {
			int start = idx;
			if (text[idx + 1] == '=') {
				idx++;
				string raw(text, idx);
				string tok = raw.substr(start, idx);
				tokens.push_back(tok);
				types.push_back("greaterequal");
			}
			else {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("greater");
			}
		}
		if (text[idx] == '<') {
			int start = idx;
			if (text[idx + 1] == '=') {
				idx++;
				string raw(text, idx);
				string tok = raw.substr(start, idx);
				tokens.push_back(tok);
				types.push_back("lessequal");
			}
			else if (text[idx + 1] == '>') {
				idx++;
				string raw(text, idx);
				string tok = raw.substr(start, idx);
				tokens.push_back(tok);
				types.push_back("notequal");
			}
			else {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("less");
			}
		}
		idx++;
	}

	return types;
}

vector<string> lex(char* text, int sz) {
	int last = 0;
	int idx = 0;
	vector<string> tokens;
	vector<string> types;

	while (idx < sz) { 
		if (text[idx] == '.') { 
			int start = idx;
			//cout << text[idx] << text[idx + 1] << endl;
			if (text[idx + 1] == '.') {
				idx++;
				string tok = "..";
				tokens.push_back(tok);
				types.push_back("caseexpression");
			}
			else {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("period");
			}
		}
		if (text[idx] == ' ' || '\t' || '\n') { //Whitespace - Skip
			
		}
		if (text[idx] == '{') { //Comment - Skip
			while (text[idx] != '}') {
				idx++;
			}
		}
		if (text[idx] == '#') { //Comment - Skip
			while (text[idx] != '\n') {
				idx++;
			}
		}
		if (isdigit(text[idx])) { 
			int start = idx;
			while (isdigit(text[idx])) {
				idx++;
			}
			string raw(text, idx);
			string tok = raw.substr(start, idx);
			tokens.push_back(tok);
			types.push_back("integer");
			idx--;
		}
		if (text[idx] == 39) { 
			if(text[idx+2] == 39) {
				string tok(1, text[idx + 1]);
				string z = "'";
				z.append(tok);
				z.append("'");
				tokens.push_back(z);
				types.push_back("char");
			}
			else {
				cout << "error" << endl;
			}
			idx = idx + 2;
		}
		if (text[idx] == 34) { 
			int start = idx+1;
			idx++;
			while (text[idx] != 34) {
				idx++;
			}
			string raw(text, idx-1);
			string tok = raw.substr(start, idx-1);
			tokens.push_back(tok);
			types.push_back("string");
		}
		if (isalpha(text[idx]) || text[idx] == 95) { 
			int start = idx;
			while (isalpha(text[idx]) || isdigit(text[idx]) || text[idx] == 95) {
				idx++;
			}
			string raw(text, idx);
			string tok = raw.substr(start, idx);
			tokens.push_back(tok);
			types.push_back("identifier");
			idx--;
		}
		if (text[idx] == ';') { 
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("semicolon");
		}
		if (text[idx] == ',') { 
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("comma");
		}
		if (text[idx] == ':') { 
			int start = idx;
			if (text[idx+1] == '=') {
				idx++;
				if (text[idx+1] == ':') {
					idx++;
					types.push_back("swap");
				}
				else {
					types.push_back("assignmentoperator");
				}
				string raw(text, idx+1);
				string tok = raw.substr(start, idx+1);
				tokens.push_back(tok);
			}
			else {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("colon");
			}
		}
		if (text[idx] == '(') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("openingbracket");
		}
		if (text[idx] == ')') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("closingbracket");
		}
		if (text[idx] == '+') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("plus");
		}
		if (text[idx] == '-') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("minus");
		}
		if (text[idx] == '*') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("multiply");
		}
		if (text[idx] == '/') {
			string tok(1, text[idx]);
			tokens.push_back(tok);
			types.push_back("divide");
		}
		if (text[idx] == '=') {
			if (text[idx - 1] != ':') {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("equal");
			}
		}
		if (text[idx] == '>') {
			int start = idx;
			if (text[idx + 1] == '=') {
				idx++;
				string raw(text, idx+1);
				string tok = raw.substr(start, idx+1);
				tokens.push_back(tok);
				types.push_back("greaterequal");
			}
			else {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("greater");
			}
		}
		if (text[idx] == '<') {
			int start = idx;
			if (text[idx + 1] == '=') {
				idx++;
				string raw(text, idx+1);
				string tok = raw.substr(start, idx+1);
				tokens.push_back(tok);
				types.push_back("lessequal");
			}
			else if (text[idx + 1] == '>') {
				idx++;
				string raw(text, idx+1);
				string tok = raw.substr(start, idx+1);
				tokens.push_back(tok);
				types.push_back("notequal");
			}
			else {
				string tok(1, text[idx]);
				tokens.push_back(tok);
				types.push_back("less");
			}
		}
		idx++;
	}

	return tokens;
}

string buildTree(string token, int x, int j) {
	string z;
	for (int i = 0; i < j; i++) {
		z.append(". ");
	}
	z.append(token);
	z.append("(");
	z.append(to_string(x));
	z.append(")");
	z.append("\n");
	return z;
}

string adjust(string x) {
	string z;
	int start = 0;
	for (int i = 0; i < x.size(); i++) {
		if (x[i] == '\n') {
			string temp = ". ";
			temp.append(x.substr(start, i - start));
			temp.append("\n");
			start = i + 1;
			z.append(temp);
		}
	}
	return z;
}

////////////////////////////////////////////////////////

string parse(vector<string> tokens, vector<string> types, int& i, int j);
string Consts(vector<string> tokens, vector<string> types, int& i, int j);
string Const(vector<string> tokens, vector<string> types, int& i, int j);
string ConstValue(vector<string> tokens, vector<string> types, int& i, int j);
string Types(vector<string> tokens, vector<string> types, int& i, int j);
string Type(vector<string> tokens, vector<string> types, int& i, int j);
string LitList(vector<string> tokens, vector<string> types, int& i, int j);
string SubProgs(vector<string> tokens, vector<string> types, int& i, int j);
string Fcn(vector<string> tokens, vector<string> types, int& i, int j);
string Params(vector<string> tokens, vector<string> types, int& i, int j);
string Dclns(vector<string> tokens, vector<string> types, int& i, int j);
string Dcln(vector<string> tokens, vector<string> types, int& i, int j);
string Body(vector<string> tokens, vector<string> types, int& i, int j);
string Statement(vector<string> tokens, vector<string> types, int& i, int j);
string OutExp(vector<string> tokens, vector<string> types, int& i, int j);
string StringNode(vector<string> tokens, vector<string> types, int& i, int j);
string Caseclauses(vector<string> tokens, vector<string> types, int& i, int j, int&x);
string Caseclause(vector<string> tokens, vector<string> types, int& i, int j);
string CaseExpression(vector<string> tokens, vector<string> types, int& i, int j);
string OtherwiseClause(vector<string> tokens, vector<string> types, int& i, int j);
string Assignment(vector<string> tokens, vector<string> types, int& i, int j);
string ForStat(vector<string> tokens, vector<string> types, int& i, int j);
string ForExp(vector<string> tokens, vector<string> types, int& i, int j);
string Expression(vector<string> tokens, vector<string> types, int& i, int j);
string Term(vector<string> tokens, vector<string> types, int& i, int j);
string Factor(vector<string> tokens, vector<string> types, int& i, int j);
string Primary(vector<string> tokens, vector<string> types, int& i, int j);
string Name(vector<string> tokens, vector<string> types, int& i, int j);

////////////////////////////////////////////////////////

string parse(vector<string> tokens, vector<string> types) {
	int i = 0;
	int j = 0;
	string tree;
	if (tokens[i] == "program") {
		i++;
		tree = buildTree("program", 7, j);
		tree.append(Name(tokens, types, i, j + 1));
		if (tokens[i] == ":") {
			i++;
			tree.append(Consts(tokens, types, i, j + 1));
			tree.append(Types(tokens, types, i, j + 1));
			tree.append(Dclns(tokens, types, i, j + 1));
			tree.append(SubProgs(tokens, types, i, j + 1));
			tree.append(Body(tokens, types, i, j + 1));
			tree.append(Name(tokens, types, i, j + 1));
		}
		if (tokens[i] == ".") {
			i++;
		}
	}
	return tree;
}

string Consts(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	if (types[i] == "const") {
		i++;
		l.append(Const(tokens, types, i, j + 1));
		x++;
		while (tokens[i] == ",") {
			l.append(Const(tokens, types, i, j + 1));
			x++;
		}
		if (tokens[i] == ";") {
			i++;
		}
		tree = buildTree("consts", x, j);
		tree.append(l);
	}
	else {
		tree = buildTree("consts", 0, j);
	}
	return tree;
}

string Const(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	tree = buildTree("const", 2, j);
	tree.append(Name(tokens, types, i, j + 1));
	if (tokens[i] == "=") {
		i++;
		tree.append(ConstValue(tokens, types, i, j + 1));
	}
	return tree;
}

string ConstValue(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	if (types[i] == "integer") {
		tree = buildTree("<integer>", 1, j);
		tree.append(buildTree(tokens[i], 0, j + 1));
		i++;
	}
	else if (types[i] == "char") {
		tree = buildTree("<char>", 1, j);
		string chr = "'";
		chr.append(tokens[i]);
		chr.append("'");
		tree.append(buildTree(chr, 0, j + 1));
		i++;
	}
	else if (types[i] == "identifier") {
		tree = buildTree("<identifier>", 1, j);
		tree.append(buildTree(tokens[i], 0, j + 1));
		i++;
	}
	return tree;
}

string Types(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	if (tokens[i] == "type") {
		i++;
		while (types[i] == "identifier") {
			l.append(Type(tokens, types, i, j + 1));
			x++;
			if (tokens[i] == ";") {
				i++;
			}
		}
		tree = buildTree("types", x, j);
		tree.append(l);
	}
	else {
		tree = buildTree("types", 0, j);
	}
	return tree;
}

string Type(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	tree = buildTree("type", 2, j); 
	tree.append(Name(tokens, types, i, j + 1));
	if (tokens[i] == "=") {
		i++;
		tree.append(LitList(tokens, types, i, j + 1));
	}
	return tree;
}

string LitList(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	//cout << l << " - " << tokens[i] << endl;
	if (tokens[i] == "(") {
		i++;
		l.append(Name(tokens, types, i, j + 1));
		x++;
		
		while (tokens[i] == ",") {
			i++;
			l.append(Name(tokens, types, i, j + 1));
			x++;
			if (tokens[i] == ")") {
				i++;
				break;
			}
		}
		tree = buildTree("lit", x, j);
		tree.append(l);
	}
	else {
		tree = buildTree("lit", 0, j);
	}
	return tree;
}

string SubProgs(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	while (tokens[i] == "function") {
		l.append(Fcn(tokens, types, i, j + 1));
		x++;
	}
	tree = buildTree("subprogs", x, j);
	tree.append(l);
	return tree;
}

string Fcn(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	tree = buildTree("fcn", 8, j);
	if (tokens[i] == "function") {
		i++;
		tree.append(Name(tokens, types, i, j + 1));
		if (tokens[i] == "(") {
			i++;
			tree.append(Params(tokens, types, i, j + 1));
			if (tokens[i] == ")") {
				i++;
				if (tokens[i] == ":") {
					i++;
					tree.append(Name(tokens, types, i, j + 1));
					if (tokens[i] == ";") {
						i++;
						tree.append(Consts(tokens, types, i, j + 1));
						tree.append(Types(tokens, types, i, j + 1));
						tree.append(Dclns(tokens, types, i, j + 1));
						tree.append(Body(tokens, types, i, j + 1));
						tree.append(Name(tokens, types, i, j + 1));
						if (tokens[i] == ";") {
							i++;
						}
					}
				}
			}
		}
	}
	return tree;
}

string Params(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	while (types[i] == "identifier") {
		l.append(Dcln(tokens, types, i, j + 1));
		x++;
		if (tokens[i] == ";") {
			i++;
		}
	}
	tree = buildTree("params", x, j);
	tree.append(l);
	return tree;
}

string Dclns(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;

	if (tokens[i] == "var") {
		i++;
		while (types[i] == "identifier") {
			l.append(Dcln(tokens, types, i, j + 1));
			x++;
			if (tokens[i] == ";") {
				i++;
			}
		}
		tree = buildTree("dclns", x, j);
		tree.append(l);
	}
	else {
		tree = buildTree("dclns", 0, j);
	}
	return tree;
}

string Dcln(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	while (types[i] == "identifier") {
		l.append(Name(tokens, types, i, j + 1));
		x++;
		if (tokens[i] == ",") {
			i++;
		}
	}
	if (tokens[i] == ":") {
		i++;
		l.append(Name(tokens, types, i, j + 1));
		x++;
	}
	tree = buildTree("var", x, j);
	tree.append(l);
	return tree;
}

string Body(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	if (tokens[i] == "begin") {
		i++;
		l.append(Statement(tokens, types, i, j + 1));
		x++;
		while (tokens[i] == ";") {
			i++;
			l.append(Statement(tokens, types, i, j + 1));
			x++;
			if (tokens[i] == "end") {
				break;
			}
		}
		if (tokens[i] == "end") {
			i++;
		}
		//cout << i << " " << tokens[i - 1] << " " << tokens[i] << " " << tokens[i + 1] << endl;
		tree = buildTree("block", x, j);
		tree.append(l);
	}
	return tree;
}

string Statement(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	if (types[i] == "identifier") {
		tree = Assignment(tokens, types, i, j);
	}
	else if (types[i] == "output") {
		i++;
		if (tokens[i] == "(") {
			i++;
			l.append(OutExp(tokens, types, i, j + 1));
			x++;
			while (tokens[i] == ",") {
				i++;
				l.append(OutExp(tokens, types, i, j + 1));
				x++;
				if (tokens[i] == ")") {
					i++;
					break;
				}
			}
			if (tokens[i] == ")") {
				i++;
			}
			//cout << i << " - " << tokens[i] << endl;
			tree = buildTree("output", x, j);
			tree.append(l);
		}
	}
	else if (types[i] == "if") {
		i++;
		int x = 0;
		string l;
		l = Expression(tokens, types, i, j + 1);
		x++;
		if (tokens[i] == "then") {
			i++;
			l.append(Statement(tokens, types, i, j + 1));
			//cout << i << " - " << tokens[i] << endl;
			x++;
			if (tokens[i] == "else") {
				i++;
				l.append(Statement(tokens, types, i, j + 1));
				x++;
			}
		}
		tree = buildTree("if", x, j);
		tree.append(l);
	}
	else if (types[i] == "while") {
		i++;
		tree = buildTree("while", 2, j);
		tree.append(Expression(tokens, types, i, j+1));
		if (types[i] == "do") {
			i++;
			tree.append(Statement(tokens, types, i, j + 1));
		}
	}
	else if (types[i] == "repeat") {
		string l;
		int x = 0;
		if (tokens[i] == "repeat") {
			i++;
			l.append(Statement(tokens, types, i, j + 1));
			x++;
			while (tokens[i] == ";") {
				i++;
				if (tokens[i] == "until") {
					i++;
					break;
				}
				l.append(Statement(tokens, types, i, j + 1));
				x++;
			}
			if (tokens[i] == "until") {
				i++;
			}
			l.append(Expression(tokens, types, i, j + 1));
			x++;
			tree = buildTree("repeat", x, j);
			tree.append(l);
		}
	}
	else if (types[i] == "for") {
		i++;
		tree = buildTree("for", 4, j);
		if (tokens[i] == "(") {
			i++;
			tree.append(ForStat(tokens, types, i, j + 1));
			if (tokens[i] == ";") {
				i++;
				//cout << tree << " - " << tokens[i] << endl;/////////////////////
				tree.append(ForExp(tokens, types, i, j + 1));
				if (tokens[i] == ";") {
					i++;
					tree.append(ForStat(tokens, types, i, j + 1));
					if (tokens[i] == ")") {
						i++;
						tree.append(Statement(tokens, types, i, j + 1));
					}
				}
			}
		}
	}
	else if (types[i] == "loop") {
		i++;
		string l;
		int x = 0;
		l.append(Statement(tokens, types, i, j + 1));
		x++;
		while (tokens[i] == ";") {
			i++;
			if (tokens[i] == "pool") {
				i++;
				break;
			}
			l.append(Statement(tokens, types, i, j + 1));
			x++;
		}
		if (tokens[i] == "pool") {
			i++;
		}
		tree = buildTree("loop", x, j);
		tree.append(l);
	}
	else if (types[i] == "case") {
		i++;
		int x = 0;
		string l;
		l.append(Expression(tokens, types, i, j + 1));
		x++;
		if (tokens[i] == "of") {
			i++;
			//cout << i << tokens[i] << endl;
			l.append(Caseclauses(tokens, types, i, j + 1, x));
			if (tokens[i] == "otherwise") {
				l.append(OtherwiseClause(tokens, types, i, j + 1));
				x++;
			}
			if (tokens[i] == "end") {
				i++;
			}
			tree = buildTree("case", x, j);
			tree.append(l);
		}
	}
	else if (types[i] == "read") {
		i++;
		string l;
		int x = 0;
		if (tokens[i] == "(") {
			i++;
			l.append(Name(tokens, types, i, j + 1));
			x++;
			while (tokens[i] == ",") {
				i++;
				l.append(Name(tokens, types, i, j + 1));
				x++;
				if (tokens[i] == ")") {
					i++;
					break;
				}
			}
			if (tokens[i] == ")") {
				i++;
			}
			tree = buildTree("read", x, j);
			tree.append(l);
		}
	}
	else if (types[i] == "exit") {
		i++;
		tree = buildTree("exit", 0, j);
	}
	else if (types[i] == "return") {
		i++;
		tree = buildTree("return", 1, j);
		tree.append(Expression(tokens, types, i, j + 1));
	}
	else if (types[i] == "begin") {
		tree = Body(tokens, types, i, j);
	}
	else {
		tree = buildTree("<null>", 0, j);
	}
	return tree;
}

string OutExp(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	if (types[i] == "string") {
		tree = buildTree("string", 1, j);
		tree.append(StringNode(tokens, types, i, j + 1));
	}
	else {
		tree = buildTree("integer", 1, j);
		tree.append(Expression(tokens, types, i, j + 1));
	}
	return tree;
}

string StringNode(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	if (types[i] == "string") {
		tree = buildTree("<string>", 1, j);
		tree.append(buildTree(tokens[i], 0, j + 1));
		i++;
	}
	return tree;
}

string Caseclauses(vector<string> tokens, vector<string> types, int& i, int j, int&x) {
	string tree;
	tree.append(Caseclause(tokens, types, i, j));
	x++;
	while (tokens[i] == ";") {
		i++;
		if (tokens[i] == "end" || tokens[i] == "otherwise") {
			break;
		}
		tree.append(Caseclause(tokens, types, i, j));
		//cout << "hey" << i << " - " << tokens[i] << endl;
		x++;
	}
	return tree;
}

string Caseclause(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	l.append(CaseExpression(tokens, types, i, j + 1));
	x++;
	while (tokens[i] == ",") {
		l.append(CaseExpression(tokens, types, i, j + 1));
		x++;
	}
	if (tokens[i] == ":") {
		i++;
		l.append(Statement(tokens, types, i, j + 1));
		x++;
	}
	tree = buildTree("case_clause", x, j);
	tree.append(l);
	//cout << "there" << i << " - " << tokens[i] << endl;
	return tree;
}

string CaseExpression(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l = ConstValue(tokens, types, i, j);
	if (tokens[i] == "..") {
		i++;
		tree = buildTree("..", 2, j);
		l = adjust(l);
		tree.append(l);
		tree.append(ConstValue(tokens, types, i, j + 1));
	}
	else {
		tree.append(l);
	}
	return tree;
}

string OtherwiseClause(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	//cout << i << " - " << tokens[i] << endl;
	if (tokens[i] == "otherwise") {
		i++;
		tree = buildTree("otherwise", 1, j);
		tree.append(Statement(tokens, types, i, j + 1));
	}
	else if (tokens[i] == ";") {
		i++;
	}
	return tree;
}

string Assignment(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	l.append(Name(tokens, types, i, j + 1));
	if (tokens[i] == ":=") {
		i++;
		tree = buildTree("assign", 2, j);
		l.append(Expression(tokens, types, i, j + 1));
	}
	else if (tokens[i] == ":=:") {
		i++;
		tree = buildTree("swap", 2, j);
		l.append(Name(tokens, types, i, j + 1));
	}
	tree.append(l);
	return tree;
}

string ForStat(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	if (types[i] == "identifier") {
		tree = Assignment(tokens, types, i, j);
	}
	else {
		tree = buildTree("<null>", 0, j);
	}
	return tree;
}

string ForExp(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	tree = Expression(tokens, types, i, j);
	//cout << i << " - " << tokens[i] << endl;
	//tree.append(buildTree("<true>", 0, j));
	return tree;
}

string Expression(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	l = Term(tokens, types, i, j);
	if (tokens[i] == "<=" || tokens[i] == "<" || tokens[i] == ">=" || tokens[i] == ">" || tokens[i] == "=" || tokens[i] == "<>") {
		if (tokens[i] == "<=") {
			tree = buildTree("<=", 2, j);
		}
		else if (tokens[i] == "<") {
			tree = buildTree("<", 2, j);
		}
		else if (tokens[i] == ">=") {
			tree = buildTree(">=", 2, j);
		}
		else if (tokens[i] == ">") {
			tree = buildTree(">", 2, j);
		}
		else if (tokens[i] == "=") {
			tree = buildTree("=", 2, j);
		}
		else if (tokens[i] == "<>") {
			tree = buildTree("<>", 2, j);
		}
		i++;
		l = adjust(l);
		tree.append(l);
		tree.append(Term(tokens, types, i, j + 1));
	}
	else {
		tree.append(l);
	}
	return tree;
}

string Term(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	string z;
	l = Factor(tokens, types, i, j);
	if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "or") {
		if (tokens[i] == "+") {
			tree = buildTree("+", 2, j);
		}
		else if (tokens[i] == "-") {
			tree = buildTree("-", 2, j);
		}
		else if (tokens[i] == "or") {
			tree = buildTree("or", 2, j);
		}
		i++;
		l = adjust(l);
		tree.append(l);
		tree.append(Factor(tokens, types, i, j+1));
		//while loop goes here
		while (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "or") {
			if (tokens[i] == "+") {
				z = buildTree("+", 2, j);
			}
			else if (tokens[i] == "-") {
				z = buildTree("-", 2, j);
			}
			else if (tokens[i] == "or") {
				z = buildTree("or", 2, j);
			}
			i++;
			tree = adjust(tree);
			z.append(tree);
			z.append(Factor(tokens, types, i, j + 1));
			tree = z;
		}
	}
	else {
		tree.append(l);
	}
	return tree;
}

string Factor(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	l = Primary(tokens, types, i, j);
	if (tokens[i] == "*" || tokens[i] == "/" || tokens[i] == "and" || tokens[i] == "mod") {
		if (tokens[i] == "*") {
			tree = buildTree("*", 2, j);
		}
		else if (tokens[i] == "/") {
			tree = buildTree("/", 2, j);
		}
		else if (tokens[i] == "and") {
			tree = buildTree("and", 2, j);
		}
		else if (tokens[i] == "mod") {
			tree = buildTree("mod", 2, j);
		}
		i++;
		l = adjust(l);
		tree.append(l);
		tree.append(Primary(tokens, types, i, j+1));
	}
	else {
		tree.append(l);
	}
	return tree;
}

string Primary(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	string l;
	int x = 0;
	if (tokens[i] == "-") {
		i++;
		tree = buildTree("-", 1, j);
		tree.append(Primary(tokens, types, i, j + 1));
	}
	else if (tokens[i] == "+") {
		i++;
		tree = buildTree("+", 1, j);
		tree.append(Primary(tokens, types, i, j + 1));
	}
	else if (tokens[i] == "not") {
		i++;
		tree = buildTree("not", 1, j);
		tree.append(Primary(tokens, types, i, j + 1));
	}
	else if (tokens[i] == "eof") {
		i++;
		tree = buildTree("eof", 0, j);
	}
	else if (types[i] == "identifier") {
		string l;
		int x = 0;
		l = Name(tokens, types, i, j);
		x++;
		if (tokens[i] == "(") {
			i++;
			l = adjust(l);
			l.append(Expression(tokens, types, i, j + 1));
			x++;
			while (tokens[i] == ",") {
				i++;
				l.append(Expression(tokens, types, i, j + 1));
				x++;
				if (tokens[i] == ")") {
					i++;
					break;
				}
			}
			if (tokens[i] == ")") {
				i++;
			}
			tree = buildTree("call", x, j);
			tree.append(l);
		}
		else {
			tree.append(l);
		}
	}
	else if (types[i] == "char") {
		tree = buildTree("<char>", 1, j);
		tree.append(buildTree(tokens[i], 0, j + 1));
		i++;
	}
	else if (types[i] == "integer") {
		tree = buildTree("<integer>", 1, j);
		tree.append(buildTree(tokens[i], 0, j + 1));
		i++;
	}
	else if (tokens[i] == "(") {
		i++;
		tree.append(Expression(tokens, types, i, j));
		if (tokens[i] == ")") {
			i++;
		}
	}
	else if (tokens[i] == "succ") {
		i++;
		tree = buildTree("succ", 1, j);
		if (tokens[i] == "(") {
			i++;
			tree.append(Expression(tokens, types, i, j + 1));
			if (tokens[i] == ")") {
				i++;
			}
		}
	}
	else if (tokens[i] == "pred") {
		i++;
		tree = buildTree("pred", 1, j);
		if (tokens[i] == "(") {
			i++;
			tree.append(Expression(tokens, types, i, j + 1));
			if (tokens[i] == ")") {
				i++;
			}
		}
	}
	else if (tokens[i] == "chr") {
		i++;
		tree = buildTree("chr", 1, j);
		if (tokens[i] == "(") {
			i++;
			tree.append(Expression(tokens, types, i, j + 1));
			if (tokens[i] == ")") {
				i++;
			}
		}
	}
	else if (tokens[i] == "ord") {
		i++;
		tree = buildTree("ord", 1, j);
		if (tokens[i] == "(") {
			i++;
			tree.append(Expression(tokens, types, i, j + 1));
			if (tokens[i] == ")") {
				i++;
			}
		}
	}

	return tree;
}

string Name(vector<string> tokens, vector<string> types, int& i, int j) {
	string tree;
	if (types[i] == "identifier") {
		tree = buildTree("<identifier>", 1, j);
		tree.append(buildTree(tokens[i], 0, j + 1));
		i++;
	}
	return tree;
}

///////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
	if (argc > 1 ) {
		string tmp = argv[1];
		if (tmp == "-ast") { 
			char* file_name = argv[2];
			string x = read_file(file_name);	
			if (x != "null") {
				//Convert to char array
				int sz = x.size();
				char data[sz];
				for (int i = 0; i < sz; i++) {
					data[i] = x[i];
				}

				//Lexical Analyzer
				vector<string> tokens;
				vector<string> types;
				tokens = lex(data, sz);
				types = tlex(data, sz);

				//Print
				//printTokens(tokens, types);

				//Recursive Descent Parser
				string ast = parse(tokens, types);
				ast = ast.substr(0, ast.size() - 1);
				cout << ast << endl;
			}
			else {
				std::cout << "Error: File not found" << endl;
			}

			return 0;
		}
	}
	
	return 0;
}