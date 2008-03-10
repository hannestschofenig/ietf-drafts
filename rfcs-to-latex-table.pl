#!/usr/bin/perl
while(<STDIN>){
    die unless /(.*)\((RFC \d+)\)/;
    print "$1 & $2 & Published \\\\\n";
}
