wget https://raw.github.com/forero/ComputationalMethodsData/master/homework/hw_1/Pi_2500000.txt
grep -o 0 Pi_2500000.txt | wc -l > 0.txt
grep -o 00 Pi_2500000.txt | wc -l > 00.txt
grep -o 000 Pi_2500000.txt | wc -l > 000.txt
grep -o 0000 Pi_2500000.txt | wc -l > 0000.txt
grep -o 00000 Pi_2500000.txt | wc -l > 00000.txt
grep -o 000000 Pi_2500000.txt | wc -l > 000000.txt
grep -o 1 Pi_2500000.txt | wc -l > 1.txt
grep -o 10 Pi_2500000.txt | wc -l > 10.txt
grep -o 100 Pi_2500000.txt | wc -l > 100.txt
grep -o 1000 Pi_2500000.txt | wc -l > 1000.txt
grep -o 10000 Pi_2500000.txt | wc -l > 10000.txt
grep -o 100000 Pi_2500000.txt | wc -l > 100000.txt
grep -o 2 Pi_2500000.txt | wc -l > 2.txt
grep -o 20 Pi_2500000.txt | wc -l > 20.txt
grep -o 200 Pi_2500000.txt | wc -l > 200.txt
grep -o 2000 Pi_2500000.txt | wc -l > 2000.txt
grep -o 20000 Pi_2500000.txt | wc -l > 20000.txt
grep -o 200000 Pi_2500000.txt | wc -l > 200000.txt
grep -o 3 Pi_2500000.txt | wc -l > 3.txt
grep -o 30 Pi_2500000.txt | wc -l > 30.txt
grep -o 300 Pi_2500000.txt | wc -l > 300.txt
grep -o 3000 Pi_2500000.txt | wc -l > 3000.txt
grep -o 30000 Pi_2500000.txt | wc -l > 30000.txt
grep -o 300000 Pi_2500000.txt | wc -l > 300000.txt
grep -o 4 Pi_2500000.txt | wc -l > 4.txt
grep -o 40 Pi_2500000.txt | wc -l > 40.txt
grep -o 400 Pi_2500000.txt | wc -l > 400.txt
grep -o 4000 Pi_2500000.txt | wc -l > 4000.txt
grep -o 40000 Pi_2500000.txt | wc -l > 40000.txt
grep -o 400000 Pi_2500000.txt | wc -l > 400000.txt
grep -o 5 Pi_2500000.txt | wc -l > 5.txt
grep -o 50 Pi_2500000.txt | wc -l > 50.txt
grep -o 500 Pi_2500000.txt | wc -l > 500.txt
grep -o 5000 Pi_2500000.txt | wc -l > 5000.txt
grep -o 50000 Pi_2500000.txt | wc -l > 50000.txt
grep -o 500000 Pi_2500000.txt | wc -l > 500000.txt
grep -o 6 Pi_2500000.txt | wc -l > 6.txt
grep -o 60 Pi_2500000.txt | wc -l > 60.txt
grep -o 600 Pi_2500000.txt | wc -l > 600.txt
grep -o 6000 Pi_2500000.txt | wc -l > 6000.txt
grep -o 60000 Pi_2500000.txt | wc -l > 60000.txt
grep -o 600000 Pi_2500000.txt | wc -l > 600000.txt
grep -o 7 Pi_2500000.txt | wc -l > 7.txt
grep -o 70 Pi_2500000.txt | wc -l > 70.txt
grep -o 700 Pi_2500000.txt | wc -l > 700.txt
grep -o 7000 Pi_2500000.txt | wc -l > 7000.txt
grep -o 70000 Pi_2500000.txt | wc -l > 70000.txt
grep -o 700000 Pi_2500000.txt | wc -l > 700000.txt
grep -o 8 Pi_2500000.txt | wc -l > 8.txt
grep -o 80 Pi_2500000.txt | wc -l > 80.txt
grep -o 800 Pi_2500000.txt | wc -l > 800.txt
grep -o 8000 Pi_2500000.txt | wc -l > 8000.txt
grep -o 80000 Pi_2500000.txt | wc -l > 80000.txt
grep -o 800000 Pi_2500000.txt | wc -l > 800000.txt
grep -o 9 Pi_2500000.txt | wc -l > 9.txt
grep -o 90 Pi_2500000.txt | wc -l > 90.txt
grep -o 900 Pi_2500000.txt | wc -l > 900.txt
grep -o 9000 Pi_2500000.txt | wc -l > 9000.txt
grep -o 90000 Pi_2500000.txt | wc -l > 90000.txt
grep -o 900000 Pi_2500000.txt | wc -l > 900000.txt
paste 0.txt 00.txt 000.txt 0000.txt 00000.txt 000000.txt > R2.txt
paste 1.txt 10.txt 100.txt 1000.txt 10000.txt 100000.txt >> R2.txt
paste 2.txt 20.txt 200.txt 2000.txt 20000.txt 200000.txt >> R2.txt
paste 3.txt 30.txt 300.txt 3000.txt 30000.txt 300000.txt >> R2.txt
paste 4.txt 40.txt 400.txt 4000.txt 40000.txt 400000.txt >> R2.txt
paste 5.txt 50.txt 500.txt 5000.txt 50000.txt 500000.txt >> R2.txt
paste 6.txt 60.txt 600.txt 6000.txt 60000.txt 600000.txt >> R2.txt
paste 7.txt 70.txt 700.txt 7000.txt 70000.txt 700000.txt >> R2.txt
paste 8.txt 80.txt 800.txt 8000.txt 80000.txt 800000.txt >> R2.txt
paste 9.txt 90.txt 900.txt 9000.txt 90000.txt 900000.txt >> R2.txt
rm 0.txt
rm 00.txt
rm 000.txt
rm 0000.txt
rm 00000.txt
rm 000000.txt
rm 1.txt
rm 10.txt
rm 100.txt
rm 1000.txt
rm 10000.txt
rm 100000.txt
rm 2.txt
rm 20.txt
rm 200.txt
rm 2000.txt
rm 20000.txt
rm 200000.txt
rm 3.txt
rm 30.txt
rm 300.txt
rm 3000.txt
rm 30000.txt
rm 300000.txt
rm 4.txt
rm 40.txt
rm 400.txt
rm 4000.txt
rm 40000.txt
rm 400000.txt
rm 5.txt
rm 50.txt
rm 500.txt
rm 5000.txt
rm 50000.txt
rm 500000.txt
rm 6.txt
rm 60.txt
rm 600.txt
rm 6000.txt
rm 60000.txt
rm 600000.txt
rm 7.txt
rm 70.txt
rm 700.txt
rm 7000.txt
rm 70000.txt
rm 700000.txt
rm 8.txt
rm 80.txt
rm 800.txt
rm 8000.txt
rm 80000.txt
rm 800000.txt
rm 9.txt
rm 90.txt
rm 900.txt
rm 9000.txt
rm 90000.txt
rm 900000.txt
rm Pi_2500000.txt