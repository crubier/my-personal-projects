/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stanleytranslator;
import javax.swing.*;
import java.util.*;
/**
 *
 * @author Yann
 */
public class ActionListModel extends AbstractListModel {

    Vector<Action> act;

    public ActionListModel(Vector<Action> act_)
    {
        super();
        act =  act_;
    }

    public void fireContentsChanged(Object s,int i0,int i1)
    {
        super.fireContentsChanged(s, i0, i1);
    }
    public Object getElementAt(int index)
    {
        return act.get(index).toString();
    }

 public int getSize()
 {
     return act.size();
 }

  public void removeAt(int i)
    {
        act.remove(i);
    }


}
