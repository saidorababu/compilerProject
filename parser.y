%{
 #include<stdio.h>
 int valid=1;
int yylex();
int yyerror(const char *s);
extern int st[100];
extern int top;
extern int count;
extern void display();
%}


%start main_block 
%error-verbose
%token declaratio identifier unary operator number assignmentop comparisionop logicalop while_x for_x if_x main_x printf_x return_x new_line 
%left '+' '-'
%left '/' '*'
%left '%'

%%

main_block : declaratio main_x '(' ')' body
	;
	
body : '{' multiple_expressions '}' multiple_expressions
	 | expression multiple_expressions
     | logical_expression multiple_expressions
     | if multiple_expressions
     | error ';'
     | for multiple_expressions
     | while multiple_expressions
     | printf
     | '{' '}' 
     | return_x number ';' | 
     ;


for:    for_x '(' assignment_expression ';' extended_logical_expression ';' extended_logical_expression ')' '{' multiple_expressions '}'
      | for_x '(' assignment_expression ';' extended_logical_expression ';' extended_logical_expression ')' expression
      | for_x '(' assignment_expression ';' extended_logical_expression ';' extended_logical_expression ')' logical_expression
      ;


if: if_x '(' extended_logical_expression ')' body
    ;
	
for : for_x '(' assignment_expression_with_null ';' extended_logical_expression_with_null ';' extended_logical_expression_with_null ')' body
	;
      
while :  while_x '(' identifier comparisionop identifier ')' 
       |  while_x '(' identifier comparisionop number ')' 
       ;

extended_logical_expression_with_null:extended_logical_expression
				    | 
				    ;
assignment_expression_with_null:assignment_expression
				| 
				;

multiple_expressions: logical_expression ';' multiple_expressions 
		    | expression ';' multiple_expressions 
          	| body 
     ;


logical_expression: comparision_expression logicalop extended_logical_expression 
		   | assignment_expression logicalop extended_logical_expression 
		   | RHS logicalop extended_logical_expression 
		   ;
 
extended_logical_expression:logical_expression
			  | comparision_expression
		          | assignment_expression
		          | RHS
		          ;

expression:  comparision_expression ';'
	   | assignment_expression ';'
       | declaration_statement ';'
	   | RHS 
	   ;

comparision_expression:RHS comparisionop RHS
		      ;

assignment_expression: declaration_statement assignmentop RHS
		     | identifier assignmentop RHS
                     ;

declaration_statement: declaratio identifier        
    		     | declaration_statement ',' pointers identifier 
    		     ;

printf: printf_x '(' '"' identifier '"' ')' ';'
	| printf_x '(' '"' identifier '"' multiple_ids ')' ';'
	;

multiple_ids: ',' identifier multiple_ids
	| ',' identifier
	;
	
pointers : pointers '*'  
	|
	;

RHS: '(' RHS ')' 
    | RHS '+' RHS
    | RHS '-' RHS
    | RHS '/' RHS
    | RHS '*' RHS
    | RHS '%' RHS 
    | F
    ;

F: identifier 
    | '*' identifier
    | '&' identifier
    | '~' identifier
    | '!' identifier
    | identifier unary
    | unary identifier
    | number
    ;

%%

#include <ctype.h>
int yyerror(const char *s)
{
  	extern int yylineno;
  	valid =0;
	if(yylineno!=27)
	{
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
	
	st[0]=0;
	top=0;
	count=0;
	yyin=fp;
	yyparse();/*
	if(valid==1)
		printf("Valid Syntax\n");
	else
		printf("Invalid Syntax\n");*/
	printf("---------------\n");
	
	display();

}
