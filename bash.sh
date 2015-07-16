make rpf
rm output_3DRPF.txt
./3DRPF_read.exe example/3DRPF_cs2cy26.txt > TEST
 sed -i "s/ 0.000/      /g" output_3DRPF.txt
