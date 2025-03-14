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
        sed -e s/myname/${program}/g ${file} > 1
        mv -f 1 ${file}
    end
cd ..

# src
set files   = "main object"
cd src
    foreach file (${files})
        mv mysetting_${file}.cpp ${program}_${file}.cpp
        sed -e s/T_PROJECT/${project}/g ${program}_${file}.cpp > 1
        sed -e s/T_PROGRAM/${program}/g 1 > ${project}_${file}.cpp
        rm -rf 1
    end
cd ..

# include
set files   = "main object"
cd include
    foreach file (${files})
        mv mysetting_${file}.hpp ${program}_${file}.hpp
        sed -e s/T_PROJECT/${project}/g ${program}_${file}.hpp > 1
        sed -e s/T_PROGRAM/${program}/g 1 > ${project}_${file}.hpp
        rm -rf 1
    end
cd ..
