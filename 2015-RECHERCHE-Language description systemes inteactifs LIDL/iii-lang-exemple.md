


interaction affect(reception a, emission b)
  custom
  // affectation (i.e.    b = a  )

interaction all(interaction... x)
  custom
  // do all the x behavior

interaction when(boolean reception a,behavior x)
  affect(a,active(x))
  custom
  // affectations in behavior x are only effective when a is true
  // we do this by encapsulating every reception of any affect inside a if(a,inactive,theActualReception)

interaction anyway(behavior x)
  affect(true,active(x))
  custom
  // cancels the restricting effect of when in which it is nested

boolean reception init()
  custom
  // boolean true on the very first step

boolean reception active(reception a)
  custom
  // boolean true if a is active

number reception random(number reception a)
  custom
  // returns a real number between 0 included and a excluded

number reception round(number reception a,number reception precision)
  custom
  // returns the multiple of precision closest to number a

number reception floor(number reception a)
  custom
  // returns the floor of number a

number reception crop(number reception number, number reception min, number reception max)
  custom
  // crop a number between min and max

number reception size(behavior a)
  custom
  // returns the size of a

interaction onInit(interaction a)
  anyway(when(init(),a))

interaction flow(emission ae, reception ar, reception achange)
  affect(if(active(achange),achange,previous(ar)),ae)
  // normally, ae=ar is a variable
  // ae = previous(ar) except if achange
  // flow(a,a,aNew)

number reception anIndexOf([interaction] a)
  affect(round(random(size(x)),1),this)

interaction either(interaction... a)
  variable number pick
  a[anIndexOf(a)]

interaction pickOneOfThemAndTellWhich(number emission choice, [interaction] a)
  affect(anIndexOf(x),choice)
  a[anIndexOf(a)]




interaction test():
  {lol:interaction,wow:interaction}




{
  lol:affect(1,x),
  wow:affect(2,y)
}.lol

pickOneOfThemAndTellWhich(choosenBehavior,[affect(1,x),affect(2,y)])

reception factorial(reception n)
  affect(times(n,factorial(n-1)),this)


either(affect(1,x),affect(2,x))



interaction speedController({inc:void,dec:void} reception controlsFromDriver, number emission speedToCar)
  affect(incDec(controlsFromDriver.inc,controlsFromDriver.dec,50,150,5),speedToCar)



number reception incDec(void reception inc, void reception dec, number reception min, number reception max,number reception step)
  variable number this
  variable number rawResult
  [
    when(active(inc),affect(previous(this)+step,rawResult)),
    when(active(dec),affect(previous(this)-step,rawResult)),
    affect(crop(round(rawResult,step),min,max),this)
  ]

number reception incDec(void reception inc, void reception dec, {min:number,max:number,step:number} reception parameters)
  incDec(inc, dec, parameters.min, parameters.max,parameters.step)





reception currentValueOf(reception r)
  variable newValue
  [
    affect(r,newValue),
    anyway(affect(append(newValue,previous(this)),this))
  ]


interaction afterDelay(time reception time,time reception delay,interaction a)
  time variable triggerTime
  [
    affect(time,triggerTime),
    anyway(
      when(and(time-triggerTime>delay,not(previous(time-triggerTime>delay))),
        a
      )
    )
  ]


reception delay(time reception time, time reception delay, reception value)
  when(active(value),
    afterDelay(time,delay,affect(value,this))
  )


// ===> becomes

reception delay(time reception time, time reception delay, reception value)
  affect(if(and(time-if(active(value),time,inactive)>delay,not(previous(time-if(active(value),time,inactive)>delay))),value,inactive),this)






































///////////////////////////////////// Trash


behavior say(String reception thingToSay)
  external SpeakerChannel speaker

  affect(thingToSay,speaker.output)






when(clicked,
  afterDelay(time,5s,say("whoohoo"))
)
