
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

	
	TreeNode *head = NULL;
	struct TreeNode *create_Node(char *label, int value, char *value_str, int num_children, ...) {
		struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
		newNode->label = label;
		newNode->value = value;
		newNode->value_str = (char*)malloc(sizeof(char) * strlen(value_str) + 1);
		strcpy(newNode->value_str,value_str);
		newNode->num_children = num_children;
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

		if(root->value ==-1 && strcmp(root->value_str,"NULL") == 0){
			printf("%d.%s\n",level, root->label);
		}else if(root->value == -1){
			printf("%d.%s\n", level,root->value_str);
		}else{
			printf("%d.(%s,%d)\n",level, root->label, root->value);
		}
		// printf("(%s,%d)\n", root->label,root->value);
		for(int i = 0;i<root->num_children;i++){
			printTree(root->children[i],level+1);
		}
	}


/* Line 189 of yacc.c  */
#line 139 "temp2.tab.c"

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
     if_x = 264,
     else_x = 265,
     while_x = 266,
     for_x = 267,
     return_x = 268,
     printf_x = 269,
     main_x = 270,
     assignmentop = 271,
     comparisionop = 272,
     logicalop = 273,
     datatype = 274,
     unary = 275,
     identifier = 276,
     string = 277,
     character = 278,
     cout = 279,
     cin = 280,
     insert = 281,
     extract = 282,
     header = 283,
     LBRACE = 284,
     RBRACE = 285,
     LPAREN = 286,
     RPAREN = 287,
     SEMICOLON = 288,
     COMMA = 289
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 66 "temp2.y"

    int num;
    char *str;
	struct TreeNode *node;



