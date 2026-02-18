# Notes on the compilation

- It is assumed that the use of <code>stop</code> values (interpreted as *no data transmitted* in the instanciation of the model in the real world) is forbidden as the *target object* output expressions (the <code> -> @(...)</code> statements) of a collective function (*spread* or *collect*).

- Since not transmitting data to a component in our synchronous models results in deadlocks, and Chips doesn't yet allow to specify behaviors of components when no data is received, the current model represents the absence of data exchanged with the Users computers as the transmission of 0 values.

- Hence, for *spread* operations, in case of <code>stop</code> value accumulated variable received, there is still a need to compute a value for the current component. In such cases, for each variable supposedly contained by the accumulator, the default value associated is:
    - the one specified by the default accumulator in the definition of the spread function if it is not an <code>input</code> containing expression,
    - <code>0</code> if the default value is an int <code>input</code> value,
    - <code>0.0</code> if the default value is a float <code>input</code> value,
    - or <code>false</code> if the default value is a bool <code>input</code> value.
In case of arrays instead of atomic variables of a given type, the arrays are of same dimension and are filled with the default values of their type.

- The problem raised by the previous item doesn't apply to the *collect* functions because the default accumulator value is supposedly already known by each component : transmitting a <code>stop</code> is equivalent to transmitting the default accumulator of the definition of the function.