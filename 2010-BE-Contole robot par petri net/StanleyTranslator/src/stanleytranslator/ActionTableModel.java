/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stanleytranslator;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;

/**
 *
 * @author Yann
 */

public class ActionTableModel extends AbstractTableModel {

    private Vector<Action> act;

    public ActionTableModel(Vector<Action> act_)
    {
        super();
        act = act_;
    }

    public String getColumnName(int col)
    {
        if(col==0){
            return "Nom";
        }
        else if(col==1){
            return "Action";
        }
        else if(col==2){
            return "Valeur";
        }
        else
            return "";
    }

    public int  getRowCount()
    {
        return act.size();
    }

     public int getColumnCount()
    {
      return 3;
    }

     public Object getValueAt(int row, int column)
    {
      if(column==0)
      {
          return act.get(row).getName();
      }
      else if(column == 1)
      {

          String op = act.get(row).getActionPrim();
          return op;

      }
      else
      {
          return act.get(row).getArgPrim();
      }
    }

      public void setValueAt(Object value, int row, int col)
     {

        if(col == 0)
        {
            act.get(row).setName((String)value);
        }
        else if(col == 1)
        {
             //act.get(row).setActionPrim(ActionEnum.STOP);
            //act.get(row).setActionPrim();

             if( value.equals(0))
             {
                 act.get(row).setActionPrim(ActionEnum.AVANCER);
             }
             else if(value.equals(1))
             {
                 act.get(row).setActionPrim(ActionEnum.RECULER);
             }
             else if(value.equals(2))
             {
                 act.get(row).setActionPrim(ActionEnum.TOURNER_GAUCHE);
             }
             else if(value.equals(3))
             {
                 act.get(row).setActionPrim(ActionEnum.TOURNER_DROITE);
             }
             else if(value.equals(4))
             {
                 act.get(row).setActionPrim(ActionEnum.OUVRIR_PINCE);
             }
             else if(value.equals(5))
             {
                 act.get(row).setActionPrim(ActionEnum.FERMER_PINCE);
             }
             else //if(value.equals(6))
             {
                 act.get(row).setActionPrim(ActionEnum.STOP);
             }


           

        }
        else
        {
            act.get(row).setArgPrim((String)value);
        }


        fireTableCellUpdated(row, col);
    }

      public Class getColumnClass(int c) {
         if(c == 0)
         {
             return String.class;
         }
         else if(c==1)
         {
             return String.class;
         }
         else
         {
             return String.class;
         }
    }

      @Override public boolean isCellEditable(int row, int col) {
             return true;
         }


/*
JComboBox comboBox1 = new JComboBox();
comboBox1.addItem("Capteur US < (m)");
comboBox1.addItem("Capteur US > (m)");
comboBox1.addItem("Capteur Sonore < (dB)");
comboBox1.addItem("Capteur Sonore > (dB)");
comboBox1.addItem("Capteur PhotoSensible < (?)");
comboBox1.addItem("Capteur PhotoSensible > (?)");
comboBox1.addItem("Capteur Tactile = (bool)");



jTable1.getColumnModel().getColumn(1).setCellEditor(new DefaultCellEditor(comboBox1));
*/
}
