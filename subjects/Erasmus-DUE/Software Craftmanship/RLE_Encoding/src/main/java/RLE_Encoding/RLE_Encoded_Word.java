package RLE_Encoding;

/**
 * RLE Encoding - Erasmus DUE Software Craftmanship Course
 * @author Arturo Olivares Martos
 */

/**
 * Functional Class that represents a RLE Encoded Word
 */
public class RLE_Encoded_Word {
    static char PRE_SEPARATOR = '(';        // Character that separates the count from the character
    static char POST_SEPARATOR = ')';       // Character that separates the character from the next count

    private String value;

    public RLE_Encoded_Word() {
        this.value = "";
    }

    public RLE_Encoded_Word(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    /**
     * Function that appends a Run to a RLE_Encoded_Word
     * @param count Number of times that the character appears consecutively
     * @param c Character to add
     */
    public void appendRun(int count, char c) {
        value += PRE_SEPARATOR + String.valueOf(count) + POST_SEPARATOR + c;
    }



    @Override
    public String toString() {
        return value;
    }
}
