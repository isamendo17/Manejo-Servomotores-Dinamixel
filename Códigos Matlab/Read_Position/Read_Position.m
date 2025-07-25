s = serialport("COM6", 9600);   % Ajusta el COM si es necesario
configureTerminator(s, "LF");

writeline(s, "leer");  % Solicita lectura continua al Arduino

tiempo_inicio = tic;
while toc(tiempo_inicio) < 5
    if s.NumBytesAvailable > 0
        respuesta = readline(s);

        if ischar(respuesta) || isstring(respuesta)
            if startsWith(respuesta, "POS_GRADOS:")
                valorTexto = extractAfter(respuesta, "POS_GRADOS:");
                angulo = str2double(valorTexto);
                fprintf("Posición actual del servo: %.2f grados\n", angulo);
            else
                warning("Respuesta inesperada: %s\n", respuesta);
            end
        else
            warning("Respuesta vacía o no válida");
        end
    end
end

