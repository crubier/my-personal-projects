/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stanleytranslator;

/**
 *
 * @author Yann
 */
public class Condition {

    private String name;
private CapteurEnum capt;
private String op;
private String val;

    public Condition(String name_)
    {
        name = name_;
        op = "";
        val = "";
        capt = CapteurEnum.ULTRASON;
    }

    public void SetCondition(CapteurEnum capt_,String op_,String val_)
    {
            capt = capt_;
            op = op_;
            val = val_;
    }

    public void setName(String name_)
    {
        name = name_;
    }

    public void setVal(String val_)
    {
        val = val_;
    }

    public void setOp(String op_)
    {
        op = op_;
    }

    public void setCapt(CapteurEnum capt_)
    {
        capt = capt_;
    }

    public String getName()
    {
        return name;
    }

    public CapteurEnum getCapt()
    {
        return capt;
    }

    public String getVal()
    {
        return val;
    }

    public String getOp()
    {
        return op;
    }

    public String toString()
    {
        return name;
    }

    public String toFileString()
    {
        String s;

        s = String.valueOf(capt.ordinal())+",";

        if(op.compareTo("<")==0 )
        {
            s=s+"1,";
        }
        else if(op.compareTo(">")==0 )
        {
            s=s+"2,";
        }
        else if(op.compareTo(">=")==0)
        {
            s=s+"3,";
        }
        else
        {
            s=s+"0,";
        }

        s=s+val;
        return s;

    }



}
