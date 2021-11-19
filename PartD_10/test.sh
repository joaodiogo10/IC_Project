#! /bin/sh
images=`ls ./imageSamples`;

[ ! -d "./results" ] && mkdir results

cd ./build ;

for img in $images
do
	tmp=`echo ${img} | cut -d '.' -f 1`;
   	format=`echo ${img} | cut -d '.' -f 2`;
 	
	./ex10 "../imageSamples/${img}" "../results/${tmp}_32.${format}" 32;
	./ex10 "../imageSamples/${img}" "../results/${tmp}_64.${format}" 64;
	./ex10 "../imageSamples/${img}" "../results/${tmp}_128.${format}" 128;
done

