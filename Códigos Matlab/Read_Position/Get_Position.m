s = serialport("COM6", 9600);   
configureTerminator(s, "LF");

% Enviar comando para leer posición
writeline(s, 'P');
pause(0.1);  % Esperar respuesta

% Leer respuesta
respuesta = readline(s);

% Procesar respuesta si viene en formato 'POS_GRADOS:valor'
if startsWith(respuesta, "POS_GRADOS:")
    valorTexto = extractAfter(respuesta, "POS_GRADOS:");
    angulo = str2double(valorTexto);
    fprintf("Posición actual del servo: %.2f grados\n", angulo);
else
    warning("Respuesta inesperada: %s", respuesta);
end

clear s  % Cierra el puerto
