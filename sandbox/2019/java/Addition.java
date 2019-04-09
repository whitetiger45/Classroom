import javax.swing.JOptionPane;

public class Addition
{
    public static void main( String args[])
    {
        String firstN = JOptionPane.showInputDialog( "Enter first integer" );

        String secondN = JOptionPane.showInputDialog( "Enter second integer" );

        int n1 = Integer.parseInt( firstN ), n2 = Integer.parseInt( secondN );
        int sum = n1 + n2;

        JOptionPane.showMessageDialog(null, "The sum is" + sum, 
                                     "Sum of two integers", JOptionPane.PLAIN_MESSAGE );
    }
}