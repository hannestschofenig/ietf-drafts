#include <stdlib.h>
#ifndef lint
#ifdef __unused
__unused
#endif
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.37 2003/02/12 18:03:55 davidc Exp $";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
#if defined(__cplusplus) || __STDC__
static int yygrowstack(void);
#else
static int yygrowstack();
#endif
#define YYPREFIX "yy"
#line 12 "gram.y"

#include "parser.h"
#include "r_log.h"
#include <stdio.h>
 
extern FILE *dotc;
extern FILE *doth;

p_decl *current_decl[10]={0};
int current_decl_depth=0;
 
void push_decl(p_decl *decl)
  {
    current_decl[++current_decl_depth]=decl;
  }

void pop_decl()
  {
    current_decl_depth--;
  }

#define CURRENT_DECL current_decl[current_decl_depth]
#line 35 "gram.y"
typedef union {
     int val;
     unsigned char str[8192];
     p_decl *decl;
} YYSTYPE;
#line 53 "y.tab.c"
#define YYERRCODE 256
#define NAME_ 257
#define NUM_ 258
#define DOT_DOT_ 259
#define PUBLIC_ 260
#define STRUCT_ 261
#define SELECT_ 262
#define OPAQUE_ 263
#define ENUM_ 264
#define DIGITALLY_SIGNED_ 265
#define COMMENT_START_ 266
#define CODE_ 267
#define COMMENT_END_ 268
#define CASE_ 269
#define CONSTANT_ 270
#define PRIMITIVE_ 271
#define TYPEDEF_ 272
#define selecttype 273
#define constant_type 274
#define selecterateds 275
#define selectmax 276
#define constval 277
const short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    2,    2,    2,    2,
   10,   10,    7,   11,   11,    3,    3,    6,    8,   12,
   12,   13,    5,   14,   15,   15,    4,    9,
};
const short yylen[] = {                                         2,
    1,    1,    2,    0,    1,    1,    1,    1,    1,    1,
    1,    2,    6,    0,    2,    3,    6,    4,    6,    1,
    3,    4,    6,    1,    0,    2,    4,    2,
};
const short yydefred[] = {                                      0,
    0,   11,   24,    0,    0,    0,    7,    0,    1,    0,
    9,    5,    6,    8,   10,    0,    0,   12,    0,    0,
    0,   28,    3,   14,   25,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   18,   16,    0,    0,   15,
    0,    0,   26,    0,    0,   21,    0,    0,    0,    0,
   22,   19,    0,   13,    0,   23,   17,   27,
};
const short yydgoto[] = {                                       8,
    9,   10,   22,   43,   11,   12,   13,   14,   15,   16,
   31,   27,   28,   17,   32,
};
const short yysindex[] = {                                   -257,
 -255,    0,    0, -113, -246, -245,    0,    0,    0, -257,
    0,    0,    0,    0,    0, -110, -107,    0, -239, -238,
 -236,    0,    0,    0,    0,  -21, -103,  -20,  -36,  -51,
 -124, -125, -233, -230, -239,    0,    0, -229, -227,    0,
 -226, -225,    0,  -13,  -26,    0,  -28,  -24,  -22,  -19,
    0,    0,  -18,    0, -245,    0,    0,    0,
};
const short yyrindex[] = {                                     37,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   38,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -86,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,
};
const short yygindex[] = {                                      0,
   32,    0,  -29,    0,    0,    0,    0,    0,    0,    0,
    0,    8,    0,    0,    0,
};
#define YYTABLESIZE 144
const short yytable[] = {                                      42,
   39,   40,    1,    2,    3,   18,    4,   37,   38,   19,
   20,   21,   24,    5,    6,   25,    7,   26,   33,   29,
   30,   34,   36,   35,   44,   58,   45,   51,   47,   48,
   49,   50,   52,   53,   54,   55,    4,    2,   20,   56,
   57,   23,   46,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   21,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   41,
};
const short yycheck[] = {                                     125,
  125,   31,  260,  261,  262,  261,  264,   59,   60,  123,
  257,  257,  123,  271,  272,  123,  274,  257,   40,  258,
  257,  125,   59,   44,  258,   55,  257,   41,  258,  257,
  257,  257,   59,   62,   59,   58,    0,    0,  125,   59,
   59,   10,   35,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  257,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  269,
};
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 277
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'","'<'",0,
"'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"NAME_","NUM_","DOT_DOT_","PUBLIC_","STRUCT_","SELECT_","OPAQUE_","ENUM_",
"DIGITALLY_SIGNED_","COMMENT_START_","CODE_","COMMENT_END_","CASE_","CONSTANT_",
"PRIMITIVE_","TYPEDEF_","selecttype","constant_type","selecterateds",
"selectmax","constval",
};
const char * const yyrule[] = {
"$accept : module",
"module : typelist",
"typelist : definition",
"typelist : definition typelist",
"definition :",
"definition : primitive",
"definition : struct_type",
"definition : constant_type",
"definition : enum",
"definition : select",
"definition : typedef",
"struct_start : STRUCT_",
"struct_start : PUBLIC_ STRUCT_",
"struct_type : struct_start '{' struct_decls '}' NAME_ ';'",
"struct_decls :",
"struct_decls : struct_decls declaration",
"declaration : NAME_ NAME_ ';'",
"declaration : NAME_ NAME_ '<' NUM_ '>' ';'",
"primitive : PRIMITIVE_ NAME_ NUM_ ';'",
"enum : ENUM_ '{' enumerateds '}' NAME_ ';'",
"enumerateds : enumerated",
"enumerateds : enumerated ',' enumerateds",
"enumerated : NAME_ '(' NUM_ ')'",
"select : select_start '{' select_arms '}' NAME_ ';'",
"select_start : SELECT_",
"select_arms :",
"select_arms : select_arms select_arm",
"select_arm : CASE_ NAME_ ':' declaration",
"typedef : TYPEDEF_ declaration",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 2:
#line 80 "gram.y"
{}
break;
case 3:
#line 82 "gram.y"
{}
break;
case 10:
#line 92 "gram.y"
{

          }
break;
case 11:
#line 99 "gram.y"
{
    p_decl *decl=0;

    r_log(LOG_GENERIC,LOG_DEBUG,"struct start\n");

    decl=RCALLOC(sizeof(p_decl));

    decl->type=TYPE_STRUCT;
    STAILQ_INIT(&decl->u.struct_.members);    
    push_decl(decl);
}
break;
case 12:
#line 111 "gram.y"
{
    p_decl *decl=0;

    r_log(LOG_GENERIC,LOG_DEBUG,"struct start\n");

    decl=RCALLOC(sizeof(p_decl));

    decl->type=TYPE_STRUCT;
    STAILQ_INIT(&decl->u.struct_.members);
    push_decl(decl);

    STAILQ_INSERT_TAIL(&public_decls,decl,entry);
}
break;
case 13:
#line 127 "gram.y"
{
    int r;

    CURRENT_DECL->name=r_strdup(yyvsp[-1].str);
    
    r_log(LOG_GENERIC,LOG_DEBUG,"Finished with struct %s\n",yyvsp[-1].str);
    
    if(r=r_assoc_insert(types,CURRENT_DECL->name,strlen(CURRENT_DECL->name),
         CURRENT_DECL,0,0,R_ASSOC_NEW)){
      r_log(LOG_GENERIC,LOG_DEBUG,"Couldn't insert struct %s. Exists?\n",yyvsp[-1].str);
      exit(1);
    }
    pop_decl();
  }
break;
case 14:
#line 142 "gram.y"
{}
break;
case 15:
#line 144 "gram.y"
{
               p_decl *decl=yyvsp[0].decl;
               
               r_log(LOG_GENERIC,LOG_DEBUG,"Adding type %s to %s\n", decl->name, CURRENT_DECL->name);

               STAILQ_INSERT_TAIL(&CURRENT_DECL->u.struct_.members,decl,entry);
             }
break;
case 16:
#line 154 "gram.y"
{ 
    p_decl *decl=0;
    void *v;
    int r;

    if(r=r_assoc_fetch(types,yyvsp[-2].str, strlen(yyvsp[-2].str), &v)){
      nr_verr_exit("Unknown type %s\n",yyvsp[-2].str);
      exit(1);
    }

    decl=RCALLOC(sizeof(p_decl));
    decl->name=r_strdup(yyvsp[-1].str);
    decl->type = TYPE_REF;
    decl->u.ref_.ref = v;

    yyval.decl=decl;
  }
break;
case 17:
#line 172 "gram.y"
{
    int r;
    p_decl *decl;
    void *v;

    if(r=r_assoc_fetch(types,yyvsp[-5].str, strlen(yyvsp[-5].str), &v)){
      nr_verr_exit("Unknown type %s\n",yyvsp[-5].str);
      exit(1);
    }

    decl=RCALLOC(sizeof(p_decl));
    decl->name=r_strdup(yyvsp[-4].str);
    decl->type = TYPE_VARRAY;
    decl->u.varray_.ref = v;
    decl->u.varray_.length = -1 * yyvsp[-2].val;

    yyval.decl=decl;
  }
break;
case 18:
#line 192 "gram.y"
{
    p_decl *decl=0;
    int r;
    decl=RCALLOC(sizeof(p_decl));

    decl->name=r_strdup(yyvsp[-2].str);
    decl->u.primitive_.bits=yyvsp[-1].val;
    decl->type=TYPE_PRIMITIVE;

    if(r=r_assoc_insert(types,decl->name,strlen(decl->name),
         decl,0,0,R_ASSOC_NEW)){
      r_log(LOG_GENERIC,LOG_DEBUG,"Couldn't insert primitive %s. Exists?\n",decl->name);
      exit(1);
    }
  }
break;
case 20:
#line 210 "gram.y"
{}
break;
case 21:
#line 211 "gram.y"
{}
break;
case 22:
#line 214 "gram.y"
{
    p_decl *decl=0;
    int r;
    decl=RCALLOC(sizeof(p_decl));

    decl->name=r_strdup(yyvsp[-3].str);
    decl->u.enum_.value=yyvsp[-1].val;
    decl->type=TYPE_ENUM;

    if(r=r_assoc_insert(types,decl->name,strlen(decl->name),
         decl,0,0,R_ASSOC_NEW)){
      r_log(LOG_GENERIC,LOG_DEBUG,"Couldn't insert enum %s. Exists?\n",decl->name);
      exit(1);
    }
  }
break;
case 23:
#line 232 "gram.y"
{
  int r;

    CURRENT_DECL->name=r_strdup(yyvsp[-1].str);
    
    r_log(LOG_GENERIC,LOG_DEBUG,"Finished with select %s\n",yyvsp[-1].str);
    
    if(r=r_assoc_insert(types,CURRENT_DECL->name,strlen(CURRENT_DECL->name),
         CURRENT_DECL,0,0,R_ASSOC_NEW)){
      r_log(LOG_GENERIC,LOG_DEBUG,"Couldn't insert struct %s. Exists?\n",yyvsp[-1].str);
      exit(1);
    }
    yyval.decl = CURRENT_DECL;

    pop_decl();
}
break;
case 24:
#line 250 "gram.y"
{
    p_decl *decl=0;

    r_log(LOG_GENERIC,LOG_DEBUG,"select start\n");

    decl=RCALLOC(sizeof(p_decl));

    decl->type=TYPE_SELECT;
    STAILQ_INIT(&decl->u.select_.arms);    
    push_decl(decl);
}
break;
case 25:
#line 262 "gram.y"
{}
break;
case 26:
#line 264 "gram.y"
{
               p_decl *decl=yyvsp[0].decl;
               
               r_log(LOG_GENERIC,LOG_DEBUG,"Adding arm %s to %s\n", decl->name, CURRENT_DECL->name);

               STAILQ_INSERT_TAIL(&CURRENT_DECL->u.select_.arms,decl,entry);
             }
break;
case 27:
#line 273 "gram.y"
{
    void *v;
    p_decl *decl=0;
    p_decl *value;
    int r;
    decl=RCALLOC(sizeof(p_decl));

    if(r=r_assoc_fetch(types,yyvsp[-2].str, strlen(yyvsp[-2].str), &v)){
      nr_verr_exit("Unknown value %s\n",yyvsp[-2].str);
      exit(1);
    }
    value=v;
    if(value->type != TYPE_ENUM)
      nr_verr_exit("%s is not a constant/enum",value->name);

    decl->name=r_strdup(yyvsp[-2].str);
    decl->u.select_arm_.ref=yyvsp[0].decl;
    decl->u.select_arm_.value=value->u.enum_.value;

    decl->type=TYPE_SELECT_ARM;

    yyval.decl=decl;
  }
break;
case 28:
#line 299 "gram.y"
{
    int r;

    if(r=r_assoc_insert(types,yyvsp[0].decl->name,strlen(yyvsp[0].decl->name),
         yyvsp[0].decl,0,0,R_ASSOC_NEW)){
      r_log(LOG_GENERIC,LOG_DEBUG,"Couldn't insert struct %s. Exists?\n",yyvsp[0].decl->name);
      exit(1);
    }
  }
break;
#line 670 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
