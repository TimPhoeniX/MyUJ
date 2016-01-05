set term png size 2000
set output "porownanie.png"

set title "Probability Distribution"

plot 'results.txt' using 1:2 title "Numerical", \
	 '' using 1:3 title "Expected" with linespoint