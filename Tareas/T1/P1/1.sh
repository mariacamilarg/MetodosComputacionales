wget https://raw.github.com/forero/ComputationalMethodsData/master/homework/hw_1/hamlet.txt
echo "El numero de lineas que no tiene la palabra the es: " 
grep -v "the" --word-regexp hamlet.txt | wc -l

echo "a" > a.txt
echo "e" > e.txt
echo "i" > i.txt
echo "o" > o.txt
echo "u" > u.txt

grep -o a hamlet.txt --ignore-case | wc -l > 1.txt 
paste 1.txt a.txt > vocales.txt
grep -o e hamlet.txt --ignore-case | wc -l > 2.txt
paste 2.txt e.txt >> vocales.txt
grep -o i hamlet.txt --ignore-case | wc -l > 3.txt
paste 3.txt i.txt >> vocales.txt
grep -o o hamlet.txt --ignore-case | wc -l > 4.txt
paste 4.txt o.txt >> vocales.txt
grep -o u hamlet.txt --ignore-case | wc -l > 5.txt
paste 5.txt u.txt >> vocales.txt

rm a.txt
rm e.txt
rm i.txt
rm o.txt
rm u.txt
rm 1.txt
rm 2.txt
rm 3.txt
rm 4.txt
rm 5.txt
rm hamlet.txt

sort -n vocales.txt | tac > vocales2.txt
echo "La vocal mas repetida es:"
awk '{print $2}' vocales2.txt | head -1
echo "Y el numero de veces que esta aparece es:"
awk '{print $1}' vocales2.txt | head -1

rm vocales.txt
rm vocales2.txt
