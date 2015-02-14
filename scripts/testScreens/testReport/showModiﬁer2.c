testScreens: testReport: showModifier2
Commit Records/Requests
If [ TEMP::kmodifier2 = "" ]
Set Field [ TEMP::modifier2name; "" ]
Exit Script [ ]
End If
#
#the pulldown menu action selects the id number,
#but not the name. To put the name into the TEMP
#global field we will need to find it which is what the
#rest of the script does.
Set Variable [ $mod; Value:TEMP::kmodifier2 ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::_Ltag; $mod ]
Perform Find [ ]
Set Variable [ $name; Value:tagTable::tag ]
Go to Layout [ original layout ]
Set Field [ TEMP::modifier2name; $name ]
Go to Field [ ]
#
#Tells user to select an order number not in use
#if the order field is blank.
If [ TEMP::orderMod2 = "" ]
Show Custom Dialog [ Message: "Select an order number to place modifier before or after currently selected location: small location or location upstairs for example."; Buttons: “OK” ]
Go to Field [ TEMP::orderMod2 ]
End If
January 7, 平成26 14:15:30 Imagination Quality Management.fp7 - showModifier2 -1-
