/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stanleytranslator;
import java.util.*;

/**
 *
 * @author Yann
 */


public class Action {

    private String name;
    private ActionEnum actions_prim;
    private String arg_prim;
   

    public Action(String name_,ActionEnum act, String arg )
    {

        name = name_;
        actions_prim = act;
        arg_prim = arg;

    }


    public String getName()
    {
        return name;
    }


    public String getActionPrim()
    {
        return actions_prim.toString();
    }

      public String getArgPrim()
    {
        return arg_prim;
    }

      public void setActionPrim(ActionEnum act_)
      {
          this.actions_prim = act_;

      }

      public void setArgPrim(String arg_)
      {
          this.arg_prim= arg_;
      }

    public void setName(String name_)
    {
        name = name_;
    }

    public String toString()
    {
        return name;
    }

    public String toFileString()
    {
        String s ;

            s = actions_prim.ordinal()+","+arg_prim;
        return s;
    }

}
