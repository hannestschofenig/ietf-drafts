#!/usr/bin/perl -Tw
# getdrafts.pl -- an IETF draft retriever/printer
# 
# Eric Rescorla
# ekr@networkresonance.com

use Getopt::Std;
use File::Path;

getopts("vVpncd:P:s",\%opts);

# Untaint env (this is perl fodder)
$env=$ENV{"PATH"};
$env="" unless $env;
$env=~/^(.*)$/;
$ENV{"PATH"}=$1;
$env="" unless $env;
$env=$ENV{"CDPATH"};
$env="" unless $env;
$env=~/^(.*)$/;
$ENV{"CDPATH"}=$1;

$VERBOSE=0;
$VERBOSE=1 if $opts{"v"};
$VERBOSE=2 if $opts{"V"};
$NODOWNLOAD=1 if $opts{"n"};
$PRINTDRAFTS=1 if $opts{"p"};
$PRINT_COMMAND=$opts{P} if $opts{"P"};
$CLEAN=1 if $opts{"c"};
$SEARCH=1 if $opts{"s"};

$stat_found=0;
$stat_total=0;

&usage() unless $#ARGV>=1;

$mtg_tmp=shift @ARGV;
die("Bad meeting name $mtg_tmp: try YY<monthname> like 07mar") unless $mtg_tmp=~/^(\d\d[a-z][a-z][a-z])$/;
$mtg=$1;

$AGENDA_URL="http://www3.ietf.org/proceedings/$mtg/agenda/";
$DRAFT_URL="http://www.ietf.org/internet-drafts/";
$PRINT_COMMAND="enscript -2rG -h" unless $PRINT_COMMAND;

if($opts{'d'}){
  $lp_tmp=$opts{'d'};
  $lp_tmp=~/^(\S+)$/;
  $lp=$1;

  $PRINT_COMMAND .= " -d $lp";
}

if($CLEAN){
  rmtree([$mtg],0,0);
}

mkdir($mtg);
chdir($mtg);

use LWP::UserAgent;

$ua=LWP::UserAgent->new;
$ua->agent("DraftScraper");

while ($wg_tmp=shift @ARGV){

  die("Bad wg name") unless $wg_tmp=~/^(\w+)$/;  # untaint wg
  $wg=$1;

  print STDERR "WG: $wg\n" if $VERBOSE;
  &get_drafts_for_wg($wg);
  &print_drafts_for_wg($wg) if $PRINTDRAFTS;
}

if($#NOTFOUNDWGS!=-1){
    print STDERR "WGs without agendas:\n";

    while($nf=shift @NOTFOUNDWGS){
	print STDERR "  $nf\n";
    }
    print STDERR "\n";
}

if($#NOTFOUNDDRAFTS!=-1){
    print STDERR "Missing drafts\n";

    while($nf=shift @NOTFOUNDDRAFTS){
	print STDERR "  $nf\n";
    }
}

print STDERR "Found $stat_found out of $stat_total drafts\n";


exit(0);


sub get_drafts_for_wg {
  local($wg)=@_;

  my @drafts=&list_drafts_for_wg($wg);

  mkdir($wg);

  return if $#drafts==-1;
  $stat_total+=$#drafts+1;

  while($draft=shift @drafts){
    if (-f "$wg/$draft") {
      print STDERR "$draft already exists\n" if $VERBOSE;
      $stat_found++;
      next;
    };
    
    if(!$NODOWNLOAD){
	my $ret;

	if($SEARCH){
	    $ret=&search_for_draft($draft, $wg);
	}
	else{
	    $ret=&get_draft($draft,"$wg/$draft",$wg,1);
	}
	$stat_found++ unless $ret;
    }
  }
}

  
sub list_drafts_for_wg {
  local($wg)=@_;
  local(@filetypes)=(".html",".htm",".txt");

  my %drafts=();
  my @drafts=();
  
  my $success=0;
  my $succ=0;

  foreach $filetype (@filetypes){
    my @drafts_tmp=&get_drafts_from_agenda($wg,$filetype,\$succ);
    
    my $draft;

    if($succ==1){
      $success=1;
    }

    while($draft=shift @drafts_tmp){
      next if $drafts{$draft};

      push(@drafts,$draft);
      $drafts{$draft}=1;
    }
  }

  if(!$success){
    print STDERR "Couldn't get agenda for $wg\n" if $VERBOSE;
    push(@NOTFOUNDWGS,"$wg");
    return ();
  }

  return @drafts;
}

