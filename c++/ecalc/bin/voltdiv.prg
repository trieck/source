r1 = 1200;
r2 = 2200;
vin = 9.00;

vout = r2 / (r1 + r2) * vin;

printf("Resistor1 = %f\n", r1);
printf("Resistor2 = %f\n", r2);
printf("VoltageIn = %f\n", vin);
printf("VoltageOut = %f\n", vout);
