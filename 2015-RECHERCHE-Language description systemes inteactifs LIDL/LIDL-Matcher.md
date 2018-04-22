
interface
  Constructor T
is
  T out

interface
  Destructor T
is
  T in

interface
  Matcher T
is
  {v:T in, x:Activation out}






data
  AlarmAction
is
  (ack (Number) | proc | clr | cancel)




// Constructor
interaction
  (ack(x:Number in)):Constructor AlarmAction

interaction
  (proc):Constructor AlarmAction

interaction
  (clr):Constructor AlarmAction

interaction
  (cancel):Constructor AlarmAction




// Destructor
interaction
  (ack(x:Number out)):Destructor AlarmAction

interaction
  (proc):Destructor AlarmAction

interaction
  (clr):Destructor AlarmAction

interaction
  (cancel):Destructor AlarmAction





// Matcher
interaction
  (ack(x:Constructor Number)):Matcher AlarmAction

interaction
  (ack(x:Matcher Number)):Matcher AlarmAction

interaction
  (proc):Matcher AlarmAction

interaction
  (clr):Matcher AlarmAction

interaction
  (cancel):Matcher AlarmAction





data
  Couple T1 T2
is
  ( (T1),(T2) )



interaction
  ((a:Matcher T1)    ,(b:Matcher T2))    :  Matcher (Couple T1 T2)

interaction
  ((a:Matcher T1)    ,(b:Constructor T2)):  Matcher (Couple T1 T2)

interaction
  ((a:Constructor T1),(b:Matcher T2))    :  Matcher (Couple T1 T2)

interaction
  ((a:Constructor T1),(b:Constructor T2)):  Matcher (Couple T1 T2)






 interaction
   ( switch (x:T in)  (y:I)
     case   (ax:T in) (ay:I')
     case   (bx:T in) (by:I')
     case   (cx:T in) (cy:I')
     default          (zy:I')
   )
