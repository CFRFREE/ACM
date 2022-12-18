i=0
while true; do
    let i++
    ./scq > 1.in
    ./sf < 1.in > out1
    ./bl < 1.in > out2
    if diff out1 out2 ; then
        printf "Accept in case $i \n"
    else
        printf "Wrong Answer in case $i\n"
        printf "************\ninput: \n"
           cat < 1.in   
        exit 0;
    fi
 
done