testScreens: testReport: showModiﬁer2
Commit Records/Requests
If [ TEMP::kmodiﬁer2 = "" ]
Set Field [ TEMP::modiﬁer2name; "" ]
Exit Script [ ]
End If
#
#the pulldown menu action selects the id number,
#but not the name. To put the name into the TEMP
#global ﬁeld we will need to ﬁnd it which is what the
#rest of the script does.
Set Variable [ $mod; Value:TEMP::kmodiﬁer2 ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::_Ltag; $mod ]
Perform Find [ ]
Set Variable [ $name; Value:tagTable::tag ]
Go to Layout [ original layout ]
Set Field [ TEMP::modiﬁer2name; $name ]
Go to Field [ ]
#
#Tells user to select an order number not in use
#if the order ﬁeld is blank.
If [ TEMP::orderMod2 = "" ]
Show Custom Dialog [ Message: "Select an order number to place modiﬁer before or after currently selected location: small location or location upstairs for example."; Buttons: “OK” ]
Go to Field [ TEMP::orderMod2 ]
End If
January 7, 平成26 14:15:30 Imagination Quality Management.fp7 - showModiﬁer2 -1-
