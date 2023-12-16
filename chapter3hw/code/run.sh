mkdir output
g++ B.cpp -o ./output/B
g++ C.cpp -o ./output/C
g++ D.cpp -o ./output/D
g++ E.cpp -o ./output/E
echo -e "\nRunning B:\n"
./output/B
echo -e "\nRunning C:\n"
./output/C
echo -e "\nRunning D:\n"
./output/D
echo -e "\nRunning E:\n"
./output/E