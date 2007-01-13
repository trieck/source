L = .01;
C = .042;
PI = 3.14159265;

frequency = 1 / ( 2 * PI * sqrt( L * C ) );

printf("Inductance:\t%f\n", L);
printf("Capacitance:\t%f\n", C);
printf("Frequency:\t%f\n", frequency);
