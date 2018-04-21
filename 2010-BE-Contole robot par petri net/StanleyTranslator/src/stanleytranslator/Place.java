/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stanleytranslator;

/**
 *
 * @author Yann
 */
public class Place {

    private int num;
    private String name;


    public Place(String name_,int num_)
    {
        name = name_;
        num = num_;
    }

    public int getNum()
    {
        return num;

    }

    public String toString()
    {
        return name;
    }


}
