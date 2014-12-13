set terminal png
set output 'aufg1.png'
plot "./aufg1.txt" u 1:2 w l title "Taylor", "" u 1:3 w l title "Funktion", "" u 1:4 w l title "Pade"
