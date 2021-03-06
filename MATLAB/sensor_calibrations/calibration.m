% Thermistor
% Room: 2.45 V -> 0.96 R
% Outside: 1.78 V -> 0.5527 R
% 
% Pressure
% Room: 3.91
% Outside: 3.91
% 
% Humidity
% Room: 0.92
% Outside: 3.32

thermis_voltage = [2.45 1.78];
temperature = [293.83 277];
B = log(0.96/0.5527)/(1.0/temperature(1) + 1.0/temperature(2));
R = 0.96 * 2.718^(-B/293.83);


pressure_voltage = [0 1];
pressure = [0 3.91];
pressure_slope = 7.928;
pressure_intercept = 0;

humidity_voltage = [0.92 3.32];
humidity = [32 92.4];
humidity_slope = 2.866;
humidity_intercept = 92.4 - humidity_slope*3.32;



