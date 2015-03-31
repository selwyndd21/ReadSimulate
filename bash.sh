make
./3DRPF_read.exe example/3DRPF_cs2cy26.txt > TEST
# sed -i "s/ 0.000/      /g" debug_CASE*
#diff -ubi CASE0101.txt debug_CASE0101.txt > diff0101
#diff -ubi CASE0201.txt debug_CASE0201.txt > diff0201
#diff -ubi CASE0301.txt debug_CASE0301.txt > diff0301
#diff -ubi CASE0401.txt debug_CASE0401.txt > diff0401
#diff -ubi CASE0501.txt debug_CASE0501.txt > diff0501
#diff -ubi CASE0601.txt debug_CASE0601.txt > diff0601
#diff -ubi CASE0701.txt debug_CASE0701.txt > diff0701
#diff -ubi CASE0801.txt debug_CASE0801.txt > diff0801
#diff -ubi CASE0901.txt debug_CASE0901.txt > diff0901
#diff -ubi CASE1001.txt debug_CASE1001.txt > diff1001
#diff -ubi CASE1101.txt debug_CASE1101.txt > diff1101
#diff -ubi CASE1201.txt debug_CASE1201.txt > diff1201
#diff -ubi CASE1301.txt debug_CASE1301.txt > diff1301
#diff -ubi CASE1401.txt debug_CASE1401.txt > diff1401
#diff -ubi CASE1501.txt debug_CASE1501.txt > diff1501
#diff -ubi CASE1601.txt debug_CASE1601.txt > diff1601
#diff -ubi CASE1701.txt debug_CASE1701.txt > diff1701
#diff -ubi CASE1801.txt debug_CASE1801.txt > diff1801
#diff -ubi CASE1901.txt debug_CASE1901.txt > diff1901
#diff -ubi CASE2001.txt debug_CASE2001.txt > diff2001
#diff -ubi CASE2101.txt debug_CASE2101.txt > diff2101
#diff -ubi CASE2201.txt debug_CASE2201.txt > diff2201
#diff -ubi CASE2301.txt debug_CASE2301.txt > diff2301
#diff -ubi CASE2401.txt debug_CASE2401.txt > diff2401
#diff -ubi CASE2501.txt debug_CASE2501.txt > diff2501
#diff -ubi CASE2601.txt debug_CASE2601.txt > diff2601
#diff -ubi CASE2701.txt debug_CASE2701.txt > diff2701
#diff -ubi CASE2801.txt debug_CASE2801.txt > diff2801
#diff -ubi CASE2901.txt debug_CASE2901.txt > diff2901
#diff -ubi CASE3001.txt debug_CASE3001.txt > diff3001
#diff -ubi CASE3101.txt debug_CASE3101.txt > diff3101
#cat diff[0-3]* > diff
#rm diff[0-3]* CASE* debug_CASE*
