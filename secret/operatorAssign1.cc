#include "secret.ih"

Secret &Secret::operator=(Secret &&tmp)
{
    if (this != &tmp) 
    { 
        wipe(); 
        d_data = move(tmp.d_data); 
        if (!tmp.d_data.empty()) 
        {
            sodium_memzero(tmp.d_data.data(), tmp.d_data.size());
            tmp.d_data.clear();
        }
    }
    
    return *this;
}