function [ q] = rot_to_quat( rot)
%ROT_TO_QUAT Summary of this function goes here
%  Detailed explanation goes here

t = trace(rot);
if(t>0)
    s= 1/(2*sqrt(t));
    q(1) = (rot(3,2)-rot(2,3))*s;
    q(2) = (rot(1,3)-rot(3,1))*s;
    q(3) = (rot(2,1)-rot(1,2))*s;
    q(4) = 1/(4*s);
else
    if(rot(1,1)>rot(2,2) && rot(1,1)>rot(3,3))
        s=sqrt(1+rot(1,1)-rot(2,2)-rot(3,3))*2;
        q(1) = 1/(2*s);
        q(2) = (rot(1,2)-rot(2,1))/s;
        q(3) = (rot(1,3)-rot(3,1))/s;
        q(4) = (rot(2,3)-rot(3,2))/s;
    elseif(rot(2,2)>rot(1,1) && rot(2,2)>rot(3,3))
        s=sqrt(1-rot(1,1)+rot(2,2)-rot(3,3))*2;
        q(2) = 1/(2*s);
        q(1) = (rot(1,2)-rot(2,1))/s;
        q(4) = (rot(1,3)-rot(3,1))/s;
        q(3) = (rot(2,3)-rot(3,2))/s;
        
   elseif(rot(3,3)>rot(1,1) && rot(3,3)>rot(2,2))
          
        s=sqrt(1-rot(1,1)-rot(2,2)+rot(3,3))*2;
        q(3) = 1/(2*s);
        q(4) = (rot(1,2)-rot(2,1))/s;
        q(1) = (rot(1,3)-rot(3,1))/s;
        q(2) = (rot(2,3)-rot(3,2))/s;
        
    else
          
        s=sqrt(1-rot(1,1)-rot(2,2)+rot(3,3))*2;
        q(3) = 1/(2*s);
        q(4) = (rot(1,2)-rot(2,1))/s;
        q(1) = (rot(1,3)-rot(3,1))/s;
        q(2) = (rot(2,3)-rot(3,2))/s;
    
    end
end



