
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "temp2.y"

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


/* Line 189 of yacc.c  */
#line 325 "temp2.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EOL = 258,
     PLUS = 259,
     MINUS = 260,
     MUL = 261,
     DIV = 262,
     number = 263,
     AND = 264,
     OR = 265,
     NOT = 266,
     if_x = 267,
     else_x = 268,
     while_x = 269,
     for_x = 270,
     return_x = 271,
     printf_x = 272,
     main_x = 273,
     assignmentop = 274,
     comparisionop = 275,
     logicalop = 276,
     datatype = 277,
     unary = 278,
     identifier = 279,
     string = 280,
     character = 281,
     cout = 282,
     cin = 283,
     insert = 284,
     extract = 285,
     header = 286,
     LBRACE = 287,
     RBRACE = 288,
     LPAREN = 289,
     RPAREN = 290,
     SEMICOLON = 291,
     COMMA = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 252 "temp2.y"

    int num;
    char *str;
	struct TreeNode *node;



/* Line 214 of yacc.c  */
#line 406 "temp2.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 418 "temp2.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNRULES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    14,    15,    18,    21,
      24,    26,    27,    29,    32,    35,    37,    47,    52,    55,
      56,    60,    63,    65,    66,    67,    68,    70,    73,    75,
      77,    79,    81,    83,    85,    88,    91,    93,    98,   102,
     104,   108,   116,   131,   141,   153,   157,   160,   164,   168,
     172,   175,   178,   182,   186,   189,   193,   197,   198,   203,
     205,   207,   211,   215,   219,   223,   228,   233,   236,   240,
     244,   246,   250,   254,   256,   258,   260,   264,   266,   269,
     272
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    41,    40,    -1,     3,    39,    -1,    39,
       3,    -1,     3,    -1,    -1,    42,    40,    -1,     3,    42,
      -1,    42,     3,    -1,     3,    -1,    -1,    31,    -1,    31,
      41,    -1,     3,    41,    -1,     3,    -1,    22,    24,    34,
      43,    35,    32,    44,    53,    33,    -1,    22,    24,    37,
      43,    -1,    22,    24,    -1,    -1,    47,    45,    44,    -1,
       3,    44,    -1,     3,    -1,    -1,    -1,    -1,    58,    -1,
      62,    36,    -1,    52,    -1,    50,    -1,    51,    -1,    54,
      -1,    56,    -1,    53,    -1,    48,    36,    -1,     1,    36,
      -1,     3,    -1,    24,    34,    49,    35,    -1,    24,    34,
      35,    -1,    24,    -1,    24,    37,    49,    -1,    12,    34,
      63,    35,    32,    44,    33,    -1,    12,    34,    63,    35,
      45,    32,    44,    33,    46,    13,    45,    32,    44,    33,
      -1,    14,    45,    34,    63,    35,    45,    32,    44,    33,
      -1,    15,    34,    58,    63,    36,    45,    63,    35,    32,
      44,    33,    -1,    16,    63,    36,    -1,    16,    36,    -1,
      27,    55,    36,    -1,    29,    63,    55,    -1,    29,    25,
      55,    -1,    29,    63,    -1,    29,    25,    -1,    28,    57,
      36,    -1,    30,    24,    57,    -1,    30,    24,    -1,    22,
      59,    36,    -1,    59,    37,    24,    -1,    -1,    59,    60,
      37,    61,    -1,    61,    -1,    24,    -1,    24,    19,    63,
      -1,    24,    19,    63,    -1,    24,    19,    63,    -1,    63,
      20,    63,    -1,    63,     9,    45,    63,    -1,    63,    10,
      45,    63,    -1,    11,    63,    -1,    63,     4,    64,    -1,
      63,     5,    64,    -1,    64,    -1,    64,     6,    65,    -1,
      64,     7,    65,    -1,    65,    -1,     8,    -1,    26,    -1,
      34,    63,    35,    -1,    24,    -1,    23,    24,    -1,    24,
      23,    -1,    25,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   267,   267,   268,   269,   270,   271,   273,   274,   275,
     276,   277,   280,   281,   282,   283,   285,   293,   299,   305,
     309,   314,   315,   316,   319,   320,   322,   323,   324,   325,
     327,   328,   329,   330,   331,   332,   333,   335,   340,   343,
     344,   347,   348,   367,   377,   386,   387,   389,   391,   392,
     393,   394,   396,   398,   399,   403,   405,   411,   411,   415,
     419,   426,   437,   446,   447,   479,   489,   499,   500,   501,
     502,   505,   506,   507,   510,   511,   512,   513,   514,   515,
     516
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EOL", "PLUS", "MINUS", "MUL", "DIV",
  "number", "AND", "OR", "NOT", "if_x", "else_x", "while_x", "for_x",
  "return_x", "printf_x", "main_x", "assignmentop", "comparisionop",
  "logicalop", "datatype", "unary", "identifier", "string", "character",
  "cout", "cin", "insert", "extract", "header", "LBRACE", "RBRACE",
  "LPAREN", "RPAREN", "SEMICOLON", "COMMA", "$accept", "program",
  "function_declarations", "headers", "function_declaration",
  "parameter_list", "statement_list", "M", "N", "statement",
  "function_call", "arg_list", "if_statement", "while_statement",
  "for_statement", "return_statement", "cout_statement",
  "insert_statement", "cin_statement", "extract_statement",
  "declaration_statement", "id_list", "$@1", "dec_assignment",
  "assignment_statement", "E", "T", "F", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    39,    39,    39,    40,    40,    40,
      40,    40,    41,    41,    41,    41,    42,    43,    43,    43,
      44,    44,    44,    44,    45,    46,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    48,    48,    49,
      49,    50,    50,    51,    52,    53,    53,    54,    55,    55,
      55,    55,    56,    57,    57,    58,    59,    60,    59,    59,
      59,    61,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    64,    64,    64,    65,    65,    65,    65,    65,    65,
      65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     0,     2,     2,     2,
       1,     0,     1,     2,     2,     1,     9,     4,     2,     0,
       3,     2,     1,     0,     0,     0,     1,     2,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     4,     3,     1,
       3,     7,    14,     9,    11,     3,     2,     3,     3,     3,
       2,     2,     3,     3,     2,     3,     3,     0,     4,     1,
       1,     3,     3,     3,     3,     4,     4,     2,     3,     3,
       1,     3,     3,     1,     1,     1,     3,     1,     2,     2,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     5,    12,     0,    11,     3,    11,    15,    13,     1,
       4,    10,     0,     2,    11,    14,     8,     0,     9,     7,
      19,     0,     0,    18,     0,    19,     0,    17,     0,     0,
       0,    24,     0,     0,     0,     0,     0,     0,     0,    24,
       0,    29,    30,    28,    33,    31,    32,    26,     0,    35,
      21,     0,     0,     0,    74,     0,     0,    77,    80,    75,
       0,    46,     0,    70,    73,    60,     0,    59,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    27,     0,     0,
       0,    67,    78,     0,    79,     0,     0,     0,    24,    24,
       0,    45,     0,     0,     0,    55,     0,     0,    62,    39,
      38,     0,    80,    50,    47,    54,    52,    16,    20,     0,
       0,     0,    63,    76,    77,    68,    69,     0,     0,    64,
      71,    72,    61,    56,     0,     0,    37,    49,    48,    53,
       0,     0,    24,    24,    65,    66,     0,    58,    40,     0,
       0,     0,     0,    41,     0,     0,     0,    25,     0,     0,
       0,    43,     0,    24,     0,     0,    44,     0,     0,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,    13,     4,    14,    22,    38,    52,   150,    39,
      40,   101,    41,    42,    43,    44,    45,    71,    46,    73,
      47,    66,    97,    67,    48,    62,    63,    64
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -50
static const yytype_int16 yypact[] =
{
      29,    86,    82,    80,    15,    61,    15,    82,   -50,   -50,
     -50,   -19,    31,   -50,    37,   -50,   -50,    36,   -19,   -50,
      64,    67,    53,    59,    68,    64,   145,   -50,    66,    11,
      78,   -50,    84,   119,    98,   -12,    97,   103,   118,   -50,
     104,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   105,   -50,
     -50,   154,   117,   127,   -50,   154,   128,    30,   -50,   -50,
     154,   -50,     0,    10,   -50,   135,    -8,   -50,   154,   -11,
     160,   120,   134,   130,   131,    51,   -50,   -50,    52,   154,
     154,   188,   -50,   154,   -50,    72,   113,   113,   -50,   -50,
     154,   -50,   113,   113,   154,   -50,   139,   133,   188,   137,
     -50,   147,   -21,   186,   -50,   103,   -50,   -50,   -50,   155,
      94,    38,   188,   -50,   166,    10,    10,   154,   154,   188,
     -50,   -50,   188,   -50,   175,   176,   -50,   -50,   -50,   -50,
      51,   169,   -50,   -50,   188,   188,   135,   -50,   -50,   170,
      51,   172,   154,   -50,   177,    51,   115,   -50,   178,   173,
     189,   -50,    51,   -50,   179,   181,   -50,    51,   183,   -50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -50,   206,   195,   174,    79,   192,   -29,   -38,   -50,   -50,
     -50,    89,   -50,   -50,   -50,   180,   -50,     3,   -50,   114,
     167,   -50,   -50,    99,   -50,   -49,    23,    39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -52
static const yytype_int16 yytable[] =
{
      50,    75,    78,    12,    86,    87,    81,    68,    70,    88,
      89,    85,    28,    99,    29,   -51,    92,    93,    11,    98,
      90,   103,    69,    30,   100,    31,    32,    33,    95,    96,
     110,   111,     1,    34,   112,    35,    91,    12,    36,    37,
      18,   119,    86,    87,   -22,   122,   108,    88,    89,    83,
     117,   118,    28,    84,    29,    17,    86,    87,    90,    12,
       2,    88,    89,    30,    10,    31,    32,    33,   134,   135,
      20,   131,    90,    34,   133,    35,    86,    87,    36,    37,
       9,    88,    89,    10,   -23,     7,    21,   109,    24,     1,
      16,    23,    90,   146,   141,   142,    25,    16,    86,    87,
      26,   139,    49,    88,    89,   127,   128,   113,   -15,   115,
     116,   144,    51,     2,    90,   155,   148,     2,    53,    86,
      87,    54,    65,   154,    88,    89,    70,    54,   158,   132,
      55,   120,   121,    72,    33,    90,    56,   114,    58,    59,
      76,    77,    56,    57,    58,    59,    28,    60,    29,    34,
     149,    79,    82,    60,    94,    61,   104,    30,   105,    31,
      32,    33,    54,   123,   107,    55,   106,    34,    54,    35,
     124,    55,    36,    37,   125,     6,     8,    56,    57,    58,
      59,    15,   126,    56,    57,   102,    59,   130,    60,    84,
      86,    87,    86,    87,    60,    88,    89,    88,    89,   136,
      99,   140,   153,   143,   145,   152,    90,     5,    90,    19,
     147,   151,   156,   157,   138,    70,   159,    27,    74,   129,
      80,     0,     0,   137
};

static const yytype_int16 yycheck[] =
{
      29,    39,    51,    22,     4,     5,    55,    19,    29,     9,
      10,    60,     1,    24,     3,    36,     6,     7,     3,    68,
      20,    70,    34,    12,    35,    14,    15,    16,    36,    37,
      79,    80,     3,    22,    83,    24,    36,    22,    27,    28,
       3,    90,     4,     5,    33,    94,    75,     9,    10,    19,
      88,    89,     1,    23,     3,    24,     4,     5,    20,    22,
      31,     9,    10,    12,     3,    14,    15,    16,   117,   118,
      34,   109,    20,    22,    36,    24,     4,     5,    27,    28,
       0,     9,    10,     3,    33,     3,    22,    35,    35,     3,
      11,    24,    20,   142,   132,   133,    37,    18,     4,     5,
      32,   130,    36,     9,    10,   102,   103,    35,    22,    86,
      87,   140,    34,    31,    20,   153,   145,    31,    34,     4,
       5,     8,    24,   152,     9,    10,    29,     8,   157,    35,
      11,    92,    93,    30,    16,    20,    23,    24,    25,    26,
      36,    36,    23,    24,    25,    26,     1,    34,     3,    22,
      35,    34,    24,    34,    19,    36,    36,    12,    24,    14,
      15,    16,     8,    24,    33,    11,    36,    22,     8,    24,
      37,    11,    27,    28,    37,     1,     2,    23,    24,    25,
      26,     7,    35,    23,    24,    25,    26,    32,    34,    23,
       4,     5,     4,     5,    34,     9,    10,     9,    10,    24,
      24,    32,    13,    33,    32,    32,    20,     1,    20,    14,
      33,    33,    33,    32,   125,    29,    33,    25,    38,   105,
      53,    -1,    -1,   124
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    31,    39,    41,    39,    41,     3,    41,     0,
       3,     3,    22,    40,    42,    41,    42,    24,     3,    40,
      34,    22,    43,    24,    35,    37,    32,    43,     1,     3,
      12,    14,    15,    16,    22,    24,    27,    28,    44,    47,
      48,    50,    51,    52,    53,    54,    56,    58,    62,    36,
      44,    34,    45,    34,     8,    11,    23,    24,    25,    26,
      34,    36,    63,    64,    65,    24,    59,    61,    19,    34,
      29,    55,    30,    57,    53,    45,    36,    36,    63,    34,
      58,    63,    24,    19,    23,    63,     4,     5,     9,    10,
      20,    36,     6,     7,    19,    36,    37,    60,    63,    24,
      35,    49,    25,    63,    36,    24,    36,    33,    44,    35,
      63,    63,    63,    35,    24,    64,    64,    45,    45,    63,
      65,    65,    63,    24,    37,    37,    35,    55,    55,    57,
      32,    45,    35,    36,    63,    63,    24,    61,    49,    44,
      32,    45,    45,    33,    44,    32,    63,    33,    44,    35,
      46,    33,    32,    13,    44,    45,    33,    32,    44,    33
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 267 "temp2.y"
    {  (yyval.node) = create_Node("program", -1, "NULL","NULL", 2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node));if(!head) head = (yyval.node);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 268 "temp2.y"
    { (yyval.node) = create_Node("program", -1, "NULL","NULL", 1,(yyvsp[(2) - (2)].node));if(!head) head = (yyval.node);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 269 "temp2.y"
    { (yyval.node) = create_Node("program", -1, "NULL","NULL", 1,(yyvsp[(1) - (2)].node));if(!head) head = (yyval.node);;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 270 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 273 "temp2.y"
    { (yyval.node) = create_Node("function_declarations", -1, "NULL","NULL", 2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 274 "temp2.y"
    { (yyval.node) = create_Node("function_declarations", -1, "NULL","NULL", 1,(yyvsp[(2) - (2)].node)); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 275 "temp2.y"
    { (yyval.node) = create_Node("function_declarations", -1, "NULL","NULL", 1,(yyvsp[(1) - (2)].node)); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 276 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 280 "temp2.y"
    {(yyval.node) = create_Node("headers", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 281 "temp2.y"
    { (yyval.node) = create_Node("headers", -1,"NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 282 "temp2.y"
    { (yyval.node) = create_Node("headers", -1, "NULL","NULL",1, (yyvsp[(2) - (2)].node));;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 283 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 285 "temp2.y"
    {
	(yyvsp[(2) - (9)].node)->dtype = (yyvsp[(1) - (9)].node)->dtype;
	(yyval.node) = create_Node("function_declaration", -1, "NULL","NULL", 8, (yyvsp[(1) - (9)].node),(yyvsp[(2) - (9)].node),(yyvsp[(3) - (9)].node), (yyvsp[(4) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(6) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(8) - (9)].node)); 
	(yyval.node)->value = (yyvsp[(4) - (9)].node)->value;
	addEntry((yyvsp[(2) - (9)].node)->value_str,(yyvsp[(2) - (9)].node)->dtype,(yyvsp[(2) - (9)].node)->scope,(yyvsp[(4) - (9)].node)->value);
	addFunctionValue((yyvsp[(2) - (9)].node)->value_str, (yyvsp[(4) - (9)].node)->value);
;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 293 "temp2.y"
    { 
	(yyval.node) = create_Node("parameter_list", -1, "NULL","NULL",4, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
	(yyvsp[(2) - (4)].node)->dtype = (yyvsp[(1) - (4)].node)->dtype;
	(yyval.node)->value = (yyvsp[(4) - (4)].node)->value + 1;
	addEntry((yyvsp[(2) - (4)].node)->value_str,(yyvsp[(2) - (4)].node)->dtype,(yyvsp[(2) - (4)].node)->scope,(yyvsp[(2) - (4)].node)->value);
	 ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 299 "temp2.y"
    {
	(yyvsp[(2) - (2)].node)->dtype = (yyvsp[(1) - (2)].node)->dtype;
	(yyval.node) = create_Node("parameter_list", -1, "NULL","NULL",2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
	(yyval.node)->value = 1;
	addEntry((yyvsp[(2) - (2)].node)->value_str,(yyvsp[(2) - (2)].node)->dtype,(yyvsp[(2) - (2)].node)->scope,(yyvsp[(2) - (2)].node)->value);
 ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 305 "temp2.y"
    { (yyval.node) = create_Node("parameter_list", -1, "NULL","NULL",0); (yyval.node)->value = 0 ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 309 "temp2.y"
    { 
			(yyval.node) = create_Node("statement_list", -1, "NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
			backpatch((yyvsp[(1) - (3)].node)->nextList,(yyvsp[(2) - (3)].node)->nextList->curr);
			(yyval.node)->nextList = (yyvsp[(3) - (3)].node)->nextList;
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 314 "temp2.y"
    { (yyval.node) = create_Node("statement_list", -1, "NULL","NULL", 1, (yyvsp[(2) - (2)].node));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 315 "temp2.y"
    {(yyval.node) = NULL;;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 319 "temp2.y"
    {(yyval.node) = create_Node("M", -1, "st_if","NULL", 0);(yyval.node)->nextList = newList(icgIndex);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 320 "temp2.y"
    {(yyval.node) = create_Node("N", -1, "st_if","NULL", 0);(yyval.node)->nextList = newList(icgIndex);generateCode("goto","","","");;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 322 "temp2.y"
    { (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 323 "temp2.y"
    {printf("assignment_statement\n"); (yyval.node) = create_Node("statement", -1,"NULL","NULL",2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 324 "temp2.y"
    {printf("for_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 325 "temp2.y"
    {printf("if_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 327 "temp2.y"
    {printf("while_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 328 "temp2.y"
    {printf("cout_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 329 "temp2.y"
    {printf("cin_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 330 "temp2.y"
    {printf("return_statement\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 331 "temp2.y"
    {printf("function_call\n"); (yyval.node) = create_Node("statement", -1, "NULL","NULL",2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 332 "temp2.y"
    { (yyval.node) = create_Node("error", -1, "NULL","NULL",0); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 333 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 335 "temp2.y"
    { 
		(yyval.node) = create_Node("function_call", -1, "NULL","NULL", 4, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node)); 
		(yyvsp[(1) - (4)].node)->value = (yyvsp[(3) - (4)].node)->value;
		checkfnArguments((yyvsp[(1) - (4)].node));
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 340 "temp2.y"
    { (yyval.node) = create_Node("function_call", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 343 "temp2.y"
    { (yyval.node) = create_Node("arg_list", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); (yyval.node)->value = 1; ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 344 "temp2.y"
    { (yyval.node) = create_Node("arg_list", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); (yyval.node)->value = (yyvsp[(3) - (3)].node)->value + 1; ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 347 "temp2.y"
    { (yyval.node) = create_Node("if_statement", -1,"NULL","NULL", 7,(yyvsp[(1) - (7)].node),(yyvsp[(2) - (7)].node),(yyvsp[(3) - (7)].node),(yyvsp[(4) - (7)].node),(yyvsp[(5) - (7)].node),(yyvsp[(6) - (7)].node),(yyvsp[(7) - (7)].node));backpatch((yyvsp[(3) - (7)].node)->trueList,(yyvsp[(6) - (7)].node)->nextList->curr);(yyval.node)->nextList = mergeList((yyvsp[(3) - (7)].node)->falseList,(yyvsp[(7) - (7)].node)->nextList);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 348 "temp2.y"
    {
		(yyval.node) = create_Node("if_statement", -1,"NULL","NULL", 13,(yyvsp[(1) - (14)].node),(yyvsp[(2) - (14)].node),(yyvsp[(3) - (14)].node),(yyvsp[(4) - (14)].node),(yyvsp[(5) - (14)].node),(yyvsp[(6) - (14)].node),(yyvsp[(7) - (14)].node),(yyvsp[(8) - (14)].node),(yyvsp[(9) - (14)].node),(yyvsp[(10) - (14)].node),(yyvsp[(11) - (14)].node),(yyvsp[(12) - (14)].node),(yyvsp[(13) - (14)].node));
		backpatch((yyvsp[(3) - (14)].node)->trueList,(yyvsp[(6) - (14)].node)->nextList->curr);
		backpatch((yyvsp[(3) - (14)].node)->falseList,(yyvsp[(10) - (14)].node)->nextList->curr);
		(yyval.node)->nextList = mergeList(mergeList((yyvsp[(7) - (14)].node)->nextList,(yyvsp[(9) - (14)].node)->nextList),(yyvsp[(13) - (14)].node)->nextList);
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 367 "temp2.y"
    {
	(yyval.node) = create_Node("while_statement", -1, "NULL","NULL", 9, (yyvsp[(1) - (9)].node), (yyvsp[(2) - (9)].node), (yyvsp[(3) - (9)].node), (yyvsp[(4) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(6) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(8) - (9)].node), (yyvsp[(9) - (9)].node));
	backpatch((yyvsp[(4) - (9)].node)->trueList,(yyvsp[(7) - (9)].node)->nextList->curr);
	backpatch((yyvsp[(8) - (9)].node)->nextList,(yyvsp[(2) - (9)].node)->nextList->curr);
	(yyval.node)->nextList = (yyvsp[(4) - (9)].node)->falseList;
	char *x = malloc(10);
	sprintf(x,"L%d",(yyvsp[(2) - (9)].node)->nextList->curr);
	generateCode("goto","","",x);
 ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 377 "temp2.y"
    { 
	(yyval.node) = create_Node("for_statement", -1, "NULL","NULL", 11, (yyvsp[(1) - (11)].node), (yyvsp[(2) - (11)].node), (yyvsp[(3) - (11)].node), (yyvsp[(4) - (11)].node), (yyvsp[(5) - (11)].node), (yyvsp[(6) - (11)].node), (yyvsp[(7) - (11)].node), (yyvsp[(8) - (11)].node), (yyvsp[(9) - (11)].node), (yyvsp[(10) - (11)].node),(yyvsp[(11) - (11)].node));
	backpatch((yyvsp[(4) - (11)].node)->nextList,(yyvsp[(10) - (11)].node)->nextList->curr);
	backpatch((yyvsp[(10) - (11)].node)->nextList,(yyvsp[(6) - (11)].node)->nextList->curr);
	backpatch((yyvsp[(10) - (11)].node)->nextList,(yyvsp[(2) - (11)].node)->nextList->curr);
	// $$->nextList = $10->nextList;
;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 386 "temp2.y"
    { (yyval.node) = create_Node("return_statement", -1,"NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node)); generateCode("return", "", "", (yyvsp[(2) - (3)].node)->label) ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 387 "temp2.y"
    { (yyval.node) = create_Node("return_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); generateCode("return", "","", "");}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 389 "temp2.y"
    { (yyval.node) = create_Node("cout_statement", -1,"NULL","NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 391 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1,"NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 392 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 393 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 394 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 396 "temp2.y"
    { (yyval.node) = create_Node("cin_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 398 "temp2.y"
    { (yyval.node) = create_Node("extract_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 399 "temp2.y"
    { (yyval.node) = create_Node("extract_statement", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 403 "temp2.y"
    { (yyvsp[(2) - (3)].node)->dtype = (yyvsp[(1) - (3)].node)->dtype;  (yyval.node) = create_Node("declaration_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 405 "temp2.y"
    {
	(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); 
	(yyvsp[(3) - (3)].node)->dtype = (yyvsp[(0) - (3)].node)->dtype;
	(yyvsp[(1) - (3)].node)->dtype = (yyvsp[(0) - (3)].node)->dtype;
	addEntry((yyvsp[(3) - (3)].node)->value_str,(yyvsp[(3) - (3)].node)->dtype,(yyvsp[(3) - (3)].node)->scope,(yyvsp[(3) - (3)].node)->value);
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 411 "temp2.y"
    {(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(0) - (1)].node)->dtype;;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 411 "temp2.y"
    {
	(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 3, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
	(yyvsp[(3) - (4)].node)->dtype = (yyvsp[(0) - (4)].node)->dtype;
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 415 "temp2.y"
    {
	(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));
	(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(0) - (1)].node)->dtype; 
;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 419 "temp2.y"
    { 
	(yyval.node) = create_Node("id_list", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));
	(yyvsp[(1) - (1)].node)->dtype = (yyvsp[(-1) - (1)].node)->dtype;
	addEntry((yyvsp[(1) - (1)].node)->value_str,(yyvsp[(1) - (1)].node)->dtype,(yyvsp[(1) - (1)].node)->scope,(yyvsp[(1) - (1)].node)->value); 
;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 426 "temp2.y"
    { 
		(yyval.node) = create_Node("dec_assignment", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); 
		checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
		(yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value;
		(yyvsp[(1) - (3)].node)->dtype = (yyvsp[(0) - (3)].node)->dtype; 
		addEntry((yyvsp[(1) - (3)].node)->value_str,(yyvsp[(1) - (3)].node)->dtype,(yyvsp[(1) - (3)].node)->scope,(yyvsp[(1) - (3)].node)->value);
		generateCode("=", (yyvsp[(3) - (3)].node)->label, "", (yyvsp[(1) - (3)].node)->label);

	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 437 "temp2.y"
    {
		(yyval.node) = create_Node("assignment_statement", -1, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));
		(yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value;
		checkid((yyvsp[(1) - (3)].node));
		checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
		generateCode("=", (yyvsp[(3) - (3)].node)->label, "", (yyvsp[(1) - (3)].node)->label);
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 446 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); (yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value;  checkid((yyvsp[(1) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 447 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); 
			(yyval.node)->trueList = newList(icgIndex);
			(yyval.node)->falseList = newList(icgIndex+1);
			char *x = malloc(strlen((yyvsp[(2) - (3)].node)->label)+strlen((yyvsp[(1) - (3)].node)->label)+strlen((yyvsp[(3) - (3)].node)->label)+1);
			int k = 0;
			for(int i = 0;i<strlen((yyvsp[(1) - (3)].node)->label);i++){
				x[k++] = (yyvsp[(1) - (3)].node)->label[i];
			}
			for(int i = 0;i<strlen((yyvsp[(2) - (3)].node)->label);i++){
				x[k++] = (yyvsp[(2) - (3)].node)->label[i];
			}
			for(int i = 0;i<strlen((yyvsp[(3) - (3)].node)->label);i++){
				x[k++] = (yyvsp[(3) - (3)].node)->label[i];
			}
			generateCode("if", x,"goto","");
			generateCode("goto","","","");
			if (strcmp((yyvsp[(2) - (3)].node)->value_str, "<=") == 0) {
				(yyval.node)->value = (yyvsp[(1) - (3)].node)->value <= (yyvsp[(3) - (3)].node)->value;
			} else if (strcmp((yyvsp[(2) - (3)].node)->value_str, ">=") == 0) {
				(yyval.node)->value = (yyvsp[(1) - (3)].node)->value >= (yyvsp[(3) - (3)].node)->value;
			} else if (strcmp((yyvsp[(2) - (3)].node)->value_str, "==") == 0) {
				(yyval.node)->value = (yyvsp[(1) - (3)].node)->value == (yyvsp[(3) - (3)].node)->value;
			} else if (strcmp((yyvsp[(2) - (3)].node)->value_str, "!=") == 0) {
				(yyval.node)->value = (yyvsp[(1) - (3)].node)->value != (yyvsp[(3) - (3)].node)->value;
			}
			else if (strcmp((yyvsp[(2) - (3)].node)->value_str, "<") == 0) {
				(yyval.node)->value = (yyvsp[(1) - (3)].node)->value < (yyvsp[(3) - (3)].node)->value;
			}
			else if (strcmp((yyvsp[(2) - (3)].node)->value_str, ">") == 0) {
				(yyval.node)->value = (yyvsp[(1) - (3)].node)->value > (yyvsp[(3) - (3)].node)->value;
			}
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 479 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node)); checkType((yyvsp[(1) - (4)].node),(yyvsp[(3) - (4)].node)); 
		if (strcmp((yyvsp[(2) - (4)].node)->value_str, "&&") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (4)].node)->value && (yyvsp[(3) - (4)].node)->value;
		} else if (strcmp((yyvsp[(2) - (4)].node)->value_str, "||") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (4)].node)->value || (yyvsp[(3) - (4)].node)->value;
		}
		backpatch((yyvsp[(1) - (4)].node)->trueList, (yyvsp[(3) - (4)].node)->nextList->curr);
		(yyval.node)->trueList = (yyvsp[(4) - (4)].node)->trueList;
		(yyval.node)->falseList = mergeList((yyvsp[(1) - (4)].node)->falseList, (yyvsp[(4) - (4)].node)->falseList);
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 489 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL","NULL", 3, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node)); checkType((yyvsp[(1) - (4)].node),(yyvsp[(3) - (4)].node)); 
		if (strcmp((yyvsp[(2) - (4)].node)->value_str, "&&") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (4)].node)->value && (yyvsp[(3) - (4)].node)->value;
		} else if (strcmp((yyvsp[(2) - (4)].node)->value_str, "||") == 0) {
			(yyval.node)->value = (yyvsp[(1) - (4)].node)->value || (yyvsp[(3) - (4)].node)->value;
		}
		backpatch((yyvsp[(1) - (4)].node)->falseList, (yyvsp[(3) - (4)].node)->nextList->curr);
		(yyval.node)->falseList = (yyvsp[(4) - (4)].node)->falseList;
		(yyval.node)->trueList = mergeList((yyvsp[(1) - (4)].node)->trueList, (yyvsp[(4) - (4)].node)->trueList);
	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 499 "temp2.y"
    { (yyval.node) = create_Node("E", !(yyvsp[(2) - (2)].node)->value,  "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); (yyval.node)->value = !(yyvsp[(2) - (2)].node)->value; (yyval.node)->trueList = (yyvsp[(2) - (2)].node)->falseList; (yyval.node)->falseList = (yyvsp[(2) - (2)].node)->trueList; ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 500 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (3)].node)->value+(yyvsp[(3) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); generateCode("+", (yyvsp[(1) - (3)].node)->label, (yyvsp[(3) - (3)].node)->label, (yyval.node)->label); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 501 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (3)].node)->value-(yyvsp[(3) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); generateCode("-", (yyvsp[(1) - (3)].node)->label, (yyvsp[(3) - (3)].node)->label, (yyval.node)->label);;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 502 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (1)].node)->value, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));  (yyval.node)->value = (yyvsp[(1) - (1)].node)->value; (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype; ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 505 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (3)].node)->value*(yyvsp[(3) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); generateCode("*", (yyvsp[(1) - (3)].node)->label, (yyvsp[(3) - (3)].node)->label, (yyval.node)->label);;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 506 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (3)].node)->value/(yyvsp[(3) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));checkType((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); generateCode("/", (yyvsp[(1) - (3)].node)->label, (yyvsp[(3) - (3)].node)->label, (yyval.node)->label);;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 507 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (1)].node)->value, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype;  (yyval.node)->value = (yyvsp[(1) - (1)].node)->value;;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 510 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));  (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype; (yyval.node)->value = (yyvsp[(1) - (1)].node)->value;  ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 511 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node));  (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype;  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 512 "temp2.y"
    { (yyval.node) = create_Node("F",(yyvsp[(2) - (3)].node)->value, "NULL","NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));  (yyval.node)->dtype = (yyvsp[(2) - (3)].node)->dtype;  ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 513 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); checkid((yyvsp[(1) - (1)].node));  (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->dtype; ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 514 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); checkid((yyvsp[(2) - (2)].node));  (yyval.node)->dtype = (yyvsp[(2) - (2)].node)->dtype; generateCode((yyvsp[(1) - (2)].node)->value_str, (yyvsp[(2) - (2)].node)->label, "", (yyvsp[(2) - (2)].node)->label); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 515 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); checkid((yyvsp[(1) - (2)].node));  (yyval.node)->dtype = (yyvsp[(1) - (2)].node)->dtype; generateCode((yyvsp[(2) - (2)].node)->value_str, (yyvsp[(1) - (2)].node)->label, "", (yyvsp[(1) - (2)].node)->label); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 516 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL","NULL", 1, (yyvsp[(1) - (1)].node)); (yyval.node)->dtype = (yyvsp[(1) - (1)].node)->label;;}
    break;



/* Line 1455 of yacc.c  */
#line 2418 "temp2.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 519 "temp2.y"

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
	printf("Intermediate Code Generation\n");
	displayICG();
}
