s = serialport("COM6", 9600); 

% Enviar una posición al servo Dynamixel
for pos = 300:50:700
    writeline(s, num2str(pos));  % Envía el número como texto
    pause(500);  % Espera 500 segundo
end

clear s