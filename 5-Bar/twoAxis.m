%clc;clear all;close all
com='com3';
%try to connect arduino
% try
%s=connect(com);
% catchco
% %comfix  
%s=connect(com);
% end

pause(2)


r=30;
k = 1; 
for tet=0:0.1:2*pi
    x=r*cos(tet)+90;
    y=r*sin(tet)+130;
    plot(x,y,'*')
    
    %fprintf(s,[num2str(x),' ']);
    %fprintf(s,[num2str(y),' ']);
    pause(0.2)
    
    %teta = fscanf(s);
    %teta = str2num(teta)
    %teta_d = fscanf(s);
    %teta_d = str2num(teta_d)
    %plot(teta, teta_d,'*')
    hold on
    
    %TETA(k)=teta;
    %TETA_D(k)=teta_d;
    %err(k)=(teta_d-teta);
    k=k+1;
    %temp1=fscanf(s);
    %temp1=str2num(temp1)*180/pi
    %temp2=fscanf(s);
    %temp2=str2num(temp2)*180/pi
end
%xlabel('teta') 
%ylabel('teta d') 
% for x = 60:100
%     y = x
%    
%     temp1=fscanf(s);
%     temp1=str2num(temp1)*180/pi
%     temp2=fscanf(s);
%     temp2=str2num(temp2)*180/pi
% end

%comfix
%plot(x, y);



%fprintf(s,x); 