sub get_drafts_from_agenda {
  local($wg,$filetype,$succ)=@_;
  my $url= $AGENDA_URL. $wg . $filetype;

  print STDERR "  URL=$url\n" if $VERBOSE;

  my $req=HTTP::Request->new(GET=>$url);
  my $res=$ua->request($req);

  if(!$res->is_success){
    $$succ=0;
    return();
  }

  my $content=$res->content;
  
  my @drafts=();
  my(%drafts)=();

  if($VERBOSE>1){
    print STDERR "CONTENTS======\n";
    print STDERR $content;
    print STDERR "==============\n";
  }

  while($content =~ m!(draft-[a-z0-9\.-]+-\d\d)!mgis){
    my $d=$1;

    # Double-check filter for bad stuff
    next unless $d=~/^[a-z0-9\.-]+-\d\d$/;

    my $draft="$d.txt";
    
    next if $drafts{$draft};

    push(@drafts,$draft);
    $drafts{$draft}=1;
      
    print STDERR "  DRAFT: $draft\n" if $VERBOSE;
  }

  $$succ=1;
  @drafts;
}


sub search_for_draft {
    local($draft, $wg)=@_;
    local($draft_base,$num);
    local($to_try);

    die("Draft doesn't match pattern") unless $draft=~/^(draft-[a-z0-9\.-]+)-(\d\d).txt$/;
    
    $draft_base=$1;
    $num=$2;
    
    # Try the base draft
    if(!&get_draft($draft,"$wg/$draft",$wg,0)){
	return 0;
    }

    print STDERR "Draft: $wg doesn't seem to exist. Looking for alternates\n" if $VERBOSE;
    
    # Try the immediately following number
    $to_try=sprintf("%s-%.2d.txt",$draft_base,$num+1);
    if(!&get_draft($to_try,"$wg/$to_try",$wg,0)){
	print STDERR "Draft: $to_try exists and appears to supersede version $num\n" if $VERBOSE;
	return 0;
    }

    # Now try the immediately preceding number
    if($num > 0){
	$to_try=sprintf("%s-%.2d.txt",$draft_base,$num-1);
	if(!&get_draft($to_try,"$wg/$to_try",$wg,0)){
	    print STDERR "Draft: $draft doesn't seem to exist yet. Substituting previous version\n" if $VERBOSE;
	    return 0;
	}
    }
    
    print STDERR "Couldn't get draft $draft\n" if $VERBOSE;
    push(@NOTFOUNDDRAFTS,"$draft (wg=$wg)");
    
    return -1;
}

sub get_draft {
  local($draft,$filename, $wg_name,$report)=@_;
  
  $url=$DRAFT_URL . $draft;

  print STDERR "draft URL: $url\n" if $VERBOSE;

  my $req=HTTP::Request->new(GET=>$url);
  my $res=$ua->request($req);

  if(!$res->is_success){
      if($report){
	  print STDERR "Couldn't get draft $draft\n" if $VERBOSE;
	  push(@NOTFOUNDDRAFTS,"$draft (wg=$wg_name)");
      }
    return -1;
  }

  open(OUT,">$filename")||die("Couldn't open $filename");
  print OUT $res->content;
  close(OUT);
  return 0;
}

sub print_drafts_for_wg {
  local($wg)=@_;

  my @files=();

  if(!opendir(DIR,"$wg")){
      print STDERR "Couldn't open directory $wg";
      return;
  }
  open(HEADER,">$wg/HEADER")||die("Couldn't open header");

  print HEADER "************** WG $wg *****************\n\n";

  while($file=readdir(DIR)){
    next if $file eq ".";
    next if $file eq "..";
    next if $file=~/.printed$/;
    next if $file=~/HEADER/;

    next unless $file=~/^(draft-[a-z0-9\.-]+-\d\d.txt)$/;
    $file=$1;

    # Add a copy of this to the header page
    print HEADER "[] $file\n";

    # suppress anything already printed
    next if -f "$wg/.printed.$file";

    push(@files,$1);
  }
  
  close(HEADER);

  return if($#files==-1);  #nothing to do

  #Print the burst page/header
  system("$PRINT_COMMAND $wg/HEADER");

  while($file=shift @files){
    system("$PRINT_COMMAND $wg/$file");    
    &touch("$wg/.printed.$file");
  }
}

sub touch {
  local($filename)=@_;
  
  open(OUT,">$filename");
  close(OUT);
}

sub usage {
  print <<FOO;
usage: [-vVpnts] getdrafts.pl <meeting-name> <wg1> <wg2>

 Get a copy of every relevant draft for a given meeting for
 some set of wgs and stuff them in <meeting-name>/<wgname>

 -v = verbose
 -V = really verbose
 -p = print all the drafts that haven't been printed yet
 -n = don't download drafts that aren't here already
 -c = clean up
 -d = print to another printer
 -P = override the printing command entirely
 -s = search for alternate draft versions if the main version isn't
      found 
FOO

exit(0);
}
