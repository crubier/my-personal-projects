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

public class ConditionTableModel extends AbstractTableModel {

    private Vector<Condition> cond;

    public ConditionTableModel(Vector<Condition> cond_)
    {
        super();
        cond = cond_;
    }

    public String getColumnName(int col)
    {
        if(col==0){
            return "Nom";
        }
        else if(col==1){
            return "Condition";
        }
        else if(col==2){
            return "Valeur";
        }
        else
            return "";
    }

    public int  getRowCount()
    {
        return cond.size();
    }

     public int getColumnCount()
    {
      return 3;
    }

     public Object getValueAt(int row, int column)
    {
      if(column==0)
      {
          return cond.get(row).getName();
      }
      else if(column == 1)
      {
          CapteurEnum capt =  cond.get(row).getCapt();
          String op = cond.get(row).getOp();
          if(capt==null)
          {

              return "Capteur US < (m)";
          }
          if(op.compareTo("<") == 0 && capt == CapteurEnum.ULTRASON)
          {
              return "Capteur US < (m)";
          }
          else if(op.compareTo(">") == 0 && capt == CapteurEnum.ULTRASON)
          {
              return "Capteur US > (m)";
          }
          else if(op.compareTo("<") == 0 && capt == CapteurEnum.SONORE)
          {
              return "Capteur Sonore < (dB)";
          }
          else if(op.compareTo(">") == 0 && capt == CapteurEnum.SONORE)
          {
              return "Capteur Sonore > (dB)";
          }
          else if(op.compareTo("<") == 0 && capt == CapteurEnum.PHOTOSENSIBLE)
          {
              return "Capteur PhotoSensible < (?)";
          }
          else if(op.compareTo(">") == 0 && capt == CapteurEnum.PHOTOSENSIBLE)
          {
              return "Capteur PhotoSensible > (?)";
          }
          else if( capt == CapteurEnum.TACTILE)
          {
              return "Capteur Tactile = (bool)";
          }
          else
          {
              return "Capteur Tactile = (bool)";
          }

      }
      else
      {
          return cond.get(row).getVal();
      }
    }

      public void setValueAt(Object value, int row, int col)
     {

        if(col == 0)
        {
            cond.get(row).setName((String)value);
        }
        else if(col == 1)
        {
             if( value.equals(0))
             {
                 cond.get(row).setCapt(CapteurEnum.ULTRASON);
                 cond.get(row).setOp("<");
             }
             else if(value.equals(1))
             {
                 cond.get(row).setCapt(CapteurEnum.ULTRASON);
                 cond.get(row).setOp(">");
             }
             else if(value.equals(2))
             {
                 cond.get(row).setCapt(CapteurEnum.SONORE);
                 cond.get(row).setOp("<");
             }
             else if(value.equals(3))
             {
                 cond.get(row).setCapt(CapteurEnum.SONORE);
                 cond.get(row).setOp(">");
             }
             else if(value.equals(4))
             {
                 cond.get(row).setCapt(CapteurEnum.PHOTOSENSIBLE);
                 cond.get(row).setOp("<");
             }
             else if(value.equals(5))
             {
                 cond.get(row).setCapt(CapteurEnum.PHOTOSENSIBLE);
                 cond.get(row).setOp(">");
             }
             else if(value.equals(6))
             {
                 cond.get(row).setCapt(CapteurEnum.TACTILE);
                 cond.get(row).setOp("");
             }
             else
             {
                 cond.get(row).setCapt(CapteurEnum.ULTRASON);
                 cond.get(row).setOp("<");
             }
        }
        else
        {
            cond.get(row).setVal(String.valueOf(value));
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
             return Integer.class;
         }
         else
         {
             return Integer.class;
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
