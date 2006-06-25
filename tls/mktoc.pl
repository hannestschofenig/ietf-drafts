#!/usr/local/bin/perl
$page=1;

while(<STDIN>){
  $page++ if(/\[Page \d+\]/);
  
  if(/(^[\dA-F]\.\S*)\s+(.*)/){
    chop;

    $num=$1;
    $entry=$2;

    $pad=10-length($num);
    $line=$num;
    for($i=0;$i<$pad;$i++){
      $line.=" ";
    }
    $line.=$entry;
    $pad=70-length($line);
    for($i=0;$i<$pad;$i++){
      $line.=" ";
    }
    $line.=$page;
    print "$line\n";
    
  }
}
