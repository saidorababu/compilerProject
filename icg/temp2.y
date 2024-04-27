%{
	#include "TreeNode.h"
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	int yylex();
	int yyerror(const char *s);
	int yyparse();
	extern void display();
	struct entry{
		char arr[20];
		int scope;
		char dtype[10];
		int value;
	};
	extern struct entry symbolTable[100];

	typedef struct threeAddrCode{
		char *result;
		char* operation;
		char* op1;
		char* op2;
	} threeAddrCode;


	threeAddrCode* createCode(char* result, char* operation, char* op1, char* op2){
		threeAddrCode* code = (threeAddrCode*)malloc(sizeof(threeAddrCode));
		code->result = (char*)malloc(strlen(result)+1);
		strcpy(code->result, result);
		code->operation = (char*)malloc(strlen(operation)+1);
		strcpy(code->operation, operation);
		code->op1 = (char*)malloc(strlen(op1)+1);
		strcpy(code->op1, op1);
		code->op2 = (char*)malloc(strlen(op2)+1);
		strcpy(code->op2, op2);
		return code;
	}

	void printCode(threeAddrCode* code){
		printf("%s = %s %s %s\n", code->result, code->op1, code->operation, code->op2);
	}

	List* newList(int i){
		List* list = (List*)malloc(sizeof(List));
		list->curr = i;
		list->next = NULL;
		return list;
	}

	List* mergeList(List* list1, List* list2){
		List* temp = list1;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = list2;
		return list1;
	}
	int tempVarNo = 1;
	struct threeAddrCode* icg[1000];
	int icgIndex = 0;
	void generateCode(char* operation, char* op1, char* op2, char* result){
		icg[icgIndex++] = createCode(result, operation, op1, op2);
	}

	char* new_label(){
		char* label = (char*)malloc(10);
		sprintf(label, "L%d", tempVarNo++);
		return label;
	}
	char* new_temp(){
		char* temp = (char*)malloc(10);
		sprintf(temp, "t%d", tempVarNo++);
		return temp;
	}
	void backpatch(List* list, int label){
		List* temp = list;
		while(temp != NULL){
			char* index = (char*)malloc(10);
			sprintf(index, "L%d", temp->curr);
			icg[temp->curr]->result = (char*)malloc(10);
			strcpy(icg[temp->curr]->result, index);
			temp = temp->next;
		}
	}
	void displayICG(){
		printf("Intermediate Code Generation\n");
		for(int i = 0; i < icgIndex; i++){
			if(icg[i]->operation[0] == 'g'){
				printf("%2d %s %s\n", i, icg[i]->operation, icg[i]->result);
			}else if(icg[i]->operation[0] == '='){
				printf("%2d %s = %s\n", i, icg[i]->result, icg[i]->op1);
			}else if( icg[i]->operation[0] == 'i'){
				printf("%2d %s %s %s %s\n", i, icg[i]->operation, icg[i]->op1,icg[i]->op2, icg[i]->result);
			}else if(icg[i]->operation[0] == 'p'){
				printf("%2d %s %s \n", i, icg[i]->operation, icg[i]->op1);
			}else if(icg[i]->operation[0] == 'c'){
				printf("%2d %s %s %s\n", i, icg[i]->operation , icg[i]->op1 , icg[i]->op2);
			}else{
				printf("%2d %s = %s %s %s\n", i, icg[i]->result, icg[i]->op1, icg[i]->operation, icg[i]->op2);
			}
		}
	}
	
	
	// void printTree(struct Node* node, int level);
	TreeNode *head = NULL;
	struct TreeNode *create_Node(char *label, int value, char *value_str,char *dtype, int num_children, ...) {
		struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
		newNode->label = label;
		newNode->value = value;
		newNode->value_str = (char*)malloc(sizeof(char) * strlen(value_str) + 1);
		strcpy(newNode->value_str,value_str);
		newNode->num_children = num_children;
		newNode->dtype= dtype;
		newNode->scope = -1;
		newNode->children = NULL;
		if(num_children<1) return newNode;
		newNode->children = malloc(sizeof(TreeNode*) * num_children);

		va_list args;
		va_start(args, num_children);

		for (int i = 0; i < num_children; i++) {
			newNode->children[i] = va_arg(args, struct TreeNode*);
		}

		va_end(args);

		return newNode;
	}

	void printTree(TreeNode *root,int level){
		if(root == NULL){
			return;
		}
		for(int i = 0;i<level;i++){
			printf("   ");
		}
		if(root->value ==-1 && strcmp(root->dtype,"NULL") == 0){
			if(strcmp(root->value_str,"NULL") == 0){
				printf("|--%d.%s\n",level, root->label);
			}else{
				printf("|--%d.%s\n",level, root->value_str);
			}
		}
		else{
			printf("|--%d.(%s,%d,%s,%s)\n",level, root->label,root->value,root->value_str,root->dtype);
		}
		
		for(int i = 0;i<root->num_children;i++){
			printTree(root->children[i],level+1);
		}
	}
	void addEntry(char *name, char *dtype,int scope,int value){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0 && symbolTable[i].scope == scope){
				//printf("Variable: %s, dtype:%s  \n",name,symbolTable[i].dtype);

				if(strcmp(symbolTable[i].dtype,"null") != 0 ){
					printf("Variable %s is already declared\n",name); 
					yyerror("Variable already declared");
					break;
					return;
				}
				symbolTable[i].value = value;
				strcpy(symbolTable[i].dtype,dtype);
				printf("Variable: %s, dtype: %s \n",name,symbolTable[i].dtype);
				// symbolTable[i].value = 0;
				
				break;
			}
		}
	}
	void addFunctionValue(char *name, int value){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0){
				symbolTable[i].value = value ;
				break;
			}
		}
	}
	struct Pair{
		char *dtype;
		int scope;
	};
	struct Pair make_pair(char* dtype, int scope) {
		struct Pair p;
		p.dtype = dtype;
		p.scope = scope;
		return p;
	}

	struct Pair checkIdentifier(char *name){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,name) == 0){
				return make_pair(symbolTable[i].dtype,symbolTable[i].scope);
				break;
			}
		}
		return make_pair("NULL",-1);
	}
	int checkEntry(char *name,char *dtype,int scope,int value){
		for(int i = 0;i<100;i++){
			
			if(strcmp(symbolTable[i].arr,name) == 0 && symbolTable[i].scope <= scope && strcmp(symbolTable[i].dtype,dtype) == 0){
				symbolTable[i].value = value;
				return 1;
				break;
			}
		}
		return 0;
	}
	void checkid(TreeNode *root){
		struct Pair p = checkIdentifier(root->value_str);
		if(p.dtype == "keyword"){
			printf("variable %s using the keyword declare again\n",root->value_str);
			yyerror("Variable using keyword");
			return;
		}

		if(p.dtype == "NULL"){
			printf("Variable %s is not declared\n",root->value_str); 
			yyerror("Variable not declared");
			return ;
		}else{
			root->dtype = p.dtype;
		}
		if(checkEntry(root->value_str,root->dtype,root->scope,root->value) == 0){
			printf("Variable %s,%s,%d is not declared\n",root->value_str,root->dtype,root->scope); 
			yyerror("Variable not declared");
			return;
		};
	}
	void checkType(TreeNode* a, TreeNode* b){
		if((a->dtype != b->dtype) && (strcmp(a->dtype, "string") == 0 || strcmp(b->dtype, "string") == 0)){
			yyerror("Type mismatch");
			return;
		}
	}
	void checkfnArguments(TreeNode* a){
		for(int i = 0;i<100;i++){
			if(strcmp(symbolTable[i].arr,a->value_str) == 0){
				if(symbolTable[i].value != a->value){
					yyerror("Number of arguments mismatch");
					return;
				}
			}
		}
	}
