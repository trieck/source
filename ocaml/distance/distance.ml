(* Compute distance between two points in a plane. *)
(* From Sedgewick 3.1 *)

type point = { x : float; y : float }

let distance a b =
	let dx = a.x -. b.x and
	dy = a.y -. b.y in
	sqrt (dx *. dx +. dy *. dy)
;;

let a = { x = 3.0; y = 4.0 }
let b = { x = 4.0; y = 5.0 };;

print_float (distance a b);;