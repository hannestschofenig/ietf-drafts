#!/opt/local/bin/perl
$page=1;

while(<STDIN>){
  $page++ if(/\[Page \d+\]/);
  
  if(/^(Appendix\s+)?([\dA-F]+\.\S*)\s+(.*)/){
    chop;

    $num=$2;
    $entry=$3;

    $pad=10-length($num);
    $line=$num;
    for($i=0;$i<$pad;$i++){
      $line.=" ";
    }
    $line.=$entry;
    $pad=67-length($line);
    for($i=0;$i<$pad;$i++){
      $line.=" ";
    }
    $line.=$page;
    print "$line\n";
    
  }
}
