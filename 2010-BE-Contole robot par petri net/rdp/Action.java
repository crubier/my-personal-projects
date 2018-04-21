package rdp;


public class Action {

    /* ATTRIBUTES */

    private int numero;
    private int parametre;

    public Action(){

    }

    public Action(int num, int param){

    this.numero=num;
    this.parametre=param;

    }

    /* METHODS */

  

    /* GETTERS */
    
    public int GetNumero(){

        return this.numero;

    }
    
    public int GetParametre(){

        return this.parametre;

    }
    


    /* SETTERS */

    public void SetNumero(int num){

        this.numero=num;

    }

    public void SetParametre(int param){

        this.parametre=param;

    }

}

