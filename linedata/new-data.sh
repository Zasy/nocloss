for i in `ls ./data/trace_data`;
do
    ./linedata ./data/trace_data/${i} ./data/loss/${i:0:6}_loss.txt 
done
