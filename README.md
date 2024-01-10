# Shapes-Database
globals.h:
    The globals.h header file contains 2 string arrays containing restricted words used by the parser to check user inputs. 

Shape.h:
    The Shape.h header file contains the instantiation of class "Shape" including variables to hold information of the shape such as name, type, location, size, and rotaion as well as functions such as accessors and mutators to perform on shape type objects.

Shape.cpp:
    Shape.cpp implements the functions found in Shape.h to get, set, and display the shapes sttributes.

parser.cpp:
    parser.cpp is the main file of the program and handles the process of taking user input and error checking following a priority list. After recieving the user input the program will either dynamically allocate a shape type object into the "Shape" pointer array if the command is error free or display the highest priority error following a heirarchy. While parsing the input the program assigns an integer number pertaining to a specific error from 1-6. The error referred by the integer 1 has the highest priority while error 6 is the lowest. 

    1: The input had an invalid argument. (i.e., using non numerical inputs for integer expected inputs.)

    2: The inputs shape name is invalid. This is the case where the name of the shape is a restricted word. That is a word which is reserved for a command prompt or shape type. These words are all, maxshapes, create, move, rotate, draw, delete, circle, ellipse, rectangle, triangle.

    3: The inputs shape name already exists. This error only occurs when creating a new shape for the database. If a shape already in the database has the same name as the one being created the command will be flagged and will cause an error

    4: The inputs shape name does not exist. This error only occurs when the user attemps to delete or modify an existing shape within the database. In the case the shape trying to be modified or deleted does not exist in the database, the command will cause an error.

    5: The inputs has an invalid shape type. This error occurs only during the creation of a new shape in the database. If the shape type is not one of the listed in globals.h (circle, triangle, rectangle, ellipse), the command will cause an error 5.

    6: The inputs value is invalid. This error will occur from the create, move, and rotate commands. The cases that will cause this error are, dimensions of the shape contain a negative number, rotation value is <0 or >359 degrees, movement of the shape with a negative value, and different sizes for a circle type shape.

    7: The input contains too many arguments. This error occurs when the user input contains more arguments than listed in Command Formats examples.

    8: The input contains too few arguments. This error occurs when the user input contains less arguments than listed in Command Formats examples.

    9: Shape array is full. This error occurs when a new shape is being created while the current array is already full. 

Arguments Explanation:

    name: String without spaces
    
    type: One of the 4 shape types listed in globals

    loc: Positive integer 

    size: Positive integer

    value: Positive integer

    angle: Positive integer (1 - 359)

    all: Applies to all current shapes in database


Command Formats:
    
    maxShapes value

    create name type loc loc size size

    move name loc loc

    rotate name angle

    draw name/all

    delete name/all



    