#ifndef YYERRCODE
#define YYERRCODE 256
#endif

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
typedef union {
     int val;
     unsigned char str[8192];
     p_decl *decl;
} YYSTYPE;
extern YYSTYPE yylval;
