
plotResult("sample01",1);
plotResult("sample02",2);
plotResult("sample03",3);
plotResult("sample04",4);
plotResult("sample05",5);
plotResult("sample06",6);
plotResult("sample07",7);

function e = plotResult(dir,fig)
    formatSpec = '%f';
    fileXAxis = fopen(dir + '/xAxis.txt','r');
    x = fscanf(fileXAxis,formatSpec);
    
    formatSpec = '%d';
    fileChannel1 = fopen(dir + '/channel1.txt','r');
    channel1 = fscanf(fileChannel1,formatSpec);
    
    fileChannel2= fopen(dir + '/channel2.txt','r');
    channel2 = fscanf(fileChannel2,formatSpec);
    
    fileMono= fopen(dir + '/monoChannel.txt','r');
    mono = fscanf(fileMono,formatSpec);


    figure(fig);
    plot(x, channel1, 'b', x, channel2, 'r', x, mono, 'g');
    legend("Channel 1", "Channel 2", "mono")
    xlabel("Amplitude");
    grid on;
end