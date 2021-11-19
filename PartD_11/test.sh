#! /bin/sh
images=`ls ./imageSamples`;

cd ./build ;

for img in $images
do
    tmp=`echo ${img} | cut -d '.' -f 1`;
    format=`echo ${img} | cut -d '.' -f 2`;
    
    echo "\n------${img}------";
    echo "2 bits reduction (4)"
	./PartD_12 "../imageSamples/${img}" "../reducedImages/${tmp}_4.${format}";
	echo "\n4 bits reduction (16)"
	./PartD_12 "../imageSamples/${img}" "../reducedImages/${tmp}_16.${format}";
    echo "\n5 bits reduction (32)"
	./PartD_12 "../imageSamples/${img}" "../reducedImages/${tmp}_32.${format}";
    echo "\n6 bits reduction (64)"
	./PartD_12 "../imageSamples/${img}" "../reducedImages/${tmp}_64.${format}";
    echo "\n7 bits reduction (128)"
    ./PartD_12 "../imageSamples/${img}" "../reducedImages/${tmp}_128.${format}";
done
