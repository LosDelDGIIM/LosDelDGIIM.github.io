package org;

import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;


public class Roman {

    private String valueInRoman;

    private static final Map<Integer, String> Map_DecimalToRoman = new LinkedHashMap<>();
    private static final Map<String, Integer> Map_RomanToDecimal = new LinkedHashMap<>();

    static {
        Map_DecimalToRoman.put(1000, "M");
        Map_DecimalToRoman.put(900,  "CM");
        Map_DecimalToRoman.put(500,  "D");
        Map_DecimalToRoman.put(400,  "CD");
        Map_DecimalToRoman.put(100,  "C");
        Map_DecimalToRoman.put(90,   "XC");
        Map_DecimalToRoman.put(50,   "L");
        Map_DecimalToRoman.put(40,   "XL");
        Map_DecimalToRoman.put(10,   "X");
        Map_DecimalToRoman.put(9,    "IX");
        Map_DecimalToRoman.put(5,    "V");
        Map_DecimalToRoman.put(4,    "IV");
        Map_DecimalToRoman.put(1,    "I");

        for (Map.Entry<Integer, String> entry : Map_DecimalToRoman.entrySet()) {
            Map_RomanToDecimal.put(entry.getValue(), entry.getKey());
        }
    }


    public void setValueFromDecimal(int dec){
        valueInRoman = "";
        for(int value : Map_DecimalToRoman.keySet()){
            while(dec >= value){
                valueInRoman += Map_DecimalToRoman.get(value);
                dec -= value;
            }
        }
    }

    public void setValueFromRoman(String valueInRoman){
        this.valueInRoman = valueInRoman;
    }

    public String getValueInRoman(){
        return valueInRoman;
    }

    public int getValueInDecimal(){
        int num = 0;
        int pre = 0;

        for(int i=valueInRoman.length()-1; i>=0; i--){
            String letter = String.valueOf(valueInRoman.charAt(i));
            int value = Map_RomanToDecimal.get(letter);

            if (value >= pre)
                num += value;
            else
                num -= value;

            pre = value;
        }

        return num;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Roman roman = new Roman();

        // --- Decimal a Romano ---
        System.out.println("Introduce enteros (finaliza con -1) para convertir a romano:");
        while (true) {
            System.out.print("Número: ");
            int dec = sc.nextInt();
            if (dec == -1) break;
            if (dec <= 0) {
                System.out.println("Introduce un número positivo.");
                continue;
            }
            roman.setValueFromDecimal(dec);
            System.out.println("Romano: " + roman.getValueInRoman());
        }

        sc.nextLine(); // limpiar buffer

        // --- Romano a Decimal ---
        System.out.println("\nIntroduce números romanos (finaliza con 'STOP') para convertir a decimal:");
        while (true) {
            System.out.print("Romano: ");
            String rom = sc.nextLine().toUpperCase();
            if (rom.equals("STOP")) break;
            try {
                roman.setValueFromRoman(rom);
                int dec = roman.getValueInDecimal();
                System.out.println("Decimal: " + dec);
            } catch (Exception e) {
                System.out.println("Número romano inválido.");
                System.out.println(e);
            }
        }

        sc.close();
        System.out.println("Programa finalizado.");
    }
}