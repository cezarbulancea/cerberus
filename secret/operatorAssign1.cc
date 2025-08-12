#include "secret.ih"

Secret &Secret::operator=(Secret &&tmp)
{
    if (this != &tmp) 
    { 
        wipe(); 
        d_data = move(tmp.d_data); 
    }
    
    return *this;
}