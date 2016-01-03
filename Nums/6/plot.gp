set term svg size 2000 1000
set output "inter.svg"

set title "Cubic Interpolation"
set style data lines

plot 'inter.txt' using 1:2 title "Interpolating Function"
