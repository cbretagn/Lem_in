#!/bin/bash

if [ -f "lem-in" ]
then
	echo -e "\033[32mprogram found"
else
	make
fi

if [ -f "generator" ]
then
	echo -e "generator found\033[0m"
else
	exit
fi

echo -e "\n\033[1mWhich map would you like to test ?"
read -p "1 : flow-one
2 : flow-ten
3: flow-thousand
4: big
5: big-superposition --> " size
read -p "
Please enter the number of tests --> " nb

if [ -z $nb ]
then
	echo -e "\033[31mErreur de saisie"
	exit
fi
(( i = 0 ))

until [ $i -eq $nb ]
do
	case $size in
		0) 
			echo -e "\033[31mErreur de saisie"
			exit
			;;
		1) 
			./generator --flow-one > test.txt && ./lem-in < test.txt | wc -l > var.txt
			read ret < var.txt
			map="flow-one"
			;;
		2) 
			./generator --flow-ten > test.txt && ./lem-in < test.txt | wc -l > var.txt
			read ret < var.txt
			map="flow-ten"
			;;
		3) 
			./generator --flow-thousand > test.txt && ./lem-in < test.txt | wc -l > var.txt
			read ret < var.txt
			map="flow-thousand"
			;;
		4) 
			./generator --big > test.txt && ./lem-in < test.txt | wc -l > var.txt
			read ret < var.txt
			map="big"
			;;
		5) 
			./generator --big-superposition > test.txt && ./lem-in < test.txt | wc -l > var.txt
			read ret < var.txt
			map="big-superposition"
			;;
		*) 
			echo -e "\033[31mErreur de saisie"
			exit
			;;
	esac
	txt_l=`wc -l test.txt | tr -dc '0-9'`
	required=`sed '2!d' test.txt | tr -dc '0-9'`
	((total = $ret - 1 - $txt_l))
	((diff = $total - $required))
		# ((diff = $ret - $required))
	if [ $diff -le 3 ]
	then
		echo -e "\033[1;32m$total vs $required\033[0m --> $diff"
	elif [ $diff -le 10 ]
	then
		echo -e "\033[1;33m$total vs $required\033[0m --> $diff"
	else
		echo -e "\033[1;31m$total vs $required\033[0m --> $diff"
	fi
	if [ -z $min ] || [ $diff -lt $min ]
	then
		min=$diff
	fi
	if [ -z $max ] || [ $diff -gt $max ]
	then
		max=$diff
	fi
	(( i++ ))
	((average = $average + $diff))
	sleep 1
done

((average = $average / $i))

echo -e "\n\033[1mAverage line difference on a map of size $map ($nb tests) :\033[0m \033[1;32m$average\033[0m."
echo -e "\n\033[1mMinimum is :\033[0m \033[1;32m$min\033[0m."
echo -e "\n\033[1mMaximum is :\033[0m \033[1;31m$max\033[0m."
