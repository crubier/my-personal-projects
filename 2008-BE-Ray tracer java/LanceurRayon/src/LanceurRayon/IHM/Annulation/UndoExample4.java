package LanceurRayon.IHM.Annulation;


/*
Core SWING Advanced Programming 
By Kim Topley
ISBN: 0 13 083292 8       
Publisher: Prentice Hall  
*/


import java.awt.BorderLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.KeyStroke;
import javax.swing.UIManager;
import javax.swing.event.UndoableEditListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;
import javax.swing.undo.AbstractUndoableEdit;
import javax.swing.undo.CannotRedoException;
import javax.swing.undo.CannotUndoException;
import javax.swing.undo.UndoManager;
import javax.swing.undo.UndoableEditSupport;


public class UndoExample4 extends JFrame {
  public UndoExample4() {
    super("Undo/Redo Example 4");

    DefaultMutableTreeNode rootNode = new DefaultMutableTreeNode("root");
    DefaultMutableTreeNode node = new DefaultMutableTreeNode("Apollo 8");
    rootNode.add(node);
    node.add(new DefaultMutableTreeNode("Borman"));
    node.add(new DefaultMutableTreeNode("Lovell"));
    node.add(new DefaultMutableTreeNode("Anders"));

    node = new DefaultMutableTreeNode("Apollo 11");
    rootNode.add(node);
    node.add(new DefaultMutableTreeNode("Armstrong"));
    node.add(new DefaultMutableTreeNode("Aldrin"));
    node.add(new DefaultMutableTreeNode("Collins"));

    node = new DefaultMutableTreeNode("Apollo 12");
    rootNode.add(node);
    node.add(new DefaultMutableTreeNode("Conrad"));
    node.add(new DefaultMutableTreeNode("Gordon"));
    node.add(new DefaultMutableTreeNode("Bean"));

    UndoableTree2 tree = new UndoableTree2(rootNode);

    getContentPane().add(new JScrollPane(tree), BorderLayout.CENTER);

    // Create the undo manager and actions
    UndoManager manager = new UndoManager();
    tree.addUndoableEditListener(manager);

    Action undoAction = new UndoAction(manager);
    Action redoAction = new RedoAction(manager);

    // Add the actions to buttons
    JPanel panel = new JPanel();
    JButton undoButton = new JButton("Undo");
    JButton redoButton = new JButton("Redo");
    undoButton.addActionListener(undoAction);
    redoButton.addActionListener(redoAction);
    panel.add(undoButton);
    panel.add(redoButton);
    getContentPane().add(panel, BorderLayout.SOUTH);

    // Assign the actions to keys
    ((JComponent) getContentPane()).registerKeyboardAction(undoAction,
        KeyStroke.getKeyStroke(KeyEvent.VK_Z, InputEvent.CTRL_MASK),
        JComponent.WHEN_IN_FOCUSED_WINDOW);
    ((JComponent) getContentPane()).registerKeyboardAction(redoAction,
        KeyStroke.getKeyStroke(KeyEvent.VK_Y, InputEvent.CTRL_MASK),
        JComponent.WHEN_IN_FOCUSED_WINDOW);
  }

  // The Undo action
  public class UndoAction extends AbstractAction {
    public UndoAction(UndoManager manager) {
      this.manager = manager;
    }

    public void actionPerformed(ActionEvent evt) {
      try {
        manager.undo();
      } catch (CannotUndoException e) {
        Toolkit.getDefaultToolkit().beep();
      }
    }

    private UndoManager manager;
  }

  // The Redo action
  public class RedoAction extends AbstractAction {
    public RedoAction(UndoManager manager) {
      this.manager = manager;
    }

    public void actionPerformed(ActionEvent evt) {
      try {
        manager.redo();
      } catch (CannotRedoException e) {
        Toolkit.getDefaultToolkit().beep();
      }
    }

    private UndoManager manager;
  }

  public static void main(String[] args) {
    try {
        UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
    } catch (Exception evt) {}
  
    JFrame f = new UndoExample4();
    f.addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent evt) {
        System.exit(0);
      }
    });
    f.pack();
    f.setVisible(true);
  }
}
class UndoableTree2 extends JTree {
  public UndoableTree2(TreeNode root) {
    super(root);
  }

  public void addUndoableEditListener(UndoableEditListener l) {
    support.addUndoableEditListener(l);
  }

  public void removeUndoableEditListener(UndoableEditListener l) {
    support.removeUndoableEditListener(l);
  }

	@Override
  public void collapsePath(TreePath path) {
    boolean wasExpanded = isExpanded(path);
    TreePath[] selections = getSelectionPaths();

    super.collapsePath(path);

    boolean isExpanded = isExpanded(path);
    if (isExpanded != wasExpanded) {
      TreePath[] newSelections = getSelectionPaths();
      support.beginUpdate();
      support.postEdit(new SelectionEdit(selections, newSelections));
      support.postEdit(new CollapseEdit(path));
      support.endUpdate();
    }
  }

  public void expandPath(TreePath path) {
    boolean wasExpanded = isExpanded(path);
    TreePath[] selections = getSelectionPaths();

    super.expandPath(path);

    boolean isExpanded = isExpanded(path);
    if (isExpanded != wasExpanded) {
      TreePath[] newSelections = getSelectionPaths();
      support.beginUpdate();
      support.postEdit(new SelectionEdit(selections, newSelections));
      support.postEdit(new ExpandEdit(path));
      support.endUpdate();
    }
  }

  private void undoExpansion(TreePath path) {
    super.collapsePath(path);
  }

  private void undoCollapse(TreePath path) {
    super.expandPath(path);
  }

  private class CollapseEdit extends AbstractUndoableEdit {
    public CollapseEdit(TreePath path) {
      this.path = path;
    }

    public void undo() throws CannotUndoException {
      super.undo();
      UndoableTree2.this.undoCollapse(path);
    }

    public void redo() throws CannotRedoException {
      super.redo();
      UndoableTree2.this.undoExpansion(path);
    }

    public String getPresentationName() {
      return "node collapse";
    }

    private TreePath path;
  }

  private class ExpandEdit extends AbstractUndoableEdit {
    public ExpandEdit(TreePath path) {
      this.path = path;
    }

		@Override
    public void undo() throws CannotUndoException {
      super.undo();
      UndoableTree2.this.undoExpansion(path);
    }

    public void redo() throws CannotRedoException {
      super.redo();
      UndoableTree2.this.undoCollapse(path);
    }

    public String getPresentationName() {
      return "node expansion";
    }

    private TreePath path;
  }

  private class SelectionEdit extends AbstractUndoableEdit {
    public SelectionEdit(TreePath[] oldSelections, TreePath[] newSelections) {
      this.oldSelections = oldSelections;
      this.newSelections = newSelections;
    }

    public void undo() throws CannotUndoException {
      super.undo();
      UndoableTree2.this.setSelectionPaths(oldSelections);
    }

    public void redo() throws CannotRedoException {
      super.redo();
      UndoableTree2.this.setSelectionPaths(newSelections);
    }

    public String getPresentationName() {
      return "selection change";
    }

    private TreePath[] oldSelections;

    private TreePath[] newSelections;
  }

  private UndoableEditSupport support = new UndoableEditSupport(this);
}

      