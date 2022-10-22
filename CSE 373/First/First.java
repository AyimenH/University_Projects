// Ayimen H Sep. 30, 2022
public class First {
    public static void main(String[] args) {
        /*
         * public means the code within {} can be accessed in other classes like test()
         * static allows main() to be called because main doesn't have an object
         * void is a type of output from the class, void means it outputs nothing
         * main() is the primary class
         */

        int myInt = 33; // int is a type, myInt is the variable, and is assigned to 8
        double shoeSize = 10; // int & double are functionally the same primitive type
        char myInitial = 'A'; // char is for charecters like letters
        String myName = "Ayimen"; // String is a type that is used for words, it must also be in double quotation
                                  // marks
        String myJersey = printJersey("Ayimen", 8);

        test(); // methods have to be used in the main class in order to have an output

        double result = myInt + shoeSize;

        System.out.println(myInt * shoeSize); // System.out.println() is how to recieve output
        System.out.println("My name is " + myName + " and my initial is " + myInitial); // + allows me to put differnt
                                                                                        // types in the same output
        System.out.println("My US Shoe size in European sizing is " + result);
    }

    private static void test() { // test is a method, which is a user created type, a method always () next to it
        System.out.println("Testing");
    }

    private static String printJersey(String name, int number) {
        return "My Jersey is " + myJersey;
    }
}
