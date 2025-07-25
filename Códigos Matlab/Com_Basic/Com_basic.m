try
    s = serialport("COM6", 57600);   % Abre el puerto
    configureTerminator(s, "LF");    
    pause(0.5);                      

    writeline(s, 'H');              
    pause(0.1);                   
    response = readline(s);        

    disp("Respuesta desde OpenRB:");
    disp(response);

    clear s                          % Cierra el puerto 
catch e
    warning("Error en la comunicación serial:");
    disp(e.message)
end
