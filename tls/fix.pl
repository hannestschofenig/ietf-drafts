#!/usr/local/bin/perl
while(<STDIN>){
  if(/(.*)FORMFEED\[Page ([^\]]*)\](.*)/){
    print STDOUT "$1         [Page $2]$3\f";
    $x=5;
    while($x--&&<STDIN>){;}
  }
  else{
    print STDOUT;
  }
}

