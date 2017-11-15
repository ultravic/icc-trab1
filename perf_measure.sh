#!/bin/bash
for i in {32,33,64,65,128,129,256,257,512,1000,200}; do
    ./invmat  -r $i -i 10;
done
# -o /dev/null