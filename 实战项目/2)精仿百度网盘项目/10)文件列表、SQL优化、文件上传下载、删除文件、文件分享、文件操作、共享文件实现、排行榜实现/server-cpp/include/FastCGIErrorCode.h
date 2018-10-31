#pragma once

namespace itcast
{
    enum ResponseCode
    {
        Succ = 0,
        Error = 1,

        //Error with user info
        UserError=10,
        UserExists=11,
        UserNotLogin,
        UserInvalid,

        //Error with file
        FileError=20, 
        FileExists,
        FileNotExists
    };
}
