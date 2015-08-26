clear;
close all;
hold on;

% Parameters
NbDevices    = 7;
dataFileName = 'SlicingTreeData.txt';

colors       = ['y','m','c','r','g','b'];
uniqueColor  = 'g';
colorsFlag   = 1;

% File
dataFile = fopen(dataFileName);
data = textscan(dataFile,'%f %f %f %f');
fclose(dataFile);

sizeinter = size(data{1}(:));
sizeData  = sizeinter(1,1);

xmax = 0;
ymax = 0;

for i=1:sizeData
    % Data Extraction
    x      = data{1}(i);
    y      = data{2}(i);
    width  = data{3}(i);
    height = data{4}(i);
    
    left   = x;
    right  = left + width;
    bottom = y;
    top    = bottom + height;
    
    x = [left left right right];
    y = [bottom top top bottom];
    
    % Plotting device
    if colorsFlag == 1
        colorSize = size(colors);
        fill(x, y, colors(mod(i,colorSize(1,2))+1))
    else
        fill(x, y, uniqueColor)
    end;
        
    strmin = ['\bf\fontsize{15}',num2str(i)];
    text(left+ width/2,bottom+ height/2,strmin,'HorizontalAlignment','center');
   
    
    % Process for the global window
    if right > xmax
        xmax = right;
    end;
    if top > ymax
        ymax = top;
    end;
end;

% Window view 
percent = 5;
xminus  = -xmax*percent/100;
yminus  = -ymax*percent/100;
xplus   =  xmax*percent/100 + xmax;
yplus   =  ymax*percent/100 + ymax;

axis([xminus xplus yminus yplus])
title ('Global Placement View')
xlabel('X axis') 
ylabel('Y axis') 
grid on;
