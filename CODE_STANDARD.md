# DIT168 - GP13

This Project will follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## The most important rules are listed bellow:

**1. Header File:** In general, every .cc file should have an associated .h file. There are some common exceptions, such as unittests and small .cc files containing just a main() function.

**2. General Naming Rules:** Give as descriptive a name as possible, within reason. Do not worry about saving horizontal space as it is far more important to make your code immediately understandable by a new reader, avoid abbreviation. The names of variables (including function parameters) and data members are all lowercase, with underscores between words. Data members of classes (but not structs) additionally have trailing underscores. For instance: a_local_variable, a_struct_data_member, a_class_data_member_.

**3. Class formatting:** The public:, protected:, and private: keywords should be indented one space. These sections should be present on the class in the respective order. Do not leave a blank line after these keywords.

**4. Line lenght:** Each line of text in your code should be at most 80 characters long.

**5. Spaces/Tabs:** Use only spaces, and indent 2 spaces at a time. Do not use tabs in your code.

**6. Conditionals:** Prefer no spaces inside parentheses. The if and else keywords belong on separate lines.

**7. Pointer/Reference Expresion:** No spaces around period or arrow. Pointer operators do not have trailing spaces.
```
x = *p; 
p = &x; 
x = r.y; 
x = r->y;
```

**8. Boolean expression:** When you have one that is longer than line lengt defined above, be consistent in how you break up the lines.

**9. Return expression:** Use parentheses in return only where you would use them as for example: return (x & expr).

**10. Comments:** They should be as readable as narrative text, with proper capitalization and punctuation. In many cases, complete sentences are more readable than sentence fragments. Shorter comments, such as comments at the end of a line of code, can sometimes be less formal, but you should be consistent with your style. Use either the // or /* */ syntax, as long as you are consistent. Be consistent with how you comment and what style you use where, try to follow the document style if already created.

**11. TODO Comments:** Use TODO comments for code that is temporary, a short-term solution, or good-enough but not perfect. TODOs should include the string TODO in all caps, followed by the name, e-mail address, bug ID, or other identifier of the person or issue with the best context about the problem referenced by the TODO. 

**12. Grammar:** Pay attention to punctuation, spelling, and grammar; it is easier to read well-written comments than badly written ones.

NOTE: This list can change if the authors find it necessary, please keep an eye on this documentation if you want to contribuite to this project.
