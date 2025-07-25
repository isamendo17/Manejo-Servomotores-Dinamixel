s = serialport("COM6", 9600);
configureTerminator(s, "LF");
pause(2);  

pause(0.5);  
for ang = 0:30:180
    cmd = sprintf("POS_GRADOS:%.2f", ang);
    writeline(s, cmd);
    fprintf("Enviado: %.f\n", ang);
    pause(1);  
end

clear s;
