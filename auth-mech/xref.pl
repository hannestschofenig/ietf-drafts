#!/usr/local/bin/perl
while(<STDIN>){
  chop;
  if(/^EKRXREF\s+(\S+)\s+(\S+)/){
    print <<FOO;
.ds xref*$1 $2
FOO
  }
}
