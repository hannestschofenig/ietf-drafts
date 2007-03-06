#!/bin/perl
require 'getopts.pl';


&Getopts("vVpnc");

$VERBOSE=1 if $opt_v;
$VERBOSE=2 if $opt_V;
$NODOWNLOAD=1 if $opt_n;
$PRINTDRAFTS=1 if $opt_p;
$CLEAN=1 if $opt_c;

&usage() unless $#ARGV>=1;

$mtg=shift @ARGV;


$AGENDA_URL="http://www3.ietf.org/proceedings/$mtg/agenda/";
$DRAFT_URL="http://www.ietf.org/internet-drafts/";
$PRINT_COMMAND="enscript -2rG -h";

if($opt_c){
  # Ok, this is gross but I don't know a perl macro for
  # recursive remove
  system("rm -rf $mtg");
}

mkdir($mtg);
chdir($mtg);

use LWP::UserAgent;

$ua=LWP::UserAgent->new;
$ua->agent("DraftScraper");


while ($wg=shift @ARGV){
  print STDERR "WG: $wg\n" if $VERBOSE;
  &get_drafts_for_wg($wg);
  &print_drafts_for_wg($wg) if $PRINTDRAFTS;

  $wgs.=" $wg";
}

while($nf=shift @NOTFOUND){
  print STDERR "NOT FOUND: $nf\n";
}


exit(0);


sub get_drafts_for_wg {
  local($wg)=@_;

  my @drafts=&list_drafts_for_wg($wg);

  return if $#drafts==-1;
  mkdir($wg);

  while($draft=shift @drafts){
    if (-f "$wg/$draft") {
      print STDERR "$draft already exists\n" if $VERBOSE;
      next;
    };
    
    &get_draft($draft,"$wg/$draft") unless $NODOWNLOAD;
  }
}

  
sub list_drafts_for_wg {
  local($wg)=@_;
  my $url= $AGENDA_URL. $wg . ".txt";
  
  print STDERR "  URL=$url\n" if $VERBOSE;

  my $req=HTTP::Request->new(GET=>$url);
  my $res=$ua->request($req);

  if(!$res->is_success){
    print STDERR "Couldn't get agenda for $wg\n";
    push(@NOTFOUND,"WG: $wg");
    return ();
  }

  my $content=$res->content;
  
  my @drafts=();

  if($VERBOSE>1){
    print STDERR "CONTENTS======\n";
    print STDERR $content;
    print STDERR "==============\n";
  }

  while($content =~ m!(draft-[^\.\s+;\|]+\d+)!mgis){
    my $d=$1;

    # Double-check filter for bad stuff
    next unless $d=~/^[a-zA-Z\-0-9]+-\d\d$/;

    my $draft="$d.txt";
    push(@drafts,$draft);
    print STDERR "  DRAFT: $draft\n" if $VERBOSE;
  }

  @drafts;
}

sub get_draft {
  local($draft,$filename)=@_;

  $url=$DRAFT_URL . $draft;

  print STDERR "draft URL: $url\n" if $VERBOSE;

  my $req=HTTP::Request->new(GET=>$url);
  my $res=$ua->request($req);

  if(!$res->is_success){
    print STDERR "Couldn't get draft $draft\n";
    push(@NOTFOUND,"DRAFT: $draft");
    return;
  }

  open(OUT,">$filename")||die("Couldn't open $filename");
  print OUT $res->content;
  close(OUT);
}

sub print_drafts_for_wg {
  local($wg)=@_;

  my @files=();

  opendir(DIR,"$wg")||die("Couldn't open directory $wg");
  open(HEADER,">$wg/HEADER")||die("Couldn't open header");

  print HEADER "************** WG $wg *****************\n\n";
  print HEADER "C  R   Draft\n";


  while($file=readdir(DIR)){
    next if $file eq ".";
    next if $file eq "..";
    next if $file=~/.printed$/;
    next if $file=~/HEADER/;
    print HEADER "[] [] $file\n";
    push(@files,$file);
  }
  
  close(HEADER);
  system("$PRINT_COMMAND $wg/HEADER");

  while($file=shift @files){
    next if -f "$wg/$file.printed";
    system("$PRINT_COMMAND $wg/$file");    
    system("touch $wg/$file.printed");
  }
}


sub usage {
  print <<FOO;
usage: [-vVpnt] getdrafts.pl <meeting-name> <wg1> <wg2>

 Get a copy of every relevant draft for a given meeting for
 some set of wgs and stuff them in <meeting-name>/<wgname>

 -v = verbose
 -V = really verbose
 -p = print all the drafts that haven't been printed yet
 -n = don't download drafts that aren't here already
 -c = clean up
FOO

exit(0);
}
