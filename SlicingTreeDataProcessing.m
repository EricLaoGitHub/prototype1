clear;
close all;
figureTest = figure;

% Windows configuration
hFigure = 1000;
wFigure = 1500;
hScreen = 1200;
wScreen = 1920;
xFigure = wScreen/2 - wFigure/2;
yFigure = hScreen/2 - hFigure/2;
set(figureTest, 'OuterPosition', [xFigure, yFigure, wFigure, hFigure]);

% Parameters
dataFileName = 'SlicingTreeData.txt';

colors       = ['y','m','c','r','g','b'];
uniqueColor  = 'g';
colorsFlag   = 1;

% File

dataFile  = fopen(dataFileName);
data = textscan(dataFile,'%f %f %f %f %f' );
fclose(dataFile);

sizeinter = size(data{1}(:));
sizeData  = sizeinter(1,1);

xmax = 0;
ymax = 0;


subplot(1,2,1); 
hold on;
for i=1:sizeData
    % Data Extraction
    if data{5}(i) == 1
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

%figure(2);
dataFileName = 'SlicingTreeData2.txt';

dataFile = fopen(dataFileName);
data = textscan(dataFile,'%f %f');
fclose(dataFile);


sizeinter = size(data{1}(:));
sizeData  = sizeinter(1,1);

xmin = data{1}(1);
ymin = data{2}(1);
xmax = data{1}(1);
ymax = data{2}(1);

subplot(1,2,2);
hold on;
for i=1:sizeData
    plot(data{1}(i), data{2}(i), '+', 'MarkerSize', 10);
    if xmin > data{1}(i)
        xmin = data{1}(i);
    end;
    if xmax < data{1}(i)
        xmax = data{1}(i);
    end;
    if ymin > data{2}(i)
        ymin = data{2}(i);
    end;
    if ymax < data{2}(i)
        ymax = data{2}(i);
    end;
end

% Window view 
percent = 5;
xminus  = (xmin-xmax)*percent/100 + xmin;
yminus  = (ymin-ymax)*percent/100 + ymin;
xplus   = (xmax-xmin)*percent/100 + xmax;
yplus   = (ymax-ymin)*percent/100 + ymax;

axis([xminus xplus yminus yplus])
title ('Global Ratio')
xlabel('Width axis') 
ylabel('Height axis') 
grid on;

onplot = false;
if onplot 
    figure;
    x = [0.05, 0.11, 0.34, 1.34, 20.2, 167.9, 640.2];
    y = [147, 597, 1024, 1945, 4527, 13718, 27355];
    hold on;
    semilogx(x,y)
    title ('Running time vs Number of Objects')
    xlabel('Running time (seconds)') 
    ylabel('Number of Object') 
    grid on;
end;
