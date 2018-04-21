/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stanleytranslator;
import java.util.regex.*;
import java.util.Vector;
/**
 *
 * @author Yann
 */
public class Transition {

    private String name;
    private Vector<String> pre;
    private Vector<String> post;
     private Vector<Place> pre_places;
    private Vector<Place> post_places;
    private Vector<Integer> n_pre;
    private Vector<Integer> n_post;
    private int priorite;

    private Vector<Condition> cond;
    private Vector<Action> actions;

    public  Transition(String name_,String pre_,String post_,Vector<Place> pre_places_,Vector<Place> post_places_)
    {

        name = name_;
        priorite = 1;

        pre = new Vector();
        post = new Vector();

        pre_places = pre_places_;
        post_places = post_places_;

        n_pre = new Vector();
        n_post = new Vector();

        cond = new Vector();
        actions = new Vector();
       
        Pattern p = Pattern.compile("([\\w\\{\\}-]+((\\x2A)(\\d)+){0,1}( ){0,1})*");
        Pattern psplit_space = Pattern.compile(" ");
        Pattern psplit = Pattern.compile("(\\x2A)");

        String b[] = new String[90];
        String a[] = new String[2];
        

        if(p.matcher(pre_).matches())
        {
            b = pre_.split(" ");
            for(int i = 0;i<b.length;i++)
            {
               a= psplit.split(b[i]);
                pre.add(a[0]);
                if(a.length>1)
                {
                    n_pre.add(new Integer(Integer.parseInt(a[1])));
                 }
                else
                {
                    n_pre.add(new Integer(1));;
                }
            }
            

        }
        else
        {

            pre.add("Incorrect Format");
            n_pre.add(new Integer(0));
      
        }

        if(p.matcher(post_).matches())
        {
           b = post_.split(" ");
            for(int i = 0;i<b.length;i++)
            {
               a= psplit.split(b[i]);
                post.add(a[0]);
                if(a.length>1)
                {
                    n_post.add(new Integer(Integer.parseInt(a[1])));
                 }
                else
                {
                    n_post.add(new Integer(1));;
                }
            }

        }
        else
        {

            post.add("Incorrect Format");
            n_post.add(new Integer(0));

        }
    }

    public String toString()
    {
        return name;
    }
    public String toFileString()
    {
        String s="tr:";
        for(int i =0;i<pre.size()-1;i++)
        {
            s=s+"p"+pre_places.get(i).getNum()+"*"+n_pre.get(i)+",";
        }
        s=s+"p"+pre_places.get(pre.size()-1).getNum()+"*"+n_pre.get(pre.size()-1)+";";
        if(cond.size()>0)
        {
            for(int i=0;i<cond.size()-1;i++)
            {
                s = s+cond.get(i).toFileString()+"/";
            }
            s = s+cond.get(cond.size()-1).toFileString()+";";
        }
        else
        {
            s=s+"6,0,6;";
        }

        for(int i =0;i<post.size()-1;i++)
        {
            s=s+"p"+post_places.get(i).getNum()+"*"+n_post.get(i)+",";
        }
        s=s+"p"+post_places.get(post.size()-1).getNum()+"*"+n_post.get(post.size()-1)+";";
        
        if(actions.size()>0)
        {
             for(int i=0;i<actions.size()-1;i++)
            {
                s = s+actions.get(i).toFileString()+"/";
            }
             s = s+actions.get(actions.size()-1).toFileString()+";";
         }
        else
        {
            s=s+"99,6;";
        }
         s = s+priorite;

        return s;
    }

  

    public String getName()
    {

        return name;
    }

    public void addCondition(Condition c)
    {
        cond.add(c);

    }

    public void addAction(Action a)
    {
        actions.add(a);
        
    }

    public void SetPriorite(int prio_)
    {
        
        priorite = prio_;
    }

    public int getPriorite()
    {
        return this.priorite;
    }
    public Vector<Condition> getConditions()
    {
        return cond;
    }

    public Vector<Action> getActions()
    {
        return actions;
    }

}
