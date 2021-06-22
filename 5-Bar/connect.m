function ser=connect(port)

% port = 'COM3';%Edit to your com port number
ser = serial(port);
set(ser, 'InputBufferSize', 2048);
set(ser, 'BaudRate', 2000000);
set(ser, 'DataBits', 8);
set(ser, 'Parity', 'none');
set(ser, 'StopBits', 1)
% s.ser=ser;
% fopen(s.ser);
fopen(ser);

end