interface
  Mutator<X>
is
  {
    get: X in,
    set: X out,
  }

interaction
  (mutator (a:X out) (b:X in)): Mutator<X>
is
  ({ get:(a) set:(b) })

interaction
  (mutation (a:X in) (b:X out)): -Mutator<X>
is
  ({ get:(a) set:(b) })

interaction
  (mutate (a: X in) to (b: X out) by (c: -Mutator<X>)):Behaviour
is
  ((mutation (a) (b) }) = (c))

interaction
  (get(x: -Mutator<X>)): X in
is
  ((x).get)

interaction
  (set(x: -Mutator<X>)): X in
is
  ((x).set)

interaction
  (element 2 (x: Mutator<Alarm>)): Mutator<Model>
is
  ( mutator
    ([ (a) (b) (get(x)) (d) ])
    ([ (a) (b) (set(x)) (d) ])
  )

interaction
  (elemnt)
