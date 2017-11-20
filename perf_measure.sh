#!/bin/bash
mkdir measurement;
likwid-topology -g -c > measurement/topology.txt

for f in {trab1,trab2}; do
    cd $f;
    make -B;
    for i in {32,33,64,65,128,129,256,257,512,1000,200}; do
        ./invmat -r $i -o ../measurement/$f_output.txt -i 10 } ;
        { likwid-perfcter -C 0 -g CACHE -m ./invmat -r $i -o /dev/null -i 10 } >>  ../measurement/cache.txt;
        { likwid-perfcter -C 0 -g MEM -m ./invmat -r $i -o /dev/null -i 10 } >>  ../measurement/mem.txt;
        { likwid-perfcter -C 0 -g FLOPS -m ./invmat -r $i -o /dev/null -i 10 } >>  ../measurement/flops.txt;
    done
    cd ..;
done
# cd trab2;
# for i in {32,33,64,65,128,129,256,257,512,1000,200}; do
#     {echo "#####\n##### trab2\n#####\n" && likwid-perfcter -C 0 -g FLOPS_AVX -m ./invmat -r $i -o /dev/null -i 10 } >/>  ../measurement/flops_avx.txt;
# done
