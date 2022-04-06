#!/bin/bash

grade=0
numTests=20

function runTests {
simpleCorrect=0
echo "[*] Testing simple addition (2 3 +) = 5.000000"
stdbuf -i0 -o0 -e0 ./pa11 inputs/in0 2> /dev/null | tail -1 | diff ans/in0 - > /dev/null
if [[ $? -eq 0 ]]; then
  simpleCorrect=$(bc <<< "$simpleCorrect + 1")
fi

echo "[*] Testing simple subtraction (2 3 -) = -1.000000"
stdbuf -i0 -o0 -e0 ./pa11 inputs/in1 2> /dev/null | tail -1 | diff ans/in1 - > /dev/null
if [[ $? -eq 0 ]]; then
  simpleCorrect=$(bc <<< "$simpleCorrect + 1")
fi

echo "[*] Testing simple multiplication (2 3 *) = 6.000000"
stdbuf -i0 -o0 -e0 ./pa11 inputs/in2 2> /dev/null | tail -1 | diff ans/in2 - > /dev/null
if [[ $? -eq 0 ]]; then
  simpleCorrect=$(bc <<< "$simpleCorrect + 1")
fi

echo "[*] Testing simple division (2 3 /) = 0.666667"
stdbuf -i0 -o0 -e0 ./pa11 inputs/in3 2> /dev/null | tail -1 | diff ans/in3 - > /dev/null
if [[ $? -eq 0 ]]; then
  simpleCorrect=$(bc <<< "$simpleCorrect + 1")
fi
echo "[*] You passed $simpleCorrect/4 of the simple test cases."

echo ""
complexCorrect=0
testCases=(4 5 6 7 8 9 10 11 12 13 14 15 16)
echo "[*] Testing several complex expressions."
for i in "${testCases[@]}"
do
  stdbuf -i0 -o0 -e0 ./pa11 inputs/in$i 2> /dev/null | tail -1 | diff ans/in$i - > /dev/null
  if [[ $? -eq 0 ]]; then
    complexCorrect=$(bc <<< "$complexCorrect + 1")
  fi
done
echo "[*] You passed $complexCorrect/13 of the complex test cases."

echo ""
errorCorrect=0
echo "[*] The following test cases should return EXIT_FAILURE."

echo "[*] Testing a file that has too many numbers for the operands given."
stdbuf -i0 -o0 -e0 ./pa11 inputs/in17 > /dev/null 2>&1
if [[ $? -eq 1 ]]; then
  errorCorrect=$(bc <<< "$errorCorrect + 1")
fi

echo "[*] Testing a file that has too few numbers for the operands given."
stdbuf -i0 -o0 -e0 ./pa11 inputs/in18 > /dev/null 2>&1
if [[ $? -eq 1 ]]; then
  errorCorrect=$(bc <<< "$errorCorrect + 1")
fi

echo "[*] Testing a nonexistant file."
stdbuf -i0 -o0 -e0 ./pa11 inputs/in19 > /dev/null 2>&1
if [[ $? -eq 1 ]]; then
  errorCorrect=$(bc <<< "$errorCorrect + 1")
fi

echo "[*] You passed $errorCorrect/3 of the error test cases."
studentCorrect=$(bc <<< "$simpleCorrect + $complexCorrect + $errorCorrect")

}

function verifyValgrind {
bytesLeaked=$(grep -P -o "in use at exit: \d{1,3}(,\d{3})*(\.\d+)?" log1 | grep -P -o "\d{1,3}(,\d{3})*(\.\d+)?")
bytesLeaked=$(sed "s/,//g" <<< $bytesLeaked)
echo "[*] There are $bytesLeaked byte(s) leaked."
valgrindErrors=$(grep -o "ERROR SUMMARY: [0-9]*" log1 | grep -o "[0-9]*")
echo "[*] There are $valgrindErrors error(s) detected by valgrind."
}

function printHeader {
echo "*****************************************************************************************************"
echo "* [!] Please contact the person who made this commit if you beleive there are errors in the result. *"
echo "* [!] In this case, it would be Alex: aionescu at purdue dot edu.                                   *"
echo "* [!] Do not contact the other TA as they would not be able to help!                                *"
echo "*****************************************************************************************************"
}

# if bash receives a segfault from a child process don't do anything
trap "" SIGSEGV

printHeader
echo ""
echo "[*] Running make clean..."
make clean > /dev/null 2>&1
if [[ $? -ne 0 ]]; then
  echo "[!] make clean did not succeed!"
  echo $grade > grade.txt
  exit
fi

echo "[*] Verifying pa11 and *.o do not exist."
if ! (find *.o || find "pa11") > /dev/null 2>&1; then
  echo "[*] Passed!"
else
  echo "[!] Failed!"
  echo "[!] Perhaps your .o files or your pa11 executable still exist after running make clean?"
  echo $grade > grade.txt
  exit
fi

echo "[*] Running make all..."
make all > /dev/null 2>&1

# test if code compiled
if [[ $? -ne 0 ]]; then
  echo "[!] There was an error in compiling the program! Grade set to 0."
  echo "[!] Please make sure you have a recipe named 'all' that creates an executable named 'pa11'."
  echo $grade > grade.txt
  exit
fi

echo "[*] Checking to see if an executable named 'pa11' exists."
if (find "pa11") > /dev/null 2>&1; then
  echo "[*] Passed!"
else
  echo "[!] Failed!"
  echo "[!] Please make sure you have a recipe named 'all' that creates an executable named 'pa11'."
  echo $grade > grade.txt
  exit
fi

# code compiled successfully
echo ""
echo "[*] Running tests with student solution..."
runTests
if (( $(bc <<< "$studentCorrect < 0") )); then
  studentCorrect=0
fi
echo "[*] You passed $studentCorrect/$numTests with your solution. (5% each)"

grade=$(bc <<< "$studentCorrect * 100/$numTests")

echo ""
echo "[*] Verifying valgrind memory leaks & errors. (-10% off per byte/error)"
valgrind --log-file=log1 --tool=memcheck --leak-check=full ./pa11 inputs/in12 > /dev/null 2>&1
if [[ $? -ne 0 ]]; then
  echo "[!] Valgrind did not exit with EXIT_SUCCESS! This is probably due to a segfault. Valgrind needs to be able to run to perform memory leak analysis. Grade set to 0%."
  grade=0
  echo $grade > grade.txt
  exit
fi
verifyValgrind
grade=$(bc <<< "$grade - 10 * $bytesLeaked - 10 * $valgrindErrors")

# bound check
if (( $(bc <<< "$grade < 0") )); then
  grade=0
fi
if (( $(bc <<< "$grade > 100") )); then
  grade=100
fi

make clean > /dev/null 2>&1

echo $grade > grade.txt