/* Line 214 of yacc.c  */
#line 217 "temp2.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 229 "temp2.tab.c"

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
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   327

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  135

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     7,    10,    13,    15,    16,    18,    22,
      25,    27,    37,    42,    45,    47,    48,    51,    54,    56,
      57,    59,    62,    64,    66,    68,    70,    72,    74,    76,
      79,    81,    89,    95,    98,   103,   106,   109,   112,   120,
     131,   135,   138,   142,   146,   150,   153,   156,   160,   164,
     167,   171,   175,   179,   181,   183,   187,   191,   195,   199,
     203,   205,   209,   213,   215,   217,   219,   223,   225,   228
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    37,    38,    36,    -1,    40,    36,    -1,
       3,    36,    -1,     3,    -1,    -1,    28,    -1,    37,     3,
      37,    -1,     3,    37,    -1,     3,    -1,    19,    21,    31,
      39,    32,    29,    40,    30,    40,    -1,    19,    21,    34,
      39,    -1,    19,    21,    -1,     3,    -1,    -1,    41,    40,
      -1,     3,    40,    -1,     3,    -1,    -1,    52,    -1,    54,
      33,    -1,    46,    -1,    42,    -1,    44,    -1,    45,    -1,
      48,    -1,    50,    -1,    47,    -1,     1,    33,    -1,     3,
      -1,     9,    31,    55,    32,    29,    40,    30,    -1,     9,
      31,    55,    32,    41,    -1,    42,     3,    -1,    10,    29,
      40,    30,    -1,    10,    41,    -1,    43,     3,    -1,    42,
      43,    -1,    11,    31,    55,    32,    29,    40,    30,    -1,
      12,    31,    52,    55,    33,    55,    32,    29,    40,    30,
      -1,    13,    55,    33,    -1,    13,    33,    -1,    24,    49,
      33,    -1,    26,    55,    49,    -1,    26,    22,    49,    -1,
      26,    55,    -1,    26,    22,    -1,    25,    51,    33,    -1,
      27,    21,    51,    -1,    27,    21,    -1,    19,    53,    33,
      -1,    21,    34,    53,    -1,    54,    34,    53,    -1,    54,
      -1,    21,    -1,    57,    16,    55,    -1,    57,    16,    55,
      -1,    55,    17,    56,    -1,    55,     4,    56,    -1,    55,
       5,    56,    -1,    56,    -1,    56,     6,    57,    -1,    56,
       7,    57,    -1,    57,    -1,     8,    -1,    23,    -1,    31,
      55,    32,    -1,    21,    -1,    20,    21,    -1,    21,    20,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    80,    80,    81,    82,    83,    84,    87,    88,    89,
      90,    92,    94,    95,    96,    97,   101,   102,   103,   104,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   120,   121,   122,   124,   125,   126,   129,   131,   133,
     135,   136,   138,   140,   141,   142,   143,   145,   147,   148,
     151,   153,   154,   155,   156,   159,   162,   163,   180,   181,
     182,   186,   187,   188,   192,   193,   194,   195,   196,   197
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EOL", "PLUS", "MINUS", "MUL", "DIV",
  "number", "if_x", "else_x", "while_x", "for_x", "return_x", "printf_x",
  "main_x", "assignmentop", "comparisionop", "logicalop", "datatype",
  "unary", "identifier", "string", "character", "cout", "cin", "insert",
  "extract", "header", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "SEMICOLON",
  "COMMA", "$accept", "program", "headers", "function_declaration",
  "parameter_list", "statement_list", "statement", "if_statement",
  "else_statement", "if_else_statement", "while_statement",
  "for_statement", "return_statement", "cout_statement",
  "insert_statement", "cin_statement", "extract_statement",
  "declaration_statement", "id_list", "assignment_statement", "E", "T",
  "F", 0
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
     285,   286,   287,   288,   289
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    36,    36,    36,    36,    37,    37,    37,
      37,    38,    39,    39,    39,    39,    40,    40,    40,    40,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    42,    42,    42,    43,    43,    43,    44,    45,    46,
      47,    47,    48,    49,    49,    49,    49,    50,    51,    51,
      52,    53,    53,    53,    53,    54,    55,    55,    55,    55,
      55,    56,    56,    56,    57,    57,    57,    57,    57,    57
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     1,     0,     1,     3,     2,
       1,     9,     4,     2,     1,     0,     2,     2,     1,     0,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     7,     5,     2,     4,     2,     2,     2,     7,    10,
       3,     2,     3,     3,     3,     2,     2,     3,     3,     2,
       3,     3,     3,     1,     1,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     1,     1,     3,     1,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    64,     0,     0,     0,     0,     0,     0,
      67,    65,     0,     0,     7,     0,     0,     0,     0,     0,
      23,    24,    25,    22,    28,    26,    27,    20,     0,     0,
      29,     4,     0,     0,     0,     0,     0,    41,     0,    60,
      63,    54,     0,    53,    68,    69,     0,     0,     0,     0,
       0,     1,     0,     0,     0,     3,     0,    16,    33,     0,
      37,    21,     0,     0,     0,     0,     0,     0,     0,    40,
       0,     0,     0,     0,    50,     0,    46,    45,    42,    49,
      47,    66,    10,     8,     0,     2,    17,    30,     0,    35,
      36,    55,     0,     0,     0,    58,    63,    59,    57,    61,
      62,    56,    51,    52,    44,    43,    48,     9,    15,     0,
       0,    32,     0,     0,    14,     0,     0,    34,     0,     0,
       0,    13,     0,    31,    38,     0,    15,     0,     0,    12,
       0,     0,     0,    39,    11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    55,    17,    54,   116,    18,    19,    20,    60,    21,
      22,    23,    24,    25,    47,    26,    49,    27,    42,    28,
      38,    39,    29
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -61
static const yytype_int16 yypact[] =
{
     154,   -17,   180,   -61,   -10,    -4,    12,    24,   289,    27,
      54,   -61,    55,    56,   -61,   296,    84,    11,   154,    93,
      70,   -61,   -61,   -61,   -61,   -61,   -61,   -61,    62,    81,
     -61,   -61,    11,   154,   296,   296,    68,   -61,     3,    28,
      99,    51,    76,    85,   -61,   -61,    69,    89,   106,   102,
      14,   -61,     9,   111,   154,   -61,   128,   -61,   -61,   232,
     135,   -61,   296,    46,    71,   296,   296,   296,   296,   -61,
     296,   296,   296,   289,   -61,   289,    55,   245,   -61,    56,
     -61,   -61,     9,   141,   114,   -61,   -61,   -61,   257,   -61,
     -61,    94,   282,   121,     6,    28,   -61,    28,    28,   -61,
     -61,    94,   -61,   -61,   -61,   -61,   -61,   141,    30,   130,
     257,   -61,   257,   296,   -61,   143,   136,   -61,   139,   140,
     129,   137,   147,   -61,   -61,   155,    30,   257,   257,   -61,
     142,   156,   206,   -61,   -61
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,     4,     0,   -61,    61,    -2,   -54,   -61,   -61,   -61,
     -61,   -61,   -61,   -61,    66,   -61,   115,   159,   -60,    -5,
       7,   -42,    -6
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -68
static const yytype_int16 yytable[] =
{
      33,    40,    32,    43,    16,    89,    31,    66,    67,    40,
      66,    67,    82,   102,    52,   103,    30,    57,    66,    67,
      68,    34,    50,    68,    95,    97,    98,    35,    40,    40,
      53,    68,     3,   114,    70,    71,    69,    14,   111,   113,
      40,    63,    64,    36,     9,    10,    81,    11,    44,   115,
      66,    67,    83,    77,    86,    15,    40,    37,    85,    40,
      96,    96,    96,    68,    99,   100,    40,   -67,    43,    91,
      43,    45,    94,    58,    45,    66,    67,     3,    92,   101,
      59,    46,   107,    48,    51,    73,   109,     8,    68,     9,
      10,    76,    11,   -19,     1,    61,    56,    62,    66,    67,
      15,     3,     4,    93,     5,     6,     7,    40,   118,    74,
     119,    68,     8,     9,    10,    72,    11,    12,    13,    75,
     120,   -19,    78,   -19,    15,   130,   131,    79,   -18,     1,
     134,    56,    84,    66,    67,    80,     3,     4,    90,     5,
       6,     7,   104,   105,    52,   108,    68,     8,     9,    10,
     112,    11,    12,    13,    -6,     1,   -18,     2,   -18,    15,
     117,   125,     3,     4,   121,     5,     6,     7,   122,   123,
     124,   126,   132,     8,     9,    10,   127,    11,    12,    13,
      -5,     1,    14,     2,   128,    15,   133,   129,     3,     4,
       0,     5,     6,     7,   106,    65,     0,     0,     0,     8,
       9,    10,     0,    11,    12,    13,   -19,     1,    14,    56,
       0,    15,     0,     0,     3,     4,     0,     5,     6,     7,
       0,     0,     0,     0,     0,     8,     9,    10,     0,    11,
      12,    13,     0,     1,   -19,    87,     0,    15,     0,     0,
       3,     4,     0,     5,     6,     7,     0,     0,     0,    66,
      67,     8,     9,    10,     0,    11,    12,    13,     1,     0,
      56,    88,    68,    15,     0,     3,     4,     0,     5,     6,
       7,    46,     0,     0,     0,     0,     8,     9,    10,     0,
      11,    12,    13,     1,     0,    87,     0,   -19,    15,     0,
       3,     4,     0,     5,     6,     7,     0,     3,     0,     0,
       0,     8,     9,    10,     3,    11,    12,    13,     0,     9,
      41,   110,    11,    15,     0,     0,     9,    10,     0,    11,
      15,     0,     0,     0,     0,     0,     0,    15
};

static const yytype_int16 yycheck[] =
{
       2,     7,     2,     8,     0,    59,     2,     4,     5,    15,
       4,     5,     3,    73,     3,    75,    33,    19,     4,     5,
      17,    31,    15,    17,    66,    67,    68,    31,    34,    35,
      19,    17,     8,     3,     6,     7,    33,    28,    92,    33,
      46,    34,    35,    31,    20,    21,    32,    23,    21,    19,
       4,     5,    52,    46,    56,    31,    62,    33,    54,    65,
      66,    67,    68,    17,    70,    71,    72,    16,    73,    62,
      75,    20,    65,     3,    20,     4,     5,     8,    32,    72,
      10,    26,    82,    27,     0,    34,    88,    19,    17,    20,
      21,    22,    23,     0,     1,    33,     3,    16,     4,     5,
      31,     8,     9,    32,    11,    12,    13,   113,   110,    33,
     112,    17,    19,    20,    21,    16,    23,    24,    25,    34,
     113,    28,    33,    30,    31,   127,   128,    21,     0,     1,
     132,     3,    21,     4,     5,    33,     8,     9,     3,    11,
      12,    13,    76,    77,     3,    31,    17,    19,    20,    21,
      29,    23,    24,    25,     0,     1,    28,     3,    30,    31,
      30,    32,     8,     9,    21,    11,    12,    13,    32,    30,
      30,    34,    30,    19,    20,    21,    29,    23,    24,    25,
       0,     1,    28,     3,    29,    31,    30,   126,     8,     9,
      -1,    11,    12,    13,    79,    36,    -1,    -1,    -1,    19,
      20,    21,    -1,    23,    24,    25,     0,     1,    28,     3,
      -1,    31,    -1,    -1,     8,     9,    -1,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    19,    20,    21,    -1,    23,
      24,    25,    -1,     1,    28,     3,    -1,    31,    -1,    -1,
       8,     9,    -1,    11,    12,    13,    -1,    -1,    -1,     4,
       5,    19,    20,    21,    -1,    23,    24,    25,     1,    -1,
       3,    29,    17,    31,    -1,     8,     9,    -1,    11,    12,
      13,    26,    -1,    -1,    -1,    -1,    19,    20,    21,    -1,
      23,    24,    25,     1,    -1,     3,    -1,    30,    31,    -1,
       8,     9,    -1,    11,    12,    13,    -1,     8,    -1,    -1,
      -1,    19,    20,    21,     8,    23,    24,    25,    -1,    20,
      21,    29,    23,    31,    -1,    -1,    20,    21,    -1,    23,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     8,     9,    11,    12,    13,    19,    20,
      21,    23,    24,    25,    28,    31,    36,    37,    40,    41,
      42,    44,    45,    46,    47,    48,    50,    52,    54,    57,
      33,    36,    37,    40,    31,    31,    31,    33,    55,    56,
      57,    21,    53,    54,    21,    20,    26,    49,    27,    51,
      55,     0,     3,    19,    38,    36,     3,    40,     3,    10,
      43,    33,    16,    55,    55,    52,     4,     5,    17,    33,
       6,     7,    16,    34,    33,    34,    22,    55,    33,    21,
      33,    32,     3,    37,    21,    36,    40,     3,    29,    41,
       3,    55,    32,    32,    55,    56,    57,    56,    56,    57,
      57,    55,    53,    53,    49,    49,    51,    37,    31,    40,
      29,    41,    29,    33,     3,    19,    39,    30,    40,    40,
      55,    21,    32,    30,    30,    32,    34,    29,    29,    39,
      40,    40,    30,    30,    40
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
#line 80 "temp2.y"
    { printf("program No: %d\n",(yyval.node)); (yyval.node) = create_Node("program", -1, "NULL", 3,(yyvsp[(1) - (3)].node),(yyvsp[(2) - (3)].node),(yyvsp[(3) - (3)].node));head = (yyval.node);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 81 "temp2.y"
    {(yyval.node) = create_Node("program", -1, "NULL", 2,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); head = (yyval.node);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 82 "temp2.y"
    {(yyval.node) = create_Node("program", -1, "NULL", 1,(yyvsp[(2) - (2)].node)); head = (yyval.node);;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 83 "temp2.y"
    {(yyval.node) = NULL;;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 87 "temp2.y"
    {(yyval.node) = create_Node("headers", -1, "NULL",1,(yyvsp[(1) - (1)].node));;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 88 "temp2.y"
    { (yyval.node) = create_Node("headers", -1,"NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 89 "temp2.y"
    { (yyval.node) = create_Node("headers", -1, "NULL",1, (yyvsp[(2) - (2)].node));;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 90 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 92 "temp2.y"
    {printf("Function NO: %d\n",(yyval.node)); (yyval.node) = create_Node("function_declaration", -1, "NULL", 9, (yyvsp[(1) - (9)].node),(yyvsp[(2) - (9)].node),(yyvsp[(3) - (9)].node), (yyvsp[(4) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(6) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(8) - (9)].node), (yyvsp[(9) - (9)].node)); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 94 "temp2.y"
    { (yyval.node) = create_Node("parameter_list", -1, "NULL",4, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node)); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 95 "temp2.y"
    { (yyval.node) = create_Node("parameter_list", -1, "NULL",2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 96 "temp2.y"
    {(yyval.node) = NULL;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 97 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 101 "temp2.y"
    { (yyval.node) = create_Node("statement_list", -1, "NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 102 "temp2.y"
    { (yyval.node) = create_Node("statement_list", -1, "NULL", 1, (yyvsp[(2) - (2)].node));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 103 "temp2.y"
    {(yyval.node) = NULL;;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 107 "temp2.y"
    {printf("declaration_statement\n"); (yyval.node) = create_Node("declaration_statement", -1, "NULL",0); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 108 "temp2.y"
    {printf("assignment_statement\n"); (yyval.node) = create_Node("assignment_statement", -1,"NULL",2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 109 "temp2.y"
    {printf("for_statement\n"); (yyval.node) = create_Node("for_statement", -1, "NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 110 "temp2.y"
    {printf("if_statement\n"); (yyval.node) = create_Node("if_statement", -1, "NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 111 "temp2.y"
    {printf("if_else_statement\n"); (yyval.node) = create_Node("if_else_statement", -1, "NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 112 "temp2.y"
    {printf("while_statement\n"); (yyval.node) = create_Node("while_statement", -1, "NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 113 "temp2.y"
    {printf("cout_statement\n"); (yyval.node) = create_Node("cout_statement", -1, "NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 114 "temp2.y"
    {printf("cin_statement\n"); (yyval.node) = create_Node("cin_statement", -1, "NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 115 "temp2.y"
    {printf("return_statement\n"); (yyval.node) = create_Node("return_statement", -1, "NULL",1,(yyvsp[(1) - (1)].node)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 116 "temp2.y"
    { (yyval.node) = create_Node("error", -1, "NULL",0); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 117 "temp2.y"
    { (yyval.node) = NULL; ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 120 "temp2.y"
    { (yyval.node) = create_Node("if_statement", -1,"NULL", 7,(yyvsp[(1) - (7)].node),(yyvsp[(2) - (7)].node),(yyvsp[(3) - (7)].node),(yyvsp[(4) - (7)].node),(yyvsp[(5) - (7)].node),(yyvsp[(6) - (7)].node),(yyvsp[(7) - (7)].node));;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 121 "temp2.y"
    { (yyval.node) = create_Node("if_statement", -1,"NULL", 5,(yyvsp[(1) - (5)].node),(yyvsp[(2) - (5)].node),(yyvsp[(3) - (5)].node),(yyvsp[(4) - (5)].node),(yyvsp[(5) - (5)].node));;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 122 "temp2.y"
    { (yyval.node) = create_Node("if_statement", -1,"NULL", 1,(yyvsp[(1) - (2)].node));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 124 "temp2.y"
    { (yyval.node) = create_Node("else_statement", -1, "NULL", 3, (yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 125 "temp2.y"
    { (yyval.node) = create_Node("else_statement", -1, "NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 126 "temp2.y"
    { (yyval.node) = create_Node("else_statement", -1, "NULL", 1, (yyvsp[(1) - (2)].node)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 129 "temp2.y"
    { (yyval.node) = create_Node("if_else_statement", -1, "NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 131 "temp2.y"
    { (yyval.node) = create_Node("while_statement", -1, "NULL", 7, (yyvsp[(1) - (7)].node), (yyvsp[(2) - (7)].node), (yyvsp[(3) - (7)].node), (yyvsp[(4) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(6) - (7)].node), (yyvsp[(7) - (7)].node)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 133 "temp2.y"
    { (yyval.node) = create_Node("for_statement", -1, "NULL", 9, (yyvsp[(1) - (10)].node), (yyvsp[(2) - (10)].node), (yyvsp[(3) - (10)].node), (yyvsp[(4) - (10)].node), (yyvsp[(5) - (10)].node), (yyvsp[(6) - (10)].node), (yyvsp[(7) - (10)].node), (yyvsp[(8) - (10)].node), (yyvsp[(9) - (10)].node)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 135 "temp2.y"
    { (yyval.node) = create_Node("return_statement", -1,"NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 136 "temp2.y"
    { (yyval.node) = create_Node("return_statement", -1, "NULL", 2, (yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 138 "temp2.y"
    { (yyval.node) = create_Node("cout_statement", -1,"NULL", 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 140 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1,"NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 141 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 142 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 143 "temp2.y"
    { (yyval.node) = create_Node("insert_statement", -1, "NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 145 "temp2.y"
    { (yyval.node) = create_Node("cin_statement", -1, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 147 "temp2.y"
    { (yyval.node) = create_Node("extract_statement", -1, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 148 "temp2.y"
    { (yyval.node) = create_Node("extract_statement", -1, "NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 151 "temp2.y"
    { (yyval.node) = create_Node("declaration_statement", -1, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 153 "temp2.y"
    { (yyval.node) = create_Node("id_list", -1, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 154 "temp2.y"
    { (yyval.node) = create_Node("id_list", -1, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 155 "temp2.y"
    { (yyval.node) = create_Node("id_list", -1, "NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 156 "temp2.y"
    { (yyval.node) = create_Node("id_list", -1, "NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 159 "temp2.y"
    {(yyval.node) = create_Node("assignment_statement", -1, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); (yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value; ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 162 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); (yyvsp[(1) - (3)].node)->value = (yyvsp[(3) - (3)].node)->value; ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 163 "temp2.y"
    { (yyval.node) = create_Node("E", -1,  "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); 
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

  case 58:

/* Line 1455 of yacc.c  */
#line 180 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (3)].node)->value+(yyvsp[(3) - (3)].node)->value, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 181 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (3)].node)->value-(yyvsp[(3) - (3)].node)->value, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 182 "temp2.y"
    { (yyval.node) = create_Node("E", (yyvsp[(1) - (1)].node)->value, "NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 186 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (3)].node)->value*(yyvsp[(3) - (3)].node)->value, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 187 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (3)].node)->value/(yyvsp[(3) - (3)].node)->value, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 188 "temp2.y"
    { (yyval.node) = create_Node("T", (yyvsp[(1) - (1)].node)->value, "NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 192 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL" , 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 193 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 194 "temp2.y"
    { (yyval.node) = create_Node("F",(yyvsp[(2) - (3)].node)->value, "NULL", 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 195 "temp2.y"
    { (yyval.node) = create_Node("identifier", -1, "NULL", 1, (yyvsp[(1) - (1)].node)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 196 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 197 "temp2.y"
    { (yyval.node) = create_Node("F", -1, "NULL", 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2054 "temp2.tab.c"
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
#line 200 "temp2.y"

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
	extern char *yytext;
	yyin=fp;
	yyparse();
	printf("---------------\n");
	printTree(head,0);
	printf("---------------\n");
	display();
}

