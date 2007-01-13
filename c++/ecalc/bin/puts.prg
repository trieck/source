
proc putc()
{
	printf("%c", $1);
}

proc puts()
{
	char=$1;
	last=char+$2;

	while (char < last) {
		putc(char);
		char = char + 1;
	}
}

puts(97, 26);
printf("\n");
puts(65, 26);
printf("\n");
puts(32, 94);