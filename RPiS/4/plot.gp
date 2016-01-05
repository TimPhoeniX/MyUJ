set term png size 2000
set output "porownanie.png"

set title "ChiSquared3 Distribution"

plot 'results.txt' using 1:2 title "Numerical" with boxes, \
	 '' using 1:3 title "Expected" with lines lw 3