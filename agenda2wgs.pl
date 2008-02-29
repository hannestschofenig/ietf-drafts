#!/usr/bin/perl

while(<STDIN>){
    next unless /\s+[A-Z][A-Z][A-Z]\s+([a-z0-9]+)\s+/;

    push(@WGS,$1) unless $WGS{$1};
    $WGS{$1}=1;
}

foreach $wg (@WGS){
    print "$wg\n";
}
