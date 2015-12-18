set term png size 2000
set output "porownanie.png"

set title "Probability Distribution"
set style data histogram

plot 'results.txt' using 2 title "Numerical", \
	 '' using 1:3 title "Expected" with linespoint

set output "fx.png"

plot 'results.txt' using 3 title "Expected"

set output "fnum.png"

plot 'results.txt' using 2 title "Numerical"
