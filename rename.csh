#!/bin/csh -f

set PROGRAM = "PWL"
set program = "pwl"

cd  src
    set     files   = `ls *.hpp.in`
    foreach file (${files})
        set output  = `basename ${file} .hpp.in`
        mv ${file} ${program}_${output}.hpp.in
    end

    set     files   = `ls *.hpp`
    foreach file (${files})
        set output  = `basename ${file} .hpp`
        mv ${file} ${program}_${output}.hpp
    end

    set     files   = `ls *.cpp`
    foreach file (${files})
        set output  = `basename ${file} .cpp`
        mv ${file} ${program}_${output}.cpp
    end

    set     files   = `ls *`
    foreach file (${files})
        sed -e s/my/${program}/g ${file} > 1
        sed -e s/MY/${PROGRAM}/g 1 > ${file}
    end
cd  ..
