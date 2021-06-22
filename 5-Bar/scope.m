clc;clear all;close all
com='com6';
try
s=connect(com);
catch
comfix  
s=connect(com);
end

figure('position',[50  200 700 400 ]);
N=100;
V1=zeros(1,N);
V2=V1;
v=nan;
t=0:N-1;

while 1
 pause(1e-6);
 flushinput(s);
 fprintf(s,'1'); 
 temp=fscanf(s);
 v=str2num(temp);
 v=v*5/1024;
 V1=[v,V1(1:N-1)];
plot(V1,'r')
ylabel('V')
xlabel('time')
axis([0,N+1,-.2,6])
grid on

end