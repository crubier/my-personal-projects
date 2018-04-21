/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stanleytranslator;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;
/**
 *
 * @author Yann
 */
public class ConditionListModel extends AbstractListModel {

    Vector<Condition> cond;
            
    public ConditionListModel(Vector<Condition> cond_)
    {
        super();

    /*    this.addListDataListener(new ListDataListener() {

    public void contentsChanged(ListDataEvent e) {
            ConditionListModel mod = (ConditionListModel)e.getSource();
            mod.fireContentsChanged(e.getSource(), e.getIndex0(), e.getIndex1());
    }
    public void intervalAdded(ListDataEvent e) {
        ConditionListModel mod = (ConditionListModel)e.getSource();
            mod.fireIntervalAdded(e.getSource(), e.getIndex0(), e.getIndex1());
    }
    public void intervalRemoved(ListDataEvent e) {
        ConditionListModel mod = (ConditionListModel)e.getSource();
            mod.fireIntervalRemoved(e.getSource(), e.getIndex0(), e.getIndex1());

    }
} );*/

        cond =  cond_;
    }

    public void fireContentsChanged(Object s,int i0,int i1)
    {
        super.fireContentsChanged(s, i0, i1);
    }
    public Object getElementAt(int index)
    {
        return cond.get(index).toString();
    }

    public void removeAt(int i)
    {
        cond.remove(i);
    }

 public int getSize()
 {
     return cond.size();
 }


}
