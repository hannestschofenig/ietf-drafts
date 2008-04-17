#!/usr/local/bin/perl
print ".nf\n";
while(<STDIN>){
  next unless /^SECTION\s+(\S+)\s+(\d+)\s+(.*)/;
  $sn=$1;
  $pn=$2;
  $title=$3;
  
  chop($sn);

  @ndots = split('\.', $sn);
  $ndots = $#ndots;
  $indent = $ndots * 2;

  if(length($title)>(47+length($pn))){
    $title=substr($title,0,(47+length($pn)));
    $title.="...  ";
  }
  $length=12+length($title)+length($pn)+($indent);

  $pad = 65 - $length;
  for($i=0;$i<$indent;$i++){
    print " ";
  }
  print "$sn";
  for($i=length($sn);$i<12;$i++){
    print " ";
  }
  
  print $title;
  print "  ";
  
  for($i=0;$i<$pad;$i++){
    print " ";
  }

  print "$pn\n";
}
print "\n.fi\n";
