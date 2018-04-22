(a:time:flow after last b:any:event) behavior:
  currenttime : time flow
  timeofevent : time flow

  on time(t):
    if(t-timeofevent<a)

    currenttime = t

  on b:
    timeofevent = currenttime



update({value:{a:53909222,b:""},t:2303932})

function update(x) {
if(x.value.t)

x.a
}
