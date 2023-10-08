#!/bin/sh
echo "Build yson lib..."

## build object files

for path in ./src/main/*.cpp; do
  file=${path##*/}
  obj_file="./build/main/${file%.*}.o"
  
  g_script="g++ -c $path -o $obj_file"
  echo $g_script
  $g_script

  obj_files="$obj_files$obj_file "

done

## build libyson

ar_script="ar rcs ./build/main/libyson.a $obj_files"
echo $ar_script
$ar_script

## build single yson.h header file

header_file=./build/main/yson.h
rm $header_file
echo "Build single header file $header_file"

for file in ./src/main/include/error/*.h; do 
    (sed '/#include ".*.h"/d' $file; echo) >> $header_file
done

### header files to include at the top of single header file

prio_files=(
"./src/main/include/jvalue.h" 
"./src/main/include/jnumber.h" 
"./src/main/include/jbool.h" 
"./src/main/include/jstring.h"
)

for file in ${prio_files[@]}; do
    echo "merge file $file"
    (sed '/#include ".*.h"/d' $file; echo) >> $header_file
done

### include all other header files
for file in ./src/main/include/*.h; do 
    if [[ ${prio_files[@]} =~ $file ]] 
    then
        echo "ignore file $file"
    else
        (sed '/#include ".*.h"/d' $file; echo) >> $header_file
    fi
done
