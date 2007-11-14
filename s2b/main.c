/**
   main.c


   Copyright (C) 1999-2000 RTFM, Inc.
   All Rights Reserved

   This package is a SSLv3/TLS protocol analyzer written by Eric Rescorla
   <ekr@rtfm.com> and licensed by RTFM, Inc.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
   3. All advertising materials mentioning features or use of this software
      must display the following acknowledgement:
   
      This product includes software developed by Eric Rescorla for
      RTFM, Inc.

   4. Neither the name of RTFM, Inc. nor the name of Eric Rescorla may be
      used to endorse or promote products derived from this
      software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY ERIC RESCORLA AND RTFM, INC. ``AS IS'' AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY SUCH DAMAGE.

   $Id: main.c,v 1.2 2000/10/17 16:10:01 ekr Exp $


   ekr@rtfm.com  Mon Jan 18 16:28:43 1999
 */


static char *RCSSTRING="$Id: main.c,v 1.2 2000/10/17 16:10:01 ekr Exp $";

#include <stdarg.h>
#include <stdio.h>
#include "parser.h"
#include "r_log.h"

extern int yydebug;

FILE *doth,*dotc;

typedef struct output_ctx_ {
  int byte_ct;
  int suppress_ct;
  int offset;
  int done;
  int indent;
  char *name;
  int (*output)(struct output_ctx_ *ctx, p_decl *decl, char *name, int bits);
  int (*output_select)(struct output_ctx_ *ctx, p_decl *decl, char *name, int bits);
} output_ctx;

int verr_exit(char *fmt,...)
  {
    va_list ap;

    va_start(ap,fmt);
    r_log(LOG_GENERIC,LOG_DEBUG,fmt,ap);
    exit(1);
  }

r_assoc *types;
p_decl_head public_decls;

int parser_preload()
  {
    int r;
    
    r_assoc_create(&types,r_assoc_crc32_hash_compute,10);
    STAILQ_INIT(&public_decls);
  }

int print_indent(int indent)
  {
    while(indent--){
      r_log(LOG_GENERIC,LOG_DEBUG," ");
    }

    return(0);
  }


int print_decl(output_ctx *ctx,p_decl *decl)
  {
    p_decl *p;

    print_indent(ctx->indent);
    r_log(LOG_GENERIC,LOG_DEBUG,"DECL %s\n",decl->name);
    
    switch(decl->type){
      case TYPE_PRIMITIVE:
        ctx->output(ctx, decl, ctx->name, decl->u.primitive_.bits);
        break;
      case TYPE_VARRAY:
        ctx->output(ctx,decl,ctx->name,decl->u.varray_.length);
        break;
      case TYPE_REF:
        ctx->indent+=2;
        print_decl(ctx,decl->u.ref_.ref);
        ctx->indent-=2;
        break;
      case TYPE_STRUCT:
        p=STAILQ_FIRST(&decl->u.struct_.members);
        while(p){
          ctx->name=p->name;
          ctx->indent+=2;
          print_decl(ctx,p);
          ctx->indent-=2;
          p=STAILQ_NEXT(p,entry);
        }
        break;

      case TYPE_SELECT:
        ctx->output_select(ctx, decl, ctx->name, 0);
        break;
         
      default:
        nr_verr_exit("Unknown decl type %s(%d)\n",decl->name,decl->type);
    }

    return(0);
  }


int print_bit_line(output_ctx *ctx, int bits)
  {
    int i;
    char lead[5]="    ";
    
    if(ctx->byte_ct && !ctx->suppress_ct)
      snprintf(lead,5,"%.3d ",ctx->byte_ct);

    printf(lead);

    putchar('+');
    for(i=0;i<bits;i++){
      putchar('-');
      putchar('+');
    }
  }

int output_bits_header(output_ctx *ctx,char *name)
  {
    printf("STRUCTURE: %s\n",name);

    printf("    0                   1                   2                   3\n");
    printf("    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2\n");
    print_bit_line(ctx,32);
    putchar('\n');

    return(0);
  }

int output_bits_footer(output_ctx *ctx)
  {
    printf("\n");

    if(ctx->offset){
      print_bit_line(ctx,ctx->offset);
      putchar('\n');
    }

    return(0);
  }

