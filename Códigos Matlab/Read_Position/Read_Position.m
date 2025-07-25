s = serialport("COM6", 9600);   % Ajusta el COM si es necesario
configureTerminator(s, "LF");

writeline(s, "leer");  % Solicita lectura continua al Arduino

tiempo_inicio = tic;
while toc(tiempo_inicio) < 5
    if s.NumBytesAvailable > 0
        respuesta = readline(s);

        if ischar(respuesta) || isstring(respuesta)
            if startsWith(respuesta, "POS_GRADOS:")
                % Extrae ángulo y velocidad si están en la misma línea
                tokens = regexp(respuesta, "POS_GRADOS:([\d\.]+),VEL:([\d\.\-]+)", 'tokens');
                if ~isempty(tokens)
                    valores = str2double(tokens{1});
                    angulo = valores(1);
                    velocidad = valores(2);
                    fprintf("Ángulo: %.2f grados | Velocidad: %.2f ticks/s\n", angulo, velocidad);
                else
                    % Si solo viene el ángulo sin velocidad
                    valorTexto = extractAfter(respuesta, "POS_GRADOS:");
                    angulo = str2double(valorTexto);
                    fprintf("Ángulo: %.2f grados (sin velocidad)\n", angulo);
                end
            else
                warning("Respuesta inesperada: %s\n", respuesta);
            end
        else
            warning("Respuesta vacía o no válida");
        end
    end
end