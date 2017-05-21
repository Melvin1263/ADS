reset
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left

plot \
"matrixcolmajor.txt" with linespoints title 'ColMajor',\
"matrixrowmajor.txt" with linespoints title 'RowMajor',\
"matrixcolmajorth.txt" with linespoints title 'ColMajorTH',\
"matrixrowmajorth.txt" with linespoints title 'RowMajorTH',\