(* List processing *)

(* From ocaml-3.07-refman *)
(* sort a list *)
let rec sort lst =
	match lst with
   	[] -> []
	| head::tail -> insert head (sort tail)
	
(* insert element into list *)
and insert elt lst =
	match lst with
   	[] -> [elt]
 	| head::tail -> 
 	if elt <= head then
   		elt::lst 
   	else
   		head::insert elt tail;;

(* print list of strings *)
let rec print_list = function
	[] -> []
 	| head::tail -> print_string head; 
   		print_string "\n"; 
   		print_list tail;;

let l = sort ["is"; "a"; "tale"; "told"; "etc."];;

print_list l;;
