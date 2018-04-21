/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stanleytranslator;
import java.util.*;
import javax.swing.*;
import java.lang.*;
import java.io.*;
import java.util.Vector;
import java.util.regex.*;
/**
 *
 * @author Yann
 */
public class Rdp {

    private Vector<Transition> trans;
    private Vector<Place> places;
    private Vector<Condition> cond;
    private Vector<Action> actions;
    private Vector<Integer> marquage;
    
    public Rdp()
    {
        cond = new Vector();
        actions = new Vector();
        trans = new Vector();
        places = new Vector();
        marquage = new Vector();
    }

    public int addPlace(String p)
    {
        boolean test = true;
        int ret = -1;
        for(int i=0;i<places.size();i++)
        {
            if(places.get(i).toString().compareTo(p) == 0)
            {
                test = false;
                ret=i;
                break;
            }
        }
        if(test)
        {
            places.add(new Place(p,places.size()+1));
            marquage.add(0);
        }
        return ret;
    }

    public void addTransition(Transition t)
    {
        trans.add(t);
    }

    public void addCondition(Condition c)
    {
        cond.add(c);
    
    }

    public void addAction(Action c)
    {
        actions.add(c);

    }

    static Rdp ReadRdpFile(String filepath)
    {

        Rdp net = new Rdp();
       

        try
        {
           BufferedReader f = new BufferedReader(new FileReader(filepath));
           while(f.ready())
           {
               String line = f.readLine();

                Pattern p = Pattern.compile("^tr.*");
                Pattern p2 = Pattern.compile("^pl.*");
                Pattern psplit = Pattern.compile(" ");
                if(p.matcher(line).matches())
                {
                   String a[] = new String[90];
                   a = psplit.split(line);
                   if(a.length>=6)
                   {
                        String t =a[3].replaceAll("(\\x2A)(\\d)+", "");
                        String pre = "";
                        
                        Vector<Place> pre_places = new Vector();
                        Vector<Place> post_places = new Vector();
                        int i= 3;
                        while(i<a.length && a[i].compareTo("->") !=0)
                        {
                            t =a[i].replaceAll("(\\x2A)(\\d)+","");
                            pre= pre+" "+a[i];
                            int ret = net.addPlace(t);
                            if(ret<0)
                            {
                                pre_places.add(net.places.lastElement());
                            }
                            else
                            {
                                pre_places.add(net.places.get(ret));
                            }
                            i++;
                        }
                        i++;
                        String post = "";
                        while(i<a.length)
                        {
                            t =a[i].replaceAll("(\\x2A)(\\d)+","");
                            post= post.trim()+" "+a[i];
                            int ret = net.addPlace(t);
                            if(ret<0)
                            {
                                post_places.add(net.places.lastElement());
                            }
                            else
                            {
                                post_places.add(net.places.get(ret));
                            }
                            i++;
                        }



                     


                        net.addTransition(new Transition(a[1],pre.trim(),post.trim(),pre_places,post_places));
                   
                   }


                }
                
                if(p2.matcher(line).matches())
                {
                    
                   String a[] = new String[10];
                   a = psplit.split(line);
                   if(a.length==3)
                   {
                        int i;
                        boolean test=false;
                        for(i=0;i<net.places.size();i++)
                        {
                            if(net.places.get(i).toString().compareTo(a[1])==0)
                            {
                                test=true;
                                break;
                            }
                        }
                        
                        if(test)
                        {
                            String t = a[2].replace("(", "");
                            t= t.replace(")", "");
                            
                            net.marquage.add(i,new Integer(Integer.parseInt(t)));
                            javax.swing.JOptionPane.showMessageDialog(null, "File successfully imported", "Info", javax.swing.JOptionPane.INFORMATION_MESSAGE);
                            return net;
                        }
                       
                             
                        
                        

                   }
                }

           }
           javax.swing.JOptionPane.showMessageDialog(null, "File not imported", "Error", javax.swing.JOptionPane.ERROR_MESSAGE);
           return null;
          
        }
        catch(FileNotFoundException e)
        {
           javax.swing.JOptionPane.showMessageDialog(null, "Unable to find file", "Error", javax.swing.JOptionPane.ERROR_MESSAGE);
        }
        catch(IOException e)
        {
           javax.swing.JOptionPane.showMessageDialog(null, "Unknown error", "Error", javax.swing.JOptionPane.ERROR_MESSAGE);
        }
        catch(java.lang.Exception e) {
            javax.swing.JOptionPane.showMessageDialog(null, "Unknown error", "Error", javax.swing.JOptionPane.ERROR_MESSAGE);
        }

        return net;

    }

    public Vector<Transition> getTransitions()
    {

        return trans;
    }

    public Vector<Action> getActions()
    {

        return actions;
    }

    public Vector<Condition> getConditions()
    {

        return cond;
    }

    public String toString()
    {
        String s="";
        s= places.size()+",";

        for(int i=0;i<places.size()-1;i++)
        {
            s=s+marquage.get(i)+",";
            System.out.println(marquage.get(i));
        }

        s=s+marquage.get(places.size()-1)+"\n";
        
        for(int i=0;i<trans.size();i++)
        {
            s= s+ trans.get(i).toFileString()+"\n";
            
        }

        return s;
    }

}
