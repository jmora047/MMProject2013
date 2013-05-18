
clear all;
close all;
y = zeros(5000);
s1 = serial('COM6');                            %define serial port
s1.BaudRate=115200;                               %define baud rate
    %'+-b'
%open serial port
fopen(s1);
clear data;
for i= 1:200                                %acquisition of 100 points
    data=fscanf(s1);%read sensor
    y(i) = str2double(data);

    plot(i,y(i))
    title('Aquisition Points');
    xlabel('Points');
    ylabel('Time');
    drawnow;
    hold on

    if y(i) > 10
        fprintf(s1, '1');
    end
    if y(i) < 10
        fprintf(s1, '0');
    end
    
    
end
% close the serial port
fclose(s1);  