int output_bits(output_ctx *ctx, p_decl *decl, char *name, int bits)
  {
    char buf[4096];
    int i;
    int start_offset;
    int remainder;
    int variable=0;
    
    if(bits < 0){
      /* Output a synthetic length field and then 
       make this two words + the rest of this word
       long with a pad */
      char buf[16];

      int maxlen=-1 * bits;
      int lenlen=0;

      while(maxlen){
        lenlen+=8;
        maxlen>>=8;
      }
      
      snprintf(buf,sizeof(buf),"%s_l",name);

      output_bits(ctx, decl, buf,lenlen);

      variable=1;
    }
    else if (bits==0){
      /* Special case */
      variable=1;
    }

    if(variable){
      bits = (32 - ctx->offset) + 64;
      ctx->suppress_ct=1;
    }


    start_offset=ctx->offset;
    remainder=bits;

    if(strlen(name)>(bits*2))
      nr_verr_exit("Name %s doesn't fit in %d bits", name, bits);
    if(bits > 4096)
      nr_verr_exit("Bits too long");

    memset(buf,' ',4096);

    i = (bits*2 - strlen(name))/2;

    memcpy(buf + i, name, strlen(name));

    if(variable){
      buf[bits*2-1]='/';
    }
    else{
      buf[bits*2-1]='|';
    }

    for(i=0;i<bits;i++){
      if(!ctx->offset){
        if(variable){
          printf("    /");
        }
        else{
          printf("    |");
        }
      }
      
      putchar(buf[i*2]);

      ctx->offset++;
      remainder--;

      if(ctx->offset && !(ctx->offset % 8))
        ctx->byte_ct++;

      if(ctx->offset==32){
        int j;

        if(variable)
          putchar('/');
        else
          putchar('|');

        putchar('\n');
        
        /* OK, print the separator. This is tricky because 
           fields sometimes flow */
        if(i==(bits-1) || (remainder < start_offset)){
          print_bit_line(ctx,32);
        }
        else{
          int final_bits=0;
          
          print_bit_line(ctx,start_offset);
          
          if(remainder < 32)
            final_bits=32-remainder;

          for(j=0;j<(32 - (start_offset+final_bits))*2-1;j++){
            putchar(' ');
          }
          if(final_bits){
            for(j=0;j<final_bits;j++){
              putchar('+');
              putchar('-');
            }
          }
          putchar('+');
          start_offset=0;
        }
        putchar('\n');

        ctx->offset=0;
      }
      else putchar(buf[2*i+1]);
    }

    return(0);
  }

int output_select_bits(output_ctx *ctx, p_decl *decl, char *name, int bits)
  {
    p_decl *p;
    output_ctx ctx2;

    if(STAILQ_NEXT(decl,entry))
      nr_verr_exit("select must be the last element in decl");
    
    /* Close the current bit diagram */
    /* First make a variable for the underlying select */
    output_bits(ctx,decl,name,0);

    printf("\n");
    if(ctx->offset){
      print_bit_line(ctx,ctx->offset);
      putchar('\n');
    }

    p=STAILQ_FIRST(&decl->u.select_.arms);
    while(p){
      char buf[10];

      memcpy(&ctx2,ctx,sizeof(output_ctx));
      
      ctx2.byte_ct=0;
      ctx2.suppress_ct=0;
      ctx2.name=p->name;
      ctx2.indent=0;
      ctx2.offset=0;
      ctx2.output=output_bits;
      ctx2.output_select=output_select_bits;

      printf("\n");

      output_bits_header(&ctx2,p->name);

      /* Make a synthetic decl for the type */
      snprintf(buf,10,"0x%.2x",p->u.select_arm_.value);

      output_bits(&ctx2,p,buf,8);

      print_decl(&ctx2,p->u.select_arm_.ref);
      
      output_bits_footer(&ctx2);

      p=STAILQ_NEXT(p,entry);
    }

    ctx->offset=0;

    return(0);
  }

int output_public_decl_bits(p_decl *decl)
  {
    output_ctx ctx;
 

    ctx.byte_ct=0;
    ctx.suppress_ct=0;
    ctx.name="NONAME";
    ctx.indent=0;
    ctx.offset=0;
    ctx.output=output_bits;
    ctx.output_select=output_select_bits;

    output_bits_header(&ctx,decl->name);
    print_decl(&ctx,decl);
    output_bits_footer(&ctx);

    return(0);
  }


 main(argc,argv)
  int argc;
  char **argv;
  {
    char name[100];
    FILE *in;
    p_decl *decl;

    parser_preload();
    
    if(argc==1){
      ;
    }
    if(argc==2){
      if(!(in=freopen(argv[1],"r",stdin)))
      verr_exit("Couldn't open input file %s\n",argv[1]);
    }
    else{
      fprintf(stderr,"usage: s2b <input-file>");
    }
    
    yyparse();

    decl=STAILQ_FIRST(&public_decls);
    

    while(decl){
      output_public_decl_bits(decl);
      
      decl=STAILQ_NEXT(decl,entry);
    }

    exit(0);
  }


extern int yylineno;

int yywrap()
{
;}

int yyerror(s)
  char *s;
  {
    printf("Parse error %s at line %d\n",s,yylineno);
    exit(1);
  }
