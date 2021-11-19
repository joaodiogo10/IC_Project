#! /bin/sh
images=`ls ./imageSamples`;

[ ! -d "./results" ] && mkdir results

cd ./build ;

for img in $images
do
	./ex10 "../imageSamples/${img}" "../results/${img}_32.jpg" 32;
	./ex10 "../imageSamples/${img}" "../results/${img}_64.jpg" 64;
	./ex10 "../imageSamples/${img}" "../results/${img}_128.jpg" 128;
done

