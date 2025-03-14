#!/bin/csh -f

set project      = "PWL"
set program      = "pwl"

# ./
set     files   = "CMakeLists.txt README.md"
foreach file (${files})
    sed -e s/T_PROGRAM/${program}/g ${file} > 1
    sed -e s/T_PROJECT/${project}/g 1 > ${file}
    rm -rf 1
end

# docs
cd docs
    set files   = "CMakeLists.txt doxygen.conf"
    foreach file (${files})
        sed -e s/T_PROJECT/${project}/g ${file} > 1
        sed -e s/T_PROGRAM/${program}/g 1 > ${file}
        rm -rf 1
    end
cd ..

# include
set files   = "main object"
cd include
    foreach file (${files})
        mv mysetting_${file}.hpp ${program}_${file}.hpp
        sed -e s/T_PROJECT/${project}/g ${program}_${file}.hpp > 1
        sed -e s/T_PROGRAM/${program}/g 1 > ${program}_${file}.hpp
        rm -rf 1
    end
cd ..

# src
set files   = "main object"
cd src
    foreach file (${files})
        mv mysetting_${file}.cpp ${program}_${file}.cpp
        sed -e s/T_PROJECT/${project}/g ${program}_${file}.cpp > 1
        sed -e s/T_PROGRAM/${program}/g 1 > ${program}_${file}.cpp
        rm -rf 1
    end
cd ..

# test
set files   = "main object"
cd test
    foreach file (${files})
        mv mysetting_${file}.test.cpp ${program}_${file}.test.cpp
        sed -e s/T_PROJECT/${project}/g ${program}_${file}.test.cpp > 1
        sed -e s/T_PROGRAM/${program}/g 1 > ${program}_${file}.test.cpp
        rm -rf 1
    end
cd ..