%}

%union {
    int num;
    char *str;
	struct TreeNode *node;
}

%start program
%token EOL
%error-verbose
%token<node> PLUS MINUS MUL DIV number AND OR NOT if_x else_x while_x for_x return_x printf_x main_x assignmentop comparisionop logicalop datatype unary identifier string character cout cin insert extract header LBRACE RBRACE LPAREN RPAREN SEMICOLON COMMA
%type<node> E T F M N function_call arg_list assignment_statement dec_assignment statement_list function_declarations function_declaration declaration_statement id_list insert_statement extract_statement if_statement while_statement for_statement return_statement cout_statement cin_statement statement headers parameter_list program
/* rules */

%%

program: headers function_declarations {  $$ = create_Node("program", -1, "NULL","NULL", 2,$1,$2);if(!head) head = $$;} 
	| EOL program { $$ = create_Node("program", -1, "NULL","NULL", 1,$2);if(!head) head = $$;}
	| program EOL { $$ = create_Node("program", -1, "NULL","NULL", 1,$1);if(!head) head = $$;}
	| EOL { $$ = NULL; }
	|;
function_declarations:
	function_declaration function_declarations { $$ = create_Node("function_declarations", -1, "NULL","NULL", 2,$1,$2); }
	| EOL function_declaration { $$ = create_Node("function_declarations", -1, "NULL","NULL", 1,$2); }
	| function_declaration EOL { $$ = create_Node("function_declarations", -1, "NULL","NULL", 1,$1); }
	| EOL { $$ = NULL; }
	| ;


