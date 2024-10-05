#!/bin/bash
# Description:
#   Script for lazy people to execute all commands at once

if [[ "$1" == "" ]]; then
    read -p "What mode, sort or check? (S/C)" mode
    if [[ "$mode" == "S" ]]; then
        read -p "What kind of sorter? (IS/QS/RQS/MS/BMS/HS)" sorter
        read -p "Size of n? (5/1000/4000/16000/32000/1000000/ALL)" size
    elif [[ "$mode" == "C" ]]; then
        read -p "Size of n? (5/1000/4000/16000/32000/1000000/ALL)" size
    fi
elif [[ "$1" == "S" ]]; then
    mode=$1
    sorter=$2
    size=$3
elif [[ "$1" == "C" ]]; then
    mode=$1
    size=$2
else
    echo "Lazy code runner:"
    echo "type './execall.sh [S/C] [IS/QS/RQS/MS/BMS/HS] [5/1000/4000/16000/32000/1000000/ALL]'"
    echo "or './execall.sh' to use"
fi

if [[ "$mode" == "S" ]]; then
    if [[ "$size" == "ALL" ]]; then
        rm ./result/$sorter.result
        echo "Now running $sorter: n = 4000..."
        echo "Sorter: $sorter, n = 4000" >> ./result/$sorter.result
        echo "----------" >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/4000.case1.in ./outputs/4000.case1.out >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/4000.case2.in ./outputs/4000.case2.out >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/4000.case3.in ./outputs/4000.case3.out >> ./result/$sorter.result
        echo "----------" >> ./result/$sorter.result
        echo "Now running $sorter: n = 16000..."
        echo "Sorter: $sorter, n = 16000" >> ./result/$sorter.result
        echo "----------" >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/16000.case1.in ./outputs/16000.case1.out >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/16000.case2.in ./outputs/16000.case2.out >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/16000.case3.in ./outputs/16000.case3.out >> ./result/$sorter.result
        echo "----------" >> ./result/$sorter.result
        echo "Now running $sorter: n = 32000..."
        echo "Sorter: $sorter, n = 32000" >> ./result/$sorter.result
        echo "----------" >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/32000.case1.in ./outputs/32000.case1.out >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/32000.case2.in ./outputs/32000.case2.out >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/32000.case3.in ./outputs/32000.case3.out >> ./result/$sorter.result
        echo "----------" >> ./result/$sorter.result
        echo "Now running $sorter: n = 1000000..."
        ulimit -s 262144
        echo "Sorter: $sorter, n = 1000000" >> ./result/$sorter.result
        echo "----------" >> ./result/$sorter.result
        printf "Running case 1...\n"
        ./bin/NTU_sort -$sorter ./inputs/1000000.case1.in ./outputs/1000000.case1.out >> ./result/$sorter.result
        printf "Running case 2...\n"
        ./bin/NTU_sort -$sorter ./inputs/1000000.case2.in ./outputs/1000000.case2.out >> ./result/$sorter.result
        printf "Running case 3...\n"
        ./bin/NTU_sort -$sorter ./inputs/1000000.case3.in ./outputs/1000000.case3.out >> ./result/$sorter.result
        echo "----------" >> ./result/$sorter.result
    else
        echo "Now running $sorter: n = $size..."
        echo "Sorter: $sorter, n = $size" >> ./result/$sorter.result
        echo "----------" >> ./result/$sorter.result
        ./bin/NTU_sort -$sorter ./inputs/$size.case1.in ./outputs/$size.case1.out >> ./result/$sorter.result
        if [[ $size -ne 5 ]]; then
            ./bin/NTU_sort -$sorter ./inputs/$size.case2.in ./outputs/$size.case2.out >> ./result/$sorter.result
            ./bin/NTU_sort -$sorter ./inputs/$size.case3.in ./outputs/$size.case3.out >> ./result/$sorter.result
        fi
        echo "----------" >> ./result/$sorter.result
    fi
elif [[ "$mode" == "C" ]]; then
    if [[ "$size" == "ALL" ]]; then
        echo "Now checking: n = 4000..."
        ./utility/PA1_Result_Checker ./inputs/4000.case1.in ./outputs/4000.case1.out
        ./utility/PA1_Result_Checker ./inputs/4000.case2.in ./outputs/4000.case2.out
        ./utility/PA1_Result_Checker ./inputs/4000.case3.in ./outputs/4000.case3.out
        echo "Now checking: n = 16000..."
        ./utility/PA1_Result_Checker ./inputs/16000.case1.in ./outputs/16000.case1.out
        ./utility/PA1_Result_Checker ./inputs/16000.case2.in ./outputs/16000.case2.out
        ./utility/PA1_Result_Checker ./inputs/16000.case3.in ./outputs/16000.case3.out
        echo "Now checking: n = 32000..."
        ./utility/PA1_Result_Checker ./inputs/32000.case1.in ./outputs/32000.case1.out
        ./utility/PA1_Result_Checker ./inputs/32000.case2.in ./outputs/32000.case2.out
        ./utility/PA1_Result_Checker ./inputs/32000.case3.in ./outputs/32000.case3.out
        echo "Now checking: n = 1000000..."
        ./utility/PA1_Result_Checker ./inputs/1000000.case1.in ./outputs/1000000.case1.out
        ./utility/PA1_Result_Checker ./inputs/1000000.case2.in ./outputs/1000000.case2.out
        ./utility/PA1_Result_Checker ./inputs/1000000.case3.in ./outputs/1000000.case3.out
    else
        echo "Now checking: n = $size..."
        ./utility/PA1_Result_Checker ./inputs/$size.case1.in ./outputs/$size.case1.out
        if [[ $size -ne 5 ]]; then
            ./utility/PA1_Result_Checker ./inputs/$size.case2.in ./outputs/$size.case2.out
            ./utility/PA1_Result_Checker ./inputs/$size.case3.in ./outputs/$size.case3.out
        fi
    fi
fi
