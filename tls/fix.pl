#!/usr/local/bin/perl
$* = 1;                                 # Enable multiline patterns.
undef $/;                               # Read whole files in a single
                                        # gulp.

while (<>) {                            # Read the entire input file.
    s/FORMFEED(\[Page\s+\d+\])\s+/        \1\n\f\n/g;
                                        # Rewrite the end-of-pages.
#    s/\f\n$/\f/;                       # Want bare formfeed at end?
#    s/\f\n$//;                         # Want no formfeed at end?
    print;                              # Print the resultant file.
}
