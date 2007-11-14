#!/usr/bin/perl
#
# Process an xml file and convert all the syntax into
# bit diagrams

use File::Temp qw/ :mktemp  /;

$S2B = "/users/ekr/doc/ietf-drafts/ekr/s2b/s2b";

&usage() unless $#ARGV==1;

open(IN,$ARGV[0]) || die("Couldn't open input file");
open(OUT,">$ARGV[1]") || die("Couldn't open output file");


while(<IN>){
    print OUT;

    if(/<!--\s*begin-prologue\s*-->/){
	while(<IN>){
	    last if /artwork/;

	    $PROLOGUE .= $_;
	}

	print OUT;
    }
    
    if(/<!--\s*begin-pdu\s*-->/){
	($fh, $file) = mkstemp( "tmpfileXXXXX" );

	print $fh $PROLOGUE;
	$PDU="";

	while(<IN>){
	    if(/<\/artwork>/){
		$last_line=$_;
		last;
	    }
	    
	    $PDU.=$_;
	    print $fh $_;
	}

	close($fh);
	$result = `$S2B $file`;
	
	if($?){
	    print OUT "PARSE ERROR: $result\n";
	    print OUT "PDU WAS: \n";
	    print OUT "---------------------------------------------\n";
	    print OUT "$PDU\n";
	    print OUT "---------------------------------------------\n";

	    print STDERR "Parse error in line $@, file=$file\n";
	    print STDERR "PDU WAS: \n";
	    print STDERR "---------------------------------------------\n";
	    print STDERR "$PDU\n";
	    print STDERR "---------------------------------------------\n";
	}
	else{
	    print OUT $result;
	    
	    unlink($file);
	}


	print OUT $last_line;
    }
}

exit 0;



sub usage {
    print <<FOO;
    usage: s2x.pl <input-file> <output-file>
FOO
    exit 0;
}	
