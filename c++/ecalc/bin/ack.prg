func ack() {
	if ($1 == 0) return $2 + 1; 
	if ($2 == 0) return ack($1 - 1, 1);
	return ack($1 - 1, ack($1, $2 - 1));
}

printf("%f", ack(3, 5));