headers: header {$$ = create_Node("headers", -1, "NULL","NULL",1,$1);}
	| header headers { $$ = create_Node("headers", -1,"NULL","NULL", 2, $1, $2);}
	| EOL headers { $$ = create_Node("headers", -1, "NULL","NULL",1, $2);}
	| EOL{ $$ = NULL; };

function_declaration: datatype identifier LPAREN parameter_list RPAREN LBRACE statement_list return_statement RBRACE {
	$2->dtype = $1->dtype;
	$$ = create_Node("function_declaration", -1, "NULL","NULL", 8, $1,$2,$3, $4, $5, $6, $7, $8); 
	$$->value = $4->value;
	addEntry($2->value_str,$2->dtype,$2->scope,$4->value);
	addFunctionValue($2->value_str, $4->value);
};

parameter_list: datatype identifier COMMA parameter_list { 
	$$ = create_Node("parameter_list", -1, "NULL","NULL",4, $1, $2, $3, $4);
	$2->dtype = $1->dtype;
	$$->value = $4->value + 1;
	addEntry($2->value_str,$2->dtype,$2->scope,$2->value);
	 }
 | datatype identifier {
	$2->dtype = $1->dtype;
	$$ = create_Node("parameter_list", -1, "NULL","NULL",2, $1, $2);
	$$->value = 1;
	addEntry($2->value_str,$2->dtype,$2->scope,$2->value);
 }
	| { $$ = create_Node("parameter_list", -1, "NULL","NULL",0); $$->value = 0 };


statement_list: 
	statement M statement_list { 
			$$ = create_Node("statement_list", -1, "NULL","NULL", 2, $1, $3);
			backpatch($1->nextList,$2->nextList->curr);
			$$->nextList = $3->nextList;
		}
	|	EOL statement_list { $$ = create_Node("statement_list", -1, "NULL","NULL", 1, $2);}
	|	EOL {$$ = NULL;}
	|
;

M : {$$ = create_Node("M", -1, "st_if","NULL", 0);$$->nextList = newList(icgIndex);}
N : {$$ = create_Node("N", -1, "st_if","NULL", 0);$$->nextList = newList(icgIndex);generateCode("goto","","","");}

