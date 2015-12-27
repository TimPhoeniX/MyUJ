set term png size 2000
set output "inter.png"

set title "Cubic Interpolation"
set style data lines

plot 'inter.txt' using 1:2 title "Interpolating Function"
