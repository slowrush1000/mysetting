#!/bin/csh -f

set     program = "pwl"

set     files   = `ls *.hpp`
foreach file (${files})
    set     output  = `basename ${file} .hpp`
    mv ${file} ${program}_${output}.hpp
end

set     files   = `ls *.cpp`
foreach file (${files})
    set     output  = `basename ${file} .cpp`
    mv ${file} ${program}_${output}.cpp
end

