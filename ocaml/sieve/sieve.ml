(* Sieve of Eratosthenes *)
let n = 1000
let a = Array.create n 1;;

a.(0) <- 0;;	(* not prime *)
a.(1) <- 0;;	(* not prime *)

let sieve = 
	for i = 2 to n - 1 do 		
		if a.(i) = 1 then
		begin
			let j = ref i in
			while (!j * i) < n do
				a.(i * !j) <- 0;
				j := !j + 1
			done
		end
	done;
	
	for i = 2 to n - 1 do 
		if a.(i) = 1 then
		begin
			print_string " ";
			print_int i
		end
	done
;;
