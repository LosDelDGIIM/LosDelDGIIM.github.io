package RLE_Encoding;
import java.util.Scanner;

/**
 * RLE Encoding - Erasmus DUE Software Craftmanship Course
 * @author Arturo Olivares Martos
 * 
 * Programm that encodes a word using Run Length Encoding (RLE) technique.
 * The encoding format is (count)character, where count is the number of
 * consecutive occurrences of the character.
 */


public class RLE_Encoding {

    /**
     * Function to RLE_Encode a Word
     * @param input Word to encode
     * @return RLE_Encoded_Word that represents the encoded word
     */
    public static RLE_Encoded_Word RLE_Encode(String input){
        RLE_Encoded_Word result = new RLE_Encoded_Word();

        if (input != null && !input.isEmpty()){
            char previousChar = input.charAt(0);
            int numberOfConsecutives = 1;   // Number of consecutive times the same letter appears

            for (int i = 1; i < input.length(); i++){
                char currentChar = input.charAt(i);
                if (previousChar == currentChar)
                    numberOfConsecutives++;
                else {
                    // Annotate the change of letter
                    result.appendRun(numberOfConsecutives, previousChar);

                    // Prepare for the next letter
                    previousChar = currentChar;
                    numberOfConsecutives = 1;
                }

            } // End-For letters


            // Annotate the last character
            result.appendRun(numberOfConsecutives, previousChar);
        }

        return result;
    }

    public static void main(String[] args) {

        System.out.println("Enter a word to RLE Encode: ");
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();

        String output  = RLE_Encode(input).toString();

        System.out.println("- Input: " +  input);
        System.out.println("- Output: " +  output);

    }
}