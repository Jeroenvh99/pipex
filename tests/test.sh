#!/bin/bash

echo 'testing zero arguments'
(../pipex 2> zero_arguments.txt)
output=$(diff zero_arguments.txt error.txt)

if [ -n "$output"]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing five arguments'
(../pipex test1.txt cat cat test1_out.txt 2> five_arguments.txt)

if [ -s five_arguments.txt ]
then
	echo 'KO'
else
	echo 'OK'
fi
rm test1_out.txt

echo 'testing a non-existing command'
(../pipex test1.txt catd cat test1_out.txt 2> test_no_command.txt)
output=$(diff test_no_command.txt no_command.txt)

if [ -s "$output" ]
then
	echo 'KO'
else
	echo 'OK'
fi
rm test1_out.txt

echo 'testing a non-existing infile'
(../pipex testx.txt cat cat test1_out.txt 2> test_no_infile.txt)
output=$(diff test_no_infile.txt no_infile.txt)

if [ -s "$output" ]
then
	echo 'KO'
else
	echo 'OK'
fi
rm test1_out.txt

echo 'testing two commands'
(../pipex test1.txt "grep i" cat test1_out.txt)
output=$(diff test1_out.txt test1_expected.txt)

if [ -n "$output"]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing two commands'
(../pipex test1.txt "wc -l" cat test2_out.txt)
output=$(diff test2_out.txt test2_expected.txt)

if [ -n "$output"]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing here_doc'
(../pipex here_doc lol "wc -l" cat test3_out.txt) < test3.txt
output=$(diff test3_out.txt test3_expected.txt)

if [ -n "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing with the path unset'
unset PATH
echo 'testing here_doc'
(../pipex here_doc lol "sed 's/i/o/g'" "wc -l" test4_out.txt) < test3.txt
output=$(/usr/bin/diff test4_out.txt test4_expected.txt)

if [ -n "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing with the path set to PATH='
export PATH=
echo 'testing here_doc'
(../pipex here_doc lol "sed 's/i/o/g'" "wc -l" test4_out.txt) < test3.txt
output=$(/usr/bin/diff test4_out.txt test4_expected.txt)

if [ -n "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

echo 'testing three commands'
(../pipex test5.txt "ls -l" "awk '{print \$1}'" "wc -l" test5_out.txt) < test3.txt
output=$(/usr/bin/diff test5_out.txt test5_expected.txt)

if [ -n "$output" ]
then
	echo 'OK'
else
	echo 'KO'
fi

PATH=$(/usr/bin/getconf PATH)