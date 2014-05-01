wget https://raw.github.com/forero/ComputationalMethodsData/master/homework/hw_1/notas_fisicaII_201320.dat
echo "El numero de estudiantes que pasaron el primer parcial es: " 
awk '{if($1>=60)print $0 }' notas_fisicaII_201320.dat > parte1.txt
wc -l < parte1.txt
echo "El numero de estudiantes que pasaron el primer parcial, perdieron el final, y pasaron la materia es: " 
awk '{if($1>=60 && $5<60 && $6>=60) print $0}' notas_fisicaII_201320.dat > parte2.txt
wc -l < parte2.txt
echo "El numero de estudiantes que perdieron al menos 1 parcial, y pasaron la materia es: " 
awk '{if(($1<60 || $2<60 || $3<60) && $6>=60) print $0}' notas_fisicaII_201320.dat > parte3.txt
wc -l < parte3.txt
echo "El numero de estudiantes que pasaron solamente dos parciales y pasaron la materia es: "
awk '{if((($1>=60 && $2>=60 && $3<60) || ($1>=60 && $3>=60 && $2<60) || ($3>=60 && $2>=60 && $1<60)) && $6>=60) print $0}' notas_fisicaII_201320.dat > parte4.txt
wc -l < parte4.txt

rm parte1.txt
rm parte2.txt
rm parte3.txt
rm parte4.txt
rm notas_fisicaII_201320.dat