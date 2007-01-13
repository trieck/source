R=0.25;
N=17;
l=7.35;

printf( "radius of coil in inches:\t%f\n", R );
printf( "number of turns:\t\t%f\n", N );
printf( "length of coil in inches:\t%f\n", l );

L = ( pow(R, 2) * pow(N, 2) ) / ( ( 9 * R ) + ( 10 * l ) );

printf( "inductance in microhenries:\t%f\n", L );