statement: declaration_statement { $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| assignment_statement SEMICOLON {printf("assignment_statement\n"); $$ = create_Node("statement", -1,"NULL","NULL",2, $1, $2);}
	| for_statement {printf("for_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| if_statement {printf("if_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	// | if_else_statement {printf("if_else_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| while_statement {printf("while_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| cout_statement {printf("cout_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| cin_statement {printf("cin_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| return_statement {printf("return_statement\n"); $$ = create_Node("statement", -1, "NULL","NULL",1,$1); }
	| function_call SEMICOLON {printf("function_call\n"); $$ = create_Node("statement", -1, "NULL","NULL",2,$1,$2); }
	| error SEMICOLON { $$ = create_Node("error", -1, "NULL","NULL",0); }
	| EOL { $$ = NULL; };

function_call: identifier LPAREN arg_list RPAREN { 
		$$ = create_Node("function_call", -1, "NULL","NULL", 4, $1, $2, $3, $4); 
		$1->value = $3->value;
		checkfnArguments($1);
	}	
	| identifier LPAREN RPAREN { $$ = create_Node("function_call", -1, "NULL","NULL", 3, $1, $2, $3); }
	;

arg_list: identifier { $$ = create_Node("arg_list", -1, "NULL","NULL", 1, $1); $$->value = 1; }
	| identifier COMMA arg_list { $$ = create_Node("arg_list", -1, "NULL","NULL", 3, $1, $2, $3); $$->value = $3->value + 1; }	
	;

if_statement: if_x LPAREN E RPAREN LBRACE statement_list RBRACE { $$ = create_Node("if_statement", -1,"NULL","NULL", 7,$1,$2,$3,$4,$5,$6,$7);backpatch($3->trueList,$6->nextList->curr);$$->nextList = mergeList($3->falseList,$7->nextList);}
	| if_x LPAREN E RPAREN M LBRACE statement_list RBRACE N else_x M LBRACE statement_list RBRACE {
		$$ = create_Node("if_statement", -1,"NULL","NULL", 13,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13);
		backpatch($3->trueList,$6->nextList->curr);
		backpatch($3->falseList,$10->nextList->curr);
		$$->nextList = mergeList(mergeList($7->nextList,$9->nextList),$13->nextList);
	}

// if_statement: if_x LPAREN E RPAREN M LBRACE statement_list RBRACE { $$ = create_Node("if_statement", -1,"NULL","NULL", 7,$1,$2,$3,$4,$6,$7,$8);backpatch($3->trueList,$6->nextList->curr);$$->nextList = mergeList($3->falseList,$8->nextList);}
// | if_x LPAREN E RPAREN  statement { $$ = create_Node("if_statement", -1,"NULL","NULL", 5,$1,$2,$3,$4,$5);}
// | if_statement EOL  { $$ = create_Node("if_statement", -1,"NULL","NULL", 1,$1);};


// else_statement: else_x LBRACE statement_list RBRACE { $$ = create_Node("else_statement", -1, "NULL","NULL", 3, $1, $2, $3); }
//  | else_x statement { $$ = create_Node("else_statement", -1, "NULL","NULL", 2, $1, $2); }
//  | else_statement EOL { $$ = create_Node("else_statement", -1, "NULL","NULL", 1, $1); }
//  ;

// if_else_statement: if_statement N else_statement { $$ = create_Node("if_else_statement", -1, "NULL","NULL", 2, $1, $3); backpatch($1->nextList,$2->nextList->curr); $$->nextList = mergeList($1->nextList,$2->nextList); };

while_statement: while_x M LPAREN E RPAREN M LBRACE statement_list RBRACE {
	$$ = create_Node("while_statement", -1, "NULL","NULL", 9, $1, $2, $3, $4, $5, $6, $7, $8, $9);
	backpatch($4->trueList,$7->nextList->curr);
	backpatch($8->nextList,$2->nextList->curr);
	$$->nextList = $4->falseList;
	char *x = malloc(10);
	sprintf(x,"L%d",$2->nextList->curr);
	generateCode("goto","","",x);
 };

for_statement: for_x LPAREN declaration_statement E SEMICOLON M E RPAREN LBRACE statement_list RBRACE { 
	$$ = create_Node("for_statement", -1, "NULL","NULL", 11, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10,$11);
	backpatch($4->nextList,$10->nextList->curr);
	backpatch($10->nextList,$6->nextList->curr);
	backpatch($10->nextList,$2->nextList->curr);
	// $$->nextList = $10->nextList;
};


return_statement: return_x E SEMICOLON { $$ = create_Node("return_statement", -1,"NULL","NULL", 2, $1, $2); generateCode("return", "", "", $2->label) }
| return_x SEMICOLON { $$ = create_Node("return_statement", -1, "NULL","NULL", 2, $1,$2); generateCode("return", "","", "")};

cout_statement: cout insert_statement SEMICOLON { $$ = create_Node("cout_statement", -1,"NULL","NULL", 2, $1, $2); };

insert_statement: insert E insert_statement { $$ = create_Node("insert_statement", -1,"NULL","NULL", 3, $1, $2, $3); }
    | insert string insert_statement { $$ = create_Node("insert_statement", -1, "NULL","NULL", 3, $1, $2, $3); }
	| insert E { $$ = create_Node("insert_statement", -1, "NULL","NULL", 2, $1, $2); }
	| insert string { $$ = create_Node("insert_statement", -1, "NULL","NULL", 2, $1, $2); }

cin_statement: cin extract_statement SEMICOLON { $$ = create_Node("cin_statement", -1, "NULL","NULL", 3, $1, $2, $3); };

extract_statement: extract identifier extract_statement { $$ = create_Node("extract_statement", -1, "NULL","NULL", 3, $1, $2, $3); }
| extract identifier { $$ = create_Node("extract_statement", -1, "NULL","NULL", 2, $1, $2); } 
;


declaration_statement: datatype id_list SEMICOLON { $2->dtype = $1->dtype;  $$ = create_Node("declaration_statement", -1, "NULL","NULL", 3, $1, $2, $3); };

id_list: id_list COMMA identifier {
	$$ = create_Node("id_list", -1, "NULL","NULL", 3, $1, $2, $3); 
	$3->dtype = $<node>0->dtype;
	$1->dtype = $<node>0->dtype;
	addEntry($3->value_str,$3->dtype,$3->scope,$3->value);
}
| id_list {$1->dtype = $<node>0->dtype;} COMMA dec_assignment {
	$$ = create_Node("id_list", -1, "NULL","NULL", 3, $1, $3, $4);
	$3->dtype = $<node>0->dtype;
}
| dec_assignment {
	$$ = create_Node("id_list", -1, "NULL","NULL", 1, $1);
	$1->dtype = $<node>0->dtype; 
}
| identifier { 
	$$ = create_Node("id_list", -1, "NULL","NULL", 1, $1);
	$1->dtype = $<node>-1->dtype;
	addEntry($1->value_str,$1->dtype,$1->scope,$1->value); 
}

dec_assignment: 
	identifier assignmentop E { 
		$$ = create_Node("dec_assignment", -1, "NULL","NULL", 3, $1, $2, $3); 
		checkType($1,$3);
		$1->value = $3->value;
		$1->dtype = $<node>0->dtype; 
		addEntry($1->value_str,$1->dtype,$1->scope,$1->value);
		generateCode("=", $3->label, "", $1->label);

	}

assignment_statement:
	identifier assignmentop E  {
		$$ = create_Node("assignment_statement", -1, "NULL","NULL", 3, $1, $2, $3);
		$1->value = $3->value;
		checkid($1);
		checkType($1,$3);
		generateCode("=", $3->label, "", $1->label);
	}
;

E: identifier assignmentop E  { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $3); $1->value = $3->value;  checkid($1); checkType($1,$3); }
	|	E comparisionop E { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $3); checkType($1,$3); 
			$$->trueList = newList(icgIndex);
			$$->falseList = newList(icgIndex+1);
			char *x = malloc(strlen($2->label)+strlen($1->label)+strlen($3->label)+1);
			int k = 0;
			for(int i = 0;i<strlen($1->label);i++){
				x[k++] = $1->label[i];
			}
			for(int i = 0;i<strlen($2->label);i++){
				x[k++] = $2->label[i];
			}
			for(int i = 0;i<strlen($3->label);i++){
				x[k++] = $3->label[i];
			}
			generateCode("if", x,"goto","");
			generateCode("goto","","","");
			if (strcmp($2->value_str, "<=") == 0) {
				$$->value = $1->value <= $3->value;
			} else if (strcmp($2->value_str, ">=") == 0) {
				$$->value = $1->value >= $3->value;
			} else if (strcmp($2->value_str, "==") == 0) {
				$$->value = $1->value == $3->value;
			} else if (strcmp($2->value_str, "!=") == 0) {
				$$->value = $1->value != $3->value;
			}
			else if (strcmp($2->value_str, "<") == 0) {
				$$->value = $1->value < $3->value;
			}
			else if (strcmp($2->value_str, ">") == 0) {
				$$->value = $1->value > $3->value;
			}
	}
	|	E AND M E { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $3); checkType($1,$3); 
		if (strcmp($2->value_str, "&&") == 0) {
			$$->value = $1->value && $3->value;
		} else if (strcmp($2->value_str, "||") == 0) {
			$$->value = $1->value || $3->value;
		}
		backpatch($1->trueList, $3->nextList->curr);
		$$->trueList = $4->trueList;
		$$->falseList = mergeList($1->falseList, $4->falseList);
	}
	|	E OR M E { $$ = create_Node("E", -1,  "NULL","NULL", 3, $1, $2, $3); checkType($1,$3); 
		if (strcmp($2->value_str, "&&") == 0) {
			$$->value = $1->value && $3->value;
		} else if (strcmp($2->value_str, "||") == 0) {
			$$->value = $1->value || $3->value;
		}
		backpatch($1->falseList, $3->nextList->curr);
		$$->falseList = $4->falseList;
		$$->trueList = mergeList($1->trueList, $4->trueList);
	}
	| NOT E { $$ = create_Node("E", !$2->value,  "NULL","NULL", 2, $1, $2); $$->value = !$2->value; $$->trueList = $2->falseList; $$->falseList = $2->trueList; }
	|   E PLUS T { $$ = create_Node("E", $1->value+$3->value, "NULL","NULL", 3, $1, $2, $3); checkType($1,$3); generateCode("+", $1->label, $3->label, $$->label); }
	|   E MINUS T { $$ = create_Node("E", $1->value-$3->value, "NULL","NULL", 3, $1, $2, $3); checkType($1,$3); generateCode("-", $1->label, $3->label, $$->label);}
	|   T { $$ = create_Node("E", $1->value, "NULL","NULL", 1, $1);  $$->value = $1->value; $$->dtype = $1->dtype; }
	;

