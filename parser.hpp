#pragma once


#include <vector>
#include <string>
#include "bp.hpp"
#include "globalLabel.hpp"

using namespace std;
enum Types { VOIDS = 0, INTS, STRINGS, BYTES, BOOLS, ENUMS, ENUMS_TYPE };

class TokenData {
public:
	string value;
	TokenData(string value_t) : value(value_t) { }
	string getValue() {
		return value;
	}
};

class IdData: public TokenData {
public:
	Types type;
	IdData(Types type_t, string name_t) : TokenData(name_t), type(type_t) { }
	IdData(string name_t) : TokenData(name_t), type() { }
	Types getType() {
		return type;
	}
};

class TypeData {
public:
	Types type;
	string enum_name; // SUNDAY , MONDAY .. {,,,,,}
	TypeData(Types type_t, string enum_name_t = "") : type(type_t), enum_name(enum_name_t) { }
	Types getType() {
		return type;
	}
};

class ExpData {
public:
	Types type;
	string name;
	string place;
	string loop_cond;
    vector<pair<int,BranchLabelIndex>> trueList;
    vector<pair<int,BranchLabelIndex>> falseList;
	ExpData(Types type_t, string name_t) : type(type_t), name(name_t), place(""), trueList(), falseList() { }
	ExpData(Types type_t) : type(type_t), name(), place(""), trueList(), falseList() { }
	Types getType() {
		return type;
	}

};

class ExpListData {
public:
	vector<ExpData*> expList;
};

class FormalDeclData: public TypeData {
public:
	string name;
	string enum_id;
	FormalDeclData(Types type, string name_t, string enum_id_t = "") : TypeData(type), name(name_t), enum_id(enum_id_t) { }
};

class FormalsData {
public:
	vector<FormalDeclData*> formalsList;
	FormalsData() : formalsList() { }
};

class StatementData {
public:
    vector<pair<int,BranchLabelIndex>> nextList;
    StatementData(): nextList(){ }
};

// Enum classes begin
// Not sure about Enums declaration HERE VVV

/* class EnumsDeclData: public TypeData {
public:
	string name;
	EnumsDeclData(Types type, string name_t) : Types(type), name(name_t) { }
}; */

class EnumsData {
public:
	string name;
	vector<TypeData*> enumList;
	EnumsData() : enumList() { }
};

class M_Data {
public:
    string quad;
    M_Data(): quad(){}
};


// end

class SymbolTable {
public:
	string name;
	int offset;
	Types type;
	bool is_fun;
	string enum_id; 
	vector<Types> fun_param_types;
	vector<string> enum_params;
	vector<pair<int,BranchLabelIndex>> continueList;
	vector<pair<int,BranchLabelIndex>> breakList;
	SymbolTable(string name_t, int offset_t, Types type_t, vector<Types> fun_param_types_t, vector<string> enum_params_t) : name(name_t), offset(offset_t), type(type_t), fun_param_types(fun_param_types_t), enum_id(""), enum_params(enum_params_t),continueList(),breakList() { }
	SymbolTable(string name_t, int offset_t, Types type_t, vector<Types> fun_param_types_t) : name(name_t), offset(offset_t), type(type_t), fun_param_types(fun_param_types_t), enum_id(""), enum_params(),continueList(),breakList() { }
	SymbolTable(string name_t, int offset_t, Types type_t, string enum_id_t) : name(name_t), offset(offset_t), type(type_t) , fun_param_types(), enum_id(enum_id_t), enum_params(),continueList(),breakList() { }
	SymbolTable(string name_t) : name(name_t), offset(-1), fun_param_types(), type(), enum_id(""), enum_params(),continueList(),breakList() { }
};

class TablesStack {
public:
	vector<SymbolTable*> tables;
	/*string arg_base;
	string local_base;
	int local_counter;
	int arg_counter;*/
	
	TablesStack() : tables()/*, local_counter(0), arg_counter(0)*/ { }
};

/*
class Function {
	public:
	string name;
	string arg_base;
	string local_base;
	int local_counter;
	int arg_counter;
	
	Function(string name_t) : name(name_t), local_counter(0), arg_counter(0) { }
};*/

typedef union {
	TokenData* token_data;
	IdData* id_data;
	TypeData* type_data;
	ExpData* exp_data;
	ExpListData* exp_list_data;
	FormalDeclData* formal_decl_data;
	FormalsData* formals_data;
	// Note to check !
	EnumsData* enum_data;
	StatementData* statement_data;
	M_Data * m_data;
} Node;

#define YYSTYPE Node
