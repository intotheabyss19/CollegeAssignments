/*1. Financial Data Analysis
As a data analyst at a financial firm, you've been given a dataset that contains the daily
closing prices of a company's stock over the past year. Your task is to write a Java program to
calculate the total sum and average closing price. The company's CEO wants to use this
information to analyze the company's financial performance over the year. Can you
accurately compute the required metrics to aid in their decision-making?
*/

import java.util.Arrays;
import java.util.Random;

public class q1_FinancialDataAnalysis {
    public static void main(String[] args) {
        SampleList slist = new SampleList();
        int [] list = slist.getList();
        MetricCalc calc = new MetricCalc();
        System.out.print("List of closing prices: ");
        System.out.println(Arrays.toString(list));
        System.out.println("Total sum: " + calc.getSum(list));
        System.out.println("Average closing price: " + calc.getAvg(list));
    }        
}

class SampleList{
    Random rand = new Random();
    int[] list = new int[10];
    SampleList() {
        for(int i = 0; i < 10; i++) {
            list[i] = 500000 + rand.nextInt(20000);
        }
    }
    int [] getList() {
        return list;
    }
}

class MetricCalc {
    int sum, avg, closing_price;
    int getSum (int [] list) {
        for (int i = 0; i < list.length; i++) {
            sum += list[i];
        }
        return sum;
    }
    double getAvg (int [] list) {
        return (double)getSum(list) / list.length;
    }
}