ROUTER=xy
EXE_DIR=/home/zhangzhe/codespace/temp-noc/linedata/
DEST_DIR=/home/zhangzhe/codespace/temp-noc/noc-traffic/data/

mkdir ${DEST_DIR}loss
for file in `ls ${DEST_DIR}trace_data/`;
do
     INPUT_FILE=${DEST_DIR}trace_data/${file}
     OUTPUT_FILE=${DEST_DIR}loss/${file:0:8}.txt

     ${EXE_DIR}linedata ${INPUT_FILE} ${OUTPUT_FILE}
done
#${EXE_DIR}linedata ${DEST_DIR}/trace_data/${i}
