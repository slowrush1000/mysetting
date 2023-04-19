#!/bin/csh -f

set MY      = "PWL"
set my      = "pwl"

#
set     files   = "CMakeLists.txt"
foreach file (${files})
    sed -e s/myname/${program}/g ${file} > 1
    mv -f 1 ${file}
end

#
cd doc
    set files   = "CMakeLists.txt doxygen.conf"
    foreach file (${files})
        sed -e s/myname/${program}/g ${file} > 1
        mv -f 1 ${file}
    end
cd ..

#
cd src
    set     files   = `ls *`
    foreach file (${files})
        sed -e s/myname/${program}/g ${file} > 1
        sed -e s/MYNAME/${PROGRAM}/g 1 > ${file}
    end

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

cd ..
