#! /bin/sh
images=`ls ./imageSamples`;
videos=`ls ./videoSamples`;

[ ! -d "./results" ] && mkdir results

cd ./build ;

for img in $images
do
	./partB_4 image "../imageSamples/${img}" "../results/${img}_out.jpg";
done

for vid in $videos
do	     
	echo "${vid}"
	./partB_4 video "../videoSamples/${vid}" "../results/${vid}_out";
done
