set term png size 2000
set output "porownanie.png"

set title "Probability Density"
set style data lines

plot 'data.txt' using 1:2 title "num density", \
	 '' using 1:3 title "density"

set output "fx.png"

plot 'data.txt' using 1:3 title "density"

set output "fnum.png"

plot 'data.txt' using 1:2 title "num density"
