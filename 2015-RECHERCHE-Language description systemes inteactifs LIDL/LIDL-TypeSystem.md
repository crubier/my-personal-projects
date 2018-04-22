# Interactions generated automatically from data types

Definitions of LIDL data types should create some interactions automatically. For example, consider the following data type:

```
data
  Toto
is
  (bob (x: Number) (y: Number)) | (joe)
```

The data type should generate the following interactions (never mind the polymorphism):

  - **Constructor**
    - To create instances of the data type
    - `interface Constructor<T> is T out`
    - Example
      - `(bob (x: Number in) (y: Number in)): Constructor<Toto>`: Create a fully defined bob
      - `(bob (x: Number in)): Constructor<Toto>`: Create a bob with inactive y
      - `(bob (y: Number in)): Constructor<Toto>`: Create a bob with inactive x
      - `(bob): Constructor<Toto>`: Create a bob with inactive x and y (but bob is active)
      - `(joe): Constructor<Toto>`: Create a joe
      - `(inactive)`: Create nothing
    - Use
      - `(bob (4) (2))`: Creates a fully defined bob
      - `(joe)`: Creates a fully defined joe
      - `(bob (inactive) (2))`
      - `(inactive)`
  - **Destructor**
    - To extract info from instances of the data type:
    - `interface Destructor<T> is T in`
    - Example
      - `(bob (x: Number out) (y: Number out)): Destructor<Toto>`: Extract x and y from a bob
      - `(bob (x: Number out)): Destructor<Toto>`: Extract x from a bob
      - `(bob (y: Number out)): Destructor<Toto>`: Extract y from a bob
      - `(bob): Destructor<Toto>`: Extract nothing from a bob
      - `(joe): Destructor<Toto>`: Extract nothing from a joe
      - `()`: Extract nothing
    - Use
      - `(bob (a) ())` Sends the x of the incoming bob to interaction a
      - `(bob (a) (b))` Sends the x of the incoming bob to interaction a, and the y to interaction b
  - **Matcher**
    - To match instances of the data type against composable patterns. used in switch interactions
    - `interface Matcher<T> is {value: T in, matched: Activation out}`
    - Example
      - `(bob (x: -Matcher<Number>) (y: -Matcher<Number>)): Matcher<Toto>`: Match a bob if both x and y match using sub matchers
      - `(bob (x: -Matcher<Number>)): Matcher<Toto>`: Match a bob if x  matches using a sub matcher and y is inactive
      - `(bob (y: -Matcher<Number>)): Matcher<Toto>`: Match a bob if x  matches using a sub matcher and x is inactive
      - `(bob): Matcher<Toto>`: Match a bob if both x and y are inactive
      - `(joe): Matcher<Toto>`: Match a joe
      - `(is (a:Toto in)):Matcher<Toto>`: Matches only if element is equal to a
      - `(to (a:Toto out)):Matcher<Toto>`: Matches everything and sends element to a
    - Use
      - `(bob (is (5)) (is (4)) )`: Matches only `(bob (5) (4))`
      - `(is (bob (5) (4)))`: Same as above, matches only `(bob (5) (4))`
      - `(bob (is(5)) (to(a)))`: Matches all bob whose x is 5, and sends their y to the interaction a
      - `(joe)`: Matches if is the tested value is a joe.
      - `(to (a))`: Matches everything and send value to a.
  - **Mutator**
    - To easily specify mutations of instances of the data type
    - `interface Mutator<T> is {get: T in, set: T out}`
    - Example
      - `(bob (x: -Mutator<Number>) (y: -Mutator<Number>)): Mutator<Toto>`: Mutate both x and y of a bob according to their mutator. If we have a joe, do not mutate it
      - `(joe): Mutator<Toto>`: Mutate a joe, except there is nothin to change really..
      - `(force (a:Toto in)): Mutator<Toto>`: Forces the output to be equal to a, whatever the input
      - `(identity (a:Toto out)): Mutator<Toto>`: Does not mutate anything, the output is equal to the input
    - Use
      - `(bob (identity()) (force(4)))`: Changes the y of a bob to 4, if the incoming toto is a joe then do nothing
      - `(bob (force(inactive)) (identity()))`: Removes the x of incoming bob, does nothing to a joe
      - `(bob (identity(a)) (force(a))))`: Changes the y of incoming bob to their x, so they have equal x and y after the mutation. Does nothing to joe
      - `(force (joe))`: Changes any incoming toto to joe
