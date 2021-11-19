#! /bin/sh
images=`ls ./imageSamples`;

cd ./build ;

for img in $images
do
    tmp=`echo ${img} | cut -d '.' -f 1`;
    format=`echo ${img} | cut -d '.' -f 2`;
    
    echo "\n------${img}------";
    echo "5 bits reduction (32)"
	./PartD_12 "../imageSamples/${img}" "../reducedImages/${tmp}_32.${format}";
    echo "\n6 bits reduction (64)"
	./PartD_12 "../imageSamples/${img}" "../reducedImages/${tmp}_64.${format}";
    echo "\n7 bits reduction (128)"
    ./PartD_12 "../imageSamples/${img}" "../reducedImages/${tmp}_128.${format}";
done
