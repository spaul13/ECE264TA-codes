#!/bin/bash

grade=0
numTests_valid=7
numTests_invalid=3
numTests=10
function runTests {
declare -A inputFiles_invalid=(
                       ["key_inputs/maze2 path2_out"]="Failure"
                       ["key_inputs/maze8 path8_out"]="Failure"
                       ["key_inputs/maze5 path5_out"]="Failure")
declare -A inputFiles_valid=(["key_inputs/maze1 path1_out"]="Success"
                       ["key_inputs/maze3 path3_out"]="Success"
                       ["key_inputs/maze4 path4_out"]="Success"
                       ["key_inputs/maze6 path6_out"]="Success"
                       ["key_inputs/maze7 path7_out"]="Success"
                       ["key_inputs/maze9 path9_out"]="Success"
                       ["key_inputs/maze10 path10_out"]="Success")
numCorrect_valid=0
numCorrect_invalid=0
numCorrect=0
for inputFile in "${!inputFiles_invalid[@]}"; do
  # the stdbuf is to ensure if they segfault in the middle we hopefully see if at least their solution
  # produced a Success/Failure message and at least give them credit for the correct answer. Valgrind
  # runs later in the script to remove points based on those errors.
  actual=$(stdbuf -i0 -o0 -e0 $1 $inputFile 2>/dev/null  | tail -1)
  grep -i ${inputFiles_invalid[$inputFile]} <<< $actual >/dev/null 2>&1 
  if [[ $? -eq 0 ]]; then
    #echo "[*] Passed!"
    numCorrect_invalid=$(bc <<< "$numCorrect_invalid + 1")
    numCorrect=$(bc <<< "$numCorrect + 1")
  else
    : # do nothing
    #echo "[!] Failed!"
  fi
done
for inputFile1 in "${!inputFiles_valid[@]}"; do
  # the stdbuf is to ensure if they segfault in the middle we hopefully see if at least their solution
  # produced a Success/Failure message and at least give them credit for the correct answer. Valgrind
  # runs later in the script to remove points based on those errors.
  actual=$(stdbuf -i0 -o0 -e0 $1 $inputFile1 2>/dev/null | tail -1)
  grep -i ${inputFiles_valid[$inputFile1]} <<< $actual > /dev/null 2>&1
  if [[ $? -eq 0 ]]; then
    #echo "[*] Passed!"
    numCorrect_valid=$(bc <<< "$numCorrect_valid + 1")
    numCorrect=$(bc <<< "$numCorrect + 1")
  else
    : # do nothing
    #echo "[!] Failed!"
  fi
done
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
echo "* [!] In this case, it would be Akshada: kulkar18 at purdue dot edu.                                   *"
echo "* [!] Do not contact the other TA as they would not be able to help!                                *"
echo "*****************************************************************************************************"
}

# if bash receives a segfault from a child process don't do anything
trap "" SIGSEGV

printHeader
echo ""
echo "[*] Cleaning up..."
make -f Makefile-script clean > /dev/null 2>&1
#stuGrade=$(echo "0.00" | bc)
stuGrade=0
stuCompile=0
instGrade=0
stu_maze3_valgrindErrors=0
inst_maze3_valgrindErrors=0
echo "[*] Attempting to compile with student's path.c and maze.c (if files are submitted - not required) and instructor's pa08.c ..."
make -f Makefile-script stu_pa08 > /dev/null 2>&1
# test if code compiled
if [[ $? -ne 0 ]]; then
	echo "[!] could not compile"
else
	stuCompile=100
	echo "[*] Running tests..."
	runTests ./stu_pa08
	studentCorrect=$numCorrect
	echo "[*] You passed $numCorrect_valid/$numTests_valid valid mazes and $numCorrect_invalid/$numTests_invalid invalid mazes."
	echo "[*] You passed $studentCorrect/$numTests total mazes with your path.c and maze.c."
	stuGrade=$(echo "scale=2;$stuGrade + ($studentCorrect/$numTests)*100" | bc)
	stu_maze3_valgrindErrors=0
		
	# valgrind check
	echo "[*] Testing valgrind errors/memory leaks. (-50% for any error)"
	valgrind --log-file=log1 --tool=memcheck --leak-check=full ./stu_pa08 key_inputs/maze3 key_inputs/path3_out > /dev/null 2>&1
	if [[ $? -ne 0 ]]; then
	  echo "[!] Valgrind did not exit with EXIT_SUCCESS! Valgrind needs to be able to run to perform memory leak analysis."
	  	stuGrade=0
	else
	 	verifyValgrind
		stu_maze3_valgrindErrors=$valgrindErrors
	fi
	if [[ $stu_maze3_valgrindErrors -ne 0 ]]; then
		stuGrade=$(echo "$stuGrade*0.5"| bc)
	fi
fi

if (( $(bc <<< "$stuGrade != 100.00" ) )); then
	make -f Makefile-script clean > /dev/null 2>&1

	echo "[*] Attempting to compile with instructor's path.c, maze.c and pa08.c ..."
	make -f Makefile-script inst_pa08 > /dev/null 2>&1
	
	# test if code compiled
	if [[ $? -ne 0 ]]; then
	  echo "[!] There was an error in compiling the program! Grade set to 0."
	  echo "[!] Please make sure to compile with -std=c99 -g -Wall -Wshadow --pedantic -Wunreachable-code -Wvla -Werror"
	  echo $grade > grade.txt
	  exit
	fi
	
	# code compiled successfully
	echo "[*] Passed!"
	echo "[*] Running tests..."
	runTests ./inst_pa08
	studentCorrect=$numCorrect
	echo "[*] You passed $numCorrect_valid/$numTests_valid valid mazes and $numCorrect_invalid/$numTests_invalid invalid mazes."
	echo "[*] You passed $studentCorrect/$numTests total mazes with instructor's path.c and maze.c."
	instGrade=$(echo "scale=2;$instGrade + ($studentCorrect/$numTests)*100" | bc)
	
	# valgrind check
	echo "[*] Testing valgrind errors/memory leaks. (-50% for any error)"
	valgrind --log-file=log1 --tool=memcheck --leak-check=full ./inst_pa08 key_inputs/maze3 key_inputs/path3_out > /dev/null 2>&1
	if [[ $? -ne 0 ]]; then
	  echo "[!] Valgrind did not exit with EXIT_SUCCESS! Valgrind needs to be able to run to perform memory leak analysis. Grade set to 0%."
	  grade=0
	  echo $grade > grade.txt
	  exit
	fi
	verifyValgrind
	inst_maze3_valgrindErrors=$valgrindErrors
	
	if [[ $inst_maze3_valgrindErrors -ne 0 ]]; then
		instGrade=$(echo "$instGrade*0.5"| bc)
	fi
fi
if (( $(bc <<< "$stuGrade >= $instGrade" ) )); then
     grade=$stuGrade
else
      grade=$instGrade
fi
# bound check
if (( $(bc <<< "$grade < 0") )); then
  grade=0
fi
if (( $(bc <<< "$grade > 100") )); then
  grade=100
fi

make -f Makefile-script clean > /dev/null 2>&1

echo $grade > grade.txt
