wget https://raw.github.com/forero/ComputationalMethodsData/master/homework/hw_1/Pi_2500000.txt
grep -o 0 Pi_2500000.txt | wc -l > 0.txt
grep -o 00 Pi_2500000.txt | wc -l > 00.txt
grep -o 000 Pi_2500000.txt | wc -l > 000.txt
grep -o 0000 Pi_2500000.txt | wc -l > 0000.txt
grep -o 00000 Pi_2500000.txt | wc -l > 00000.txt
grep -o 000000 Pi_2500000.txt | wc -l > 000000.txt
grep -o 1 Pi_2500000.txt | wc -l > 1.txt
grep -o 12 Pi_2500000.txt | wc -l > 12.txt
grep -o 123 Pi_2500000.txt | wc -l > 123.txt
grep -o 1234 Pi_2500000.txt | wc -l > 1234.txt
grep -o 12345 Pi_2500000.txt | wc -l > 12345.txt
grep -o 123456 Pi_2500000.txt | wc -l > 123456.txt
paste 0.txt 00.txt 000.txt 0000.txt 00000.txt 000000.txt > remolinagutierrez.txt
paste 1.txt 12.txt 123.txt 1234.txt 12345.txt 123456.txt >> remolinagutierrez.txt
rm 0.txt
rm 00.txt
rm 000.txt
rm 0000.txt
rm 00000.txt
rm 000000.txt
rm 1.txt
rm 12.txt
rm 123.txt
rm 1234.txt
rm 12345.txt
rm 123456.txt
rm Pi_2500000.txt