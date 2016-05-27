#include "ds.h"

KEYWORD keyTable[] = {
	{"integer", 1},		{"real", 2}, 		{"boolean", 3},
	{"if", 4}, 			{"then", 5}, 		{"else", 6},
	{"begin", 7}, 		{"end", 8}, 		{"while", 9},
	{"do", 10}, 		{"read", 11}, 		{"write", 12},
	{"array", 13}, 		{"of", 14}, 		{"record", 15},
	{"var", 16}, 		{"function", 17}, 	{"procedure", 18},
	{"program", 19}, 	{"true", 20}, 		{"false", 21}
};


IDLIST idlist[IDLIST_LEN];
int IDLIST_CUR_NUM = 0;

NUMLIST numlist[NUMLIST_LEN];
int NUMLIST_CUR_NUM = 0;

// 错误类型表：
char* errList[ERR_TYPES] = {
	"No num",
	"No name"
};


// 产生式定义
int genOp[GENOP_NUM][OP_LEN] = {
	{0},
	{1,-1,2,4,72},
	{2,-1,68,35,43,3,44,46},
	{3,-1,35,28},
	{4,-1,5,9,15},
	{5,-1,65,6,46,-1,73},
	{6,-1,3,45,7,27},
	{7,-1,8,-1,63,48,74,75,74,49,63,8,-1,64,6,57},
	{8,-1,50,-1,51,-1,52,-1,36,75,36},
	{9,-1,29},
	{10,-1,11,5,15},
	{11,-1,66,35,12,45,8,46,-1,67,35,12,46},
	{12,-1,43,13,44,-1,73},
	{13,-1,14,30},
	{14,-1,65,3,45,7,-1,3,45,7},
	{15,-1,56,16,57},
	{16,-1,17,-1,73},
	{17,-1,18,31},
	{18,-1,19,41,22,-1,20,-1,15,-1,53,22,54,18,55,18,-1,58,22,59,18,-1,60,43,3,44,-1,61,43,21,44},
	{19,-1,35,-1,35,48,22,49},
	{20,-1,35,-1,35,43,21,44},
	{21,-1,22,32},
	{22,-1,23,42,23,-1,23},
	{23,-1,24,33,-1,26,24,33},
	{24,-1,25,34},
	{25,-1,35,-1,35,43,21,44,-1,35,48,22,49,-1,36,-1,43,22,44,-1,71,25,-1,69,-1,70},
	{26,-1,37,-1,38},
	{27,-1,46,3,45,7,27,-1,73},
	{28,-1,47,35,28,-1,73},
	{29,-1,10,46,29,-1,73},
	{30,-1,46,14,30,-1,73},
	{31,-1,46,18,31,-1,73},
	{32,-1,47,22,32,-1,73},
	{33,-1,39,24,33,-1,73},
	{34,-1,40,25,34,-1,73}
};

int genOp_more[GENOP_NUM][OP_LEN] = {
{0},
{1,-1,2,4,100,72},
{2,-1,68,101,35,102,43,3,44,103,46},
{3,-1,35,104,28},
{4,-1,5,9,15},
{5,-1,65,6,46,-1,73},
{6,-1,3,45,200,7,201,27,106},
{7,-1,8,-1,63,48,75,49,63,8,-1,64,6,57},
{8,-1,50,107,-1,51,108,-1,52,109,-1,76},
{9,-1,29},
{10,-1,11,145,5,15,113},
{11,-1,66,35,202,12,45,114,8,201,46,-1,67,35,202,12,115,46},
{12,-1,43,13,116,44,-1,73},
{13,-1,14,30},
{14,-1,65,3,45,200,7,140,-1,3,45,200,7,140},
{15,-1,56,16,57},
{16,-1,17,-1,73},
{17,-1,18,31},
{18,-1,19,41,137,22,139,-1,20,106,-1,15,106,-1,53,118,22,136,54,112,18,113,55,119,18,113,-1,58,123,22,124,18,138,-1,60,120,43,3,141,44,-1,61,122,43,21,142,44},
{19,-1,35,104,-1,35,48,126,22,49,127},
{20,-1,35,104,-1,35,129,43,21,121,44},
{21,-1,22,143,32},
{22,-1,23,42,137,23,121,-1,23},
{23,-1,24,33,-1,26,24,33},
{24,-1,25,34},
{25,-1,35,104,-1,35,43,129,21,144,44,-1,35,48,126,22,49,127,-1,36,130,-1,128,43,22,44,121,-1,71,25,131,-1,69,132,-1,70,133},
{26,-1,37,134,-1,38,135},
{27,-1,46,106,3,45,200,7,27,-1,73},
{28,-1,47,105,35,104,28,-1,73},
{29,-1,103,10,46,29,-1,73},
{30,-1,46,105,14,30,-1,73},
{31,-1,46,18,31,-1,73},
{32,-1,47,105,22,32,-1,73},
{33,-1,39,137,24,33,121,-1,73},
{34,-1,40,137,25,34,121,-1,73}
};

//保留字
char* reserve_words[RESERVE_WORD_NUM]={
	"",
	"",
	"+",
	"-",
	"*",
	"/",
	"div",
	"mod",
	":=",
	"=",
	"<> ",
	"< ",
	"<=",
	"> ",
	">=",
	"(",
	")",
	":",
	";",
	",",
	"[",
	"]",
	"integer",
	"real",
	"boolean",
	"if",
	"then",
	"else",
	"begin",
	"end",
	"while",
	"do",
	"read",
	"write",
	"array",
	"of",
	"record",
	"var",
	"function",
	"procedure",
	"program",
	"true",
	"false",
	"not",
	"and",
	"or",
	"xor",
	"+",
	"-",
	".",
	".."
};

// VAR_NUM表
char* var_list[]={
"",
"Program",
"program_head",
"identifier_list",
"program_body",
"declarations",
"declaration",
"type",
"standard_type",
"subprogram_declarations",
"subprogram_declaration",
"subprogram_head",
"arguments",
"parameter_lists",
"parameter_list",
"compound_statement",
"optional_statements",
"statement_list",
"statement",
"variable",
"procedure_call_statement",
"expr_list",
"expression",
"simple_expr",
"term",
"factor",
"sign ",
"temp0",
"temp1",
"temp2",
"temp3",
"temp4",
"temp5",
"temp6",
"temp7",
"id",
"num",
"+",
"-",
"addop",
"mulop",
"assignop",
"relop",
"(",
")",
":",
";",
",",
"[",
"]",
"integer",
"real",
"boolean",
"if",
"then",
"else",
"begin",
"end",
"while",
"do",
"read",
"write",
"array",
"of",
"record",
"var",
"function",
"procedure",
"program",
"true",
"false",
"logop",
".",
"&",
"digits",
".."
// "num..num"
};

// 符号表
SN symbolTable;

// TOKEN表
TOKEN tokenlist[TOKENLIST_LEN];
int TOKEN_CUR_LEN = 0;

// 项目集规范族
PROJECT_SET PS[PROJECT_SET_NUM];
int PS_CUR_NUM = 0;						// 记录当前的项目集的个数


// goto数组
int gto[PROJECT_SET_NUM][VN_NUM];
// action数组
act_block act[PROJECT_SET_NUM][VT_NUM];