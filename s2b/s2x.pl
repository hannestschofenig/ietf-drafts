#!/usr/bin/perl
#
# Process an xml file and convert all the syntax into
# bit diagrams

use Getopt::Std;
my %opts;

getopts("ne",\%opts);

$EXTRACT=1 if $opts{'e'};

use File::Temp qw/ :mktemp  /;

$S2B = "/users/ekr/doc/ietf-drafts/ekr/s2b/s2b";

&usage() unless $#ARGV==1;

open(IN,$ARGV[0]) || die("Couldn't open input file");
open(OUT,">$ARGV[1]") || die("Couldn't open output file");
open(S2C,">$ARGV[0].s2c")||die("Couldn't open s2c file") if $EXTRACT;

$output=0;
$in_pdu=0;

while(<IN>){
    print OUT;

    next unless $EXTRACT;

    if(/<!--\s*begin-prologue\s*-->/){
	$in_pdu=1;
	next;
    }
    if(/<!--\s*end-prologue\s*-->/){
	$in_pdu=0;
	$output=0;
	next;
    }
    if(/<!--\s*begin-pdu\s*-->/){
	$in_pdu=1;
	next;
    }
    if(/<!--\s*end-pdu\s*-->/){
	$in_pdu=0;
	$output=0;
	next;
    }

    if(m!/artwork!){
	$in_pdu=0;
	$output=0;
	next;
    }
    
    if($in_pdu && /artwork/){
	$output=1;
	next;
    }
    
    if($output){
	print S2C;
    }
}

exit 0;



sub usage {
    print <<FOO;
    usage: s2x.pl <input-file> <output-file>
FOO
    exit 0;
}	
