mkdir output
g++ test_bisection.cpp -o ./output/test_bisection
g++ test_secant.cpp -o ./output/test_secant
g++ test_Newton.cpp -o ./output/test_Newton
g++ E.cpp -o ./output/E
g++ F.cpp -o ./output/F
echo -e "\ntest_bisection.cpp output:\n"
./output/test_bisection
echo -e "\ntest_Newton.cpp output:\n"
./output/test_Newton
echo -e "\ntest_secant.cpp output:\n"
./output/test_secant
echo -e "\nE.cpp output:\n"
./output/E
echo -e "\nF.cpp output:\n"
./output/F