T: T MUL F { $$ = create_Node("T", $1->value*$3->value, "NULL","NULL", 3, $1, $2, $3); checkType($1,$3); generateCode("*", $1->label, $3->label, $$->label);}
	|	T DIV F { $$ = create_Node("T", $1->value/$3->value, "NULL","NULL", 3, $1, $2, $3);checkType($1,$3); generateCode("/", $1->label, $3->label, $$->label);}
	|	F { $$ = create_Node("T", $1->value, "NULL","NULL", 1, $1); $$->dtype = $1->dtype;  $$->value = $1->value;} 
	;

F: number { $$ = create_Node("F", -1, "NULL","NULL", 1, $1);  $$->dtype = $1->dtype; $$->value = $1->value;  }
	| character { $$ = create_Node("F", -1, "NULL","NULL", 1, $1);  $$->dtype = $1->dtype;  }
	| LPAREN E RPAREN { $$ = create_Node("F",$2->value, "NULL","NULL", 3, $1, $2, $3);  $$->dtype = $2->dtype;  }
	| identifier { $$ = create_Node("F", -1, "NULL","NULL", 1, $1); checkid($1);  $$->dtype = $1->dtype; }
	| unary identifier { $$ = create_Node("F", -1, "NULL","NULL", 2, $1, $2); checkid($2);  $$->dtype = $2->dtype; generateCode($1->value_str, $2->label, "", $2->label); }
	| identifier unary { $$ = create_Node("F", -1, "NULL","NULL", 2, $1, $2); checkid($1);  $$->dtype = $1->dtype; generateCode($2->value_str, $1->label, "", $1->label); }
	| string { $$ = create_Node("F", -1, "NULL","NULL", 1, $1); $$->dtype = $1->label;}
	;

%%
#include <ctype.h>
int yyerror(const char *s)
{
  	extern int yylineno;
  	// valid = 0;
	if(yylineno != 27){
		printf("Line no: %d \n The error is: %s\n",yylineno,s);
	}
}
extern FILE *yyin;
int main(int argc,char **argv){
	if(argc<2)
	{
		printf("Usage: %s <filename>\n",argv[0]);
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("Error: File not found\n");
		return 1;
	}
	// initializeSymbolTable()
	extern char *yytext;
	yyin=fp;
	yyparse();
	// yyparse();
	printf("---------------\n");
	printTree(head,0);
	printf("---------------\n");
	display();

	printf("---------------\n");
	displayICG();
}