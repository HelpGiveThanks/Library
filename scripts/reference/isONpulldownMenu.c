January 18, 2018 14:42:08 Library.fmp12 - isONpulldownMenu -1-
reference: isONpulldownMenu
#
#
#Clear the other fields.
Set Field [ reference::otherIsOn; "" ]
Set Field [ reference::otherIsWhat; "" ]
#
#Clear the 'What is it?' key.
Set Field [ reference::kisWhat; "" ]
#
#If 'What is it?' insert other's key.
If [ Left (isON::key ; 1 ) = 9 ]
Set Field [ reference::kisWhat; 5122017153755111 ]
End If
#
#copyright tags are, then exit the script.
If [ isON::key = 9.1 ]
Set Field [ reference::otherIsWhat; "database" ]
Go to Field [ reference::otherIsWhat ]
Else If [ isON::key = 9.2 ]
Set Field [ reference::otherIsWhat; "broadcast" ]
Go to Field [ reference::otherIsWhat ]
Else If [ isON::key = 9.3 ]
Set Field [ reference::otherIsWhat; "museum" ]
Go to Field [ reference::otherIsWhat ]
Else If [ isON::key = 9.4 ]
Set Field [ reference::otherIsWhat; "conversation" ]
Go to Field [ reference::otherIsWhat ]
Else If [ isON::key = 9.5 ]
Set Field [ reference::otherIsWhat; "computer" ]
Go to Field [ reference::otherIsWhat ]
Else If [ isON::key = 9.6 ]
Set Field [ reference::otherIsWhat; "experience" ]
Go to Field [ reference::otherIsWhat ]
Else If [ isON::key = 9.7 ]
Set Field [ reference::otherIsWhat; "painting" ]
Go to Field [ reference::otherIsWhat ]
Else If [ isON::key = 9.8 ]
Set Field [ reference::otherIsWhat; "performance" ]
Go to Field [ reference::otherIsWhat ]
Else If [ isON::key = 9.9 ]
Set Field [ reference::otherIsWhat; "presentation" ]
Go to Field [ reference::otherIsWhat ]
Else
Go to Field [ ]
End If
#
Halt Script
#
