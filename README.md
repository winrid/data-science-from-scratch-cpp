# data-science-from-scratch-cpp
The exercises from the book "Data Science from Scratch" - but in C++17 instead of Python.

### Why would you hurt yourself this way?

C++ isn't going away anytime soon. While I'd pick Rust for most new projects,
knowing C++ is a useful tool for diving into all different kinds of existing systems. Also, "Modern C++" is pretty
easy to work with.

### Can I use this as a library?

If you like to live on the edge you sure can, however I haven't written any unit tests. I'm just following the book, so I enter their testing data and see
that the results match. If anyone wants to add tests and make this "useful" - create a PR!

#### Findings

I haven't really found anything astonishing, other than if I were to do data science I'd probably use C++. Python has some
really cool stuff for working with numbers, but C++ is not much harder to write for this kind of thing (can just let the OS clean up the memory at the end in most use cases, or use RAII).

Basic arguments for static typing. For example, reading the book it's very hard to tell if a function is taking an int or a float. It's just so easy to type "int" - why not do it?
