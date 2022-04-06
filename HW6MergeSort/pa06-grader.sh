#!/bin/bash

valgrindFailed=false

function verifyOutputFiles {
funcs=(id first last)
numCompareCorrect=9
for i in 1 2 3; do
  for j in "${funcs[@]}"; do
    if [[ -e $j$i ]]; then
      linesDifferent=$(diff -U 0 --ignore-all-space -B $j$i expected/$j$i | grep ^@ | wc -l)
      echo "[*] There are $linesDifferent line difference(s) for $j$i"
      if [[ linesDifferent -ne 0 ]]; then
        numCompareCorrect=$(echo "$numCompareCorrect - 1" | bc)
      fi
    else
      echo "[!] Could not find output file $j$i"
      numCompareCorrect=$(echo "$numCompareCorrect - 1" | bc)
    fi
  done
done
}

function verifyValgrind {
#echo 'grep -P -o "in use at exit: \d{1,3}(,\d{3})*(\.\d+)?" log3 | grep -P -o "\d{1,3}(,\d{3})*(\.\d+)?"'
bytesLeaked=$(grep -P -o "in use at exit: \d{1,3}(,\d{3})*(\.\d+)?" log3 | grep -P -o "\d{1,3}(,\d{3})*(\.\d+)?")
bytesLeaked=$(sed "s/,//g" <<< $bytesLeaked)
echo "[*] You have leaked $bytesLeaked byte(s) of memory."
echo "[*] Testing valgrind errors reported. (-50% for any error)"
echo 'grep -o "ERROR SUMMARY: [0-9]*" log3 | grep -o "[0-9]*"'
valgrindErrors=$(grep -o "ERROR SUMMARY: [0-9]*" log3 | grep -o "[0-9]*")
echo "[*] You have $valgrindErrors error(s) detected by valgrind."
}

compilestu=true
grade=0
studentGrade=0
partialGrade=0
echo "[*] Cleaning up..."
make -f Makefile-script clean > /dev/null
echo "[*] Compiling student's files"
make -f Makefile-script pa06-stu-of > /dev/null
if [[ $? -ne 0 ]]; then
	make -f Makefile-script pa06-stu > /dev/null
	if [[ $? -ne 0 ]]; then
		echo "[!] There was an error in compiling with your pa06.c and student.c!"
  		compilestu=false
	else
		echo "[*] Passed!"
	fi
else
	echo "[*] Passed!"
fi

# test output files
if [[ "$compilestu" = true ]]; then
  echo "[*] Running tests(100%), 50% points will be deducted for any valgrind error"
  make -f Makefile-script test-stu > /dev/null
  if [[ $? -ne 0 ]]; then
    echo "[!] There was an error in running the tests!"
    echo "[!] Failed"
  fi
    echo "[*] Verifying output files."
    verifyOutputFiles
    stuCorrect=$numCompareCorrect
      echo "[*] You passed $stuCorrect/9 test cases with your solution."

      studentGrade=$(echo "scale=2;$studentGrade + ($stuCorrect/9)*100" | bc)
      valgrind --log-file=log3 --tool=memcheck --leak-check=full ./pa06-stu inputs/testinput3 id3 first3 last3 > /dev/null
    if [[ $? -ne 0 ]]; then
      echo "[!] Valgrind did not exit cleanly. This may be due to a segmentation fault. 50% points reduced."
      valgrindErrors=1
    else
      verifyValgrind
      rm log3
    fi

   if [[ $valgrindErrors -ne 0 ]]; then
      studentGrade=$(echo "$studentGrade*0.5" | bc)

  fi
fi
echo " "

if (( $(bc <<< "$studentGrade != 100.00" ) )); then
    instructorMergeCorrect=0
    instructorMergeGrade=0
    instructorMsortCorrect=0
    instructorMsortGrade=0
      
    echo "[****] Attempting to give partial credit..."
    echo "[*] Attempting to compile and run your msort function with instructor's merge and coy functions...(40%)"
    make -f Makefile-script pa06-msort > /dev/null
    if [[ $? -ne 0 ]]; then
	echo "[!] There was an error in compiling your msort function with instructor's merge"
    else
        make -f Makefile-script test-msort > /dev/null
        if [[ $? -ne 0 ]]; then
            echo "[!] There was an error in running the tests!"
            echo "[!] Failed"
        fi
        echo "[*] Verifying output files."
        verifyOutputFiles
        instructorMergeCorrect=$numCompareCorrect
        echo "[*] You passed $instructorMergeCorrect/9 test cases with the instructor's merge and copy function."
        instructorMergeGrade=$(echo "scale=2;$instructorMergeGrade + ($instructorMergeCorrect/9)*100" | bc)

        valgrind --log-file=log3 --tool=memcheck --leak-check=full ./pa06-msort inputs/testinput3 id3 first3 last3 > /dev/null
        if [[ $? -ne 0 ]]; then
            echo "[!] Valgrind did not exit cleanly. This may be due to a segmentation fault. 50% points reduced."
            valgrindErrors=1
        else
            verifyValgrind
            rm log3
        fi
        if [[ $valgrindErrors -ne 0 ]]; then
            instructorMergeGrade=$(echo "$instructorMergeGrade*0.5" | bc)

        fi
    fi
       
    echo " "
    echo "[*] Attempting to compile and run your merge and copy funciton with instructor's msort functions...(60%)"
    make -f Makefile-script pa06-merge > /dev/null
    if [[ $? -ne 0 ]]; then
	echo "[!] There was an error in compiling your merge function with instructor's msort"
    else
        make -f Makefile-script test-merge > /dev/null
        if [[ $? -ne 0 ]]; then
            echo "[!] There was an error in running the tests!"
            echo "[!] Failed"
        fi
        echo "[*] Verifying output files."
        verifyOutputFiles
        instructorMsortCorrect=$numCompareCorrect
        echo "[*] You passed $instructorMsortCorrect/9 test cases with the instructor's msort function."
        instructorMsortGrade=$(echo "scale=2;$instructorMsortGrade + ($instructorMsortCorrect/9)*100" | bc)

        valgrind --log-file=log3 --tool=memcheck --leak-check=full ./pa06-merge inputs/testinput3 id3 first3 last3 > /dev/null
        if [[ $? -ne 0 ]]; then
            echo "[!] Valgrind did not exit cleanly. This may be due to a segmentation fault. 50% points reduced."
            valgrindErrors=1
        else
            verifyValgrind
            rm log3
        fi
        if [[ $valgrindErrors -ne 0 ]]; then
            instructorMsortGrade=$(echo "$instructorMsortGrade*0.5" | bc)

        fi
    fi
    
    partialGrade=$(echo "scale=2;($instructorMsortGrade*0.6) + ($instructorMergeGrade*0.4)" | bc)

fi

echo " "
echo "[*]Checking for unreachable code ..."
make -f Makefile-script pa06-stu-check-unreachable > /dev/null
if [[ $? -ne 0 ]]; then
    echo "[!] Warning! You have unreachable code. For next assignemnt this warning will be treated as an error.!"
else
    echo "No unreachable code present"
fi


echo " "
if (( $(bc <<< "$studentGrade >= $partialGrade" ) )); then
    echo "[*] It is more advantageous for you to receive credit with your solution."
     grade=$studentGrade
else
      echo "[*] It is more advantageous for you to receive partial credit."
      grade=$partialGrade
fi

echo $grade > grade.txt
