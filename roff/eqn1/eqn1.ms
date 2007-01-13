.EQ
delim $$
.EN
.TL
Nondeterministic Finite Automata
.AU
Alfred V. Aho
Ravi Sethi
Jeffrey D. Ullman
.AB
A
.I nondeterministic
.I finite
.I automaton
(NFA, for short)
is a mathematical model that consists of:
.AE
.NH
a set of states \fI S
.NH
a set of input symbols $SIGMA$ (the \fIinput symbol alphabet)
.NH
a transition function \fImove\fP that maps state-symbol pairs to sets of states
.NH
a state $s sub 0$ that is distinguished as the \fIstart\fP (or \fIinitial\fP) \fIstate
.NH
a set of states \fIF\fP distinguished as \fIaccepting\fP (or \fIfinal\fP) \fIstates
.LP
An NFA can be represented diagrammatically by a labeled directed graph,
called a \fItransition graph\fP, in which the nodes are the states and
the labeled edges represent the transition function.
This graph looks like a transition diagram, but the same character can 
label two or more transitions out of one state, and edges can be labeled
by the special symbol $epsilon$ as well as by input symbols.
.PP
The transition graph for an NFA that recognizes the language
\fI(a|b)*abb\fP is shown in Fig. 3.19.
The set of states of the NFA is {0, 1, 2, 3} and the input
symbol alphabet is \fI{a, b}\fP.
State 0 in Fig. 3.19 is distinguished as the start
state, and the accepting state 3 is indicated by a double circle.
.PS
arrow "start" above
circle "0"
arrow "a" above
circle "1"
arrow "b" above
circle "2"
arrow "b" above
circle "3"
.PE
